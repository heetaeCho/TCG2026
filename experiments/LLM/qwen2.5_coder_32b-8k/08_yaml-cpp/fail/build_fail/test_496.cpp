#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_496 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_496, SetIndent_ValidValue_GlobalScope_496) {

    EXPECT_TRUE(emitter_state.SetIndent(2, FmtScope::Global));

}



TEST_F(EmitterStateTest_496, SetIndent_ValidValue_BlockScope_496) {

    EXPECT_TRUE(emitter_state.SetIndent(3, FmtScope::Block));

}



TEST_F(EmitterStateTest_496, SetIndent_MinBoundary_GlobalScope_496) {

    EXPECT_FALSE(emitter_state.SetIndent(1, FmtScope::Global));

}



TEST_F(EmitterStateTest_496, SetIndent_ZeroValue_BlockScope_496) {

    EXPECT_FALSE(emitter_state.SetIndent(0, FmtScope::Block));

}



TEST_F(EmitterStateTest_496, SetIndent_MaxBoundary_GlobalScope_496) {

    EXPECT_TRUE(emitter_state.SetIndent(std::numeric_limits<std::size_t>::max(), FmtScope::Global));

}
