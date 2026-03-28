#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

// We need to use MemIo (a concrete BasicIo implementation) for testing
#include "exiv2/bmffimage.hpp"

// If MemIo is available from basicio.hpp
namespace {

// Helper to create a MemIo with specific content
std::unique_ptr<Exiv2::BasicIo> createMemIo(const std::vector<uint8_t>& data) {
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    io->open();
    return io;
}

// Helper to create a valid ASF header buffer
// GUID (16 bytes) + QWORD size (8 bytes) = 24 bytes minimum
std::vector<uint8_t> createValidHeader(uint64_t size) {
    std::vector<uint8_t> data(24, 0);
    // Fill GUID with some recognizable pattern
    for (int i = 0; i < 16; i++) {
        data[i] = static_cast<uint8_t>(i + 1);
    }
    // Write size as little-endian uint64_t
    for (int i = 0; i < 8; i++) {
        data[16 + i] = static_cast<uint8_t>((size >> (8 * i)) & 0xFF);
    }
    return data;
}

} // anonymous namespace

class AsfVideoHeaderReaderTest_2199 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: HeaderReader with valid data containing exactly minimum size (GUID + QWORD = 24)
TEST_F(AsfVideoHeaderReaderTest_2199, ValidMinimumSizeHeader_2199) {
    // size_ = 24 (GUID + QWORD), so remaining_size_ = 24 - 16 - 8 = 0
    auto data = createValidHeader(24);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 24u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader with valid data and a larger size value
TEST_F(AsfVideoHeaderReaderTest_2199, ValidLargerSizeHeader_2199) {
    // size_ = 100, remaining_size_ = 100 - 16 - 8 = 76
    auto data = createValidHeader(100);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 100u);
    EXPECT_EQ(reader.getRemainingSize(), 76u);
}

// Test: HeaderReader reads the correct GUID bytes
TEST_F(AsfVideoHeaderReaderTest_2199, ReadsCorrectGUID_2199) {
    auto data = createValidHeader(24);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    Exiv2::DataBuf& id = reader.getId();
    EXPECT_EQ(id.size(), 16u);
    // Verify the GUID bytes match what we put in
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(id.read_uint8(i), static_cast<uint8_t>(i + 1));
    }
}

// Test: HeaderReader with empty IO (size 0) - not enough data
TEST_F(AsfVideoHeaderReaderTest_2199, EmptyIoNoRead_2199) {
    std::vector<uint8_t> data;
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    // When there's not enough data, size_ and remaining_size_ should remain at default (0)
    EXPECT_EQ(reader.getSize(), 0u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader with data smaller than GUID + QWORD (e.g., 23 bytes)
TEST_F(AsfVideoHeaderReaderTest_2199, InsufficientDataNoRead_2199) {
    std::vector<uint8_t> data(23, 0); // One byte short
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 0u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader with exactly GUID bytes (16 bytes, missing QWORD)
TEST_F(AsfVideoHeaderReaderTest_2199, OnlyGuidBytesNoQword_2199) {
    std::vector<uint8_t> data(16, 0xAB);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 0u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader where the size field is less than GUID + QWORD
// In this case remaining_size_ should stay 0 because the condition size_ >= GUID + QWORD fails
TEST_F(AsfVideoHeaderReaderTest_2199, SizeSmallerThanMinimum_2199) {
    // Write size = 10 (less than 24)
    auto data = createValidHeader(10);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 10u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader where size is exactly GUID + QWORD - 1 = 23
TEST_F(AsfVideoHeaderReaderTest_2199, SizeExactlyOneLessThanMinimum_2199) {
    auto data = createValidHeader(23);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 23u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader with a very large size value
TEST_F(AsfVideoHeaderReaderTest_2199, VeryLargeSizeValue_2199) {
    uint64_t largeSize = 0xFFFFFFFFFFFFFFULL; // A very large but valid size
    auto data = createValidHeader(largeSize);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), largeSize);
    EXPECT_EQ(reader.getRemainingSize(), largeSize - 16 - 8);
}

// Test: HeaderReader with size = 0 (zero size in the data)
TEST_F(AsfVideoHeaderReaderTest_2199, ZeroSizeField_2199) {
    auto data = createValidHeader(0);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 0u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader with IO positioned partway through (tell() > 0)
TEST_F(AsfVideoHeaderReaderTest_2199, IoPositionedPartway_2199) {
    // Put some padding before the actual header data
    std::vector<uint8_t> headerData = createValidHeader(50);
    std::vector<uint8_t> data(10, 0x00); // 10 bytes padding
    data.insert(data.end(), headerData.begin(), headerData.end());

    auto io = createMemIo(data);
    // Seek past the padding
    io->seek(10, Exiv2::BasicIo::beg);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 50u);
    EXPECT_EQ(reader.getRemainingSize(), 50u - 16u - 8u);
}

// Test: HeaderReader with IO positioned such that remaining bytes < GUID + QWORD
TEST_F(AsfVideoHeaderReaderTest_2199, IoPositionedNearEnd_2199) {
    std::vector<uint8_t> data(30, 0x00);
    auto io = createMemIo(data);
    // Seek to position 8, leaving only 22 bytes (< 24 = GUID + QWORD)
    io->seek(8, Exiv2::BasicIo::beg);

    Exiv2::AsfVideo::HeaderReader reader(io);

    // 30 - 8 = 22 < 24, so condition fails
    EXPECT_EQ(reader.getSize(), 0u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test: HeaderReader getId returns a buffer of GUID size
TEST_F(AsfVideoHeaderReaderTest_2199, GetIdReturnsGuidSizeBuffer_2199) {
    auto data = createValidHeader(24);
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getId().size(), 16u);
}

// Test: HeaderReader with all zeros in GUID
TEST_F(AsfVideoHeaderReaderTest_2199, AllZerosGuid_2199) {
    std::vector<uint8_t> data(24, 0);
    // Size = 24 in little-endian at offset 16
    data[16] = 24;
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 24u);
    EXPECT_EQ(reader.getRemainingSize(), 0u);

    // GUID should be all zeros
    for (size_t i = 0; i < 16; i++) {
        EXPECT_EQ(reader.getId().read_uint8(i), 0u);
    }
}

// Test: HeaderReader with all 0xFF in GUID
TEST_F(AsfVideoHeaderReaderTest_2199, AllOnesGuid_2199) {
    std::vector<uint8_t> data(24, 0xFF);
    // Need to set size properly - all 0xFF would be max uint64
    // Let's set a reasonable size
    uint64_t size = 24;
    for (int i = 0; i < 8; i++) {
        data[16 + i] = static_cast<uint8_t>((size >> (8 * i)) & 0xFF);
    }
    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader(io);

    EXPECT_EQ(reader.getSize(), 24u);

    // GUID bytes should all be 0xFF
    for (size_t i = 0; i < 16; i++) {
        EXPECT_EQ(reader.getId().read_uint8(i), 0xFF);
    }
}

// Test: Multiple HeaderReaders from same IO sequentially
TEST_F(AsfVideoHeaderReaderTest_2199, SequentialReads_2199) {
    // Create two headers back to back
    auto header1 = createValidHeader(24);
    auto header2 = createValidHeader(48);
    // Modify header2 GUID to be distinguishable
    for (int i = 0; i < 16; i++) {
        header2[i] = static_cast<uint8_t>(0xA0 + i);
    }

    std::vector<uint8_t> data;
    data.insert(data.end(), header1.begin(), header1.end());
    data.insert(data.end(), header2.begin(), header2.end());

    auto io = createMemIo(data);

    Exiv2::AsfVideo::HeaderReader reader1(io);
    EXPECT_EQ(reader1.getSize(), 24u);
    EXPECT_EQ(reader1.getRemainingSize(), 0u);

    Exiv2::AsfVideo::HeaderReader reader2(io);
    EXPECT_EQ(reader2.getSize(), 48u);
    EXPECT_EQ(reader2.getRemainingSize(), 24u);

    // Verify second reader has different GUID
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(reader2.getId().read_uint8(i), static_cast<uint8_t>(0xA0 + i));
    }
}
