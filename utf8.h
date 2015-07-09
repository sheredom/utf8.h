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

#ifndef __UTF8_H__
#define __UTF8_H__

#include <stddef.h>

#if defined(__cplusplus) && defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__clang__) || defined(__gcc__)
#define utf8_pure __attribute__((pure))
#define utf8_weak __attribute__((weak))
#else
#error Non clang, non gcc compiler found!
#endif

utf8_pure utf8_weak void* utf8cat(void* dst, const void* src);
utf8_pure utf8_weak void* utf8chr(const void* src, int chr);
utf8_pure utf8_weak int utf8cmp(const void* src1, const void* src2);
utf8_pure utf8_weak void* utf8cpy(void* dst, const void* src);
utf8_pure utf8_weak size_t utf8cspn(const void* src, const void* reject);
utf8_pure utf8_weak size_t utf8len(const void* str);
utf8_pure utf8_weak void* utf8rchr(const void* src, int chr);
utf8_pure utf8_weak size_t utf8spn(const void* src, const void* accept);
utf8_pure utf8_weak void* utf8str(const void*, const void*);

#undef utf8_weak
#undef utf8_pure

void* utf8cat(void* dst, const void* src) {
  char* d = (char* )dst;
  const char* s = (const char* )src;

  while ('\0' != *d) {
    d++;
  }

  do {
    *d++ = *s++;
  } while ('\0' != *s);

  *d = '\0';

  return dst;
}

void* utf8chr(const void* src, int chr) {
  char c[5] = {'\0', '\0', '\0', '\0', '\0'};

  if (0 == chr) {
    const char* s = (const char* )src;
    while ('\0' != *s) {
      s++;
    }
    return (void * )s;
  } else if (0 == ((int)0xffffff80 & chr)) {
    // ascii
    c[0] = (char)chr;
  } else if (0 == ((int)0xfffff800 & chr)) {
    c[0] = 0xc0 | (char)(chr >> 6);
    c[1] = 0x80 | (char)(chr & 0x3f);
  } else if (0 == ((int)0xffff0000 & chr)) {
    c[0] = 0xe0 | (char)(chr >> 12);
    c[1] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[2] = 0x80 | (char)(chr & 0x3f);
  } else { // if (0 == ((int)0xffe00000 & chr)) {
    c[0] = 0xf0 | (char)(chr >> 18);
    c[1] = 0x80 | (char)((chr >> 12) & 0x3f);
    c[2] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[3] = 0x80 | (char)(chr & 0x3f);
  }

  return utf8str(src, c);
}

int utf8cmp(const void* src1, const void* src2) {
  const unsigned char* s1 = (const unsigned char* )src1;
  const unsigned char* s2 = (const unsigned char* )src2;

  while (('\0' != *s1) && ('\0' != *s2)) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }

    s1++;
    s2++;
  }

  return 0;
}

int utf8coll(const void* src1, const void* src2);

void* utf8cpy(void* dst, const void* src) {
  char* d = (char* )dst;
  const char* s = (const char* )src;

  do {
    *d++ = *s++;
  } while ('\0' != *s);

  *d = '\0';

  return dst;
}

size_t utf8cspn(const void* src, const void* reject) {
  const char* s = (const char* )src;
  size_t chars = 0;

  while('\0' != *s) {
    const char* r = (const char* )reject;
    size_t offset = 0;

    while ('\0' != *r) {
      if ((0x80 != (0xc0 & *r)) && (0 < offset)) {
        // found a match
        return chars;
      } else {
        if (*r == s[offset]) {
          offset++;
          r++;
        } else {
          // need to march a onwards and reset
          offset = 0;
          do {
            r++;
          } while (0x80 == (0xc0 & *r));
        }
      }
    }

    do {
      s++;
    } while ((0x80 == (0xc0 & *s)));
    chars++;
  }

  return chars;
}

void* utf8dup(const void* src);

void* utf8fry(const void* str);

size_t utf8len(const void* str) {
  const unsigned char* s = (const unsigned char* )str;
  size_t length = 0;

  while ('\0' != *s) {
    if (0xf0 == (0xf8 & *s)) {
      s += 4;
    } else if (0xe0 == (0xf0 & *s)) {
      s += 3;
    } else if (0xc0 == (0xe0 & *s)) {
      s += 2;
    } else { // if (0x00 == (0x80 & *s)) {
      s += 1;
    }

    length += 1;
  }

  return length;
}

void* utf8rchr(const void* src, int chr) {
  const char* s = (const char* )src;
  const char* match = 0;
  char c[5] = {'\0', '\0', '\0', '\0', '\0'};

  if (0 == chr) {
    while ('\0' != *s) {
      s++;
    }
    return (void * )s;
  } else if (0 == ((int)0xffffff80 & chr)) {
    // ascii
    c[0] = (char)chr;
  } else if (0 == ((int)0xfffff800 & chr)) {
    c[0] = 0xc0 | (char)(chr >> 6);
    c[1] = 0x80 | (char)(chr & 0x3f);
  } else if (0 == ((int)0xffff0000 & chr)) {
    c[0] = 0xe0 | (char)(chr >> 12);
    c[1] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[2] = 0x80 | (char)(chr & 0x3f);
  } else { // if (0 == ((int)0xffe00000 & chr)) {
    c[0] = 0xf0 | (char)(chr >> 18);
    c[1] = 0x80 | (char)((chr >> 12) & 0x3f);
    c[2] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[3] = 0x80 | (char)(chr & 0x3f);
  }

  while ('\0' != *s) {
    size_t offset = 0;

    while (s[offset] == c[offset]) {
      offset++;
    }

    if ('\0' == c[offset]) {
      match = s;
      s += offset;
    } else {
      // need to march s along to next utf8 char start
      s += offset;
      if ('\0' != *s) {
        do {
          s++;
        } while (0x80 == (0xc0 & *s));
      }
    }
  }

  return (void* )match;
}

size_t utf8spn(const void* src, const void* accept) {
  const char* s = (const char* )src;
  size_t chars = 0;

  while('\0' != *s) {
    const char* a = (const char* )accept;
    size_t offset = 0;

    while ('\0' != *a) {
      if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
        // found a match
        chars++;
        s += offset;
        break;
      } else {
        if (*a == s[offset]) {
          offset++;
          a++;
        } else {
          // need to march a onwards and reset
          offset = 0;
          do {
            a++;
          } while (0x80 == (0xc0 & *a));
        }
      }
    }

    if ('\0' == *a) {
      return chars;
    }
  }

  return chars;
}

void* utf8str(const void* haystack, const void* needle) {
  const char* h = (const char* )haystack;

  if ('\0' == (const char* )needle) {
    return (void* )haystack;
  }

  while ('\0' != *h) {
    const char* hMaybeMatch = h;
    const char* n = (const char* )needle;

    while (*h == *n) {
      n++;
      h++;
    }

    if ('\0' == *n) {
      return (void* )hMaybeMatch;
    } else {
      // need to march h along to next utf8 char start
      if ('\0' != *h) {
        do {
          h++;
        } while (0x80 == (0xc0 & *h));
      }
    }
  }

  return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif

#if defined(__cplusplus) && defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif//__UTF8_H__
