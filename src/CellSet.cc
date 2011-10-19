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

#include <sudoku/CellSet.h>
#include <sudoku/Puzzle.h>
#include <sudoku/Cell.h>
#include <sudoku/CloneHelper.h>

namespace sudoku {
    CellSet::CellSet(Puzzle *puz) : std::vector<Position>(), _puz(puz) {
    }

    void CellSet::unpencil(int v) {
        std::vector<Position>::iterator it;
        for ( it = begin(); it < end(); it++ )
            _puz->cell(*it)->unpencil(v);
    }

    void CellSet::disqualifyPencil() {
        std::vector<Position>::iterator it;
        for ( it = begin(); it < end(); it++ ) {
            int v = _puz->cell(*it)->value();
            if ( v ) unpencil(v);
        }
    }

    CellSet *CellSet::clone(CloneHelper *ch) {
        CellSet *cs = new CellSet(*this);
        cs->_puz = ch->puzzle();
        return cs;
    }
}
