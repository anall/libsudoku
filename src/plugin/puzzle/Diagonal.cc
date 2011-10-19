#include <sudoku/Puzzle.h>
#include <sudoku/CellSet.h>
#include <sudoku/plugin/puzzle/Diagonal.h>

namespace sudoku {namespace plugin {namespace puzzle {
    Diagonal::Diagonal() {}
    Diagonal::~Diagonal() {}

    void Diagonal::addExtraSets(sudoku::Puzzle *pz) {
        int size = pz->size();
        std::vector<CellSet *> &cellsets = pz->cellsets();

        CellSet *cs;

        cs = new CellSet(pz);
        cellsets.push_back(cs);
        for ( int i = 0; i < size; i++ ) {
            Position p(i,i);
            cs->push_back(p);
            pz->cell(p)->registerForCellSet(cs);
        }

        cs = new CellSet(pz);
        cellsets.push_back(cs);
        for ( int i = 0; i < size; i++ ) {
            Position p(i, pz->size() - i - 1);
            cs->push_back(p);
            pz->cell(p)->registerForCellSet(cs);
        }
    }
}}}