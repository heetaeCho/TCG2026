#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/asfvideo.hpp>
#include <cstring>
#include <memory>

using namespace Exiv2;

class AsfVideoHeaderReaderTest_1044 : public ::testing::Test {
protected:
    // ASF Header structure: 16-byte GUID + 8-byte little-endian size
    // Minimum valid header is 24 bytes
    static constexpr size_t GUID_SIZE = 16;
    static constexpr size_t HEADER_SIZE = 24; // GUID (16) + size (8)

    std::unique_ptr<BasicIo> createMemoryIoWithHeader(const uint8_t guid[16], uint64_t size) {
        std::vector<uint8_t> data(HEADER_SIZE);
        std::memcpy(data.data(), guid, GUID_SIZE);
        // Write size as little-endian uint64_t
        for (int i = 0; i < 8; i++) {
            data[GUID_SIZE + i] = static_cast<uint8_t>((size >> (8 * i)) & 0xFF);
        }
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        io->open();
        return io;
    }

    std::unique_ptr<BasicIo> createMemoryIoFromRawData(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        io->open();
        return io;
    }
};

// Test that getSize returns the size read from the header
TEST_F(AsfVideoHeaderReaderTest_1044, GetSizeReturnsCorrectValue_1044) {
    uint8_t guid[16] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                         0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    uint64_t expectedSize = 100;
    auto io = createMemoryIoWithHeader(guid, expectedSize);
    AsfVideo::HeaderReader reader(io);
    EXPECT_EQ(reader.getSize(), expectedSize);
}

// Test that getRemainingSize returns size minus header overhead
TEST_F(AsfVideoHeaderReaderTest_1044, GetRemainingSizeReturnsValue_1044) {
    uint8_t guid[16] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                         0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    uint64_t size = 200;
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    // remaining_size should be size minus the 24-byte header that was read
    EXPECT_EQ(reader.getRemainingSize(), size - HEADER_SIZE);
}

// Test getId returns a non-empty DataBuf of GUID size
TEST_F(AsfVideoHeaderReaderTest_1044, GetIdReturnsGuidBuffer_1044) {
    uint8_t guid[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                         0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    uint64_t size = 50;
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    DataBuf& idBuf = reader.getId();
    EXPECT_EQ(idBuf.size(), GUID_SIZE);
}

// Test that getId contains the correct GUID bytes
TEST_F(AsfVideoHeaderReaderTest_1044, GetIdContainsCorrectGuidBytes_1044) {
    uint8_t guid[16] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11,
                         0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    uint64_t size = 48;
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    DataBuf& idBuf = reader.getId();
    ASSERT_EQ(idBuf.size(), GUID_SIZE);
    for (size_t i = 0; i < GUID_SIZE; i++) {
        EXPECT_EQ(idBuf.data()[i], guid[i]) << "Mismatch at byte " << i;
    }
}

// Test with minimum possible size (equal to header size = 24)
TEST_F(AsfVideoHeaderReaderTest_1044, MinimumSizeHeader_1044) {
    uint8_t guid[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint64_t size = HEADER_SIZE; // 24 bytes - just the header itself
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    EXPECT_EQ(reader.getSize(), size);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test with a large size value
TEST_F(AsfVideoHeaderReaderTest_1044, LargeSizeValue_1044) {
    uint8_t guid[16] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8,
                         0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0};
    uint64_t size = 0x0000FFFFFFFFFFFF; // Large but reasonable size
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    EXPECT_EQ(reader.getSize(), size);
}

// Test getSize is const-correct
TEST_F(AsfVideoHeaderReaderTest_1044, GetSizeIsConst_1044) {
    uint8_t guid[16] = {0};
    uint64_t size = 100;
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    const auto& constReader = reader;
    EXPECT_EQ(constReader.getSize(), size);
}

// Test getRemainingSize is const-correct
TEST_F(AsfVideoHeaderReaderTest_1044, GetRemainingSizeIsConst_1044) {
    uint8_t guid[16] = {0};
    uint64_t size = 100;
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    const auto& constReader = reader;
    EXPECT_EQ(constReader.getRemainingSize(), size - HEADER_SIZE);
}

// Test with size equal to 24 (header size) results in zero remaining
TEST_F(AsfVideoHeaderReaderTest_1044, ZeroRemainingSize_1044) {
    uint8_t guid[16] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                         0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    uint64_t size = 24;
    auto io = createMemoryIoWithHeader(guid, size);
    AsfVideo::HeaderReader reader(io);
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test with a known ASF header object GUID
TEST_F(AsfVideoHeaderReaderTest_1044, KnownAsfHeaderObjectGuid_1044) {
    // ASF Header Object GUID: 30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
    uint8_t asfHeaderGuid[16] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                                  0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    uint64_t size = 1024;
    auto io = createMemoryIoWithHeader(asfHeaderGuid, size);
    AsfVideo::HeaderReader reader(io);
    EXPECT_EQ(reader.getSize(), size);
    DataBuf& idBuf = reader.getId();
    ASSERT_EQ(idBuf.size(), GUID_SIZE);
    for (size_t i = 0; i < GUID_SIZE; i++) {
        EXPECT_EQ(idBuf.data()[i], asfHeaderGuid[i]);
    }
}
