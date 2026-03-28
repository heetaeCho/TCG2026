#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for RegexpStatus tests
class RegexpStatusTest_137 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test default construction - should be success/ok
TEST_F(RegexpStatusTest_137, DefaultConstructionIsOk_137) {
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test set_code and code getter
TEST_F(RegexpStatusTest_137, SetCodeAndGetCode_137) {
  status_.set_code(kRegexpInternalError);
  EXPECT_EQ(status_.code(), kRegexpInternalError);
  EXPECT_FALSE(status_.ok());
}

// Test set_code back to success
TEST_F(RegexpStatusTest_137, SetCodeBackToSuccess_137) {
  status_.set_code(kRegexpInternalError);
  EXPECT_FALSE(status_.ok());
  status_.set_code(kRegexpSuccess);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test set_error_arg and error_arg getter
TEST_F(RegexpStatusTest_137, SetErrorArgAndGetErrorArg_137) {
  std::string arg = "test_error";
  status_.set_error_arg(arg);
  EXPECT_EQ(status_.error_arg(), "test_error");
}

// Test set_error_arg with empty string
TEST_F(RegexpStatusTest_137, SetErrorArgEmpty_137) {
  status_.set_error_arg("");
  EXPECT_EQ(status_.error_arg(), "");
}

// Test set_error_arg with a longer string
TEST_F(RegexpStatusTest_137, SetErrorArgLongString_137) {
  std::string long_arg(1000, 'x');
  status_.set_error_arg(long_arg);
  EXPECT_EQ(status_.error_arg(), long_arg);
}

// Test ok() returns true for success
TEST_F(RegexpStatusTest_137, OkReturnsTrueForSuccess_137) {
  EXPECT_TRUE(status_.ok());
}

// Test ok() returns false for error codes
TEST_F(RegexpStatusTest_137, OkReturnsFalseForInternalError_137) {
  status_.set_code(kRegexpInternalError);
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, OkReturnsFalseForBadEscape_137) {
  status_.set_code(kRegexpBadEscape);
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, OkReturnsFalseForBadCharClass_137) {
  status_.set_code(kRegexpBadCharClass);
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, OkReturnsFalseForBadCharRange_137) {
  status_.set_code(kRegexpBadCharRange);
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, OkReturnsFalseForMissingBracket_137) {
  status_.set_code(kRegexpMissingBracket);
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, OkReturnsFalseForMissingParen_137) {
  status_.set_code(kRegexpMissingParen);
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, OkReturnsFalseForBadRepeatOp_137) {
  status_.set_code(kRegexpBadRepeatOp);
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, OkReturnsFalseForBadRepeatArgument_137) {
  status_.set_code(kRegexpBadRepeatArgument);
  EXPECT_FALSE(status_.ok());
}

// Test CodeText for known codes
TEST_F(RegexpStatusTest_137, CodeTextSuccess_137) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

TEST_F(RegexpStatusTest_137, CodeTextInternalError_137) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

TEST_F(RegexpStatusTest_137, CodeTextBadEscape_137) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test Text() method
TEST_F(RegexpStatusTest_137, TextForSuccessStatus_137) {
  // For success status, Text() should return something
  const std::string text = status_.Text();
  // Just ensure it doesn't crash; the exact text is implementation-dependent
}

TEST_F(RegexpStatusTest_137, TextForErrorStatus_137) {
  status_.set_code(kRegexpBadEscape);
  status_.set_error_arg("\\q");
  const std::string text = status_.Text();
  EXPECT_FALSE(text.empty());
}

// Test set_tmp
TEST_F(RegexpStatusTest_137, SetTmpNullptr_137) {
  status_.set_tmp(nullptr);
  // Should not crash
}

TEST_F(RegexpStatusTest_137, SetTmpValidPointer_137) {
  std::string tmp_str = "temporary";
  status_.set_tmp(&tmp_str);
  // Should not crash
}

// Test Copy method
TEST_F(RegexpStatusTest_137, CopyFromAnotherStatus_137) {
  RegexpStatus source;
  source.set_code(kRegexpBadEscape);
  source.set_error_arg("\\z");

  status_.Copy(source);
  EXPECT_EQ(status_.code(), kRegexpBadEscape);
  EXPECT_EQ(status_.error_arg(), "\\z");
  EXPECT_FALSE(status_.ok());
}

TEST_F(RegexpStatusTest_137, CopySuccessStatus_137) {
  status_.set_code(kRegexpInternalError);
  status_.set_error_arg("some error");

  RegexpStatus source;
  // source is default (success)
  status_.Copy(source);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test overwriting error_arg
TEST_F(RegexpStatusTest_137, OverwriteErrorArg_137) {
  status_.set_error_arg("first");
  EXPECT_EQ(status_.error_arg(), "first");
  status_.set_error_arg("second");
  EXPECT_EQ(status_.error_arg(), "second");
}

// Test overwriting code
TEST_F(RegexpStatusTest_137, OverwriteCode_137) {
  status_.set_code(kRegexpBadEscape);
  EXPECT_EQ(status_.code(), kRegexpBadEscape);
  status_.set_code(kRegexpMissingParen);
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
}

// Test that different error codes produce different CodeText
TEST_F(RegexpStatusTest_137, DifferentCodesHaveDifferentText_137) {
  std::string text1 = RegexpStatus::CodeText(kRegexpSuccess);
  std::string text2 = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_NE(text1, text2);
}

}  // namespace re2
