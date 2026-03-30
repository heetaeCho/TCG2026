#include <gtest/gtest.h>

#include "exiv2/asfvideo.hpp"



using namespace Exiv2;



// Test fixture for AsfVideo::isASFType function

class AsfVideoTest_1560 : public ::testing::Test {

protected:

    byte buf[16];

};



// Test normal operation where the buffer matches the Header GUIDTag

TEST_F(AsfVideoTest_1560, IsASFType_MatchingBuffer_1560) {

    std::array<byte, 8> data4 = {166, 217, 0, 170, 0, 98, 206, 108};

    GUIDTag expectedHeader(1974609456, 26254, 4559, data4);



    // Manually setting buf to match the Header GUIDTag

    memcpy(buf, &expectedHeader, sizeof(GUIDTag));



    EXPECT_TRUE(isASFType(buf));

}



// Test normal operation where the buffer does not match the Header GUIDTag

TEST_F(AsfVideoTest_1560, IsASFType_NonMatchingBuffer_1560) {

    // Setting buf to a different value than the Header GUIDTag

    for (int i = 0; i < 16; ++i) {

        buf[i] = static_cast<byte>(i);

    }



    EXPECT_FALSE(isASFType(buf));

}



// Test boundary condition with all zeros in the buffer

TEST_F(AsfVideoTest_1560, IsASFType_ZeroBuffer_1560) {

    memset(buf, 0, sizeof(buf));



    EXPECT_FALSE(isASFType(buf));

}



// Test boundary condition with all ones in the buffer

TEST_F(AsfVideoTest_1560, IsASFType_OneBuffer_1560) {

    memset(buf, 1, sizeof(buf));



    EXPECT_FALSE(isASFType(buf));

}
