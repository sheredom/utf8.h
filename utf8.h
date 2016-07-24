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

#ifndef SHEREDOM_UTF8_H_INCLUDED
#define SHEREDOM_UTF8_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wcast-qual"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__clang__) || defined(__GNUC__)
#define utf8_nonnull __attribute__((nonnull))
#define utf8_pure __attribute__((pure))
#define utf8_restrict __restrict__
#define utf8_weak __attribute__((weak))
#elif defined(_MSC_VER)
#define utf8_nonnull
#define utf8_pure
#define utf8_restrict __restrict
#define utf8_weak __inline
#else
#error Non clang, non gcc, non MSVC compiler found!
#endif

// While ignoring the case of ASCII characters, return less
// than 0, 0, greater than 0 if src1 < src2, src1 == src2,
// src1 > src2 respectively.
utf8_nonnull utf8_pure utf8_weak int utf8casecmp(const void *src1,
                                                 const void *src2);

// Append the utf8 string src onto the utf8 string dst.
utf8_nonnull utf8_weak void *utf8cat(void *utf8_restrict dst,
                                     const void *utf8_restrict src);

// Find the first match of the utf8 codepoint chr in the utf8 string src.
utf8_nonnull utf8_pure utf8_weak void *utf8chr(const void *src, long chr);

// Return less than 0, 0, greater than 0 if src1 < src2,
// src1 == src2, src1 > src2 respectively.
utf8_nonnull utf8_pure utf8_weak int utf8cmp(const void *src1,
                                             const void *src2);

// Copy the utf8 string src onto the memory allocated in dst.
utf8_nonnull utf8_weak void *utf8cpy(void *utf8_restrict dst,
                                     const void *utf8_restrict src);

// Number of utf8 codepoints in the utf8 string src that consists entirely
// of utf8 codepoints not from the utf8 string reject.
utf8_nonnull utf8_pure utf8_weak size_t utf8cspn(const void *src,
                                                 const void *reject);

// Duplicate the utf8 string src by getting its size, malloc'ing a new buffer
// copying over the data, and returning that. Or 0 if malloc failed.
utf8_nonnull utf8_weak void *utf8dup(const void *src);

// Number of utf8 codepoints in the utf8 string str,
// excluding the null terminating byte.
utf8_nonnull utf8_pure utf8_weak size_t utf8len(const void *str);

// While ignoring the case of ASCII characters, return less
// than 0, 0, greater than 0 if src1 < src2, src1 == src2,
// src1 > src2 respectively. Checking at most n
// bytes of each utf8 string.
utf8_nonnull utf8_pure utf8_weak int utf8ncasecmp(const void *src1,
                                                  const void *src2, size_t n);

// Append the utf8 string src onto the utf8 string dst,
// writing at most n+1 bytes. Can produce an invalid utf8
// string if n falls partway through a utf8 codepoint.
utf8_nonnull utf8_weak void *utf8ncat(void *utf8_restrict dst,
                                      const void *utf8_restrict src, size_t n);

// Return less than 0, 0, greater than 0 if src1 < src2,
// src1 == src2, src1 > src2 respectively. Checking at most n
// bytes of each utf8 string.
utf8_nonnull utf8_pure utf8_weak int utf8ncmp(const void *src1,
                                              const void *src2, size_t n);

// Copy the utf8 string src onto the memory allocated in dst.
// Copies at most n bytes. If there is no terminating null byte in
// the first n bytes of src, the string placed into dst will not be
// null-terminated. If the size (in bytes) of src is less than n,
// extra null terminating bytes are appended to dst such that at
// total of n bytes are written. Can produce an invalid utf8
// string if n falls partway through a utf8 codepoint.
utf8_nonnull utf8_weak void *utf8ncpy(void *utf8_restrict dst,
                                      const void *utf8_restrict src, size_t n);

// Locates the first occurence in the utf8 string str of any byte in the
// utf8 string accept, or 0 if no match was found.
utf8_nonnull utf8_pure utf8_weak void *utf8pbrk(const void *str,
                                                const void *accept);

// Find the last match of the utf8 codepoint chr in the utf8 string src.
utf8_nonnull utf8_pure utf8_weak void *utf8rchr(const void *src, int chr);

// Number of bytes in the utf8 string str,
// including the null terminating byte.
utf8_nonnull utf8_pure utf8_weak size_t utf8size(const void *str);

// Number of utf8 codepoints in the utf8 string src that consists entirely
// of utf8 codepoints from the utf8 string accept.
utf8_nonnull utf8_pure utf8_weak size_t utf8spn(const void *src,
                                                const void *accept);

// The position of the utf8 string needle in the utf8 string haystack.
utf8_nonnull utf8_pure utf8_weak void *utf8str(const void *haystack,
                                               const void *needle);

// The position of the utf8 string needle in the utf8 string haystack, case
// instensitive.
utf8_nonnull utf8_pure utf8_weak void *utf8casestr(const void *haystack,
                                                   const void *needle);

// Return 0 on success, or the position of the invalid
// utf8 codepoint on failure.
utf8_nonnull utf8_pure utf8_weak void *utf8valid(const void *str);

// Sets out_codepoint to the next utf8 codepoint in str, and returns the address
// of the utf8 codepoint after the current one in str.
utf8_nonnull utf8_weak void *utf8codepoint(const void *utf8_restrict str,
                                           long *utf8_restrict out_codepoint);

#undef utf8_weak
#undef utf8_pure
#undef utf8_nonnull

int utf8casecmp(const void *src1, const void *src2) {
  const unsigned char *s1 = (const unsigned char *)src1;
  const unsigned char *s2 = (const unsigned char *)src2;

  while (('\0' != *s1) || ('\0' != *s2)) {
    unsigned char a = *s1;
    unsigned char b = *s2;

    if (('A' <= a) && ('Z' >= a)) {
      a |= 0x20; // make a lowercase
    }

    if (('A' <= b) && ('Z' >= b)) {
      b |= 0x20; // make b lowercase
    }

    if (a < b) {
      return -1;
    } else if (a > b) {
      return 1;
    }

    s1++;
    s2++;
  }

  // both utf8 strings matched
  return 0;
}

void *utf8cat(void *utf8_restrict dst, const void *utf8_restrict src) {
  char *d = (char *)dst;
  const char *s = (const char *)src;

  // find the null terminating byte in dst
  while ('\0' != *d) {
    d++;
  }

  // overwriting the null terminating byte in dst, append src byte-by-byte
  while ('\0' != *s) {
    *d++ = *s++;
  }

  // write out a new null terminating byte into dst
  *d = '\0';

  return dst;
}

void *utf8chr(const void *src, long chr) {
  char c[5] = {'\0', '\0', '\0', '\0', '\0'};

  if (0 == chr) {
    // being asked to return position of null terminating byte, so
    // just run s to the end, and return!
    const char *s = (const char *)src;
    while ('\0' != *s) {
      s++;
    }
    return (void *)s;
  } else if (0 == ((long)0xffffff80 & chr)) {
    // 1-byte/7-bit ascii
    // (0b0xxxxxxx)
    c[0] = (char)chr;
  } else if (0 == ((long)0xfffff800 & chr)) {
    // 2-byte/11-bit utf8 code point
    // (0b110xxxxx 0b10xxxxxx)
    c[0] = 0xc0 | (char)(chr >> 6);
    c[1] = 0x80 | (char)(chr & 0x3f);
  } else if (0 == ((long)0xffff0000 & chr)) {
    // 3-byte/16-bit utf8 code point
    // (0b1110xxxx 0b10xxxxxx 0b10xxxxxx)
    c[0] = 0xe0 | (char)(chr >> 12);
    c[1] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[2] = 0x80 | (char)(chr & 0x3f);
  } else { // if (0 == ((int)0xffe00000 & chr)) {
    // 4-byte/21-bit utf8 code point
    // (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx)
    c[0] = 0xf0 | (char)(chr >> 18);
    c[1] = 0x80 | (char)((chr >> 12) & 0x3f);
    c[2] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[3] = 0x80 | (char)(chr & 0x3f);
  }

  // we've made c into a 2 utf8 codepoint string, one for the chr we are
  // seeking, another for the null terminating byte. Now use utf8str to
  // search
  return utf8str(src, c);
}

int utf8cmp(const void *src1, const void *src2) {
  const unsigned char *s1 = (const unsigned char *)src1;
  const unsigned char *s2 = (const unsigned char *)src2;

  while (('\0' != *s1) || ('\0' != *s2)) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }

    s1++;
    s2++;
  }

  // both utf8 strings matched
  return 0;
}

int utf8coll(const void *src1, const void *src2);

void *utf8cpy(void *utf8_restrict dst, const void *utf8_restrict src) {
  char *d = (char *)dst;
  const char *s = (const char *)src;

  // overwriting anything previously in dst, write byte-by-byte
  // from src
  while ('\0' != *s) {
    *d++ = *s++;
  }

  // append null terminating byte
  *d = '\0';

  return dst;
}

size_t utf8cspn(const void *src, const void *reject) {
  const char *s = (const char *)src;
  size_t chars = 0;

  while ('\0' != *s) {
    const char *r = (const char *)reject;
    size_t offset = 0;

    while ('\0' != *r) {
      // checking that if *r is the start of a utf8 codepoint
      // (it is not 0b10xxxxxx) and we have successfully matched
      // a previous character (0 < offset) - we found a match
      if ((0x80 != (0xc0 & *r)) && (0 < offset)) {
        return chars;
      } else {
        if (*r == s[offset]) {
          // part of a utf8 codepoint matched, so move our checking
          // onwards to the next byte
          offset++;
          r++;
        } else {
          // r could be in the middle of an unmatching utf8 code point,
          // so we need to march it on to the next character beginning,

          do {
            r++;
          } while (0x80 == (0xc0 & *r));

          // reset offset too as we found a mismatch
          offset = 0;
        }
      }
    }

    // the current utf8 codepoint in src did not match reject, but src
    // could have been partway through a utf8 codepoint, so we need to
    // march it onto the next utf8 codepoint starting byte
    do {
      s++;
    } while ((0x80 == (0xc0 & *s)));
    chars++;
  }

  return chars;
}

size_t utf8size(const void *str);

void *utf8dup(const void *src) {
  const char *s = (const char *)src;
  char *n = 0;

  // figure out how many bytes (including the terminator) we need to copy first
  size_t bytes = utf8size(src);

  n = (char *)malloc(bytes);

  if (0 == n) {
    // out of memory so we bail
    return 0;
  } else {
    bytes = 0;

    // copy src byte-by-byte into our new utf8 string
    while ('\0' != s[bytes]) {
      n[bytes] = s[bytes];
      bytes++;
    }

    // append null terminating byte
    n[bytes] = '\0';
    return n;
  }
}

void *utf8fry(const void *str);

size_t utf8len(const void *str) {
  const unsigned char *s = (const unsigned char *)str;
  size_t length = 0;

  while ('\0' != *s) {
    if (0xf0 == (0xf8 & *s)) {
      // 4-byte utf8 code point (began with 0b11110xxx)
      s += 4;
    } else if (0xe0 == (0xf0 & *s)) {
      // 3-byte utf8 code point (began with 0b1110xxxx)
      s += 3;
    } else if (0xc0 == (0xe0 & *s)) {
      // 2-byte utf8 code point (began with 0b110xxxxx)
      s += 2;
    } else { // if (0x00 == (0x80 & *s)) {
      // 1-byte ascii (began with 0b0xxxxxxx)
      s += 1;
    }

    // no matter the bytes we marched s forward by, it was
    // only 1 utf8 codepoint
    length++;
  }

  return length;
}

int utf8ncasecmp(const void *src1, const void *src2, size_t n) {
  const unsigned char *s1 = (const unsigned char *)src1;
  const unsigned char *s2 = (const unsigned char *)src2;

  while ((('\0' != *s1) || ('\0' != *s2)) && (0 != n--)) {
    unsigned char a = *s1;
    unsigned char b = *s2;

    if (('A' <= a) && ('Z' >= a)) {
      a |= 0x20; // make a lowercase
    }

    if (('A' <= b) && ('Z' >= b)) {
      b |= 0x20; // make b lowercase
    }

    if (a < b) {
      return -1;
    } else if (a > b) {
      return 1;
    }

    s1++;
    s2++;
  }

  // both utf8 strings matched
  return 0;
}

void *utf8ncat(void *utf8_restrict dst, const void *utf8_restrict src,
               size_t n) {
  char *d = (char *)dst;
  const char *s = (const char *)src;

  // find the null terminating byte in dst
  while ('\0' != *d) {
    d++;
  }

  // overwriting the null terminating byte in dst, append src byte-by-byte
  // stopping if we run out of space
  do {
    *d++ = *s++;
  } while (('\0' != *s) && (0 != --n));

  // write out a new null terminating byte into dst
  *d = '\0';

  return dst;
}

int utf8ncmp(const void *src1, const void *src2, size_t n) {
  const unsigned char *s1 = (const unsigned char *)src1;
  const unsigned char *s2 = (const unsigned char *)src2;

  while ((('\0' != *s1) || ('\0' != *s2)) && (0 != n--)) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }

    s1++;
    s2++;
  }

  // both utf8 strings matched
  return 0;
}

void *utf8ncpy(void *utf8_restrict dst, const void *utf8_restrict src,
               size_t n) {
  char *d = (char *)dst;
  const char *s = (const char *)src;

  // overwriting anything previously in dst, write byte-by-byte
  // from src
  do {
    *d++ = *s++;
  } while (('\0' != *s) && (0 != --n));

  // append null terminating byte
  while (0 != n) {
    *d++ = '\0';
    n--;
  }

  return dst;
}

void *utf8rchr(const void *src, int chr) {
  const char *s = (const char *)src;
  const char *match = 0;
  char c[5] = {'\0', '\0', '\0', '\0', '\0'};

  if (0 == chr) {
    // being asked to return position of null terminating byte, so
    // just run s to the end, and return!
    while ('\0' != *s) {
      s++;
    }
    return (void *)s;
  } else if (0 == ((int)0xffffff80 & chr)) {
    // 1-byte/7-bit ascii
    // (0b0xxxxxxx)
    c[0] = (char)chr;
  } else if (0 == ((int)0xfffff800 & chr)) {
    // 2-byte/11-bit utf8 code point
    // (0b110xxxxx 0b10xxxxxx)
    c[0] = 0xc0 | (char)(chr >> 6);
    c[1] = 0x80 | (char)(chr & 0x3f);
  } else if (0 == ((int)0xffff0000 & chr)) {
    // 3-byte/16-bit utf8 code point
    // (0b1110xxxx 0b10xxxxxx 0b10xxxxxx)
    c[0] = 0xe0 | (char)(chr >> 12);
    c[1] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[2] = 0x80 | (char)(chr & 0x3f);
  } else { // if (0 == ((int)0xffe00000 & chr)) {
    // 4-byte/21-bit utf8 code point
    // (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx)
    c[0] = 0xf0 | (char)(chr >> 18);
    c[1] = 0x80 | (char)((chr >> 12) & 0x3f);
    c[2] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[3] = 0x80 | (char)(chr & 0x3f);
  }

  // we've created a 2 utf8 codepoint string in c that is
  // the utf8 character asked for by chr, and a null
  // terminating byte

  while ('\0' != *s) {
    size_t offset = 0;

    while (s[offset] == c[offset]) {
      offset++;
    }

    if ('\0' == c[offset]) {
      // we found a matching utf8 code point
      match = s;
      s += offset;
    } else {
      s += offset;

      // need to march s along to next utf8 codepoint start
      // (the next byte that doesn't match 0b10xxxxxx)
      if ('\0' != *s) {
        do {
          s++;
        } while (0x80 == (0xc0 & *s));
      }
    }
  }

  // return the last match we found (or 0 if no match was found)
  return (void *)match;
}

void *utf8pbrk(const void *str, const void *accept) {
  const char *s = (const char *)str;

  while ('\0' != *s) {
    const char *a = (const char *)accept;
    size_t offset = 0;

    while ('\0' != *a) {
      // checking that if *a is the start of a utf8 codepoint
      // (it is not 0b10xxxxxx) and we have successfully matched
      // a previous character (0 < offset) - we found a match
      if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
        return (void *)s;
      } else {
        if (*a == s[offset]) {
          // part of a utf8 codepoint matched, so move our checking
          // onwards to the next byte
          offset++;
          a++;
        } else {
          // r could be in the middle of an unmatching utf8 code point,
          // so we need to march it on to the next character beginning,

          do {
            a++;
          } while (0x80 == (0xc0 & *a));

          // reset offset too as we found a mismatch
          offset = 0;
        }
      }
    }

    // we found a match on the last utf8 codepoint
    if (0 < offset) {
      return (void *)s;
    }

    // the current utf8 codepoint in src did not match accept, but src
    // could have been partway through a utf8 codepoint, so we need to
    // march it onto the next utf8 codepoint starting byte
    do {
      s++;
    } while ((0x80 == (0xc0 & *s)));
  }

  return 0;
}

size_t utf8size(const void *str) {
  const char *s = (const char *)str;
  size_t size = 0;
  while ('\0' != s[size]) {
    size++;
  }

  // we are including the null terminating byte in the size calculation
  size++;
  return size;
}

size_t utf8spn(const void *src, const void *accept) {
  const char *s = (const char *)src;
  size_t chars = 0;

  while ('\0' != *s) {
    const char *a = (const char *)accept;
    size_t offset = 0;

    while ('\0' != *a) {
      // checking that if *r is the start of a utf8 codepoint
      // (it is not 0b10xxxxxx) and we have successfully matched
      // a previous character (0 < offset) - we found a match
      if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
        // found a match, so increment the number of utf8 codepoints
        // that have matched and stop checking whether any other utf8
        // codepoints in a match
        chars++;
        s += offset;
        break;
      } else {
        if (*a == s[offset]) {
          offset++;
          a++;
        } else {
          // a could be in the middle of an unmatching utf8 codepoint,
          // so we need to march it on to the next character beginning,
          do {
            a++;
          } while (0x80 == (0xc0 & *a));

          // reset offset too as we found a mismatch
          offset = 0;
        }
      }
    }

    // if a got to its terminating null byte, then we didn't find a match.
    // Return the current number of matched utf8 codepoints
    if ('\0' == *a) {
      return chars;
    }
  }

  return chars;
}

void *utf8str(const void *haystack, const void *needle) {
  const char *h = (const char *)haystack;

  // if needle has no utf8 codepoints before the null terminating
  // byte then return haystack
  if ('\0' == *((const char *)needle)) {
    return (void *)haystack;
  }

  while ('\0' != *h) {
    const char *maybeMatch = h;
    const char *n = (const char *)needle;

    while (*h == *n) {
      n++;
      h++;
    }

    if ('\0' == *n) {
      // we found the whole utf8 string for needle in haystack at
      // maybeMatch, so return it
      return (void *)maybeMatch;
    } else {
      // h could be in the middle of an unmatching utf8 codepoint,
      // so we need to march it on to the next character beginning,
      if ('\0' != *h) {
        do {
          h++;
        } while (0x80 == (0xc0 & *h));
      }
    }
  }

  // no match
  return 0;
}

void *utf8casestr(const void *haystack, const void *needle) {
  const char *h = (const char *)haystack;

  // if needle has no utf8 codepoints before the null terminating
  // byte then return haystack
  if ('\0' == *((const char *)needle)) {
    return (void *)haystack;
  }

  while ('\0' != *h) {
    const char *maybeMatch = h;
    const char *n = (const char *)needle;

    for (;;) {
      char a = *h;
      char b = *n;
      // not entirely correct, but good enough
      if (('A' <= a) && ('Z' >= a)) {
        a |= 0x20; // make a lowercase
      }

      if (('A' <= b) && ('Z' >= b)) {
        b |= 0x20; // make b lowercase
      }

      // if we find a mismatch, bail out!
      if (a != b) {
        break;
      }

      n++;
      h++;
    }

    if ('\0' == *n) {
      // we found the whole utf8 string for needle in haystack at
      // maybeMatch, so return it
      return (void *)maybeMatch;
    } else {
      // h could be in the middle of an unmatching utf8 codepoint,
      // so we need to march it on to the next character beginning,
      if ('\0' != *h) {
        do {
          h++;
        } while (0x80 == (0xc0 & *h));
      }
    }
  }

  // no match
  return 0;
}

void *utf8valid(const void *str) {
  const char *s = (const char *)str;

  while ('\0' != *s) {
    if (0xf0 == (0xf8 & *s)) {
      // ensure each of the 3 following bytes in this 4-byte
      // utf8 codepoint began with 0b10xxxxxx
      if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2])) ||
          (0x80 != (0xc0 & s[3]))) {
        return (void *)s;
      }

      // ensure that our utf8 codepoint ended after 4 bytes
      if (0x80 == (0xc0 & s[4])) {
        return (void *)s;
      }

      // ensure that the top 5 bits of this 4-byte utf8
      // codepoint were not 0, as then we could have used
      // one of the smaller encodings
      if ((0 == (0x07 & s[0])) && (0 == (0x30 & s[1]))) {
        return (void *)s;
      }

      // 4-byte utf8 code point (began with 0b11110xxx)
      s += 4;
    } else if (0xe0 == (0xf0 & *s)) {
      // ensure each of the 2 following bytes in this 3-byte
      // utf8 codepoint began with 0b10xxxxxx
      if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2]))) {
        return (void *)s;
      }

      // ensure that our utf8 codepoint ended after 3 bytes
      if (0x80 == (0xc0 & s[3])) {
        return (void *)s;
      }

      // ensure that the top 5 bits of this 3-byte utf8
      // codepoint were not 0, as then we could have used
      // one of the smaller encodings
      if ((0 == (0x0f & s[0])) && (0 == (0x20 & s[1]))) {
        return (void *)s;
      }

      // 3-byte utf8 code point (began with 0b1110xxxx)
      s += 3;
    } else if (0xc0 == (0xe0 & *s)) {
      // ensure the 1 following byte in this 2-byte
      // utf8 codepoint began with 0b10xxxxxx
      if (0x80 != (0xc0 & s[1])) {
        return (void *)s;
      }

      // ensure that our utf8 codepoint ended after 2 bytes
      if (0x80 == (0xc0 & s[2])) {
        return (void *)s;
      }

      // ensure that the top 4 bits of this 2-byte utf8
      // codepoint were not 0, as then we could have used
      // one of the smaller encodings
      if (0 == (0x1e & s[0])) {
        return (void *)s;
      }

      // 2-byte utf8 code point (began with 0b110xxxxx)
      s += 2;
    } else if (0x00 == (0x80 & *s)) {
      // 1-byte ascii (began with 0b0xxxxxxx)
      s += 1;
    } else {
      // we have an invalid 0b1xxxxxxx utf8 code point entry
      return (void *)s;
    }
  }

  return 0;
}

void *utf8codepoint(const void *utf8_restrict str,
                    long *utf8_restrict out_codepoint) {
  const char *s = (const char *)str;

  if (0xf0 == (0xf8 & s[0])) {
    // 4 byte utf8 codepoint
    *out_codepoint = ((0x07 & s[0]) << 18) | ((0x3f & s[1]) << 12) |
                     ((0x3f & s[2]) << 6) | (0x3f & s[3]);
    s += 4;
  } else if (0xe0 == (0xf0 & s[0])) {
    // 3 byte utf8 codepoint
    *out_codepoint =
        ((0x0f & s[0]) << 12) | ((0x3f & s[1]) << 6) | (0x3f & s[2]);
    s += 3;
  } else if (0xc0 == (0xe0 & s[0])) {
    // 2 byte utf8 codepoint
    *out_codepoint = ((0x1f & s[0]) << 6) | (0x3f & s[1]);
    s += 2;
  } else {
    // 1 byte utf8 codepoint otherwise
    *out_codepoint = s[0];
    s += 1;
  }

  return (void *)s;
}

#undef utf8_restrict

#ifdef __cplusplus
} // extern "C"
#endif

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // SHEREDOM_UTF8_H_INCLUDED
