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

#include <bfaffinity.h>
#include <intrinsics.h>

int main()
{
  // We don't do core synchronization in the hypervisor for modifying EPT
  // which means that its possible (unlikely) for a CPU race to occur. To
  // prevent this, we tell our application to only run on CPU 0. To remove
  // this, EPT would need to be set up on all cores, and modifications to
  // EPT would require core synchronization, while requires IPIs that are
  // trapped by the hypervisor and processed properly. This can be done
  // using the EAPIs (all of the APIs are available), but it would make the
  // example far more complicated.
  //
  set_affinity(0);
  ::intel_x64::vm::call();
  return 0;
}