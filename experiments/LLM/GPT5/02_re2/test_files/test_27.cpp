// File: re2_options_set_dot_nl_test.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

//
// We only interact with the public interface (ctor, getters, setters, Copy()).
//

// [Normal] Default should be false.
TEST(RE2OptionsTest_27, DefaultDotNlIsFalse_27) {
  RE2::Options opt;
  EXPECT_FALSE(opt.dot_nl());
}

// [Normal] Setting to true should reflect via the getter.
TEST(RE2OptionsTest_27, SetDotNlTrue_27) {
  RE2::Options opt;
  opt.set_dot_nl(true);
  EXPECT_TRUE(opt.dot_nl());
}

// [Boundary] Toggling true -> false should reflect via the getter.
TEST(RE2OptionsTest_27, ToggleDotNlTrueThenFalse_27) {
  RE2::Options opt;
  opt.set_dot_nl(true);
  ASSERT_TRUE(opt.dot_nl());  // confirm intermediate state
  opt.set_dot_nl(false);
  EXPECT_FALSE(opt.dot_nl());
}

// [Interaction/Independence] Changing never_nl should not implicitly change dot_nl,
// since they are separate options and only observable changes via their own setters/getters.
TEST(RE2OptionsTest_27, DotNlIndependentFromNeverNl_27) {
  RE2::Options opt;

  // Start with known state.
  EXPECT_FALSE(opt.dot_nl());
  EXPECT_FALSE(opt.never_nl());

  // Flip never_nl only; dot_nl should remain unchanged.
  opt.set_never_nl(true);
  EXPECT_TRUE(opt.never_nl());
  EXPECT_FALSE(opt.dot_nl());

  // Now set dot_nl and then flip never_nl back; dot_nl should remain what we set.
  opt.set_dot_nl(true);
  ASSERT_TRUE(opt.dot_nl());
  opt.set_never_nl(false);
  EXPECT_FALSE(opt.never_nl());
  EXPECT_TRUE(opt.dot_nl());
}

// [Copy semantics] Copy() should preserve the dot_nl observable setting.
TEST(RE2OptionsTest_27, CopyPreservesDotNl_27) {
  RE2::Options src;
  src.set_dot_nl(true);   // set a non-default value to verify copy behavior

  RE2::Options dst;
  EXPECT_FALSE(dst.dot_nl()); // sanity: default before copy

  dst.Copy(src);
  EXPECT_TRUE(dst.dot_nl());
}
