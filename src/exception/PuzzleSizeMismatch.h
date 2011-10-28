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

#ifndef __SUDOKU__EXCEPTION__PUZZLESIZEMISMATCH_H__
#define __SUDOKU__EXCEPTION__PUZZLESIZEMISMATCH_H__
#include <string>
#include <sudoku/exception/Exception.h>
#include <malloc.h>

namespace sudoku {
    namespace exception {
        class PuzzleSizeMismatch : public Exception {
        private:
            char *_what;
            int _pz, _ot;
        public:
            PuzzleSizeMismatch(const char *what, int pz, int ot) throw();
            virtual ~PuzzleSizeMismatch() throw() { delete[] _what; }

            virtual const char* what() const throw() { return _what; }
            virtual const int pz() const throw() { return _pz; }
            virtual const int ot() const throw() { return _ot; }
        };
    }
}

#endif