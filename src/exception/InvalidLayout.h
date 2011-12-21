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

#ifndef __SUDOKU__EXCEPTION__INVALIDLAYOUT_H__
#define __SUDOKU__EXCEPTION__INVALIDLAYOUT_H__
#include <string>
#include <sudoku/exception/Exception.h>

namespace sudoku {
    namespace exception {
        class InvalidLayout : public Exception {
        private:
            std::string _what;
        public:
            InvalidLayout(const char *what) throw();
            virtual ~InvalidLayout() throw() {}
        };
    }
}

#endif