// File: options_set_word_boundary_test_35.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

namespace {

using Options = re2::RE2::Options;

// Test fixture (with TEST_ID in the name)
class OptionsWordBoundaryTest_35 : public ::testing::Test {};

//
// Normal operation
//

// Verifies the default observable state for word_boundary.
TEST_F(OptionsWordBoundaryTest_35, DefaultIsFalse_35) {
  Options opt;
  // Observable behavior only: check the public getter.
  EXPECT_FALSE(opt.word_boundary());
}

// Setting to true should be observable via the getter.
TEST_F(OptionsWordBoundaryTest_35, SetTrueThenGet_35) {
  Options opt;
  opt.set_word_boundary(true);
  EXPECT_TRUE(opt.word_boundary());
}

// Setting back to false should be observable via the getter.
TEST_F(OptionsWordBoundaryTest_35, SetFalseAfterTrue_35) {
  Options opt;
  opt.set_word_boundary(true);
  ASSERT_TRUE(opt.word_boundary());  // establish precondition via public API

  opt.set_word_boundary(false);
  EXPECT_FALSE(opt.word_boundary());
}

//
// Boundary conditions (booleans -> both edges, repeated sets)
//

// Repeatedly setting the same value should keep the same observable state.
TEST_F(OptionsWordBoundaryTest_35, IdempotentWhenSettingSameValue_True_35) {
  Options opt;
  opt.set_word_boundary(true);
  EXPECT_TRUE(opt.word_boundary());
  opt.set_word_boundary(true);
  EXPECT_TRUE(opt.word_boundary());
}

// Repeatedly setting the same value (false) should also be stable.
TEST_F(OptionsWordBoundaryTest_35, IdempotentWhenSettingSameValue_False_35) {
  Options opt;
  opt.set_word_boundary(false);
  EXPECT_FALSE(opt.word_boundary());
  opt.set_word_boundary(false);
  EXPECT_FALSE(opt.word_boundary());
}

//
// Interactions with other public functions
//

// Copy should copy the observable word_boundary state from src to dst.
TEST_F(OptionsWordBoundaryTest_35, CopyCopiesWordBoundary_35) {
  Options src;
  src.set_word_boundary(true);

  Options dst;               // default state
  ASSERT_FALSE(dst.word_boundary());  // establish precondition

  dst.Copy(src);             // use only the public Copy API
  EXPECT_TRUE(dst.word_boundary());
}

// After Copy, subsequent changes to the source should not affect the destination.
TEST_F(OptionsWordBoundaryTest_35, CopyCreatesIndependentState_35) {
  Options src;
  src.set_word_boundary(true);

  Options dst;
  dst.Copy(src);
  ASSERT_TRUE(dst.word_boundary());   // copied state is true

  // Change the source; destination should remain as previously copied.
  src.set_word_boundary(false);
  EXPECT_FALSE(src.word_boundary());
  EXPECT_TRUE(dst.word_boundary());
}

}  // namespace
