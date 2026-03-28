#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



class EmitterStateTest_465 : public ::testing::Test {

protected:

    YAML::EmitterState emitter_state;

};



TEST_F(EmitterStateTest_465, GetDoublePrecision_DefaultValue_465) {

    EXPECT_EQ(emitter_state.GetDoublePrecision(), 0);

}



TEST_F(EmitterStateTest_465, SetAndGetDoublePrecision_NormalOperation_465) {

    ASSERT_TRUE(emitter_state.SetDoublePrecision(17, YAML::FmtScope::GLOBAL));

    EXPECT_EQ(emitter_state.GetDoublePrecision(), 17);

}



TEST_F(EmitterStateTest_465, SetAndGetDoublePrecision_BoundaryConditions_465) {

    ASSERT_TRUE(emitter_state.SetDoublePrecision(0, YAML::FmtScope::LOCAL));

    EXPECT_EQ(emitter_state.GetDoublePrecision(), 0);



    ASSERT_TRUE(emitter_state.SetDoublePrecision(std::numeric_limits<std::size_t>::max(), YAML::FmtScope::GLOBAL));

    EXPECT_EQ(emitter_state.GetDoublePrecision(), std::numeric_limits<std::size_t>::max());

}



TEST_F(EmitterStateTest_465, SetDoublePrecision_ExceptionalCases_465) {

    // Assuming setting an invalid scope could be an exceptional case

    EXPECT_FALSE(emitter_state.SetDoublePrecision(10, static_cast<YAML::FmtScope::value>(-1)));

}
