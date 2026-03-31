#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Provide necessary type definitions and macros that the code depends on
#ifndef XMP_StringPtr
#define XMP_StringPtr const char *
#endif

#ifndef XMP_Uns32
typedef unsigned long XMP_Uns32;
#endif

#ifndef XMP_Assert
#define XMP_Assert(x) assert(x)
#endif

#ifndef UnsByte
#define UnsByte(x) ((unsigned char)(x))
#endif

#ifndef UCP
#define UCP(x) ((UniCodePoint)(x))
#endif

typedef unsigned long UniCodePoint;

typedef enum UniCharKind {
    UCK_normal = 0,
    UCK_space = 1,
    UCK_comma = 2,
    UCK_semicolon = 3,
    UCK_quote = 4,
    UCK_control = 5
} UniCharKind;

// Include the static function by copying its implementation for testing
static void ClassifyCharacter(XMP_StringPtr fullString, size_t offset,
                               UniCharKind *charKind, size_t *charSize,
                               UniCodePoint *uniChar) {
    *charKind = UCK_normal;
    unsigned char currByte = UnsByte(fullString[offset]);

    if (currByte < UnsByte(0x80)) {
        *charSize = 1;
        *uniChar = currByte;

        if (currByte > UnsByte(0x22)) {
            if (currByte == UnsByte(0x2C)) {
                *charKind = UCK_comma;
            } else if (currByte == UnsByte(0x3B)) {
                *charKind = UCK_semicolon;
            } else if ((currByte == UnsByte(0x5B)) || (currByte == UnsByte(0x5D))) {
                *charKind = UCK_quote;
            }
        } else {
            if (currByte == UnsByte(0x22)) {
                *charKind = UCK_quote;
            } else if (currByte == UnsByte(0x21)) {
                *charKind = UCK_normal;
            } else if (currByte == UnsByte(0x20)) {
                *charKind = UCK_space;
            } else {
                *charKind = UCK_control;
            }
        }
    } else {
        *charSize = 0;
        *uniChar = currByte;
        while ((*uniChar & 0x80) != 0) {
            ++(*charSize);
            *uniChar = *uniChar << 1;
        }
        XMP_Assert((offset + *charSize) <= strlen(fullString));

        *uniChar = *uniChar & 0x7F;
        *uniChar = *uniChar >> *charSize;

        for (size_t i = (offset + 1); i < (offset + *charSize); ++i) {
            *uniChar = (*uniChar << 6) | (UnsByte(fullString[i]) & 0x3F);
        }

        XMP_Uns32 upperBits = *uniChar >> 8;

        if (upperBits == 0xFF) {
            if (*uniChar == UCP(0xFF0C)) {
                *charKind = UCK_comma;
            } else if (*uniChar == UCP(0xFF1B)) {
                *charKind = UCK_semicolon;
            } else if (*uniChar == UCP(0xFF64)) {
                *charKind = UCK_comma;
            }
        } else if (upperBits == 0xFE) {
            if (*uniChar == UCP(0xFE50)) {
                *charKind = UCK_comma;
            } else if (*uniChar == UCP(0xFE51)) {
                *charKind = UCK_comma;
            } else if (*uniChar == UCP(0xFE54)) {
                *charKind = UCK_semicolon;
            }
        } else if (upperBits == 0x30) {
            if (*uniChar == UCP(0x3000)) {
                *charKind = UCK_space;
            } else if (*uniChar == UCP(0x3001)) {
                *charKind = UCK_comma;
            } else if ((UCP(0x3008) <= *uniChar) && (*uniChar <= UCP(0x300F))) {
                *charKind = UCK_quote;
            } else if (*uniChar == UCP(0x303F)) {
                *charKind = UCK_space;
            } else if ((UCP(0x301D) <= *uniChar) && (*uniChar <= UCP(0x301F))) {
                *charKind = UCK_quote;
            }
        } else if (upperBits == 0x20) {
            if ((UCP(0x2000) <= *uniChar) && (*uniChar <= UCP(0x200B))) {
                *charKind = UCK_space;
            } else if (*uniChar == UCP(0x2015)) {
                *charKind = UCK_quote;
            } else if ((UCP(0x2018) <= *uniChar) && (*uniChar <= UCP(0x201F))) {
                *charKind = UCK_quote;
            } else if (*uniChar == UCP(0x2028)) {
                *charKind = UCK_control;
            } else if (*uniChar == UCP(0x2029)) {
                *charKind = UCK_control;
            } else if ((*uniChar == UCP(0x2039)) || (*uniChar == UCP(0x203A))) {
                *charKind = UCK_quote;
            }
        } else if (upperBits == 0x06) {
            if (*uniChar == UCP(0x060C)) {
                *charKind = UCK_comma;
            } else if (*uniChar == UCP(0x061B)) {
                *charKind = UCK_semicolon;
            }
        } else if (upperBits == 0x05) {
            if (*uniChar == UCP(0x055D)) {
                *charKind = UCK_comma;
            }
        } else if (upperBits == 0x03) {
            if (*uniChar == UCP(0x037E)) {
                *charKind = UCK_semicolon;
            }
        } else if (upperBits == 0x00) {
            if ((*uniChar == UCP(0x00AB)) || (*uniChar == UCP(0x00BB))) {
                *charKind = UCK_quote;
            }
        }
    }
}

// Helper: encode a Unicode code point to UTF-8 string
static std::string EncodeUTF8(UniCodePoint cp) {
    std::string result;
    if (cp < 0x80) {
        result += (char)cp;
    } else if (cp < 0x800) {
        result += (char)(0xC0 | (cp >> 6));
        result += (char)(0x80 | (cp & 0x3F));
    } else if (cp < 0x10000) {
        result += (char)(0xE0 | (cp >> 12));
        result += (char)(0x80 | ((cp >> 6) & 0x3F));
        result += (char)(0x80 | (cp & 0x3F));
    } else {
        result += (char)(0xF0 | (cp >> 18));
        result += (char)(0x80 | ((cp >> 12) & 0x3F));
        result += (char)(0x80 | ((cp >> 6) & 0x3F));
        result += (char)(0x80 | (cp & 0x3F));
    }
    return result;
}

class ClassifyCharacterTest_1915 : public ::testing::Test {
protected:
    UniCharKind charKind;
    size_t charSize;
    UniCodePoint uniChar;

    void Classify(const char* str, size_t offset = 0) {
        ClassifyCharacter(str, offset, &charKind, &charSize, &uniChar);
    }

    void ClassifyCodePoint(UniCodePoint cp) {
        std::string s = EncodeUTF8(cp);
        encoded_ = s;
        ClassifyCharacter(encoded_.c_str(), 0, &charKind, &charSize, &uniChar);
    }

    std::string encoded_;
};

// ============================================================
// ASCII normal characters
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiLetterA_IsNormal_1915) {
    Classify("A");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)'A');
}

TEST_F(ClassifyCharacterTest_1915, AsciiLetterZ_IsNormal_1915) {
    Classify("z");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)'z');
}

TEST_F(ClassifyCharacterTest_1915, AsciiDigit0_IsNormal_1915) {
    Classify("0");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
}

TEST_F(ClassifyCharacterTest_1915, AsciiExclamation_IsNormal_1915) {
    // 0x21 = '!'
    Classify("!");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x21);
}

// ============================================================
// ASCII space (0x20)
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiSpace_IsSpace_1915) {
    Classify(" ");
    EXPECT_EQ(charKind, UCK_space);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x20);
}

// ============================================================
// ASCII comma (0x2C)
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiComma_IsComma_1915) {
    Classify(",");
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x2C);
}

// ============================================================
// ASCII semicolon (0x3B)
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiSemicolon_IsSemicolon_1915) {
    Classify(";");
    EXPECT_EQ(charKind, UCK_semicolon);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x3B);
}

// ============================================================
// ASCII double quote (0x22)
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiDoubleQuote_IsQuote_1915) {
    Classify("\"");
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x22);
}

// ============================================================
// ASCII open bracket (0x5B) and close bracket (0x5D) — quotes in CJK
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiOpenBracket_IsQuote_1915) {
    Classify("[");
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x5B);
}

TEST_F(ClassifyCharacterTest_1915, AsciiCloseBracket_IsQuote_1915) {
    Classify("]");
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x5D);
}

// ============================================================
// ASCII control characters (< 0x20, not space or exclamation)
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiNullByte_IsControl_1915) {
    // Null byte at offset 0 in a longer string
    const char str[] = "\x01\x00";
    Classify(str, 0);
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 1u);
}

TEST_F(ClassifyCharacterTest_1915, AsciiTab_IsControl_1915) {
    Classify("\t");
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x09);
}

TEST_F(ClassifyCharacterTest_1915, AsciiNewline_IsControl_1915) {
    Classify("\n");
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x0A);
}

TEST_F(ClassifyCharacterTest_1915, AsciiCarriageReturn_IsControl_1915) {
    Classify("\r");
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x0D);
}

TEST_F(ClassifyCharacterTest_1915, AsciiControlChar0x1F_IsControl_1915) {
    Classify("\x1F");
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 1u);
}

// ============================================================
// ASCII characters between 0x23 and 0x7F that are not special
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiHash_IsNormal_1915) {
    // 0x23 = '#'
    Classify("#");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
}

TEST_F(ClassifyCharacterTest_1915, AsciiDot_IsNormal_1915) {
    Classify(".");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
}

TEST_F(ClassifyCharacterTest_1915, AsciiColon_IsNormal_1915) {
    // 0x3A = ':'
    Classify(":");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
}

// ============================================================
// Offset parameter test
// ============================================================

TEST_F(ClassifyCharacterTest_1915, OffsetSelectsCorrectCharacter_1915) {
    Classify("A,B", 1);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)',');
}

TEST_F(ClassifyCharacterTest_1915, OffsetSelectsThirdCharacter_1915) {
    Classify("A,B", 2);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)'B');
}

// ============================================================
// UTF-8 2-byte characters: U+00AB and U+00BB (guillemet quotes)
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U00AB_IsQuote_1915) {
    ClassifyCodePoint(0x00AB);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x00AB);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U00BB_IsQuote_1915) {
    ClassifyCodePoint(0x00BB);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x00BB);
}

// ============================================================
// U+00-- but not quote -> normal
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U00A0_IsNormal_1915) {
    ClassifyCodePoint(0x00A0);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x00A0);
}

// ============================================================
// UTF-8 2-byte: Greek semicolon U+037E
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U037E_IsSemicolon_1915) {
    ClassifyCodePoint(0x037E);
    EXPECT_EQ(charKind, UCK_semicolon);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x037E);
}

// ============================================================
// UTF-8 2-byte: Armenian comma U+055D
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U055D_IsComma_1915) {
    ClassifyCodePoint(0x055D);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x055D);
}

// ============================================================
// UTF-8 2-byte: Arabic comma U+060C and semicolon U+061B
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U060C_IsComma_1915) {
    ClassifyCodePoint(0x060C);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x060C);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U061B_IsSemicolon_1915) {
    ClassifyCodePoint(0x061B);
    EXPECT_EQ(charKind, UCK_semicolon);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x061B);
}

// ============================================================
// UTF-8 3-byte: U+20xx range
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U2000_IsSpace_1915) {
    ClassifyCodePoint(0x2000);
    EXPECT_EQ(charKind, UCK_space);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x2000);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U200B_IsSpace_1915) {
    ClassifyCodePoint(0x200B);
    EXPECT_EQ(charKind, UCK_space);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x200B);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U2005_IsSpace_1915) {
    // mid-range of U+2000..U+200B
    ClassifyCodePoint(0x2005);
    EXPECT_EQ(charKind, UCK_space);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U2015_IsQuote_1915) {
    ClassifyCodePoint(0x2015);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x2015);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U2018_IsQuote_1915) {
    ClassifyCodePoint(0x2018);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U201F_IsQuote_1915) {
    ClassifyCodePoint(0x201F);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U201C_IsQuote_1915) {
    ClassifyCodePoint(0x201C);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U2028_IsControl_1915) {
    ClassifyCodePoint(0x2028);
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x2028);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U2029_IsControl_1915) {
    ClassifyCodePoint(0x2029);
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x2029);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U2039_IsQuote_1915) {
    ClassifyCodePoint(0x2039);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U203A_IsQuote_1915) {
    ClassifyCodePoint(0x203A);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U200C_IsNormal_1915) {
    // Just past the space range, should be normal
    ClassifyCodePoint(0x200C);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U2016_IsNormal_1915) {
    // Not a recognized special char in U+20xx
    ClassifyCodePoint(0x2016);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

// ============================================================
// UTF-8 3-byte: U+30xx range
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U3000_IsSpace_1915) {
    ClassifyCodePoint(0x3000);
    EXPECT_EQ(charKind, UCK_space);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x3000);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U3001_IsComma_1915) {
    ClassifyCodePoint(0x3001);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U3008_IsQuote_1915) {
    ClassifyCodePoint(0x3008);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U300F_IsQuote_1915) {
    ClassifyCodePoint(0x300F);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U300B_IsQuote_1915) {
    // Mid-range of 3008..300F
    ClassifyCodePoint(0x300B);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U303F_IsSpace_1915) {
    ClassifyCodePoint(0x303F);
    EXPECT_EQ(charKind, UCK_space);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U301D_IsQuote_1915) {
    ClassifyCodePoint(0x301D);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U301E_IsQuote_1915) {
    ClassifyCodePoint(0x301E);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U301F_IsQuote_1915) {
    ClassifyCodePoint(0x301F);
    EXPECT_EQ(charKind, UCK_quote);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U3002_IsNormal_1915) {
    // Not a recognized special char in the U+30xx range
    ClassifyCodePoint(0x3002);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U3007_IsNormal_1915) {
    // Just before the quote range 3008
    ClassifyCodePoint(0x3007);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U3010_IsNormal_1915) {
    // Just after the quote range 300F
    ClassifyCodePoint(0x3010);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

// ============================================================
// UTF-8 3-byte: U+FExx range
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_UFE50_IsComma_1915) {
    ClassifyCodePoint(0xFE50);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UFE51_IsComma_1915) {
    ClassifyCodePoint(0xFE51);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UFE54_IsSemicolon_1915) {
    ClassifyCodePoint(0xFE54);
    EXPECT_EQ(charKind, UCK_semicolon);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UFE52_IsNormal_1915) {
    // Not a recognized special in FE range
    ClassifyCodePoint(0xFE52);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

// ============================================================
// UTF-8 3-byte: U+FFxx range
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_UFF0C_IsComma_1915) {
    ClassifyCodePoint(0xFF0C);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0xFF0C);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UFF1B_IsSemicolon_1915) {
    ClassifyCodePoint(0xFF1B);
    EXPECT_EQ(charKind, UCK_semicolon);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UFF64_IsComma_1915) {
    ClassifyCodePoint(0xFF64);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UFF00_IsNormal_1915) {
    // Not a recognized special in FF range
    ClassifyCodePoint(0xFF00);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

// ============================================================
// Boundary: just outside recognized ranges
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U1FFF_IsNormal_1915) {
    // Just before the U+20xx range
    ClassifyCodePoint(0x1FFF);
    EXPECT_EQ(charKind, UCK_normal);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U0500_IsNormal_1915) {
    // In U+05xx but not 055D
    ClassifyCodePoint(0x0500);
    EXPECT_EQ(charKind, UCK_normal);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U055E_IsNormal_1915) {
    // Just after Armenian comma
    ClassifyCodePoint(0x055E);
    EXPECT_EQ(charKind, UCK_normal);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U0600_IsNormal_1915) {
    // In U+06xx but not 060C or 061B
    ClassifyCodePoint(0x0600);
    EXPECT_EQ(charKind, UCK_normal);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U0300_IsNormal_1915) {
    // In U+03xx but not 037E
    ClassifyCodePoint(0x0300);
    EXPECT_EQ(charKind, UCK_normal);
}

// ============================================================
// Multi-byte character at non-zero offset
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_MultiByteAtOffset_1915) {
    // "A" followed by U+3001 (ideographic comma, 3 bytes: E3 80 81)
    std::string s = "A";
    s += EncodeUTF8(0x3001);
    ClassifyCharacter(s.c_str(), 1, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x3001);
}

// ============================================================
// Verify charSize for various byte lengths
// ============================================================

TEST_F(ClassifyCharacterTest_1915, CharSizeIs1ForAscii_1915) {
    Classify("X");
    EXPECT_EQ(charSize, 1u);
}

TEST_F(ClassifyCharacterTest_1915, CharSizeIs2ForTwoByteUTF8_1915) {
    ClassifyCodePoint(0x00C0); // 2-byte UTF-8
    EXPECT_EQ(charSize, 2u);
}

TEST_F(ClassifyCharacterTest_1915, CharSizeIs3ForThreeByteUTF8_1915) {
    ClassifyCodePoint(0x3000); // 3-byte UTF-8
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, CharSizeIs4ForFourByteUTF8_1915) {
    ClassifyCodePoint(0x10000); // 4-byte UTF-8
    EXPECT_EQ(charSize, 4u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x10000);
    EXPECT_EQ(charKind, UCK_normal);
}

// ============================================================
// Unrecognized multi-byte ranges -> normal
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_U4E00_IsNormal_1915) {
    // CJK unified ideograph, not a special character
    ClassifyCodePoint(0x4E00);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 3u);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U10FFFF_IsNormal_1915) {
    // Max valid Unicode code point, 4-byte UTF-8, should be normal
    ClassifyCodePoint(0x10FFFF);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 4u);
}

// ============================================================
// Boundary between ascii and multi-byte
// ============================================================

TEST_F(ClassifyCharacterTest_1915, AsciiMaxNonSpecial0x7E_IsNormal_1915) {
    // '~' = 0x7E
    Classify("~");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x7E);
}

TEST_F(ClassifyCharacterTest_1915, Ascii0x7F_IsNormal_1915) {
    // DEL = 0x7F, still < 0x80
    Classify("\x7F");
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x7F);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_U0080_IsNormal_1915) {
    // First 2-byte UTF-8 character, should be normal
    ClassifyCodePoint(0x0080);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 2u);
    EXPECT_EQ(uniChar, (UniCodePoint)0x0080);
}

// ============================================================
// Multiple ASCII characters with offset to verify isolation
// ============================================================

TEST_F(ClassifyCharacterTest_1915, StringWithMultipleSpecials_1915) {
    const char* str = " ,;\"[A";

    // offset 0: space
    ClassifyCharacter(str, 0, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_space);

    // offset 1: comma
    ClassifyCharacter(str, 1, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_comma);

    // offset 2: semicolon
    ClassifyCharacter(str, 2, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_semicolon);

    // offset 3: double quote
    ClassifyCharacter(str, 3, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_quote);

    // offset 4: open bracket
    ClassifyCharacter(str, 4, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_quote);

    // offset 5: 'A' normal
    ClassifyCharacter(str, 5, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_normal);
}

// ============================================================
// Verify uniChar value for multi-byte
// ============================================================

TEST_F(ClassifyCharacterTest_1915, UTF8_UniCharValueCorrectForU2018_1915) {
    ClassifyCodePoint(0x2018);
    EXPECT_EQ(uniChar, (UniCodePoint)0x2018);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UniCharValueCorrectForUFF0C_1915) {
    ClassifyCodePoint(0xFF0C);
    EXPECT_EQ(uniChar, (UniCodePoint)0xFF0C);
}

TEST_F(ClassifyCharacterTest_1915, UTF8_UniCharValueCorrectForU10000_1915) {
    ClassifyCodePoint(0x10000);
    EXPECT_EQ(uniChar, (UniCodePoint)0x10000);
}
