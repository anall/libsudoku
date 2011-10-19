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

#include <sudoku/Puzzle.h>
#include <sudoku/Cell.h>
#include <sudoku/CellSet.h>
#include <sudoku/plugin/square/Standard.h>
#include <sudoku/CloneHelper.h>

#include <sudoku/exception/InvalidLayout.h>

namespace sudoku {
    Cell* Puzzle::makeCellForPuzzle(Position pos) {
        Cell *cl = 0;
        if ( _cellPlugin.exists() )
            cl = _cellPlugin->makeCellForPuzzle(this,pos);
        if ( cl == 0 )
            cl = new Cell(pos, this);
        cl->resetPencil();
        return cl;
    }

    Puzzle::Puzzle(int size, Ref<plugin::Cell> cellPlugin, Ref<plugin::Square> squarePlugin, Ref<plugin::Puzzle> puzzlePlugin ) :
            _size(size), _ready(false) {
        if ( cellPlugin.exists() )
            _cellPlugin = cellPlugin->clone();

        if ( squarePlugin.exists() )
            _squarePlugin = squarePlugin->clone();
        else
            _squarePlugin = new plugin::square::Standard();

        if ( puzzlePlugin.exists() )
            _puzzlePlugin = puzzlePlugin->clone();

        if ( _cellPlugin.exists() ) _cellPlugin->validateForPuzzle(this);
        if ( _squarePlugin.exists() ) _squarePlugin->validateForPuzzle(this);
        if ( _puzzlePlugin.exists() ) _puzzlePlugin->validateForPuzzle(this);

        for ( int r = 0; r < _size; r++ ) {
            CellSet *csR = new CellSet(this);
            for ( int c = 0; c < _size; c++ ) {
                Position p = Position(r,c);
                Cell *cl = makeCellForPuzzle(p);
                _cells.push_back(cl);
                cl->registerForCellSet(csR);
                csR->push_back(p);
            }
            _cellsets.push_back(csR);
        }

        for ( int c = 0; c < _size; c++ ) {
            CellSet *csC = new CellSet(this);
            for ( int r = 0; r < _size; r++ ) {
                Position p = Position(r,c);
                Cell *cl = cell(p);
                cl->registerForCellSet(csC);
                csC->push_back(p);
            }
            _cellsets.push_back(csC);
        }

        _squarePlugin->addSquareSets(this);

        // Ensure every cell has the same number of cellsets
        int cSets = _cells.front()->cellsets().size();
        for ( std::vector<Cell *>::iterator it = _cells.begin(); it < _cells.end(); it++ ) {
            int tCt = (*it)->cellsets().size();
            if ( tCt != cSets ) throw exception::InvalidLayout("Cellset count mismatch");
        }

        if ( _puzzlePlugin.exists() )
            _puzzlePlugin->addExtraSets(this);
    }

    Puzzle::Puzzle(Ref<Puzzle> other ) : _size(other->_size), _cellPlugin(other->_cellPlugin), _squarePlugin(other->_squarePlugin), _puzzlePlugin(other->_puzzlePlugin), _ready(false) {
        CloneHelper ch(this);
        _cellsets = ch.cloneCellSets(other->_cellsets);
        _cells = ch.cloneCells(other->_cells);
        _ready = other->_ready;
    }

    Puzzle::~Puzzle() {
        for ( std::vector<Cell *>::iterator it = _cells.begin(); it < _cells.end(); it++ )
            delete *it;
        for ( std::vector<CellSet *>::iterator it = _cellsets.begin(); it < _cellsets.end(); it++ )
            delete *it;
    }

    void Puzzle::resetPencil() {
        std::vector<Cell *>::iterator it;
        for ( it = _cells.begin(); it < _cells.end(); it++ )
            (*it)->resetPencil();
    }

    void Puzzle::disqualifyPencil() {
        std::vector<CellSet *>::iterator it;
        for ( it = _cellsets.begin(); it < _cellsets.end(); it++ )
            (*it)->disqualifyPencil();
    }

    bool Puzzle::solved() {
        unsigned int ct = 0;
        std::vector<Cell *>::iterator it;
        for ( it = _cells.begin(); it < _cells.end(); it++ )
            if ( (*it)->value() != 0 ) ct++;
        return ct == _cells.size();
    }

    bool Puzzle::solvable() {
        unsigned int ct = 0;
        std::vector<Cell *>::iterator it;
        for ( it = _cells.begin(); it < _cells.end(); it++ )
            if ( (*it)->solvable() ) ct++;
        return ct == _cells.size();
    }
};