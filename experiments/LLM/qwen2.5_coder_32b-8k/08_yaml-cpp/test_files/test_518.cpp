#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



class EmitterTest_518 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_518, SetStringFormat_NormalOperation_518) {

    EXPECT_TRUE(emitter.SetStringFormat(YAML::EMITTER_MANIP::Auto));

}



TEST_F(EmitterTest_518, SetStringFormat_BoundaryCondition_518) {

    EXPECT_TRUE(emitter.SetStringFormat(YAML::EMITTER_MANIP::SingleQuoted));

    EXPECT_TRUE(emitter.SetStringFormat(YAML::EMITTER_MANIP::DoubleQuoted));

    EXPECT_TRUE(emitter.SetStringFormat(YAML::EMITTER_MANIP::Literal));

    EXPECT_TRUE(emitter.SetStringFormat(YAML::EMITTER_MANIP::Folded));

}



TEST_F(EmitterTest_518, SetStringFormat_ErrorCase_518) {

    // Assuming invalid EMITTER_MANIP values are not defined, thus no specific error case for this function.

    // If there were invalid values, they should be tested here to ensure the function handles them gracefully.

}



TEST_F(EmitterTest_518, SetStringFormat_VerifyStateChange_518) {

    emitter.SetStringFormat(YAML::EMITTER_MANIP::SingleQuoted);

    EXPECT_EQ(emitter.GetStringFormat(), YAML::EMITTER_MANIP::SingleQuoted);



    emitter.SetStringFormat(YAML::EMITTER_MANIP::DoubleQuoted);

    EXPECT_EQ(emitter.GetStringFormat(), YAML::EMITTER_MANIP::DoubleQuoted);

}
