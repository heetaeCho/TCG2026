#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1062 : public ::testing::Test {

protected:

    DataBuf dataBuffer;

    Image* image;



    void SetUp() override {

        // Initialize a DataBuf with 8 bytes of data

        byte buffer[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

        dataBuffer = DataBuf(buffer, 8);

        image = new Image(imageTypeNone, supportedMetadataExif | supportedMetadataIptc | supportedMetadataXmp, nullptr);

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1062, ByteSwap8_NoSwap_1062) {

    // Test byteSwap8 with no swap (bSwap = false)

    uint64_t result = image->byteSwap8(dataBuffer, 0, false);

    EXPECT_EQ(result, 0x0102030405060708);

}



TEST_F(ImageTest_1062, ByteSwap8_Swap_1062) {

    // Test byteSwap8 with swap (bSwap = true)

    uint64_t result = image->byteSwap8(dataBuffer, 0, true);

    EXPECT_EQ(result, 0x0807060504030201);

}



TEST_F(ImageTest_1062, ByteSwap8_Offset_1062) {

    // Test byteSwap8 with offset

    uint64_t result = image->byteSwap8(dataBuffer, 2, false);

    EXPECT_EQ(result, 0x0304050607080000);



    result = image->byteSwap8(dataBuffer, 2, true);

    EXPECT_EQ(result, 0x0000080706050403);

}



TEST_F(ImageTest_1062, ByteSwap8_BoundaryCondition_1062) {

    // Test byteSwap8 at boundary condition (offset + 8 == size)

    uint64_t result = image->byteSwap8(dataBuffer, 0, false);

    EXPECT_EQ(result, 0x0102030405060708);



    result = image->byteSwap8(dataBuffer, 0, true);

    EXPECT_EQ(result, 0x0807060504030201);

}



TEST_F(ImageTest_1062, ByteSwap8_OutOfBounds_1062) {

    // Test byteSwap8 with out-of-bounds offset

    EXPECT_THROW(image->byteSwap8(dataBuffer, 5, false), std::out_of_range);

    EXPECT_THROW(image->byteSwap8(dataBuffer, 5, true), std::out_of_range);

}
