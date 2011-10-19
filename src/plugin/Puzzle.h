#ifndef __SUDOKU__PLUGIN__PUZZLE_H__
#define __SUDOKU__PLUGIN__PUZZLE_H__
#include <sudoku/exception/Exception.h>
#include <sudoku/Ref.h>

namespace sudoku {
    class Puzzle;

    namespace plugin {
        class Puzzle : public Counted {
        public:
            Puzzle();
            virtual ~Puzzle();

            virtual void validateForPuzzle(sudoku::Puzzle *puzzle)  { return; }
            virtual void addExtraSets(sudoku::Puzzle *pz) = 0;

            virtual Ref<Puzzle> clone() = 0;
        };
    }
}

#endif