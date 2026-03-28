#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for RegexpStatus tests
class RegexpStatusTest_136 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test default construction results in ok() being true
TEST_F(RegexpStatusTest_136, DefaultConstructionIsOk_136) {
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test set_code and code() accessor
TEST_F(RegexpStatusTest_136, SetCodeAndGetCode_136) {
  status_.set_code(kRegexpInternalError);
  EXPECT_EQ(status_.code(), kRegexpInternalError);
  EXPECT_FALSE(status_.ok());
}

// Test set_code with kRegexpSuccess restores ok state
TEST_F(RegexpStatusTest_136, SetCodeToSuccessIsOk_136) {
  status_.set_code(kRegexpInternalError);
  EXPECT_FALSE(status_.ok());
  status_.set_code(kRegexpSuccess);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test set_error_arg and error_arg() accessor
TEST_F(RegexpStatusTest_136, SetErrorArgAndGetErrorArg_136) {
  status_.set_code(kRegexpBadEscape);
  status_.set_error_arg("test_arg");
  EXPECT_EQ(status_.error_arg(), "test_arg");
}

// Test error_arg with empty string
TEST_F(RegexpStatusTest_136, SetEmptyErrorArg_136) {
  status_.set_error_arg("");
  EXPECT_EQ(status_.error_arg(), "");
}

// Test CodeText for kRegexpSuccess
TEST_F(RegexpStatusTest_136, CodeTextSuccess_136) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpInternalError
TEST_F(RegexpStatusTest_136, CodeTextInternalError_136) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadEscape
TEST_F(RegexpStatusTest_136, CodeTextBadEscape_136) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadCharClass
TEST_F(RegexpStatusTest_136, CodeTextBadCharClass_136) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharClass);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadCharRange
TEST_F(RegexpStatusTest_136, CodeTextBadCharRange_136) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharRange);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpMissingBracket
TEST_F(RegexpStatusTest_136, CodeTextMissingBracket_136) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingBracket);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpMissingParen
TEST_F(RegexpStatusTest_136, CodeTextMissingParen_136) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingParen);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadRepeatOp
TEST_F(RegexpStatusTest_136, CodeTextBadRepeatOp_136) {
  std::string text = RegexpStatus::CodeText(kRegexpBadRepeatOp);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpRepeatSize
TEST_F(RegexpStatusTest_136, CodeTextRepeatSize_136) {
  std::string text = RegexpStatus::CodeText(kRegexpRepeatSize);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpRepeatOp
TEST_F(RegexpStatusTest_136, CodeTextRepeatOp_136) {
  std::string text = RegexpStatus::CodeText(kRegexpRepeatOp);
  EXPECT_FALSE(text.empty());
}

// Test Text() method with error code and error arg
TEST_F(RegexpStatusTest_136, TextWithErrorCodeAndArg_136) {
  status_.set_code(kRegexpBadEscape);
  status_.set_error_arg("\\x");
  std::string text = status_.Text();
  EXPECT_FALSE(text.empty());
}

// Test Text() method with success code
TEST_F(RegexpStatusTest_136, TextWithSuccessCode_136) {
  std::string text = status_.Text();
  // Text should return something even for success
  // We just verify it doesn't crash
  (void)text;
}

// Test Copy method
TEST_F(RegexpStatusTest_136, CopyStatus_136) {
  RegexpStatus source;
  source.set_code(kRegexpBadEscape);
  source.set_error_arg("copy_test");

  status_.Copy(source);
  EXPECT_EQ(status_.code(), kRegexpBadEscape);
  EXPECT_EQ(status_.error_arg(), "copy_test");
  EXPECT_FALSE(status_.ok());
}

// Test Copy from a success status
TEST_F(RegexpStatusTest_136, CopySuccessStatus_136) {
  status_.set_code(kRegexpInternalError);
  EXPECT_FALSE(status_.ok());

  RegexpStatus source;
  status_.Copy(source);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test set_tmp with nullptr
TEST_F(RegexpStatusTest_136, SetTmpNull_136) {
  status_.set_tmp(nullptr);
  // Just verify it doesn't crash
  EXPECT_TRUE(status_.ok());
}

// Test set_tmp with a valid string pointer
TEST_F(RegexpStatusTest_136, SetTmpValidPointer_136) {
  std::string tmp = "temporary";
  status_.set_tmp(&tmp);
  // Just verify it doesn't crash
  EXPECT_TRUE(status_.ok());
}

// Test multiple code changes
TEST_F(RegexpStatusTest_136, MultipleCodeChanges_136) {
  status_.set_code(kRegexpBadEscape);
  EXPECT_EQ(status_.code(), kRegexpBadEscape);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpBadCharClass);
  EXPECT_EQ(status_.code(), kRegexpBadCharClass);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpSuccess);
  EXPECT_EQ(status_.code(), kRegexpSuccess);
  EXPECT_TRUE(status_.ok());
}

// Test that different error codes produce different CodeText
TEST_F(RegexpStatusTest_136, DifferentCodesProduceDifferentText_136) {
  std::string text1 = RegexpStatus::CodeText(kRegexpBadEscape);
  std::string text2 = RegexpStatus::CodeText(kRegexpBadCharClass);
  std::string text3 = RegexpStatus::CodeText(kRegexpSuccess);
  // Different error codes should generally produce different text descriptions
  EXPECT_NE(text1, text2);
  EXPECT_NE(text1, text3);
}

// Test ok() for various error codes
TEST_F(RegexpStatusTest_136, OkReturnsFalseForAllErrorCodes_136) {
  status_.set_code(kRegexpBadEscape);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpBadCharClass);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpBadCharRange);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpMissingBracket);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpMissingParen);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpBadRepeatOp);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpRepeatSize);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpRepeatOp);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpBadPerlOp);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpBadUTF8);
  EXPECT_FALSE(status_.ok());

  status_.set_code(kRegexpBadNamedCapture);
  EXPECT_FALSE(status_.ok());
}

}  // namespace re2
