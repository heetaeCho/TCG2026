#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_482 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_482, CurGroupFlowType_NoGroups_482) {

    EXPECT_EQ(emitterState.CurGroupFlowType(), FlowType::NoType);

}



TEST_F(EmitterStateTest_482, CurGroupFlowType_OneGroup_482) {

    emitterState.StartedGroup(GroupType::Block);

    EXPECT_EQ(emitterState.CurGroupFlowType(), FlowType::NoType); // Default flow type for Block is NoType

    emitterState.EndedGroup(GroupType::Block);

}



TEST_F(EmitterStateTest_482, CurGroupFlowType_MultipleGroups_482) {

    emitterState.StartedGroup(GroupType::Flow);

    emitterState.ForceFlow();

    emitterState.StartedGroup(GroupType::Block); // Nested group

    EXPECT_EQ(emitterState.CurGroupFlowType(), FlowType::NoType); // Inner block group should have NoType by default

    emitterState.EndedGroup(GroupType::Block);

    EXPECT_EQ(emitterState.CurGroupFlowType(), FlowType::Flow); // Back to outer flow group with Flow type

    emitterState.EndedGroup(GroupType::Flow);

}



TEST_F(EmitterStateTest_482, CurGroupFlowType_AfterEndingGroups_482) {

    emitterState.StartedGroup(GroupType::Block);

    emitterState.EndedGroup(GroupType::Block);

    EXPECT_EQ(emitterState.CurGroupFlowType(), FlowType::NoType); // No groups left

}
