#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_485, CurGroupLongKey_EmptyGroups_ReturnsFalse_485) {

    EXPECT_FALSE(emitterState.CurGroupLongKey());

}



TEST_F(EmitterStateTest_485, CurGroupLongKey_LongKeySet_ReturnsTrue_485) {

    emitterState.StartedGroup(GroupType::value::BLOCK_MAP);

    emitterState.SetLongKey();

    EXPECT_TRUE(emitterState.CurGroupLongKey());

}



TEST_F(EmitterStateTest_485, CurGroupLongKey_GroupEnded_ReturnsFalse_485) {

    emitterState.StartedGroup(GroupType::value::BLOCK_MAP);

    emitterState.SetLongKey();

    emitterState.EndedGroup(GroupType::value::BLOCK_MAP);

    EXPECT_FALSE(emitterState.CurGroupLongKey());

}



TEST_F(EmitterStateTest_485, CurGroupLongKey_MultipleGroups_ReturnsTrueForCurrentGroup_485) {

    emitterState.StartedGroup(GroupType::value::BLOCK_MAP);

    emitterState.SetLongKey();

    emitterState.StartedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_FALSE(emitterState.CurGroupLongKey());

    emitterState.EndedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_TRUE(emitterState.CurGroupLongKey());

}



TEST_F(EmitterStateTest_485, CurGroupLongKey_GroupStartedWithoutLongKey_ReturnsFalse_485) {

    emitterState.StartedGroup(GroupType::value::BLOCK_MAP);

    EXPECT_FALSE(emitterState.CurGroupLongKey());

}
