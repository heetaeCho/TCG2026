#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



namespace {



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    DataBuf dataBuf;

    Image* image;



    void SetUp() override {

        // Initialize a DataBuf with some sample data

        byte testData[] = {0x12, 0x34};

        dataBuf = DataBuf(testData, sizeof(testData));

        

        // Create an instance of Image (using a minimal mock for BasicIo)

        image = new Image(imageTypeNone, 0, nullptr);

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1060, ByteSwap2_NoSwap_1060) {

    bool bSwap = false;

    uint16_t result = image->byteSwap2(dataBuf, 0, bSwap);

    EXPECT_EQ(result, 0x1234);

}



TEST_F(ImageTest_1060, ByteSwap2_Swap_1060) {

    bool bSwap = true;

    uint16_t result = image->byteSwap2(dataBuf, 0, bSwap);

    EXPECT_EQ(result, 0x3412);

}



TEST_F(ImageTest_1060, ByteSwap2_OffsetBoundary_1060) {

    bool bSwap = false;

    dataBuf.write_uint8(0, 0xAB);

    dataBuf.write_uint8(1, 0xCD);



    uint16_t result = image->byteSwap2(dataBuf, 1, bSwap);

    EXPECT_EQ(result, 0xCD00);

}



TEST_F(ImageTest_1060, ByteSwap2_OutOfBounds_1060) {

    bool bSwap = false;

    EXPECT_THROW(image->byteSwap2(dataBuf, 10, bSwap), std::out_of_range);

}



} // namespace
