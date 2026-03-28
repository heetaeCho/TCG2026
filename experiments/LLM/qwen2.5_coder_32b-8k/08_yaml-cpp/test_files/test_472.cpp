#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_472 : public ::testing::Test {

protected:

    EmitterState state;

};



TEST_F(EmitterStateTest_472, SetLongKeyWithEmptyGroups_472) {

    // Arrange

    // No groups are started



    // Act & Assert

    EXPECT_DEATH(state.SetLongKey(), ".*m_groups.empty().*");

}



TEST_F(EmitterStateTest_472, SetLongKeyWithNonMapGroup_472) {

    // Arrange

    state.StartedGroup(GroupType::Seq);



    // Act & Assert

    EXPECT_DEATH(state.SetLongKey(), ".*m_groups.back()->type == GroupType::Map.*");

}



TEST_F(EmitterStateTest_472, SetLongKeyWithValidMapGroup_472) {

    // Arrange

    state.StartedGroup(GroupType::Map);



    // Act

    state.SetLongKey();



    // Assert

    EXPECT_TRUE(state.CurGroupLongKey());

}



TEST_F(EmitterStateTest_472, SetLongKeyMultipleTimes_472) {

    // Arrange

    state.StartedGroup(GroupType::Map);

    state.SetLongKey();

    EXPECT_TRUE(state.CurGroupLongKey());



    // Act

    state.SetLongKey();



    // Assert

    EXPECT_TRUE(state.CurGroupLongKey());

}



TEST_F(EmitterStateTest_472, SetLongKeyAndCheckState_472) {

    // Arrange

    state.StartedGroup(GroupType::Map);



    // Act

    state.SetLongKey();



    // Assert

    EXPECT_TRUE(state.CurGroupLongKey());



    // Check that other group properties remain unchanged

    EXPECT_EQ(state.CurGroupIndent(), 0);

    EXPECT_EQ(state.CurGroupChildCount(), 0);

}



TEST_F(EmitterStateTest_472, SetLongKeyNestedGroups_472) {

    // Arrange

    state.StartedGroup(GroupType::Map);

    state.StartedGroup(GroupType::Seq);



    // Act & Assert

    EXPECT_DEATH(state.SetLongKey(), ".*m_groups.back()->type == GroupType::Map.*");



    // Cleanup

    state.EndedGroup(GroupType::Seq);

    state.EndedGroup(GroupType::Map);

}



TEST_F(EmitterStateTest_472, SetLongKeyAndEndGroup_472) {

    // Arrange

    state.StartedGroup(GroupType::Map);



    // Act

    state.SetLongKey();

    state.EndedGroup(GroupType::Map);



    // Assert

    EXPECT_FALSE(state.CurGroupLongKey());

}
