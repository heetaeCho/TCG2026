#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <cstdint>



using namespace Exiv2;



class ImageTest_1057 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = std::make_unique<BasicIo>();

    Image image {ImageType::jpeg, 0x0F, std::move(io)};

};



TEST_F(ImageTest_1057, ByteSwapNoSwap_1057) {

    uint64_t value = 0x123456789ABCDEF0;

    EXPECT_EQ(image.byteSwap(value, false), value);

}



TEST_F(ImageTest_1057, ByteSwapSwap_1057) {

    uint64_t value = 0x123456789ABCDEF0;

    uint64_t expectedSwappedValue = 0xF0DEBC9A78563412;

    EXPECT_EQ(image.byteSwap(value, true), expectedSwappedValue);

}



TEST_F(ImageTest_1057, ByteSwapBoundaryConditionZero_1057) {

    uint64_t value = 0x0;

    EXPECT_EQ(image.byteSwap(value, true), value);

    EXPECT_EQ(image.byteSwap(value, false), value);

}



TEST_F(ImageTest_1057, ByteSwapBoundaryConditionMaxValue_1057) {

    uint64_t value = UINT64_MAX;

    EXPECT_EQ(image.byteSwap(value, true), value);

    EXPECT_EQ(image.byteSwap(value, false), value);

}
