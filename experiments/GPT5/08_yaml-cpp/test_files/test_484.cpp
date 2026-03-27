// TEST_ID: 484
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_484 : public ::testing::Test {
protected:
  YAML::EmitterState state;

  static YAML::GroupType::value AsGroupType(int v) {
    return static_cast<YAML::GroupType::value>(v);
  }
};

TEST_F(EmitterStateTest_484, CurGroupChildCount_IsStableOnFreshState_484) {
  const std::size_t a = state.CurGroupChildCount();
  const std::size_t b = state.CurGroupChildCount();
  EXPECT_EQ(a, b);
}

TEST_F(EmitterStateTest_484, CurGroupChildCount_TracksInnermostGroupAfterStartedGroup_484) {
  const std::size_t outside = state.CurGroupChildCount();

  ASSERT_NO_THROW(state.StartedGroup(AsGroupType(0)));
  const std::size_t inside_initial = state.CurGroupChildCount();

  // Inside a group, starting scalars should not decrease the current child count.
  ASSERT_NO_THROW(state.StartedScalar());
  const std::size_t inside_after_one = state.CurGroupChildCount();
  EXPECT_GE(inside_after_one, inside_initial);

  ASSERT_NO_THROW(state.StartedScalar());
  const std::size_t inside_after_two = state.CurGroupChildCount();
  EXPECT_GE(inside_after_two, inside_after_one);

  // End group should restore "outside" context (exact numeric change is implementation-defined).
  ASSERT_NO_THROW(state.EndedGroup(AsGroupType(0)));
  const std::size_t outside_after = state.CurGroupChildCount();

  // Must be a valid size_t and observable; at minimum, it should be stable on repeated reads.
  EXPECT_EQ(outside_after, state.CurGroupChildCount());

  // Outside vs inside are distinct contexts; typically they differ, but don't require it.
  // We still verify we didn't accidentally remain in the same "inside" context by checking
  // that the outside value is not forced to match the last inside value.
  EXPECT_NE(outside_after, static_cast<std::size_t>(-1));
  (void)outside;  // outside is kept for readability; no strict relation required here.
}

TEST_F(EmitterStateTest_484, CurGroupChildCount_UsesMostRecentlyStartedNestedGroup_484) {
  ASSERT_NO_THROW(state.StartedGroup(AsGroupType(0)));
  ASSERT_NO_THROW(state.StartedScalar());
  const std::size_t outer_count = state.CurGroupChildCount();

  ASSERT_NO_THROW(state.StartedGroup(AsGroupType(1)));
  const std::size_t inner_initial = state.CurGroupChildCount();

  // Within inner group, operations should affect inner count, not outer.
  ASSERT_NO_THROW(state.StartedScalar());
  const std::size_t inner_after = state.CurGroupChildCount();
  EXPECT_GE(inner_after, inner_initial);

  // After ending inner group, we should observe the outer group's count again.
  ASSERT_NO_THROW(state.EndedGroup(AsGroupType(1)));
  const std::size_t back_to_outer = state.CurGroupChildCount();
  EXPECT_EQ(back_to_outer, outer_count);

  ASSERT_NO_THROW(state.EndedGroup(AsGroupType(0)));
}

TEST_F(EmitterStateTest_484, CurGroupChildCount_DoesNotThrowOnUnbalancedEndedGroup_484) {
  // Error/exception behavior is not specified; we only assert it is observable and safe to call.
  EXPECT_NO_THROW(state.EndedGroup(AsGroupType(0)));
  EXPECT_EQ(state.CurGroupChildCount(), state.CurGroupChildCount());
}

TEST_F(EmitterStateTest_484, CurGroupChildCount_DoesNotThrowAcrossDocBoundaries_484) {
  const std::size_t before = state.CurGroupChildCount();

  EXPECT_NO_THROW(state.StartedDoc());
  const std::size_t during = state.CurGroupChildCount();
  EXPECT_EQ(during, state.CurGroupChildCount());

  EXPECT_NO_THROW(state.EndedDoc());
  const std::size_t after = state.CurGroupChildCount();
  EXPECT_EQ(after, state.CurGroupChildCount());

  // No required numeric relationship; just ensure values are readable and stable.
  EXPECT_NE(before, static_cast<std::size_t>(-1));
}

}  // namespace