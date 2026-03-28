// File: pcre_terminate_number_test.cc

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>

// Include the implementation file so we can test the internal (static) function.
// This compiles the function into this translation unit, keeping it black-box from behavior POV.
#include "TestProjects/re2/util/pcre.cc"

namespace {

using re2::TerminateNumber;
using re2::kMaxNumberLength;

// Helper to make a long string consisting of 'X' followed by a marker char.
std::string MakePadded(size_t n, char marker_after_n) {
  std::string s(n, 'X');
  s.push_back(marker_after_n);
  s.push_back('Y');  // extra padding to keep str[n] valid and not at '\0'
  return s;
}

// Normal operation: next char is a digit; n within limit -> copies first n chars into buf and returns buf.
TEST(TerminateNumberTest_202, NextCharIsDigit_WithinLimit_ReturnsBufAndCopies_202) {
  std::string s = MakePadded(5, '7');  // str[5] is a digit
  char buf[64] = {0};

  const char* ret = TerminateNumber(buf, s.c_str(), 5);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "XXXXX");  // first 5 chars copied
}

// Normal operation: next char is lowercase hex [a-f]; n within limit -> returns buf and copies.
TEST(TerminateNumberTest_202, NextCharIsHexLower_WithinLimit_ReturnsBufAndCopies_202) {
  std::string s = MakePadded(3, 'a');  // hex lower
  char buf[16] = {0};

  const char* ret = TerminateNumber(buf, s.c_str(), 3);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "XXX");
}

// Normal operation: next char is uppercase hex [A-F]; n within limit -> returns buf and copies.
TEST(TerminateNumberTest_202, NextCharIsHexUpper_WithinLimit_ReturnsBufAndCopies_202) {
  std::string s = MakePadded(2, 'F');  // hex upper
  char buf[16] = {0};

  const char* ret = TerminateNumber(buf, s.c_str(), 2);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "XX");
}

// Boundary: n == 0 and next char is digit/hex -> function should set buf to empty string and return buf.
TEST(TerminateNumberTest_202, NIsZero_NextIsDigit_ReturnsEmptyStringInBuf_202) {
  std::string s = MakePadded(0, '9');  // str[0] is a digit
  char buf[8] = {'\0'};  // pre-zeroed for clarity

  const char* ret = TerminateNumber(buf, s.c_str(), 0);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "");  // copied 0 chars -> empty string
}

// Boundary: n > kMaxNumberLength and next char is digit/hex -> returns empty string literal.
TEST(TerminateNumberTest_202, ExceedsMaxLengthWithDigitAfterN_ReturnsEmptyString_202) {
  const size_t n = static_cast<size_t>(kMaxNumberLength) + 1;
  std::string s = MakePadded(n, '3');  // ensure str[n] is a digit
  char buf[128];

  const char* ret = TerminateNumber(buf, s.c_str(), n);

  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret, "");  // returns empty string indicator
}

// Exceptional/early exit observable: n > 0 and first char is whitespace -> returns empty string.
TEST(TerminateNumberTest_202, LeadingWhitespaceWithPositiveN_ReturnsEmptyString_202) {
  const char* str = " 123";
  char buf[16];

  const char* ret = TerminateNumber(buf, str, 1);  // n>0 and *str is space

  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret, "");
}

// Observable branch: next char after n is NOT digit nor hex -> returns original str pointer.
TEST(TerminateNumberTest_202, NextCharIsNonDigitNonHex_ReturnsOriginalPointer_202) {
  std::string s = MakePadded(4, 'Z');  // 'Z' is not 0-9 or A-F/a-f
  char buf[32];

  const char* ret = TerminateNumber(buf, s.c_str(), 4);

  EXPECT_EQ(ret, s.c_str());  // returns the same pointer
}

// Edge check: n == 0 and first char is whitespace -> not caught by whitespace check (requires n>0),
// and next char is not digit/hex, so it should return the original str pointer.
TEST(TerminateNumberTest_202, NIsZero_LeadingWhitespace_ReturnsOriginalPointer_202) {
  const char* str = " ";  // str[0] is space; not digit/hex
  char buf[8];

  const char* ret = TerminateNumber(buf, str, 0);

  EXPECT_EQ(ret, str);
}

}  // namespace
