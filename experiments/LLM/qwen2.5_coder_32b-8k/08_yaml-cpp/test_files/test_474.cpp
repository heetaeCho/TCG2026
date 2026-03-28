#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_474 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_474, NextGroupType_BlockSeq_474) {

    emitterState.SetFlowType(GroupType::Seq, Block, FmtScope::Global);

    EXPECT_EQ(emitterState.NextGroupType(GroupType::Seq), EmitterNodeType::BlockSeq);

}



TEST_F(EmitterStateTest_474, NextGroupType_FlowSeq_474) {

    emitterState.SetFlowType(GroupType::Seq, Flow, FmtScope::Global);

    EXPECT_EQ(emitterState.NextGroupType(GroupType::Seq), EmitterNodeType::FlowSeq);

}



TEST_F(EmitterStateTest_474, NextGroupType_BlockMap_474) {

    emitterState.SetFlowType(GroupType::Map, Block, FmtScope::Global);

    EXPECT_EQ(emitterState.NextGroupType(GroupType::Map), EmitterNodeType::BlockMap);

}



TEST_F(EmitterStateTest_474, NextGroupType_FlowMap_474) {

    emitterState.SetFlowType(GroupType::Map, Flow, FmtScope::Global);

    EXPECT_EQ(emitterState.NextGroupType(GroupType::Map), EmitterNodeType::FlowMap);

}



// Boundary conditions

TEST_F(EmitterStateTest_474, NextGroupType_DefaultBlockSeq_474) {

    // Assuming default flow type for Seq is Block if not explicitly set.

    EXPECT_EQ(emitterState.NextGroupType(GroupType::Seq), EmitterNodeType::BlockSeq);

}



TEST_F(EmitterStateTest_474, NextGroupType_DefaultFlowMap_474) {

    // Assuming default flow type for Map is Flow if not explicitly set.

    EXPECT_EQ(emitterState.NextGroupType(GroupType::Map), EmitterNodeType::FlowMap);

}
