#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <cstring>

// Include necessary headers
#include "exiv2/basicio.hpp"
#include "exiv2/jpgimage.hpp"

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::Invoke;

// Mock class for BasicIo
class MockBasicIo : public BasicIo {
public:
    MockBasicIo() : BasicIo() {}
    ~MockBasicIo() override = default;

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

class ExvImageWriteHeaderTest_1226 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test that writeHeader returns 0 on successful write of 7 bytes with no error
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderSuccess_1226) {
    // Create ExvImage with a separate BasicIo for construction
    // We need to test writeHeader via the interface
    // Since writeHeader is protected, we test it through a derived or friend approach
    // However, looking at the partial code, writeHeader is public in ExvImage within the snippet
    // Let's use the mock directly

    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce(Return(7));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));

    // We need to create an ExvImage instance to call writeHeader
    // Since ExvImage constructor requires a unique_ptr<BasicIo>, we create a MemoryIo
    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 0);
}

// Test that writeHeader returns 4 when write returns less than 7 bytes
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderFailsOnShortWrite_1226) {
    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce(Return(5));  // Short write

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 4);
}

// Test that writeHeader returns 4 when write returns 0 bytes
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderFailsOnZeroWrite_1226) {
    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce(Return(0));

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 4);
}

// Test that writeHeader returns 4 when outIo.error() returns non-zero after successful write
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderFailsOnIoError_1226) {
    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce(Return(7));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));  // Error condition

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 4);
}

// Test that writeHeader writes the correct data (0xff, 0x01, then exiv2 id bytes)
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderWritesCorrectData_1226) {
    std::vector<byte> capturedData;

    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce([&capturedData](const byte* data, size_t wcount) -> size_t {
            capturedData.assign(data, data + wcount);
            return wcount;
        });
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 0);

    // Verify the header data
    ASSERT_EQ(capturedData.size(), 7u);
    EXPECT_EQ(capturedData[0], 0xff);
    EXPECT_EQ(capturedData[1], 0x01);
    // The remaining 5 bytes should be the exiv2 identifier
}

// Test that writeHeader returns 4 when write returns more than 7 (edge case, unlikely but tests != check)
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderFailsOnOverWrite_1226) {
    // write returning value != 7 should cause failure
    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce(Return(8));

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 4);
}

// Test that writeHeader writes exactly 7 bytes
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderRequestsExactly7Bytes_1226) {
    EXPECT_CALL(mockIo, write(_, 7))
        .Times(1)
        .WillOnce(Return(7));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 0);
}

// Test mimeType returns expected value for ExvImage
TEST(ExvImageMimeTypeTest_1226, MimeTypeReturnsExpectedValue_1226) {
    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    std::string mimeType = img.mimeType();
    // ExvImage should have a specific mime type
    EXPECT_FALSE(mimeType.empty());
}

// Test write returns 4 when exactly 1 byte is written (boundary)
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderFailsOnSingleByteWrite_1226) {
    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce(Return(1));

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 4);
}

// Test write returns 4 when 6 bytes written (off by one boundary)
TEST_F(ExvImageWriteHeaderTest_1226, WriteHeaderFailsOnSixBytesWritten_1226) {
    EXPECT_CALL(mockIo, write(_, 7))
        .WillOnce(Return(6));

    auto memIo = std::make_unique<MemoryIo>();
    ExvImage img(std::move(memIo), true);

    int result = img.writeHeader(mockIo);
    EXPECT_EQ(result, 4);
}
