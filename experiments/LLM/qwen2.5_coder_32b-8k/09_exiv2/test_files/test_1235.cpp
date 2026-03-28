#include <gtest/gtest.h>

#include <exiv2/types.hpp>

#include "pngchunk_int.hpp"



using namespace Exiv2::Internal;

using namespace Exiv2;



TEST(PngChunkTest_1235, DecodeIHDRChunk_ValidData_1235) {

    uint8_t dataArr[] = {0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x01, 0xF4}; // width and height are both 500

    DataBuf data(dataArr, sizeof(dataArr));

    uint32_t width = 0, height = 0;



    PngChunk::decodeIHDRChunk(data, &width, &height);



    EXPECT_EQ(width, 500);

    EXPECT_EQ(height, 500);

}



TEST(PngChunkTest_1235, DecodeIHDRChunk_ZeroWidth_1235) {

    uint8_t dataArr[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4}; // width is 0, height is 500

    DataBuf data(dataArr, sizeof(dataArr));

    uint32_t width = 0, height = 0;



    PngChunk::decodeIHDRChunk(data, &width, &height);



    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 500);

}



TEST(PngChunkTest_1235, DecodeIHDRChunk_ZeroHeight_1235) {

    uint8_t dataArr[] = {0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00}; // width is 500, height is 0

    DataBuf data(dataArr, sizeof(dataArr));

    uint32_t width = 0, height = 0;



    PngChunk::decodeIHDRChunk(data, &width, &height);



    EXPECT_EQ(width, 500);

    EXPECT_EQ(height, 0);

}



TEST(PngChunkTest_1235, DecodeIHDRChunk_MaxValues_1235) {

    uint8_t dataArr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // both width and height are max uint32_t

    DataBuf data(dataArr, sizeof(dataArr));

    uint32_t width = 0, height = 0;



    PngChunk::decodeIHDRChunk(data, &width, &height);



    EXPECT_EQ(width, 0xFFFFFFFF);

    EXPECT_EQ(height, 0xFFFFFFFF);

}



TEST(PngChunkTest_1235, DecodeIHDRChunk_TooShortData_1235) {

    uint8_t dataArr[] = {0x00, 0x00, 0x01}; // less than 8 bytes of data

    DataBuf data(dataArr, sizeof(dataArr));

    uint32_t width = 0, height = 0;



    EXPECT_THROW(PngChunk::decodeIHDRChunk(data, &width, &height), std::out_of_range);

}



TEST(PngChunkTest_1235, DecodeIHDRChunk_NullOutputWidth_1235) {

    uint8_t dataArr[] = {0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x01, 0xF4};

    DataBuf data(dataArr, sizeof(dataArr));

    uint32_t height = 0;



    EXPECT_THROW(PngChunk::decodeIHDRChunk(data, nullptr, &height), std::invalid_argument);

}



TEST(PngChunkTest_1235, DecodeIHDRChunk_NullOutputHeight_1235) {

    uint8_t dataArr[] = {0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x01, 0xF4};

    DataBuf data(dataArr, sizeof(dataArr));

    uint32_t width = 0;



    EXPECT_THROW(PngChunk::decodeIHDRChunk(data, &width, nullptr), std::invalid_argument);

}
