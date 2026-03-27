#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_486 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_486, LastIndent_ReturnsZeroWhenNoGroups_486) {

    EXPECT_EQ(emitter_state.LastIndent(), 0);

}



TEST_F(EmitterStateTest_486, LastIndent_ReturnsCorrectValueWithSingleGroup_486) {

    emitter_state.StartedGroup(GroupType::value::BLOCK_MAP); // Assuming BLOCK_MAP is a valid group type

    emitter_state.m_curIndent = 5;

    EXPECT_EQ(emitter_state.LastIndent(), 0);

}



TEST_F(EmitterStateTest_486, LastIndent_ReturnsCorrectValueWithMultipleGroups_486) {

    emitter_state.StartedGroup(GroupType::value::BLOCK_MAP); // Assuming BLOCK_MAP is a valid group type

    emitter_state.m_curIndent = 5;

    emitter_state.StartedGroup(GroupType::value::BLOCK_SEQ); // Assuming BLOCK_SEQ is a valid group type

    emitter_state.m_groups.back()->indent = 3; // Manually setting the indent for testing purposes

    EXPECT_EQ(emitter_state.LastIndent(), 2);

}



TEST_F(EmitterStateTest_486, LastIndent_ReturnsCorrectValueAfterEndingGroup_486) {

    emitter_state.StartedGroup(GroupType::value::BLOCK_MAP); // Assuming BLOCK_MAP is a valid group type

    emitter_state.m_curIndent = 5;

    emitter_state.StartedGroup(GroupType::value::BLOCK_SEQ); // Assuming BLOCK_SEQ is a valid group type

    emitter_state.m_groups.back()->indent = 3; // Manually setting the indent for testing purposes

    emitter_state.EndedGroup(GroupType::value::BLOCK_SEQ);

    EXPECT_EQ(emitter_state.LastIndent(), 0);

}
