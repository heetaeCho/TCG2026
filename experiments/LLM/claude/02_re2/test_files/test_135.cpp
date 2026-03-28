#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for RegexpStatus tests
class RegexpStatusTest_135 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test default construction results in success/ok state
TEST_F(RegexpStatusTest_135, DefaultConstructionIsOk_135) {
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test that setting code to success keeps ok() true
TEST_F(RegexpStatusTest_135, SetCodeSuccess_135) {
  status_.set_code(kRegexpSuccess);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test that setting code to an error makes ok() false
TEST_F(RegexpStatusTest_135, SetCodeInternalError_135) {
  status_.set_code(kRegexpInternalError);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpInternalError);
}

// Test setting bad escape error code
TEST_F(RegexpStatusTest_135, SetCodeBadEscape_135) {
  status_.set_code(kRegexpBadEscape);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadEscape);
}

// Test setting bad char class error code
TEST_F(RegexpStatusTest_135, SetCodeBadCharClass_135) {
  status_.set_code(kRegexpBadCharClass);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadCharClass);
}

// Test setting bad char range error code
TEST_F(RegexpStatusTest_135, SetCodeBadCharRange_135) {
  status_.set_code(kRegexpBadCharRange);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadCharRange);
}

// Test setting missing bracket error code
TEST_F(RegexpStatusTest_135, SetCodeMissingBracket_135) {
  status_.set_code(kRegexpMissingBracket);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test setting missing paren error code
TEST_F(RegexpStatusTest_135, SetCodeMissingParen_135) {
  status_.set_code(kRegexpMissingParen);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
}

// Test setting bad repetition error code
TEST_F(RegexpStatusTest_135, SetCodeBadRepetition_135) {
  status_.set_code(kRegexpBadRepetition);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadRepetition);
}

// Test setting bad named capture error code
TEST_F(RegexpStatusTest_135, SetCodeBadNamedCapture_135) {
  status_.set_code(kRegexpBadNamedCapture);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadNamedCapture);
}

// Test setting bad perl op error code
TEST_F(RegexpStatusTest_135, SetCodeBadPerlOp_135) {
  status_.set_code(kRegexpBadPerlOp);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test setting bad UTF8 error code
TEST_F(RegexpStatusTest_135, SetCodeBadUTF8_135) {
  status_.set_code(kRegexpBadUTF8);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadUTF8);
}

// Test setting error_arg
TEST_F(RegexpStatusTest_135, SetErrorArg_135) {
  status_.set_error_arg("test_error");
  EXPECT_EQ(status_.error_arg(), "test_error");
}

// Test setting empty error_arg
TEST_F(RegexpStatusTest_135, SetEmptyErrorArg_135) {
  status_.set_error_arg("");
  EXPECT_EQ(status_.error_arg(), "");
}

// Test default error_arg is empty
TEST_F(RegexpStatusTest_135, DefaultErrorArgIsEmpty_135) {
  EXPECT_EQ(status_.error_arg(), "");
}

// Test CodeText for success
TEST_F(RegexpStatusTest_135, CodeTextSuccess_135) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for internal error
TEST_F(RegexpStatusTest_135, CodeTextInternalError_135) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad escape
TEST_F(RegexpStatusTest_135, CodeTextBadEscape_135) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for bad char class
TEST_F(RegexpStatusTest_135, CodeTextBadCharClass_135) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharClass);
  EXPECT_FALSE(text.empty());
}

// Test CodeText returns different strings for different codes
TEST_F(RegexpStatusTest_135, CodeTextDifferentCodes_135) {
  std::string success_text = RegexpStatus::CodeText(kRegexpSuccess);
  std::string error_text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_NE(success_text, error_text);
}

// Test Text() method with default state
TEST_F(RegexpStatusTest_135, TextDefaultState_135) {
  std::string text = status_.Text();
  // Default state is success, text should be something
  EXPECT_FALSE(text.empty());
}

// Test Text() method with error state
TEST_F(RegexpStatusTest_135, TextWithError_135) {
  status_.set_code(kRegexpBadEscape);
  status_.set_error_arg("\\q");
  std::string text = status_.Text();
  EXPECT_FALSE(text.empty());
}

// Test Copy method copies code
TEST_F(RegexpStatusTest_135, CopyCode_135) {
  RegexpStatus source;
  source.set_code(kRegexpBadEscape);
  source.set_error_arg("test");

  status_.Copy(source);
  EXPECT_EQ(status_.code(), kRegexpBadEscape);
  EXPECT_EQ(status_.error_arg(), "test");
  EXPECT_FALSE(status_.ok());
}

// Test Copy from success state
TEST_F(RegexpStatusTest_135, CopySuccessState_135) {
  status_.set_code(kRegexpInternalError);
  EXPECT_FALSE(status_.ok());

  RegexpStatus source;
  status_.Copy(source);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test set_tmp with new string
TEST_F(RegexpStatusTest_135, SetTmp_135) {
  std::string* tmp = new std::string("temporary");
  status_.set_tmp(tmp);
  // The destructor should clean up tmp_, so we just verify no crash
}

// Test set_tmp with nullptr
TEST_F(RegexpStatusTest_135, SetTmpNull_135) {
  status_.set_tmp(nullptr);
  // Should not crash on destruction
}

// Test setting code back and forth
TEST_F(RegexpStatusTest_135, SetCodeBackAndForth_135) {
  status_.set_code(kRegexpBadEscape);
  EXPECT_FALSE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpBadEscape);

  status_.set_code(kRegexpSuccess);
  EXPECT_TRUE(status_.ok());
  EXPECT_EQ(status_.code(), kRegexpSuccess);
}

// Test Copy preserves error_arg content
TEST_F(RegexpStatusTest_135, CopyPreservesErrorArg_135) {
  RegexpStatus source;
  source.set_code(kRegexpMissingParen);
  source.set_error_arg("(abc");

  status_.Copy(source);
  EXPECT_EQ(status_.code(), kRegexpMissingParen);
  EXPECT_EQ(status_.error_arg(), "(abc");
}

// Test setting error_arg multiple times
TEST_F(RegexpStatusTest_135, SetErrorArgMultipleTimes_135) {
  status_.set_error_arg("first");
  EXPECT_EQ(status_.error_arg(), "first");

  status_.set_error_arg("second");
  EXPECT_EQ(status_.error_arg(), "second");

  status_.set_error_arg("third");
  EXPECT_EQ(status_.error_arg(), "third");
}

// Test setting code multiple times
TEST_F(RegexpStatusTest_135, SetCodeMultipleTimes_135) {
  status_.set_code(kRegexpBadEscape);
  EXPECT_EQ(status_.code(), kRegexpBadEscape);

  status_.set_code(kRegexpBadCharClass);
  EXPECT_EQ(status_.code(), kRegexpBadCharClass);

  status_.set_code(kRegexpMissingBracket);
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test CodeText for all known codes are non-empty
TEST_F(RegexpStatusTest_135, CodeTextAllCodesNonEmpty_135) {
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpSuccess).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpInternalError).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpBadEscape).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpBadCharClass).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpBadCharRange).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpMissingBracket).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpMissingParen).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpBadRepetition).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpBadNamedCapture).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpBadPerlOp).empty());
  EXPECT_FALSE(RegexpStatus::CodeText(kRegexpBadUTF8).empty());
}

// Test Copy to self-like scenario (copy from another initialized object)
TEST_F(RegexpStatusTest_135, CopyFromInitializedObject_135) {
  RegexpStatus other;
  other.set_code(kRegexpBadUTF8);
  other.set_error_arg("bad utf8 sequence");

  RegexpStatus target;
  target.Copy(other);

  EXPECT_EQ(target.code(), kRegexpBadUTF8);
  EXPECT_EQ(target.error_arg(), "bad utf8 sequence");
  EXPECT_FALSE(target.ok());
}

}  // namespace re2
