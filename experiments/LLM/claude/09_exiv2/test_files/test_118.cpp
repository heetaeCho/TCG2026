#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"
#include "helper_functions.hpp"

#include <cstring>
#include <vector>

// We need a concrete implementation of BasicIo for testing.
// MemIo is available in exiv2, but we can also use it directly.
// Let's use Exiv2::MemIo which is a memory-based BasicIo implementation.
#include "exiv2/basicio.hpp"

namespace {

using namespace Exiv2;

class ReadWORDTagTest_118 : public ::testing::Test {
protected:
    // Helper to create a MemIo with specific data
    BasicIo::UniquePtr createMemIo(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        io->open();
        return io;
    }
};

// Test reading a simple WORD value (little-endian)
TEST_F(ReadWORDTagTest_118, ReadsLittleEndianWordCorrectly_118) {
    // 0x0100 in little-endian is stored as {0x00, 0x01}
    std::vector<byte> data = {0x00, 0x01};
    auto io = createMemIo(data);
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 0x0100);
}

// Test reading a WORD value of zero
TEST_F(ReadWORDTagTest_118, ReadsZeroValue_118) {
    std::vector<byte> data = {0x00, 0x00};
    auto io = createMemIo(data);
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 0x0000);
}

// Test reading maximum WORD value (0xFFFF)
TEST_F(ReadWORDTagTest_118, ReadsMaxWordValue_118) {
    std::vector<byte> data = {0xFF, 0xFF};
    auto io = createMemIo(data);
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 0xFFFF);
}

// Test reading a known little-endian value
TEST_F(ReadWORDTagTest_118, ReadsKnownLittleEndianValue_118) {
    // Little-endian: low byte first, high byte second
    // Value 0x0201: stored as {0x01, 0x02}
    std::vector<byte> data = {0x01, 0x02};
    auto io = createMemIo(data);
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 0x0201);
}

// Test that readWORDTag advances the IO position by 2 bytes
TEST_F(ReadWORDTagTest_118, AdvancesPositionByTwoBytes_118) {
    std::vector<byte> data = {0xAB, 0xCD, 0xEF, 0x12};
    auto io = createMemIo(data);
    size_t posBefore = io->tell();
    readWORDTag(io);
    size_t posAfter = io->tell();
    EXPECT_EQ(posAfter - posBefore, 2u);
}

// Test reading two consecutive WORD values
TEST_F(ReadWORDTagTest_118, ReadsTwoConsecutiveWords_118) {
    std::vector<byte> data = {0x01, 0x00, 0x02, 0x00};
    auto io = createMemIo(data);
    uint16_t first = readWORDTag(io);
    uint16_t second = readWORDTag(io);
    EXPECT_EQ(first, 0x0001);
    EXPECT_EQ(second, 0x0002);
}

// Test that reading from an empty IO throws an exception (corrupted metadata)
TEST_F(ReadWORDTagTest_118, ThrowsOnEmptyIo_118) {
    std::vector<byte> data = {};
    auto io = createMemIo(data);
    EXPECT_THROW(readWORDTag(io), Exiv2::Error);
}

// Test that reading when only 1 byte is available throws an exception
TEST_F(ReadWORDTagTest_118, ThrowsOnInsufficientData_118) {
    std::vector<byte> data = {0x01};
    auto io = createMemIo(data);
    EXPECT_THROW(readWORDTag(io), Exiv2::Error);
}

// Test that reading past the end of a multi-byte buffer throws
TEST_F(ReadWORDTagTest_118, ThrowsWhenPositionedAtEndOfBuffer_118) {
    std::vector<byte> data = {0x01, 0x02};
    auto io = createMemIo(data);
    // Read the first word successfully
    readWORDTag(io);
    // Now at end, should throw
    EXPECT_THROW(readWORDTag(io), Exiv2::Error);
}

// Test reading from a specific offset (after seeking)
TEST_F(ReadWORDTagTest_118, ReadsFromMiddleOfBuffer_118) {
    std::vector<byte> data = {0x00, 0x00, 0x34, 0x12};
    auto io = createMemIo(data);
    io->seek(2, BasicIo::beg);
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 0x1234);
}

// Test with value 1 in little-endian
TEST_F(ReadWORDTagTest_118, ReadsValueOne_118) {
    std::vector<byte> data = {0x01, 0x00};
    auto io = createMemIo(data);
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 1);
}

// Test with 0x8000 (high bit set)
TEST_F(ReadWORDTagTest_118, ReadsHighBitSet_118) {
    // 0x8000 in little-endian: {0x00, 0x80}
    std::vector<byte> data = {0x00, 0x80};
    auto io = createMemIo(data);
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 0x8000);
}

// Test reading when exactly 2 bytes remain (boundary)
TEST_F(ReadWORDTagTest_118, ReadsExactlyTwoBytesRemaining_118) {
    std::vector<byte> data = {0xAA, 0xBB, 0xCC, 0xDD};
    auto io = createMemIo(data);
    io->seek(2, BasicIo::beg);
    // Exactly 2 bytes remain
    uint16_t result = readWORDTag(io);
    EXPECT_EQ(result, 0xDDCC);
}

// Test that only 1 byte remaining at current position throws
TEST_F(ReadWORDTagTest_118, ThrowsWhenOnlyOneByteRemaining_118) {
    std::vector<byte> data = {0xAA, 0xBB, 0xCC};
    auto io = createMemIo(data);
    io->seek(2, BasicIo::beg);
    // Only 1 byte remains
    EXPECT_THROW(readWORDTag(io), Exiv2::Error);
}

}  // namespace
