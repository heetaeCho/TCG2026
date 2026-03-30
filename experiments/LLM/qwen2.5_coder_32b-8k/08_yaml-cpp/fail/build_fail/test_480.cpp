#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_480 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_480, CurGroupNodeType_NoGroups_480) {

    EXPECT_EQ(emitter_state.CurGroupNodeType(), EmitterNodeType::NoType);

}



TEST_F(EmitterStateTest_480, CurGroupNodeType_OneGroup_480) {

    emitter_state.StartedGroup(GroupType::BlockMap);

    EXPECT_NE(emitter_state.CurGroupNodeType(), EmitterNodeType::NoType);

}



TEST_F(EmitterStateTest_480, CurGroupNodeType_MultipleGroups_480) {

    emitter_state.StartedGroup(GroupType::BlockMap);

    emitter_state.StartedGroup(GroupType::BlockSequence);

    EXPECT_NE(emitter_state.CurGroupNodeType(), EmitterNodeType::NoType);

}



TEST_F(EmitterStateTest_480, CurGroupNodeType_EndGroup_ReturnsPrevious_480) {

    emitter_state.StartedGroup(GroupType::BlockMap);

    emitter_state.StartedGroup(GroupType::BlockSequence);

    emitter_state.EndedGroup(GroupType::BlockSequence);

    EXPECT_EQ(emitter_state.CurGroupNodeType(), EmitterState::CurGroupNodeType());

}
