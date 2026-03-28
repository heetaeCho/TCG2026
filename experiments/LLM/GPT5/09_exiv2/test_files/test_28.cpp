#include <gtest/gtest.h>
#include "exiv2/types.hpp"  // Assuming this is the correct path for your header file.

namespace Exiv2 {
    
// Test case for the DataBuf class
class DataBufTest : public ::testing::Test {
protected:
    // This is a helper function to create a DataBuf instance with a given size
    DataBuf createDataBufWithSize(size_t size) {
        return DataBuf(size);
    }

    // Test case for DataBuf size method
    TEST_F(DataBufTest, SizeReturnsCorrectSize_28) {
        DataBuf buf(100);
        EXPECT_EQ(buf.size(), 100);  // Check if the size of the DataBuf is correct.
    }

    // Test case for DataBuf empty method
    TEST_F(DataBufTest, EmptyReturnsTrueForZeroSize_29) {
        DataBuf buf(0);
        EXPECT_TRUE(buf.empty());  // Check if the DataBuf is empty for size 0.
    }

    TEST_F(DataBufTest, EmptyReturnsFalseForNonZeroSize_30) {
        DataBuf buf(100);
        EXPECT_FALSE(buf.empty());  // Check if the DataBuf is not empty for non-zero size.
    }

    // Test case for resizing DataBuf
    TEST_F(DataBufTest, ResizeChangesSize_31) {
        DataBuf buf(100);
        buf.resize(200);
        EXPECT_EQ(buf.size(), 200);  // Check if resizing changes the size of the DataBuf.
    }

    // Test case for reset method
    TEST_F(DataBufTest, ResetClearsData_32) {
        DataBuf buf(100);
        buf.reset();
        EXPECT_EQ(buf.size(), 0);  // Check if the reset method clears the data.
    }

    // Test case for reading a single byte
    TEST_F(DataBufTest, ReadWriteUint8_33) {
        DataBuf buf(10);
        buf.write_uint8(0, 255);  // Write value 255 to offset 0
        uint8_t result = buf.read_uint8(0);
        EXPECT_EQ(result, 255);  // Check if the value written is read back correctly.
    }

    // Test case for reading a uint16
    TEST_F(DataBufTest, ReadWriteUint16_34) {
        DataBuf buf(10);
        buf.write_uint16(0, 12345, ByteOrder::little);  // Write value 12345
        uint16_t result = buf.read_uint16(0, ByteOrder::little);
        EXPECT_EQ(result, 12345);  // Check if the value written is read back correctly.
    }

    // Test case for comparing bytes
    TEST_F(DataBufTest, CompareBytesMatches_35) {
        uint8_t data[] = {1, 2, 3, 4, 5};
        DataBuf buf(reinterpret_cast<const byte*>(data), 5);
        int cmpResult = buf.cmpBytes(0, data, 5);
        EXPECT_EQ(cmpResult, 0);  // Expect no difference between the byte buffers.
    }

    // Test case for comparing bytes mismatch
    TEST_F(DataBufTest, CompareBytesMismatch_36) {
        uint8_t data1[] = {1, 2, 3, 4, 5};
        uint8_t data2[] = {5, 4, 3, 2, 1};
        DataBuf buf1(reinterpret_cast<const byte*>(data1), 5);
        DataBuf buf2(reinterpret_cast<const byte*>(data2), 5);
        int cmpResult = buf1.cmpBytes(0, data2, 5);
        EXPECT_NE(cmpResult, 0);  // Expect mismatch between the byte buffers.
    }

    // Exceptional case: trying to read/write out of bounds (assumes these methods handle out-of-bounds access)
    TEST_F(DataBufTest, ReadWriteOutOfBounds_37) {
        DataBuf buf(10);
        EXPECT_THROW(buf.read_uint8(20), std::out_of_range);  // Expect an out-of-range exception for invalid read
        EXPECT_THROW(buf.write_uint8(20, 123), std::out_of_range);  // Expect an out-of-range exception for invalid write
    }
}

}  // namespace Exiv2