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

#ifndef __SUDOKU__REF_H__
#define __SUDOKU__REF_H__

namespace sudoku {
    template <class T>
    class Ref {
    private:
        T *_ptr;

        void _update(T *ptr) {
            if ( ptr == _ptr ) return;
            ptr->_retain();
            if ( _ptr ) _ptr->_release();
            _ptr = ptr;
        }
    public:
        Ref(T *ptr = 0) : _ptr(0) {
            _update(ptr);
        }
        Ref (const Ref<T> &other) : _ptr(0) {
            _update(other._ptr);
        }

        T *operator=(T *ptr) {
            _update(ptr);
            return ptr;
        }
        Ref<T> &operator=(const Ref<T> &other) {
            _update(other._ptr);
            return *this;
        }

        ~Ref() {
            if ( _ptr ) _ptr->_release();
        }

        T &operator*() { return &_ptr; }
        T *operator->() { return _ptr; }
        T *get() { return _ptr; }

        operator bool() { return _ptr != 0; }
        bool exists() { return _ptr != 0; }
        bool operator==(T *ptr) { return _ptr == ptr; }
        bool operator!=(T *ptr) { return _ptr != ptr; }
    };

    class Counted {
    private:
        int __refct;
    public:
        Counted() { __refct = 0; }
        virtual ~Counted() {}
    private:
        void _retain() {
            __refct++;
        }
        void _release() {
            __refct--;
            if ( __refct <= 0 ) delete this;
        }

        template <class T>
        friend class Ref;
    };
}

#endif
