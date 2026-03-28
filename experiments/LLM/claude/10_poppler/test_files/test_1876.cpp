#include <gtest/gtest.h>

// Include the implementation to access the static combine function
// We need the Unicode type definition
#include "poppler/CharTypes.h"

// Forward declare or include necessary headers
#include "poppler/UnicodeTypeTable.h"

// Since combine is static, we need to include the .cc file to test it directly
// or use the public normalizeNFKC function. We'll test via the public API.
// Looking at the header, the public function is unicodeNormalizeNFKC.

// For testing the static combine function, include the source
namespace {
#include "poppler/UnicodeTypeTable.cc"
}

class CombineTest_1876 : public ::testing::Test {
protected:
    Unicode out;
};

// Test basic Latin composition: A + grave accent = À
TEST_F(CombineTest_1876, CombineAWithGrave_1876) {
    Unicode out = 0;
    bool result = combine(0x0041, 0x0300, &out); // A + combining grave = À
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00C0); // À
}

// Test basic Latin composition: A + acute accent = Á
TEST_F(CombineTest_1876, CombineAWithAcute_1876) {
    Unicode out = 0;
    bool result = combine(0x0041, 0x0301, &out); // A + combining acute = Á
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00C1); // Á
}

// Test basic Latin composition: A + circumflex = Â
TEST_F(CombineTest_1876, CombineAWithCircumflex_1876) {
    Unicode out = 0;
    bool result = combine(0x0041, 0x0302, &out); // A + combining circumflex = Â
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00C2);
}

// Test basic Latin composition: A + tilde = Ã
TEST_F(CombineTest_1876, CombineAWithTilde_1876) {
    Unicode out = 0;
    bool result = combine(0x0041, 0x0303, &out); // A + combining tilde = Ã
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00C3);
}

// Test basic Latin composition: A + diaeresis = Ä
TEST_F(CombineTest_1876, CombineAWithDiaeresis_1876) {
    Unicode out = 0;
    bool result = combine(0x0041, 0x0308, &out); // A + combining diaeresis = Ä
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00C4);
}

// Test basic Latin composition: A + ring above = Å
TEST_F(CombineTest_1876, CombineAWithRingAbove_1876) {
    Unicode out = 0;
    bool result = combine(0x0041, 0x030A, &out); // A + combining ring above = Å
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00C5);
}

// Test lowercase: a + grave = à
TEST_F(CombineTest_1876, CombineLowercaseAWithGrave_1876) {
    Unicode out = 0;
    bool result = combine(0x0061, 0x0300, &out); // a + combining grave = à
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00E0);
}

// Test lowercase: a + acute = á
TEST_F(CombineTest_1876, CombineLowercaseAWithAcute_1876) {
    Unicode out = 0;
    bool result = combine(0x0061, 0x0301, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00E1);
}

// Test E + grave = È
TEST_F(CombineTest_1876, CombineEWithGrave_1876) {
    Unicode out = 0;
    bool result = combine(0x0045, 0x0300, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00C8);
}

// Test O + acute = Ó
TEST_F(CombineTest_1876, CombineOWithAcute_1876) {
    Unicode out = 0;
    bool result = combine(0x004F, 0x0301, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00D3);
}

// Test N + tilde = Ñ
TEST_F(CombineTest_1876, CombineNWithTilde_1876) {
    Unicode out = 0;
    bool result = combine(0x004E, 0x0303, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00D1);
}

// Test n + tilde = ñ
TEST_F(CombineTest_1876, CombineLowercaseNWithTilde_1876) {
    Unicode out = 0;
    bool result = combine(0x006E, 0x0303, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00F1);
}

// Test U + diaeresis = Ü
TEST_F(CombineTest_1876, CombineUWithDiaeresis_1876) {
    Unicode out = 0;
    bool result = combine(0x0055, 0x0308, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, 0x00DC);
}

// Test characters that cannot combine
TEST_F(CombineTest_1876, CombineFailsForNonComposable_1876) {
    Unicode out = 0;
    bool result = combine(0x0042, 0x0300, &out); // B + grave - no composition exists
    EXPECT_FALSE(result);
}

// Test with zero base
TEST_F(CombineTest_1876, CombineFailsForZeroBase_1876) {
    Unicode out = 0;
    bool result = combine(0x0000, 0x0300, &out);
    EXPECT_FALSE(result);
}

// Test with zero add
TEST_F(CombineTest_1876, CombineFailsForZeroAdd_1876) {
    Unicode out = 0;
    bool result = combine(0x0041, 0x0000, &out);
    EXPECT_FALSE(result);
}

// Test Hangul L + V composition
TEST_F(CombineTest_1876, HangulLVComposition_1876) {
    // Hangul L base = 0x1100, V base = 0x1161
    // LV syllable = S_BASE + (L - L_BASE) * V_COUNT * T_COUNT + (V - V_BASE) * T_COUNT
    // For L=0x1100, V=0x1161: S = 0xAC00 + 0 * 21 * 28 + 0 * 28 = 0xAC00
    Unicode out = 0;
    bool result = combine(0x1100, 0x1161, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0xAC00));
}

// Test Hangul LV + T composition
TEST_F(CombineTest_1876, HangulLVTComposition_1876) {
    // LV = 0xAC00, T = 0x11A8 (first jongseong)
    // Result = LV + (T - T_BASE) = 0xAC00 + 1 = 0xAC01
    Unicode out = 0;
    bool result = combine(0xAC00, 0x11A8, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0xAC01));
}

// Test Hangul LV + T where T is last valid
TEST_F(CombineTest_1876, HangulLVTCompositionLastT_1876) {
    // T_BASE = 0x11A7, T_COUNT = 28, so last T = 0x11A7 + 27 = 0x11C2
    Unicode out = 0;
    bool result = combine(0xAC00, 0x11C2, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0xAC00 + 27));
}

// Test Hangul: already composed LVT should not combine with T
TEST_F(CombineTest_1876, HangulAlreadyLVTCannotCombine_1876) {
    Unicode out = 0;
    // 0xAC01 is LVT (already has T), should not combine with another T
    bool result = combine(0xAC01, 0x11A8, &out);
    EXPECT_FALSE(result);
}

// Test second Hangul L+V pair
TEST_F(CombineTest_1876, HangulSecondLV_1876) {
    // L=0x1101, V=0x1161
    Unicode out = 0;
    bool result = combine(0x1101, 0x1161, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0xAC00 + 1 * 21 * 28));
}

// Test compose_first_single path: specific known pairs
// F + dot above = Ḟ (U+1E1E) — via compose_first_single
TEST_F(CombineTest_1876, ComposeFirstSingleFDotAbove_1876) {
    Unicode out = 0;
    bool result = combine(0x0046, 0x0307, &out); // F + combining dot above
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0x1E1E));
}

// Test compose_second_single: Arabic Alef + Hamza above
TEST_F(CombineTest_1876, ComposeSecondSingleArabic_1876) {
    Unicode out = 0;
    // Alef (0x0627) + Hamza above (0x0654) = Alef with Hamza above (0x0623)
    bool result = combine(0x0627, 0x0654, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0x0623));
}

// Test compose_second_single: Arabic Alef + Madda
TEST_F(CombineTest_1876, ComposeSecondSingleArabicMadda_1876) {
    Unicode out = 0;
    // Alef (0x0627) + Madda above (0x0653) = Alef with Madda (0x0622)
    bool result = combine(0x0627, 0x0653, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0x0622));
}

// Test that two random ASCII characters don't combine
TEST_F(CombineTest_1876, RandomASCIIDontCombine_1876) {
    Unicode out = 0;
    bool result = combine('X', 'Y', &out);
    EXPECT_FALSE(result);
}

// Test very large Unicode values that are out of range
TEST_F(CombineTest_1876, OutOfRangeCharactersDontCombine_1876) {
    Unicode out = 0;
    bool result = combine(0x10FFFF, 0x10FFFF, &out);
    EXPECT_FALSE(result);
}

// Test C + cedilla = Ç
TEST_F(CombineTest_1876, CombineCWithCedilla_1876) {
    Unicode out = 0;
    bool result = combine(0x0043, 0x0327, &out); // C + combining cedilla
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0x00C7));
}

// Test c + cedilla = ç
TEST_F(CombineTest_1876, CombineLowercaseCWithCedilla_1876) {
    Unicode out = 0;
    bool result = combine(0x0063, 0x0327, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0x00E7));
}

// Test Y + acute = Ý
TEST_F(CombineTest_1876, CombineYWithAcute_1876) {
    Unicode out = 0;
    bool result = combine(0x0059, 0x0301, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0x00DD));
}

// Test combining with stroke (not equals via stroke)
TEST_F(CombineTest_1876, CombineEqualsWithStroke_1876) {
    Unicode out = 0;
    // = (0x003D) + combining long stroke overlay (0x0338) = ≠ (0x2260)... 
    // Actually from the table: 824 = 0x0338, and the pair gives 8800 = 0x2260
    bool result = combine(0x003D, 0x0338, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(0x2260));
}

// Test combining less-than with stroke
TEST_F(CombineTest_1876, CombineLessThanWithStroke_1876) {
    Unicode out = 0;
    // < (0x003C) + 0x0338 = ≮ (0x226E = 8814)
    bool result = combine(0x003C, 0x0338, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(8814));
}

// Test combining greater-than with stroke
TEST_F(CombineTest_1876, CombineGreaterThanWithStroke_1876) {
    Unicode out = 0;
    // > (0x003E) + 0x0338 = ≯ (0x226F = 8815)
    bool result = combine(0x003E, 0x0338, &out);
    EXPECT_TRUE(result);
    EXPECT_EQ(out, static_cast<Unicode>(8815));
}

// Boundary: last Hangul L with first V
TEST_F(CombineTest_1876, HangulLastLFirstV_1876) {
    // Last L = L_BASE + L_COUNT - 1 = 0x1100 + 18 = 0x1112
    Unicode out = 0;
    bool result = combine(0x1112, 0x1161, &out);
    EXPECT_TRUE(result);
    Unicode expected = 0xAC00 + 18 * 21 * 28;
    EXPECT_EQ(out, expected);
}

// Boundary: first L with last V
TEST_F(CombineTest_1876, HangulFirstLLastV_1876) {
    // Last V = V_BASE + V_COUNT - 1 = 0x1161 + 20 = 0x1175
    Unicode out = 0;
    bool result = combine(0x1100, 0x1175, &out);
    EXPECT_TRUE(result);
    Unicode expected = 0xAC00 + 0 * 21 * 28 + 20 * 28;
    EXPECT_EQ(out, expected);
}

// Test that base and add both being 0 fails
TEST_F(CombineTest_1876, BothZeroFails_1876) {
    Unicode out = 0;
    bool result = combine(0, 0, &out);
    EXPECT_FALSE(result);
}
