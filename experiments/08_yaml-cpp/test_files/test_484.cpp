#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_484 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_484, CurGroupChildCount_ReturnsDocCountWhenNoGroups_484) {

    EXPECT_EQ(emitterState.CurGroupChildCount(), 0);

}



TEST_F(EmitterStateTest_484, CurGroupChildCount_ReturnsLastGroupChildCount_484) {

    emitterState.StartedGroup(GroupType::value::BLOCK_MAP);

    EXPECT_EQ(emitterState.CurGroupChildCount(), 0);



    emitterState.StartedScalar();

    emitterState.EndedGroup(GroupType::value::BLOCK_MAP);

    EXPECT_EQ(emitterState.CurGroupChildCount(), 1);

}



TEST_F(EmitterStateTest_484, CurGroupChildCount_ReturnsUpdatedChildCountAfterMultipleScalars_484) {

    emitterState.StartedGroup(GroupType::value::BLOCK_MAP);

    for (int i = 0; i < 5; ++i) {

        emitterState.StartedScalar();

        emitterState.EndedGroup(GroupType::value::SCALAR);

    }

    EXPECT_EQ(emitterState.CurGroupChildCount(), 5);

}



TEST_F(EmitterStateTest_484, CurGroupChildCount_ReturnsZeroAfterEndedDoc_484) {

    emitterState.StartedDoc();

    emitterState.EndedDoc();

    EXPECT_EQ(emitterState.CurGroupChildCount(), 0);

}
