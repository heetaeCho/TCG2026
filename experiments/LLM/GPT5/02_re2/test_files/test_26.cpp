// File: re2_options_dot_nl_test_26.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

namespace {

using re2::RE2;

class RE2OptionsTest_26 : public ::testing::Test {
protected:
  RE2::Options opts_;
};

// [Normal] Default-constructed Options should report dot_nl() == false.
TEST_F(RE2OptionsTest_26, DefaultDotNlIsFalse_26) {
  EXPECT_FALSE(opts_.dot_nl()) << "dot_nl() should be false by default";
}

// [Normal] set_dot_nl(true) should make dot_nl() return true.
TEST_F(RE2OptionsTest_26, SetDotNlTrue_26) {
  opts_.set_dot_nl(true);
  EXPECT_TRUE(opts_.dot_nl());
}

// [Normal] set_dot_nl(false) should make dot_nl() return false.
TEST_F(RE2OptionsTest_26, SetDotNlFalse_26) {
  opts_.set_dot_nl(true);
  ASSERT_TRUE(opts_.dot_nl());  // precondition
  opts_.set_dot_nl(false);
  EXPECT_FALSE(opts_.dot_nl());
}

// [Boundary/Idempotence] Repeatedly setting the same value should be stable.
TEST_F(RE2OptionsTest_26, SetDotNlIdempotent_26) {
  opts_.set_dot_nl(true);
  EXPECT_TRUE(opts_.dot_nl());
  opts_.set_dot_nl(true);
  EXPECT_TRUE(opts_.dot_nl());

  opts_.set_dot_nl(false);
  EXPECT_FALSE(opts_.dot_nl());
  opts_.set_dot_nl(false);
  EXPECT_FALSE(opts_.dot_nl());
}

// [Isolation from other options] Toggling dot_nl() should not affect never_nl().
TEST_F(RE2OptionsTest_26, DotNlDoesNotAffectNeverNl_26) {
  const bool initial_never_nl = opts_.never_nl();

  opts_.set_dot_nl(true);
  EXPECT_EQ(initial_never_nl, opts_.never_nl());

  opts_.set_dot_nl(false);
  EXPECT_EQ(initial_never_nl, opts_.never_nl());
}

// [Copy semantics] Copy() should preserve the dot_nl() value.
TEST_F(RE2OptionsTest_26, CopyPreservesDotNl_26) {
  RE2::Options src;
  src.set_dot_nl(true);

  RE2::Options dst;
  // Ensure dst starts different to catch improper copy behavior.
  dst.set_dot_nl(false);
  ASSERT_FALSE(dst.dot_nl());

  dst.Copy(src);
  EXPECT_TRUE(dst.dot_nl());
  EXPECT_TRUE(src.dot_nl());  // source remains as set
}

// [Roundtrip] Flipping true -> false -> true should reflect exactly via getter.
TEST_F(RE2OptionsTest_26, DotNlRoundtrip_26) {
  EXPECT_FALSE(opts_.dot_nl());

  opts_.set_dot_nl(true);
  EXPECT_TRUE(opts_.dot_nl());

  opts_.set_dot_nl(false);
  EXPECT_FALSE(opts_.dot_nl());

  opts_.set_dot_nl(true);
  EXPECT_TRUE(opts_.dot_nl());
}

}  // namespace
