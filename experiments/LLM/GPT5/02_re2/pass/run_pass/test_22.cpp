// File: options_literal_test_22.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class OptionsLiteralTest_22 : public ::testing::Test {};

// [Normal] Default-constructed Options should report literal() == false.
TEST_F(OptionsLiteralTest_22, DefaultLiteralIsFalse_22) {
  RE2::Options opt;
  EXPECT_FALSE(opt.literal());
}

// [Normal] set_literal(true) should make literal() return true, and toggling back works.
TEST_F(OptionsLiteralTest_22, SetLiteralTrueAndBackToFalse_22) {
  RE2::Options opt;

  opt.set_literal(true);
  EXPECT_TRUE(opt.literal());

  opt.set_literal(false);
  EXPECT_FALSE(opt.literal());
}

// [Boundary] Repeatedly setting the same value should be idempotent (observable via getter).
TEST_F(OptionsLiteralTest_22, RepeatedSetLiteralIsIdempotent_22) {
  RE2::Options opt;

  opt.set_literal(true);
  EXPECT_TRUE(opt.literal());
  opt.set_literal(true);
  EXPECT_TRUE(opt.literal());

  opt.set_literal(false);
  EXPECT_FALSE(opt.literal());
  opt.set_literal(false);
  EXPECT_FALSE(opt.literal());
}

// [External interaction/observable effect] Copy() should copy the literal flag from src to dst.
TEST_F(OptionsLiteralTest_22, CopyCopiesLiteralFlag_22) {
  RE2::Options src;
  RE2::Options dst;

  src.set_literal(true);
  dst.set_literal(false);

  dst.Copy(src);
  EXPECT_TRUE(dst.literal());  // matches src
}

// [Boundary/independence] After Copy(), subsequent changes to the source should not affect the destination.
TEST_F(OptionsLiteralTest_22, CopyDoesNotCreateAlias_22) {
  RE2::Options src;
  RE2::Options dst;

  src.set_literal(true);
  dst.Copy(src);
  ASSERT_TRUE(dst.literal());  // verify copy result first

  // Change source; destination should remain as previously copied value.
  src.set_literal(false);
  EXPECT_TRUE(dst.literal());
}
