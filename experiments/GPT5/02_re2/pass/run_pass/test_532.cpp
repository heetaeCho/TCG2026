// File: ./TestProjects/re2/re2/tests/is_valid_capture_name_test.cc

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// Include the .cc directly so the internal-linkage function is visible
// in this translation unit without modifying production code.
#include "re2/parse.cc"

namespace re2 {

TEST(IsValidCaptureName_532, EmptyStringIsInvalid_532) {
  EXPECT_FALSE(IsValidCaptureName(absl::string_view("")));
}

TEST(IsValidCaptureName_532, ValidAsciiLetters_532) {
  EXPECT_TRUE(IsValidCaptureName("abc"));
  EXPECT_TRUE(IsValidCaptureName("AbcDEF"));
}

TEST(IsValidCaptureName_532, UnderscoreAndDigitsAllowed_532) {
  EXPECT_TRUE(IsValidCaptureName("_"));
  EXPECT_TRUE(IsValidCaptureName("__"));
  EXPECT_TRUE(IsValidCaptureName("name_1"));
  EXPECT_TRUE(IsValidCaptureName("1"));          // Digits permitted by Nd
  EXPECT_TRUE(IsValidCaptureName("1_2_3"));
}

TEST(IsValidCaptureName_532, HyphenIsRejected_532) {
  EXPECT_FALSE(IsValidCaptureName("-"));
  EXPECT_FALSE(IsValidCaptureName("name-1"));
}

TEST(IsValidCaptureName_532, SpaceIsRejected_532) {
  EXPECT_FALSE(IsValidCaptureName(" "));
  EXPECT_FALSE(IsValidCaptureName("hello world"));
}

TEST(IsValidCaptureName_532, DotIsRejected_532) {
  EXPECT_FALSE(IsValidCaptureName("."));
  EXPECT_FALSE(IsValidCaptureName("abc.def"));
}

TEST(IsValidCaptureName_532, UnicodeLettersAreAccepted_532) {
  // Greek capital Delta (Lu) followed by ASCII letters
  EXPECT_TRUE(IsValidCaptureName("Δelta"));          // U+0394
  // CJK characters (Lo) and ASCII digits (Nd)
  EXPECT_TRUE(IsValidCaptureName(u8"名字123"));
}

TEST(IsValidCaptureName_532, LetterNumberNlIsAccepted_532) {
  // Roman numerals are in Nl (Letter Number)
  EXPECT_TRUE(IsValidCaptureName(u8"ⅠⅡ"));          // U+2160 U+2161
}

TEST(IsValidCaptureName_532, CombiningMarksAreAccepted_532) {
  // Combining acute accent (Mn)
  EXPECT_TRUE(IsValidCaptureName(u8"\u0301"));
  // Base letter + combining mark
  EXPECT_TRUE(IsValidCaptureName(u8"a\u0301"));
}

TEST(IsValidCaptureName_532, EmojiIsRejected_532) {
  // GRINNING FACE is So (Symbol, other) → not in the allowed sets
  EXPECT_FALSE(IsValidCaptureName(u8"😀"));
  EXPECT_FALSE(IsValidCaptureName(u8"😀name"));
}

TEST(IsValidCaptureName_532, InvalidUtf8YieldsFalse_532) {
  // Invalid UTF-8 byte sequence: 0xC3 0x28
  const std::string invalid("\xC3\x28", 2);
  EXPECT_FALSE(IsValidCaptureName(absl::string_view(invalid)));
}

}  // namespace re2
