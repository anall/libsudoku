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

#include <sudoku/exception/OutOfRange.h>
#include <sstream>

#define BUFFER_LENGTH 256

namespace sudoku {namespace exception {
    OutOfRange::OutOfRange(const char *what, int value, int min, int max) throw() : sudoku::exception::Exception(), _value(value), _min(min), _max(max) {
        char tmp[BUFFER_LENGTH];
        if ( value < min )
            snprintf(tmp,BUFFER_LENGTH,"%s: %i < %i (minumum value)",what,value,min);
        else if ( value > max )
            snprintf(tmp,BUFFER_LENGTH,"%s: %i > %i (maximum value)",what,value,max);
        _what = tmp;
    }
}}