#include <gtest/gtest.h>

#include "emitterstate.h"

#include "setting.h"



using namespace YAML;



class EmitterStateTest_456 : public ::testing::Test {

protected:

    EmitterState emitter_state_;

};



TEST_F(EmitterStateTest_456, GetBoolLengthFormat_DefaultValue_456) {

    EMITTER_MANIP default_value = emitter_state_.GetBoolLengthFormat();

    EXPECT_EQ(default_value, EMITTER_MANIP_DEFAULT); // Assuming a default value of some kind

}



TEST_F(EmitterStateTest_456, SetBoolLengthFormat_NormalOperation_456) {

    bool success = emitter_state_.SetBoolLengthFormat(EMITTER_MANIP_TRUE, FmtScope::LOCAL);

    EXPECT_TRUE(success);



    EMITTER_MANIP format = emitter_state_.GetBoolLengthFormat();

    EXPECT_EQ(format, EMITTER_MANIP_TRUE);

}



TEST_F(EmitterStateTest_456, SetBoolLengthFormat_GlobalScope_456) {

    bool success = emitter_state_.SetBoolLengthFormat(EMITTER_MANIP_FALSE, FmtScope::GLOBAL);

    EXPECT_TRUE(success);



    EMITTER_MANIP format = emitter_state_.GetBoolLengthFormat();

    EXPECT_EQ(format, EMITTER_MANIP_FALSE);

}



TEST_F(EmitterStateTest_456, SetBoolLengthFormat_RestoreGlobalModifiedSettings_456) {

    emitter_state_.SetBoolLengthFormat(EMITTER_MANIP_TRUE, FmtScope::GLOBAL);

    emitter_state_.ClearModifiedSettings();



    emitter_state_.RestoreGlobalModifiedSettings();

    EMITTER_MANIP format = emitter_state_.GetBoolLengthFormat();

    EXPECT_EQ(format, EMITTER_MANIP_TRUE); // Assuming global state was restored

}



TEST_F(EmitterStateTest_456, SetBoolLengthFormat_UnsupportedScope_456) {

    bool success = emitter_state_.SetBoolLengthFormat(EMITTER_MANIP_FALSE, static_cast<FmtScope::value>(99));

    EXPECT_FALSE(success); // Assuming invalid scope returns false

}



TEST_F(EmitterStateTest_456, SetBoolLengthFormat_RestoreDefaultAfterClearModifiedSettings_456) {

    emitter_state_.SetBoolLengthFormat(EMITTER_MANIP_TRUE, FmtScope::LOCAL);

    emitter_state_.ClearModifiedSettings();



    EMITTER_MANIP format = emitter_state_.GetBoolLengthFormat();

    EXPECT_EQ(format, EMITTER_MANIP_DEFAULT); // Assuming default after clearing modifications

}
