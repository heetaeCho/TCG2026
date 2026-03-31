#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/asfvideo.hpp>

#include <cstring>
#include <memory>
#include <vector>

// ASF GUIDs are 16 bytes, and the header structure after that is typically
// 16 bytes GUID + 8 bytes size (little-endian uint64_t) = 24 bytes minimum.

namespace {

// Helper to create a buffer representing a minimal ASF header object
// GUID (16 bytes) + Size (8 bytes little-endian)
std::vector<Exiv2::byte> createAsfHeaderData(uint64_t size) {
    std::vector<Exiv2::byte> data(24, 0);
    // Fill GUID with some arbitrary bytes
    for (int i = 0; i < 16; i++) {
        data[i] = static_cast<Exiv2::byte>(i + 1);
    }
    // Write size as little-endian uint64_t
    for (int i = 0; i < 8; i++) {
        data[16 + i] = static_cast<Exiv2::byte>((size >> (8 * i)) & 0xFF);
    }
    return data;
}

class AsfVideoHeaderReaderTest_1045 : public ::testing::Test {
 protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getRemainingSize returns a value consistent with the header
// When size is exactly 24 (minimum: 16 GUID + 8 size field), remaining should be 0
TEST_F(AsfVideoHeaderReaderTest_1045, GetRemainingSizeWithMinimalHeader_1045) {
    uint64_t totalSize = 24;  // 16 (GUID) + 8 (size field) = 24, so remaining = 0
    auto data = createAsfHeaderData(totalSize);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    // remaining_size_ should be totalSize - 24 = 0
    EXPECT_EQ(reader.getRemainingSize(), 0u);
}

// Test with a larger size value
TEST_F(AsfVideoHeaderReaderTest_1045, GetRemainingSizeWithLargerHeader_1045) {
    uint64_t totalSize = 1024;
    auto data = createAsfHeaderData(totalSize);
    // Pad data to have enough bytes (though reader just reads header)
    data.resize(1024, 0);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    // remaining_size_ should be totalSize - 24 = 1000
    EXPECT_EQ(reader.getRemainingSize(), 1000u);
}

// Test with size equal to just beyond the header
TEST_F(AsfVideoHeaderReaderTest_1045, GetRemainingSizeWithOneByteRemaining_1045) {
    uint64_t totalSize = 25;  // 1 byte remaining
    auto data = createAsfHeaderData(totalSize);
    data.resize(25, 0);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getRemainingSize(), 1u);
}

// Test getSize returns the size read from the header
TEST_F(AsfVideoHeaderReaderTest_1045, GetSizeReturnsCorrectValue_1045) {
    uint64_t totalSize = 500;
    auto data = createAsfHeaderData(totalSize);
    data.resize(500, 0);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getSize(), totalSize);
}

// Test getId returns a non-empty DataBuf of GUID size (16 bytes)
TEST_F(AsfVideoHeaderReaderTest_1045, GetIdReturnsGuidSizedBuffer_1045) {
    uint64_t totalSize = 24;
    auto data = createAsfHeaderData(totalSize);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    Exiv2::DataBuf& id = reader.getId();
    EXPECT_EQ(id.size(), 16u);
}

// Test that getId returns the correct GUID bytes
TEST_F(AsfVideoHeaderReaderTest_1045, GetIdReturnsCorrectGuidBytes_1045) {
    uint64_t totalSize = 24;
    auto data = createAsfHeaderData(totalSize);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    Exiv2::DataBuf& id = reader.getId();
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(id.data()[i], static_cast<Exiv2::byte>(i + 1)) << "Mismatch at byte " << i;
    }
}

// Test with a large remaining size
TEST_F(AsfVideoHeaderReaderTest_1045, GetRemainingSizeWithLargeValue_1045) {
    uint64_t totalSize = 1000000;
    auto data = createAsfHeaderData(totalSize);
    // We don't need to have all the data in memory, just enough to read the header
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getRemainingSize(), totalSize - 24);
}

// Test that getSize and getRemainingSize are consistent
TEST_F(AsfVideoHeaderReaderTest_1045, SizeAndRemainingSizeConsistent_1045) {
    uint64_t totalSize = 256;
    auto data = createAsfHeaderData(totalSize);
    data.resize(256, 0);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::AsfVideo::HeaderReader reader(io);
    
    // remaining_size should be size - 24 (GUID + size field)
    EXPECT_EQ(reader.getSize(), totalSize);
    EXPECT_EQ(reader.getRemainingSize(), totalSize - 24);
    EXPECT_EQ(reader.getSize() - 24, reader.getRemainingSize());
}

}  // namespace
