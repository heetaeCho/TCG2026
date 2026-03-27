#include <gtest/gtest.h>

#include "Stream.h"



class RGBGrayEncoderTest : public ::testing::Test {

protected:

    RGBGrayEncoder encoder;

};



TEST_F(RGBGrayEncoderTest_240, IsBinary_ReturnsFalse_240) {

    EXPECT_FALSE(encoder.isBinary());

}



// Boundary condition test for the isBinary method

TEST_F(RGBGrayEncoderTest_240, IsBinaryWithLastTrue_ReturnsFalse_240) {

    EXPECT_FALSE(encoder.isBinary(true));

}



TEST_F(RGBGrayEncoderTest_240, IsBinaryWithLastFalse_ReturnsFalse_240) {

    EXPECT_FALSE(encoder.isBinary(false));

}
