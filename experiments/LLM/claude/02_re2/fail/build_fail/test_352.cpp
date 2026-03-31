#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for RegexpStatus tests
class RegexpStatusTest_352 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction - should be success/ok
TEST_F(RegexpStatusTest_352, DefaultConstructionIsOk_352) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test set_code and code getter
TEST_F(RegexpStatusTest_352, SetCodeAndGetCode_352) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_EQ(status.code(), kRegexpInternalError);
  EXPECT_FALSE(status.ok());
}

// Test set_code back to success
TEST_F(RegexpStatusTest_352, SetCodeBackToSuccess_352) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());
  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test set_error_arg and error_arg getter
TEST_F(RegexpStatusTest_352, SetErrorArgAndGetErrorArg_352) {
  RegexpStatus status;
  std::string error_str = "test error argument";
  status.set_error_arg(error_str);
  EXPECT_EQ(status.error_arg(), "test error argument");
}

// Test set_error_arg with empty string
TEST_F(RegexpStatusTest_352, SetErrorArgEmpty_352) {
  RegexpStatus status;
  status.set_error_arg("");
  EXPECT_EQ(status.error_arg(), "");
}

// Test Copy method copies code
TEST_F(RegexpStatusTest_352, CopyCopiesCode_352) {
  RegexpStatus src;
  src.set_code(kRegexpInternalError);
  
  RegexpStatus dst;
  dst.Copy(src);
  EXPECT_EQ(dst.code(), kRegexpInternalError);
}

// Test Copy method copies error_arg
TEST_F(RegexpStatusTest_352, CopyCopiesErrorArg_352) {
  RegexpStatus src;
  src.set_code(kRegexpInternalError);
  src.set_error_arg("some error");
  
  RegexpStatus dst;
  dst.Copy(src);
  EXPECT_EQ(dst.code(), kRegexpInternalError);
  EXPECT_EQ(dst.error_arg(), "some error");
}

// Test Copy from a default (ok) status
TEST_F(RegexpStatusTest_352, CopyFromDefaultStatus_352) {
  RegexpStatus src;
  
  RegexpStatus dst;
  dst.set_code(kRegexpInternalError);
  dst.set_error_arg("old error");
  
  dst.Copy(src);
  EXPECT_TRUE(dst.ok());
  EXPECT_EQ(dst.code(), kRegexpSuccess);
}

// Test CodeText for success
TEST_F(RegexpStatusTest_352, CodeTextSuccess_352) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for internal error
TEST_F(RegexpStatusTest_352, CodeTextInternalError_352) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad escape
TEST_F(RegexpStatusTest_352, CodeTextBadEscape_352) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad char class
TEST_F(RegexpStatusTest_352, CodeTextBadCharClass_352) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharClass);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad char range
TEST_F(RegexpStatusTest_352, CodeTextBadCharRange_352) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharRange);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for missing bracket
TEST_F(RegexpStatusTest_352, CodeTextMissingBracket_352) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingBracket);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for missing paren
TEST_F(RegexpStatusTest_352, CodeTextMissingParen_352) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingParen);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad repetition
TEST_F(RegexpStatusTest_352, CodeTextBadRepetition_352) {
  std::string text = RegexpStatus::CodeText(kRegexpBadRepetition);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad named capture
TEST_F(RegexpStatusTest_352, CodeTextBadNamedCapture_352) {
  std::string text = RegexpStatus::CodeText(kRegexpBadNamedCapture);
  EXPECT_FALSE(text.empty());
}

// Test Text method on default status
TEST_F(RegexpStatusTest_352, TextOnDefaultStatus_352) {
  RegexpStatus status;
  std::string text = status.Text();
  // Default is success, so text should reflect that
  EXPECT_FALSE(text.empty());
}

// Test Text method on error status with error_arg
TEST_F(RegexpStatusTest_352, TextOnErrorStatusWithArg_352) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  status.set_error_arg("\\q");
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

// Test ok() returns true for success
TEST_F(RegexpStatusTest_352, OkReturnsTrueForSuccess_352) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
}

// Test ok() returns false for various error codes
TEST_F(RegexpStatusTest_352, OkReturnsFalseForErrors_352) {
  RegexpStatus status;
  
  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());
  
  status.set_code(kRegexpBadEscape);
  EXPECT_FALSE(status.ok());
  
  status.set_code(kRegexpBadCharClass);
  EXPECT_FALSE(status.ok());
  
  status.set_code(kRegexpBadCharRange);
  EXPECT_FALSE(status.ok());
  
  status.set_code(kRegexpMissingBracket);
  EXPECT_FALSE(status.ok());
  
  status.set_code(kRegexpMissingParen);
  EXPECT_FALSE(status.ok());
  
  status.set_code(kRegexpBadRepetition);
  EXPECT_FALSE(status.ok());
  
  status.set_code(kRegexpBadNamedCapture);
  EXPECT_FALSE(status.ok());
}

// Test set_tmp
TEST_F(RegexpStatusTest_352, SetTmp_352) {
  RegexpStatus status;
  std::string tmp_str = "temporary";
  status.set_tmp(&tmp_str);
  // We can't directly observe tmp_, but we ensure it doesn't crash
}

// Test set_tmp with nullptr
TEST_F(RegexpStatusTest_352, SetTmpNull_352) {
  RegexpStatus status;
  status.set_tmp(nullptr);
  // Ensure no crash
}

// Test Copy self-like scenario with same values
TEST_F(RegexpStatusTest_352, CopyWithMultipleFields_352) {
  RegexpStatus src;
  src.set_code(kRegexpBadRepetition);
  src.set_error_arg("abc{-1}");
  
  RegexpStatus dst;
  dst.Copy(src);
  
  EXPECT_EQ(dst.code(), kRegexpBadRepetition);
  EXPECT_EQ(dst.error_arg(), "abc{-1}");
  EXPECT_FALSE(dst.ok());
}

// Test different CodeText values are different strings
TEST_F(RegexpStatusTest_352, DifferentCodeTextValues_352) {
  std::string success_text = RegexpStatus::CodeText(kRegexpSuccess);
  std::string error_text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_NE(success_text, error_text);
}

// Test Copy overwrites existing state completely
TEST_F(RegexpStatusTest_352, CopyOverwritesExistingState_352) {
  RegexpStatus src;
  src.set_code(kRegexpBadEscape);
  src.set_error_arg("new error");
  
  RegexpStatus dst;
  dst.set_code(kRegexpMissingParen);
  dst.set_error_arg("old error");
  
  dst.Copy(src);
  EXPECT_EQ(dst.code(), kRegexpBadEscape);
  EXPECT_EQ(dst.error_arg(), "new error");
}

}  // namespace re2
