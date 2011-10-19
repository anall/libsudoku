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

#include <sudoku/CloneHelper.h>

namespace sudoku {
    CloneHelper::CloneHelper(Puzzle *puz) : _puz(puz) {
    }

    std::vector<CellSet *> CloneHelper::cloneCellSets(const std::vector<CellSet *> &cs) {
        std::vector<CellSet *>::const_iterator it;
        std::vector<CellSet *> out;
        for ( it = cs.begin(); it < cs.end(); it++ ) {
            CellSet *old = *it;
            CellSet *clone = old->clone(this);

            _cellsets[old] = clone;
            out.push_back(clone);
        }
        return out;
    }

    std::vector<Cell *> CloneHelper::cloneCells(const std::vector<Cell *> &cs) {
        std::vector<Cell *>::const_iterator it;
        std::vector<Cell *> out;
        for ( it = cs.begin(); it < cs.end(); it++ ) {
            Cell *old = *it;
            Cell *clone = old->clone(this);

            out.push_back(clone);
        }
        return out;
    }

    std::vector<CellSet *> CloneHelper::remapCellSets(const std::vector<CellSet *> &cs) {
        std::vector<CellSet *>::const_iterator it;
        std::vector<CellSet *> out;
        for ( it = cs.begin(); it < cs.end(); it++ ) {
            CellSet *old = *it;
            CellSet *rmp = _cellsets[old];
            out.push_back(rmp);
        }
        return out;
    }
}
