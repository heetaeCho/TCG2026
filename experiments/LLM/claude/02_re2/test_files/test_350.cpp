#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test CodeText for all valid RegexpStatusCode values
TEST(RegexpStatusTest_350, CodeTextSuccess_350) {
  EXPECT_EQ("no error", RegexpStatus::CodeText(kRegexpSuccess));
}

TEST(RegexpStatusTest_350, CodeTextInternalError_350) {
  EXPECT_EQ("unexpected error", RegexpStatus::CodeText(kRegexpInternalError));
}

TEST(RegexpStatusTest_350, CodeTextBadEscape_350) {
  EXPECT_EQ("invalid escape sequence", RegexpStatus::CodeText(kRegexpBadEscape));
}

TEST(RegexpStatusTest_350, CodeTextBadCharClass_350) {
  EXPECT_EQ("invalid character class", RegexpStatus::CodeText(kRegexpBadCharClass));
}

TEST(RegexpStatusTest_350, CodeTextBadCharRange_350) {
  EXPECT_EQ("invalid character class range", RegexpStatus::CodeText(kRegexpBadCharRange));
}

TEST(RegexpStatusTest_350, CodeTextMissingBracket_350) {
  EXPECT_EQ("missing ]", RegexpStatus::CodeText(kRegexpMissingBracket));
}

TEST(RegexpStatusTest_350, CodeTextMissingParen_350) {
  EXPECT_EQ("missing )", RegexpStatus::CodeText(kRegexpMissingParen));
}

TEST(RegexpStatusTest_350, CodeTextUnexpectedParen_350) {
  EXPECT_EQ("unexpected )", RegexpStatus::CodeText(kRegexpUnexpectedParen));
}

TEST(RegexpStatusTest_350, CodeTextTrailingBackslash_350) {
  EXPECT_EQ("trailing \\", RegexpStatus::CodeText(kRegexpTrailingBackslash));
}

TEST(RegexpStatusTest_350, CodeTextRepeatArgument_350) {
  EXPECT_EQ("no argument for repetition operator", RegexpStatus::CodeText(kRegexpRepeatArgument));
}

TEST(RegexpStatusTest_350, CodeTextRepeatSize_350) {
  EXPECT_EQ("invalid repetition size", RegexpStatus::CodeText(kRegexpRepeatSize));
}

TEST(RegexpStatusTest_350, CodeTextRepeatOp_350) {
  EXPECT_EQ("bad repetition operator", RegexpStatus::CodeText(kRegexpRepeatOp));
}

TEST(RegexpStatusTest_350, CodeTextBadPerlOp_350) {
  EXPECT_EQ("invalid perl operator", RegexpStatus::CodeText(kRegexpBadPerlOp));
}

TEST(RegexpStatusTest_350, CodeTextBadUTF8_350) {
  EXPECT_EQ("invalid UTF-8", RegexpStatus::CodeText(kRegexpBadUTF8));
}

TEST(RegexpStatusTest_350, CodeTextBadNamedCapture_350) {
  EXPECT_EQ("invalid named capture group", RegexpStatus::CodeText(kRegexpBadNamedCapture));
}

// Boundary: negative code should fall back to kRegexpInternalError
TEST(RegexpStatusTest_350, CodeTextNegativeCode_350) {
  EXPECT_EQ("unexpected error", RegexpStatus::CodeText(static_cast<RegexpStatusCode>(-1)));
}

// Boundary: code beyond the valid range should fall back to kRegexpInternalError
TEST(RegexpStatusTest_350, CodeTextOutOfRangeHigh_350) {
  EXPECT_EQ("unexpected error", RegexpStatus::CodeText(static_cast<RegexpStatusCode>(15)));
}

TEST(RegexpStatusTest_350, CodeTextOutOfRangeVeryHigh_350) {
  EXPECT_EQ("unexpected error", RegexpStatus::CodeText(static_cast<RegexpStatusCode>(100)));
}

TEST(RegexpStatusTest_350, CodeTextOutOfRangeVeryNegative_350) {
  EXPECT_EQ("unexpected error", RegexpStatus::CodeText(static_cast<RegexpStatusCode>(-100)));
}

// Test default construction: code should be kRegexpSuccess, ok() should be true
TEST(RegexpStatusTest_350, DefaultConstructionIsSuccess_350) {
  RegexpStatus status;
  EXPECT_EQ(kRegexpSuccess, status.code());
  EXPECT_TRUE(status.ok());
}

// Test set_code and code()
TEST(RegexpStatusTest_350, SetCodeAndReadBack_350) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  EXPECT_EQ(kRegexpBadEscape, status.code());
  EXPECT_FALSE(status.ok());
}

// Test set_error_arg and error_arg()
TEST(RegexpStatusTest_350, SetErrorArgAndReadBack_350) {
  RegexpStatus status;
  status.set_error_arg("test_arg");
  EXPECT_EQ("test_arg", status.error_arg());
}

// Test ok() returns true only for kRegexpSuccess
TEST(RegexpStatusTest_350, OkTrueOnlyForSuccess_350) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());

  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());

  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
}

// Test Copy method
TEST(RegexpStatusTest_350, CopyStatus_350) {
  RegexpStatus src;
  src.set_code(kRegexpBadCharClass);
  src.set_error_arg("some_arg");

  RegexpStatus dst;
  dst.Copy(src);
  EXPECT_EQ(kRegexpBadCharClass, dst.code());
  EXPECT_EQ("some_arg", dst.error_arg());
  EXPECT_FALSE(dst.ok());
}

// Test Text() method includes code text
TEST(RegexpStatusTest_350, TextContainsCodeText_350) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  status.set_error_arg("\\z");
  std::string text = status.Text();
  // The text should contain the error string for bad escape
  EXPECT_NE(std::string::npos, text.find("invalid escape sequence"));
}

// Test Text() for success status
TEST(RegexpStatusTest_350, TextForSuccess_350) {
  RegexpStatus status;
  std::string text = status.Text();
  EXPECT_NE(std::string::npos, text.find("no error"));
}

// Test setting multiple error codes in sequence
TEST(RegexpStatusTest_350, SetMultipleCodes_350) {
  RegexpStatus status;
  for (int i = kRegexpSuccess; i <= kRegexpBadNamedCapture; i++) {
    RegexpStatusCode code = static_cast<RegexpStatusCode>(i);
    status.set_code(code);
    EXPECT_EQ(code, status.code());
    if (code == kRegexpSuccess) {
      EXPECT_TRUE(status.ok());
    } else {
      EXPECT_FALSE(status.ok());
    }
  }
}

// Test Copy from a success status
TEST(RegexpStatusTest_350, CopyFromSuccessStatus_350) {
  RegexpStatus src;
  // src is default success

  RegexpStatus dst;
  dst.set_code(kRegexpBadUTF8);
  dst.Copy(src);
  EXPECT_TRUE(dst.ok());
  EXPECT_EQ(kRegexpSuccess, dst.code());
}

// Test empty error_arg
TEST(RegexpStatusTest_350, EmptyErrorArg_350) {
  RegexpStatus status;
  EXPECT_EQ("", status.error_arg());
}

}  // namespace re2
