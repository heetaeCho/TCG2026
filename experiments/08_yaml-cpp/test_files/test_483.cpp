#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_483 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_483, CurGroupIndent_ReturnsZeroWhenNoGroups_483) {

    EXPECT_EQ(emitterState.CurGroupIndent(), 0);

}



TEST_F(EmitterStateTest_483, CurGroupIndent_ReturnsCorrectIndentAfterStartingGroup_483) {

    emitterState.StartedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_EQ(emitterState.CurGroupIndent(), 0); // Assuming default indent is 0



    emitterState.SetIndent(2, FmtScope::value::LOCAL);

    emitterState.StartedGroup(GroupType::value::BLOCK_MAPPING);

    EXPECT_EQ(emitterState.CurGroupIndent(), 2);



    emitterState.EndedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_EQ(emitterState.CurGroupIndent(), 0); // Back to default after ending group

}



TEST_F(EmitterStateTest_483, CurGroupIndent_ReturnsCorrectNestedIndents_483) {

    emitterState.SetIndent(2, FmtScope::value::LOCAL);

    emitterState.StartedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_EQ(emitterState.CurGroupIndent(), 0);



    emitterState.StartedGroup(GroupType::value::BLOCK_MAPPING);

    EXPECT_EQ(emitterState.CurGroupIndent(), 2);



    emitterState.SetIndent(4, FmtScope::value::LOCAL); // Change indent within nested group

    emitterState.StartedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_EQ(emitterState.CurGroupIndent(), 6);



    emitterState.EndedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_EQ(emitterState.CurGroupIndent(), 2);



    emitterState.EndedGroup(GroupType::value::BLOCK_MAPPING);

    EXPECT_EQ(emitterState.CurGroupIndent(), 0);



    emitterState.EndedGroup(GroupType::value::BLOCK_SEQUENCE);

    EXPECT_EQ(emitterState.CurGroupIndent(), 0);

}
