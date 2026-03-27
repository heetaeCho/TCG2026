#include <gtest/gtest.h>



// Assuming DeviceNRecoder is part of a namespace or included properly

// Otherwise, ensure to include the necessary header file



class DeviceNRecoderTest : public ::testing::Test {

protected:

    DeviceNRecoder recoder;

};



TEST_F(DeviceNRecoderTest_1669, IsBinary_ReturnsTrue_1669) {

    // Testing normal operation where isBinary should return true

    EXPECT_TRUE(recoder.isBinary());

}



TEST_F(DeviceNRecoderTest_1669, IsBinary_LastFalse_ReturnsTrue_1669) {

    // Testing boundary condition with last parameter as false

    EXPECT_TRUE(recoder.isBinary(false));

}



TEST_F(DeviceNRecoderTest_1669, IsBinary_LastTrue_ReturnsTrue_1669) {

    // Testing boundary condition with last parameter as true

    EXPECT_TRUE(recoder.isBinary(true));

}

```


