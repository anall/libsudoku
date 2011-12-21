#include <sudoku/Puzzle.h>
#include <sudoku/CellSet.h>
#include <sudoku/Cell.h>
#include <sudoku/plugin/square/Standard.h>
#include <math.h>

#include <assert.h>

namespace sudoku {namespace plugin {namespace square {
    Standard::Standard() {}

    void Standard::setupForSquare(sudoku::Puzzle *pz, int sqrt_sz) {
        std::vector<CellSet *> &cellsets = pz->cellsets();
        int sqId = 0;
        for ( int r = 0; r < sqrt_sz; r++ ) {
            int rbase = r * sqrt_sz;
            for ( int c = 0; c < sqrt_sz; c++ ) {
                int cbase = c * sqrt_sz;
                CellSet *cs = new CellSet(pz);
                cellsets.push_back(cs);
                sqId++;
                for ( int ir = 0; ir < sqrt_sz; ir++ ) {
                    for ( int ic = 0; ic < sqrt_sz; ic++ ) {
                        Position p = Position(rbase + ir, cbase + ic);
                        sudoku::Cell *cl = pz->cell( p );
                        cs->push_back(p);
                        cl->sqId(sqId);
                        cl->registerForCellSet(cs);
                    }
                }
            }
        }
    }

    void Standard::setupForRectangle(sudoku::Puzzle *pz, int sz) {
        std::vector<CellSet *> &cellsets = pz->cellsets();
        int sqId = 0;
        for ( int r = 0; r < sz; r++ ) {
            int rbase = r * (sz + 1);
            for ( int c = 0; c < (sz + 1); c++ ) {
                int cbase = c * sz;
                CellSet *cs = new CellSet(pz);
                cellsets.push_back(cs);
                sqId++;
                for ( int ir = 0; ir < (sz+1); ir++ ) {
                    for ( int ic = 0; ic < sz; ic++ ) {
                        Position p = Position(rbase + ir, cbase + ic);
                        sudoku::Cell *cl = pz->cell( p );
                        cs->push_back(p);
                        cl->sqId(sqId);
                        cl->registerForCellSet(cs);
                    }
                }
            }
        }
    }

    void Standard::validateForPuzzle(sudoku::Puzzle *pz) {
        int size = pz->size();
        float sqrt_sz_f = sqrt((float)size);
        int sqrt_sz = (int)sqrt_sz_f;

        if ( (float)sqrt_sz_f == sqrt_sz ) return;
        else if ( sqrt_sz * (sqrt_sz+1) == size ) return;
        else throw InvalidShape();
    }

    void Standard::addSquareSets(sudoku::Puzzle *pz) {
        int size = pz->size();
        float sqrt_sz_f = sqrt((float)size);
        int sqrt_sz = (int)sqrt_sz_f;
        if ( (float)sqrt_sz_f == sqrt_sz ) setupForSquare(pz, sqrt_sz);
        else if ( sqrt_sz * ( sqrt_sz + 1 ) == size ) setupForRectangle(pz, sqrt_sz);
    }
}}}