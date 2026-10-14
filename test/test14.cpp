#include "utest.h"
#include "utf8.h"

namespace {
constexpr utf8_int8_t bounded_haystack[] = {'A', 'b', 'C'};
constexpr utf8_int8_t bounded_needle[] = {'B', 'c'};
static_assert(utf8ncasestr(bounded_haystack, sizeof(bounded_haystack),
                         bounded_needle, sizeof(bounded_needle)) ==
                  bounded_haystack + 1,
              "bounded case search must work in constant expressions");
}

#define UTF8_SUITE cpp14
#include "test_shared.h"
