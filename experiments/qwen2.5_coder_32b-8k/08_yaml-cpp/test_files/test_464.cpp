#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



using namespace YAML;



class EmitterStateTest_464 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_464, GetFloatPrecision_DefaultValue_464) {

    EXPECT_EQ(emitter_state.GetFloatPrecision(), 0);

}



TEST_F(EmitterStateTest_464, SetFloatPrecision_NormalOperation_464) {

    ASSERT_TRUE(emitter_state.SetFloatPrecision(10, FmtScope::value::BLOCK_IN));

    EXPECT_EQ(emitter_state.GetFloatPrecision(), 10);

}



TEST_F(EmitterStateTest_464, SetFloatPrecision_BoundaryCondition_Zero_464) {

    ASSERT_TRUE(emitter_state.SetFloatPrecision(0, FmtScope::value::BLOCK_IN));

    EXPECT_EQ(emitter_state.GetFloatPrecision(), 0);

}



TEST_F(EmitterStateTest_464, SetFloatPrecision_BoundaryCondition_MaxSizeT_464) {

    ASSERT_TRUE(emitter_state.SetFloatPrecision(std::numeric_limits<std::size_t>::max(), FmtScope::value::BLOCK_IN));

    EXPECT_EQ(emitter_state.GetFloatPrecision(), std::numeric_limits<std::size_t>::max());

}



TEST_F(EmitterStateTest_464, SetFloatPrecision_ErrorCase_ReturnFalse_464) {

    // Assuming invalid scope would cause the function to return false

    bool result = emitter_state.SetFloatPrecision(10, static_cast<FmtScope::value>(-1));

    EXPECT_FALSE(result);

}
