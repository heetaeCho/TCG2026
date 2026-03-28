// File: re2_options_word_boundary_test.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

//
// Tests target only the public, observable interface:
// - RE2::Options::word_boundary() getter
// - RE2::Options::set_word_boundary(bool) setter
// - RE2::Options::Copy(const Options&)
// No assumptions are made about internal state beyond what can be observed.
//

// Default construction should expose a well-defined initial value via the getter.
TEST(RE2OptionsWordBoundaryTest_34, DefaultIsFalse_34) {
  RE2::Options opt;
  // Observable behavior: initial getter value
  EXPECT_FALSE(opt.word_boundary());
}

// Setting the flag to true should be observable through the getter.
TEST(RE2OptionsWordBoundaryTest_34, SetToTrueReflectsInGetter_34) {
  RE2::Options opt;
  opt.set_word_boundary(true);
  EXPECT_TRUE(opt.word_boundary());
}

// Toggling the flag on and then off should be observable through the getter.
TEST(RE2OptionsWordBoundaryTest_34, ToggleTrueThenFalse_34) {
  RE2::Options opt;
  opt.set_word_boundary(true);
  ASSERT_TRUE(opt.word_boundary());  // ensure it flipped on
  opt.set_word_boundary(false);
  EXPECT_FALSE(opt.word_boundary());
}

// Copy should duplicate the externally observable flag value.
// Further mutations of the source should not retroactively change the copy.
TEST(RE2OptionsWordBoundaryTest_34, CopyPreservesAndDecouplesState_34) {
  RE2::Options src;
  src.set_word_boundary(true);

  RE2::Options dst;
  dst.Copy(src);

  // After copy, both should report the same observed value.
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(src.word_boundary());

  // Changing the source afterward should not affect the destination's observable state.
  src.set_word_boundary(false);
  EXPECT_FALSE(src.word_boundary());   // changed
  EXPECT_TRUE(dst.word_boundary());    // unchanged
}
