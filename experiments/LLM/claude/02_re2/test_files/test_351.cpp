#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"

namespace re2 {

// Test default construction
TEST(RegexpStatusTest_351, DefaultConstructor_351) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test set_code and code
TEST(RegexpStatusTest_351, SetCodeAndCode_351) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_EQ(status.code(), kRegexpInternalError);
  EXPECT_FALSE(status.ok());
}

// Test set_code to success
TEST(RegexpStatusTest_351, SetCodeSuccess_351) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());
  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test set_error_arg and error_arg
TEST(RegexpStatusTest_351, SetErrorArgAndErrorArg_351) {
  RegexpStatus status;
  status.set_error_arg("test error argument");
  EXPECT_EQ(status.error_arg(), "test error argument");
}

// Test Text with no error_arg (empty)
TEST(RegexpStatusTest_351, TextWithNoErrorArg_351) {
  RegexpStatus status;
  status.set_code(kRegexpSuccess);
  std::string text = status.Text();
  // With empty error_arg, Text() should return just CodeText(code_)
  std::string code_text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_EQ(text, code_text);
}

// Test Text with error_arg set
TEST(RegexpStatusTest_351, TextWithErrorArg_351) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  status.set_error_arg("some pattern");
  std::string text = status.Text();
  std::string code_text = RegexpStatus::CodeText(kRegexpInternalError);
  std::string expected = code_text + ": " + "some pattern";
  EXPECT_EQ(text, expected);
}

// Test CodeText for success
TEST(RegexpStatusTest_351, CodeTextSuccess_351) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for internal error
TEST(RegexpStatusTest_351, CodeTextInternalError_351) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad escape
TEST(RegexpStatusTest_351, CodeTextBadEscape_351) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad char class
TEST(RegexpStatusTest_351, CodeTextBadCharClass_351) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharClass);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad char range
TEST(RegexpStatusTest_351, CodeTextBadCharRange_351) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharRange);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for missing bracket
TEST(RegexpStatusTest_351, CodeTextMissingBracket_351) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingBracket);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for missing paren
TEST(RegexpStatusTest_351, CodeTextMissingParen_351) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingParen);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad repetition
TEST(RegexpStatusTest_351, CodeTextBadRepetition_351) {
  std::string text = RegexpStatus::CodeText(kRegexpBadRepetition);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for repeat size
TEST(RegexpStatusTest_351, CodeTextRepeatSize_351) {
  std::string text = RegexpStatus::CodeText(kRegexpRepeatSize);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for repeat op
TEST(RegexpStatusTest_351, CodeTextRepeatOp_351) {
  std::string text = RegexpStatus::CodeText(kRegexpRepeatOp);
  EXPECT_FALSE(text.empty());
}

// Test ok returns true for success
TEST(RegexpStatusTest_351, OkReturnsTrueForSuccess_351) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
}

// Test ok returns false for non-success
TEST(RegexpStatusTest_351, OkReturnsFalseForNonSuccess_351) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  EXPECT_FALSE(status.ok());
}

// Test Copy
TEST(RegexpStatusTest_351, CopyStatus_351) {
  RegexpStatus src;
  src.set_code(kRegexpInternalError);
  src.set_error_arg("copy test");

  RegexpStatus dst;
  dst.Copy(src);
  EXPECT_EQ(dst.code(), kRegexpInternalError);
  EXPECT_EQ(dst.error_arg(), "copy test");
  EXPECT_EQ(dst.Text(), src.Text());
}

// Test Copy from a default status
TEST(RegexpStatusTest_351, CopyDefaultStatus_351) {
  RegexpStatus src;
  RegexpStatus dst;
  dst.set_code(kRegexpBadEscape);
  dst.set_error_arg("should be overwritten");
  dst.Copy(src);
  EXPECT_TRUE(dst.ok());
  EXPECT_EQ(dst.code(), kRegexpSuccess);
}

// Test set_tmp
TEST(RegexpStatusTest_351, SetTmp_351) {
  RegexpStatus status;
  std::string tmp_str = "temporary";
  status.set_tmp(&tmp_str);
  // We can't directly verify tmp_ but we verify it doesn't crash
  // and the object remains functional
  EXPECT_TRUE(status.ok());
}

// Test set_tmp with nullptr
TEST(RegexpStatusTest_351, SetTmpNull_351) {
  RegexpStatus status;
  status.set_tmp(nullptr);
  EXPECT_TRUE(status.ok());
}

// Test empty error_arg by default
TEST(RegexpStatusTest_351, DefaultErrorArgEmpty_351) {
  RegexpStatus status;
  EXPECT_TRUE(status.error_arg().empty());
}

// Test Text with empty error arg returns just code text
TEST(RegexpStatusTest_351, TextEmptyErrorArgEqualsCodeText_351) {
  RegexpStatus status;
  status.set_code(kRegexpBadRepetition);
  // error_arg is empty by default
  std::string text = status.Text();
  std::string code_text = RegexpStatus::CodeText(kRegexpBadRepetition);
  EXPECT_EQ(text, code_text);
}

// Test different code texts are different from each other
TEST(RegexpStatusTest_351, DifferentCodesProduceDifferentText_351) {
  std::string success_text = RegexpStatus::CodeText(kRegexpSuccess);
  std::string error_text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_NE(success_text, error_text);
}

// Test setting error_arg multiple times
TEST(RegexpStatusTest_351, SetErrorArgMultipleTimes_351) {
  RegexpStatus status;
  status.set_error_arg("first");
  EXPECT_EQ(status.error_arg(), "first");
  status.set_error_arg("second");
  EXPECT_EQ(status.error_arg(), "second");
}

// Test setting code multiple times
TEST(RegexpStatusTest_351, SetCodeMultipleTimes_351) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  EXPECT_EQ(status.code(), kRegexpBadEscape);
  status.set_code(kRegexpMissingParen);
  EXPECT_EQ(status.code(), kRegexpMissingParen);
  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
}

}  // namespace re2
