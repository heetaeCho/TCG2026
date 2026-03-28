// File: re2_options_never_nl_test.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class OptionsNeverNLTest_24 : public ::testing::Test {
protected:
  RE2::Options opts_;
};

// [Normal] Default should be false for never_nl()
TEST_F(OptionsNeverNLTest_24, DefaultIsFalse_24) {
  EXPECT_FALSE(opts_.never_nl());
}

// [Normal] Setter should toggle the observable getter result
TEST_F(OptionsNeverNLTest_24, SetTrueThenFalse_24) {
  opts_.set_never_nl(true);
  EXPECT_TRUE(opts_.never_nl());

  opts_.set_never_nl(false);
  EXPECT_FALSE(opts_.never_nl());
}

// [Boundary] Idempotency when setting the same value repeatedly
TEST_F(OptionsNeverNLTest_24, SettingTrueTwiceIsIdempotent_24) {
  opts_.set_never_nl(true);
  EXPECT_TRUE(opts_.never_nl());

  // Set again to the same value; behavior (getter's visible state) should remain the same
  opts_.set_never_nl(true);
  EXPECT_TRUE(opts_.never_nl());
}

// [Interaction] Copy(...) should copy the observable flag value from source
TEST_F(OptionsNeverNLTest_24, CopyPreservesNeverNL_24) {
  RE2::Options src;
  src.set_never_nl(true);

  RE2::Options dst;
  // Verify precondition (dst starts with some state that may differ)
  EXPECT_FALSE(dst.never_nl());

  dst.Copy(src);

  EXPECT_TRUE(dst.never_nl());
  // Ensure source remains unchanged (observable)
  EXPECT_TRUE(src.never_nl());
}

// [Construction] CannedOptions-based constructor should leave never_nl() false (observable default)
TEST_F(OptionsNeverNLTest_24, CannedConstructorsDefaultNeverNLFalse_24) {
  // These CannedOptions are part of the public interface per the provided header snippet.
  RE2::Options latin1(RE2::Latin1);
  RE2::Options posix(RE2::POSIX);
  RE2::Options quiet(RE2::Quiet);

  EXPECT_FALSE(latin1.never_nl());
  EXPECT_FALSE(posix.never_nl());
  EXPECT_FALSE(quiet.never_nl());
}

// [Non-regression/Isolation] Changing never_nl should not alter other observable flags
TEST_F(OptionsNeverNLTest_24, SettingNeverNLDoesNotAffectOtherFlags_24) {
  // Capture some other observable flags up-front without asserting their specific values.
  const bool case_sensitive_before = opts_.case_sensitive();
  const bool dot_nl_before = opts_.dot_nl();
  const bool longest_match_before = opts_.longest_match();

  // Change only never_nl
  opts_.set_never_nl(true);
  EXPECT_TRUE(opts_.never_nl());

  // Other observable flags should remain unchanged
  EXPECT_EQ(case_sensitive_before, opts_.case_sensitive());
  EXPECT_EQ(dot_nl_before, opts_.dot_nl());
  EXPECT_EQ(longest_match_before, opts_.longest_match());
}
