#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace ::testing;



class RunLengthEncoderTest : public Test {

protected:

    RunLengthEncoder encoder;

};



TEST_F(RunLengthEncoderTest_223, GetPSFilter_ReturnsEmptyOptional_223) {

    auto result = encoder.getPSFilter(0, "");

    EXPECT_FALSE(result.has_value());

}



TEST_F(RunLengthEncoderTest_223, GetPSFilter_BoundaryCondition_ZeroPsLevel_223) {

    auto result = encoder.getPSFilter(0, "  ");

    EXPECT_FALSE(result.has_value());

}



TEST_F(RunLengthEncoderTest_223, GetPSFilter_BoundaryCondition_NonEmptyIndent_223) {

    auto result = encoder.getPSFilter(1, "indent");

    EXPECT_FALSE(result.has_value());

}
