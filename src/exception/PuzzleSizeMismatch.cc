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

#include <sudoku/exception/PuzzleSizeMismatch.h>
#include <sstream>

#define BUFFER_LENGTH 256

namespace sudoku {namespace exception {
    PuzzleSizeMismatch::PuzzleSizeMismatch(const char *what, int pz, int ot) throw() : sudoku::exception::Exception(), _pz(pz), _ot(ot) {
        char tmp[BUFFER_LENGTH];
        snprintf(tmp,BUFFER_LENGTH,"%s: %i (puzzle), %i (other)",what,pz,ot);
        _what = tmp;
    }
}}