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

#ifndef __SUDOKU__EXCEPTION__OUTOFRANGE_H__
#define __SUDOKU__EXCEPTION__OUTOFRANGE_H__
#include <string>
#include <sudoku/exception/Exception.h>

namespace sudoku {
    namespace exception {
        class OutOfRange : public Exception {
        private:
            std::string _what;
            int _value, _min, _max;
        public:
            OutOfRange(const char *what, int value, int min, int max) throw();
            virtual ~OutOfRange() throw() {}

            virtual const char* what() const throw() { return _what.c_str(); }
            virtual const int value() const throw() { return _value; }
            virtual const int min() const throw() { return _min; }
            virtual const int max() const throw() { return _max; }
        };
    }
}

#endif