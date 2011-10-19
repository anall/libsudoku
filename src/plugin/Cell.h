#ifndef __SUDOKU__PLUGIN__CELL_H__
#define __SUDOKU__PLUGIN__CELL_H__
#include <sudoku/Position.h>
#include <sudoku/exception/Exception.h>
#include <sudoku/Ref.h>

namespace sudoku {
    class Puzzle;
    class Cell;

    namespace plugin {
        class Cell : public Counted {
        public:
            Cell();
            virtual ~Cell();

            virtual void validateForPuzzle(sudoku::Puzzle *puzzle) { return; }
            virtual sudoku::Cell *makeCellForPuzzle(sudoku::Puzzle *puzzle, Position pos) = 0;

            virtual Ref<Cell> clone() = 0;
        };
    }
}

#endif