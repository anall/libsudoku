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

#ifndef __SUDOKU__POSITION_H__
#define __SUDOKU__POSITION_H__
#include <vector>
#include <climits>
#include <sudoku/exception/OutOfRange.h>

namespace sudoku {
    class Position {
    private:
        unsigned char _r, _c;
    public:
        Position() : _r(0), _c(0) {}
        Position(unsigned char r, unsigned char c) : _r(r), _c(c) {}

        unsigned char r() const { return _r; }
        unsigned char c() const { return _c; }

        int idForSize(int size) const throw(sudoku::exception::Exception);
    };
}

#endif