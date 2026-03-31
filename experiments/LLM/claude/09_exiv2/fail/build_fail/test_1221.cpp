#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/jpgimage.hpp>
#include <cstdint>

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::Invoke;

// Mock class for BasicIo
class MockBasicIo : public BasicIo {
public:
    MockBasicIo() = default;
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

class JpegImageWriteHeaderTest_1221 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that writeHeader returns 0 on successful write of 2 bytes with no error
TEST_F(JpegImageWriteHeaderTest_1221, WriteHeaderSuccess_1221) {
    auto mockIo = std::make_unique<MockBasicIo>();
    MockBasicIo* mockIoPtr = mockIo.get();

    // Create a separate mock for the outIo parameter
    MockBasicIo outIo;

    // Expect write to be called with 2 bytes, return 2 (success)
    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce([](const byte* data, size_t wcount) -> size_t {
            // Verify the SOI marker bytes: 0xFF 0xD8
            EXPECT_EQ(data[0], 0xFF);
            EXPECT_EQ(data[1], static_cast<byte>(0xD8)); // soi_ = -40 = 0xD8 as unsigned byte
            return 2;
        });

    // No error after write
    EXPECT_CALL(outIo, error())
        .WillOnce(Return(0));

    // We need a valid JpegImage. Use MemIo for creation.
    auto memIo = std::make_unique<MemIo>();
    // Write a minimal JPEG to make the constructor happy
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    memIo->write(jpegData, sizeof(jpegData));
    memIo->seek(0, BasicIo::beg);

    JpegImage img(std::move(memIo), false);

    // writeHeader is protected, but we can test it indirectly
    // Since writeHeader is protected, we need a workaround.
    // Let's create a test helper that calls it through a derived class or friend.
    // Actually, looking at the partial code, writeHeader is const and protected.
    // We'll need to use a wrapper or test through the public interface.
    
    // Alternative: Since we can't directly call protected method, let's verify
    // through the provided partial implementation by creating a testable subclass.
}

// Helper class to expose protected writeHeader for testing
class TestableJpegImage : public JpegImage {
public:
    TestableJpegImage(BasicIo::UniquePtr io, bool create)
        : JpegImage(std::move(io), create) {}

    using JpegImage::writeHeader;
};

class JpegImageWriteHeaderDirectTest_1221 : public ::testing::Test {
protected:
    std::unique_ptr<TestableJpegImage> createTestableImage() {
        auto memIo = std::make_unique<MemIo>();
        const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
        memIo->write(jpegData, sizeof(jpegData));
        memIo->seek(0, BasicIo::beg);
        return std::make_unique<TestableJpegImage>(std::move(memIo), false);
    }
};

// Test writeHeader returns 0 on successful write
TEST_F(JpegImageWriteHeaderDirectTest_1221, WriteHeaderReturnsZeroOnSuccess_1221) {
    auto img = createTestableImage();
    MockBasicIo outIo;

    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce(Return(2));
    EXPECT_CALL(outIo, error())
        .WillOnce(Return(0));

    int result = img->writeHeader(outIo);
    EXPECT_EQ(result, 0);
}

// Test writeHeader returns 4 when write returns less than 2 bytes
TEST_F(JpegImageWriteHeaderDirectTest_1221, WriteHeaderReturnsErrorWhenWriteFails_1221) {
    auto img = createTestableImage();
    MockBasicIo outIo;

    // Write fails - returns 0 instead of 2
    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce(Return(0));

    int result = img->writeHeader(outIo);
    EXPECT_EQ(result, 4);
}

// Test writeHeader returns 4 when write returns 1 byte (partial write)
TEST_F(JpegImageWriteHeaderDirectTest_1221, WriteHeaderReturnsErrorOnPartialWrite_1221) {
    auto img = createTestableImage();
    MockBasicIo outIo;

    // Partial write - returns 1 instead of 2
    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce(Return(1));

    int result = img->writeHeader(outIo);
    EXPECT_EQ(result, 4);
}

// Test writeHeader returns 4 when outIo reports error after successful write
TEST_F(JpegImageWriteHeaderDirectTest_1221, WriteHeaderReturnsErrorWhenIoErrorOccurs_1221) {
    auto img = createTestableImage();
    MockBasicIo outIo;

    // Write succeeds but error() returns non-zero
    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce(Return(2));
    EXPECT_CALL(outIo, error())
        .WillOnce(Return(1));

    int result = img->writeHeader(outIo);
    EXPECT_EQ(result, 4);
}

// Test writeHeader writes correct SOI marker bytes (0xFF, 0xD8)
TEST_F(JpegImageWriteHeaderDirectTest_1221, WriteHeaderWritesCorrectSOIMarker_1221) {
    auto img = createTestableImage();
    MockBasicIo outIo;

    byte capturedData[2] = {0, 0};
    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce([&capturedData](const byte* data, size_t wcount) -> size_t {
            capturedData[0] = data[0];
            capturedData[1] = data[1];
            return 2;
        });
    EXPECT_CALL(outIo, error())
        .WillOnce(Return(0));

    int result = img->writeHeader(outIo);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(capturedData[0], 0xFF);
    // soi_ = -40, as unsigned byte = 0xD8
    EXPECT_EQ(capturedData[1], static_cast<byte>(0xD8));
}

// Test writeHeader with write returning a large value (boundary)
TEST_F(JpegImageWriteHeaderDirectTest_1221, WriteHeaderReturnsErrorWhenWriteReturnsLargeValue_1221) {
    auto img = createTestableImage();
    MockBasicIo outIo;

    // Write returns a value larger than 2 - still not equal to 2
    // Actually, size_t can't be negative, and 3 != 2, so should return 4
    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce(Return(3));

    int result = img->writeHeader(outIo);
    EXPECT_EQ(result, 4);
}

// Test that error() is not called if write fails
TEST_F(JpegImageWriteHeaderDirectTest_1221, ErrorNotCheckedIfWriteFails_1221) {
    auto img = createTestableImage();
    MockBasicIo outIo;

    EXPECT_CALL(outIo, write(_, 2))
        .WillOnce(Return(0));
    // error() should NOT be called since write already failed
    EXPECT_CALL(outIo, error())
        .Times(0);

    int result = img->writeHeader(outIo);
    EXPECT_EQ(result, 4);
}

// Test isJpegType with valid JPEG data
TEST(JpegImageIsJpegType_1221, ValidJpegReturnsTrue_1221) {
    auto memIo = std::make_unique<MemIo>();
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    memIo->write(jpegData, sizeof(jpegData));
    memIo->seek(0, BasicIo::beg);

    bool result = JpegImage::isJpegType(*memIo, false);
    EXPECT_TRUE(result);
}

// Test isJpegType with invalid data
TEST(JpegImageIsJpegType_1221, InvalidDataReturnsFalse_1221) {
    auto memIo = std::make_unique<MemIo>();
    const byte nonJpegData[] = {0x89, 0x50, 0x4E, 0x47}; // PNG signature start
    memIo->write(nonJpegData, sizeof(nonJpegData));
    memIo->seek(0, BasicIo::beg);

    bool result = JpegImage::isJpegType(*memIo, false);
    EXPECT_FALSE(result);
}

// Test isJpegType with empty data
TEST(JpegImageIsJpegType_1221, EmptyDataReturnsFalse_1221) {
    auto memIo = std::make_unique<MemIo>();

    bool result = JpegImage::isJpegType(*memIo, false);
    EXPECT_FALSE(result);
}

// Test isJpegType with advance=true repositions the stream
TEST(JpegImageIsJpegType_1221, AdvanceTrueMovesPosition_1221) {
    auto memIo = std::make_unique<MemIo>();
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    memIo->write(jpegData, sizeof(jpegData));
    memIo->seek(0, BasicIo::beg);

    bool result = JpegImage::isJpegType(*memIo, true);
    EXPECT_TRUE(result);
    // After advance=true, position should have advanced
    EXPECT_GT(memIo->tell(), static_cast<size_t>(0));
}

// Test isJpegType with advance=false does not reposition stream
TEST(JpegImageIsJpegType_1221, AdvanceFalseDoesNotMovePosition_1221) {
    auto memIo = std::make_unique<MemIo>();
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    memIo->write(jpegData, sizeof(jpegData));
    memIo->seek(0, BasicIo::beg);

    bool result = JpegImage::isJpegType(*memIo, false);
    EXPECT_TRUE(result);
    // After advance=false, position should be back to 0
    EXPECT_EQ(memIo->tell(), static_cast<size_t>(0));
}

// Test mimeType returns correct JPEG MIME type
TEST(JpegImageMimeType_1221, ReturnsJpegMimeType_1221) {
    auto memIo = std::make_unique<MemIo>();
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    memIo->write(jpegData, sizeof(jpegData));
    memIo->seek(0, BasicIo::beg);

    JpegImage img(std::move(memIo), false);
    std::string mime = img.mimeType();
    EXPECT_EQ(mime, "image/jpeg");
}

// Test isJpegType with only one byte
TEST(JpegImageIsJpegType_1221, SingleByteReturnsFalse_1221) {
    auto memIo = std::make_unique<MemIo>();
    const byte data[] = {0xFF};
    memIo->write(data, sizeof(data));
    memIo->seek(0, BasicIo::beg);

    bool result = JpegImage::isJpegType(*memIo, false);
    EXPECT_FALSE(result);
}

// Test isJpegType with 0xFF followed by wrong second byte
TEST(JpegImageIsJpegType_1221, WrongSecondByteReturnsFalse_1221) {
    auto memIo = std::make_unique<MemIo>();
    const byte data[] = {0xFF, 0x00}; // 0xFF followed by non-SOI
    memIo->write(data, sizeof(data));
    memIo->seek(0, BasicIo::beg);

    bool result = JpegImage::isJpegType(*memIo, false);
    EXPECT_FALSE(result);
}
