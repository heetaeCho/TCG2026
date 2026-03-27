#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = nullptr;

    Image image {ImageType::jpeg, 0x1F, std::move(io)};

};



TEST_F(ImageTest_1059, ByteSwap_NoSwap_1059) {

    uint16_t value = 0xABCD;

    bool bSwap = false;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0xABCD);

}



TEST_F(ImageTest_1059, ByteSwap_Swap_1059) {

    uint16_t value = 0xABCD;

    bool bSwap = true;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0xCDAB);

}



TEST_F(ImageTest_1059, ByteSwap_Zero_NoSwap_1059) {

    uint16_t value = 0x0000;

    bool bSwap = false;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0x0000);

}



TEST_F(ImageTest_1059, ByteSwap_Zero_Swap_1059) {

    uint16_t value = 0x0000;

    bool bSwap = true;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0x0000);

}



TEST_F(ImageTest_1059, ByteSwap_MaxValue_NoSwap_1059) {

    uint16_t value = 0xFFFF;

    bool bSwap = false;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0xFFFF);

}



TEST_F(ImageTest_1059, ByteSwap_MaxValue_Swap_1059) {

    uint16_t value = 0xFFFF;

    bool bSwap = true;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0xFFFF);

}
