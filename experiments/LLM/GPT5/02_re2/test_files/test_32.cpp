// File: re2_options_perl_classes_test_32.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

namespace re2 {

class RE2Options_PerlClassesTest_32 : public ::testing::Test {};

// Verifies the default value exposed by the public getter.
TEST_F(RE2Options_PerlClassesTest_32, DefaultIsFalse_32) {
  RE2::Options opt;
  EXPECT_FALSE(opt.perl_classes()) << "Default perl_classes() should be false";
}

// Verifies that setting perl_classes to true is observable via the getter.
TEST_F(RE2Options_PerlClassesTest_32, SetTrueThenGet_32) {
  RE2::Options opt;
  opt.set_perl_classes(true);
  EXPECT_TRUE(opt.perl_classes());
}

// Verifies toggling behavior (true -> false) via the public setter/getter.
TEST_F(RE2Options_PerlClassesTest_32, ToggleTrueThenFalse_32) {
  RE2::Options opt;
  opt.set_perl_classes(true);
  ASSERT_TRUE(opt.perl_classes());
  opt.set_perl_classes(false);
  EXPECT_FALSE(opt.perl_classes());
}

// Verifies that Copy() transfers the perl_classes observable state.
TEST_F(RE2Options_PerlClassesTest_32, CopyCopiesPerlClasses_32) {
  RE2::Options src;
  src.set_perl_classes(true);

  RE2::Options dst;
  ASSERT_FALSE(dst.perl_classes()) << "Baseline: dst should start as false";
  dst.Copy(src);

  EXPECT_TRUE(dst.perl_classes()) << "dst should reflect src after Copy()";
}

// Verifies that calling ParseFlags() (an observable API) does not mutate perl_classes.
// We do not assert any specific flag values; we only check the lack of side effects
// on the perl_classes observable state.
TEST_F(RE2Options_PerlClassesTest_32, ParseFlagsDoesNotChangePerlClasses_32) {
  RE2::Options opt;
  opt.set_perl_classes(true);
  const bool before = opt.perl_classes();

  // Exercise the method; ignore return value as internal details are out of scope.
  (void)opt.ParseFlags();

  EXPECT_EQ(before, opt.perl_classes())
      << "perl_classes() should remain unchanged after ParseFlags()";
}

}  // namespace re2
