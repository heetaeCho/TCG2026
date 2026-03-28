#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_523 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_523, SetMapFormat_NormalOperation_ReturnsTrue_523) {

    EXPECT_TRUE(emitter.SetMapFormat(EMITTER_MANIP::Block));

}



TEST_F(EmitterTest_523, SetMapFormat_BoundaryCondition_Block_ReturnsTrue_523) {

    EXPECT_TRUE(emitter.SetMapFormat(EMITTER_MANIP::Block));

}



TEST_F(EmitterTest_523, SetMapFormat_BoundaryCondition_Flow_ReturnsTrue_523) {

    EXPECT_TRUE(emitter.SetMapFormat(EMITTER_MANIP::Flow));

}



TEST_F(EmitterTest_523, SetMapFormat_ExceptionalCase_UnrecognizedValue_ReturnsFalse_523) {

    EMITTER_MANIP invalid_value = static_cast<EMITTER_MANIP>(-1);

    EXPECT_FALSE(emitter.SetMapFormat(invalid_value));

}
