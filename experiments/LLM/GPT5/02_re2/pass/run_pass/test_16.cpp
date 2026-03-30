// File: options_posix_syntax_test_16.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class OptionsPosixSyntaxTest_16 : public ::testing::Test {
protected:
  RE2::Options opts_;
};

// [Normal] Default-constructed Options should have posix_syntax() == false.
TEST_F(OptionsPosixSyntaxTest_16, DefaultIsFalse_16) {
  EXPECT_FALSE(opts_.posix_syntax());
}

// [Normal] set_posix_syntax toggles the observable value.
TEST_F(OptionsPosixSyntaxTest_16, SetTrueThenFalse_16) {
  opts_.set_posix_syntax(true);
  EXPECT_TRUE(opts_.posix_syntax());

  opts_.set_posix_syntax(false);
  EXPECT_FALSE(opts_.posix_syntax());
}

// [Normal] Canned option POSIX should enable posix_syntax().
TEST_F(OptionsPosixSyntaxTest_16, CannedOptionsPOSIXIsTrue_16) {
  RE2::Options posix_opts(RE2::POSIX);
  EXPECT_TRUE(posix_opts.posix_syntax());
}

// [Boundary] Non-POSIX canned options should NOT enable posix_syntax().
// Use a clearly non-POSIX canned option (e.g., Latin1).
TEST_F(OptionsPosixSyntaxTest_16, CannedOptionsNonPOSIXIsFalse_16) {
  RE2::Options latin1_opts(RE2::Latin1);
  EXPECT_FALSE(latin1_opts.posix_syntax());
}

// [Interaction/Copy] Copy() should preserve the observable posix_syntax() setting.
TEST_F(OptionsPosixSyntaxTest_16, CopyPreservesPosixSyntax_16) {
  opts_.set_posix_syntax(true);
  RE2::Options dst;
  dst.Copy(opts_);
  EXPECT_TRUE(dst.posix_syntax());

  // Also check copying when false.
  opts_.set_posix_syntax(false);
  dst.Copy(opts_);
  EXPECT_FALSE(dst.posix_syntax());
}

// [API/Const-correctness] posix_syntax() callable on const objects and returns bool.
TEST_F(OptionsPosixSyntaxTest_16, ConstGetterWorks_16) {
  opts_.set_posix_syntax(true);
  const RE2::Options& const_ref = opts_;
  // Compile-time const access and runtime value check.
  EXPECT_TRUE(const_ref.posix_syntax());
}
