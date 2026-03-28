#include <gtest/gtest.h>
#include "poppler/UnicodeTypeTable.h"
#include "poppler/CharTypes.h"

// Forward declaration of the function under test
extern Unicode *unicodeNormalizeNFKC(const Unicode *in, int len, int *out_len, int **indices, bool reverseRTL);

class UnicodeNormalizeNFKCTest_1878 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled per test
    }
};

// Test: Empty input produces empty output
TEST_F(UnicodeNormalizeNFKCTest_1878, EmptyInput_1878) {
    Unicode input[] = {};
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 0, &out_len, nullptr, false);
    EXPECT_EQ(out_len, 0);
    gfree(result);
}

// Test: Single ASCII character passes through unchanged
TEST_F(UnicodeNormalizeNFKCTest_1878, SingleASCIIChar_1878) {
    Unicode input[] = { 'A' }; // U+0041
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_GE(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)'A');
    gfree(result);
}

// Test: Multiple ASCII characters pass through unchanged
TEST_F(UnicodeNormalizeNFKCTest_1878, MultipleASCIIChars_1878) {
    Unicode input[] = { 'H', 'e', 'l', 'l', 'o' };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 5, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 5);
    EXPECT_EQ(result[0], (Unicode)'H');
    EXPECT_EQ(result[1], (Unicode)'e');
    EXPECT_EQ(result[2], (Unicode)'l');
    EXPECT_EQ(result[3], (Unicode)'l');
    EXPECT_EQ(result[4], (Unicode)'o');
    gfree(result);
}

// Test: Precomposed character (é = U+00E9) stays as-is or normalizes correctly
TEST_F(UnicodeNormalizeNFKCTest_1878, PrecomposedCharacter_1878) {
    Unicode input[] = { 0x00E9 }; // é precomposed
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_GE(out_len, 1);
    // NFKC should keep é as U+00E9
    EXPECT_EQ(result[0], (Unicode)0x00E9);
    gfree(result);
}

// Test: Decomposed e + combining acute (U+0065 U+0301) should compose to U+00E9
TEST_F(UnicodeNormalizeNFKCTest_1878, DecomposedToComposed_1878) {
    Unicode input[] = { 0x0065, 0x0301 }; // e + combining acute accent
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr, false);
    ASSERT_GE(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x00E9); // Should compose to é
    gfree(result);
}

// Test: Hangul Jamo L + V composition
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulLVComposition_1878) {
    // L = 0x1100 (ᄀ), V = 0x1161 (ᅡ) -> should compose to syllable 0xAC00 (가)
    Unicode input[] = { 0x1100, 0x1161 };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0xAC00);
    gfree(result);
}

// Test: Hangul Jamo L + V + T composition
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulLVTComposition_1878) {
    // L = 0x1100, V = 0x1161, T = 0x11A8 -> should compose to 0xAC01 (각)
    Unicode input[] = { 0x1100, 0x1161, 0x11A8 };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 3, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0xAC01);
    gfree(result);
}

// Test: Hangul LV syllable + T composition
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulSyllableLVPlusT_1878) {
    // LV syllable 0xAC00 (가) + T 0x11A8 -> 0xAC01 (각)
    Unicode input[] = { 0xAC00, 0x11A8 };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0xAC01);
    gfree(result);
}

// Test: Hangul LV syllable without trailing T
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulSyllableLVOnly_1878) {
    Unicode input[] = { 0xAC00 }; // 가 (LV syllable)
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0xAC00);
    gfree(result);
}

// Test: Hangul L without following V stays as-is
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulLWithoutV_1878) {
    Unicode input[] = { 0x1100 }; // L only
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x1100);
    gfree(result);
}

// Test: Indices array is populated correctly for simple input
TEST_F(UnicodeNormalizeNFKCTest_1878, IndicesPopulated_1878) {
    Unicode input[] = { 'A', 'B', 'C' };
    int out_len = -1;
    int *indices = nullptr;
    Unicode *result = unicodeNormalizeNFKC(input, 3, &out_len, &indices, false);
    ASSERT_EQ(out_len, 3);
    ASSERT_NE(indices, nullptr);
    // The sentinel value at indices[out_len] should be len
    EXPECT_EQ(indices[out_len], 3);
    gfree(result);
    gfree(indices);
}

// Test: Indices with nullptr does not crash
TEST_F(UnicodeNormalizeNFKCTest_1878, IndicesNullptr_1878) {
    Unicode input[] = { 'A' };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)'A');
    gfree(result);
}

// Test: NFKC compatibility decomposition - fullwidth 'Ａ' (U+FF21) -> 'A' (U+0041)
TEST_F(UnicodeNormalizeNFKCTest_1878, CompatibilityDecompositionFullwidth_1878) {
    Unicode input[] = { 0xFF21 }; // Fullwidth Latin Capital Letter A
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_GE(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x0041); // Should decompose to 'A'
    gfree(result);
}

// Test: NFKC for superscript two (U+00B2) -> '2' (U+0032)
TEST_F(UnicodeNormalizeNFKCTest_1878, SuperscriptTwo_1878) {
    Unicode input[] = { 0x00B2 }; // ²
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_GE(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x0032); // '2'
    gfree(result);
}

// Test: Multiple combining marks are reordered by canonical combining class
TEST_F(UnicodeNormalizeNFKCTest_1878, CombiningMarkReordering_1878) {
    // U+0041 (A) + U+0327 (combining cedilla, ccc=202) + U+0301 (combining acute, ccc=230)
    // After reordering: cedilla first (lower ccc), then acute
    // Then composition: A + cedilla = no standard composition; check output order
    Unicode input[] = { 0x0041, 0x0327, 0x0301 };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 3, &out_len, nullptr, false);
    ASSERT_GE(out_len, 1);
    // The output should be valid NFKC; at minimum we check it's non-empty and doesn't crash
    gfree(result);
}

// Test: Combining marks with same class are not reordered (stability)
TEST_F(UnicodeNormalizeNFKCTest_1878, CombiningMarksSameClass_1878) {
    // Two combining marks with same combining class should maintain order
    // U+0041 + U+0300 (ccc=230) + U+0301 (ccc=230)
    Unicode input[] = { 0x0041, 0x0300, 0x0301 };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 3, &out_len, nullptr, false);
    ASSERT_GE(out_len, 1);
    // A + grave should compose to À (U+00C0), then acute should remain
    EXPECT_EQ(result[0], (Unicode)0x00C0); // À
    if (out_len > 1) {
        EXPECT_EQ(result[1], (Unicode)0x0301); // combining acute remains
    }
    gfree(result);
}

// Test: Hangul LVT syllable stays as-is
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulLVTSyllablePassthrough_1878) {
    Unicode input[] = { 0xAC01 }; // 각 (LVT syllable)
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0xAC01);
    gfree(result);
}

// Test: Single length input of length 1
TEST_F(UnicodeNormalizeNFKCTest_1878, SingleCharLength1_1878) {
    Unicode input[] = { 0x0000 }; // NULL character
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x0000);
    gfree(result);
}

// Test: Indices for Hangul composition
TEST_F(UnicodeNormalizeNFKCTest_1878, IndicesForHangulComposition_1878) {
    Unicode input[] = { 0x1100, 0x1161, 0x11A8 }; // L + V + T
    int out_len = -1;
    int *indices = nullptr;
    Unicode *result = unicodeNormalizeNFKC(input, 3, &out_len, &indices, false);
    ASSERT_EQ(out_len, 1);
    ASSERT_NE(indices, nullptr);
    // The sentinel should point to the end of input
    EXPECT_EQ(indices[out_len], 3);
    gfree(result);
    gfree(indices);
}

// Test: fi ligature (U+FB01) decomposes to f + i in NFKC
TEST_F(UnicodeNormalizeNFKCTest_1878, FiLigatureDecomposition_1878) {
    Unicode input[] = { 0xFB01 }; // ﬁ ligature
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 2);
    EXPECT_EQ(result[0], (Unicode)0x0066); // 'f'
    EXPECT_EQ(result[1], (Unicode)0x0069); // 'i'
    gfree(result);
}

// Test: Mixed ASCII and combining characters
TEST_F(UnicodeNormalizeNFKCTest_1878, MixedASCIIAndCombining_1878) {
    // "e" + combining acute + " " + "a"
    Unicode input[] = { 0x0065, 0x0301, 0x0020, 0x0061 };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 4, &out_len, nullptr, false);
    ASSERT_GE(out_len, 3);
    EXPECT_EQ(result[0], (Unicode)0x00E9); // é
    EXPECT_EQ(result[1], (Unicode)0x0020); // space
    EXPECT_EQ(result[2], (Unicode)0x0061); // a
    gfree(result);
}

// Test: reverseRTL parameter does not crash
TEST_F(UnicodeNormalizeNFKCTest_1878, ReverseRTLTrue_1878) {
    Unicode input[] = { 'A', 'B' };
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr, true);
    ASSERT_EQ(out_len, 2);
    gfree(result);
}

// Test: Large input doesn't crash
TEST_F(UnicodeNormalizeNFKCTest_1878, LargeInput_1878) {
    const int size = 1000;
    Unicode input[size];
    for (int i = 0; i < size; ++i) {
        input[i] = 'A' + (i % 26);
    }
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, size, &out_len, nullptr, false);
    ASSERT_EQ(out_len, size);
    gfree(result);
}

// Test: Indices sentinel value for decomposed input
TEST_F(UnicodeNormalizeNFKCTest_1878, IndicesSentinelForDecomposed_1878) {
    Unicode input[] = { 0xFB01 }; // ﬁ -> f + i
    int out_len = -1;
    int *indices = nullptr;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, &indices, false);
    ASSERT_EQ(out_len, 2);
    ASSERT_NE(indices, nullptr);
    EXPECT_EQ(indices[out_len], 1); // sentinel = input length
    gfree(result);
    gfree(indices);
}

// Test: Hangul L followed by non-V character
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulLFollowedByNonV_1878) {
    Unicode input[] = { 0x1100, 0x0041 }; // L + 'A'
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 2);
    EXPECT_EQ(result[0], (Unicode)0x1100);
    EXPECT_EQ(result[1], (Unicode)0x0041);
    gfree(result);
}

// Test: Hangul LV syllable followed by non-T character
TEST_F(UnicodeNormalizeNFKCTest_1878, HangulLVFollowedByNonT_1878) {
    Unicode input[] = { 0xAC00, 0x0041 }; // 가 + 'A'
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 2, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 2);
    EXPECT_EQ(result[0], (Unicode)0xAC00);
    EXPECT_EQ(result[1], (Unicode)0x0041);
    gfree(result);
}

// Test: Micro sign (U+00B5) -> Greek small letter mu (U+03BC) in NFKC
TEST_F(UnicodeNormalizeNFKCTest_1878, MicroSignNormalization_1878) {
    Unicode input[] = { 0x00B5 }; // µ (micro sign)
    int out_len = -1;
    Unicode *result = unicodeNormalizeNFKC(input, 1, &out_len, nullptr, false);
    ASSERT_EQ(out_len, 1);
    EXPECT_EQ(result[0], (Unicode)0x03BC); // μ (Greek small letter mu)
    gfree(result);
}
