#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_453 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_453, GetOutputCharset_DefaultValue_453) {

    EXPECT_EQ(emitter_state.GetOutputCharset(), EMITTER_MANIP::DEFAULT); // Assuming DEFAULT is a valid EMITTER_MANIP value

}



TEST_F(EmitterStateTest_453, SetOutputCharset_ValidValue_LocalScope_453) {

    EXPECT_TRUE(emitter_state.SetOutputCharset(EMITTER_MANIP::UTF8, FmtScope::LOCAL));

    EXPECT_EQ(emitter_state.GetOutputCharset(), EMITTER_MANIP::UTF8);

}



TEST_F(EmitterStateTest_453, SetOutputCharset_ValidValue_GlobalScope_453) {

    EXPECT_TRUE(emitter_state.SetOutputCharset(EMITTER_MANIP::ASCII, FmtScope::GLOBAL));

    EXPECT_EQ(emitter_state.GetOutputCharset(), EMITTER_MANIP::ASCII);

}



TEST_F(EmitterStateTest_453, SetOutputCharset_InvalidValue_453) {

    // Assuming there is a way to test invalid values

    EXPECT_FALSE(emitter_state.SetOutputCharset(static_cast<EMITTER_MANIP>(-1), FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_453, GetIndent_DefaultValue_453) {

    EXPECT_EQ(emitter_state.GetIndent(), 2u); // Assuming default indent is 2

}



TEST_F(EmitterStateTest_453, SetIndent_ValidValue_LocalScope_453) {

    EXPECT_TRUE(emitter_state.SetIndent(4u, FmtScope::LOCAL));

    EXPECT_EQ(emitter_state.GetIndent(), 4u);

}



TEST_F(EmitterStateTest_453, SetIndent_ValidValue_GlobalScope_453) {

    EXPECT_TRUE(emitter_state.SetIndent(6u, FmtScope::GLOBAL));

    EXPECT_EQ(emitter_state.GetIndent(), 6u);

}



TEST_F(EmitterStateTest_453, SetIndent_ZeroValue_453) {

    // Assuming zero indent is not allowed

    EXPECT_FALSE(emitter_state.SetIndent(0u, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_453, Good_DefaultState_453) {

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_453, SetError_Message_Set_453) {

    emitter_state.SetError("Test error");

    EXPECT_FALSE(emitter_state.good());

    EXPECT_EQ(emitter_state.GetLastError(), "Test error");

}
