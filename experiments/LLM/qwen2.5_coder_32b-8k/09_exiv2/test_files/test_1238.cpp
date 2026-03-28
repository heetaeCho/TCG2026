#include <gtest/gtest.h>

#include "pngchunk_int.hpp"

#include "types.hpp"

#include "error.hpp"



using namespace Exiv2::Internal;

using namespace Exiv2;



TEST_F(PngChunkTest_1238, KeyTXTChunk_NormalOperation_1238) {

    DataBuf data("key\0value", 9);

    bool stripHeader = false;

    DataBuf result = PngChunk().keyTXTChunk(data, stripHeader);

    EXPECT_EQ(result.size(), 3u);

    EXPECT_STREQ(reinterpret_cast<const char*>(result.c_data()), "key");

}



TEST_F(PngChunkTest_1238, KeyTXTChunk_NormalOperation_WithStripHeader_1238) {

    DataBuf data("headerkey\0value", 15);

    bool stripHeader = true;

    DataBuf result = PngChunk().keyTXTChunk(data, stripHeader);

    EXPECT_EQ(result.size(), 4u);

    EXPECT_STREQ(reinterpret_cast<const char*>(result.c_data()), "key");

}



TEST_F(PngChunkTest_1238, KeyTXTChunk_EmptyData_1238) {

    DataBuf data("", 0);

    bool stripHeader = false;

    EXPECT_THROW(PngChunk().keyTXTChunk(data, stripHeader), Error);

}



TEST_F(PngChunkTest_1238, KeyTXTChunk_DataTooShort_1238) {

    DataBuf data("short", 5);

    bool stripHeader = true;

    EXPECT_THROW(PngChunk().keyTXTChunk(data, stripHeader), Error);

}



TEST_F(PngChunkTest_1238, KeyTXTChunk_NoNullTerminator_1238) {

    DataBuf data("no\0nullterminator", 15);

    bool stripHeader = false;

    EXPECT_THROW(PngChunk().keyTXTChunk(data, stripHeader), Error);

}



TEST_F(PngChunkTest_1238, KeyTXTChunk_NoNullTerminator_WithStripHeader_1238) {

    DataBuf data("headerno\0nullterminator", 23);

    bool stripHeader = true;

    EXPECT_THROW(PngChunk().keyTXTChunk(data, stripHeader), Error);

}
