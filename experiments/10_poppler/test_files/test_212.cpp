#include <gtest/gtest.h>

#include "Stream.h"



class ASCIIHexEncoderTest : public ::testing::Test {

protected:

    ASCIIHexEncoder encoder;

};



TEST_F(ASCIIHexEncoderTest_NormalOperation_212, IsBinary_ReturnsFalseForNonLast_212) {

    EXPECT_FALSE(encoder.isBinary(false));

}



TEST_F(ASCIIHexEncoderTest_NormalOperation_212, IsBinary_ReturnsFalseForLast_212) {

    EXPECT_FALSE(encoder.isBinary(true));

}



TEST_F(ASCIIHexEncoderTest_BoundaryConditions_212, IsBinary_DefaultParameter_212) {

    EXPECT_FALSE(encoder.isBinary());

}
