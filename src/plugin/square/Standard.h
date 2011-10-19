#ifndef __SUDOKU__PLUGIN__SQUARE__STANDARD_H__
#define __SUDOKU__PLUGIN__SQUARE__STANDARD_H__
#include <sudoku/plugin/Square.h>
#include <sudoku/exception/Exception.h>

namespace sudoku {
    namespace plugin { namespace square {
        class Standard : public Square {
        private:
            void setupForSquare(sudoku::Puzzle *pz, int ct);
            void setupForRectangle(sudoku::Puzzle *pz, int ct);
        public:
            Standard();

            virtual void validateForPuzzle(sudoku::Puzzle *puzzle) throw(sudoku::exception::Exception);
            virtual void addSquareSets(sudoku::Puzzle *pz);

            virtual Ref<Square> clone() {
                return this;
            }

            class InvalidShape : public sudoku::exception::Exception {
            public:
                InvalidShape() throw() : sudoku::exception::Exception() {}
                virtual ~InvalidShape() throw() {}

                virtual const char* what() const throw() { return "Invalid shape"; }
            };
        };
    }}
}

#endif