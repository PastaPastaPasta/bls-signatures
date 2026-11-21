// Copyright (c) 2020 The Dash Core developers

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ERROR_H_
#define ERROR_H_
#include <cstring>
#include <type_traits>

// Trivially destructible so that no thread-exit destructor can run before a
// later failure on the same thread writes to it.
struct ErrorMessage {
    char buf[512];

    ErrorMessage& operator=(const char* msg) {
        std::strncpy(buf, msg, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = '\0';
        return *this;
    }

    const char* c_str() const { return buf; }
};
static_assert(std::is_trivially_destructible<ErrorMessage>::value, "");

extern thread_local ErrorMessage gErrMsg;

#endif  // ERROR_H_
