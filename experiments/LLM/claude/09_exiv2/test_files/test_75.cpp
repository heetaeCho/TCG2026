#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <sstream>
#include <cstring>

// Include the necessary headers
#include <exiv2/riffvideo.hpp>
#include <exiv2/basicio.hpp>

using namespace Exiv2;

class RiffVideoHeaderReaderTest_75 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }

  // Helper to create a MemIo with specific data
  std::unique_ptr<BasicIo> createMemIoWithData(const std::vector<uint8_t>& data) {
    auto memIo = std::make_unique<MemIo>(data.data(), data.size());
    memIo->open();
    return memIo;
  }
};

// Test that HeaderReader correctly reads a valid RIFF chunk ID
TEST_F(RiffVideoHeaderReaderTest_75, ValidChunkIdIsRead_75) {
  // A RIFF header: 4-byte ID + 4-byte size (little-endian)
  // ID = "RIFF", size = 100 (0x64000000 in LE)
  std::vector<uint8_t> data = {
    'R', 'I', 'F', 'F',          // ID
    0x64, 0x00, 0x00, 0x00        // size = 100
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "RIFF");
}

// Test that HeaderReader correctly reads the size field
TEST_F(RiffVideoHeaderReaderTest_75, ValidChunkSizeIsRead_75) {
  std::vector<uint8_t> data = {
    'R', 'I', 'F', 'F',
    0x64, 0x00, 0x00, 0x00        // size = 100
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getSize(), 100u);
}

// Test with a different chunk ID (e.g., "LIST")
TEST_F(RiffVideoHeaderReaderTest_75, ListChunkIdIsRead_75) {
  std::vector<uint8_t> data = {
    'L', 'I', 'S', 'T',
    0x00, 0x01, 0x00, 0x00        // size = 256
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "LIST");
}

// Test with size = 0
TEST_F(RiffVideoHeaderReaderTest_75, ZeroSizeChunk_75) {
  std::vector<uint8_t> data = {
    'a', 'v', 'i', 'h',
    0x00, 0x00, 0x00, 0x00        // size = 0
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "avih");
  EXPECT_EQ(reader.getSize(), 0u);
}

// Test with a large size value
TEST_F(RiffVideoHeaderReaderTest_75, LargeSizeValue_75) {
  std::vector<uint8_t> data = {
    'd', 'a', 't', 'a',
    0xFF, 0xFF, 0xFF, 0x7F        // size = 0x7FFFFFFF = 2147483647
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "data");
  EXPECT_EQ(reader.getSize(), 0x7FFFFFFFu);
}

// Test getId returns a reference to the same string consistently
TEST_F(RiffVideoHeaderReaderTest_75, GetIdReturnsConsistentReference_75) {
  std::vector<uint8_t> data = {
    'R', 'I', 'F', 'F',
    0x0A, 0x00, 0x00, 0x00
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  const std::string& id1 = reader.getId();
  const std::string& id2 = reader.getId();
  EXPECT_EQ(&id1, &id2);
}

// Test with "fmt " chunk ID (with space)
TEST_F(RiffVideoHeaderReaderTest_75, FmtChunkIdWithSpace_75) {
  std::vector<uint8_t> data = {
    'f', 'm', 't', ' ',
    0x10, 0x00, 0x00, 0x00        // size = 16
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "fmt ");
  EXPECT_EQ(reader.getSize(), 16u);
}

// Test with maximum 4-byte size
TEST_F(RiffVideoHeaderReaderTest_75, MaxFourByteSizeValue_75) {
  std::vector<uint8_t> data = {
    'J', 'U', 'N', 'K',
    0xFF, 0xFF, 0xFF, 0xFF        // size = 0xFFFFFFFF = 4294967295
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "JUNK");
  EXPECT_EQ(reader.getSize(), 0xFFFFFFFFu);
}

// Test with numeric-like chunk ID
TEST_F(RiffVideoHeaderReaderTest_75, NumericChunkId_75) {
  std::vector<uint8_t> data = {
    '0', '1', 'w', 'b',
    0x20, 0x00, 0x00, 0x00        // size = 32
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "01wb");
  EXPECT_EQ(reader.getSize(), 32u);
}

// Test reading from empty IO should handle gracefully (boundary condition)
TEST_F(RiffVideoHeaderReaderTest_75, EmptyIoHandling_75) {
  std::vector<uint8_t> data = {};
  auto io = createMemIoWithData(data);
  
  try {
    RiffVideo::HeaderReader reader(io);
    // If it doesn't throw, the id should be empty or size should be 0
    // We just verify it doesn't crash
    reader.getId();
    reader.getSize();
  } catch (...) {
    // It's acceptable to throw on empty data
    SUCCEED();
  }
}

// Test reading from IO with insufficient data (only 4 bytes, missing size)
TEST_F(RiffVideoHeaderReaderTest_75, InsufficientDataHandling_75) {
  std::vector<uint8_t> data = {
    'R', 'I', 'F', 'F'
    // Missing size bytes
  };
  auto io = createMemIoWithData(data);
  
  try {
    RiffVideo::HeaderReader reader(io);
    // If it doesn't throw, just verify we can call methods
    reader.getId();
    reader.getSize();
  } catch (...) {
    // Acceptable to throw on insufficient data
    SUCCEED();
  }
}

// Test with "AVI " as chunk ID
TEST_F(RiffVideoHeaderReaderTest_75, AviChunkId_75) {
  std::vector<uint8_t> data = {
    'A', 'V', 'I', ' ',
    0x00, 0x10, 0x00, 0x00        // size = 4096
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "AVI ");
  EXPECT_EQ(reader.getSize(), 4096u);
}

// Test with "idx1" chunk ID
TEST_F(RiffVideoHeaderReaderTest_75, Idx1ChunkId_75) {
  std::vector<uint8_t> data = {
    'i', 'd', 'x', '1',
    0x80, 0x00, 0x00, 0x00        // size = 128
  };
  auto io = createMemIoWithData(data);
  
  RiffVideo::HeaderReader reader(io);
  EXPECT_EQ(reader.getId(), "idx1");
  EXPECT_EQ(reader.getSize(), 128u);
}
