// File: utflen_test.cc
#include <gtest/gtest.h>

// Only rely on the public interface / signatures.
namespace re2 {
  // Forward declaration of the function under test.
  int utflen(const char* s);
}

namespace {

// Basic: empty string -> 0
TEST(UtflenTest_208, EmptyStringReturnsZero_208) {
  const char* s = "";
  EXPECT_EQ(0, re2::utflen(s));
}

// ASCII-only: counts bytes as runes
TEST(UtflenTest_208, CountsAsciiOnly_208) {
  const char* s = "abcXYZ";
  EXPECT_EQ(6, re2::utflen(s));
}

// Two-byte UTF-8 rune (U+00E9 'é' -> C3 A9)
TEST(UtflenTest_208, CountsTwoByteRune_208) {
  const char* s = "\xC3\xA9";  // "é"
  EXPECT_EQ(1, re2::utflen(s));
}

// Three-byte UTF-8 rune (U+20AC '€' -> E2 82 AC)
TEST(UtflenTest_208, CountsThreeByteRune_208) {
  const char* s = "\xE2\x82\xAC";  // "€"
  EXPECT_EQ(1, re2::utflen(s));
}

// Four-byte UTF-8 rune (U+1F600 '😀' -> F0 9F 98 80)
TEST(UtflenTest_208, CountsFourByteRune_208) {
  const char* s = "\xF0\x9F\x98\x80";  // "😀"
  EXPECT_EQ(1, re2::utflen(s));
}

// Mixed ASCII + multi-byte runes
// "a" + "€" + "b" + "é" + "😀" -> total 5 runes
TEST(UtflenTest_208, MixedAsciiAndMultibyte_208) {
  const char* s = "a"
                  "\xE2\x82\xAC"  // €
                  "b"
                  "\xC3\xA9"      // é
                  "\xF0\x9F\x98\x80"; // 😀
  EXPECT_EQ(5, re2::utflen(s));
}

// Boundary: stops at the first null terminator even if buffer has more data
TEST(UtflenTest_208, StopsAtNullTerminator_208) {
  const char buf[] = {
      'a', 'b', '\0',
      // Additional bytes that must be ignored by utflen:
      static_cast<char>(0xE2), static_cast<char>(0x82), static_cast<char>(0xAC),
      'x'
  };
  EXPECT_EQ(2, re2::utflen(buf));
}

// Exceptional/invalid sequence case (observable through return value):
// Standalone continuation byte 0x80, followed by NUL.
// Many UTF-8 decoders surface this as a single replacement rune and advance by 1,
// which should make utflen count it as one rune.
TEST(UtflenTest_208, InvalidUtf8ByteCountedAsOneRune_208) {
  const char* s = "\x80";  // Invalid as a standalone byte; string ends right after.
  EXPECT_EQ(1, re2::utflen(s));
}

// Another incomplete leading byte (e.g., 0xC2) should still be counted as one rune
// by external decoder semantics, observable as length 1 here.
TEST(UtflenTest_208, IncompleteLeadingByteCountsAsOneRune_208) {
  const char* s = "\xC2";
  EXPECT_EQ(1, re2::utflen(s));
}

}  // namespace
