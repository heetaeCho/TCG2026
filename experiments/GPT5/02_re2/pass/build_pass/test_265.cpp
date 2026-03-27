// File: re2_rewrite_test_265.cc
#include <gtest/gtest.h>
#include "re2/re2.h"
#include "absl/strings/string_view.h"

using re2::RE2;

class RewriteTest_265 : public ::testing::Test {
protected:
  // We don't rely on any internal state; just need a valid RE2 instance.
  // Pattern choice is irrelevant for Rewrite's observable behavior here.
  RE2 re_{".*"};
};

// Normal operation: literal text is copied as-is.
TEST_F(RewriteTest_265, LiteralOnly_ReturnsTrueAndCopies_265) {
  std::string out;
  const absl::string_view vec[] = {};
  const bool ok = re_.Rewrite(&out, "hello world", vec, /*veclen=*/0);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "hello world");
}

// Normal operation: single-digit group substitutions within range are appended.
TEST_F(RewriteTest_265, DigitSubstitution_ValidIndices_265) {
  std::string out;
  const absl::string_view vec[] = {"X", "YZ"};
  // Pattern uses \0 and \1 with literals around them.
  const bool ok = re_.Rewrite(&out, "a\\0-b\\1c", vec, /*veclen=*/2);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "aX-bYZc");
}

// Boundary/normal: empty snippets are skipped (no characters appended).
TEST_F(RewriteTest_265, DigitSubstitution_EmptySnip_SkipsAppend_265) {
  std::string out;
  const absl::string_view vec[] = {"", "Q"};
  const bool ok = re_.Rewrite(&out, "L\\0M\\1N", vec, /*veclen=*/2);

  EXPECT_TRUE(ok);
  // \0 contributes nothing; \1 contributes "Q".
  EXPECT_EQ(out, "LMQN");
}

// Normal operation: escaped backslash becomes a single backslash.
TEST_F(RewriteTest_265, EscapedBackslash_ProducesBackslash_265) {
  std::string out;
  const absl::string_view vec[] = {};
  const bool ok = re_.Rewrite(&out, "path\\\\to\\\\file", vec, /*veclen=*/0);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "path\\to\\file");
}

// Error/exceptional: digit reference out of range -> returns false.
// Output contains any literals processed before the failure.
TEST_F(RewriteTest_265, InvalidSubstitution_IndexOutOfRange_ReturnsFalse_265) {
  std::string out;
  const absl::string_view vec[] = {"A"};  // veclen = 1 (only \0 valid)
  const bool ok = re_.Rewrite(&out, "pre\\2post", vec, /*veclen=*/1);

  EXPECT_FALSE(ok);
  // "pre" processed before encountering invalid \2
  EXPECT_EQ(out, "pre");
}

// Error/exceptional: invalid escape (non-digit & non-backslash) -> returns false.
TEST_F(RewriteTest_265, InvalidEscapeChar_ReturnsFalse_265) {
  std::string out;
  const absl::string_view vec[] = {"A", "B"};
  const bool ok = re_.Rewrite(&out, "x\\ay", vec, /*veclen=*/2);

  EXPECT_FALSE(ok);
  // 'x' is appended before hitting invalid "\a"
  EXPECT_EQ(out, "x");
}

// Boundary: rewrite ends with a single backslash -> invalid, returns false.
TEST_F(RewriteTest_265, TrailingBackslash_ReturnsFalse_265) {
  std::string out;
  const absl::string_view vec[] = {"Z"};
  const bool ok = re_.Rewrite(&out, "end\\", vec, /*veclen=*/1);

  EXPECT_FALSE(ok);
  // "end" is appended before failing on trailing backslash
  EXPECT_EQ(out, "end");
}

// Boundary: veclen == 0 but pattern references \0 -> invalid.
TEST_F(RewriteTest_265, NoGroups_VeclenZero_IndexZeroRef_ReturnsFalse_265) {
  std::string out;
  const absl::string_view vec[] = {};  // veclen = 0
  const bool ok = re_.Rewrite(&out, "a\\0b", vec, /*veclen=*/0);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "a");
}

// Mixed content: multiple substitutions and escapes combined.
TEST_F(RewriteTest_265, MixedLiteralsSubsAndEscapes_265) {
  std::string out;
  const absl::string_view vec[] = {"0", "ONE"};
  const bool ok = re_.Rewrite(&out, "A\\1-B\\0C\\\\D\\1", vec, /*veclen=*/2);

  EXPECT_TRUE(ok);
  // \1 -> "ONE", \0 -> "0", "\\\\" -> "\", final \1 -> "ONE"
  EXPECT_EQ(out, "AONE-B0C\\DONE");
}
