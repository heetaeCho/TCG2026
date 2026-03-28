// TEST_ID: 488
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_488 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_488, RestoreWithoutPriorChangesDoesNotChangeIndent_488) {
  const std::size_t before = state.GetIndent();

  state.RestoreGlobalModifiedSettings();

  EXPECT_EQ(state.GetIndent(), before);
}

TEST_F(EmitterStateTest_488, RestoreAfterSingleGlobalIndentChangeRevertsToOriginal_488) {
  const std::size_t original = state.GetIndent();
  const std::size_t changed = original + 2;

  ASSERT_TRUE(state.SetIndent(changed, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetIndent(), changed);

  state.RestoreGlobalModifiedSettings();

  EXPECT_EQ(state.GetIndent(), original);
}

TEST_F(EmitterStateTest_488, RestoreAfterMultipleGlobalIndentChangesRevertsToOriginal_488) {
  const std::size_t original = state.GetIndent();
  const std::size_t changed1 = original + 2;
  const std::size_t changed2 = original + 4;

  ASSERT_TRUE(state.SetIndent(changed1, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetIndent(), changed1);

  ASSERT_TRUE(state.SetIndent(changed2, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetIndent(), changed2);

  state.RestoreGlobalModifiedSettings();

  EXPECT_EQ(state.GetIndent(), original);
}

TEST_F(EmitterStateTest_488, RestoreIsIdempotentWhenCalledMultipleTimes_488) {
  const std::size_t original = state.GetIndent();
  const std::size_t changed = original + 2;

  ASSERT_TRUE(state.SetIndent(changed, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetIndent(), changed);

  state.RestoreGlobalModifiedSettings();
  const std::size_t after_first_restore = state.GetIndent();

  state.RestoreGlobalModifiedSettings();
  const std::size_t after_second_restore = state.GetIndent();

  EXPECT_EQ(after_first_restore, original);
  EXPECT_EQ(after_second_restore, original);
}

}  // namespace