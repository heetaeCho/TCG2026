// File: re2_options_never_nl_test.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

// A simple fixture in case future tests need shared setup.
class OptionsNeverNlTest : public ::testing::Test {};

// Verifies the default value exposed by the public getter.
TEST_F(OptionsNeverNlTest, DefaultNeverNlIsFalse_25) {
  RE2::Options opt;
  EXPECT_FALSE(opt.never_nl()) << "Default never_nl() should be false";
}

// Verifies that setting never_nl to true is observable via the getter.
TEST_F(OptionsNeverNlTest, SetNeverNlTrue_25) {
  RE2::Options opt;
  opt.set_never_nl(true);
  EXPECT_TRUE(opt.never_nl());
}

// Verifies that toggling back to false is observable via the getter.
TEST_F(OptionsNeverNlTest, ToggleNeverNlTrueThenFalse_25) {
  RE2::Options opt;
  opt.set_never_nl(true);
  ASSERT_TRUE(opt.never_nl()) << "Precondition check";
  opt.set_never_nl(false);
  EXPECT_FALSE(opt.never_nl());
}

// Verifies that repeated sets to the same value keep behavior stable (idempotence).
TEST_F(OptionsNeverNlTest, RepeatedSetsAreIdempotent_25) {
  RE2::Options opt;

  // Repeatedly set to true
  opt.set_never_nl(true);
  opt.set_never_nl(true);
  EXPECT_TRUE(opt.never_nl());

  // Repeatedly set to false
  opt.set_never_nl(false);
  opt.set_never_nl(false);
  EXPECT_FALSE(opt.never_nl());
}

// Verifies that Copy() reproduces the observable never_nl state in the destination.
TEST_F(OptionsNeverNlTest, CopyPropagatesNeverNl_25) {
  RE2::Options src;
  RE2::Options dst;

  // Set in source and copy over
  src.set_never_nl(true);
  dst.Copy(src);
  EXPECT_TRUE(dst.never_nl());

  // Change source again; destination should reflect the copied snapshot (not live linkage).
  src.set_never_nl(false);
  EXPECT_TRUE(dst.never_nl()) << "dst should keep the copied value after src changes";
}

// (Optional) Sanity check: Copy() when source has default value.
TEST_F(OptionsNeverNlTest, CopyDefaultKeepsFalse_25) {
  RE2::Options src;  // default never_nl() expected false (observed via getter)
  RE2::Options dst;
  dst.set_never_nl(true);   // ensure it actually changes
  ASSERT_TRUE(dst.never_nl());

  dst.Copy(src);
  EXPECT_FALSE(dst.never_nl());
}
