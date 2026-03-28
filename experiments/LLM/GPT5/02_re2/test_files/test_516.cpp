// File: is_valid_utf8_test_516.cc

#include <string>
#include "gtest/gtest.h"

// Bring in the function under test (it's `static` in the .cc).
// Including the .cc in the test TU is a common pattern for testing
// internal-linkage helpers safely without altering production code.
#include "re2/parse.cc"

#include "re2/regexp.h"
#include "absl/strings/string_view.h"

using re2::RegexpStatus;

class IsValidUTF8Test_516 : public ::testing::Test {};

// Normal operation: pure ASCII should be valid.
TEST_F(IsValidUTF8Test_516, AsciiIsValid_516) {
  RegexpStatus status;
  const std::string ascii = "Hello, world!";
  EXPECT_TRUE(re2::IsValidUTF8(ascii, &status));
  // Observable via public API only.
  EXPECT_TRUE(status.ok());
}

// Normal operation: empty string should be valid.
TEST_F(IsValidUTF8Test_516, EmptyIsValid_516) {
  RegexpStatus status;
  const std::string empty;
  EXPECT_TRUE(re2::IsValidUTF8(empty, &status));
  EXPECT_TRUE(status.ok());
}

// Normal operation: valid multi-byte UTF-8 (Korean) should be valid.
TEST_F(IsValidUTF8Test_516, MultibyteKoreanIsValid_516) {
  RegexpStatus status;
  const std::string korean = u8"안녕하세요";  // valid UTF-8
  EXPECT_TRUE(re2::IsValidUTF8(korean, &status));
  EXPECT_TRUE(status.ok());
}

// Boundary: passing a null status pointer with valid input should still succeed.
TEST_F(IsValidUTF8Test_516, NullStatusWithValidInput_516) {
  const std::string ascii = "OK";
  // Only verify return value; we do not touch status when it's null.
  EXPECT_TRUE(re2::IsValidUTF8(ascii, /*status=*/nullptr));
}

// Error case: clearly invalid UTF-8 should be rejected, and status should reflect failure via its public API.
TEST_F(IsValidUTF8Test_516, InvalidUtf8IsRejected_516) {
  RegexpStatus status;
  // 0xC3 0x28 is an invalid 2-byte sequence (lone lead byte followed by '(').
  const std::string invalid("\xC3\x28", 2);
  EXPECT_FALSE(re2::IsValidUTF8(invalid, &status));
  // We only assert what the public interface exposes.
  EXPECT_FALSE(status.ok());
}

// Error case: lone continuation byte should be rejected.
TEST_F(IsValidUTF8Test_516, LoneContinuationByteRejected_516) {
  RegexpStatus status;
  const std::string invalid("\x80", 1);  // invalid by itself
  EXPECT_FALSE(re2::IsValidUTF8(invalid, &status));
  EXPECT_FALSE(status.ok());
}
