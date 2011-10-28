/*
 * Copyright 2010-2011 Andrea Nall
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>
#include <sudoku/Solver.h>
#include <sudoku/Puzzle.h>
#include <sudoku/CellSet.h>
#include <sudoku/Cell.h>

#include <stdio.h>
#include <assert.h>

namespace sudoku {
    static int phase1_alone(Ref<Puzzle> pz, CellSet *cs);


#ifdef DEBUG
    const char *Solver::solveMethod::_empty = "";
#endif

    static const Solver::solveMethod methods[] = {
        Solver::solveMethod(phase1_alone, "only poss"),
        0
    };

    Solver::Solver(Ref<Puzzle> pz, bool allowRecurse, SolverSettings settings, Ref<SolverCallbacks> cb ) : _iters(0), _bfIters(0), _solutionCt(0), _settings(settings), _allowRecurse(allowRecurse), _callbacks(cb) {
        _pz = new Puzzle(pz);
    }

    Solver::Solver(const Solver &sv, Ref<Puzzle> pz ) : _pz(pz), _iters(sv._iters), _bfIters(sv._bfIters), _solutionCt(sv._solutionCt), _settings(sv._settings), _allowRecurse(sv._allowRecurse), _callbacks(sv._callbacks) {
    }

    void Solver::solve() {
        if ( _pz->solved() || ! _pz->solvable() ) return;
        solveSingle();
        if ( _pz->solved() ) {
            _solutionCt++;
            _solutions.push_back(_pz);
            if ( _callbacks )
                _callbacks->gotSolution( _pz );
        }
        if ( _pz->solved() || ! _pz->solvable() ) return;
        if ( _allowRecurse && _bfIters < _settings.bruteIterLimit && _solutionCt < _settings.maxSolutions )
            solveBrute();
    }

    /* UNUSED>
    static void copyValues(Ref<Puzzle> to, Ref<Puzzle> from) {
        assert( to->size() == from->size() );
        std::vector<Cell *> &cells = from->cells();
        std::vector<Cell *>::iterator it;
        for ( it = cells.begin(); it < cells.end(); it++ ) {
            Cell *fc = *it;
            Cell *tc = to->cell(fc->position());
            if ( fc->value() == 0 ) continue;
            if ( tc->value() ) continue;
            tc->value(fc->value());
        }
    } */

    void Solver::solveBrute() {
        if ( _bfIters % 100 == 0 ) {
            printf("Brute iter %i / %i\n",_bfIters,_settings.bruteIterLimit);
        }
        _bfIters++;
        // find an unset cell with the fewest options!
        int sz = _pz->size();
        int ct = sz + 1;
        Cell *cl = 0;
        std::vector<Cell *> &cells = _pz->cells();
        std::vector<Cell *>::iterator it;
        for ( it = cells.begin(); it < cells.end(); it++ ) {
            if ( (*it)->value() != 0 ) continue;
            int ict = (*it)->pencilCount();
            if ( ict < ct ) {
                ct = ict;
                cl = *it;
            }
        }
        if ( ct == sz + 1 ) return;
        for ( int i = 1; i <= sz; i++ ) {
            if ( cl->pencil(i) == false ) continue;
            Ref<Puzzle> npz = new Puzzle( _pz );
            npz->cell(cl->position())->value(i);
            if ( npz->solved() ) {
                _solutionCt++;
                _solutions.push_back(npz);
                if ( _callbacks )
                    _callbacks->gotSolution( npz );
                return; // If we're solved here, there's probably not another solution
            } else if ( npz->solvable() ) {
                Solver slv(*this,npz);
                slv.solve();
                _solutions.insert( _solutions.end(), slv._solutions.begin(), slv._solutions.end() );
                _iters = slv._iters;
                _bfIters = slv._bfIters;
                _solutionCt = slv._solutionCt;
            }
            if ( _solutionCt >= _settings.maxSolutions ) return;
        }
    }

    void Solver::solveSingle() {
        int iters = 0;
        int dn = -1;
        int idn = -1;
        _pz->ready(true);
        while ( dn != 0 && iters < _settings.iterLimit ) {
            dn = 0;
            const Solver::solveMethod *mthd = methods;
            while ( mthd->exists() && iters < _settings.iterLimit ) {
                do {
                    idn = mthd->solveUsing(_pz);
                    if ( _pz->solved() || ! _pz->solvable() ) return;
                    dn += idn;
                    iters++;
                    _iters++;
                } while (idn != 0 && iters < _settings.iterLimit );
                mthd++;
            }
        }
    }

    Solver::solveMethod::solveMethod(solveMethodSub ms, const char *name) : _mthd(ms) {
#ifdef DEBUG
        _name = name;
#endif
    }

#ifdef DEBUG
    const char *Solver::solveMethod::name() const { return _name; }
#endif
    bool Solver::solveMethod::exists() const { return _mthd != NULL; }

    int Solver::solveMethod::solveUsing(Ref<Puzzle> pz) const {
        std::vector<CellSet *> &css = pz->cellsets();
        std::vector<CellSet *>::iterator it;
        int ct = 0;
        for ( it = css.begin() ; it < css.end(); it++ )
            ct += _mthd(pz,*it);
        return ct;
    }

    int phase1_alone(Ref<Puzzle> pz, CellSet *cs) {
        std::vector<Position>::iterator it;
        unsigned int sz = pz->size();
        int *cts = new int[sz];
        Cell **cls = new Cell*[sz];
        Cell **cla = new Cell*[sz];
        memset(cts,0,sizeof(int) * sz);
        memset(cls,0,sizeof(Cell *) * sz);
        memset(cla,0,sizeof(Cell *) * sz);
        if ( sz != cs->size() ) return 0;
        for ( it = cs->begin(); it < cs->end(); it++ ) {
            Cell *ccl = pz->cell(*it);
            int ct = 0;
            int v = 0;

            // This is a gaurd against any problems!
            if ( ( v = ccl->value() ) != 0 ) {
                cts[v-1] = sz + 1;
                continue;
            }

            for ( unsigned int i = 1; i <= sz; i++ ) {
                if ( ccl->pencil(i) ) {
                    v = i;
                    ct++;

                    cts[i-1]++;
                    cls[i-1] = ccl;
                }
            }
            if ( ct == 1 ) {
                cts[v-1]++;
                cla[v-1] = ccl;
            }
        }
        int ct = 0;
        int lct = 0;
        for ( unsigned int i = 0; i < sz; i++ ) {
            lct = ct;
            if ( cla[i] != 0 && cla[i]->value() == 0 ) {
                assert( cla[i]->value() == 0 && "Tried setting an already-set cell" );
                cla[i]->value(i+1);
                ct++;
            }
            if ( cts[i] == 1 && cls[i]->value() == 0 ) {
                assert( cls[i]->value() == 0 && "Tried setting an already set cell" );
                cls[i]->value(i+1);
                ct++;
            }
        }
        delete[] cts;
        delete[] cls;
        delete[] cla;
        return ct;
    }
}
