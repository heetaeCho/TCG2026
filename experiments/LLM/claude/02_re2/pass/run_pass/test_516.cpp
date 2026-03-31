#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

// We test IsValidUTF8 indirectly through the public interface since it's a static function
// in the re2 namespace. The most observable way to test UTF-8 validation is through
// RE2's pattern compilation, which uses IsValidUTF8 internally.

namespace re2 {

// We can test IsValidUTF8 behavior through Regexp::Parse which calls it internally
// when the pattern is not valid UTF-8.

class IsValidUTF8Test_516 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a valid ASCII string compiles successfully
TEST_F(IsValidUTF8Test_516, ValidASCIIString_516) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

// Test that valid UTF-8 multi-byte sequences compile successfully
TEST_F(IsValidUTF8Test_516, ValidUTF8MultiByte_516) {
  // 2-byte UTF-8: é (U+00E9) = 0xC3 0xA9
  RE2 re("h\xC3\xA9llo");
  EXPECT_TRUE(re.ok());
}

// Test that valid 3-byte UTF-8 sequences compile successfully
TEST_F(IsValidUTF8Test_516, ValidUTF8ThreeByte_516) {
  // 3-byte UTF-8: ∀ (U+2200) = 0xE2 0x88 0x80
  RE2 re("\xE2\x88\x80");
  EXPECT_TRUE(re.ok());
}

// Test that valid 4-byte UTF-8 sequences compile successfully
TEST_F(IsValidUTF8Test_516, ValidUTF8FourByte_516) {
  // 4-byte UTF-8: 𝄞 (U+1D11E) = 0xF0 0x9D 0x84 0x9E
  RE2 re("\xF0\x9D\x84\x9E");
  EXPECT_TRUE(re.ok());
}

// Test that an empty string is valid UTF-8
TEST_F(IsValidUTF8Test_516, EmptyString_516) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
}

// Test that an invalid UTF-8 continuation byte alone fails
TEST_F(IsValidUTF8Test_516, InvalidUTF8LoneContinuationByte_516) {
  // 0x80 is a continuation byte, not valid as a start byte
  // RE2 in Latin1 mode would accept it, but in UTF-8 mode it should fail
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  RE2 re("\x80", opts);
  EXPECT_FALSE(re.ok());
}

// Test that an incomplete 2-byte UTF-8 sequence fails
TEST_F(IsValidUTF8Test_516, InvalidUTF8Incomplete2Byte_516) {
  // 0xC3 expects one more continuation byte
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  RE2 re("\xC3", opts);
  EXPECT_FALSE(re.ok());
}

// Test that an incomplete 3-byte UTF-8 sequence fails
TEST_F(IsValidUTF8Test_516, InvalidUTF8Incomplete3Byte_516) {
  // 0xE2 expects two more continuation bytes, but we only provide one
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  RE2 re("\xE2\x88", opts);
  EXPECT_FALSE(re.ok());
}

// Test that an overlong encoding is rejected
TEST_F(IsValidUTF8Test_516, InvalidUTF8OverlongEncoding_516) {
  // Overlong encoding of '/' (U+002F): 0xC0 0xAF
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  RE2 re("\xC0\xAF", opts);
  EXPECT_FALSE(re.ok());
}

// Test that 0xFE byte (invalid in UTF-8) is rejected
TEST_F(IsValidUTF8Test_516, InvalidUTF8ByteFE_516) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  RE2 re("\xFE", opts);
  EXPECT_FALSE(re.ok());
}

// Test that 0xFF byte (invalid in UTF-8) is rejected
TEST_F(IsValidUTF8Test_516, InvalidUTF8ByteFF_516) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  RE2 re("\xFF", opts);
  EXPECT_FALSE(re.ok());
}

// Test that valid UTF-8 with mixed ASCII and multibyte works
TEST_F(IsValidUTF8Test_516, ValidMixedASCIIAndMultibyte_516) {
  RE2 re("abc\xC3\xA9\xE2\x88\x80xyz");
  EXPECT_TRUE(re.ok());
}

// Test that Latin1 mode accepts invalid UTF-8
TEST_F(IsValidUTF8Test_516, Latin1ModeAcceptsInvalidUTF8_516) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("\x80\xFE\xFF", opts);
  EXPECT_TRUE(re.ok());
}

// Test RegexpStatus default construction
TEST_F(IsValidUTF8Test_516, RegexpStatusDefaultConstruction_516) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test RegexpStatus set_code and code
TEST_F(IsValidUTF8Test_516, RegexpStatusSetAndGetCode_516) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_EQ(status.code(), kRegexpInternalError);
  EXPECT_FALSE(status.ok());
}

// Test RegexpStatus set_error_arg and error_arg
TEST_F(IsValidUTF8Test_516, RegexpStatusSetAndGetErrorArg_516) {
  RegexpStatus status;
  status.set_error_arg("test error");
  EXPECT_EQ(status.error_arg(), "test error");
}

// Test RegexpStatus Copy
TEST_F(IsValidUTF8Test_516, RegexpStatusCopy_516) {
  RegexpStatus status1;
  status1.set_code(kRegexpInternalError);
  status1.set_error_arg("error");
  
  RegexpStatus status2;
  status2.Copy(status1);
  EXPECT_EQ(status2.code(), kRegexpInternalError);
}

// Test RegexpStatus CodeText
TEST_F(IsValidUTF8Test_516, RegexpStatusCodeText_516) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test that invalid UTF-8 embedded in a longer pattern is caught
TEST_F(IsValidUTF8Test_516, InvalidUTF8InMiddleOfPattern_516) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  // Valid ASCII, then invalid byte, then valid ASCII
  RE2 re("abc\x80xyz", opts);
  EXPECT_FALSE(re.ok());
}

// Test surrogate half (U+D800) encoded in UTF-8 is rejected
TEST_F(IsValidUTF8Test_516, InvalidUTF8SurrogateHalf_516) {
  // U+D800 = 0xED 0xA0 0x80 (surrogate, invalid in UTF-8)
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  opts.set_log_errors(false);
  RE2 re("\xED\xA0\x80", opts);
  EXPECT_FALSE(re.ok());
}

}  // namespace re2
