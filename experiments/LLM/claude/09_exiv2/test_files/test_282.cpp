#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "basicio.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AtLeast;

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
    MOCK_METHOD(const size_t, tell, (), (const, override));
    MOCK_METHOD(const size_t, size, (), (const, override));
    MOCK_METHOD(const bool, isopen, (), (const, override));
    MOCK_METHOD(const int, error, (), (const, override));
    MOCK_METHOD(const bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class IoWrapperTest_282 : public ::testing::Test {
protected:
    MockBasicIo mockIo_;
    byte header_[8] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
};

// Test that first write also writes the header before writing data
TEST_F(IoWrapperTest_282, FirstWriteWritesHeaderThenData_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0x01, 0x02, 0x03};

    // Expect header write first, then data write
    {
        ::testing::InSequence seq;
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        EXPECT_CALL(mockIo_, write(data, 3))
            .Times(1)
            .WillOnce(Return(3));
    }

    size_t result = wrapper.write(data, 3);
    EXPECT_EQ(result, 3u);
}

// Test that second write does NOT write the header again
TEST_F(IoWrapperTest_282, SecondWriteDoesNotWriteHeaderAgain_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data1[] = {0x01, 0x02};
    byte data2[] = {0x03, 0x04, 0x05};

    {
        ::testing::InSequence seq;
        // First write: header + data1
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        EXPECT_CALL(mockIo_, write(data1, 2))
            .Times(1)
            .WillOnce(Return(2));
        // Second write: only data2, no header
        EXPECT_CALL(mockIo_, write(data2, 3))
            .Times(1)
            .WillOnce(Return(3));
    }

    wrapper.write(data1, 2);
    size_t result = wrapper.write(data2, 3);
    EXPECT_EQ(result, 3u);
}

// Test writing zero bytes - wcount is 0, header should NOT be written
TEST_F(IoWrapperTest_282, WriteZeroBytesDoesNotWriteHeader_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0x00};

    // With wcount == 0, the condition !wroteHeader_ && wcount > 0 is false
    // So only io_.write(pData, 0) should be called
    EXPECT_CALL(mockIo_, write(_, sizeof(header_)))
        .Times(0);
    EXPECT_CALL(mockIo_, write(data, 0))
        .Times(1)
        .WillOnce(Return(0));

    size_t result = wrapper.write(data, 0);
    EXPECT_EQ(result, 0u);
}

// Test that after writing zero bytes, a subsequent non-zero write still writes header
TEST_F(IoWrapperTest_282, WriteZeroThenNonZeroStillWritesHeader_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0x01};

    {
        ::testing::InSequence seq;
        // Zero-byte write: no header
        EXPECT_CALL(mockIo_, write(data, 0))
            .Times(1)
            .WillOnce(Return(0));
        // Non-zero write: header + data
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        EXPECT_CALL(mockIo_, write(data, 1))
            .Times(1)
            .WillOnce(Return(1));
    }

    wrapper.write(data, 0);
    size_t result = wrapper.write(data, 1);
    EXPECT_EQ(result, 1u);
}

// Test write with a single byte
TEST_F(IoWrapperTest_282, WriteSingleByte_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0xFF};

    {
        ::testing::InSequence seq;
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        EXPECT_CALL(mockIo_, write(data, 1))
            .Times(1)
            .WillOnce(Return(1));
    }

    size_t result = wrapper.write(data, 1);
    EXPECT_EQ(result, 1u);
}

// Test write with large data
TEST_F(IoWrapperTest_282, WriteLargeData_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    std::vector<byte> largeData(10000, 0xAB);

    {
        ::testing::InSequence seq;
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        EXPECT_CALL(mockIo_, write(largeData.data(), 10000))
            .Times(1)
            .WillOnce(Return(10000));
    }

    size_t result = wrapper.write(largeData.data(), 10000);
    EXPECT_EQ(result, 10000u);
}

// Test that the return value reflects the underlying io's return value
TEST_F(IoWrapperTest_282, WriteReturnValueFromUnderlyingIo_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};

    {
        ::testing::InSequence seq;
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        // Simulate partial write
        EXPECT_CALL(mockIo_, write(data, 5))
            .Times(1)
            .WillOnce(Return(2));
    }

    size_t result = wrapper.write(data, 5);
    EXPECT_EQ(result, 2u);
}

// Test multiple sequential writes - header written only once
TEST_F(IoWrapperTest_282, MultipleWritesHeaderOnlyOnce_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data1[] = {0x01};
    byte data2[] = {0x02};
    byte data3[] = {0x03};

    {
        ::testing::InSequence seq;
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        EXPECT_CALL(mockIo_, write(data1, 1))
            .Times(1)
            .WillOnce(Return(1));
        EXPECT_CALL(mockIo_, write(data2, 1))
            .Times(1)
            .WillOnce(Return(1));
        EXPECT_CALL(mockIo_, write(data3, 1))
            .Times(1)
            .WillOnce(Return(1));
    }

    wrapper.write(data1, 1);
    wrapper.write(data2, 1);
    wrapper.write(data3, 1);
}

// Test with zero-size header
TEST_F(IoWrapperTest_282, ZeroSizeHeader_282) {
    byte emptyHeader[] = {};
    IoWrapper wrapper(mockIo_, emptyHeader, 0, nullptr);

    byte data[] = {0x01, 0x02};

    {
        ::testing::InSequence seq;
        // Header write with size 0 still happens on first non-zero write
        EXPECT_CALL(mockIo_, write(emptyHeader, 0))
            .Times(1)
            .WillOnce(Return(0));
        EXPECT_CALL(mockIo_, write(data, 2))
            .Times(1)
            .WillOnce(Return(2));
    }

    size_t result = wrapper.write(data, 2);
    EXPECT_EQ(result, 2u);
}

// Test that underlying io write failure is propagated
TEST_F(IoWrapperTest_282, WriteFailurePropagated_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0x01};

    {
        ::testing::InSequence seq;
        EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
            .Times(1)
            .WillOnce(Return(sizeof(header_)));
        EXPECT_CALL(mockIo_, write(data, 1))
            .Times(1)
            .WillOnce(Return(0));  // Write failure
    }

    size_t result = wrapper.write(data, 1);
    EXPECT_EQ(result, 0u);
}

// Test putb delegates to underlying io
TEST_F(IoWrapperTest_282, PutbDelegatesToIo_282) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    EXPECT_CALL(mockIo_, putb(0x42))
        .Times(1)
        .WillOnce(Return(0x42));

    int result = wrapper.putb(0x42);
    EXPECT_EQ(result, 0x42);
}
