#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1119 : public ::testing::Test {

protected:

    DataBuf dataBuf;

};



TEST_F(DataBufTest_1119, WriteWithinBounds_1119) {

    const size_t bufferSize = 10;

    uint8_t valueToWrite = 42;

    size_t offset = 5;



    dataBuf.alloc(bufferSize);

    EXPECT_NO_THROW(dataBuf.write_uint8(offset, valueToWrite));

    EXPECT_EQ(valueToWrite, dataBuf.read_uint8(offset));

}



TEST_F(DataBufTest_1119, WriteAtBoundary_1119) {

    const size_t bufferSize = 10;

    uint8_t valueToWrite = 42;

    size_t offset = bufferSize - 1;



    dataBuf.alloc(bufferSize);

    EXPECT_NO_THROW(dataBuf.write_uint8(offset, valueToWrite));

    EXPECT_EQ(valueToWrite, dataBuf.read_uint8(offset));

}



TEST_F(DataBufTest_1119, WriteOutOfBounds_1119) {

    const size_t bufferSize = 10;

    uint8_t valueToWrite = 42;

    size_t offset = bufferSize;



    dataBuf.alloc(bufferSize);

    EXPECT_THROW(dataBuf.write_uint8(offset, valueToWrite), std::out_of_range);

}



TEST_F(DataBufTest_1119, WriteAfterResizeLarger_1119) {

    const size_t initialSize = 5;

    const size_t newSize = 10;

    uint8_t valueToWrite = 42;

    size_t offset = newSize - 1;



    dataBuf.alloc(initialSize);

    dataBuf.resize(newSize);

    EXPECT_NO_THROW(dataBuf.write_uint8(offset, valueToWrite));

    EXPECT_EQ(valueToWrite, dataBuf.read_uint8(offset));

}



TEST_F(DataBufTest_1119, WriteAfterResizeSmaller_1119) {

    const size_t initialSize = 10;

    const size_t newSize = 5;

    uint8_t valueToWrite = 42;

    size_t offset = newSize;



    dataBuf.alloc(initialSize);

    dataBuf.resize(newSize);

    EXPECT_THROW(dataBuf.write_uint8(offset, valueToWrite), std::out_of_range);

}



TEST_F(DataBufTest_1119, WriteAfterReset_1119) {

    const size_t bufferSize = 10;

    uint8_t valueToWrite = 42;

    size_t offset = 5;



    dataBuf.alloc(bufferSize);

    dataBuf.reset();

    EXPECT_THROW(dataBuf.write_uint8(offset, valueToWrite), std::out_of_range);

}



TEST_F(DataBufTest_1119, WriteEmptyBuffer_1119) {

    uint8_t valueToWrite = 42;

    size_t offset = 0;



    EXPECT_THROW(dataBuf.write_uint8(offset, valueToWrite), std::out_of_range);

}
