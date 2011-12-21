#ifndef __SUDOKU__PLUGIN__SQUARE__IRREGULAR_H__
#define __SUDOKU__PLUGIN__SQUARE__IRREGULAR_H__
#include <vector>
#include <sudoku/Position.h>
#include <sudoku/plugin/Square.h>
#include <sudoku/exception/Exception.h>

namespace sudoku {
    namespace plugin { namespace square {
        class Irregular : public Square {
        private:
            std::vector<std::vector<Position> > _squares;
        public:
            Irregular();
            Irregular(const Irregular &other);

            void addSquare(std::vector<Position> &sq);

            virtual void validateForPuzzle(sudoku::Puzzle *puzzle);
            virtual void addSquareSets(sudoku::Puzzle *pz);

            virtual Ref<Square> clone() {
                return new Irregular(*this);
            }
        };
    }}
}

#endif