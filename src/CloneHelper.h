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

#ifndef __SUDOKU__CLONEHELPER_H__
#define __SUDOKU__CLONEHELPER_H__
#include <map>
#include <vector>
#include <sudoku/Puzzle.h>
#include <sudoku/Cell.h>
#include <sudoku/CellSet.h>

namespace sudoku {
    class CloneHelper {
    private:
        Puzzle *_puz;
        std::map<CellSet *, CellSet *> _cellsets;
    public:
        CloneHelper(Puzzle *puz);
        std::vector<CellSet *> cloneCellSets(const std::vector<CellSet *> &cs);
        std::vector<Cell *> cloneCells(const std::vector<Cell *> &cs);

        std::vector<CellSet *> remapCellSets(const std::vector<CellSet *> &cs);

        Puzzle *puzzle() { return _puz; }
    };
}

#endif