#include <sudoku/Puzzle.h>
#include <sudoku/CellSet.h>
#include <sudoku/Cell.h>
#include <sudoku/plugin/square/Irregular.h>
#include <sudoku/exception/PuzzleSizeMismatch.h>

namespace sudoku {namespace plugin {namespace square {
    Irregular::Irregular() : Square() {}
    Irregular::Irregular(const Irregular &other) : Square(), _squares(other._squares) {}

    void Irregular::addSquare(std::vector<Position> &sq) {
        _squares.push_back(sq);
    }

    void Irregular::validateForPuzzle(sudoku::Puzzle *pz) throw(sudoku::exception::Exception){
        unsigned int sz = pz->size();
        if ( _squares.size() != sz ) {
            throw sudoku::exception::PuzzleSizeMismatch("Insufficient squares",sz,_squares.size());
            return;
        }
        for ( std::vector<std::vector<Position> >::iterator it = _squares.begin(); it < _squares.end(); it++ ) {
            if ( (*it).size() != sz ) {
                throw sudoku::exception::PuzzleSizeMismatch("Cellset wrong length",sz,(*it).size());
                return;
            }
        }
        return;
    }

    void Irregular::addSquareSets(sudoku::Puzzle *pz) {
        std::vector<CellSet *> &cellsets = pz->cellsets();
        int sqId = 0;
        for ( std::vector<std::vector<Position> >::iterator it = _squares.begin(); it < _squares.end(); it++ ) {
            CellSet *cs = new CellSet(pz);
            std::vector<Position> &pv = *it;
            sqId++;
            for ( std::vector<Position>::iterator pit = pv.begin(); pit < pv.end(); pit++ ) {
                cs->push_back(*pit);
                sudoku::Cell *cl = pz->cell(*pit);
                cl->sqId(sqId);
                cl->registerForCellSet(cs);
            }
            cellsets.push_back(cs);
        }
    }
}}}