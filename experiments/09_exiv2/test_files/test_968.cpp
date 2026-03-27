#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "pngimage.cpp"



namespace Exiv2 {

    class ZlibToDataBufTest_968 : public ::testing::Test {

    protected:

        byte compressedData[10];

        uLongf compressedLength = sizeof(compressedData);

        DataBuf result;

    };



    TEST_F(ZlibToDataBufTest_968, ValidCompression_968) {

        // Arrange

        const char* originalData = "Exiv2 Test";

        size_t originalLength = strlen(originalData) + 1;



        // Compress the data manually for testing purposes

        uLongf compressedSize = compressBound(originalLength);

        byte compressed[compressedSize];

        compress(compressed, &compressedSize, (const Bytef*)originalData, originalLength);



        // Act

        bool success = zlibToDataBuf(compressed, compressedSize, result);



        // Assert

        EXPECT_TRUE(success);

        EXPECT_EQ(result.size(), originalLength);

        EXPECT_EQ(memcmp(result.c_data(0), originalData, originalLength), 0);

    }



    TEST_F(ZlibToDataBufTest_968, EmptyInput_968) {

        // Arrange

        byte emptyData[1] = {0};

        uLongf zeroLength = 0;



        // Act

        bool success = zlibToDataBuf(emptyData, zeroLength, result);



        // Assert

        EXPECT_TRUE(success);

        EXPECT_EQ(result.size(), 0);

    }



    TEST_F(ZlibToDataBufTest_968, LargeInputFailure_968) {

        // Arrange

        uLongf largeSize = 17 * 1024 * 1024; // Exceeds the limit of 16MB



        // Act

        bool success = zlibToDataBuf(compressedData, largeSize, result);



        // Assert

        EXPECT_FALSE(success);

    }



    TEST_F(ZlibToDataBufTest_968, InvalidCompression_968) {

        // Arrange

        byte invalidData[10] = {0}; // Manually crafted invalid data



        // Act

        bool success = zlibToDataBuf(invalidData, sizeof(invalidData), result);



        // Assert

        EXPECT_FALSE(success);

    }



    TEST_F(ZlibToDataBufTest_968, ExactSizeSuccess_968) {

        // Arrange

        const char* originalData = "Exiv2";

        size_t originalLength = strlen(originalData) + 1;



        // Compress the data manually for testing purposes

        uLongf compressedSize = compressBound(originalLength);

        byte compressed[compressedSize];

        compress(compressed, &compressedSize, (const Bytef*)originalData, originalLength);



        // Act

        bool success = zlibToDataBuf(compressed, compressedSize, result);



        // Assert

        EXPECT_TRUE(success);

        EXPECT_EQ(result.size(), originalLength);

        EXPECT_EQ(memcmp(result.c_data(0), originalData, originalLength), 0);

    }

}
