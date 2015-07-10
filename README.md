# utf8.h #

A simple one header solution to supporting utf8 strings in C and C++.

Functions are provided to match the string.h header but with a utf8* prefix instead of the str* prefix from string.h.

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
strrchr | utf8rchr | &#10004;
strspn | utf8spn | &#10004;
strstr | utf8str |  &#10004;

## Usage ##

Just include utf8.h in your code!

The current supported compilers are gcc and clang - with MSVC support coming soon (I simply haven't had time to test and port to windows yet to be sure).

## Design ##

The utf8.h API matches the string.h API as much as possible by design. There are a few major differences though.

I use void* instead of char* when passing around utf8 strings. My reasoning is that I really don't want people accidentally thinking they can use integer arthimetic on the pointer and always get a valid character like you would with an ASCII string. Having it as a void* forces a user to explicitly cast the utf8 string to char* such that the onus is on them not to break the code anymore!

Anywhere in the string.h documentation where it refers to 'bytes' I have changed that to utf8 codepoints. For instance, utf8len will return the number of utf8 codepoints in a utf8 string - which does not necessarily equate to the number of bytes.

## Todo ##

The current feature list is;

- Implement utf8coll (akin to strcoll).
- ~~Implement utf8cspn (akin to strcspn).~~
- ~~Implement utf8dup (akin to strdup).~~
- Implement utf8fry (akin to strfry).
- ~~Implement utf8rchr (akin to strrchr).~~
- ~~Add utf8size to allow users to get the size in bytes of a utf8 string.~~
- ~~Add utf8valid to check that a given utf8 string is actually a valid utf8 string.~~
- Add NULL pointer support. Should I NULL check the arguments to the API?
- Add Doxygen (or similar) to mimic the Unix man pages for string.h.
- Investigate adding dst buffer sizes for utf8cpy and utf8cat to catch overwrites (as suggested by [@FlohOfWoe](https://twitter.com/FlohOfWoe) in https://twitter.com/FlohOfWoe/status/618669237771608064)
- Investigate adding a utf8canon which would turn 'bad' utf8 sequences (like ASCII values encoded in 4-byte utf8 codepoints) into their 'good' equivalents (as suggested by [@KmBenzie](https://twitter.com/KmBenzie))
- Investigate changing to [Creative Commons Zero License](http://creativecommons.org/publicdomain/zero/1.0/legalcode.txt) (as suggested by [@mcclure111](https://twitter.com/mcclure111))
- ~~Document the code to make it more understandable (as suggested by [@mcclure111](https://twitter.com/mcclure111))~~
- Add strn* variants (should n be by bytes or utf8 codepoints though?)

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
