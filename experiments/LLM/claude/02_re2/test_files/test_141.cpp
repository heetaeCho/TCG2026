#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for RegexpStatus tests
class RegexpStatusTest_141 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction yields ok() == true and code() == kRegexpSuccess
TEST_F(RegexpStatusTest_141, DefaultConstructionIsOk_141) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test that setting code to kRegexpSuccess keeps ok() true
TEST_F(RegexpStatusTest_141, SetCodeSuccess_141) {
  RegexpStatus status;
  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Test that setting code to an error makes ok() false
TEST_F(RegexpStatusTest_141, SetCodeInternalError_141) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpInternalError);
}

// Test setting code to kRegexpBadEscape
TEST_F(RegexpStatusTest_141, SetCodeBadEscape_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpBadEscape);
}

// Test setting code to kRegexpBadCharClass
TEST_F(RegexpStatusTest_141, SetCodeBadCharClass_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadCharClass);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpBadCharClass);
}

// Test setting code to kRegexpBadCharRange
TEST_F(RegexpStatusTest_141, SetCodeBadCharRange_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadCharRange);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpBadCharRange);
}

// Test setting code to kRegexpMissingBracket
TEST_F(RegexpStatusTest_141, SetCodeMissingBracket_141) {
  RegexpStatus status;
  status.set_code(kRegexpMissingBracket);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpMissingBracket);
}

// Test setting code to kRegexpMissingParen
TEST_F(RegexpStatusTest_141, SetCodeMissingParen_141) {
  RegexpStatus status;
  status.set_code(kRegexpMissingParen);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpMissingParen);
}

// Test setting code to kRegexpUnexpectedParen
TEST_F(RegexpStatusTest_141, SetCodeUnexpectedParen_141) {
  RegexpStatus status;
  status.set_code(kRegexpUnexpectedParen);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpUnexpectedParen);
}

// Test setting code to kRegexpTrailingBackslash
TEST_F(RegexpStatusTest_141, SetCodeTrailingBackslash_141) {
  RegexpStatus status;
  status.set_code(kRegexpTrailingBackslash);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpTrailingBackslash);
}

// Test setting code to kRegexpRepeatArgument
TEST_F(RegexpStatusTest_141, SetCodeRepeatArgument_141) {
  RegexpStatus status;
  status.set_code(kRegexpRepeatArgument);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpRepeatArgument);
}

// Test setting code to kRegexpRepeatSize
TEST_F(RegexpStatusTest_141, SetCodeRepeatSize_141) {
  RegexpStatus status;
  status.set_code(kRegexpRepeatSize);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpRepeatSize);
}

// Test setting code to kRegexpRepeatOp
TEST_F(RegexpStatusTest_141, SetCodeRepeatOp_141) {
  RegexpStatus status;
  status.set_code(kRegexpRepeatOp);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpRepeatOp);
}

// Test setting code to kRegexpBadPerlOp
TEST_F(RegexpStatusTest_141, SetCodeBadPerlOp_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadPerlOp);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpBadPerlOp);
}

// Test setting code to kRegexpBadUTF8
TEST_F(RegexpStatusTest_141, SetCodeBadUTF8_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadUTF8);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpBadUTF8);
}

// Test setting code to kRegexpBadNamedCapture
TEST_F(RegexpStatusTest_141, SetCodeBadNamedCapture_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadNamedCapture);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), kRegexpBadNamedCapture);
}

// Test set_error_arg and error_arg
TEST_F(RegexpStatusTest_141, SetAndGetErrorArg_141) {
  RegexpStatus status;
  status.set_error_arg("test_error");
  EXPECT_EQ(status.error_arg(), "test_error");
}

// Test error_arg with empty string
TEST_F(RegexpStatusTest_141, SetEmptyErrorArg_141) {
  RegexpStatus status;
  status.set_error_arg("");
  EXPECT_EQ(status.error_arg(), "");
}

// Test CodeText for kRegexpSuccess
TEST_F(RegexpStatusTest_141, CodeTextSuccess_141) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for various error codes returns non-empty strings
TEST_F(RegexpStatusTest_141, CodeTextInternalError_141) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

TEST_F(RegexpStatusTest_141, CodeTextBadEscape_141) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test that CodeText returns different strings for different codes
TEST_F(RegexpStatusTest_141, CodeTextDifferentCodes_141) {
  std::string success_text = RegexpStatus::CodeText(kRegexpSuccess);
  std::string error_text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_NE(success_text, error_text);
}

// Test Text() method on default status
TEST_F(RegexpStatusTest_141, TextOnDefaultStatus_141) {
  RegexpStatus status;
  std::string text = status.Text();
  // Default status is success, so Text() should return something meaningful
  EXPECT_FALSE(text.empty());
}

// Test Text() method with error code and error arg
TEST_F(RegexpStatusTest_141, TextWithErrorAndArg_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  status.set_error_arg("\\z");
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

// Test Copy method
TEST_F(RegexpStatusTest_141, CopyFromError_141) {
  RegexpStatus src;
  src.set_code(kRegexpMissingParen);
  src.set_error_arg("(abc");

  RegexpStatus dst;
  dst.Copy(src);
  EXPECT_EQ(dst.code(), kRegexpMissingParen);
  EXPECT_EQ(dst.error_arg(), "(abc");
  EXPECT_FALSE(dst.ok());
}

// Test Copy from default (success) status
TEST_F(RegexpStatusTest_141, CopyFromSuccess_141) {
  RegexpStatus src;

  RegexpStatus dst;
  dst.set_code(kRegexpBadEscape);
  dst.Copy(src);
  EXPECT_TRUE(dst.ok());
  EXPECT_EQ(dst.code(), kRegexpSuccess);
}

// Test overwriting error code (set error, then set back to success)
TEST_F(RegexpStatusTest_141, OverwriteCodeBackToSuccess_141) {
  RegexpStatus status;
  status.set_code(kRegexpBadCharClass);
  EXPECT_FALSE(status.ok());

  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
}

// Test set_tmp with nullptr
TEST_F(RegexpStatusTest_141, SetTmpNull_141) {
  RegexpStatus status;
  status.set_tmp(nullptr);
  // Should not crash; no observable effect other than not crashing
  EXPECT_TRUE(status.ok());
}

// Test set_tmp with a valid string pointer
TEST_F(RegexpStatusTest_141, SetTmpValidPointer_141) {
  RegexpStatus status;
  std::string tmp_str = "temporary";
  status.set_tmp(&tmp_str);
  // No crash expected
  EXPECT_TRUE(status.ok());
}

// Test multiple error_arg changes
TEST_F(RegexpStatusTest_141, MultipleErrorArgChanges_141) {
  RegexpStatus status;
  status.set_error_arg("first");
  EXPECT_EQ(status.error_arg(), "first");

  status.set_error_arg("second");
  EXPECT_EQ(status.error_arg(), "second");

  status.set_error_arg("third");
  EXPECT_EQ(status.error_arg(), "third");
}

// Test Copy preserves error_arg
TEST_F(RegexpStatusTest_141, CopyPreservesErrorArg_141) {
  RegexpStatus src;
  src.set_code(kRegexpBadUTF8);
  src.set_error_arg("bad_utf8_data");

  RegexpStatus dst;
  dst.Copy(src);
  EXPECT_EQ(dst.code(), kRegexpBadUTF8);
  EXPECT_FALSE(dst.ok());
  // The error_arg should be preserved after copy
  EXPECT_EQ(dst.error_arg(), "bad_utf8_data");
}

// Test that CodeText covers all known error codes
TEST_F(RegexpStatusTest_141, CodeTextAllCodes_141) {
  RegexpStatusCode codes[] = {
    kRegexpSuccess,
    kRegexpInternalError,
    kRegexpBadEscape,
    kRegexpBadCharClass,
    kRegexpBadCharRange,
    kRegexpMissingBracket,
    kRegexpMissingParen,
    kRegexpUnexpectedParen,
    kRegexpTrailingBackslash,
    kRegexpRepeatArgument,
    kRegexpRepeatSize,
    kRegexpRepeatOp,
    kRegexpBadPerlOp,
    kRegexpBadUTF8,
    kRegexpBadNamedCapture,
  };

  for (auto code : codes) {
    std::string text = RegexpStatus::CodeText(code);
    EXPECT_FALSE(text.empty()) << "CodeText empty for code " << code;
  }
}

}  // namespace re2
