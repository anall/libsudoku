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

#ifndef __SUDOKU__PUZZLE_H__
#define __SUDOKU__PUZZLE_H__
#include <vector>
#include <sudoku/Position.h>
#include <sudoku/plugin/Cell.h>
#include <sudoku/plugin/Square.h>
#include <sudoku/plugin/Puzzle.h>
#include <sudoku/Ref.h>

namespace sudoku {
    class Cell;
    class CellSet;

    class Puzzle : public Counted {
    protected:
        int _size;
        std::vector<Cell *> _cells;
        std::vector<CellSet *> _cellsets;

        virtual Cell* makeCellForPuzzle(Ref<plugin::Cell> &cellPlugin, Position pos);

        bool _ready;
    public:
        static Ref<Puzzle> create(int size, plugin::Cell *cellPlugin) {
            return Ref<Puzzle>( new Puzzle( size, cellPlugin, Ref<plugin::Square>(), Ref<plugin::Puzzle>() ) );
        }
        static Ref<Puzzle> create(int size, Ref<plugin::Cell> cellPlugin) {
            return Ref<Puzzle>( new Puzzle( size, cellPlugin, Ref<plugin::Square>(), Ref<plugin::Puzzle>() ) );
        }

        static Ref<Puzzle> create(int size, plugin::Square *squarePlugin) {
            return Ref<Puzzle>( new Puzzle( size, Ref<plugin::Cell>(), squarePlugin, Ref<plugin::Puzzle>() ) );
        }
        static Ref<Puzzle> create(int size, Ref<plugin::Square> squarePlugin) {
            return Ref<Puzzle>( new Puzzle( size, Ref<plugin::Cell>(), squarePlugin, Ref<plugin::Puzzle>() ) );
        }

        static Ref<Puzzle> create(int size, plugin::Puzzle *puzzlePlugin) {
            return Ref<Puzzle>( new Puzzle( size, Ref<plugin::Cell>(), Ref<plugin::Square>(), puzzlePlugin ) );
        }
        static Ref<Puzzle> create(int size, Ref<plugin::Puzzle> puzzlePlugin) {
            return Ref<Puzzle>( new Puzzle( size, Ref<plugin::Cell>(), Ref<plugin::Square>(), puzzlePlugin ) );
        }

        static Ref<Puzzle> create(int size, plugin::Cell *cellPlugin, plugin::Square *squarePlugin, plugin::Puzzle *puzzlePlugin) {
            return Ref<Puzzle>( new Puzzle(size,cellPlugin,squarePlugin,puzzlePlugin));
        }
        static Ref<Puzzle> create(int size, Ref<plugin::Cell> cellPlugin = Ref<plugin::Cell>(), Ref<plugin::Square> squarePlugin = Ref<plugin::Square>(), Ref<plugin::Puzzle> puzzlePlugin = Ref<plugin::Puzzle>()) {
            return Ref<Puzzle>( new Puzzle(size,cellPlugin,squarePlugin,puzzlePlugin));
        }

        Puzzle(int size, Ref<plugin::Cell> cellPlugin = Ref<plugin::Cell>(), Ref<plugin::Square> squarePlugin = Ref<plugin::Square>(), Ref<plugin::Puzzle> puzzlePlugin = Ref<plugin::Puzzle>());
        Puzzle(Ref<Puzzle> other);
        ~Puzzle();

        int size() const { return _size; }

        Cell &operator[](Position pos) { return *cell(pos); }
        const Cell *operator[](Position pos) const { return cell(pos); }

        Cell *cell(Position pos) { return _cells[pos.idForSize(_size)]; }
        const Cell *cell(Position pos) const { return _cells[pos.idForSize(_size)];  }

        void resetPencil();
        void disqualifyPencil();

        std::vector<Cell *> &cells() { return _cells; }
        std::vector<CellSet *> &cellsets() { return _cellsets; }

        bool ready() const { return _ready; }
        void ready(bool r) { _ready = r; }

        bool solved();
        bool solvable();
    };
}

#endif