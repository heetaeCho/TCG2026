#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <sstream>
#include <cstring>

// Include the header under test
#include "exiv2/riffvideo.hpp"
#include "exiv2/basicio.hpp"

using namespace Exiv2;

// Helper to create a MemIo with specific bytes
static BasicIo::UniquePtr createMemIoWithData(const std::vector<uint8_t>& data) {
    auto memIo = std::make_unique<MemIo>(data.data(), data.size());
    return memIo;
}

// Helper to create a RIFF-like chunk header (4-byte ID + 4-byte little-endian size)
static std::vector<uint8_t> makeChunkHeader(const std::string& id, uint32_t size) {
    std::vector<uint8_t> data;
    // Write 4-byte ID (padded with spaces if shorter)
    for (size_t i = 0; i < 4; ++i) {
        if (i < id.size())
            data.push_back(static_cast<uint8_t>(id[i]));
        else
            data.push_back(' ');
    }
    // Write 4-byte little-endian size
    data.push_back(static_cast<uint8_t>(size & 0xFF));
    data.push_back(static_cast<uint8_t>((size >> 8) & 0xFF));
    data.push_back(static_cast<uint8_t>((size >> 16) & 0xFF));
    data.push_back(static_cast<uint8_t>((size >> 24) & 0xFF));
    return data;
}

class RiffVideoHeaderReaderTest_74 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that HeaderReader reads a normal chunk header with a known size
TEST_F(RiffVideoHeaderReaderTest_74, NormalChunkHeader_GetSize_74) {
    auto data = makeChunkHeader("RIFF", 1024);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getSize(), 1024u);
}

// Test that HeaderReader reads the correct ID from a normal chunk header
TEST_F(RiffVideoHeaderReaderTest_74, NormalChunkHeader_GetId_74) {
    auto data = makeChunkHeader("RIFF", 1024);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getId(), "RIFF");
}

// Test with zero size
TEST_F(RiffVideoHeaderReaderTest_74, ZeroSize_74) {
    auto data = makeChunkHeader("data", 0);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getSize(), 0u);
    EXPECT_EQ(reader.getId(), "data");
}

// Test with maximum 32-bit size value
TEST_F(RiffVideoHeaderReaderTest_74, MaxUint32Size_74) {
    auto data = makeChunkHeader("LIST", 0xFFFFFFFF);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getSize(), 0xFFFFFFFFu);
}

// Test with a typical AVI chunk ID
TEST_F(RiffVideoHeaderReaderTest_74, AviChunkId_74) {
    auto data = makeChunkHeader("AVI ", 512);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getId(), "AVI ");
    EXPECT_EQ(reader.getSize(), 512u);
}

// Test with "fmt " chunk ID (common in RIFF/WAV)
TEST_F(RiffVideoHeaderReaderTest_74, FmtChunkId_74) {
    auto data = makeChunkHeader("fmt ", 16);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getId(), "fmt ");
    EXPECT_EQ(reader.getSize(), 16u);
}

// Test with "LIST" chunk ID
TEST_F(RiffVideoHeaderReaderTest_74, ListChunkHeader_74) {
    auto data = makeChunkHeader("LIST", 256);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getId(), "LIST");
    EXPECT_EQ(reader.getSize(), 256u);
}

// Test with a size of 1 (boundary)
TEST_F(RiffVideoHeaderReaderTest_74, SizeOne_74) {
    auto data = makeChunkHeader("test", 1);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getSize(), 1u);
}

// Test with a large but non-max size
TEST_F(RiffVideoHeaderReaderTest_74, LargeSize_74) {
    auto data = makeChunkHeader("hdrl", 0x7FFFFFFF);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getSize(), 0x7FFFFFFFu);
    EXPECT_EQ(reader.getId(), "hdrl");
}

// Test that getSize returns consistent results on repeated calls
TEST_F(RiffVideoHeaderReaderTest_74, GetSizeIsIdempotent_74) {
    auto data = makeChunkHeader("RIFF", 42);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    uint64_t size1 = reader.getSize();
    uint64_t size2 = reader.getSize();
    EXPECT_EQ(size1, size2);
    EXPECT_EQ(size1, 42u);
}

// Test that getId returns consistent results on repeated calls
TEST_F(RiffVideoHeaderReaderTest_74, GetIdIsIdempotent_74) {
    auto data = makeChunkHeader("RIFF", 42);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    const std::string& id1 = reader.getId();
    const std::string& id2 = reader.getId();
    EXPECT_EQ(id1, id2);
    EXPECT_EQ(id1, "RIFF");
}

// Test with insufficient data in IO (less than 8 bytes) - error/boundary case
TEST_F(RiffVideoHeaderReaderTest_74, InsufficientData_74) {
    // Only 4 bytes provided instead of 8
    std::vector<uint8_t> data = {'R', 'I', 'F', 'F'};
    auto io = createMemIoWithData(data);
    
    // Depending on implementation, this may throw or produce default values
    try {
        RiffVideo::HeaderReader reader(io);
        // If it doesn't throw, size should be 0 or some default
        // We just verify it doesn't crash
        reader.getSize();
        reader.getId();
    } catch (const std::exception&) {
        // Expected - insufficient data may cause an exception
        SUCCEED();
    }
}

// Test with empty IO - error/boundary case
TEST_F(RiffVideoHeaderReaderTest_74, EmptyIo_74) {
    std::vector<uint8_t> data;
    auto io = createMemIoWithData(data);
    
    try {
        RiffVideo::HeaderReader reader(io);
        // If it doesn't throw, just verify we can call getters
        reader.getSize();
        reader.getId();
    } catch (const std::exception&) {
        // Expected for empty data
        SUCCEED();
    }
}

// Test with numeric characters in chunk ID
TEST_F(RiffVideoHeaderReaderTest_74, NumericChunkId_74) {
    auto data = makeChunkHeader("00dc", 4096);
    auto io = createMemIoWithData(data);
    
    RiffVideo::HeaderReader reader(io);
    
    EXPECT_EQ(reader.getId(), "00dc");
    EXPECT_EQ(reader.getSize(), 4096u);
}
