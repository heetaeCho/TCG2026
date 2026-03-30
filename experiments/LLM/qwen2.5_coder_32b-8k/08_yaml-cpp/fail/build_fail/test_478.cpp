#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_478 : public ::testing::Test {

protected:

    EmitterState state;

};



TEST_F(EmitterStateTest_478, StartedGroup_DefaultIndentation_478) {

    state.StartedGroup(GroupType::value::Sequence);

    EXPECT_EQ(state.CurGroupIndent(), 0);

}



TEST_F(EmitterStateTest_478, StartedGroup_NestedGroups_478) {

    state.SetIndent(2, FmtScope::value::Block);

    state.StartedGroup(GroupType::value::Mapping);

    state.StartedGroup(GroupType::value::Sequence);

    EXPECT_EQ(state.CurGroupIndent(), 4); // 2 (parent indent) + 2 (default indentation)

}



TEST_F(EmitterStateTest_478, StartedGroup_BlockFlowType_478) {

    state.SetIndent(2, FmtScope::value::Block);

    state.StartedGroup(GroupType::value::Mapping);

    EXPECT_EQ(state.CurGroupFlowType(), FlowType::value::Block);

}



TEST_F(EmitterStateTest_478, StartedGroup_FlowFlowType_478) {

    state.SetIndent(2, FmtScope::value::Block);

    state.StartedGroup(GroupType::value::Sequence);

    EXPECT_EQ(state.CurGroupFlowType(), FlowType::value::Flow);

}



TEST_F(EmitterStateTest_478, StartedGroup_ModifiedSettingsMoved_478) {

    SettingChanges changes;

    changes.push(std::unique_ptr<SettingChangeBase>(new SomeConcreteSettingChange()));

    state.m_modifiedSettings = std::move(changes);



    state.StartedGroup(GroupType::value::Sequence);

    EXPECT_TRUE(state.CurGroupModifiedSettings().empty()); // Assuming modified settings are cleared or moved

}
