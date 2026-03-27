#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_481 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_481, CurGroupType_NoGroups_481) {

    EXPECT_EQ(emitterState.CurGroupType(), GroupType::NoType);

}



TEST_F(EmitterStateTest_481, CurGroupType_OneGroupAdded_481) {

    emitterState.StartedGroup(GroupType::BlockMap);

    EXPECT_EQ(emitterState.CurGroupType(), GroupType::BlockMap);

}



TEST_F(EmitterStateTest_481, CurGroupType_MultipleGroups_481) {

    emitterState.StartedGroup(GroupType::BlockMap);

    emitterState.StartedGroup(GroupType::FlowSeq);

    EXPECT_EQ(emitterState.CurGroupType(), GroupType::FlowSeq);

}



TEST_F(EmitterStateTest_481, CurGroupType_GroupEnded_481) {

    emitterState.StartedGroup(GroupType::BlockMap);

    emitterState.EndedGroup(GroupType::BlockMap);

    EXPECT_EQ(emitterState.CurGroupType(), GroupType::NoType);

}



TEST_F(EmitterStateTest_481, CurGroupType_MixedOperations_481) {

    emitterState.StartedGroup(GroupType::BlockMap);

    emitterState.StartedGroup(GroupType::FlowSeq);

    emitterState.EndedGroup(GroupType::FlowSeq);

    EXPECT_EQ(emitterState.CurGroupType(), GroupType::BlockMap);

}



TEST_F(EmitterStateTest_481, CurGroupType_EndGroupMismatch_481) {

    // This test assumes that ending a group with a type that doesn't match the current top of stack is an error.

    // However, based on provided interface, we cannot enforce or verify this behavior directly.

    emitterState.StartedGroup(GroupType::BlockMap);

    emitterState.EndedGroup(GroupType::FlowSeq); // Assuming no exception is thrown and it just pops regardless

    EXPECT_EQ(emitterState.CurGroupType(), GroupType::NoType);

}
