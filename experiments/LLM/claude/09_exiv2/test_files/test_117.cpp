#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

// Include the header for readDWORDTag
#include "helper_functions.hpp"

// We need a mock or concrete BasicIo implementation for testing.
// Since BasicIo has virtual methods, we can use MemIo which is a concrete implementation,
// or we can create a mock. Let's use MemIo if available, otherwise mock.

// Using MemIo from exiv2
#include "exiv2/basicio.hpp"

namespace {

using namespace Exiv2;

class ReadDWORDTagTest_117 : public ::testing::Test {
protected:
    // Helper to create a MemIo with given data
    BasicIo::UniquePtr createMemIo(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        io->open();
        return io;
    }
};

// Test reading a DWORD value of zero
TEST_F(ReadDWORDTagTest_117, ReadsZeroValue_117) {
    std::vector<byte> data = {0x00, 0x00, 0x00, 0x00};
    auto io = createMemIo(data);
    
    uint32_t result = readDWORDTag(io);
    EXPECT_EQ(result, 0u);
}

// Test reading a known little-endian DWORD value
TEST_F(ReadDWORDTagTest_117, ReadsLittleEndianValue_117) {
    // Little-endian: 0x01 0x00 0x00 0x00 = 1
    std::vector<byte> data = {0x01, 0x00, 0x00, 0x00};
    auto io = createMemIo(data);
    
    uint32_t result = readDWORDTag(io);
    EXPECT_EQ(result, 1u);
}

// Test reading a larger little-endian DWORD value
TEST_F(ReadDWORDTagTest_117, ReadsLargerLittleEndianValue_117) {
    // Little-endian: 0x78 0x56 0x34 0x12 = 0x12345678
    std::vector<byte> data = {0x78, 0x56, 0x34, 0x12};
    auto io = createMemIo(data);
    
    uint32_t result = readDWORDTag(io);
    EXPECT_EQ(result, 0x12345678u);
}

// Test reading max DWORD value (0xFFFFFFFF)
TEST_F(ReadDWORDTagTest_117, ReadsMaxValue_117) {
    std::vector<byte> data = {0xFF, 0xFF, 0xFF, 0xFF};
    auto io = createMemIo(data);
    
    uint32_t result = readDWORDTag(io);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

// Test reading from a stream with more data than needed (only reads first 4 bytes from current position)
TEST_F(ReadDWORDTagTest_117, ReadsFromCurrentPosition_117) {
    std::vector<byte> data = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    auto io = createMemIo(data);
    
    uint32_t result1 = readDWORDTag(io);
    EXPECT_EQ(result1, 1u);
    
    uint32_t result2 = readDWORDTag(io);
    EXPECT_EQ(result2, 2u);
}

// Test that reading advances the position by 4 bytes
TEST_F(ReadDWORDTagTest_117, AdvancesPositionByFourBytes_117) {
    std::vector<byte> data = {0x0A, 0x0B, 0x0C, 0x0D, 0xEE, 0xEE, 0xEE, 0xEE};
    auto io = createMemIo(data);
    
    size_t posBefore = io->tell();
    readDWORDTag(io);
    size_t posAfter = io->tell();
    
    EXPECT_EQ(posAfter - posBefore, 4u);
}

// Test reading when not enough data is available (less than 4 bytes remaining)
TEST_F(ReadDWORDTagTest_117, ThrowsWhenNotEnoughData_117) {
    std::vector<byte> data = {0x01, 0x02, 0x03}; // Only 3 bytes
    auto io = createMemIo(data);
    
    EXPECT_THROW(readDWORDTag(io), Exiv2::Error);
}

// Test reading when no data is available (empty stream)
TEST_F(ReadDWORDTagTest_117, ThrowsWhenEmptyStream_117) {
    std::vector<byte> data = {};
    auto io = createMemIo(data);
    
    EXPECT_THROW(readDWORDTag(io), Exiv2::Error);
}

// Test reading when exactly at the end of stream
TEST_F(ReadDWORDTagTest_117, ThrowsWhenAtEndOfStream_117) {
    std::vector<byte> data = {0x01, 0x02, 0x03, 0x04};
    auto io = createMemIo(data);
    
    // Read the first DWORD successfully
    readDWORDTag(io);
    
    // Now we're at the end, should throw
    EXPECT_THROW(readDWORDTag(io), Exiv2::Error);
}

// Test reading with only 1 byte remaining
TEST_F(ReadDWORDTagTest_117, ThrowsWhenOnlyOneByteRemaining_117) {
    std::vector<byte> data = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto io = createMemIo(data);
    
    // Read the first DWORD successfully
    readDWORDTag(io);
    
    // Only 1 byte remaining, should throw
    EXPECT_THROW(readDWORDTag(io), Exiv2::Error);
}

// Test reading with only 2 bytes remaining
TEST_F(ReadDWORDTagTest_117, ThrowsWhenOnlyTwoBytesRemaining_117) {
    std::vector<byte> data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    auto io = createMemIo(data);
    
    readDWORDTag(io);
    
    // Only 2 bytes remaining
    EXPECT_THROW(readDWORDTag(io), Exiv2::Error);
}

// Test reading a specific known value: 256 in little-endian
TEST_F(ReadDWORDTagTest_117, Reads256InLittleEndian_117) {
    // 256 = 0x00000100, little-endian: 0x00, 0x01, 0x00, 0x00
    std::vector<byte> data = {0x00, 0x01, 0x00, 0x00};
    auto io = createMemIo(data);
    
    uint32_t result = readDWORDTag(io);
    EXPECT_EQ(result, 256u);
}

// Test reading from a seeked position within the stream
TEST_F(ReadDWORDTagTest_117, ReadsFromSeekedPosition_117) {
    std::vector<byte> data = {0x00, 0x00, 0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD};
    auto io = createMemIo(data);
    
    // Seek to offset 4
    io->seek(4, BasicIo::beg);
    
    uint32_t result = readDWORDTag(io);
    // Little-endian: 0xAA, 0xBB, 0xCC, 0xDD = 0xDDCCBBAA
    EXPECT_EQ(result, 0xDDCCBBAAu);
}

// Test multiple sequential reads
TEST_F(ReadDWORDTagTest_117, MultipleSequentialReads_117) {
    std::vector<byte> data = {
        0x01, 0x00, 0x00, 0x00,  // 1
        0x02, 0x00, 0x00, 0x00,  // 2
        0x03, 0x00, 0x00, 0x00   // 3
    };
    auto io = createMemIo(data);
    
    EXPECT_EQ(readDWORDTag(io), 1u);
    EXPECT_EQ(readDWORDTag(io), 2u);
    EXPECT_EQ(readDWORDTag(io), 3u);
}

// Boundary: exactly 4 bytes available
TEST_F(ReadDWORDTagTest_117, ExactlyFourBytesAvailable_117) {
    std::vector<byte> data = {0xDE, 0xAD, 0xBE, 0xEF};
    auto io = createMemIo(data);
    
    uint32_t result = readDWORDTag(io);
    // Little-endian: 0xDE, 0xAD, 0xBE, 0xEF = 0xEFBEADDE
    EXPECT_EQ(result, 0xEFBEADDEu);
}

}  // namespace
