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

#ifndef __SUDOKU__SOLVER_H__
#define __SUDOKU__SOLVER_H__
#include <stddef.h>
#include <vector>
#include <sudoku/Ref.h>
#include <sudoku/exception/Exception.h>

namespace sudoku {
    class Puzzle;
    class CellSet;

    struct SolverSettings {
        int iterLimit;
        int bruteIterLimit;
        int maxSolutions;

        SolverSettings() {
            iterLimit = 100;
            bruteIterLimit = 30;
            maxSolutions = 6;
        }
    };

    class SolverCallbacks : public Counted {
    protected:
        SolverCallbacks() : Counted() {}
    public:
        virtual void gotSolution(Ref<Puzzle> pz) = 0;
        virtual ~SolverCallbacks() {}
    };

    class Solver {
    private:
        std::vector<Ref<Puzzle> > _solutions;
        Ref<Puzzle> _pz;
        int _iters;
        int _bfIters;
        int _solutionCt;

        SolverSettings _settings;
        Ref<SolverCallbacks> _callbacks;

        bool _allowRecurse;

        Solver(const Solver &sv, Ref<Puzzle> pz );

        void solveSingle();
        void solveBrute();
    public:

        Solver(Ref<Puzzle> pz, bool allowRecurse = true,SolverSettings settings = SolverSettings(), Ref<SolverCallbacks> callbacks = 0 );
        void solve();

        int iters() const { return _iters; }
        int bruteIters() const { return _bfIters; }
        int solutionCount() const { return _solutionCt; }
        std::vector<Ref<Puzzle> > &solutions() { return _solutions; }

        Ref<Puzzle> getBestAttempt() { return _pz; }
    public:
        typedef int (*solveMethodSub)(Ref<Puzzle>, CellSet *);
        class solveMethod {
        private:
#ifdef DEBUG
            static const char *_empty;
#endif
        public:
            solveMethodSub _mthd;
#ifdef DEBUG
            const char *_name;
#endif
        public:
            solveMethod(solveMethodSub ms, const char *name = 0);
#ifdef DEBUG
            const char *name() const;
#endif
            bool exists() const;

            int solveUsing(Ref<Puzzle> pz) const;
        };
    };
}

#endif