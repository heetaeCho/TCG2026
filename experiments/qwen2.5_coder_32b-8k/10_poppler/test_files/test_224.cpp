#include <gtest/gtest.h>



class RunLengthEncoderTest : public ::testing::Test {

protected:

    RunLengthEncoder encoder;

};



TEST_F(RunLengthEncoderTest_224, IsBinary_ReturnsTrue_224) {

    EXPECT_TRUE(encoder.isBinary(true));

}



TEST_F(RunLengthEncoderTest_224, IsBinary_LastFalse_ReturnsTrue_224) {

    EXPECT_TRUE(encoder.isBinary(false));

}
