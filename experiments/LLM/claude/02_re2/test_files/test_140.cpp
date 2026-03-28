#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test default construction
TEST(RegexpStatusTest_140, DefaultConstructionIsOk_140) {
  RegexpStatus status;
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_TRUE(status.error_arg().empty());
}

// Test set_code and code
TEST(RegexpStatusTest_140, SetCodeAndRetrieve_140) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_EQ(status.code(), kRegexpInternalError);
  EXPECT_FALSE(status.ok());
}

// Test set_error_arg and error_arg
TEST(RegexpStatusTest_140, SetErrorArgAndRetrieve_140) {
  RegexpStatus status;
  status.set_error_arg("some_error_arg");
  EXPECT_EQ(status.error_arg(), "some_error_arg");
}

// Test ok() returns true for kRegexpSuccess
TEST(RegexpStatusTest_140, OkReturnsTrueForSuccess_140) {
  RegexpStatus status;
  status.set_code(kRegexpSuccess);
  EXPECT_TRUE(status.ok());
}

// Test ok() returns false for non-success codes
TEST(RegexpStatusTest_140, OkReturnsFalseForNonSuccess_140) {
  RegexpStatus status;
  status.set_code(kRegexpInternalError);
  EXPECT_FALSE(status.ok());
}

// Test CodeText for kRegexpSuccess
TEST(RegexpStatusTest_140, CodeTextSuccess_140) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpInternalError
TEST(RegexpStatusTest_140, CodeTextInternalError_140) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadEscape
TEST(RegexpStatusTest_140, CodeTextBadEscape_140) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadCharClass
TEST(RegexpStatusTest_140, CodeTextBadCharClass_140) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharClass);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadCharRange
TEST(RegexpStatusTest_140, CodeTextBadCharRange_140) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharRange);
  EXPECT_FALSE(text.empty());
}

// Test Text() with error code and error arg
TEST(RegexpStatusTest_140, TextWithErrorCodeAndArg_140) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  status.set_error_arg("\\q");
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

// Test Text() with success code
TEST(RegexpStatusTest_140, TextWithSuccessCode_140) {
  RegexpStatus status;
  status.set_code(kRegexpSuccess);
  std::string text = status.Text();
  // The text representation of success should be something (possibly empty or a message)
  // Just check it doesn't crash
}

// Test Copy
TEST(RegexpStatusTest_140, CopyStatus_140) {
  RegexpStatus src;
  src.set_code(kRegexpBadEscape);
  src.set_error_arg("test_arg");

  RegexpStatus dst;
  dst.Copy(src);

  EXPECT_EQ(dst.code(), kRegexpBadEscape);
  EXPECT_EQ(dst.error_arg(), "test_arg");
  EXPECT_FALSE(dst.ok());
}

// Test Copy from default status
TEST(RegexpStatusTest_140, CopyDefaultStatus_140) {
  RegexpStatus src;
  RegexpStatus dst;
  dst.set_code(kRegexpInternalError);
  dst.set_error_arg("old_arg");

  dst.Copy(src);
  EXPECT_EQ(dst.code(), kRegexpSuccess);
  EXPECT_TRUE(dst.ok());
}

// Test set_error_arg with empty string
TEST(RegexpStatusTest_140, SetEmptyErrorArg_140) {
  RegexpStatus status;
  status.set_error_arg("");
  EXPECT_TRUE(status.error_arg().empty());
}

// Test set_error_arg with a long string
TEST(RegexpStatusTest_140, SetLongErrorArg_140) {
  RegexpStatus status;
  std::string long_arg(1000, 'x');
  status.set_error_arg(long_arg);
  EXPECT_EQ(status.error_arg(), long_arg);
}

// Test setting code multiple times
TEST(RegexpStatusTest_140, SetCodeMultipleTimes_140) {
  RegexpStatus status;
  status.set_code(kRegexpBadEscape);
  EXPECT_EQ(status.code(), kRegexpBadEscape);
  status.set_code(kRegexpInternalError);
  EXPECT_EQ(status.code(), kRegexpInternalError);
  status.set_code(kRegexpSuccess);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_TRUE(status.ok());
}

// Test setting error_arg multiple times
TEST(RegexpStatusTest_140, SetErrorArgMultipleTimes_140) {
  RegexpStatus status;
  status.set_error_arg("first");
  EXPECT_EQ(status.error_arg(), "first");
  status.set_error_arg("second");
  EXPECT_EQ(status.error_arg(), "second");
}

// Test set_tmp
TEST(RegexpStatusTest_140, SetTmpDoesNotCrash_140) {
  RegexpStatus status;
  std::string tmp_str = "temporary";
  status.set_tmp(&tmp_str);
  // We can't observe internal tmp_ directly, but verify no crash
  // and that other methods still work
  EXPECT_TRUE(status.ok());
}

// Test set_tmp with nullptr
TEST(RegexpStatusTest_140, SetTmpNull_140) {
  RegexpStatus status;
  status.set_tmp(nullptr);
  EXPECT_TRUE(status.ok());
}

// Test that Copy preserves ok status
TEST(RegexpStatusTest_140, CopyPreservesOkStatus_140) {
  RegexpStatus src;
  EXPECT_TRUE(src.ok());

  RegexpStatus dst;
  dst.set_code(kRegexpBadCharClass);
  EXPECT_FALSE(dst.ok());

  dst.Copy(src);
  EXPECT_TRUE(dst.ok());
  EXPECT_EQ(dst.code(), kRegexpSuccess);
}

// Test Text for various error codes
TEST(RegexpStatusTest_140, TextForMissingBracket_140) {
  RegexpStatus status;
  status.set_code(kRegexpMissingBracket);
  status.set_error_arg("[abc");
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

// Test Text for missing paren
TEST(RegexpStatusTest_140, TextForMissingParen_140) {
  RegexpStatus status;
  status.set_code(kRegexpMissingParen);
  status.set_error_arg("(abc");
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

}  // namespace re2
