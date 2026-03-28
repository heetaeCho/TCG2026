#include <gtest/gtest.h>

#include "FlateEncoder.h"



class FlateEncoderTest : public ::testing::Test {

protected:

    FlateEncoder encoder;

};



TEST_F(FlateEncoderTest_1653, IsBinary_ReturnsTrueForLastBlock_1653) {

    EXPECT_TRUE(encoder.isBinary(true));

}



TEST_F(FlateEncoderTest_1653, IsBinary_ReturnsTrueForNonLastBlock_1653) {

    EXPECT_TRUE(encoder.isBinary(false));

}
