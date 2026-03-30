#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



namespace Exiv2 {



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image image;



    ImageTest() : io(std::make_unique<BasicIo>()),

                  image(static_cast<ImageType>(0), 0, std::move(io)) {}

};



TEST_F(ImageTest_1058, ByteSwap_NoSwap_1058) {

    uint32_t value = 0x12345678;

    bool bSwap = false;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0x12345678);

}



TEST_F(ImageTest_1058, ByteSwap_Swap_1058) {

    uint32_t value = 0x12345678;

    bool bSwap = true;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0x78563412);

}



TEST_F(ImageTest_1058, ByteSwap_MaxValue_NoSwap_1058) {

    uint32_t value = std::numeric_limits<uint32_t>::max();

    bool bSwap = false;

    EXPECT_EQ(image.byteSwap(value, bSwap), std::numeric_limits<uint32_t>::max());

}



TEST_F(ImageTest_1058, ByteSwap_MaxValue_Swap_1058) {

    uint32_t value = std::numeric_limits<uint32_t>::max();

    bool bSwap = true;

    EXPECT_EQ(image.byteSwap(value, bSwap), std::numeric_limits<uint32_t>::max());

}



TEST_F(ImageTest_1058, ByteSwap_Zero_NoSwap_1058) {

    uint32_t value = 0;

    bool bSwap = false;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0);

}



TEST_F(ImageTest_1058, ByteSwap_Zero_Swap_1058) {

    uint32_t value = 0;

    bool bSwap = true;

    EXPECT_EQ(image.byteSwap(value, bSwap), 0);

}



} // namespace Exiv2
