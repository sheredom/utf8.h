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
const char haystack[] = "foobar";
const char needle[] = "oba";
const char endfailneedle[] = "ra";
const char cspnmultisearch[] = "another test; string|one more";
const char cspnmultidelims[] = "|;";
const char spnasciisearch[] = ",,hello,,world";
const char spnasciidelims[] = ",";

struct LowerUpperPair {
  int lower;
  int upper;
};

const struct LowerUpperPair lowupPairs[] = {
    /* ascii */
    {0x0061, 0x0041},
    {0x0062, 0x0042},
    {0x0063, 0x0043},
    {0x0064, 0x0044},
    {0x0065, 0x0045},
    {0x0066, 0x0046},
    {0x0067, 0x0047},
    {0x0068, 0x0048},
    {0x0069, 0x0049},
    {0x006a, 0x004a},
    {0x006b, 0x004b},
    {0x006c, 0x004c},
    {0x006d, 0x004d},
    {0x006e, 0x004e},
    {0x006f, 0x004f},
    {0x0070, 0x0050},
    {0x0071, 0x0051},
    {0x0072, 0x0052},
    {0x0073, 0x0053},
    {0x0074, 0x0054},
    {0x0075, 0x0055},
    {0x0076, 0x0056},
    {0x0077, 0x0057},
    {0x0078, 0x0058},
    {0x0079, 0x0059},
    {0x007a, 0x005a},

    /* Latin-1 Supplement */
    {0x00e0, 0x00c0},
    {0x00e1, 0x00c1},
    {0x00e2, 0x00c2},
    {0x00e3, 0x00c3},
    {0x00e4, 0x00c4},
    {0x00e5, 0x00c5},
    {0x00e6, 0x00c6},
    {0x00e7, 0x00c7},
    {0x00e8, 0x00c8},
    {0x00e9, 0x00c9},
    {0x00ea, 0x00ca},
    {0x00eb, 0x00cb},
    {0x00ec, 0x00cc},
    {0x00ed, 0x00cd},
    {0x00ee, 0x00ce},
    {0x00ef, 0x00cf},
    {0x00f0, 0x00d0},
    {0x00f1, 0x00d1},
    {0x00f2, 0x00d2},
    {0x00f3, 0x00d3},
    {0x00f4, 0x00d4},
    {0x00f5, 0x00d5},
    {0x00f6, 0x00d6},
    {0x00f8, 0x00d8},
    {0x00f9, 0x00d9},
    {0x00fa, 0x00da},
    {0x00fb, 0x00db},
    {0x00fc, 0x00dc},
    {0x00fd, 0x00dd},
    {0x00fe, 0x00de},
    {0x00ff, 0x0178},

    /* Latin Extended-A */
    {0x0101, 0x0100},
    {0x0103, 0x0102},
    {0x0105, 0x0104},
    {0x0107, 0x0106},
    {0x0109, 0x0108},
    {0x010b, 0x010a},
    {0x010d, 0x010c},
    {0x010f, 0x010e},
    {0x0111, 0x0110},
    {0x0113, 0x0112},
    {0x0115, 0x0114},
    {0x0117, 0x0116},
    {0x0119, 0x0118},
    {0x011b, 0x011a},
    {0x011d, 0x011c},
    {0x011f, 0x011e},
    {0x0121, 0x0120},
    {0x0123, 0x0122},
    {0x0125, 0x0124},
    {0x0127, 0x0126},
    {0x0129, 0x0128},
    {0x012b, 0x012a},
    {0x012d, 0x012c},
    {0x012f, 0x012e},
    {0x0133, 0x0132},
    {0x0135, 0x0134},
    {0x0137, 0x0136},
    {0x013a, 0x0139},
    {0x013c, 0x013b},
    {0x013e, 0x013d},
    {0x0140, 0x013f},
    {0x0142, 0x0141},
    {0x0144, 0x0143},
    {0x0146, 0x0145},
    {0x0148, 0x0147},
    {0x014b, 0x014a},
    {0x014d, 0x014c},
    {0x014f, 0x014e},
    {0x0151, 0x0150},
    {0x0153, 0x0152},
    {0x0155, 0x0154},
    {0x0157, 0x0156},
    {0x0159, 0x0158},
    {0x015b, 0x015a},
    {0x015d, 0x015c},
    {0x015f, 0x015e},
    {0x0161, 0x0160},
    {0x0163, 0x0162},
    {0x0165, 0x0164},
    {0x0167, 0x0166},
    {0x0169, 0x0168},
    {0x016b, 0x016a},
    {0x016d, 0x016c},
    {0x016f, 0x016e},
    {0x0171, 0x0170},
    {0x0173, 0x0172},
    {0x0175, 0x0174},
    {0x0177, 0x0176},
    {0x017a, 0x0179},
    {0x017c, 0x017b},
    {0x017e, 0x017d},

    /* Latin Extended-B */
    {0x0180, 0x0243},
    {0x01dd, 0x018e},
    {0x019a, 0x023d},
    {0x019e, 0x0220},
    {0x0292, 0x01b7},
    {0x01c6, 0x01c4},
    {0x01c9, 0x01c7},
    {0x01cc, 0x01ca},
    {0x01f3, 0x01f1},
    {0x01bf, 0x01f7},
    {0x0183, 0x0182},
    {0x0185, 0x0184},
    {0x0188, 0x0187},
    {0x018c, 0x018b},
    {0x0192, 0x0191},
    {0x0199, 0x0198},
    {0x01a1, 0x01a0},
    {0x01a3, 0x01a2},
    {0x01a5, 0x01a4},
    {0x01a8, 0x01a7},
    {0x01ad, 0x01ac},
    {0x01b0, 0x01af},
    {0x01b4, 0x01b3},
    {0x01b6, 0x01b5},
    {0x01b9, 0x01b8},
    {0x01bd, 0x01bc},
    {0x01ce, 0x01cd},
    {0x01d0, 0x01cf},
    {0x01d2, 0x01d1},
    {0x01d4, 0x01d3},
    {0x01d6, 0x01d5},
    {0x01d8, 0x01d7},
    {0x01da, 0x01d9},
    {0x01dc, 0x01db},
    {0x01df, 0x01de},
    {0x01e1, 0x01e0},
    {0x01e3, 0x01e2},
    {0x01e5, 0x01e4},
    {0x01e7, 0x01e6},
    {0x01e9, 0x01e8},
    {0x01eb, 0x01ea},
    {0x01ed, 0x01ec},
    {0x01ef, 0x01ee},
    {0x01f5, 0x01f4},
    {0x01f9, 0x01f8},
    {0x01fb, 0x01fa},
    {0x01fd, 0x01fc},
    {0x01ff, 0x01fe},
    {0x0201, 0x0200},
    {0x0203, 0x0202},
    {0x0205, 0x0204},
    {0x0207, 0x0206},
    {0x0209, 0x0208},
    {0x020b, 0x020a},
    {0x020d, 0x020c},
    {0x020f, 0x020e},
    {0x0211, 0x0210},
    {0x0213, 0x0212},
    {0x0215, 0x0214},
    {0x0217, 0x0216},
    {0x0219, 0x0218},
    {0x021b, 0x021a},
    {0x021d, 0x021c},
    {0x021f, 0x021e},
    {0x0223, 0x0222},
    {0x0225, 0x0224},
    {0x0227, 0x0226},
    {0x0229, 0x0228},
    {0x022b, 0x022a},
    {0x022d, 0x022c},
    {0x022f, 0x022e},
    {0x0231, 0x0230},
    {0x0233, 0x0232},
    {0x023c, 0x023b},
    {0x0242, 0x0241},
    {0x0247, 0x0246},
    {0x0249, 0x0248},
    {0x024b, 0x024a},
    {0x024d, 0x024c},
    {0x024f, 0x024e},

    /* Greek and Coptic */
    {0x037b, 0x03fd},
    {0x037c, 0x03fe},
    {0x037d, 0x03ff},

    {0x03f3, 0x037f},
    {0x03ac, 0x0386},

    {0x03ad, 0x0388},
    {0x03ae, 0x0389},
    {0x03af, 0x038a},

    {0x03cc, 0x038c},

    {0x03cd, 0x038e},
    {0x03ce, 0x038f},

    {0x0371, 0x0370},
    {0x0373, 0x0372},
    {0x0377, 0x0376},

    {0x03B1, 0x0391},
    {0x03B2, 0x0392},
    {0x03B3, 0x0393},
    {0x03B4, 0x0394},
    {0x03B5, 0x0395},
    {0x03B6, 0x0396},
    {0x03B7, 0x0397},
    {0x03B8, 0x0398},
    {0x03B9, 0x0399},
    {0x03BA, 0x039A},
    {0x03BB, 0x039B},
    {0x03BC, 0x039C},
    {0x03BD, 0x039D},
    {0x03BE, 0x039E},
    {0x03BF, 0x039F},
    {0x03C0, 0x03A0},
    {0x03C1, 0x03A1},

    {0x03C3, 0x03A3},
    {0x03C4, 0x03A4},
    {0x03C5, 0x03A5},
    {0x03C6, 0x03A6},
    {0x03C7, 0x03A7},
    {0x03C8, 0x03A8},
    {0x03C9, 0x03A9},
    {0x03ca, 0x03aa},
    {0x03cb, 0x03ab},

    {0x03d1, 0x03f4},

    {0x03d7, 0x03cf},

    {0x03d9, 0x03d8},
    {0x03db, 0x03da},
    {0x03dd, 0x03dc},
    {0x03df, 0x03de},
    {0x03e1, 0x03e0},
    {0x03e3, 0x03e2},
    {0x03e5, 0x03e4},
    {0x03e7, 0x03e6},
    {0x03e9, 0x03e8},
    {0x03eb, 0x03ea},
    {0x03ed, 0x03ec},
    {0x03ef, 0x03ee},

    {0x03f2, 0x03f9},

    {0x03f8, 0x03f7},

    {0x03fb, 0x03fa},

    /* Cyrillic */
    {0x0450, 0x0400},
    {0x0451, 0x0401},
    {0x0452, 0x0402},
    {0x0453, 0x0403},
    {0x0454, 0x0404},
    {0x0455, 0x0405},
    {0x0456, 0x0406},
    {0x0457, 0x0407},
    {0x0458, 0x0408},
    {0x0459, 0x0409},
    {0x045a, 0x040a},
    {0x045b, 0x040b},
    {0x045c, 0x040c},
    {0x045d, 0x040d},
    {0x045e, 0x040e},
    {0x045f, 0x040f},

    {0x0430, 0x0410},
    {0x0431, 0x0411},
    {0x0432, 0x0412},
    {0x0433, 0x0413},
    {0x0434, 0x0414},
    {0x0435, 0x0415},
    {0x0436, 0x0416},
    {0x0437, 0x0417},
    {0x0438, 0x0418},
    {0x0439, 0x0419},
    {0x043a, 0x041a},
    {0x043b, 0x041b},
    {0x043c, 0x041c},
    {0x043d, 0x041d},
    {0x043e, 0x041e},
    {0x043f, 0x041f},
    {0x0440, 0x0420},
    {0x0441, 0x0421},
    {0x0442, 0x0422},
    {0x0443, 0x0423},
    {0x0444, 0x0424},
    {0x0445, 0x0425},
    {0x0446, 0x0426},
    {0x0447, 0x0427},
    {0x0448, 0x0428},
    {0x0449, 0x0429},
    {0x044a, 0x042a},
    {0x044b, 0x042b},
    {0x044c, 0x042c},
    {0x044d, 0x042d},
    {0x044e, 0x042e},
    {0x044f, 0x042f},

    {0x0461, 0x0460},
    {0x0463, 0x0462},
    {0x0465, 0x0464},
    {0x0467, 0x0466},
    {0x0469, 0x0468},
    {0x046b, 0x046a},
    {0x046d, 0x046c},
    {0x046f, 0x046e},
    {0x0471, 0x0470},
    {0x0473, 0x0472},
    {0x0475, 0x0474},
    {0x0477, 0x0476},
    {0x0479, 0x0478},
    {0x047b, 0x047a},
    {0x047d, 0x047c},
    {0x047f, 0x047e},
    {0x0481, 0x0480},

    {0x048b, 0x048a},
    {0x048d, 0x048c},
    {0x048f, 0x048e},
    {0x0491, 0x0490},
    {0x0493, 0x0492},
    {0x0495, 0x0494},
    {0x0497, 0x0496},
    {0x0499, 0x0498},
    {0x049b, 0x049a},
    {0x049d, 0x049c},
    {0x049f, 0x049e},
    {0x04a1, 0x04a0},
    {0x04a3, 0x04a2},
    {0x04a5, 0x04a4},
    {0x04a7, 0x04a6},
    {0x04a9, 0x04a8},
    {0x04ab, 0x04aa},
    {0x04ad, 0x04ac},
    {0x04af, 0x04ae},
    {0x04b1, 0x04b0},
    {0x04b3, 0x04b2},
    {0x04b5, 0x04b4},
    {0x04b7, 0x04b6},
    {0x04b9, 0x04b8},
    {0x04bb, 0x04ba},
    {0x04bd, 0x04bc},
    {0x04bf, 0x04be},
    {0x04c1, 0x04c0},
    {0x04c3, 0x04c2},
    {0x04c5, 0x04c4},
    {0x04c7, 0x04c6},
    {0x04c9, 0x04c8},
    {0x04cb, 0x04ca},
    {0x04cd, 0x04cc},
    {0x04cf, 0x04ce},
    {0x04d1, 0x04d0},
    {0x04d3, 0x04d2},
    {0x04d5, 0x04d4},
    {0x04d7, 0x04d6},
    {0x04d9, 0x04d8},
    {0x04db, 0x04da},
    {0x04dd, 0x04dc},
    {0x04df, 0x04de},
    {0x04e1, 0x04e0},
    {0x04e3, 0x04e2},
    {0x04e5, 0x04e4},
    {0x04e7, 0x04e6},
    {0x04e9, 0x04e8},
    {0x04eb, 0x04ea},
    {0x04ed, 0x04ec},
    {0x04ef, 0x04ee},
    {0x04f1, 0x04f0},
    {0x04f3, 0x04f2},
    {0x04f5, 0x04f4},
    {0x04f7, 0x04f6},
    {0x04f9, 0x04f8},
    {0x04fb, 0x04fa},
    {0x04fd, 0x04fc},
    {0x04ff, 0x04fe},

    // End of array marker
    {0, 0}};

const char lowersStr[] = {
    '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69',
    '\x6a', '\x6b', '\x6c', '\x6d', '\x6e', '\x6f', '\x70', '\x71', '\x72',
    '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7a', '\xc3',
    '\xa0', '\xc3', '\xa1', '\xc3', '\xa2', '\xc3', '\xa3', '\xc3', '\xa4',
    '\xc3', '\xa5', '\xc3', '\xa6', '\xc3', '\xa7', '\xc3', '\xa8', '\xc3',
    '\xa9', '\xc3', '\xaa', '\xc3', '\xab', '\xc3', '\xac', '\xc3', '\xad',
    '\xc3', '\xae', '\xc3', '\xaf', '\xc3', '\xb0', '\xc3', '\xb1', '\xc3',
    '\xb2', '\xc3', '\xb3', '\xc3', '\xb4', '\xc3', '\xb5', '\xc3', '\xb6',
    '\xc3', '\xb8', '\xc3', '\xb9', '\xc3', '\xba', '\xc3', '\xbb', '\xc3',
    '\xbc', '\xc3', '\xbd', '\xc3', '\xbe', '\xc3', '\xbf', '\xc4', '\x81',
    '\xc4', '\x83', '\xc4', '\x85', '\xc4', '\x87', '\xc4', '\x89', '\xc4',
    '\x8b', '\xc4', '\x8d', '\xc4', '\x8f', '\xc4', '\x91', '\xc4', '\x93',
    '\xc4', '\x95', '\xc4', '\x97', '\xc4', '\x99', '\xc4', '\x9b', '\xc4',
    '\x9d', '\xc4', '\x9f', '\xc4', '\xa1', '\xc4', '\xa3', '\xc4', '\xa5',
    '\xc4', '\xa7', '\xc4', '\xa9', '\xc4', '\xab', '\xc4', '\xad', '\xc4',
    '\xaf', '\xc4', '\xb3', '\xc4', '\xb5', '\xc4', '\xb7', '\xc4', '\xba',
    '\xc4', '\xbc', '\xc4', '\xbe', '\xc5', '\x80', '\xc5', '\x82', '\xc5',
    '\x84', '\xc5', '\x86', '\xc5', '\x88', '\xc5', '\x8b', '\xc5', '\x8d',
    '\xc5', '\x8f', '\xc5', '\x91', '\xc5', '\x93', '\xc5', '\x95', '\xc5',
    '\x97', '\xc5', '\x99', '\xc5', '\x9b', '\xc5', '\x9d', '\xc5', '\x9f',
    '\xc5', '\xa1', '\xc5', '\xa3', '\xc5', '\xa5', '\xc5', '\xa7', '\xc5',
    '\xa9', '\xc5', '\xab', '\xc5', '\xad', '\xc5', '\xaf', '\xc5', '\xb1',
    '\xc5', '\xb3', '\xc5', '\xb5', '\xc5', '\xb7', '\xc5', '\xba', '\xc5',
    '\xbc', '\xc5', '\xbe', '\xc6', '\x80', '\xc7', '\x9d', '\xc6', '\x9a',
    '\xc6', '\x9e', '\xca', '\x92', '\xc7', '\x86', '\xc7', '\x89', '\xc7',
    '\x8c', '\xc7', '\xb3', '\xc6', '\xbf', '\xc6', '\x83', '\xc6', '\x85',
    '\xc6', '\x88', '\xc6', '\x8c', '\xc6', '\x92', '\xc6', '\x99', '\xc6',
    '\xa1', '\xc6', '\xa3', '\xc6', '\xa5', '\xc6', '\xa8', '\xc6', '\xad',
    '\xc6', '\xb0', '\xc6', '\xb4', '\xc6', '\xb6', '\xc6', '\xb9', '\xc6',
    '\xbd', '\xc7', '\x8e', '\xc7', '\x90', '\xc7', '\x92', '\xc7', '\x94',
    '\xc7', '\x96', '\xc7', '\x98', '\xc7', '\x9a', '\xc7', '\x9c', '\xc7',
    '\x9f', '\xc7', '\xa1', '\xc7', '\xa3', '\xc7', '\xa5', '\xc7', '\xa7',
    '\xc7', '\xa9', '\xc7', '\xab', '\xc7', '\xad', '\xc7', '\xaf', '\xc7',
    '\xb5', '\xc7', '\xb9', '\xc7', '\xbb', '\xc7', '\xbd', '\xc7', '\xbf',
    '\xc8', '\x81', '\xc8', '\x83', '\xc8', '\x85', '\xc8', '\x87', '\xc8',
    '\x89', '\xc8', '\x8b', '\xc8', '\x8d', '\xc8', '\x8f', '\xc8', '\x91',
    '\xc8', '\x93', '\xc8', '\x95', '\xc8', '\x97', '\xc8', '\x99', '\xc8',
    '\x9b', '\xc8', '\x9d', '\xc8', '\x9f', '\xc8', '\xa3', '\xc8', '\xa5',
    '\xc8', '\xa7', '\xc8', '\xa9', '\xc8', '\xab', '\xc8', '\xad', '\xc8',
    '\xaf', '\xc8', '\xb1', '\xc8', '\xb3', '\xc8', '\xbc', '\xc9', '\x82',
    '\xc9', '\x87', '\xc9', '\x89', '\xc9', '\x8b', '\xc9', '\x8d', '\xc9',
    '\x8f', '\xcd', '\xbb', '\xcd', '\xbc', '\xcd', '\xbd', '\xcf', '\xb3',
    '\xce', '\xac', '\xce', '\xad', '\xce', '\xae', '\xce', '\xaf', '\xcf',
    '\x8c', '\xcf', '\x8d', '\xcf', '\x8e', '\xcd', '\xb1', '\xcd', '\xb3',
    '\xcd', '\xb7', '\xce', '\xb1', '\xce', '\xb2', '\xce', '\xb3', '\xce',
    '\xb4', '\xce', '\xb5', '\xce', '\xb6', '\xce', '\xb7', '\xce', '\xb8',
    '\xce', '\xb9', '\xce', '\xba', '\xce', '\xbb', '\xce', '\xbc', '\xce',
    '\xbd', '\xce', '\xbe', '\xce', '\xbf', '\xcf', '\x80', '\xcf', '\x81',
    '\xcf', '\x83', '\xcf', '\x84', '\xcf', '\x85', '\xcf', '\x86', '\xcf',
    '\x87', '\xcf', '\x88', '\xcf', '\x89', '\xcf', '\x8a', '\xcf', '\x8b',
    '\xcf', '\x97', '\xcf', '\x99', '\xcf', '\x9b', '\xcf', '\x9d', '\xcf',
    '\x9f', '\xcf', '\xa1', '\xcf', '\xa3', '\xcf', '\xa5', '\xcf', '\xa7',
    '\xcf', '\xa9', '\xcf', '\xab', '\xcf', '\xad', '\xcf', '\xaf', '\xcf',
    '\xb2', '\xcf', '\xb8', '\xcf', '\xbb', '\xd0', '\xb0', '\xd0', '\xb1',
    '\xd0', '\xb2', '\xd0', '\xb3', '\xd0', '\xb4', '\xd0', '\xb5', '\xd1',
    '\x91', '\xd0', '\xb6', '\xd0', '\xb7', '\xd0', '\xb8', '\xd0', '\xb9',
    '\xd0', '\xba', '\xd0', '\xbb', '\xd0', '\xbc', '\xd0', '\xbd', '\xd0',
    '\xbe', '\xd0', '\xbf', '\xd1', '\x80', '\xd1', '\x81', '\xd1', '\x82',
    '\xd1', '\x83', '\xd1', '\x84', '\xd1', '\x85', '\xd1', '\x86', '\xd1',
    '\x87', '\xd1', '\x88', '\xd1', '\x89', '\xd1', '\x8a', '\xd1', '\x8b',
    '\xd1', '\x8c', '\xd1', '\x8d', '\xd1', '\x8e', '\xd1', '\x8f', '\0'};

const char uppersStr[] = {
    '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49',
    '\x4a', '\x4b', '\x4c', '\x4d', '\x4e', '\x4f', '\x50', '\x51', '\x52',
    '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59', '\x5a', '\xc3',
    '\x80', '\xc3', '\x81', '\xc3', '\x82', '\xc3', '\x83', '\xc3', '\x84',
    '\xc3', '\x85', '\xc3', '\x86', '\xc3', '\x87', '\xc3', '\x88', '\xc3',
    '\x89', '\xc3', '\x8a', '\xc3', '\x8b', '\xc3', '\x8c', '\xc3', '\x8d',
    '\xc3', '\x8e', '\xc3', '\x8f', '\xc3', '\x90', '\xc3', '\x91', '\xc3',
    '\x92', '\xc3', '\x93', '\xc3', '\x94', '\xc3', '\x95', '\xc3', '\x96',
    '\xc3', '\x98', '\xc3', '\x99', '\xc3', '\x9a', '\xc3', '\x9b', '\xc3',
    '\x9c', '\xc3', '\x9d', '\xc3', '\x9e', '\xc5', '\xb8', '\xc4', '\x80',
    '\xc4', '\x82', '\xc4', '\x84', '\xc4', '\x86', '\xc4', '\x88', '\xc4',
    '\x8a', '\xc4', '\x8c', '\xc4', '\x8e', '\xc4', '\x90', '\xc4', '\x92',
    '\xc4', '\x94', '\xc4', '\x96', '\xc4', '\x98', '\xc4', '\x9a', '\xc4',
    '\x9c', '\xc4', '\x9e', '\xc4', '\xa0', '\xc4', '\xa2', '\xc4', '\xa4',
    '\xc4', '\xa6', '\xc4', '\xa8', '\xc4', '\xaa', '\xc4', '\xac', '\xc4',
    '\xae', '\xc4', '\xb2', '\xc4', '\xb4', '\xc4', '\xb6', '\xc4', '\xb9',
    '\xc4', '\xbb', '\xc4', '\xbd', '\xc4', '\xbf', '\xc5', '\x81', '\xc5',
    '\x83', '\xc5', '\x85', '\xc5', '\x87', '\xc5', '\x8a', '\xc5', '\x8c',
    '\xc5', '\x8e', '\xc5', '\x90', '\xc5', '\x92', '\xc5', '\x94', '\xc5',
    '\x96', '\xc5', '\x98', '\xc5', '\x9a', '\xc5', '\x9c', '\xc5', '\x9e',
    '\xc5', '\xa0', '\xc5', '\xa2', '\xc5', '\xa4', '\xc5', '\xa6', '\xc5',
    '\xa8', '\xc5', '\xaa', '\xc5', '\xac', '\xc5', '\xae', '\xc5', '\xb0',
    '\xc5', '\xb2', '\xc5', '\xb4', '\xc5', '\xb6', '\xc5', '\xb9', '\xc5',
    '\xbb', '\xc5', '\xbd', '\xc9', '\x83', '\xc6', '\x8e', '\xc8', '\xbd',
    '\xc8', '\xa0', '\xc6', '\xb7', '\xc7', '\x84', '\xc7', '\x87', '\xc7',
    '\x8a', '\xc7', '\xb1', '\xc7', '\xb7', '\xc6', '\x82', '\xc6', '\x84',
    '\xc6', '\x87', '\xc6', '\x8b', '\xc6', '\x91', '\xc6', '\x98', '\xc6',
    '\xa0', '\xc6', '\xa2', '\xc6', '\xa4', '\xc6', '\xa7', '\xc6', '\xac',
    '\xc6', '\xaf', '\xc6', '\xb3', '\xc6', '\xb5', '\xc6', '\xb8', '\xc6',
    '\xbc', '\xc7', '\x8d', '\xc7', '\x8f', '\xc7', '\x91', '\xc7', '\x93',
    '\xc7', '\x95', '\xc7', '\x97', '\xc7', '\x99', '\xc7', '\x9b', '\xc7',
    '\x9e', '\xc7', '\xa0', '\xc7', '\xa2', '\xc7', '\xa4', '\xc7', '\xa6',
    '\xc7', '\xa8', '\xc7', '\xaa', '\xc7', '\xac', '\xc7', '\xae', '\xc7',
    '\xb4', '\xc7', '\xb8', '\xc7', '\xba', '\xc7', '\xbc', '\xc7', '\xbe',
    '\xc8', '\x80', '\xc8', '\x82', '\xc8', '\x84', '\xc8', '\x86', '\xc8',
    '\x88', '\xc8', '\x8a', '\xc8', '\x8c', '\xc8', '\x8e', '\xc8', '\x90',
    '\xc8', '\x92', '\xc8', '\x94', '\xc8', '\x96', '\xc8', '\x98', '\xc8',
    '\x9a', '\xc8', '\x9c', '\xc8', '\x9e', '\xc8', '\xa2', '\xc8', '\xa4',
    '\xc8', '\xa6', '\xc8', '\xa8', '\xc8', '\xaa', '\xc8', '\xac', '\xc8',
    '\xae', '\xc8', '\xb0', '\xc8', '\xb2', '\xc8', '\xbb', '\xc9', '\x81',
    '\xc9', '\x86', '\xc9', '\x88', '\xc9', '\x8a', '\xc9', '\x8c', '\xc9',
    '\x8e', '\xcf', '\xbd', '\xcf', '\xbe', '\xcf', '\xbf', '\xcd', '\xbf',
    '\xce', '\x86', '\xce', '\x88', '\xce', '\x89', '\xce', '\x8a', '\xce',
    '\x8c', '\xce', '\x8e', '\xce', '\x8f', '\xcd', '\xb0', '\xcd', '\xb2',
    '\xcd', '\xb6', '\xce', '\x91', '\xce', '\x92', '\xce', '\x93', '\xce',
    '\x94', '\xce', '\x95', '\xce', '\x96', '\xce', '\x97', '\xce', '\x98',
    '\xce', '\x99', '\xce', '\x9a', '\xce', '\x9b', '\xce', '\x9c', '\xce',
    '\x9d', '\xce', '\x9e', '\xce', '\x9f', '\xce', '\xa0', '\xce', '\xa1',
    '\xce', '\xa3', '\xce', '\xa4', '\xce', '\xa5', '\xce', '\xa6', '\xce',
    '\xa7', '\xce', '\xa8', '\xce', '\xa9', '\xce', '\xaa', '\xce', '\xab',
    '\xcf', '\x8f', '\xcf', '\x98', '\xcf', '\x9a', '\xcf', '\x9c', '\xcf',
    '\x9e', '\xcf', '\xa0', '\xcf', '\xa2', '\xcf', '\xa4', '\xcf', '\xa6',
    '\xcf', '\xa8', '\xcf', '\xaa', '\xcf', '\xac', '\xcf', '\xae', '\xcf',
    '\xb9', '\xcf', '\xb7', '\xcf', '\xba', '\xd0', '\x90', '\xd0', '\x91',
    '\xd0', '\x92', '\xd0', '\x93', '\xd0', '\x94', '\xd0', '\x95', '\xd0',
    '\x81', '\xd0', '\x96', '\xd0', '\x97', '\xd0', '\x98', '\xd0', '\x99',
    '\xd0', '\x9a', '\xd0', '\x9b', '\xd0', '\x9c', '\xd0', '\x9d', '\xd0',
    '\x9e', '\xd0', '\x9f', '\xd0', '\xa0', '\xd0', '\xa1', '\xd0', '\xa2',
    '\xd0', '\xa3', '\xd0', '\xa4', '\xd0', '\xa5', '\xd0', '\xa6', '\xd0',
    '\xa7', '\xd0', '\xa8', '\xd0', '\xa9', '\xd0', '\xaa', '\xd0', '\xab',
    '\xd0', '\xac', '\xd0', '\xad', '\xd0', '\xae', '\xd0', '\xaf', '\0'};

UTEST(utf8len, data) { ASSERT_EQ(53, utf8len(data)); }

UTEST(utf8nlen, data) { ASSERT_EQ(52, utf8nlen(data, 103)); }

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

UTEST(utf8str, partial) { ASSERT_EQ(haystack + 2, utf8str(haystack, needle)); }

UTEST(utf8str, endfail) {
  ASSERT_EQ((void *)0, utf8str(haystack, endfailneedle));
}

UTEST(utf8casestr, cmp) { ASSERT_EQ(data + 21, utf8casestr(data, cmp)); }

UTEST(utf8casestr, test) { ASSERT_EQ((void *)0, utf8casestr(data, "test")); }

UTEST(utf8casestr, empty) { ASSERT_EQ(data, utf8casestr(data, "")); }

UTEST(utf8casestr, partial) {
  ASSERT_EQ(haystack + 2, utf8casestr(haystack, needle));
}

UTEST(utf8casestr, endfail) {
  ASSERT_EQ((void *)0, utf8casestr(haystack, endfailneedle));
}

UTEST(utf8casestr, latin) {
  ASSERT_EQ(lowersStr, utf8casestr(lowersStr, uppersStr));
}

UTEST(utf8chr, a) { ASSERT_EQ(data + 21, utf8chr(data, 0x3bc)); }

UTEST(utf8chr, b) { ASSERT_EQ(NULL, utf8chr(data, 0x20ac)); }

UTEST(utf8chr, null_terminator) { ASSERT_EQ(data + 104, utf8chr(data, '\0')); }

UTEST(utf8chr, 0x20) { ASSERT_EQ(data + 12, utf8chr(data, 0x20)); }

UTEST(utf8cmp, lt) { ASSERT_LT(0, utf8cmp(data, lt)); }

UTEST(utf8cmp, eq) { ASSERT_EQ(0, utf8cmp(data, data)); }

UTEST(utf8cmp, gt) { ASSERT_GT(0, utf8cmp(data, gt)); }

UTEST(utf8cpy, data) {
  char cpy[512] = {'\0'};

  ASSERT_EQ(53, utf8len(utf8cpy(cpy, data)));
}

// Matches \xce\x93 \xce\xb1 \xce\xb6 \xce\xad \xce\xb5 \xcf\x82 \x20 \xce\xba
// \xce\xb1
UTEST(utf8spn, spn) { ASSERT_EQ(9, utf8spn(data, spn)); }

UTEST(utf8spn, data) { ASSERT_EQ(53, utf8spn(data, data)); }

UTEST(utf8spn, ascii) { ASSERT_EQ(0, utf8spn(data, "ab")); }

UTEST(utf8spn, spnasciisearch) {
  ASSERT_EQ(2, utf8spn(spnasciisearch, spnasciidelims));
}

UTEST(utf8cspn, spn) { ASSERT_EQ(0, utf8cspn(data, spn)); }

UTEST(utf8cspn, data) { ASSERT_EQ(0, utf8cspn(data, data)); }

UTEST(utf8cspn, ascii) { ASSERT_EQ(53, utf8cspn(data, "ab")); }

UTEST(utf8cspn, cspnmultisearch) {
  ASSERT_EQ(12, utf8cspn(cspnmultisearch, cspnmultidelims));
}

UTEST(utf8rchr, a) { ASSERT_EQ(data + 21, utf8rchr(data, 0x3bc)); }

UTEST(utf8rchr, b) { ASSERT_EQ(NULL, utf8rchr(data, 0x20ac)); }

UTEST(utf8rchr, null_terminator) {
  ASSERT_EQ(data + 104, utf8rchr(data, '\0'));
}

UTEST(utf8rchr, 0x20) { ASSERT_EQ(data + 90, utf8rchr(data, 0x20)); }

UTEST(utf8rchr, overrun) {
  const char ascii[] = "Hello\0Hello ";
  ASSERT_EQ(4, utf8rchr(ascii, 'o') - ascii);
}

UTEST(utf8rchr, underrun) {
  const char ascii[] = "Helloo";
  ASSERT_EQ(5, utf8rchr(ascii, 'o') - ascii);
}

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

UTEST(utf8ndup, ascii) {
  void *const dup = utf8ndup("1234567890", 4);
  ASSERT_TRUE(dup);
  ASSERT_EQ(4, utf8len(dup));
  free(dup);
}

UTEST(utf8ndup, ascii_larger) {
  void *const dup = utf8ndup("1234567890", 100);
  ASSERT_TRUE(dup);
  ASSERT_EQ(10, utf8len(dup));
  free(dup);
}

static utf8_int8_t *allocate_from_buffer(utf8_int8_t *user_data, size_t n) {
  return user_data;
}

UTEST(utf8dup_ex, ascii) {
  char user_data[1024];
  void *const dup = utf8dup_ex("1234567890", allocate_from_buffer, user_data);
  ASSERT_TRUE(dup);
  ASSERT_EQ(dup, user_data);
  ASSERT_EQ(10, utf8len(dup));
}

UTEST(utf8ndup_ex, ascii) {
  char user_data[1024];
  void *const dup =
      utf8ndup_ex("1234567890", 4, allocate_from_buffer, user_data);
  ASSERT_TRUE(dup);
  ASSERT_EQ(dup, user_data);
  ASSERT_EQ(4, utf8len(dup));
}

UTEST(utf8size, data) { ASSERT_EQ(105, utf8size(data)); }

UTEST(utf8size, ascii) { ASSERT_EQ(3, utf8size("ab")); }

UTEST(utf8size, empty) { ASSERT_EQ(1, utf8size("")); }

UTEST(utf8size_lazy, data) { ASSERT_EQ(104, utf8size_lazy(data)); }

UTEST(utf8size_lazy, ascii) { ASSERT_EQ(2, utf8size_lazy("ab")); }

UTEST(utf8size_lazy, empty) { ASSERT_EQ(0, utf8size_lazy("")); }

UTEST(utf8nsize_lazy, data) { ASSERT_EQ(50, utf8nsize_lazy(data, 50)); }

UTEST(utf8nsize_lazy, ascii) { ASSERT_EQ(2, utf8nsize_lazy("ab", 50)); }

UTEST(utf8nsize_lazy, empty) { ASSERT_EQ(0, utf8nsize_lazy("", 50)); }

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

UTEST(utf8valid, data) { ASSERT_EQ(NULL, utf8valid(data)); }

UTEST(utf8valid, ascii) { ASSERT_EQ(NULL, utf8valid("ab")); }

UTEST(utf8valid, empty) { ASSERT_EQ(NULL, utf8valid("")); }

UTEST(utf8nvalid, a) {
  char valid[3];

  const char *invalid = valid;
  const size_t invalid_size = 1;

  valid[0] = '\xc2';
  valid[1] = '\x80';
  valid[2] = '\0';

  ASSERT_EQ(invalid, utf8nvalid(valid, invalid_size));
}

UTEST(utf8nvalid, b) {
  char valid[4];

  const char *invalid = valid;
  const size_t invalid_size = 2;

  valid[0] = '\xe0';
  valid[1] = '\x80';
  valid[2] = '\x80';
  valid[3] = '\0';

  ASSERT_EQ(invalid, utf8nvalid(valid, invalid_size));
}

UTEST(utf8nvalid, c) {
  char valid[5];

  const char *invalid = valid;
  const size_t invalid_size = 3;

  valid[0] = '\xf0';
  valid[1] = '\x80';
  valid[2] = '\x80';
  valid[3] = '\x80';
  valid[4] = '\0';
  ASSERT_EQ(invalid, utf8nvalid(valid, invalid_size));
}

UTEST(utf8nvalid, data) { ASSERT_EQ(NULL, utf8nvalid(data, 105)); }

UTEST(utf8nvalid, ascii) { ASSERT_EQ(NULL, utf8nvalid("ab", 3)); }

UTEST(utf8nvalid, empty) { ASSERT_EQ(NULL, utf8nvalid("", 1)); }

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

UTEST(utf8ncat, zero_n) {
  char cat[512] = {'\0'};
  ASSERT_EQ(NULL, utf8valid(utf8ncat(cat, data, 0)));
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

UTEST(utf8ncpy, check_no_buffer_overflow) {
  utf8_int32_t i;
  char buffer[11] = {0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
                     0xdd, 0xdd, 0xdd, 0xdd, 0xdd};
  ASSERT_EQ(buffer, utf8ncpy(buffer, "foo", 10));

  ASSERT_EQ('f', buffer[0]);
  ASSERT_EQ('o', buffer[1]);
  ASSERT_EQ('o', buffer[2]);

  for (i = 3; 10 != i; i++) {
    ASSERT_EQ(0, buffer[i]);
  }

  ASSERT_EQ((char)0xdd, buffer[10]);
}

UTEST(utf8ncpy, check_no_n_overflow) {
  char buffer[4] = {1, 2, 3, 4};
  ASSERT_EQ(buffer, utf8ncpy(buffer, "foo", 2));

  ASSERT_EQ('f', buffer[0]);
  ASSERT_EQ('o', buffer[1]);
  ASSERT_EQ(3, buffer[2]);
  ASSERT_EQ(4, buffer[3]);
}

UTEST(utf8ncpy, truncated_copy_valid) {
  char cpy1[32] = {'\0'};
  char cpy2[3] = {'\0'};
  char cpy3[1] = {'\0'};

  utf8ncpy(cpy1, data, 32);
  ASSERT_EQ(NULL, utf8valid(cpy1));

  utf8ncpy(cpy2, data, 3);
  ASSERT_EQ(NULL, utf8valid(cpy2));

  utf8ncpy(cpy3, data, 1);
  ASSERT_EQ(NULL, utf8valid(cpy3));
}

UTEST(utf8ncpy, truncated_copy_null_terminated) {
  char cpy1[32] = {'\0'};
  char cpy2[2] = {'\0'};
  char cpy3[3] = {'\0'};

  utf8ncpy(cpy1, data, 32);
  ASSERT_EQ('\0', cpy1[31]);

  utf8ncpy(cpy2, data, 2);
  ASSERT_EQ('\0', cpy2[0]);

  utf8ncpy(cpy3, data, 3);
  ASSERT_EQ('\0', cpy3[2]);
}

UTEST(utf8pbrk, pbrk) { ASSERT_EQ(data + 8, utf8pbrk(data, pbrk)); }

UTEST(utf8pbrk, data) { ASSERT_EQ(data, utf8pbrk(data, data)); }

UTEST(utf8casecmp, ascii) { ASSERT_EQ(0, utf8casecmp(ascii1, ascii2)); }
UTEST(utf8casecmp, latin_upvslow) {
  ASSERT_EQ(0, utf8casecmp(lowersStr, uppersStr));
}
UTEST(utf8casecmp, latin_lowvsup) {
  ASSERT_EQ(0, utf8casecmp(uppersStr, lowersStr));
}

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

UTEST(utf8ncasecmp, ascii) { ASSERT_EQ(0, utf8ncasecmp(ascii1, ascii2, 4)); }
UTEST(utf8ncasecmp, latin_upvslow) {
  ASSERT_EQ(0, utf8ncasecmp(lowersStr, uppersStr, 120));
}
UTEST(utf8ncasecmp, latin_lowvsup) {
  ASSERT_EQ(0, utf8ncasecmp(uppersStr, lowersStr, 120));
}

UTEST(utf8ncasecmp, basic_ascii) {
  ASSERT_EQ(-15, utf8ncasecmp(".gdoc", ".GSHeeT", 5));
  ASSERT_EQ(-4, utf8ncasecmp(".gsheet", ".gSLiDe", 7));

#ifndef _MSC_VER
  ASSERT_EQ(strcasecmp(".gdoc", ".GSHeeT"),
            utf8ncasecmp(".gdoc", ".GSHeeT", 5));
  ASSERT_EQ(strcasecmp(".gsheet", ".gSLiDe"),
            utf8ncasecmp(".gsheet", ".gSLiDe", 7));
#endif
}

UTEST(utf8ncasecmp, latin_extended_a) {
	ASSERT_EQ(96, utf8ncasecmp("Camón Romasan", "camu", 4));
}

UTEST(utf8codepoint, data) {
  utf8_int32_t codepoint;
  void *v;
  size_t expected_length = utf8len(data) - 1;
  for (v = utf8codepoint(data, &codepoint); codepoint;
       v = utf8codepoint(v, &codepoint)) {
    ASSERT_EQ(expected_length, utf8len(v));
    expected_length -= 1;
  }
}

UTEST(utf8codepointcalcsize, data) {
  const char *v;
  // No -1 here since we start at the beginning
  size_t expected_length = utf8len(data);
  for (v = data; *v; v += utf8codepointcalcsize(v)) {
    ASSERT_EQ(expected_length, utf8len(v));
    expected_length -= 1;
  }
}

UTEST(utf8codepointsize, size_1) { ASSERT_EQ(1, utf8codepointsize('A')); }

UTEST(utf8codepointsize, size_4) { ASSERT_EQ(4, utf8codepointsize(0x20C78)); }

UTEST(utf8catcodepoint, data) {
  char buffer[129];
  char *p = buffer;
  long cp;
  int i;
  memset(buffer, 0, 129);
  for (i = 0; i < 128; i++) {
    cp = (i % 2 == 0 ? 'A' : 0x20C78);
    p = utf8catcodepoint(p, cp, 128 - (p - buffer));
    if (!p) {
      break;
    }
  }
  ASSERT_EQ(51, utf8len(buffer));
}

UTEST(utf8islower, upper) {
  utf8_int32_t i;

  for (i = 0; 0 != lowupPairs[i].lower; i++) {
    ASSERT_EQ(0, utf8islower(lowupPairs[i].upper));
  }
}

UTEST(utf8islower, lower) {
  utf8_int32_t i;

  for (i = 0; 0 != lowupPairs[i].lower; i++) {
    ASSERT_EQ(1, utf8islower(lowupPairs[i].lower));
  }
}

UTEST(utf8isupper, upper) {
  utf8_int32_t i;

  for (i = 0; 0 != lowupPairs[i].lower; i++) {
    ASSERT_EQ(1, utf8isupper(lowupPairs[i].upper));
  }
}

UTEST(utf8isupper, lower) {
  utf8_int32_t i;

  for (i = 0; 0 != lowupPairs[i].lower; i++) {
    ASSERT_EQ(0, utf8isupper(lowupPairs[i].lower));
  }
}

UTEST(utf8lwr, ascii) {
  size_t sz;
  char *str;
  sz = strlen(ascii1);
  str = (char *)malloc(sz + 1);
  memcpy(str, ascii1, sz + 1);
  utf8lwr(str);
  ASSERT_EQ(0, strcmp(str, "i like goats yarhar."));
  free(str);
}

UTEST(utf8lwr, latin_lower) {
  size_t sz;
  void *str;
  sz = utf8size(lowersStr);
  str = malloc(sz);
  memcpy(str, lowersStr, sz);
  utf8lwr(str);
  ASSERT_EQ(0, utf8cmp(str, lowersStr));
  free(str);
}

UTEST(utf8lwr, latin_upper) {
  size_t sz;
  void *str;
  sz = utf8size(uppersStr);
  str = malloc(sz);
  memcpy(str, uppersStr, sz);
  utf8lwr(str);
  ASSERT_EQ(0, utf8cmp(str, lowersStr));
  free(str);
}

UTEST(utf8upr, ascii) {
  size_t sz;
  char *str;
  sz = strlen(ascii1);
  str = (char *)malloc(sz + 1);
  memcpy(str, ascii1, sz + 1);
  utf8upr(str);
  ASSERT_EQ(0, strcmp(str, "I LIKE GOATS YARHAR."));
  free(str);
}

UTEST(utf8upr, latin_lower) {
  size_t sz;
  void *str;
  sz = utf8size(lowersStr);
  str = malloc(sz);
  memcpy(str, lowersStr, sz);
  utf8upr(str);
  ASSERT_EQ(0, utf8cmp(str, uppersStr));
  free(str);
}

UTEST(utf8upr, latin_upper) {
  size_t sz;
  void *str;
  sz = utf8size(uppersStr);
  str = malloc(sz);
  memcpy(str, uppersStr, sz);
  utf8upr(str);
  ASSERT_EQ(0, utf8cmp(str, uppersStr));
  free(str);
}

UTEST(utf8casecmp, basic_ascii) {
  ASSERT_EQ(-15, utf8casecmp(".gdoc", ".GSHeeT"));
  ASSERT_EQ(-4, utf8casecmp(".gsheet", ".gSLiDe"));

#ifndef _MSC_VER
  ASSERT_EQ(strcasecmp(".gdoc", ".GSHeeT"), utf8casecmp(".gdoc", ".GSHeeT"));
  ASSERT_EQ(strcasecmp(".gsheet", ".gSLiDe"),
            utf8casecmp(".gsheet", ".gSLiDe"));
#endif
}

UTEST(utf8lwr, greek_capital_theta) {
  const char ref[] = {'\xce', '\xb8', '\xce', '\xb8', '\xce',
                      '\xb8', '\xcf', '\x91', '\0'};
  char str[] = {'\xcf', '\xb4', '\xce', '\xb8', '\xce',
                '\x98', '\xcf', '\x91', '\0'};

  utf8lwr(str);

  ASSERT_EQ(0, utf8cmp(str, ref));
}

UTEST(utf8upr, greek_capital_theta) {
  const char ref[] = {'\xcf', '\xb4', '\xce', '\x98', '\xce',
                      '\x98', '\xce', '\x98', '\0'};
  char str[] = {'\xcf', '\xb4', '\xce', '\xb8', '\xce',
                '\x98', '\xcf', '\x91', '\0'};

  utf8upr(str);

  ASSERT_EQ(0, utf8cmp(str, ref));
}

UTEST(utf8casecmp, greek_capital_theta) {
  const char ref[] = {'\xcf', '\xb4', '\xce', '\x98', '\xce',
                      '\x98', '\xce', '\x98', '\0'};
  char str[] = {'\xcf', '\xb4', '\xce', '\xb8', '\xce',
                '\x98', '\xcf', '\x91', '\0'};

  ASSERT_EQ(0, utf8casecmp(ref, str));
}

UTEST(utf8ncasecmp, greek_capital_theta) {
  const char ref[] = {'\xcf', '\xb4', '\xce', '\x98', '\xce',
                      '\x98', '\xce', '\x98', '\0'};
  char str[] = {'\xcf', '\xb4', '\xce', '\xb8', '\xce',
                '\x98', '\xcf', '\x91', '\0'};

  ASSERT_EQ(0, utf8ncasecmp(ref, str, 8));
}

UTEST(utf8rcodepoint, ascii) {
  utf8_int32_t codepoint;

  ASSERT_EQ(ascii1, utf8rcodepoint(ascii1 + 1, &codepoint));

  ASSERT_EQ(ascii1[1], codepoint);
}

UTEST(utf8rcodepoint, latin) {
  utf8_int32_t codepoint;

  ASSERT_EQ(data, utf8rcodepoint(data + 2, &codepoint));

  ASSERT_EQ(0x3B1, codepoint);
}

UTEST(utf8makevalid, a) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xf0';
  invalid[1] = '\x8f';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '\xef');
}

UTEST(utf8makevalid, b) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xf1';
  invalid[1] = '\x3f';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '?');
  ASSERT_EQ(invalid[2], '?');
  ASSERT_EQ(invalid[3], '?');
  ASSERT_EQ(invalid[4], '\0');
}

UTEST(utf8makevalid, c) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xf1';
  invalid[1] = '\xbf';
  invalid[2] = '\x3f';
  invalid[3] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '?');
  ASSERT_EQ(invalid[2], '?');
  ASSERT_EQ(invalid[3], '?');
  ASSERT_EQ(invalid[4], '\0');
}

UTEST(utf8makevalid, d) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xf1';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';
  invalid[3] = '\x3f';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '?');
  ASSERT_EQ(invalid[2], '?');
  ASSERT_EQ(invalid[3], '?');
  ASSERT_EQ(invalid[4], '\0');
}

UTEST(utf8makevalid, e) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xe0';
  invalid[1] = '\x9f';
  invalid[2] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '\xdf');
  ASSERT_EQ(invalid[1], '\xbf');
  ASSERT_EQ(invalid[2], '\0');
}

UTEST(utf8makevalid, f) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xef';
  invalid[1] = '\x3f';
  invalid[2] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '?');
  ASSERT_EQ(invalid[2], '?');
  ASSERT_EQ(invalid[3], '\0');
}

UTEST(utf8makevalid, g) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xef';
  invalid[1] = '\xbf';
  invalid[2] = '\x3f';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '?');
  ASSERT_EQ(invalid[2], '?');
  ASSERT_EQ(invalid[3], '\0');
}

UTEST(utf8makevalid, h) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xc1';
  invalid[1] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '\x7f');
  ASSERT_EQ(invalid[1], '\0');
}

UTEST(utf8makevalid, i) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xdf';
  invalid[1] = '\x3f';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '?');
  ASSERT_EQ(invalid[2], '\0');
}

UTEST(utf8makevalid, j) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\x80';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '\0');
}

UTEST(utf8makevalid, k) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xf8';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '?');
  ASSERT_EQ(invalid[1], '\0');
}

UTEST(utf8makevalid, l) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xf1';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';
  invalid[4] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '\xf1');
  ASSERT_EQ(invalid[1], '\xbf');
  ASSERT_EQ(invalid[2], '\xbf');
  ASSERT_EQ(invalid[3], '\xbf');
  ASSERT_EQ(invalid[4], '?');
  ASSERT_EQ(invalid[5], '\0');
}

UTEST(utf8makevalid, m) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xef';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';
  invalid[3] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '\xef');
  ASSERT_EQ(invalid[1], '\xbf');
  ASSERT_EQ(invalid[2], '\xbf');
  ASSERT_EQ(invalid[3], '?');
  ASSERT_EQ(invalid[4], '\0');
}

UTEST(utf8makevalid, n) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xdf';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';

  ASSERT_EQ(0, utf8makevalid(invalid, '?'));

  ASSERT_EQ(invalid[0], '\xdf');
  ASSERT_EQ(invalid[1], '\xbf');
  ASSERT_EQ(invalid[2], '?');
  ASSERT_EQ(invalid[3], '\0');
}

UTEST(utf8makevalid, invalid_replacement) {
  char invalid[6];
  memset(invalid, 0, 6);

  invalid[0] = '\xdf';
  invalid[1] = '\xbf';
  invalid[2] = '\xbf';

  ASSERT_NE(0, utf8makevalid(invalid, 0x80));
}

UTEST(utf8nvalid, exactly_2_bytes) {
  const char terminated[] = "\xc2\xa3";
  ASSERT_EQ(utf8nvalid(terminated, 2), NULL);
}

UTEST(utf8nvalid, exactly_3_bytes) {
  const char terminated[] = "\xe1\xbd\xb6";
  ASSERT_EQ(utf8nvalid(terminated, 3), NULL);
}

UTEST(utf8nvalid, exactly_4_bytes) {
  const char terminated[] = "\xf0\x90\x8d\x88";
  ASSERT_EQ(utf8nvalid(terminated, 4), NULL);
}

UTEST_MAIN();
