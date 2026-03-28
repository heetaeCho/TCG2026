#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest_499 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_499, SetFlowType_Seq_Block_Global_499) {

    EXPECT_TRUE(emitter_state.SetFlowType(GroupType::Seq, Block, FmtScope::Global));

}



TEST_F(EmitterStateTest_499, SetFlowType_Map_Flow_Local_499) {

    EXPECT_TRUE(emitter_state.SetFlowType(GroupType::Map, Flow, FmtScope::Local));

}



TEST_F(EmitterStateTest_499, SetFlowType_Seq_Block_Local_499) {

    EXPECT_TRUE(emitter_state.SetFlowType(GroupType::Seq, Block, FmtScope::Local));

}



TEST_F(EmitterStateTest_499, SetFlowType_Map_Flow_Global_499) {

    EXPECT_TRUE(emitter_state.SetFlowType(GroupType::Map, Flow, FmtScope::Global));

}



TEST_F(EmitterStateTest_499, SetFlowType_Seq_Default_ReturnsFalse_499) {

    EXPECT_FALSE(emitter_state.SetFlowType(GroupType::Seq, Auto, FmtScope::Local));

}



TEST_F(EmitterStateTest_499, SetFlowType_Map_Default_ReturnsFalse_499) {

    EXPECT_FALSE(emitter_state.SetFlowType(GroupType::Map, Auto, FmtScope::Global));

}
