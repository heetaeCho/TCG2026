#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "emitterstate.h"



namespace YAML {



class EmitterStateTest : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_473, ForceFlowWithEmptyGroups_473) {

    EXPECT_DEATH(emitterState.ForceFlow(), ".*Assertion `!m_groups.empty\\(\\)` failed.");

}



TEST_F(EmitterStateTest_473, ForceFlowWithNonEmptyGroups_473) {

    emitterState.StartedGroup(GroupType::value::BLOCK);

    emitterState.ForceFlow();

    EXPECT_EQ(emitterState.CurGroupFlowType(), FlowType::value::FLOW);

}



}  // namespace YAML
