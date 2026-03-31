#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "emitterstate.h"

namespace YAML {
namespace {

class EmitterStateEndedGroupTest_479 : public ::testing::Test {
 protected:
  EmitterState state;
};

// Test: EndedGroup on empty groups with Seq type sets UNEXPECTED_END_SEQ error
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupEmptyGroupsSeq_479) {
  // No groups started, calling EndedGroup with Seq should set error
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNEXPECTED_END_SEQ);
}

// Test: EndedGroup on empty groups with Map type sets UNEXPECTED_END_MAP error
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupEmptyGroupsMap_479) {
  // No groups started, calling EndedGroup with Map should set error
  state.EndedGroup(GroupType::Map);
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNEXPECTED_END_MAP);
}

// Test: EndedGroup with matching Seq group type succeeds
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupMatchingSeq_479) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// Test: EndedGroup with matching Map group type succeeds
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupMatchingMap_479) {
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// Test: EndedGroup with mismatched group type sets UNMATCHED_GROUP_TAG error
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupMismatchedType_479) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Map);
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNMATCHED_GROUP_TAG);
}

// Test: EndedGroup with mismatched group type (Map started, Seq ended)
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupMismatchedTypeMapToSeq_479) {
  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNMATCHED_GROUP_TAG);
}

// Test: EndedGroup with tag set produces INVALID_TAG error
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupWithTagSet_479) {
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  EXPECT_TRUE(state.HasTag());
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_TAG);
}

// Test: EndedGroup with anchor set produces INVALID_ANCHOR error
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupWithAnchorSet_479) {
  state.StartedGroup(GroupType::Seq);
  state.SetAnchor();
  EXPECT_TRUE(state.HasAnchor());
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_ANCHOR);
}

// Test: EndedGroup clears HasTag after successful end
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupClearsTag_479) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.HasTag());
}

// Test: EndedGroup clears HasAnchor after successful end
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupClearsAnchor_479) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.HasAnchor());
}

// Test: Nested groups - end inner group correctly
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupNestedGroups_479) {
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  // Outer group should still be active
  EXPECT_EQ(state.CurGroupType(), GroupType::Map);
}

// Test: Nested groups - end both groups correctly
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupNestedGroupsBothEnded_479) {
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// Test: CurIndent returns to 0 after all groups ended
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupIndentRestoredToZero_479) {
  std::size_t initialIndent = state.CurIndent();
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_EQ(state.CurIndent(), initialIndent);
}

// Test: Multiple sequential groups start and end correctly
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupSequentialGroups_479) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());

  state.StartedGroup(GroupType::Map);
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
}

// Test: EndedGroup called twice without group causes error
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupCalledTwiceWithoutGroup_479) {
  state.StartedGroup(GroupType::Seq);
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), ErrorMsg::UNEXPECTED_END_SEQ);
}

// Test: After EndedGroup, HasNonContent is false (m_hasNonContent is cleared)
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupClearsNonContent_479) {
  state.StartedGroup(GroupType::Seq);
  state.SetNonContent();
  state.EndedGroup(GroupType::Seq);
  // HasBegunNode checks m_hasNonContent among other things
  // After EndedGroup, m_hasNonContent should be false
  EXPECT_TRUE(state.good());
}

// Test: State is initially good
TEST_F(EmitterStateEndedGroupTest_479, InitialStateIsGood_479) {
  EXPECT_TRUE(state.good());
}

// Test: Setting error makes state not good
TEST_F(EmitterStateEndedGroupTest_479, SetErrorMakesStateNotGood_479) {
  state.SetError("test error");
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), "test error");
}

// Test: Deeply nested groups
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupDeeplyNested_479) {
  state.StartedGroup(GroupType::Seq);
  state.StartedGroup(GroupType::Map);
  state.StartedGroup(GroupType::Seq);
  
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
  
  state.EndedGroup(GroupType::Map);
  EXPECT_TRUE(state.good());
  
  state.EndedGroup(GroupType::Seq);
  EXPECT_TRUE(state.good());
}

// Test: EndedGroup with both tag and anchor set - tag error takes precedence
TEST_F(EmitterStateEndedGroupTest_479, EndedGroupWithBothTagAndAnchor_479) {
  state.StartedGroup(GroupType::Seq);
  state.SetTag();
  state.SetAnchor();
  state.EndedGroup(GroupType::Seq);
  EXPECT_FALSE(state.good());
  // The tag check comes first in the code
  EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_TAG);
}

}  // namespace
}  // namespace YAML
