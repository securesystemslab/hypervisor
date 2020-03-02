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

// Start of .text
extern char __executable_start;

// End of .text
extern char __etext;

using namespace bfvmm::intel_x64;
extern void code_layout_rando_randomize();

void
global_init()
{
  bfdebug_info(0, "Running Code Layout Randomization Proof of Concept");
  bfdebug_lnbr(0);
}

bool
randomize_vmcall_handler(vcpu_t *vcpu)
{
  guard_exceptions([&] {
    code_layout_rando_randomize();
  });
  return vcpu->advance();
}

void
vcpu_init_nonroot(vcpu_t *vcpu)
{
  using namespace vmcs_n;

  // Add a VMCall handler. This will catch the VMCalls made by the
  // userspace application and call the vmcall_handler() function.
  //
  vcpu->add_exit_handler_for_reason(
      exit_reason::basic_exit_reason::vmcall, randomize_vmcall_handler);
}