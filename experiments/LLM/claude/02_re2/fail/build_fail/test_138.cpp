#include "gtest/gtest.h"
#include "re2/regexp.h"
#include <string>

namespace re2 {

// Test fixture for RegexpStatus tests
class RegexpStatusTest_138 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = new RegexpStatus();
  }

  void TearDown() override {
    delete status_;
  }

  RegexpStatus* status_;
};

// Test default construction - should be successful/ok
TEST_F(RegexpStatusTest_138, DefaultConstructionIsOk_138) {
  EXPECT_TRUE(status_->ok());
  EXPECT_EQ(status_->code(), kRegexpSuccess);
}

// Test set_code and code getter
TEST_F(RegexpStatusTest_138, SetCodeAndGetCode_138) {
  status_->set_code(kRegexpInternalError);
  EXPECT_EQ(status_->code(), kRegexpInternalError);
  EXPECT_FALSE(status_->ok());
}

// Test set_code back to success
TEST_F(RegexpStatusTest_138, SetCodeBackToSuccess_138) {
  status_->set_code(kRegexpInternalError);
  EXPECT_FALSE(status_->ok());
  status_->set_code(kRegexpSuccess);
  EXPECT_TRUE(status_->ok());
  EXPECT_EQ(status_->code(), kRegexpSuccess);
}

// Test set_error_arg and error_arg getter
TEST_F(RegexpStatusTest_138, SetErrorArgAndGet_138) {
  std::string arg = "test_error";
  status_->set_error_arg(arg);
  EXPECT_EQ(status_->error_arg(), "test_error");
}

// Test set_tmp with a new string
TEST_F(RegexpStatusTest_138, SetTmpWithNewString_138) {
  std::string* tmp = new std::string("temporary");
  status_->set_tmp(tmp);
  // set_tmp takes ownership; we just verify no crash
}

// Test set_tmp with nullptr
TEST_F(RegexpStatusTest_138, SetTmpWithNullptr_138) {
  status_->set_tmp(nullptr);
  // Should not crash
}

// Test set_tmp replaces previous tmp (no leak, no crash)
TEST_F(RegexpStatusTest_138, SetTmpReplacesOldTmp_138) {
  std::string* tmp1 = new std::string("first");
  std::string* tmp2 = new std::string("second");
  status_->set_tmp(tmp1);
  status_->set_tmp(tmp2);
  // The old tmp1 should be deleted by set_tmp; no crash expected
}

// Test CodeText for kRegexpSuccess
TEST_F(RegexpStatusTest_138, CodeTextSuccess_138) {
  std::string text = RegexpStatus::CodeText(kRegexpSuccess);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpInternalError
TEST_F(RegexpStatusTest_138, CodeTextInternalError_138) {
  std::string text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadEscape
TEST_F(RegexpStatusTest_138, CodeTextBadEscape_138) {
  std::string text = RegexpStatus::CodeText(kRegexpBadEscape);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadCharClass
TEST_F(RegexpStatusTest_138, CodeTextBadCharClass_138) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharClass);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadCharRange
TEST_F(RegexpStatusTest_138, CodeTextBadCharRange_138) {
  std::string text = RegexpStatus::CodeText(kRegexpBadCharRange);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpMissingBracket
TEST_F(RegexpStatusTest_138, CodeTextMissingBracket_138) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingBracket);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpMissingParen
TEST_F(RegexpStatusTest_138, CodeTextMissingParen_138) {
  std::string text = RegexpStatus::CodeText(kRegexpMissingParen);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpBadRepeatOp
TEST_F(RegexpStatusTest_138, CodeTextBadRepeatOp_138) {
  std::string text = RegexpStatus::CodeText(kRegexpBadRepeatOp);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpRepeatSize
TEST_F(RegexpStatusTest_138, CodeTextRepeatSize_138) {
  std::string text = RegexpStatus::CodeText(kRegexpRepeatSize);
  EXPECT_FALSE(text.empty());
}

// Test CodeText for kRegexpRepeatArgument
TEST_F(RegexpStatusTest_138, CodeTextRepeatArgument_138) {
  std::string text = RegexpStatus::CodeText(kRegexpRepeatArgument);
  EXPECT_FALSE(text.empty());
}

// Test Text() when status is ok
TEST_F(RegexpStatusTest_138, TextWhenOk_138) {
  std::string text = status_->Text();
  // When ok, text should still be a valid string
  EXPECT_FALSE(text.empty());
}

// Test Text() when status has an error
TEST_F(RegexpStatusTest_138, TextWhenError_138) {
  status_->set_code(kRegexpBadEscape);
  status_->set_error_arg("\\x");
  std::string text = status_->Text();
  EXPECT_FALSE(text.empty());
}

// Test Copy method
TEST_F(RegexpStatusTest_138, CopyFromAnother_138) {
  RegexpStatus other;
  other.set_code(kRegexpBadCharClass);
  other.set_error_arg("bad_class");

  status_->Copy(other);
  EXPECT_EQ(status_->code(), kRegexpBadCharClass);
  EXPECT_EQ(status_->error_arg(), "bad_class");
  EXPECT_FALSE(status_->ok());
}

// Test Copy from a successful status
TEST_F(RegexpStatusTest_138, CopyFromSuccessStatus_138) {
  status_->set_code(kRegexpInternalError);
  EXPECT_FALSE(status_->ok());

  RegexpStatus other;
  status_->Copy(other);
  EXPECT_TRUE(status_->ok());
  EXPECT_EQ(status_->code(), kRegexpSuccess);
}

// Test ok() returns true only for kRegexpSuccess
TEST_F(RegexpStatusTest_138, OkOnlyForSuccess_138) {
  status_->set_code(kRegexpSuccess);
  EXPECT_TRUE(status_->ok());

  status_->set_code(kRegexpInternalError);
  EXPECT_FALSE(status_->ok());

  status_->set_code(kRegexpBadEscape);
  EXPECT_FALSE(status_->ok());

  status_->set_code(kRegexpBadCharClass);
  EXPECT_FALSE(status_->ok());
}

// Test set_error_arg with empty string
TEST_F(RegexpStatusTest_138, SetErrorArgEmpty_138) {
  status_->set_error_arg("");
  EXPECT_EQ(status_->error_arg(), "");
}

// Test set_error_arg with a long string
TEST_F(RegexpStatusTest_138, SetErrorArgLongString_138) {
  std::string long_arg(1000, 'x');
  status_->set_error_arg(long_arg);
  EXPECT_EQ(status_->error_arg(), long_arg);
}

// Test setting tmp to nullptr after having a value
TEST_F(RegexpStatusTest_138, SetTmpToNullAfterValue_138) {
  status_->set_tmp(new std::string("value"));
  status_->set_tmp(nullptr);
  // Should not crash; old value deleted
}

// Test multiple set_tmp calls
TEST_F(RegexpStatusTest_138, MultipleTmpSets_138) {
  for (int i = 0; i < 10; i++) {
    status_->set_tmp(new std::string("tmp_" + std::to_string(i)));
  }
  status_->set_tmp(nullptr);
}

// Test Copy preserves error_arg correctly
TEST_F(RegexpStatusTest_138, CopyPreservesErrorArg_138) {
  RegexpStatus src;
  src.set_code(kRegexpMissingParen);
  src.set_error_arg("missing)");

  RegexpStatus dst;
  dst.Copy(src);

  EXPECT_EQ(dst.code(), kRegexpMissingParen);
  EXPECT_EQ(dst.error_arg(), "missing)");
}

// Test that different error codes produce different CodeText
TEST_F(RegexpStatusTest_138, DifferentCodesProduceDifferentText_138) {
  std::string success_text = RegexpStatus::CodeText(kRegexpSuccess);
  std::string error_text = RegexpStatus::CodeText(kRegexpInternalError);
  EXPECT_NE(success_text, error_text);
}

}  // namespace re2
