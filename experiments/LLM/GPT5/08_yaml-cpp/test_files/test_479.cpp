// File: ./TestProjects/yaml-cpp/test/emitterstate_endedgroup_test.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"
#include "yaml-cpp/exceptions.h"

namespace {

using YAML::EmitterState;
using YAML::ErrorMsg;
using YAML::GroupType;

class EmitterStateEndedGroupTest_479 : public ::testing::Test {
 protected:
  EmitterState state;
};

TEST_F(EmitterStateEndedGroupTest_479, EndSeqWithNoOpenGroupsSetsUnexpectedEndSeqError_479) {
  const std::size_t indent_before = state.CurIndent();

  state.EndedGroup(GroupType::Seq);

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNEXPECTED_END_SEQ);
  EXPECT_EQ(state.CurIndent(), indent_before);
}

TEST_F(EmitterStateEndedGroupTest_479, EndMapWithNoOpenGroupsSetsUnexpectedEndMapError_479) {
  const std::size_t indent_before = state.CurIndent();

  state.EndedGroup(GroupType::Map);

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNEXPECTED_END_MAP);
  EXPECT_EQ(state.CurIndent(), indent_before);
}

TEST_F(EmitterStateEndedGroupTest_479, EndingMismatchedGroupTypeSetsUnmatchedGroupTagError_479) {
  state.StartedGroup(GroupType::Seq);

  state.EndedGroup(GroupType::Map);

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNMATCHED_GROUP_TAG);
}

TEST_F(EmitterStateEndedGroupTest_479, EndingGroupWithTagSetSetsInvalidTagError_479) {
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  ASSERT_TRUE(state.HasTag());

  state.EndedGroup(GroupType::Seq);

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_TAG);
  EXPECT_FALSE(state.HasTag());  // flags are cleared at end of EndedGroup
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateEndedGroupTest_479, EndingGroupWithAnchorSetSetsInvalidAnchorError_479) {
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  ASSERT_TRUE(state.HasAnchor());

  state.EndedGroup(GroupType::Seq);

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_ANCHOR);
  EXPECT_FALSE(state.HasAnchor());  // flags are cleared at end of EndedGroup
  EXPECT_FALSE(state.HasTag());
}

TEST_F(EmitterStateEndedGroupTest_479, EndingGroupWithBothTagAndAnchorSetLastErrorIsInvalidAnchor_479) {
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  state.SetAnchor();
  ASSERT_TRUE(state.HasTag());
  ASSERT_TRUE(state.HasAnchor());

  state.EndedGroup(GroupType::Seq);

  EXPECT_FALSE(state.good());
  // Per implementation: INVALID_TAG is set, then INVALID_ANCHOR is set afterwards.
  EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_ANCHOR);
  EXPECT_FALSE(state.HasTag());
  EXPECT_FALSE(state.HasAnchor());
}

TEST_F(EmitterStateEndedGroupTest_479, SuccessfulEndOfNestedGroupRestoresPreviousIndent_479) {
  // Start an outer group and capture its indent.
  state.StartedGroup(GroupType::Map);
  const std::size_t outer_indent = state.CurIndent();

  // Start an inner group; indent may change (implementation-defined).
  state.StartedGroup(GroupType::Seq);

  // End inner group; indent should return to what it was at the outer group level.
  state.EndedGroup(GroupType::Seq);

  EXPECT_EQ(state.CurIndent(), outer_indent);

  // Cleanup: end outer group as well.
  state.EndedGroup(GroupType::Map);
}

}  // namespace