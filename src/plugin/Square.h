#ifndef __SUDOKU__PLUGIN__SQUARE_H__
#define __SUDOKU__PLUGIN__SQUARE_H__
#include <sudoku/exception/Exception.h>
#include <sudoku/Ref.h>

namespace sudoku {
    class Puzzle;

    namespace plugin {
        class Square : public Counted {
        public:
            Square();
            virtual ~Square();

            virtual void validateForPuzzle(sudoku::Puzzle *) throw(sudoku::exception::Exception){ return; }
            virtual void addSquareSets(sudoku::Puzzle *pz) = 0;

            virtual Ref<Square> clone() = 0;
        };
    }
}

#endif
