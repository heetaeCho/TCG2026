// TEST_ID: 496
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

// The library typically exposes this header path.
// If your build uses a different include path, adjust accordingly.
#include "yaml-cpp/emitterstate.h"

namespace {

class EmitterStateTest_496 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  // Avoid depending on specific enumerator names for FmtScope::value.
  static constexpr YAML::FmtScope::value Scope0() {
    return static_cast<YAML::FmtScope::value>(0);
  }
  static constexpr YAML::FmtScope::value Scope1() {
    return static_cast<YAML::FmtScope::value>(1);
  }
};

TEST_F(EmitterStateTest_496, SetIndentRejectsZero_496) {
  const std::size_t before = state.GetIndent();
  EXPECT_FALSE(state.SetIndent(0u, Scope0()));
  EXPECT_EQ(state.GetIndent(), before);
}

TEST_F(EmitterStateTest_496, SetIndentRejectsOne_496) {
  const std::size_t before = state.GetIndent();
  EXPECT_FALSE(state.SetIndent(1u, Scope0()));
  EXPECT_EQ(state.GetIndent(), before);
}

TEST_F(EmitterStateTest_496, SetIndentAcceptsTwoAndUpdatesIndent_Scope0_496) {
  EXPECT_TRUE(state.SetIndent(2u, Scope0()));
  EXPECT_EQ(state.GetIndent(), 2u);
}

TEST_F(EmitterStateTest_496, SetIndentAcceptsLargerValueAndUpdatesIndent_Scope0_496) {
  EXPECT_TRUE(state.SetIndent(8u, Scope0()));
  EXPECT_EQ(state.GetIndent(), 8u);
}

TEST_F(EmitterStateTest_496, InvalidCallDoesNotOverwritePreviousValidIndent_496) {
  ASSERT_TRUE(state.SetIndent(6u, Scope0()));
  ASSERT_EQ(state.GetIndent(), 6u);

  EXPECT_FALSE(state.SetIndent(1u, Scope0()));
  EXPECT_EQ(state.GetIndent(), 6u);

  EXPECT_FALSE(state.SetIndent(0u, Scope0()));
  EXPECT_EQ(state.GetIndent(), 6u);
}

TEST_F(EmitterStateTest_496, SetIndentIsIdempotentForSameValue_496) {
  ASSERT_TRUE(state.SetIndent(4u, Scope0()));
  ASSERT_EQ(state.GetIndent(), 4u);

  EXPECT_TRUE(state.SetIndent(4u, Scope0()));
  EXPECT_EQ(state.GetIndent(), 4u);
}

TEST_F(EmitterStateTest_496, SetIndentAcceptsTwoAndUpdatesIndent_Scope1_496) {
  EXPECT_TRUE(state.SetIndent(2u, Scope1()));
  EXPECT_EQ(state.GetIndent(), 2u);
}

TEST_F(EmitterStateTest_496, SetIndentAcceptsReasonablyLargeValue_496) {
  const std::size_t kLarge = 1000u;
  EXPECT_TRUE(state.SetIndent(kLarge, Scope0()));
  EXPECT_EQ(state.GetIndent(), kLarge);
}

}  // namespace