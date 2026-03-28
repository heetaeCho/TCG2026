#include <gtest/gtest.h>
#include <vector>
#include <cstring>

// Include the necessary headers from poppler
#include "poppler/CharTypes.h"
#include "poppler/UnicodeTypeTable.h"

class UnicodeTypeTableTest_1877 : public ::testing::Test {
protected:
    void TearDown() override {
    }
};

// Test NFKC normalization with empty input
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_EmptyInput_1877) {
    const Unicode *input = nullptr;
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 0, &out_len, nullptr);
    // With empty/null input, expect out_len to be 0 or result to handle gracefully
    EXPECT_GE(out_len, 0);
    if (result) {
        gfree(result);
    }
}

// Test NFKC normalization with a single ASCII character
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_SingleASCII_1877) {
    Unicode input[] = { 'A' };
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)'A');
    gfree(result);
}

// Test NFKC normalization with multiple ASCII characters
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_MultipleASCII_1877) {
    Unicode input[] = { 'H', 'e', 'l', 'l', 'o' };
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 5, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 5);
    EXPECT_EQ(result[0], (Unicode)'H');
    EXPECT_EQ(result[1], (Unicode)'e');
    EXPECT_EQ(result[2], (Unicode)'l');
    EXPECT_EQ(result[3], (Unicode)'l');
    EXPECT_EQ(result[4], (Unicode)'o');
    gfree(result);
}

// Test NFKC normalization with a precomposed character (e.g., U+00E9 = é)
// This should remain as is in NFKC (it's already NFC/NFKC)
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_PrecomposedChar_1877) {
    Unicode input[] = { 0x00E9 }; // é (precomposed)
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x00E9);
    gfree(result);
}

// Test NFKC normalization with decomposed character (e + combining acute accent)
// U+0065 U+0301 should compose to U+00E9
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_DecomposedToComposed_1877) {
    Unicode input[] = { 0x0065, 0x0301 }; // e + combining acute accent
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x00E9); // é
    gfree(result);
}

// Test NFKC normalization with compatibility decomposition
// U+FB01 (fi ligature) should decompose to 'f' 'i' in NFKC
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_CompatibilityDecomposition_1877) {
    Unicode input[] = { 0xFB01 }; // fi ligature
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 2);
    EXPECT_EQ(result[0], (Unicode)'f');
    EXPECT_EQ(result[1], (Unicode)'i');
    gfree(result);
}

// Test NFKC normalization with indices parameter
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_WithIndices_1877) {
    Unicode input[] = { 0x0065, 0x0301 }; // e + combining acute
    int out_len = 0;
    int *indices = nullptr;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, &indices);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x00E9);
    if (indices) {
        EXPECT_EQ(indices[0], 0);
        gfree(indices);
    }
    gfree(result);
}

// Test NFKC normalization with Hangul syllable (composed)
// U+AC00 is a Hangul syllable (가) = L_BASE + V_BASE composed
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_HangulSyllable_1877) {
    Unicode input[] = { 0xAC00 }; // 가
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_GE(out_len, 1);
    // A composed Hangul syllable should stay composed in NFKC
    EXPECT_EQ(result[0], (Unicode)0xAC00);
    gfree(result);
}

// Test NFKC normalization with Hangul Jamo (decomposed LV)
// L=0x1100, V=0x1161 should compose to U+AC00
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_HangulJamoComposition_1877) {
    Unicode input[] = { 0x1100, 0x1161 }; // ᄀ + ᅡ
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0xAC00); // 가
    gfree(result);
}

// Test NFKC normalization with Hangul Jamo LVT composition
// L=0x1100, V=0x1161, T=0x11A8 should compose to U+AC01
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_HangulJamoLVT_1877) {
    Unicode input[] = { 0x1100, 0x1161, 0x11A8 };
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 3, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0xAC01); // 각
    gfree(result);
}

// Test NFKC with fullwidth Latin letter (compatibility character)
// U+FF21 (Ａ fullwidth) should map to U+0041 (A)
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_FullwidthLatin_1877) {
    Unicode input[] = { 0xFF21 }; // Ａ
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x0041); // A
    gfree(result);
}

// Test NFKC normalization with a length of 1 and a simple character
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_LengthOne_1877) {
    Unicode input[] = { 0x0041 }; // A
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x0041);
    gfree(result);
}

// Test NFKC with superscript digit (compatibility)
// U+00B2 (²) should decompose to U+0032 ('2') in NFKC
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_SuperscriptDigit_1877) {
    Unicode input[] = { 0x00B2 }; // ²
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x0032); // '2'
    gfree(result);
}

// Test NFKC with multiple combining marks in canonical order
// U+0041 U+0308 U+0323 -> should reorder and compose
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_MultipleCombiningMarks_1877) {
    Unicode input[] = { 0x0041, 0x0308, 0x0323 }; // A + diaeresis + dot below
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 3, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_GE(out_len, 1);
    gfree(result);
}

// Test NFKC normalization preserves already-NFKC text
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_AlreadyNormalized_1877) {
    Unicode input[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F }; // Hello
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 5, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(result[i], input[i]);
    }
    gfree(result);
}

// Test NFKC with U+2126 (Ohm sign) -> should map to U+03A9 (Greek capital omega)
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_OhmSign_1877) {
    Unicode input[] = { 0x2126 }; // Ω (Ohm sign)
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x03A9); // Ω (Greek capital letter omega)
    gfree(result);
}

// Test NFKC with U+2160 (Roman numeral one) -> should map to 'I' (U+0049)
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_RomanNumeral_1877) {
    Unicode input[] = { 0x2160 }; // Ⅰ
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x0049); // I
    gfree(result);
}

// Test with indices for a compatibility decomposition
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_IndicesCompatDecomp_1877) {
    Unicode input[] = { 0x0041, 0xFB01 }; // A + fi ligature
    int out_len = 0;
    int *indices = nullptr;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, &indices);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 3); // A, f, i
    EXPECT_EQ(result[0], (Unicode)'A');
    EXPECT_EQ(result[1], (Unicode)'f');
    EXPECT_EQ(result[2], (Unicode)'i');
    if (indices) {
        EXPECT_EQ(indices[0], 0); // A maps to index 0
        EXPECT_EQ(indices[1], 1); // f maps to index 1
        EXPECT_EQ(indices[2], 1); // i maps to index 1
        gfree(indices);
    }
    gfree(result);
}

// Test with a BMP character that has no decomposition
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_NoDecomposition_1877) {
    Unicode input[] = { 0x4E2D }; // 中 (Chinese character)
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x4E2D);
    gfree(result);
}

// Test with U+00C5 (Å) which is a precomposed character - should stay as is in NFKC
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_AngstromVsARing_1877) {
    // U+212B (Angstrom sign) should normalize to U+00C5 (Latin capital A with ring above)
    Unicode input[] = { 0x212B };
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x00C5); // Å
    gfree(result);
}

// Test with a longer string containing mixed content
TEST_F(UnicodeTypeTableTest_1877, NormalizeNFKC_MixedContent_1877) {
    Unicode input[] = { 0x0041, 0x0301, 0x0020, 0xFF21 }; // A + combining acute, space, fullwidth A
    int out_len = 0;
    Unicode *result = unicodeNormalizeNFKC(input, 4, &out_len, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_GE(out_len, 3); // At least: Á, space, A
    gfree(result);
}
