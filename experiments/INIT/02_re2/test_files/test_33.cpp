// File: re2_options_set_perl_classes_test_33.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2OptionsPerlClassesTest_33 : public ::testing::Test {
protected:
  RE2::Options opt_;
};

// Default should be false (as observable via the public getter).
TEST_F(RE2OptionsPerlClassesTest_33, DefaultIsFalse_33) {
  EXPECT_FALSE(opt_.perl_classes());
}

// Setting to true should be observable via the getter.
TEST_F(RE2OptionsPerlClassesTest_33, SetTrueReflectsInGetter_33) {
  opt_.set_perl_classes(true);
  EXPECT_TRUE(opt_.perl_classes());
}

// Toggling true -> false should be observable via the getter.
TEST_F(RE2OptionsPerlClassesTest_33, ToggleTrueThenFalse_33) {
  opt_.set_perl_classes(true);
  ASSERT_TRUE(opt_.perl_classes());  // sanity check
  opt_.set_perl_classes(false);
  EXPECT_FALSE(opt_.perl_classes());
}

// Copy should copy the perl_classes setting from the source to the destination.
TEST_F(RE2OptionsPerlClassesTest_33, CopyCopiesPerlClassesFlag_33) {
  RE2::Options src;
  RE2::Options dst;

  src.set_perl_classes(true);
  dst.Copy(src);
  EXPECT_EQ(dst.perl_classes(), src.perl_classes());

  // Also verify copying when the flag is false.
  src.set_perl_classes(false);
  dst.Copy(src);
  EXPECT_EQ(dst.perl_classes(), src.perl_classes());
}

// Changing unrelated options should not change perl_classes (observable independence).
TEST_F(RE2OptionsPerlClassesTest_33, UnrelatedOptionChangesDoNotAffectPerlClasses_33) {
  // Start with a known value.
  opt_.set_perl_classes(true);
  ASSERT_TRUE(opt_.perl_classes());

  // Flip various other flags; perl_classes should remain unchanged.
  opt_.set_case_sensitive(false);
  opt_.set_never_nl(true);
  opt_.set_dot_nl(true);
  opt_.set_never_capture(true);
  opt_.set_longest_match(true);
  opt_.set_log_errors(false);
  opt_.set_literal(true);
  opt_.set_posix_syntax(true);
  opt_.set_one_line(true);
  opt_.set_word_boundary(true);

  EXPECT_TRUE(opt_.perl_classes());

  // And after toggling it ourselves, it should follow only our direct changes.
  opt_.set_perl_classes(false);
  EXPECT_FALSE(opt_.perl_classes());
}
