// TEST_ID: 485
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_485 : public ::testing::Test {
protected:
  YAML::EmitterState state;

  // Avoid depending on specific enumerator names (Map/Seq/etc.).
  // yaml-cpp typically models these as enums (e.g., struct GroupType { enum value {...}; }).
  static constexpr YAML::GroupType::value kGroupA =
      static_cast<YAML::GroupType::value>(1);
  static constexpr YAML::GroupType::value kGroupB =
      static_cast<YAML::GroupType::value>(2);
};

TEST_F(EmitterStateTest_485, CurGroupLongKey_DefaultStateIsFalse_485) {
  // With no observable "current group", CurGroupLongKey() should be safely queryable.
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_485, CurGroupLongKey_DoesNotThrowWhenNoGroup_485) {
  EXPECT_NO_THROW({
    const bool v = state.CurGroupLongKey();
    (void)v;
  });
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_485, CurGroupLongKey_InitiallyFalseAfterStartingGroup_485) {
  ASSERT_NO_THROW(state.StartedGroup(kGroupA));
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_485, CurGroupLongKey_BecomesTrueAfterSetLongKey_485) {
  ASSERT_NO_THROW(state.StartedGroup(kGroupA));

  // Observable behavior via public API: SetLongKey should affect what CurGroupLongKey reports.
  ASSERT_NO_THROW(state.SetLongKey());
  EXPECT_TRUE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_485, CurGroupLongKey_IsScopedToCurrentGroupWithNesting_485) {
  ASSERT_NO_THROW(state.StartedGroup(kGroupA));
  ASSERT_NO_THROW(state.SetLongKey());
  ASSERT_TRUE(state.CurGroupLongKey());  // Outer group longKey should be observable.

  // Start a nested group; the "current group" changes.
  ASSERT_NO_THROW(state.StartedGroup(kGroupB));
  EXPECT_FALSE(state.CurGroupLongKey());  // New group should not inherit longKey by default.

  // Setting longKey now should apply to the current (inner) group.
  ASSERT_NO_THROW(state.SetLongKey());
  EXPECT_TRUE(state.CurGroupLongKey());

  // Ending the inner group should return us to the outer group's state.
  ASSERT_NO_THROW(state.EndedGroup(kGroupB));
  EXPECT_TRUE(state.CurGroupLongKey());

  // Cleanup: end outer group; after that, querying should again be safe and false.
  ASSERT_NO_THROW(state.EndedGroup(kGroupA));
  EXPECT_FALSE(state.CurGroupLongKey());
}

TEST_F(EmitterStateTest_485, CurGroupLongKey_EndingGroupWithoutStartingDoesNotCrash_485) {
  // "Exceptional or error cases (if observable through the interface)":
  // We can't assume it throws; we only assert it doesn't crash and remains queryable.
  EXPECT_NO_THROW(state.EndedGroup(kGroupA));
  EXPECT_FALSE(state.CurGroupLongKey());
}

}  // namespace