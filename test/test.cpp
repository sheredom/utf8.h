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

#include "utf8.h"

// We don't care about the results. We only want to check compilation

#if defined(__clang__)
#pragma clang diagnostic push

#if __has_warning("-Wunsafe-buffer-usage")
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#endif

#if defined(__cplusplus) && __cplusplus >= 201402L
constexpr void test() {
  constexpr utf8_int8_t in_str[20]{};
  constexpr utf8_int32_t in_chr{};
  utf8_int32_t out_chr{};

  utf8codepoint(in_str, &out_chr);
  utf8rcodepoint(in_str + 1, &out_chr);
  static_assert(utf8chr(in_str, utf8_int32_t{}), "utf8 constexpr fail");
  static_assert(utf8cmp(in_str, in_str) == 0, "utf8 constexpr fail");
  static_assert(utf8cspn(in_str, in_str) == 0, "utf8 constexpr fail");
  static_assert(utf8len(in_str) == 0, "utf8 constexpr fail");
  static_assert(utf8nlen(in_str, 1) == 0, "utf8 constexpr fail");
  static_assert(utf8ncmp(in_str, in_str, 1) == 0, "utf8 constexpr fail");
  static_assert(utf8pbrk(in_str, in_str) == nullptr, "utf8 constexpr fail");
  static_assert(utf8rchr(in_str, 1) == nullptr, "utf8 constexpr fail");
  static_assert(utf8spn(in_str, in_str) == 0, "utf8 constexpr fail");
  static_assert(utf8str(in_str, in_str), "utf8 constexpr fail");
  static_assert(utf8casecmp(in_str, in_str) == 0, "utf8 constexpr fail");
  static_assert(utf8ncasecmp(in_str, in_str, 1) == 0, "utf8 constexpr fail");
  static_assert(utf8casestr(in_str, in_str), "utf8 constexpr fail");
  static_assert(utf8size(in_str), "utf8 constexpr fail");
  static_assert(utf8size_lazy(in_str) == 0, "utf8 constexpr faillazy;");
  static_assert(utf8nsize_lazy(in_str, 1) == 0, "utf8 constexpr faillazy;");
  static_assert(utf8valid(in_str) == nullptr, "utf8 constexpr fail");
  static_assert(utf8nvalid(in_str, 1) == nullptr, "utf8 constexpr fail");
  static_assert(utf8codepointsize(in_chr), "utf8 constexpr fail");
  static_assert(utf8isupper(in_chr) == false, "utf8 constexpr fail");
  static_assert(utf8islower(in_chr) == false, "utf8 constexpr fail");
  static_assert(utf8lwrcodepoint(in_chr) == in_chr, "utf8 constexpr fail");
  static_assert(utf8uprcodepoint(in_chr) == in_chr, "utf8 constexpr fail");
}
#else
static void test() {}
#endif

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

int main() { test(); }
