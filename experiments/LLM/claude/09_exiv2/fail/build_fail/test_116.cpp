#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"
#include "helper_functions.hpp"

using namespace Exiv2;

// We need a concrete implementation of BasicIo for testing.
// Using MemIo which is typically available in exiv2, but if not,
// we create a mock that behaves like a memory-based IO.

// Mock class for BasicIo to control behavior in tests
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

class ReadQWORDTagTest_116 : public ::testing::Test {
protected:
    void SetUp() override {
        mockIo = std::make_unique<MockBasicIo>();
    }

    std::unique_ptr<MockBasicIo> mockIo;
};

// Test: Reading a QWORD value of zero
TEST_F(ReadQWORDTagTest_116, ReadsZeroValue_116) {
    // 8 bytes of zeros in little-endian = 0
    byte data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    DataBuf buf(data, 8);

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(8));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    EXPECT_EQ(result, 0u);
}

// Test: Reading a known QWORD value in little-endian
TEST_F(ReadQWORDTagTest_116, ReadsKnownLittleEndianValue_116) {
    // Value 1 in little-endian: 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    byte data[8] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    DataBuf buf(data, 8);

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(8));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    EXPECT_EQ(result, 1u);
}

// Test: Reading max uint64 value (0xFFFFFFFFFFFFFFFF)
TEST_F(ReadQWORDTagTest_116, ReadsMaxUint64Value_116) {
    byte data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    DataBuf buf(data, 8);

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(8));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test: Reading a specific multi-byte little-endian value
TEST_F(ReadQWORDTagTest_116, ReadsSpecificMultiByteValue_116) {
    // 0x0102030405060708 in little-endian: 08 07 06 05 04 03 02 01
    byte data[8] = {0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
    DataBuf buf(data, 8);

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(8));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    EXPECT_EQ(result, 0x0102030405060708ULL);
}

// Test: Not enough data remaining - should throw (enforce fails)
TEST_F(ReadQWORDTagTest_116, ThrowsWhenNotEnoughData_116) {
    // size = 7, tell = 0 => remaining = 7 < QWORD (8)
    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(7));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    EXPECT_THROW(readQWORDTag(ioPtr), Exiv2::Error);
}

// Test: tell() is at end of stream, no bytes remaining
TEST_F(ReadQWORDTagTest_116, ThrowsWhenAtEndOfStream_116) {
    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(100));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(100));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    EXPECT_THROW(readQWORDTag(ioPtr), Exiv2::Error);
}

// Test: Exactly 8 bytes remaining (boundary)
TEST_F(ReadQWORDTagTest_116, ExactlyEightBytesRemaining_116) {
    byte data[8] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89};
    DataBuf buf(data, 8);

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(16));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(8));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    // Little-endian: 0x89674523_01EFCDAB
    EXPECT_EQ(result, 0x8967452301EFCDABULL);
}

// Test: 7 bytes remaining should throw (boundary - 1 below QWORD)
TEST_F(ReadQWORDTagTest_116, ThrowsWhenSevenBytesRemaining_116) {
    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(15));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(8));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    EXPECT_THROW(readQWORDTag(ioPtr), Exiv2::Error);
}

// Test: Reading from middle of a larger stream
TEST_F(ReadQWORDTagTest_116, ReadsFromMiddleOfStream_116) {
    byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    DataBuf buf(data, 8);

    // Stream is 1024 bytes, we're at position 512, plenty of room
    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(1024));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(512));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    // Little-endian: 0x00000001_00000000 = 4294967296
    EXPECT_EQ(result, 0x0000000100000000ULL);
}

// Test: Value with only high byte set
TEST_F(ReadQWORDTagTest_116, ReadsHighByteOnlyValue_116) {
    // 0x8000000000000000 in LE: 00 00 00 00 00 00 00 80
    byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
    DataBuf buf(data, 8);

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(8));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    EXPECT_EQ(result, 0x8000000000000000ULL);
}

// Test: tell() returns value making remaining exactly less than QWORD
TEST_F(ReadQWORDTagTest_116, ThrowsWhenTellNearEnd_116) {
    // size = 100, tell = 93 => remaining = 7 < 8
    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(100));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(93));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    EXPECT_THROW(readQWORDTag(ioPtr), Exiv2::Error);
}

// Test: Reading value 256 (0x0100) in little-endian
TEST_F(ReadQWORDTagTest_116, Reads256Value_116) {
    byte data[8] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    DataBuf buf(data, 8);

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(8));
    EXPECT_CALL(*mockIo, tell()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*mockIo, read(static_cast<size_t>(8))).WillOnce(::testing::Return(buf));

    BasicIo::UniquePtr ioPtr(mockIo.release());
    uint64_t result = readQWORDTag(ioPtr);
    EXPECT_EQ(result, 256u);
}
