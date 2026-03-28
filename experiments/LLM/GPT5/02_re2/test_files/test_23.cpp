// File: ./TestProjects/re2/tests/re2_options_literal_test.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

namespace {

using re2::RE2;

class RE2OptionsTest_23 : public ::testing::Test {
protected:
  RE2::Options opts_;
};

// [Normal] Default value should be false
TEST_F(RE2OptionsTest_23, DefaultLiteralIsFalse_23) {
  EXPECT_FALSE(opts_.literal()) << "literal() should default to false";
}

// [Normal] Setting literal to true reflects via getter
TEST_F(RE2OptionsTest_23, SetLiteralTrue_23) {
  opts_.set_literal(true);
  EXPECT_TRUE(opts_.literal());
}

// [Boundary] Toggling from true back to false reflects via getter
TEST_F(RE2OptionsTest_23, SetLiteralFalseAfterTrue_23) {
  opts_.set_literal(true);
  opts_.set_literal(false);
  EXPECT_FALSE(opts_.literal());
}

// [Boundary] Idempotence: setting the same value twice should keep that value
TEST_F(RE2OptionsTest_23, SetLiteralTrueTwice_Idempotent_23) {
  opts_.set_literal(true);
  opts_.set_literal(true);
  EXPECT_TRUE(opts_.literal());
}

TEST_F(RE2OptionsTest_23, SetLiteralFalseTwice_Idempotent_23) {
  opts_.set_literal(false);
  opts_.set_literal(false);
  EXPECT_FALSE(opts_.literal());
}

// [Interaction] Changing literal should not change unrelated observable options
// We only check via other public getters (e.g., case_sensitive()).
TEST_F(RE2OptionsTest_23, SetLiteralDoesNotAffectCaseSensitivity_23) {
  // Capture initial observable state of an unrelated option.
  bool initial_case_sensitive = opts_.case_sensitive();
  // Change literal a couple of times.
  opts_.set_literal(true);
  opts_.set_literal(false);
  // Verify unrelated option remains the same via its public getter.
  EXPECT_EQ(initial_case_sensitive, opts_.case_sensitive())
      << "set_literal() should not affect case sensitivity";
}

// [External interaction via public API] Copy() should transfer literal setting
TEST_F(RE2OptionsTest_23, CopyTransfersLiteral_23) {
  RE2::Options src;
  RE2::Options dst;

  // Make their initial states intentionally different.
  src.set_literal(true);
  dst.set_literal(false);

  // Act: copy from src to dst
  dst.Copy(src);

  // Assert: observable behavior matches the source after copy
  EXPECT_TRUE(dst.literal());
  EXPECT_EQ(src.literal(), dst.literal());
}

// [Consistency] Copy does not require prior equality of other options;
// we specifically verify literal changes from dst's previous value to src's.
TEST_F(RE2OptionsTest_23, CopyOverridesDestinationLiteral_23) {
  RE2::Options src;
  RE2::Options dst;

  src.set_literal(false);
  dst.set_literal(true);

  dst.Copy(src);

  EXPECT_FALSE(dst.literal());
  EXPECT_EQ(src.literal(), dst.literal());
}

}  // namespace
