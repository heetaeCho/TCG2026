#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "basicio.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock for BasicIo
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class IoWrapperTest_2157 : public ::testing::Test {
protected:
    MockBasicIo mockIo_;
    byte header_[4] = {0x49, 0x49, 0x2A, 0x00};
};

// Test construction with valid header
TEST_F(IoWrapperTest_2157, ConstructWithValidHeader_2157) {
    OffsetWriter pow;
    EXPECT_NO_THROW(IoWrapper wrapper(mockIo_, header_, sizeof(header_), &pow));
}

// Test construction with nullptr header sets wroteHeader to true (header won't be written)
TEST_F(IoWrapperTest_2157, ConstructWithNullHeader_2157) {
    OffsetWriter pow;
    EXPECT_NO_THROW(IoWrapper wrapper(mockIo_, nullptr, 4, &pow));
}

// Test construction with size 0 sets wroteHeader to true
TEST_F(IoWrapperTest_2157, ConstructWithZeroSize_2157) {
    OffsetWriter pow;
    EXPECT_NO_THROW(IoWrapper wrapper(mockIo_, header_, 0, &pow));
}

// Test construction with nullptr OffsetWriter
TEST_F(IoWrapperTest_2157, ConstructWithNullOffsetWriter_2157) {
    EXPECT_NO_THROW(IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr));
}

// Test construction with both null header and null OffsetWriter
TEST_F(IoWrapperTest_2157, ConstructWithNullHeaderAndNullOffsetWriter_2157) {
    EXPECT_NO_THROW(IoWrapper wrapper(mockIo_, nullptr, 0, nullptr));
}

// Test write with valid data - first write should include header when header is provided
TEST_F(IoWrapperTest_2157, WriteWithValidDataAndHeader_2157) {
    OffsetWriter pow;
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), &pow);

    byte data[] = {0x01, 0x02, 0x03};
    
    // The first write should write the header first, then the data
    // We expect at least one write call to the underlying io
    EXPECT_CALL(mockIo_, write(::testing::_, ::testing::_))
        .WillRepeatedly(::testing::ReturnArg<1>());
    
    size_t result = wrapper.write(data, sizeof(data));
    // Result should reflect something was written
    EXPECT_GT(result, 0u);
}

// Test write when no header (nullptr header) - should just pass through
TEST_F(IoWrapperTest_2157, WriteWithNoHeader_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    byte data[] = {0x01, 0x02, 0x03};
    
    EXPECT_CALL(mockIo_, write(::testing::_, 3))
        .WillOnce(::testing::Return(3));
    
    size_t result = wrapper.write(data, sizeof(data));
    EXPECT_EQ(result, 3u);
}

// Test write with zero count
TEST_F(IoWrapperTest_2157, WriteZeroBytes_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    byte data[] = {0x01};
    
    EXPECT_CALL(mockIo_, write(::testing::_, 0))
        .WillOnce(::testing::Return(0));
    
    size_t result = wrapper.write(data, 0);
    EXPECT_EQ(result, 0u);
}

// Test putb delegates to underlying io (when header already written)
TEST_F(IoWrapperTest_2157, PutbWithNoHeader_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    EXPECT_CALL(mockIo_, putb(0x42))
        .WillOnce(::testing::Return(0x42));
    
    int result = wrapper.putb(0x42);
    EXPECT_EQ(result, 0x42);
}

// Test putb when header needs to be written first
TEST_F(IoWrapperTest_2157, PutbWithHeader_2157) {
    OffsetWriter pow;
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), &pow);

    // First putb should trigger header write
    EXPECT_CALL(mockIo_, write(::testing::_, ::testing::_))
        .WillRepeatedly(::testing::ReturnArg<1>());
    EXPECT_CALL(mockIo_, putb(0x55))
        .WillOnce(::testing::Return(0x55));
    
    int result = wrapper.putb(0x55);
    EXPECT_EQ(result, 0x55);
}

// Test setTarget with valid OffsetWriter
TEST_F(IoWrapperTest_2157, SetTargetWithOffsetWriter_2157) {
    OffsetWriter pow;
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), &pow);

    // setTarget should not throw when OffsetWriter is provided
    EXPECT_NO_THROW(wrapper.setTarget(0, 100));
}

// Test setTarget with null OffsetWriter - should be safe (no-op)
TEST_F(IoWrapperTest_2157, SetTargetWithNullOffsetWriter_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    // Should not crash when OffsetWriter is null
    EXPECT_NO_THROW(wrapper.setTarget(0, 100));
}

// Test multiple writes - header should only be written once
TEST_F(IoWrapperTest_2157, MultipleWritesHeaderOnlyOnce_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    byte data1[] = {0x01, 0x02};
    byte data2[] = {0x03, 0x04};
    
    EXPECT_CALL(mockIo_, write(::testing::_, 2))
        .Times(2)
        .WillRepeatedly(::testing::Return(2));
    
    size_t result1 = wrapper.write(data1, sizeof(data1));
    size_t result2 = wrapper.write(data2, sizeof(data2));
    
    EXPECT_EQ(result1, 2u);
    EXPECT_EQ(result2, 2u);
}

// Test write with large data
TEST_F(IoWrapperTest_2157, WriteLargeData_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    std::vector<byte> largeData(10000, 0xAB);
    
    EXPECT_CALL(mockIo_, write(::testing::_, 10000))
        .WillOnce(::testing::Return(10000));
    
    size_t result = wrapper.write(largeData.data(), largeData.size());
    EXPECT_EQ(result, 10000u);
}

// Test putb with boundary byte values
TEST_F(IoWrapperTest_2157, PutbBoundaryValues_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    // Test with 0x00
    EXPECT_CALL(mockIo_, putb(0x00))
        .WillOnce(::testing::Return(0x00));
    EXPECT_EQ(wrapper.putb(0x00), 0x00);

    // Test with 0xFF
    EXPECT_CALL(mockIo_, putb(0xFF))
        .WillOnce(::testing::Return(0xFF));
    EXPECT_EQ(wrapper.putb(0xFF), 0xFF);
}

// Test write followed by putb
TEST_F(IoWrapperTest_2157, WriteFollowedByPutb_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    byte data[] = {0x01};
    
    EXPECT_CALL(mockIo_, write(::testing::_, 1))
        .WillOnce(::testing::Return(1));
    EXPECT_CALL(mockIo_, putb(0x02))
        .WillOnce(::testing::Return(0x02));
    
    size_t writeResult = wrapper.write(data, 1);
    int putbResult = wrapper.putb(0x02);
    
    EXPECT_EQ(writeResult, 1u);
    EXPECT_EQ(putbResult, 0x02);
}

// Test setTarget with different IDs
TEST_F(IoWrapperTest_2157, SetTargetMultipleIds_2157) {
    OffsetWriter pow;
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), &pow);

    EXPECT_NO_THROW(wrapper.setTarget(0, 0));
    EXPECT_NO_THROW(wrapper.setTarget(1, 256));
    EXPECT_NO_THROW(wrapper.setTarget(0, 512));
}

// Test write when underlying io returns partial write
TEST_F(IoWrapperTest_2157, WritePartialReturn_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    
    EXPECT_CALL(mockIo_, write(::testing::_, 5))
        .WillOnce(::testing::Return(3));  // Partial write
    
    size_t result = wrapper.write(data, 5);
    EXPECT_EQ(result, 3u);
}

// Test write single byte
TEST_F(IoWrapperTest_2157, WriteSingleByte_2157) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    byte data[] = {0xAA};
    
    EXPECT_CALL(mockIo_, write(::testing::_, 1))
        .WillOnce(::testing::Return(1));
    
    size_t result = wrapper.write(data, 1);
    EXPECT_EQ(result, 1u);
}
