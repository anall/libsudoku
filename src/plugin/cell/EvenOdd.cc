#include <sudoku/Puzzle.h>
#include <sudoku/plugin/cell/EvenOdd.h>
#include <sudoku/exception/Exception.h>
#include <sudoku/exception/PuzzleSizeMismatch.h>

namespace sudoku {namespace plugin {namespace cell {
    EvenOdd::EvenOdd(int cells) : sudoku::plugin::Cell(), _cells(cells) {
        int sz = cells * cells;
        _data = new EvenOddFlag[sz];
        memset(_data, 0, sizeof(EvenOddFlag) * sz);
    }
    EvenOdd::EvenOdd(const EvenOdd &other) : sudoku::plugin::Cell(), _cells(other._cells) {
        int sz = _cells * _cells;
        _data = new EvenOddFlag[sz];
        memcpy(_data, other._data, sizeof(EvenOddFlag) * sz);
    }

    EvenOdd::~EvenOdd() {
        delete[] _data;
    }

    void EvenOdd::validateForPuzzle(sudoku::Puzzle *puzzle) throw(sudoku::exception::Exception){
        if ( puzzle->size() != _cells )
            throw sudoku::exception::PuzzleSizeMismatch("Even/Odd plugin size mismatch",puzzle->size(),_cells);
    }

    sudoku::Cell *EvenOdd::makeCellForPuzzle(sudoku::Puzzle *puzzle, Position pos) {
        EvenOddFlag flag = _data[pos.idForSize(_cells)];
        if ( flag != NONE )
            return new EvenOdd::Cell(pos, puzzle, flag);
        else
            return NULL;
    }

    EvenOdd::Cell::Cell(Position pos, sudoku::Puzzle *puz, EvenOddFlag flag) : sudoku::Cell(pos,puz), _flag(flag) {
    }

    EvenOdd::Cell::Cell(Cell &sv, CloneHelper *ch) : sudoku::Cell(sv, ch), _flag(sv._flag) {
    }

    bool EvenOdd::Cell::validateValue(int v) {
        if ( ! sudoku::Cell::validateValue(v) ) return false;
        if ( _flag == EVEN && ( v & 1 ) == 1 )
            return false;
        else if ( _flag == ODD && ( v & 1 ) == 0 )
            return false;
        else
            return true;
    }

    void EvenOdd::Cell::resetPencil() {
        sudoku::Cell::resetPencil();
        if ( value() ) return;
        if ( _flag == NONE ) return;
        for ( int i = 1; i <= puzzle()->size(); i++ ) {
            if ( _flag == EVEN && ( i & 1 ) == 1 ) {
                pencil(i) = 0;
            } else if (  _flag == ODD && ( i & 1 ) == 0 ) {
                pencil(i) = 0;
            }
        }
    }
}}}