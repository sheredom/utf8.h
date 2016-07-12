# utf8.h #

[![Build status](https://ci.appveyor.com/api/projects/status/phfjjahhs9j4gxvs?svg=true)](https://ci.appveyor.com/project/sheredom/utf8-h)

[![Build status](https://api.travis-ci.org/repositories/sheredom/utf8.h.svg)](https://travis-ci.org/sheredom/utf8.h)

A simple one header solution to supporting utf8 strings in C and C++.

Functions provided from the C header string.h but with a utf8* prefix instead of the str* prefix:

string.h | utf8.h | complete
---------|--------|---------
strcat | utf8cat | &#10004;
strchr | utf8chr | &#10004;
strcmp | utf8cmp | &#10004;
strcoll | utf8coll |
strcpy | utf8cpy | &#10004;
strcspn | utf8cspn | &#10004;
strdup | utf8dup | &#10004;
strfry | utf8fry |
strlen | utf8len | &#10004;
strncat | utf8ncat | &#10004;
strncmp | utf8ncmp | &#10004;
strncpy | utf8ncpy | &#10004;
strpbrk | utf8pbrk | &#10004;
strrchr | utf8rchr | &#10004;
strsep | utf8sep |
strspn | utf8spn | &#10004;
strstr | utf8str | &#10004;
strtok | utf8tok |
strxfrm | utf8xfrm |

Functions provided from the C header strings.h but with a utf8* prefix instead of the str* prefix:

strings.h | utf8.h | complete
----------|--------|---------
strcasecmp | utf8casecmp | ~~&#10004;~~
strncasecmp | utf8ncasecmp | ~~&#10004;~~
strcasestr | utf8casestr | ~~&#10004;~~

Functions provided that are unique to utf8.h:

utf8.h | complete
-------|---------
utf8codepoint | &#10004;
utf8size | &#10004;
utf8valid | &#10004;

## Usage ##

Just include utf8.h in your code!

The current supported compilers are gcc, clang and msvc.

The current tested compiler versions are gcc 4.8.2, clang 3.5 and MSVC 18.0.21005.1.

## Design ##

The utf8.h API matches the string.h API as much as possible by design. There are a few major differences though.

I use void* instead of char* when passing around utf8 strings. My reasoning is that I really don't want people accidentally thinking they can use integer arthimetic on the pointer and always get a valid character like you would with an ASCII string. Having it as a void* forces a user to explicitly cast the utf8 string to char* such that the onus is on them not to break the code anymore!

Anywhere in the string.h or strings.h documentation where it refers to 'bytes' I have changed that to utf8 codepoints. For instance, utf8len will return the number of utf8 codepoints in a utf8 string - which does not necessarily equate to the number of bytes.

## Todo ##

- Implement utf8coll (akin to strcoll).
- Implement utf8fry (akin to strfry).
- ~~Add NULL pointer support. Should I NULL check the arguments to the API?~~
- Add Doxygen (or similar) to mimic the Unix man pages for string.h.
- Investigate adding dst buffer sizes for utf8cpy and utf8cat to catch overwrites (as suggested by [@FlohOfWoe](https://twitter.com/FlohOfWoe) in https://twitter.com/FlohOfWoe/status/618669237771608064)
- Investigate adding a utf8canon which would turn 'bad' utf8 sequences (like ASCII values encoded in 4-byte utf8 codepoints) into their 'good' equivalents (as suggested by [@KmBenzie](https://twitter.com/KmBenzie))
- Investigate changing to [Creative Commons Zero License](http://creativecommons.org/publicdomain/zero/1.0/legalcode.txt) (as suggested by [@mcclure111](https://twitter.com/mcclure111))
- ~~Add utf8casecmp and utf8ncasecmp to compare two strings case-insensitively (as insensitively suggested by [@daniel_collin](https://twitter.com/daniel_collin))~~
- Extend utf8casecmp range to consume non-ASCII case differences too (I don't even rightly know if there are any!)

## License ##

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
