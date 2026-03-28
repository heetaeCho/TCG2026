#include <gtest/gtest.h>
#include "emitterstate.h"

namespace YAML {

// Test fixture for Group::NodeType
class GroupNodeTypeTest_466 : public ::testing::Test {
protected:
};

// Test: Seq + Flow => FlowSeq
TEST_F(GroupNodeTypeTest_466, SeqFlowReturnsFlowSeq_466) {
    EmitterState::Group group(GroupType::Seq);
    group.flowType = FlowType::Flow;
    EXPECT_EQ(EmitterNodeType::FlowSeq, group.NodeType());
}

// Test: Seq + Block => BlockSeq
TEST_F(GroupNodeTypeTest_466, SeqBlockReturnsBlockSeq_466) {
    EmitterState::Group group(GroupType::Seq);
    group.flowType = FlowType::Block;
    EXPECT_EQ(EmitterNodeType::BlockSeq, group.NodeType());
}

// Test: Map + Flow => FlowMap
TEST_F(GroupNodeTypeTest_466, MapFlowReturnsFlowMap_466) {
    EmitterState::Group group(GroupType::Map);
    group.flowType = FlowType::Flow;
    EXPECT_EQ(EmitterNodeType::FlowMap, group.NodeType());
}

// Test: Map + Block => BlockMap
TEST_F(GroupNodeTypeTest_466, MapBlockReturnsBlockMap_466) {
    EmitterState::Group group(GroupType::Map);
    group.flowType = FlowType::Block;
    EXPECT_EQ(EmitterNodeType::BlockMap, group.NodeType());
}

// Test: Constructor initializes type correctly for Seq
TEST_F(GroupNodeTypeTest_466, ConstructorWithSeqSetsType_466) {
    EmitterState::Group group(GroupType::Seq);
    // We verify indirectly: setting flowType to Flow should give FlowSeq (confirming type is Seq)
    group.flowType = FlowType::Flow;
    EXPECT_EQ(EmitterNodeType::FlowSeq, group.NodeType());
}

// Test: Constructor initializes type correctly for Map
TEST_F(GroupNodeTypeTest_466, ConstructorWithMapSetsType_466) {
    EmitterState::Group group(GroupType::Map);
    // We verify indirectly: setting flowType to Flow should give FlowMap (confirming type is Map)
    group.flowType = FlowType::Flow;
    EXPECT_EQ(EmitterNodeType::FlowMap, group.NodeType());
}

// Test: Changing flowType after construction changes NodeType result
TEST_F(GroupNodeTypeTest_466, ChangingFlowTypeChangesNodeType_466) {
    EmitterState::Group group(GroupType::Seq);
    group.flowType = FlowType::Flow;
    EXPECT_EQ(EmitterNodeType::FlowSeq, group.NodeType());

    group.flowType = FlowType::Block;
    EXPECT_EQ(EmitterNodeType::BlockSeq, group.NodeType());
}

// Test: NodeType is consistent across multiple calls
TEST_F(GroupNodeTypeTest_466, NodeTypeConsistentAcrossMultipleCalls_466) {
    EmitterState::Group group(GroupType::Map);
    group.flowType = FlowType::Block;
    EXPECT_EQ(EmitterNodeType::BlockMap, group.NodeType());
    EXPECT_EQ(EmitterNodeType::BlockMap, group.NodeType());
    EXPECT_EQ(EmitterNodeType::BlockMap, group.NodeType());
}

}  // namespace YAML
