#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"

#include "yaml-cpp/exceptions.h"



using namespace YAML;



class EmitterStateTest_479 : public ::testing::Test {

protected:

    EmitterState state;

};



TEST_F(EmitterStateTest_479, EndedGroup_EmptyGroups_UnmatchedSeq_479) {

    state.EndedGroup(GroupType::Seq);

    EXPECT_EQ(state.GetLastError(), ErrorMsg::UNEXPECTED_END_SEQ);

}



TEST_F(EmitterStateTest_479, EndedGroup_EmptyGroups_UnmatchedMap_479) {

    state.EndedGroup(GroupType::Map);

    EXPECT_EQ(state.GetLastError(), ErrorMsg::UNEXPECTED_END_MAP);

}



TEST_F(EmitterStateTest_479, EndedGroup_HasTag_Error_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    state.m_groups.push_back(std::move(group));

    state.SetTag();

    state.EndedGroup(GroupType::Seq);

    EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_TAG);

}



TEST_F(EmitterStateTest_479, EndedGroup_HasAnchor_Error_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    state.m_groups.push_back(std::move(group));

    state.SetAnchor();

    state.EndedGroup(GroupType::Seq);

    EXPECT_EQ(state.GetLastError(), ErrorMsg::INVALID_ANCHOR);

}



TEST_F(EmitterStateTest_479, EndedGroup_UnmatchedTag_Error_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    state.m_groups.push_back(std::move(group));

    state.EndedGroup(GroupType::Map);

    EXPECT_EQ(state.GetLastError(), ErrorMsg::UNMATCHED_GROUP_TAG);

}



TEST_F(EmitterStateTest_479, EndedGroup_MatchTag_NoError_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    state.m_groups.push_back(std::move(group));

    state.EndedGroup(GroupType::Seq);

    EXPECT_EQ(state.GetLastError(), "");

}



TEST_F(EmitterStateTest_479, EndedGroup_ReduceIndentation_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    group->indent = 2;

    state.m_groups.push_back(std::move(group));

    state.m_curIndent = 5;

    state.EndedGroup(GroupType::Seq);

    EXPECT_EQ(state.CurIndent(), 3);

}



TEST_F(EmitterStateTest_479, EndedGroup_ClearModifiedSettings_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    group->modifiedSettings.push(std::make_unique<SettingChangeBase>());

    state.m_groups.push_back(std::move(group));

    state.EndedGroup(GroupType::Seq);

    EXPECT_EQ(state.m_modifiedSettings.size(), 0);

}



TEST_F(EmitterStateTest_479, EndedGroup_RestoreGlobalModifiedSettings_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    state.m_groups.push_back(std::move(group));

    SettingChangeBase* change = new SettingChangeBase();

    state.m_globalModifiedSettings.push(std::unique_ptr<SettingChangeBase>(change));

    state.EndedGroup(GroupType::Seq);

    EXPECT_EQ(state.m_globalModifiedSettings.size(), 1);

}



TEST_F(EmitterStateTest_479, EndedGroup_ResetFlags_479) {

    std::unique_ptr<Group> group(new Group(GroupType::Seq));

    state.m_groups.push_back(std::move(group));

    state.SetAnchor();

    state.SetAlias();

    state.SetTag();

    state.EndedGroup(GroupType::Seq);

    EXPECT_FALSE(state.HasAnchor());

    EXPECT_FALSE(state.HasAlias());

    EXPECT_FALSE(state.HasTag());

}
