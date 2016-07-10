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
#include "utf8.h"

const char data[] = {
    '\xce', '\x93', '\xce', '\xb1', '\xce', '\xb6', '\xce', '\xad', '\xce',
    '\xb5', '\xcf', '\x82', '\x20', '\xce', '\xba', '\xce', '\xb1', '\xe1',
    '\xbd', '\xb6', '\x20', '\xce', '\xbc', '\xcf', '\x85', '\xcf', '\x81',
    '\xcf', '\x84', '\xce', '\xb9', '\xe1', '\xbd', '\xb2', '\xcf', '\x82',
    '\x20', '\xce', '\xb4', '\xe1', '\xbd', '\xb2', '\xce', '\xbd', '\x20',
    '\xce', '\xb8', '\xe1', '\xbd', '\xb0', '\x20', '\xce', '\xb2', '\xcf',
    '\x81', '\xe1', '\xbf', '\xb6', '\x20', '\xcf', '\x80', '\xce', '\xb9',
    '\xe1', '\xbd', '\xb0', '\x20', '\xcf', '\x83', '\xcf', '\x84', '\xe1',
    '\xbd', '\xb8', '\x20', '\xcf', '\x87', '\xcf', '\x81', '\xcf', '\x85',
    '\xcf', '\x83', '\xce', '\xb1', '\xcf', '\x86', '\xe1', '\xbd', '\xb6',
    '\x20', '\xce', '\xbe', '\xce', '\xad', '\xcf', '\x86', '\xcf', '\x89',
    '\xcf', '\x84', '\xce', '\xbf', '\x0a', '\0'};

const char cmp[] = {'\xce', '\xbc', '\xcf', '\x85', '\0'};

const char lt[] = {'\xce', '\x93', '\xce', '\xb1', '\xce',
                   '\xb6', '\xce', '\xac', '\0'};

const char gt[] = {'\xce', '\x93', '\xce', '\xb1', '\xce',
                   '\xb6', '\xce', '\xae', '\0'};

const char spn[] = {'\xce', '\x93', '\xce', '\xb1', '\xce', '\xb6',
                    '\xce', '\xad', '\xce', '\xb5', '\xcf', '\x82',
                    '\x20', '\xce', '\xba', '\0'};

const char pbrk[] = {'\xcf', '\x82', '\x20', '\xce', '\xb5', '\0'};

const char ascii1[] = "I lIke GOATS YARHAR.";
const char ascii2[] = "i LIKE goats yarHAR.";
const char allascii1[] = "abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWYZ";
const char allascii2[] = "ABCDEFGHIJKLMNOPQRSTUVWYZabcdefghijklmnopqrstuvwyz";

UTEST(utf8len, data) { ASSERT_EQ(53, utf8len(data)); }

UTEST(utf8cat, empty_cat_data) {
  char cat[512] = {'\0'};

  ASSERT_EQ(0, utf8len(cat));

  ASSERT_EQ(53, utf8len(utf8cat(cat, data)));
}

UTEST(utf8cat, one_byte_cat_data) {
  char cat[512];

  cat[0] = 'a';
  cat[1] = '\0';

  ASSERT_EQ(1, utf8len(cat));

  ASSERT_EQ(54, utf8len(utf8cat(cat, data)));
}

UTEST(utf8cat, two_bytes_cat_data) {
  char cat[512];

  cat[0] = '\xce';
  cat[1] = '\x93';
  cat[2] = '\0';

  ASSERT_EQ(1, utf8len(cat));

  ASSERT_EQ(54, utf8len(utf8cat(cat, data)));
}

UTEST(utf8cat, three_bytes_cat_data) {
  char cat[512];

  cat[0] = '\xe1';
  cat[1] = '\xbd';
  cat[2] = '\xb6';
  cat[3] = '\0';

  ASSERT_EQ(1, utf8len(cat));

  ASSERT_EQ(54, utf8len(utf8cat(cat, data)));
}

UTEST(utf8cat, four_bytes_cat_data) {
  char cat[512];

  cat[0] = '\xf0';
  cat[1] = '\x90';
  cat[2] = '\x8d';
  cat[3] = '\x88';
  cat[4] = '\0';

  ASSERT_EQ(1, utf8len(cat));

  ASSERT_EQ(54, utf8len(utf8cat(cat, data)));
}

UTEST(utf8cat, cat_data_data) {
  char cat[512] = {'\0'};

  ASSERT_EQ(0, utf8len(cat));

  ASSERT_EQ(106, utf8len(utf8cat(utf8cat(cat, data), data)));
}

UTEST(utf8str, cmp) { ASSERT_EQ(data + 21, utf8str(data, cmp)); }

UTEST(utf8str, test) { ASSERT_EQ((void *)0, utf8str(data, "test")); }

UTEST(utf8str, empty) { ASSERT_EQ(data, utf8str(data, "")); }

UTEST(utf8chr, a) { ASSERT_EQ(data + 21, utf8chr(data, 0x3bc)); }

UTEST(utf8chr, b) { ASSERT_EQ(0, utf8chr(data, 0x20ac)); }

UTEST(utf8chr, null_terminator) { ASSERT_EQ(data + 104, utf8chr(data, '\0')); }

UTEST(utf8chr, 0x20) { ASSERT_EQ(data + 12, utf8chr(data, 0x20)); }

UTEST(utf8cmp, lt) { ASSERT_LT(0, utf8cmp(data, lt)); }

UTEST(utf8cmp, eq) { ASSERT_EQ(0, utf8cmp(data, data)); }

UTEST(utf8cmp, gt) { ASSERT_GT(0, utf8cmp(data, gt)); }

UTEST(utf8cpy, data) {
  char cpy[512] = {'\0'};

  ASSERT_EQ(53, utf8len(utf8cpy(cpy, data)));
}

UTEST(utf8spn, spn) { ASSERT_EQ(7, utf8spn(data, spn)); }

UTEST(utf8spn, data) { ASSERT_EQ(52, utf8spn(data, data)); }

UTEST(utf8spn, ascii) { ASSERT_EQ(0, utf8spn(data, "ab")); }

UTEST(utf8cspn, spn) { ASSERT_EQ(0, utf8cspn(data, spn)); }

UTEST(utf8cspn, data) { ASSERT_EQ(0, utf8cspn(data, data)); }

UTEST(utf8cspn, ascii) { ASSERT_EQ(53, utf8cspn(data, "ab")); }

UTEST(utf8rchr, a) { ASSERT_EQ(data + 21, utf8rchr(data, 0x3bc)); }

UTEST(utf8rchr, b) { ASSERT_EQ(0, utf8rchr(data, 0x20ac)); }

UTEST(utf8rchr, null_terminator) {
  ASSERT_EQ(data + 104, utf8rchr(data, '\0'));
}

UTEST(utf8rchr, 0x20) { ASSERT_EQ(data + 90, utf8rchr(data, 0x20)); }

UTEST(utf8dup, data) {
  void *const dup = utf8dup(data);
  ASSERT_TRUE(dup);
  ASSERT_EQ(53, utf8len(dup));
  free(dup);
}

UTEST(utf8dup, ascii) {
  void *const dup = utf8dup("ab");
  ASSERT_TRUE(dup);
  ASSERT_EQ(2, utf8len(dup));
  free(dup);
}

UTEST(utf8dup, empty) {
  void *const dup = utf8dup("");
  ASSERT_TRUE(dup);
  ASSERT_EQ(0, utf8len(dup));
  free(dup);
}

UTEST(utf8size, data) { ASSERT_EQ(105, utf8size(data)); }

UTEST(utf8size, ascii) { ASSERT_EQ(3, utf8size("ab")); }

UTEST(utf8size, empty) { ASSERT_EQ(1, utf8size("")); }

UTEST(utf8valid, a) {
  char invalid[6];

  invalid[0] = '\xf0';
  invalid[1] = '\x8f';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';
  invalid[4] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, b) {
  char invalid[6];

  invalid[0] = '\xf1';
  invalid[1] = '\x3f';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';
  invalid[4] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, c) {
  char invalid[6];

  invalid[0] = '\xf1';
  invalid[1] = '\xbf';
  invalid[2] = '\x3f';
  invalid[3] = '\xbf';
  invalid[4] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, d) {
  char invalid[6];

  invalid[0] = '\xf1';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';
  invalid[3] = '\x3f';
  invalid[4] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, e) {
  char invalid[6];

  invalid[0] = '\xe0';
  invalid[1] = '\x9f';
  invalid[2] = '\xbf';
  invalid[3] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, f) {
  char invalid[6];

  invalid[0] = '\xef';
  invalid[1] = '\x3f';
  invalid[2] = '\xbf';
  invalid[3] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, g) {
  char invalid[6];

  invalid[0] = '\xef';
  invalid[1] = '\xbf';
  invalid[2] = '\x3f';
  invalid[3] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, h) {
  char invalid[6];

  invalid[0] = '\xc1';
  invalid[1] = '\xbf';
  invalid[2] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, i) {
  char invalid[6];

  invalid[0] = '\xdf';
  invalid[1] = '\x3f';
  invalid[2] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, j) {
  char invalid[6];

  invalid[0] = '\x80';
  invalid[1] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, k) {
  char invalid[6];

  invalid[0] = '\xf8';
  invalid[1] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, l) {
  char invalid[6];

  invalid[0] = '\xf1';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';
  invalid[4] = '\xbf';
  invalid[5] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, m) {
  char invalid[6];

  invalid[0] = '\xef';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';
  invalid[4] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, n) {
  char invalid[6];

  invalid[0] = '\xdf';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';
  invalid[3] = '\0';

  ASSERT_EQ(invalid, utf8valid(invalid));
}

UTEST(utf8valid, data) { ASSERT_EQ(0, utf8valid(data)); }

UTEST(utf8valid, ascii) { ASSERT_EQ(0, utf8valid("ab")); }

UTEST(utf8valid, empty) { ASSERT_EQ(0, utf8valid("")); }

UTEST(utf8ncat, ascii_cat_data) {
  char cat[512] = {'\0'};
  cat[0] = 'a';
  cat[1] = '\0';
  ASSERT_EQ(2, utf8len(utf8ncat(cat, data, 2)));
}

UTEST(utf8ncat, cat_data) {
  char cat[512] = {'\0'};
  ASSERT_EQ(53, utf8len(utf8ncat(cat, data, 40000)));
}

UTEST(utf8ncat, bad_cat) {
  char cat[512] = {'\0'};
  ASSERT_EQ(cat, utf8valid(utf8ncat(cat, data, 1)));
}

UTEST(utf8ncmp, lt_large) { ASSERT_LT(0, utf8ncmp(data, lt, 4000)); }

UTEST(utf8ncmp, lt_small) { ASSERT_EQ(0, utf8ncmp(data, lt, 7)); }

UTEST(utf8ncmp, eq_large) { ASSERT_EQ(0, utf8ncmp(data, data, 4000)); }

UTEST(utf8ncmp, eq_small) { ASSERT_EQ(0, utf8ncmp(data, data, 7)); }

UTEST(utf8ncmp, gt_large) { ASSERT_GT(0, utf8ncmp(data, gt, 4000)); }

UTEST(utf8ncmp, gt_small) { ASSERT_EQ(0, utf8ncmp(data, gt, 7)); }

UTEST(utf8ncpy, data_null_terminated) {
  char cpy[512] = {'\0'};
  ASSERT_EQ('\0', *((char *)utf8ncpy(cpy, data, 106) + 105));
}

UTEST(utf8ncpy, data) {
  char cpy[512] = {'\0'};
  ASSERT_EQ(53, utf8len(utf8ncpy(cpy, data, 105)));
}

UTEST(utf8pbrk, pbrk) { ASSERT_EQ(data + 8, utf8pbrk(data, pbrk)); }

UTEST(utf8pbrk, data) { ASSERT_EQ(data, utf8pbrk(data, data)); }

UTEST(utf8casecmp, ascii) { ASSERT_EQ(0, utf8casecmp(ascii1, ascii2)); }

UTEST(utf8casecmp, allascii) {
  ASSERT_EQ(0, utf8casecmp(allascii1, allascii2));
}

UTEST(utf8casecmp, data_lt) { ASSERT_LT(0, utf8casecmp(data, lt)); }

UTEST(utf8casecmp, data_eq) { ASSERT_EQ(0, utf8casecmp(data, data)); }

UTEST(utf8casecmp, data_gt) { ASSERT_GT(0, utf8casecmp(data, gt)); }

UTEST(utf8ncasecmp, lt_large) { ASSERT_LT(0, utf8ncasecmp(data, lt, 4000)); }

UTEST(utf8ncasecmp, lt_small) { ASSERT_EQ(0, utf8ncasecmp(data, lt, 7)); }

UTEST(utf8ncasecmp, eq_large) { ASSERT_EQ(0, utf8ncasecmp(data, data, 4000)); }

UTEST(utf8ncasecmp, eq_small) { ASSERT_EQ(0, utf8ncasecmp(data, data, 7)); }

UTEST(utf8ncasecmp, gt_large) { ASSERT_GT(0, utf8ncasecmp(data, gt, 4000)); }

UTEST(utf8ncasecmp, gt_small) { ASSERT_EQ(0, utf8ncasecmp(data, gt, 7)); }

UTEST(utf8codepoint, data) {
  long codepoint;
  void *v;
  unsigned expected_length = utf8len(data) - 1;
  for (v = utf8codepoint(data, &codepoint); '\0' != codepoint;
       v = utf8codepoint(v, &codepoint)) {
    ASSERT_EQ(expected_length, utf8len(v));
    expected_length -= 1;
  }
}

UTEST_MAIN();
