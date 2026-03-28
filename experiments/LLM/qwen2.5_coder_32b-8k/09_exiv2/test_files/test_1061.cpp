#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



namespace Exiv2 {

    class ImageTest : public ::testing::Test {

    protected:

        DataBuf dataBuf;

        Image image(ImageType::jpeg, 0, nullptr);



        void SetUp() override {

            // Initialize a sample buffer with known values

            byte sampleData[4] = {0x12, 0x34, 0x56, 0x78};

            dataBuf = DataBuf(sampleData, 4);

        }

    };



    TEST_F(ImageTest_1061, ByteSwap4_LittleEndianToBigEndian_1061) {

        uint32_t result = image.byteSwap4(dataBuf, 0, true);

        EXPECT_EQ(result, 0x78563412);

    }



    TEST_F(ImageTest_1061, ByteSwap4_BigEndianToLittleEndian_1061) {

        uint32_t result = image.byteSwap4(dataBuf, 0, false);

        EXPECT_EQ(result, 0x12345678);

    }



    TEST_F(ImageTest_1061, ByteSwap4_OffsetBoundary_1061) {

        byte sampleData[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

        dataBuf = DataBuf(sampleData, 8);

        uint32_t result = image.byteSwap4(dataBuf, 4, true);

        EXPECT_EQ(result, 0xF0DEBC9A);

    }



    TEST_F(ImageTest_1061, ByteSwap4_OutOfBoundsOffset_1061) {

        EXPECT_THROW({

            image.byteSwap4(dataBuf, 1, true);

        }, std::out_of_range); // Assuming out of range throws an exception

    }



    TEST_F(ImageTest_1061, ByteSwap4_ZeroSizeBuffer_1061) {

        dataBuf.reset();

        EXPECT_THROW({

            image.byteSwap4(dataBuf, 0, true);

        }, std::out_of_range); // Assuming out of range throws an exception

    }

}
