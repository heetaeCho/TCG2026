#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"
#include "util/utf.h"
#include "absl/strings/string_view.h"

// We need access to the static function. Since it's in an anonymous/static scope,
// we need to declare it or include the relevant header. Since StringViewToRune is
// a static function in parse.cc, we need to either make it accessible or replicate
// the declaration. We'll use a workaround by declaring it in the re2 namespace.

// Forward declare the function - since it's static in parse.cc, we need to
// include the source or use a test-specific approach. For this test, we'll
// assume we can access it through a test helper or by including the .cc file.

// Including the .cc file to access the static function
#include "re2/parse.cc"

namespace re2 {
namespace {

class StringViewToRuneTest_515 : public ::testing::Test {
 protected:
  Rune r_;
  RegexpStatus status_;
};

// Test normal ASCII character
TEST_F(StringViewToRuneTest_515, NormalAsciiChar_515) {
  absl::string_view sp("A");
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(r_, 'A');
  EXPECT_TRUE(sp.empty());
}

// Test normal ASCII character with remaining data
TEST_F(StringViewToRuneTest_515, NormalAsciiCharWithRemaining_515) {
  absl::string_view sp("AB");
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(r_, 'A');
  EXPECT_EQ(sp.size(), 1u);
  EXPECT_EQ(sp[0], 'B');
}

// Test 2-byte UTF-8 character (e.g., U+00C0 = 0xC3 0x80)
TEST_F(StringViewToRuneTest_515, TwoByteUtf8_515) {
  const char data[] = "\xC3\x80";  // U+00C0 (À)
  absl::string_view sp(data, 2);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 2);
  EXPECT_EQ(r_, 0x00C0);
  EXPECT_TRUE(sp.empty());
}

// Test 3-byte UTF-8 character (e.g., U+4E16 = 0xE4 0xB8 0x96, '世')
TEST_F(StringViewToRuneTest_515, ThreeByteUtf8_515) {
  const char data[] = "\xE4\xB8\x96";  // U+4E16 (世)
  absl::string_view sp(data, 3);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 3);
  EXPECT_EQ(r_, 0x4E16);
  EXPECT_TRUE(sp.empty());
}

// Test 4-byte UTF-8 character (e.g., U+1F600 = 0xF0 0x9F 0x98 0x80, '😀')
TEST_F(StringViewToRuneTest_515, FourByteUtf8_515) {
  const char data[] = "\xF0\x9F\x98\x80";  // U+1F600
  absl::string_view sp(data, 4);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 4);
  EXPECT_EQ(r_, 0x1F600);
  EXPECT_TRUE(sp.empty());
}

// Test invalid UTF-8 (single continuation byte)
TEST_F(StringViewToRuneTest_515, InvalidUtf8SingleContinuationByte_515) {
  const char data[] = "\x80";
  absl::string_view sp(data, 1);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test invalid UTF-8 (0xFF byte)
TEST_F(StringViewToRuneTest_515, InvalidUtf8_0xFF_515) {
  const char data[] = "\xFF";
  absl::string_view sp(data, 1);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test invalid UTF-8 (0xFE byte)
TEST_F(StringViewToRuneTest_515, InvalidUtf8_0xFE_515) {
  const char data[] = "\xFE";
  absl::string_view sp(data, 1);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test with null status pointer on bad UTF-8
TEST_F(StringViewToRuneTest_515, InvalidUtf8NullStatus_515) {
  const char data[] = "\x80";
  absl::string_view sp(data, 1);
  int result = StringViewToRune(&r_, &sp, nullptr);
  EXPECT_EQ(result, -1);
}

// Test empty string_view
TEST_F(StringViewToRuneTest_515, EmptyStringView_515) {
  absl::string_view sp("");
  int result = StringViewToRune(&r_, &sp, &status_);
  // Empty string: fullrune should return false for empty data, so status should be set
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test truncated 2-byte sequence
TEST_F(StringViewToRuneTest_515, TruncatedTwoByteSequence_515) {
  const char data[] = "\xC3";  // Start of 2-byte sequence, missing second byte
  absl::string_view sp(data, 1);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test truncated 3-byte sequence
TEST_F(StringViewToRuneTest_515, TruncatedThreeByteSequence_515) {
  const char data[] = "\xE4\xB8";  // Start of 3-byte, missing third byte
  absl::string_view sp(data, 2);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test truncated 4-byte sequence
TEST_F(StringViewToRuneTest_515, TruncatedFourByteSequence_515) {
  const char data[] = "\xF0\x9F\x98";  // Start of 4-byte, missing fourth byte
  absl::string_view sp(data, 3);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test null byte (U+0000)
TEST_F(StringViewToRuneTest_515, NullByte_515) {
  const char data[] = "\x00";
  absl::string_view sp(data, 1);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(r_, 0);
  EXPECT_TRUE(sp.empty());
}

// Test maximum valid Unicode codepoint (U+10FFFF = 0xF4 0x8F 0xBF 0xBF)
TEST_F(StringViewToRuneTest_515, MaxUnicodeCodepoint_515) {
  const char data[] = "\xF4\x8F\xBF\xBF";  // U+10FFFF
  absl::string_view sp(data, 4);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 4);
  EXPECT_EQ(r_, 0x10FFFF);
  EXPECT_TRUE(sp.empty());
}

// Test sequence consuming only first character, leaving rest
TEST_F(StringViewToRuneTest_515, MultipleCharactersConsumesOne_515) {
  absl::string_view sp("Hello");
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(r_, 'H');
  EXPECT_EQ(sp.size(), 4u);
  EXPECT_EQ(sp, "ello");
}

// Test consecutive calls
TEST_F(StringViewToRuneTest_515, ConsecutiveCalls_515) {
  absl::string_view sp("AB");
  Rune r1, r2;
  
  int result1 = StringViewToRune(&r1, &sp, &status_);
  EXPECT_EQ(result1, 1);
  EXPECT_EQ(r1, 'A');
  EXPECT_EQ(sp.size(), 1u);
  
  int result2 = StringViewToRune(&r2, &sp, &status_);
  EXPECT_EQ(result2, 1);
  EXPECT_EQ(r2, 'B');
  EXPECT_TRUE(sp.empty());
}

// Test U+007F (DEL, last single-byte character)
TEST_F(StringViewToRuneTest_515, LastSingleByteChar_515) {
  const char data[] = "\x7F";
  absl::string_view sp(data, 1);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(r_, 0x7F);
  EXPECT_TRUE(sp.empty());
}

// Test U+0080 (first 2-byte character)
TEST_F(StringViewToRuneTest_515, FirstTwoByteChar_515) {
  const char data[] = "\xC2\x80";  // U+0080
  absl::string_view sp(data, 2);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 2);
  EXPECT_EQ(r_, 0x80);
  EXPECT_TRUE(sp.empty());
}

// Test overlong encoding (2-byte encoding for ASCII)
TEST_F(StringViewToRuneTest_515, OverlongEncoding_515) {
  const char data[] = "\xC0\x80";  // Overlong encoding of U+0000
  absl::string_view sp(data, 2);
  int result = StringViewToRune(&r_, &sp, &status_);
  // Overlong encodings decode to Runeerror, which triggers the error path
  EXPECT_EQ(result, -1);
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test that string_view with UTF-8 followed by more data works correctly
TEST_F(StringViewToRuneTest_515, Utf8FollowedByMoreData_515) {
  const char data[] = "\xE4\xB8\x96\x41";  // U+4E16 followed by 'A'
  absl::string_view sp(data, 4);
  int result = StringViewToRune(&r_, &sp, &status_);
  EXPECT_EQ(result, 3);
  EXPECT_EQ(r_, 0x4E16);
  EXPECT_EQ(sp.size(), 1u);
  EXPECT_EQ(sp[0], 'A');
}

// Test value beyond Runemax - encoding that would decode to value > 0x10FFFF
TEST_F(StringViewToRuneTest_515, BeyondRunemax_515) {
  // 0xF4 0x90 0x80 0x80 would be U+110000 which is > Runemax
  const char data[] = "\xF4\x90\x80\x80";
  absl::string_view sp(data, 4);
  int result = StringViewToRune(&r_, &sp, &status_);
  // This should either return -1 (bad UTF8) or handle the > Runemax case
  // Based on the code, if chartorune decodes it and r > Runemax, n=1 and r=Runeerror
  // Then it falls into the n==1 && r==Runeerror check, returning -1
  EXPECT_EQ(result, -1);
}

}  // namespace
}  // namespace re2
