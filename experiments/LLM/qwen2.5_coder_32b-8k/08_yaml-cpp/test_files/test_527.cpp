#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



class EmitterTest_527 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_527, SetFloatPrecision_NormalOperation_527) {

    EXPECT_TRUE(emitter.SetFloatPrecision(10));

}



TEST_F(EmitterTest_527, SetFloatPrecision_BoundaryCondition_Zero_527) {

    EXPECT_TRUE(emitter.SetFloatPrecision(0));

}



TEST_F(EmitterTest_527, SetFloatPrecision_BoundaryCondition_MaxSizeT_527) {

    EXPECT_TRUE(emitter.SetFloatPrecision(std::numeric_limits<std::size_t>::max()));

}



TEST_F(EmitterTest_527, SetFloatPrecision_ExceptionalCase_NegativeValueThroughWrapAround_527) {

    EXPECT_FALSE(emitter.SetFloatPrecision(static_cast<std::size_t>(-1)));

}
