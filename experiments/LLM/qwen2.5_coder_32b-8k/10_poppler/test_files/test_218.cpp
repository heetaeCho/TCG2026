#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Stream.h"



class ASCII85EncoderTest : public ::testing::Test {

protected:

    ASCII85Encoder encoder;

};



TEST_F(ASCII85EncoderTest_NormalOperation_218, IsBinary_ReturnsFalse_218) {

    EXPECT_FALSE(encoder.isBinary(true));

}



TEST_F(ASCII85EncoderTest_BoundaryConditions_218, IsBinary_DefaultParameter_ReturnsFalse_218) {

    EXPECT_FALSE(encoder.isBinary());

}



// Since the function does not have any observable exceptional behavior or external interactions,

// no additional test cases for exceptions or mocks are needed.
