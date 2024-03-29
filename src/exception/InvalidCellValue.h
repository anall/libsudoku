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

#ifndef __SUDOKU__EXCEPTION__INVALIDCELLVALUE_H__
#define __SUDOKU__EXCEPTION__INVALIDCELLVALUE_H__
#include <string>
#include <sudoku/exception/Exception.h>
#include <sudoku/Position.h>

namespace sudoku {
    namespace exception {
        class InvalidCellValue : public Exception {
        private:
            std::string _what;
            sudoku::Position _pos;
            int _value;
        public:
            InvalidCellValue(const char *what, sudoku::Position &pos, int value) throw();
            virtual ~InvalidCellValue() throw() {}

            virtual const char* what() const throw() { return _what.c_str(); }
            virtual const sudoku::Position& pos() const throw() { return _pos; }
            virtual const int value() const throw() { return _value; }
        };
    }
}

#endif