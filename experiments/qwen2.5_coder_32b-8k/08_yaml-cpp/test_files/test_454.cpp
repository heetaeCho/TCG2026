#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_454 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_454, GetStringFormat_DefaultValue_454) {

    EMITTER_MANIP default_format = emitter_state.GetStringFormat();

    // Assuming a sensible default value for EMITTER_MANIP

    EXPECT_EQ(default_format, EMITTER_MANIP_DEFAULT); // Replace EMITTER_MANIP_DEFAULT with the actual expected default value if known

}



TEST_F(EmitterStateTest_454, SetStringFormat_Success_454) {

    bool result = emitter_state.SetStringFormat(EMITTER_MANIP_SINGLE_QUOTED, FmtScope::local);

    EXPECT_TRUE(result);



    EMITTER_MANIP format = emitter_state.GetStringFormat();

    EXPECT_EQ(format, EMITTER_MANIP_SINGLE_QUOTED);

}



TEST_F(EmitterStateTest_454, SetStringFormat_GlobalScope_Success_454) {

    bool result = emitter_state.SetStringFormat(EMITTER_MANIP_DOUBLE_QUOTED, FmtScope::global);

    EXPECT_TRUE(result);



    EMITTER_MANIP format = emitter_state.GetStringFormat();

    EXPECT_EQ(format, EMITTER_MANIP_DOUBLE_QUOTED);

}



TEST_F(EmitterStateTest_454, SetStringFormat_InvalidValue_Failure_454) {

    bool result = emitter_state.SetStringFormat(static_cast<EMITTER_MANIP>(-1), FmtScope::local);

    EXPECT_FALSE(result);



    EMITTER_MANIP format = emitter_state.GetStringFormat();

    // Assuming the value remains unchanged on failure

    EXPECT_NE(format, static_cast<EMITTER_MANIP>(-1));

}



TEST_F(EmitterStateTest_454, SetStringFormat_BoundaryValue_Success_454) {

    bool result = emitter_state.SetStringFormat(EMITTER_MANIP_HEX, FmtScope::local);

    EXPECT_TRUE(result);



    EMITTER_MANIP format = emitter_state.GetStringFormat();

    EXPECT_EQ(format, EMITTER_MANIP_HEX);

}



TEST_F(EmitterStateTest_454, GetLastIndent_DefaultValue_454) {

    std::size_t indent = emitter_state.LastIndent();

    // Assuming a sensible default value for indentation

    EXPECT_EQ(indent, 0); // Replace 0 with the actual expected default value if known

}



TEST_F(EmitterStateTest_454, SetIndent_Success_454) {

    bool result = emitter_state.SetIndent(2, FmtScope::local);

    EXPECT_TRUE(result);



    std::size_t indent = emitter_state.GetIndent();

    EXPECT_EQ(indent, 2);

}



TEST_F(EmitterStateTest_454, SetIndent_GlobalScope_Success_454) {

    bool result = emitter_state.SetIndent(3, FmtScope::global);

    EXPECT_TRUE(result);



    std::size_t indent = emitter_state.GetIndent();

    EXPECT_EQ(indent, 3);

}



TEST_F(EmitterStateTest_454, SetIndent_ZeroValue_Success_454) {

    bool result = emitter_state.SetIndent(0, FmtScope::local);

    EXPECT_TRUE(result);



    std::size_t indent = emitter_state.GetIndent();

    EXPECT_EQ(indent, 0);

}



TEST_F(EmitterStateTest_454, SetIndent_LargeValue_Success_454) {

    bool result = emitter_state.SetIndent(128, FmtScope::local);

    EXPECT_TRUE(result);



    std::size_t indent = emitter_state.GetIndent();

    EXPECT_EQ(indent, 128);

}
