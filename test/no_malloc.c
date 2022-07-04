// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>

// include the unit testing framework
#include "utest.h"

// include the header we are testing
#define UTF8_NO_STD_MALLOC
#include "utf8.h"

UTEST(no_malloc_utf8dup, ascii) {
  void *const dup = utf8dup("1234567890");
  ASSERT_FALSE(dup);
}

UTEST(no_malloc_utf8ndup, ascii) {
  void *const dup = utf8ndup("1234567890", 4);
  ASSERT_FALSE(dup);
}

static utf8_int8_t *allocate_from_buffer(utf8_int8_t *user_data, size_t n) {
  return user_data;
}

UTEST(no_malloc_utf8dup_ex, ascii) {
  char user_data[1024];
  void *const dup = utf8dup_ex("1234567890", allocate_from_buffer, user_data);
  ASSERT_TRUE(dup);
  ASSERT_EQ(dup, user_data);
  ASSERT_EQ(10, utf8len(dup));
}

UTEST(no_malloc_utf8ndup_ex, ascii) {
  char user_data[1024];
  void *const dup =
      utf8ndup_ex("1234567890", 4, allocate_from_buffer, user_data);
  ASSERT_TRUE(dup);
  ASSERT_EQ(dup, user_data);
  ASSERT_EQ(4, utf8len(dup));
}

UTEST_MAIN();
