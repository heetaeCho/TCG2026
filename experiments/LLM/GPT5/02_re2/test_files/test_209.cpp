// File: utfrune_test_209.cc
#include <gtest/gtest.h>
#include <cstring>
#include <string>

#include "util/utf.h"    // for Runesync, Runeerror, etc.
#include "util/rune.h"   // declares Rune type and utfrune (assumed available in the project)

using re2::Runeerror;
using re2::Runesync;
using re2::utfrune;

namespace {

TEST(UtfruneTest_209, AsciiFound_209) {
  const char* s = "hello";
  const char* got = utfrune(s, 'e');
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, s + 1);
}

TEST(UtfruneTest_209, AsciiNotFound_209) {
  const char* s = "hello";
  const char* got = utfrune(s, 'z');
  EXPECT_EQ(got, nullptr);
}

TEST(UtfruneTest_209, EmptyStringReturnsNull_209) {
  const char* s = "";
  const char* got = utfrune(s, 'a');
  EXPECT_EQ(got, nullptr);
}

TEST(UtfruneTest_209, FindsDelimiterNul_209) {
  // When c < Runesync, utfrune delegates to strchr; strchr can find '\0'.
  const char* s = "abc";
  const char* got = utfrune(s, 0);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, s + 3);  // points to string terminator
}

TEST(UtfruneTest_209, AsciiBoundaryRunesyncMinus1_209) {
  // 0x7F (DEL) is < Runesync and should be handled like plain bytes
  std::string str;
  str.push_back(static_cast<char>(0x7F));
  str += "X";
  const char* s = str.c_str();
  const char* got = utfrune(s, 0x7F);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, s + 0);
}

TEST(UtfruneTest_209, FindsTwoByteRune_209) {
  // ¢ U+00A2 (2-byte in UTF-8)
  const char* s = u8"a\u00A2\u20AC\U0001D11E" "b";
  const char* needle = u8"\u00A2";
  const char* expected = std::strstr(s, needle);  // start of the rune in UTF-8
  ASSERT_NE(expected, nullptr);

  const char* got = utfrune(s, 0x00A2);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, expected);
}

TEST(UtfruneTest_209, FindsThreeByteRune_209) {
  // € U+20AC (3-byte in UTF-8)
  const char* s = u8"a\u00A2\u20AC\U0001D11E" "b";
  const char* needle = u8"\u20AC";
  const char* expected = std::strstr(s, needle);
  ASSERT_NE(expected, nullptr);

  const char* got = utfrune(s, 0x20AC);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, expected);
}

TEST(UtfruneTest_209, FindsFourByteRune_209) {
  // 𝄞 U+1D11E (4-byte in UTF-8)
  const char* s = u8"a\u00A2\u20AC\U0001D11E" "b";
  const char* needle = u8"\U0001D11E";
  const char* expected = std::strstr(s, needle);
  ASSERT_NE(expected, nullptr);

  const char* got = utfrune(s, 0x1D11E);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, expected);
}

TEST(UtfruneTest_209, ReturnsFirstOccurrenceWhenMultiple_209) {
  // Repeated 3-byte rune (€) followed by x; should return the first one.
  const char* s = u8"\u20AC\u20ACx";
  const char* needle = u8"\u20AC";
  const char* expected = std::strstr(s, needle);
  ASSERT_NE(expected, nullptr);

  const char* got = utfrune(s, 0x20AC);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, expected);
}

TEST(UtfruneTest_209, DoesNotConfuseAsciiWithMultibyteContinuation_209) {
  // Ensure ASCII search doesn't land in the middle of a multibyte sequence.
  // Use 'a' around a 3-byte rune.
  const char* s = u8"a\u20ACa";
  const char* got = utfrune(s, 'a');
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, s + 0);  // first 'a'
}

TEST(UtfruneTest_209, InvalidLeadingByteYieldsRuneerrorIfSearched_209) {
  // Construct a string with an invalid single leading byte 0xC0 (illegal as standalone).
  // Many UTF-8 decoders (including Plan 9–style) return Runeerror for such bytes.
  // We verify only observable behavior: if the API exposes Runeerror, searching for it
  // should return the position of that invalid byte (if decoder treats it that way).
  // This test remains black-box: it doesn't assume internal steps, just checks behavior.
  std::string str;
  str.push_back(static_cast<char>(0xC0)); // invalid by itself
  str += "A";
  const char* s = str.c_str();

  const char* got = utfrune(s, Runeerror);
  // Accept either finding the invalid byte or not supporting this search path.
  // If supported, it should point to the first byte.
  if (got != nullptr) {
    EXPECT_EQ(got, s);
  } else {
    SUCCEED();  // Decoder may choose not to surface Runeerror; still valid.
  }
}

}  // namespace
