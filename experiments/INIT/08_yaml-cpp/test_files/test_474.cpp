// TEST_ID: 474
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterStateTest_474 : public ::testing::Test {
protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_474, NextGroupType_SeqBlock_ReturnsBlockSeq_474) {
  // Force sequence flow type to Block and verify NextGroupType reflects it.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Seq, YAML::Block, YAML::FmtScope::Local));
  EXPECT_EQ(YAML::EmitterNodeType::BlockSeq, state.NextGroupType(YAML::GroupType::Seq));
}

TEST_F(EmitterStateTest_474, NextGroupType_SeqFlow_ReturnsFlowSeq_474) {
  // Force sequence flow type to Flow and verify NextGroupType reflects it.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Seq, YAML::Flow, YAML::FmtScope::Local));
  EXPECT_EQ(YAML::EmitterNodeType::FlowSeq, state.NextGroupType(YAML::GroupType::Seq));
}

TEST_F(EmitterStateTest_474, NextGroupType_MapBlock_ReturnsBlockMap_474) {
  // Force map flow type to Block and verify NextGroupType reflects it.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Map, YAML::Block, YAML::FmtScope::Local));
  EXPECT_EQ(YAML::EmitterNodeType::BlockMap, state.NextGroupType(YAML::GroupType::Map));
}

TEST_F(EmitterStateTest_474, NextGroupType_MapFlow_ReturnsFlowMap_474) {
  // Force map flow type to Flow and verify NextGroupType reflects it.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Map, YAML::Flow, YAML::FmtScope::Local));
  EXPECT_EQ(YAML::EmitterNodeType::FlowMap, state.NextGroupType(YAML::GroupType::Map));
}

TEST_F(EmitterStateTest_474, NextGroupType_SeqAndMapIndependentSettings_474) {
  // Boundary-ish: make sure Seq and Map settings don't interfere with each other.
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Seq, YAML::Block, YAML::FmtScope::Local));
  ASSERT_TRUE(state.SetFlowType(YAML::GroupType::Map, YAML::Flow, YAML::FmtScope::Local));

  EXPECT_EQ(YAML::EmitterNodeType::BlockSeq, state.NextGroupType(YAML::GroupType::Seq));
  EXPECT_EQ(YAML::EmitterNodeType::FlowMap, state.NextGroupType(YAML::GroupType::Map));
}

#ifndef NDEBUG
TEST_F(EmitterStateTest_474, NextGroupType_InvalidGroupType_TriggersAssert_474) {
  // Exceptional/error case: implementation asserts on unknown GroupType values.
  const auto badType = static_cast<YAML::GroupType::value>(999);
  EXPECT_DEATH({ (void)state.NextGroupType(badType); }, ".*");
}
#endif

}  // namespace