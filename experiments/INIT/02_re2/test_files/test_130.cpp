// File: prog_can_prefix_accel_test_130.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace {

using re2::Prog;

// Test fixture kept simple for clarity/consistency.
class ProgCanPrefixAccelTest_130 : public ::testing::Test {
protected:
  Prog prog_;
};

// [Normal] Freshly constructed Prog should not have prefix acceleration.
TEST_F(ProgCanPrefixAccelTest_130, DefaultIsDisabled_130) {
  EXPECT_FALSE(prog_.can_prefix_accel());
}

// [Normal] Configuring a non-empty prefix should enable prefix acceleration.
// We don't assume how it's implemented—just check the observable effect.
TEST_F(ProgCanPrefixAccelTest_130, NonEmptyPrefixEnables_130) {
  prog_.ConfigurePrefixAccel("abc", /*prefix_foldcase=*/false);
  EXPECT_TRUE(prog_.can_prefix_accel());
}

// [Boundary] Configuring with an empty prefix should leave acceleration disabled.
TEST_F(ProgCanPrefixAccelTest_130, EmptyPrefixKeepsDisabled_130) {
  prog_.ConfigurePrefixAccel("", /*prefix_foldcase=*/false);
  EXPECT_FALSE(prog_.can_prefix_accel());
}

// [Behavioral robustness] Toggling: enable with non-empty, then set empty.
// Observable expectation: enabled → disabled again via public API.
TEST_F(ProgCanPrefixAccelTest_130, ReconfigureEmptyDisablesAfterNonEmpty_130) {
  prog_.ConfigurePrefixAccel("xyz", /*prefix_foldcase=*/true);
  ASSERT_TRUE(prog_.can_prefix_accel()) << "Should enable after non-empty prefix";

  prog_.ConfigurePrefixAccel("", /*prefix_foldcase=*/true);
  EXPECT_FALSE(prog_.can_prefix_accel()) << "Should disable after empty prefix";
}

}  // namespace
