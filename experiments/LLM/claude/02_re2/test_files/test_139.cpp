#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test default construction
TEST(RegexpStatusTest_139, DefaultConstructionIsSuccess_139) {
  RegexpStatus status;
  EXPECT_EQ(kRegexpSuccess, status.code());
}

TEST(RegexpStatusTest_139, DefaultConstructionIsOk_139) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
}

// Test set_code and code
TEST(RegexpStatusTest_139, SetCodeAndRetrieve_139) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_EQ(kRegexpInternalError, status.code());
}

TEST(RegexpStatusTest_139, SetCodeBadCharClass_139) {
  RegexpStatus status;
  status.set_code(kRegexpBadCharClass);
  EXPECT_EQ(kRegexpBadCharClass, status.code());
  EXPECT_FALSE(status.ok());
}

TEST(RegexpStatusTest_139, SetCodeBadCharRange_139) {
  RegexpStatus status;
  status.set_code(kRegexpBadCharRange);
  EXPECT_EQ(kRegexpBadCharRange, status.code());
  EXPECT_FALSE(status.ok());
}

TEST(RegexpStatusTest_139, SetCodeMissingBracket_139) {
  RegexpStatus status;
  status.set_code(kRegexpMissingBracket);
  EXPECT_EQ(kRegexpMissingBracket, status.code());
  EXPECT_FALSE(status.ok());
}

TEST(RegexpStatusTest_139, SetCodeMissingParen_139) {
  RegexpStatus status;
  status.set_code(kRegexpMissingParen);
  EXPECT_EQ(kRegexpMissingParen, status.code());
  EXPECT_FALSE(status.ok());
}

TEST(RegexpStatusTest_139, SetCodeBadRepeatOp_139) {
  RegexpStatus status;
  status.set_code(kRegexpBadRepeatOp);
  EXPECT_EQ(kRegexpBadRepeatOp, status.code());
  EXPECT_FALSE(status.ok());
}

TEST(RegexpStatusTest_139, SetCodeBadRepeatArg_139) {
  RegexpStatus status;
  status.set_code(kRegexpBadRepeatArg);
  EXPECT_EQ(kRegexpBadRepeatArg, status.code());
  EXPECT_FALSE(status.ok());
}

TEST(RegexpStatusTest_139, SetCodeBadEscape_139) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  EXPECT_EQ(kRegexpBadEscape, status.code());
  EXPECT_FALSE(status.ok());
}

TEST(RegexpStatusTest_139, SetCodeBadNamedCapture_139) {
  RegexpStatus status;
  status.set_code(kRegexpBadNamedCapture);
  EXPECT_EQ(kRegexpBadNamedCapture, status.code());
  EXPECT_FALSE(status.ok());
}

// Test ok() returns true only for success
TEST(RegexpStatusTest_139, OkReturnsTrueForSuccess_139) {
  RegexpStatus status;
  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
}

TEST(RegexpStatusTest_139, OkReturnsFalseForError_139) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());
}

// Test set_error_arg and error_arg
TEST(RegexpStatusTest_139, SetErrorArgAndRetrieve_139) {
  RegexpStatus status;
  status.set_error_arg("test_error");
  EXPECT_EQ("test_error", status.error_arg());
}

TEST(RegexpStatusTest_139, ErrorArgDefaultEmpty_139) {
  RegexpStatus status;
  EXPECT_EQ("", status.error_arg());
}

TEST(RegexpStatusTest_139, SetErrorArgEmpty_139) {
  RegexpStatus status;
  status.set_error_arg("");
  EXPECT_EQ("", status.error_arg());
}

// Test CodeText
TEST(RegexpStatusTest_139, CodeTextSuccess_139) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextInternalError_139) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextBadEscape_139) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextBadCharClass_139) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharClass);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextBadCharRange_139) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharRange);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextMissingBracket_139) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingBracket);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextMissingParen_139) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingParen);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextBadRepeatOp_139) {
  std::string text = RegexpStatus::CodeText(kRegexpBadRepeatOp);
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, CodeTextBadRepeatArg_139) {
  std::string text = RegexpStatus::CodeText(kRegexpBadRepeatArg);
  EXPECT_FALSE(text.empty());
}

// Test Text()
TEST(RegexpStatusTest_139, TextForSuccess_139) {
  RegexpStatus status;
  status.set_code(kRegexpSuccess);
  std::string text = status.Text();
  // Text should return something meaningful for success
  EXPECT_FALSE(text.empty());
}

TEST(RegexpStatusTest_139, TextForErrorWithArg_139) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  status.set_error_arg("\\x");
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

// Test Copy
TEST(RegexpStatusTest_139, CopyStatus_139) {
  RegexpStatus src;
  src.set_code(kRegexpBadEscape);
  src.set_error_arg("test_arg");

  RegexpStatus dst;
  dst.Copy(src);
  
  EXPECT_EQ(kRegexpBadEscape, dst.code());
  EXPECT_EQ("test_arg", dst.error_arg());
}

TEST(RegexpStatusTest_139, CopySuccessStatus_139) {
  RegexpStatus src;
  // src is default success
  
  RegexpStatus dst;
  dst.set_code(kRegexpInternalError);
  dst.Copy(src);
  
  EXPECT_EQ(kRegexpSuccess, dst.code());
  EXPECT_TRUE(dst.ok());
}

// Test set_code back to success after error
TEST(RegexpStatusTest_139, ResetCodeToSuccess_139) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());
  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(kRegexpSuccess, status.code());
}

// Test set_tmp
TEST(RegexpStatusTest_139, SetTmpNullptr_139) {
  RegexpStatus status;
  status.set_tmp(nullptr);
  // Just ensuring no crash
  EXPECT_TRUE(status.ok());
}

TEST(RegexpStatusTest_139, SetTmpWithString_139) {
  RegexpStatus status;
  std::string tmp = "temporary";
  status.set_tmp(&tmp);
  // Just ensuring no crash; we can't observe tmp directly without internals
}

// Test different CodeText values are distinct
TEST(RegexpStatusTest_139, CodeTextValuesAreDistinct_139) {
  std::string success_text = RegexpStatus::CodeText(kRegexpSuccess);
  std::string internal_error_text = RegexpStatus::CodeText(kRegexpInternalError);
  std::string bad_escape_text = RegexpStatus::CodeText(kRegexpBadEscape);
  
  EXPECT_NE(success_text, internal_error_text);
  EXPECT_NE(success_text, bad_escape_text);
  EXPECT_NE(internal_error_text, bad_escape_text);
}

// Test Copy preserves error_arg content
TEST(RegexpStatusTest_139, CopyPreservesErrorArg_139) {
  RegexpStatus src;
  src.set_code(kRegexpBadCharClass);
  src.set_error_arg("some_arg");

  RegexpStatus dst;
  dst.Copy(src);

  EXPECT_EQ(src.code(), dst.code());
  EXPECT_EQ(src.error_arg(), dst.error_arg());
}

// Test overwriting error_arg
TEST(RegexpStatusTest_139, OverwriteErrorArg_139) {
  RegexpStatus status;
  status.set_error_arg("first");
  EXPECT_EQ("first", status.error_arg());
  status.set_error_arg("second");
  EXPECT_EQ("second", status.error_arg());
}

}  // namespace re2
