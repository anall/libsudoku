#ifndef __SUDOKU__PLUGIN__CELL__EVENODD_H__
#define __SUDOKU__PLUGIN__CELL__EVENODD_H__
#include <sudoku/plugin/Cell.h>
#include <sudoku/exception/Exception.h>
#include <sudoku/Cell.h>
#include <sudoku/CloneHelper.h>

namespace sudoku {
    class Puzzle;

    namespace plugin { namespace cell {
        class EvenOdd : public sudoku::plugin::Cell {
        public:
            enum EvenOddFlag {
                NONE,
                EVEN,
                ODD
            };
        private:
            int _cells;
            EvenOddFlag *_data;
        public:
            EvenOdd(int cells);
            EvenOdd(const EvenOdd &other);
            virtual ~EvenOdd();

            virtual void validateForPuzzle(sudoku::Puzzle *puzzle) throw(sudoku::exception::Exception);
            virtual sudoku::Cell *makeCellForPuzzle(sudoku::Puzzle *puzzle, Position pos);

            virtual Ref<Cell> clone() {
                return new EvenOdd(*this);
            }

            int size() const { return _cells; }

            EvenOddFlag &cell(Position pos) { return _data[pos.idForSize(_cells)]; }
            EvenOddFlag &operator[](Position pos) { return _data[pos.idForSize(_cells)]; }
        public:
            class Cell : public sudoku::Cell {
            private:
                EvenOddFlag _flag;
            public:
                Cell(Position pos, sudoku::Puzzle *puz, EvenOddFlag flag);
                Cell(Cell &sv, CloneHelper *ch);

                virtual void resetPencil();
                virtual bool validateValue(int v);

                virtual sudoku::Cell *clone(CloneHelper *ch) {
                    return new Cell(*this,ch);
                }
            };
        };
    }}
}

#endif