#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/types.hpp"

namespace Exiv2 {

class DataBufTest_27 : public ::testing::Test {
protected:
    DataBufTest_27() = default;
    ~DataBufTest_27() override = default;

    // Set up your test fixture and common objects here
    DataBuf dataBuf;
};

TEST_F(DataBufTest_27, DefaultConstructor_27) {
    // Test the default constructor
    DataBuf dataBuf;
    EXPECT_EQ(dataBuf.size(), 0);
    EXPECT_TRUE(dataBuf.empty());
}

TEST_F(DataBufTest_27, ConstructorWithSize_27) {
    // Test constructor with size argument
    size_t size = 10;
    DataBuf dataBuf(size);
    EXPECT_EQ(dataBuf.size(), size);
    EXPECT_FALSE(dataBuf.empty());
}

TEST_F(DataBufTest_27, ConstructorWithData_27) {
    // Test constructor with pointer to data
    uint8_t testData[] = {1, 2, 3, 4};
    DataBuf dataBuf(testData, 4);
    EXPECT_EQ(dataBuf.size(), 4);
    EXPECT_EQ(dataBuf.read_uint8(0), 1);
    EXPECT_EQ(dataBuf.read_uint8(1), 2);
    EXPECT_EQ(dataBuf.read_uint8(2), 3);
    EXPECT_EQ(dataBuf.read_uint8(3), 4);
}

TEST_F(DataBufTest_27, Alloc_27) {
    // Test alloc function
    size_t size = 20;
    dataBuf.alloc(size);
    EXPECT_EQ(dataBuf.size(), size);
    EXPECT_FALSE(dataBuf.empty());
}

TEST_F(DataBufTest_27, Resize_27) {
    // Test resize function
    size_t initialSize = 5;
    dataBuf.alloc(initialSize);
    EXPECT_EQ(dataBuf.size(), initialSize);

    size_t newSize = 10;
    dataBuf.resize(newSize);
    EXPECT_EQ(dataBuf.size(), newSize);
}

TEST_F(DataBufTest_27, Reset_27) {
    // Test reset function
    size_t size = 20;
    dataBuf.alloc(size);
    EXPECT_EQ(dataBuf.size(), size);

    dataBuf.reset();
    EXPECT_EQ(dataBuf.size(), 0);
    EXPECT_TRUE(dataBuf.empty());
}

TEST_F(DataBufTest_27, ReadWriteUint8_27) {
    // Test read and write functions for uint8_t
    dataBuf.alloc(1);
    dataBuf.write_uint8(0, 255);
    EXPECT_EQ(dataBuf.read_uint8(0), 255);
}

TEST_F(DataBufTest_27, ReadWriteUint16_27) {
    // Test read and write functions for uint16_t
    dataBuf.alloc(2);
    dataBuf.write_uint16(0, 12345, ByteOrder::littleEndian);
    EXPECT_EQ(dataBuf.read_uint16(0, ByteOrder::littleEndian), 12345);
}

TEST_F(DataBufTest_27, ReadWriteUint32_27) {
    // Test read and write functions for uint32_t
    dataBuf.alloc(4);
    dataBuf.write_uint32(0, 1234567890, ByteOrder::littleEndian);
    EXPECT_EQ(dataBuf.read_uint32(0, ByteOrder::littleEndian), 1234567890);
}

TEST_F(DataBufTest_27, ReadWriteUint64_27) {
    // Test read and write functions for uint64_t
    dataBuf.alloc(8);
    dataBuf.write_uint64(0, 1234567890123456789, ByteOrder::littleEndian);
    EXPECT_EQ(dataBuf.read_uint64(0, ByteOrder::littleEndian), 1234567890123456789);
}

TEST_F(DataBufTest_27, CmpBytes_27) {
    // Test cmpBytes function
    uint8_t testData[] = {1, 2, 3, 4};
    dataBuf.alloc(4);
    dataBuf.write_uint8(0, 1);
    dataBuf.write_uint8(1, 2);
    dataBuf.write_uint8(2, 3);
    dataBuf.write_uint8(3, 4);
    
    EXPECT_EQ(dataBuf.cmpBytes(0, testData, 4), 0);
    uint8_t wrongData[] = {5, 6, 7, 8};
    EXPECT_NE(dataBuf.cmpBytes(0, wrongData, 4), 0);
}

TEST_F(DataBufTest_27, EndIterator_27) {
    // Test end() iterator functionality
    dataBuf.alloc(10);
    auto it = dataBuf.end();
    EXPECT_EQ(it - dataBuf.begin(), 10);
}

TEST_F(DataBufTest_27, ExceptionalCase_InvalidRead_27) {
    // Test for reading out of bounds (invalid read)
    dataBuf.alloc(5);
    EXPECT_THROW(dataBuf.read_uint8(10), std::out_of_range);
}

}  // namespace Exiv2