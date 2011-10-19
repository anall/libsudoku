/*
 * Copyright 2010-2011 Andrea Nall
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sudoku/Cell.h>
#include <sudoku/CellSet.h>
#include <sudoku/Puzzle.h>
#include <sudoku/CloneHelper.h>
#include <sudoku/exception/InvalidCellValue.h>
#include <sudoku/exception/OutOfRange.h>

#include <assert.h>

namespace sudoku {
    Cell::Cell(Position pos, Puzzle *puz) : _pos(pos), _puz(puz), _value(0), _sqId(-1) {
        int size = puz->size();
        _pencil = new bool[size];
    }

    Cell::Cell(const Cell &other, CloneHelper *ch) : _pos(other._pos), _value(other._value), _sqId(other._sqId) {
        _puz = ch->puzzle();
        int size = _puz->size();
        _pencil = new bool[size];
        memcpy(_pencil, other._pencil, sizeof(bool) * size);
        _cellsets = ch->remapCellSets(other._cellsets);
        assert(other._cellsets.size() == _cellsets.size());
    }

    Cell::~Cell() {
        delete[] _pencil;
    }

    void Cell::resetPencil() {
        if (_value)
            memset(_pencil, 0, sizeof(bool) * _puz->size());
        else
            memset(_pencil, 1, sizeof(bool) * _puz->size());
    }

    bool Cell::validateValue(int v) {
        if ( v < 0 || v > _puz->size() ) return false;
        return true;
    }

    bool Cell::value(int v) throw(sudoku::exception::Exception){
        _value = v;
        if ( v == 0 ) return true;
        if ( ! validateValue(v) ) {
            throw sudoku::exception::InvalidCellValue("Invalid value",_pos,v);
            return false;
        }
        memset(_pencil, 0, sizeof(bool) * _puz->size());
        std::vector<CellSet *>::iterator it;
        for ( it = _cellsets.begin(); it < _cellsets.end(); it++ )
            (*it)->unpencil(v);
        return true;
    }

    void Cell::unpencil(int v) {
        if ( _value != 0 ) return;
        if ( v < 0 || v > _puz->size() ) return;
        if (v)
            _pencil[v - 1] = 0;
        int ct = 0;
        for ( int i = 0; i < _puz->size(); i++ )
            if ( _pencil[i] ) ct++;
        assert( ct != _puz->size() && "Invalid count after unpenciling" );
    }

    Cell *Cell::clone(CloneHelper *ch) {
        return new Cell(*this,ch);
    }

    int Cell::pencilCount() {
        int ct = 0;
        for ( int i = 0; i < _puz->size(); i++ )
            if ( _pencil[i] ) ct++;
        return ct;
    }

    bool Cell::solvable() {
        return value() != 0 || pencilCount() > 0;
    }

    bool &Cell::operator[](int i) {
        if ( i >= 0 && i < _puz->size() )
            return _pencil[i];
        throw sudoku::exception::OutOfRange("pencil value",i,0,_puz->size()-1);
    }

    bool Cell::operator[](int i) const {
        if ( i >= 0 && i < _puz->size() )
            return _pencil[i];
        return false;
    }

    bool &Cell::pencil(int i) {
        if ( i > 0 && i <= _puz->size() )
            return _pencil[i - 1];
        throw sudoku::exception::OutOfRange("pencil value",i,1,_puz->size());
    }
}