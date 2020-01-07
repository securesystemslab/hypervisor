//
// Copyright (C) 2019 Assured Information Security, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <vmm.h>

void
global_init()
{
    // SafeStack static analysis should determine that this needs to be stored on the unsafe
    // stack due to interprocedural flow to bfdebug_nhex. 
    uint64_t unsafe_stack_flag;

    bfdebug_nhex(0, "unsafe_stack_ptr_bottom:", __builtin___get_unsafe_stack_bottom());
    bfdebug_nhex(0, "unsafe_stack_ptr_top:", __builtin___get_unsafe_stack_top());
    bfdebug_nhex(0, "unsafe_stack_ptr:", __builtin___get_unsafe_stack_ptr());
    bfdebug_nhex(0, "flag:", &unsafe_stack_flag);
}
