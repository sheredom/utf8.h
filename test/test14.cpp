#include "utest.h"
#include "utf8.h"

namespace {
constexpr utf8_int8_t bounded_haystack[] = {'A', 'b', 'C'};
constexpr utf8_int8_t bounded_needle[] = {'B', 'c'};
constexpr utf8_int8_t bounded_codepoint[] = {
    '\xe2', '\x82', '\xac', 'x'};
static_assert(utf8ncasestr(bounded_haystack, sizeof(bounded_haystack),
                         bounded_needle, sizeof(bounded_needle)) ==
                  bounded_haystack + 1,
              "bounded case search must work in constant expressions");
constexpr bool bounded_codepoint_is_constexpr() {
  utf8_int32_t codepoint = 0;
  return utf8ncodepoint(bounded_codepoint, &codepoint, 3) ==
             bounded_codepoint + 3 &&
         codepoint == 0x20ac;
}
static_assert(bounded_codepoint_is_constexpr(),
              "bounded codepoint decoding must work in constant expressions");
}

#define UTF8_SUITE cpp14
#include "test_shared.h"
