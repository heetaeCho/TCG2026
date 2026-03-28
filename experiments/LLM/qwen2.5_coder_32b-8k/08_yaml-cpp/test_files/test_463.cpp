#include <gtest/gtest.h>

#include <yaml-cpp/src/emitterstate.h>



using namespace YAML;



class EmitterStateTest_463 : public ::testing::Test {

protected:

    EmitterState state;

};



TEST_F(EmitterStateTest_463, DefaultMapKeyFormat_463) {

    EXPECT_EQ(state.GetMapKeyFormat(), EMITTER_MANIP::DEFAULT);

}



TEST_F(EmitterStateTest_463, SetAndGetMapKeyFormatLocalScope_463) {

    ASSERT_TRUE(state.SetMapKeyFormat(EMITTER_MANIP::BLOCK, FmtScope::LOCAL));

    EXPECT_EQ(state.GetMapKeyFormat(), EMITTER_MANIP::BLOCK);

}



TEST_F(EmitterStateTest_463, SetAndGetMapKeyFormatGlobalScope_463) {

    ASSERT_TRUE(state.SetMapKeyFormat(EMITTER_MANIP::FLOW, FmtScope::GLOBAL));

    EXPECT_EQ(state.GetMapKeyFormat(), EMITTER_MANIP::FLOW);

}



TEST_F(EmitterStateTest_463, InvalidSetMapKeyFormat_463) {

    // Assuming there is some invalid format that can be tested

    EXPECT_FALSE(state.SetMapKeyFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::LOCAL));

}
