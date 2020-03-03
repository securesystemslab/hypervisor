#include <stdint.h>

#include <bfdebug.h>

__attribute__((noinline))
void __lt_rando_cookie_check(uintptr_t expected, uintptr_t value) {
  //BFDEBUG("[LT-RANDO] Expected Cookie: %lu, Actual Cookie: %lu\n",
          //expected, value);
  // FIXME: How to stop the entire VMM rather than just print out errors?
  if (expected != value) {
    BFERROR("[LT-RANDO] Cookie Mismatch! Expected: %lu, Actual: %lu\n",
            expected, value);
  }
}
