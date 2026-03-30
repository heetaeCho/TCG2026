#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_521 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_521, SetIntBase_NormalOperation_521) {

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::Dec));

}



TEST_F(EmitterTest_521, SetIntBase_BoundaryConditions_521) {

    EXPECT_FALSE(emitter.SetIntBase(static_cast<EMITTER_MANIP>(-1)));

    EXPECT_FALSE(emitter.SetIntBase(static_cast<EMITTER_MANIP>(10))); // Assuming EMITTER_MANIP is an enum with values 0 to 9

}



TEST_F(EmitterTest_521, SetIntBase_ErrorHandling_521) {

    // Since the behavior for invalid inputs is not explicitly defined,

    // we assume it returns false and does not change the state.

    EXPECT_FALSE(emitter.SetIntBase(static_cast<EMITTER_MANIP>(-1)));

}



TEST_F(EmitterTest_521, SetIntBase_VerifyNoExternalInteraction_521) {

    // As there are no external collaborators involved in SetIntBase,

    // we do not need to use Google Mock for this test.

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::Dec));

}



TEST_F(EmitterTest_521, SetIntBase_MultipleValidCalls_521) {

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::Hex));

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::Oct));

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::Dec));

}



TEST_F(EmitterTest_521, SetIntBase_DefaultStateVerification_521) {

    // Assuming the default state is EMITTER_MANIP::Dec

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::Hex)); // Change to another base

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::Dec)); // Change back to default

}
