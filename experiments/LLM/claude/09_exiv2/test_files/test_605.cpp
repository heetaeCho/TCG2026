#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

// Since RemoteIo is abstract-like and requires network infrastructure,
// we need to test the read(size_t) method which calls read(byte*, size_t).
// We'll create a testable subclass that overrides the byte-level read.

class TestableRemoteIo : public RemoteIo {
public:
    TestableRemoteIo() : RemoteIo() {}

    // We'll track what the byte-level read should return
    std::vector<byte> fakeData_;
    size_t fakeReadReturn_ = 0;

    // Override the byte-level read to return controlled data
    size_t read(byte* buf, size_t rcount) override {
        size_t toRead = std::min(rcount, fakeReadReturn_);
        if (toRead > 0 && buf != nullptr) {
            size_t copySize = std::min(toRead, fakeData_.size());
            std::memcpy(buf, fakeData_.data(), copySize);
        }
        return toRead;
    }

    // Override read(size_t) to use the parent's implementation
    DataBuf read(size_t rcount) override {
        return RemoteIo::read(rcount);
    }

    // Provide minimal implementations for pure virtual methods
    int open() override { return 0; }
    int close() override { return 0; }
    size_t write(const byte* data, size_t wcount) override { return 0; }
    size_t write(BasicIo& src) override { return 0; }
    int putb(byte data) override { return 0; }
    int getb() override { return 0; }
    void transfer(BasicIo& src) override {}
    int seek(int64_t offset, Position pos) override { return 0; }
    byte* mmap(bool isWriteable) override { return nullptr; }
    int munmap() override { return 0; }
    size_t tell() const override { return 0; }
    size_t size() const override { return fakeData_.size(); }
    bool isopen() const override { return true; }
    int error() const override { return 0; }
    bool eof() const override { return false; }
    const std::string& path() const noexcept override {
        static std::string p = "test";
        return p;
    }
    void populateFakeData() override {}
};

class RemoteIoReadTest_605 : public ::testing::Test {
protected:
    TestableRemoteIo io_;
};

// Test that read(size_t) returns a DataBuf with correct size when data is available
TEST_F(RemoteIoReadTest_605, ReadReturnsCorrectDataBuf_605) {
    io_.fakeData_ = {0x01, 0x02, 0x03, 0x04, 0x05};
    io_.fakeReadReturn_ = 5;

    DataBuf buf = io_.read(5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
    EXPECT_EQ(buf.read_uint8(4), 0x05);
}

// Test that read(size_t) throws when read returns 0 bytes
TEST_F(RemoteIoReadTest_605, ReadThrowsWhenZeroBytesRead_605) {
    io_.fakeData_ = {};
    io_.fakeReadReturn_ = 0;

    EXPECT_THROW({
        io_.read(10);
    }, Error);
}

// Test that read(size_t) throws with correct error code when read returns 0
TEST_F(RemoteIoReadTest_605, ReadThrowsInputDataReadFailedError_605) {
    io_.fakeData_ = {};
    io_.fakeReadReturn_ = 0;

    try {
        io_.read(5);
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerInputDataReadFailed);
    }
}

// Test partial read: requested more than available
TEST_F(RemoteIoReadTest_605, ReadResizesBufferForPartialRead_605) {
    io_.fakeData_ = {0xAA, 0xBB, 0xCC};
    io_.fakeReadReturn_ = 3;  // Only 3 bytes available even though we request 10

    DataBuf buf = io_.read(10);
    EXPECT_EQ(buf.size(), 3u);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.read_uint8(2), 0xCC);
}

// Test reading exactly 1 byte
TEST_F(RemoteIoReadTest_605, ReadSingleByte_605) {
    io_.fakeData_ = {0xFF};
    io_.fakeReadReturn_ = 1;

    DataBuf buf = io_.read(1);
    EXPECT_EQ(buf.size(), 1u);
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

// Test reading a large amount of data
TEST_F(RemoteIoReadTest_605, ReadLargeData_605) {
    const size_t largeSize = 10000;
    io_.fakeData_.resize(largeSize, 0x42);
    io_.fakeReadReturn_ = largeSize;

    DataBuf buf = io_.read(largeSize);
    EXPECT_EQ(buf.size(), largeSize);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
    EXPECT_EQ(buf.read_uint8(largeSize - 1), 0x42);
}

// Test that requesting 0 bytes throws (since read would return 0)
TEST_F(RemoteIoReadTest_605, ReadZeroBytesThrows_605) {
    io_.fakeData_ = {};
    io_.fakeReadReturn_ = 0;

    EXPECT_THROW({
        io_.read(0);
    }, Error);
}

// Test that the returned buffer contains correct content after partial read
TEST_F(RemoteIoReadTest_605, PartialReadContentIsCorrect_605) {
    io_.fakeData_ = {0x10, 0x20, 0x30, 0x40, 0x50};
    io_.fakeReadReturn_ = 2;  // Only return 2 bytes

    DataBuf buf = io_.read(5);
    EXPECT_EQ(buf.size(), 2u);
    EXPECT_EQ(buf.read_uint8(0), 0x10);
    EXPECT_EQ(buf.read_uint8(1), 0x20);
}

// Test multiple successive reads
TEST_F(RemoteIoReadTest_605, MultipleReadsWork_605) {
    io_.fakeData_ = {0x01, 0x02, 0x03};
    io_.fakeReadReturn_ = 3;

    DataBuf buf1 = io_.read(3);
    EXPECT_EQ(buf1.size(), 3u);

    io_.fakeData_ = {0x04, 0x05};
    io_.fakeReadReturn_ = 2;

    DataBuf buf2 = io_.read(2);
    EXPECT_EQ(buf2.size(), 2u);
    EXPECT_EQ(buf2.read_uint8(0), 0x04);
}

// Test that read with return count equal to request doesn't resize
TEST_F(RemoteIoReadTest_605, ReadExactCountNoResize_605) {
    io_.fakeData_ = {0xDE, 0xAD, 0xBE, 0xEF};
    io_.fakeReadReturn_ = 4;

    DataBuf buf = io_.read(4);
    EXPECT_EQ(buf.size(), 4u);
}
