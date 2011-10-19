#ifndef __SUDOKU__PLUGIN__PUZZLE__DIAGONAL_H__
#define __SUDOKU__PLUGIN__PUZZLE__DIAGONAL_H__
#include <sudoku/plugin/Puzzle.h>
#include <sudoku/Cell.h>

namespace sudoku {
    class Puzzle;

    namespace plugin { namespace puzzle {
        class Diagonal : public sudoku::plugin::Puzzle {
        public:
            Diagonal();
            virtual ~Diagonal();

            virtual void addExtraSets(sudoku::Puzzle *pz);

            virtual Ref<Puzzle> clone() {
                return this;
            }
        };
    }}
}

#endif