// Copyright (c) 2019, Tom Westerhout
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "/test/dual-annealing/include/assert.hpp"

#include <cstdio>  // std::fprintf
#include <cstdlib> // std::abort
#if defined(__linux__)
#    include <unistd.h> // isatty
#endif

TCM_ASSERT_NAMESPACE_BEGIN

auto assert_fail(char const* file, unsigned line, char const* function,
                 char const* expression, char const* message) noexcept -> void
{
    static auto const writing_to_terminal = []() {
#if defined(__linux__)
        return static_cast<bool>(::isatty(STDERR_FILENO));
#else
        return false;
#endif
    }();
    if (writing_to_terminal) {
        // NOLINTNEXTLINE
        std::fprintf(stderr,
                     TCM_ASSERT_MESSAGE_HEADER
                     "\x1b[1m\x1b[91mAssertion failed\x1b[0m at %s:%u: %s: "
                     "\"\x1b[1m\x1b[97m%s\x1b[0m\" evaluated to false: "
                     "\x1b[1m\x1b[97m%s\x1b[0m\n",
                     file, line, function, expression, message);
    }
    else {
        // NOLINTNEXTLINE
        std::fprintf(
            stderr,
            TCM_ASSERT_MESSAGE_HEADER
            "Assertion failed at %s:%u: %s: \"%s\" evaluated to false: %s\n",
            file, line, function, expression, message);
    }
    std::abort();
}

TCM_ASSERT_NAMESPACE_END
