// TEST_ID: 466
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateGroupNodeTypeTest_466 : public ::testing::Test {
protected:
  using Group = YAML::EmitterState::Group;
};

TEST_F(EmitterStateGroupNodeTypeTest_466, SeqFlowReturnsFlowSeq_466) {
  Group g(YAML::GroupType::Seq);
  g.type = YAML::GroupType::Seq;
  g.flowType = YAML::FlowType::Flow;

  const auto beforeType = g.type;
  const auto beforeFlow = g.flowType;

  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::FlowSeq);

  // Verify no visible state mutation (observable through public members).
  EXPECT_EQ(g.type, beforeType);
  EXPECT_EQ(g.flowType, beforeFlow);
}

TEST_F(EmitterStateGroupNodeTypeTest_466, SeqBlockReturnsBlockSeq_466) {
  Group g(YAML::GroupType::Seq);
  g.type = YAML::GroupType::Seq;
  g.flowType = YAML::FlowType::Block;

  const auto beforeType = g.type;
  const auto beforeFlow = g.flowType;

  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::BlockSeq);

  EXPECT_EQ(g.type, beforeType);
  EXPECT_EQ(g.flowType, beforeFlow);
}

TEST_F(EmitterStateGroupNodeTypeTest_466, MapFlowReturnsFlowMap_466) {
  Group g(YAML::GroupType::Map);
  g.type = YAML::GroupType::Map;
  g.flowType = YAML::FlowType::Flow;

  const auto beforeType = g.type;
  const auto beforeFlow = g.flowType;

  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::FlowMap);

  EXPECT_EQ(g.type, beforeType);
  EXPECT_EQ(g.flowType, beforeFlow);
}

TEST_F(EmitterStateGroupNodeTypeTest_466, MapBlockReturnsBlockMap_466) {
  Group g(YAML::GroupType::Map);
  g.type = YAML::GroupType::Map;
  g.flowType = YAML::FlowType::Block;

  const auto beforeType = g.type;
  const auto beforeFlow = g.flowType;

  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::BlockMap);

  EXPECT_EQ(g.type, beforeType);
  EXPECT_EQ(g.flowType, beforeFlow);
}

TEST_F(EmitterStateGroupNodeTypeTest_466, RepeatedCallsAreConsistentAcrossStateChanges_466) {
  Group g(YAML::GroupType::Seq);

  g.type = YAML::GroupType::Seq;
  g.flowType = YAML::FlowType::Flow;
  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::FlowSeq);
  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::FlowSeq);

  // Change only the observable inputs and verify the observable output changes accordingly.
  g.flowType = YAML::FlowType::Block;
  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::BlockSeq);

  g.type = YAML::GroupType::Map;
  g.flowType = YAML::FlowType::Flow;
  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::FlowMap);

  g.flowType = YAML::FlowType::Block;
  EXPECT_EQ(g.NodeType(), YAML::EmitterNodeType::BlockMap);
}

// Exceptional / error case (observable via assert). This is only meaningful in debug builds.
#if GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
TEST_F(EmitterStateGroupNodeTypeTest_466, InvalidGroupTypeTriggersAssertDeath_466) {
  Group g(YAML::GroupType::Seq);

  // Force an invalid enum value to exercise the defensive assert in NodeType().
  g.type = static_cast<YAML::GroupType::value>(-1);
  g.flowType = YAML::FlowType::Flow;

  EXPECT_DEATH({ (void)g.NodeType(); }, "");
}
#endif

}  // namespace