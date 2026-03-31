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

class IoWrapperTest_283 : public ::testing::Test {
protected:
    MockBasicIo mockIo_;
    byte header_[4] = {0x49, 0x49, 0x2A, 0x00}; // Example TIFF header (little-endian)
};

// Test that putb writes the header on the first call
TEST_F(IoWrapperTest_283, PutbWritesHeaderOnFirstCall_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    // Expect that the header is written first, then putb is called
    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(0x42))
        .Times(1)
        .WillOnce(Return(0x42));

    int result = wrapper.putb(0x42);
    EXPECT_EQ(result, 0x42);
}

// Test that putb does NOT write the header on subsequent calls
TEST_F(IoWrapperTest_283, PutbDoesNotWriteHeaderOnSubsequentCalls_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    // First call: header + putb
    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    wrapper.putb(0x01);
    // Second call: only putb, no write
    wrapper.putb(0x02);
}

// Test putb returns value from underlying io
TEST_F(IoWrapperTest_283, PutbReturnsValueFromUnderlyingIo_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(0xFF))
        .WillOnce(Return(0xFF));

    int result = wrapper.putb(0xFF);
    EXPECT_EQ(result, 0xFF);
}

// Test putb with zero byte
TEST_F(IoWrapperTest_283, PutbWithZeroByte_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(0x00))
        .WillOnce(Return(0x00));

    int result = wrapper.putb(0x00);
    EXPECT_EQ(result, 0x00);
}

// Test putb when underlying putb returns error (-1)
TEST_F(IoWrapperTest_283, PutbReturnsErrorFromUnderlyingIo_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(0x10))
        .WillOnce(Return(-1));

    int result = wrapper.putb(0x10);
    EXPECT_EQ(result, -1);
}

// Test write method writes header on first call
TEST_F(IoWrapperTest_283, WriteWritesHeaderOnFirstCall_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0x01, 0x02, 0x03};

    // Header write, then data write
    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, write(data, sizeof(data)))
        .Times(1)
        .WillOnce(Return(sizeof(data)));

    size_t result = wrapper.write(data, sizeof(data));
    EXPECT_EQ(result, sizeof(data));
}

// Test write method does not write header on subsequent calls
TEST_F(IoWrapperTest_283, WriteDoesNotWriteHeaderOnSubsequentCalls_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data1[] = {0x01};
    byte data2[] = {0x02};

    // Header should only be written once
    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, write(data1, sizeof(data1)))
        .WillOnce(Return(sizeof(data1)));
    EXPECT_CALL(mockIo_, write(data2, sizeof(data2)))
        .WillOnce(Return(sizeof(data2)));

    wrapper.write(data1, sizeof(data1));
    wrapper.write(data2, sizeof(data2));
}

// Test that putb after write does not re-write header
TEST_F(IoWrapperTest_283, PutbAfterWriteDoesNotRewriteHeader_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0xAA};

    // Header written once during write()
    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, write(data, sizeof(data)))
        .WillOnce(Return(sizeof(data)));
    EXPECT_CALL(mockIo_, putb(0xBB))
        .WillOnce(Return(0xBB));

    wrapper.write(data, sizeof(data));
    int result = wrapper.putb(0xBB);
    EXPECT_EQ(result, 0xBB);
}

// Test that write after putb does not re-write header
TEST_F(IoWrapperTest_283, WriteAfterPutbDoesNotRewriteHeader_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0xCC};

    // Header written once during putb()
    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(0xDD))
        .WillOnce(Return(0xDD));
    EXPECT_CALL(mockIo_, write(data, sizeof(data)))
        .WillOnce(Return(sizeof(data)));

    wrapper.putb(0xDD);
    size_t result = wrapper.write(data, sizeof(data));
    EXPECT_EQ(result, sizeof(data));
}

// Test with empty header (size 0)
TEST_F(IoWrapperTest_283, PutbWithEmptyHeader_283) {
    IoWrapper wrapper(mockIo_, nullptr, 0, nullptr);

    // Even with size 0, write might still be called with size 0
    EXPECT_CALL(mockIo_, write(_, 0))
        .Times(AtLeast(0))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo_, putb(0x55))
        .WillOnce(Return(0x55));

    int result = wrapper.putb(0x55);
    EXPECT_EQ(result, 0x55);
}

// Test multiple putb calls return correct values
TEST_F(IoWrapperTest_283, MultiplePutbCallsReturnCorrectValues_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(0x01)).WillOnce(Return(0x01));
    EXPECT_CALL(mockIo_, putb(0x02)).WillOnce(Return(0x02));
    EXPECT_CALL(mockIo_, putb(0x03)).WillOnce(Return(0x03));

    EXPECT_EQ(wrapper.putb(0x01), 0x01);
    EXPECT_EQ(wrapper.putb(0x02), 0x02);
    EXPECT_EQ(wrapper.putb(0x03), 0x03);
}

// Test write with large data
TEST_F(IoWrapperTest_283, WriteWithLargeData_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    std::vector<byte> largeData(10000, 0xAB);

    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, write(largeData.data(), largeData.size()))
        .WillOnce(Return(largeData.size()));

    size_t result = wrapper.write(largeData.data(), largeData.size());
    EXPECT_EQ(result, largeData.size());
}

// Test write with zero count
TEST_F(IoWrapperTest_283, WriteWithZeroCount_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    byte data[] = {0x00};

    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .Times(1)
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, write(data, 0))
        .WillOnce(Return(0));

    size_t result = wrapper.write(data, 0);
    EXPECT_EQ(result, 0u);
}

// Test putb with max byte value
TEST_F(IoWrapperTest_283, PutbWithMaxByteValue_283) {
    IoWrapper wrapper(mockIo_, header_, sizeof(header_), nullptr);

    EXPECT_CALL(mockIo_, write(header_, sizeof(header_)))
        .WillOnce(Return(sizeof(header_)));
    EXPECT_CALL(mockIo_, putb(255))
        .WillOnce(Return(255));

    int result = wrapper.putb(255);
    EXPECT_EQ(result, 255);
}

// Test with single byte header
TEST_F(IoWrapperTest_283, PutbWithSingleByteHeader_283) {
    byte singleHeader[] = {0xAA};
    IoWrapper wrapper(mockIo_, singleHeader, 1, nullptr);

    EXPECT_CALL(mockIo_, write(singleHeader, 1))
        .Times(1)
        .WillOnce(Return(1));
    EXPECT_CALL(mockIo_, putb(0x11))
        .WillOnce(Return(0x11));

    int result = wrapper.putb(0x11);
    EXPECT_EQ(result, 0x11);
}
