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

#ifndef __SUDOKU__CELL_H__
#define __SUDOKU__CELL_H__
#include <vector>
#include <sudoku/Position.h>

namespace sudoku {
    class Puzzle;
    class CellSet;
    class CloneHelper;

    class Cell {
    private:
        Position _pos;
        Puzzle *_puz;
        int _value;
        bool *_pencil;
        int _sqId;

        std::vector<CellSet *> _cellsets;
    public:
        Cell(Position pos, Puzzle *puz);
        Cell(const Cell &other, CloneHelper *ch);

        virtual Cell *clone(CloneHelper *ch);
        virtual ~Cell();

        void registerForCellSet(CellSet *cs) { _cellsets.push_back(cs); }

        Puzzle *puzzle() { return _puz; }
        Position position() { return _pos; }

        int value() const { return _value; }
        bool value(int v) throw(sudoku::exception::Exception);
        virtual bool validateValue(int v);

        int sqId() const { return _sqId; }
        void sqId(int sqId) { _sqId = sqId; }

        void unpencil(int v);

        virtual void resetPencil();

        bool &operator[](int i);
        bool operator[](int i) const;
        bool &pencil(int i);

        const std::vector<CellSet *> &cellsets() const { return _cellsets; }

        int pencilCount();
        bool solvable();
    };
}

#endif