#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace Exiv2 {

    class DataBufTest : public ::testing::Test {
    protected:
        DataBufTest() {}
        ~DataBufTest() override {}

        // Helper method to create a DataBuf object
        DataBuf createDataBuf(size_t size) {
            return DataBuf(size);
        }
    };

    // Test for constructor (DataBuf(size_t size))
    TEST_F(DataBufTest, Constructor_AllocatesMemory_26) {
        size_t size = 1024;
        DataBuf buf = createDataBuf(size);
        ASSERT_EQ(buf.size(), size);
        ASSERT_FALSE(buf.empty());
    }

    // Test for constructor (DataBuf(const byte* pData, size_t size))
    TEST_F(DataBufTest, Constructor_WithPointer_27) {
        const uint8_t data[] = { 1, 2, 3, 4, 5 };
        size_t size = sizeof(data);
        DataBuf buf(data, size);
        
        ASSERT_EQ(buf.size(), size);
        ASSERT_FALSE(buf.empty());
        ASSERT_EQ(buf.read_uint8(0), 1);
    }

    // Test for alloc()
    TEST_F(DataBufTest, Alloc_SetsSize_28) {
        DataBuf buf;
        buf.alloc(2048);
        ASSERT_EQ(buf.size(), 2048);
        ASSERT_FALSE(buf.empty());
    }

    // Test for resize()
    TEST_F(DataBufTest, Resize_ChangesSize_29) {
        size_t initialSize = 512;
        DataBuf buf = createDataBuf(initialSize);
        buf.resize(1024);
        
        ASSERT_EQ(buf.size(), 1024);
        ASSERT_FALSE(buf.empty());
    }

    // Test for reset()
    TEST_F(DataBufTest, Reset_EmptiesDataBuf_30) {
        size_t size = 1024;
        DataBuf buf = createDataBuf(size);
        buf.reset();
        
        ASSERT_EQ(buf.size(), 0);
        ASSERT_TRUE(buf.empty());
    }

    // Test for read_uint8() and write_uint8()
    TEST_F(DataBufTest, ReadWriteUint8_31) {
        size_t size = 1024;
        DataBuf buf = createDataBuf(size);
        buf.write_uint8(100, 42);
        
        uint8_t result = buf.read_uint8(100);
        ASSERT_EQ(result, 42);
    }

    // Test for read_uint16() and write_uint16()
    TEST_F(DataBufTest, ReadWriteUint16_32) {
        size_t size = 1024;
        DataBuf buf = createDataBuf(size);
        ByteOrder byteOrder = ByteOrder::bigEndian;
        buf.write_uint16(100, 12345, byteOrder);
        
        uint16_t result = buf.read_uint16(100, byteOrder);
        ASSERT_EQ(result, 12345);
    }

    // Test for read_uint32() and write_uint32()
    TEST_F(DataBufTest, ReadWriteUint32_33) {
        size_t size = 1024;
        DataBuf buf = createDataBuf(size);
        ByteOrder byteOrder = ByteOrder::littleEndian;
        buf.write_uint32(200, 987654321, byteOrder);
        
        uint32_t result = buf.read_uint32(200, byteOrder);
        ASSERT_EQ(result, 987654321);
    }

    // Test for read_uint64() and write_uint64()
    TEST_F(DataBufTest, ReadWriteUint64_34) {
        size_t size = 1024;
        DataBuf buf = createDataBuf(size);
        ByteOrder byteOrder = ByteOrder::bigEndian;
        uint64_t expectedValue = 1234567890123456789ULL;
        buf.write_uint64(300, expectedValue, byteOrder);
        
        uint64_t result = buf.read_uint64(300, byteOrder);
        ASSERT_EQ(result, expectedValue);
    }

    // Test for cmpBytes()
    TEST_F(DataBufTest, CompareBytes_35) {
        const uint8_t data[] = { 1, 2, 3, 4, 5 };
        size_t size = sizeof(data);
        DataBuf buf(data, size);
        
        uint8_t comparisonData[] = { 1, 2, 3, 4, 5 };
        int cmpResult = buf.cmpBytes(0, comparisonData, sizeof(comparisonData));
        
        ASSERT_EQ(cmpResult, 0);  // Expect 0 for exact match
    }

    // Test for begin() and end()
    TEST_F(DataBufTest, Iterators_36) {
        const uint8_t data[] = { 1, 2, 3, 4, 5 };
        size_t size = sizeof(data);
        DataBuf buf(data, size);
        
        auto beginIt = buf.begin();
        auto endIt = buf.end();
        
        ASSERT_EQ(*beginIt, 1);
        ASSERT_EQ(*(endIt - 1), 5);
    }

    // Test for edge cases in read_uint8()
    TEST_F(DataBufTest, ReadOutOfBounds_37) {
        size_t size = 512;
        DataBuf buf = createDataBuf(size);
        
        ASSERT_THROW(buf.read_uint8(size), std::out_of_range);
    }

    // Test for write beyond allocated memory
    TEST_F(DataBufTest, WriteBeyondAllocatedMemory_38) {
        size_t size = 512;
        DataBuf buf = createDataBuf(size);
        
        ASSERT_THROW(buf.write_uint8(size, 123), std::out_of_range);
    }
}