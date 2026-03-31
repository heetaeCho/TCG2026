#include <gtest/gtest.h>
#include <cstdint>
#include "exiv2/types.hpp"
#include "pngchunk_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PngChunkTest_1235 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test normal decoding of IHDR chunk with known width and height
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_NormalValues_1235) {
  // Create a DataBuf with 8 bytes: 4 bytes for width, 4 bytes for height (big-endian)
  DataBuf data(8);
  // Width = 1920 = 0x00000780
  data.write_uint32(0, 1920, bigEndian);
  // Height = 1080 = 0x00000438
  data.write_uint32(4, 1080, bigEndian);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 1920u);
  EXPECT_EQ(height, 1080u);
}

// Test decoding IHDR chunk with zero dimensions
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_ZeroDimensions_1235) {
  DataBuf data(8);
  data.write_uint32(0, 0, bigEndian);
  data.write_uint32(4, 0, bigEndian);

  uint32_t width = 999;
  uint32_t height = 999;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 0u);
  EXPECT_EQ(height, 0u);
}

// Test decoding IHDR chunk with maximum uint32 values
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_MaxValues_1235) {
  DataBuf data(8);
  data.write_uint32(0, 0xFFFFFFFF, bigEndian);
  data.write_uint32(4, 0xFFFFFFFF, bigEndian);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 0xFFFFFFFFu);
  EXPECT_EQ(height, 0xFFFFFFFFu);
}

// Test decoding IHDR chunk with width = 1, height = 1
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_MinimalDimensions_1235) {
  DataBuf data(8);
  data.write_uint32(0, 1, bigEndian);
  data.write_uint32(4, 1, bigEndian);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 1u);
  EXPECT_EQ(height, 1u);
}

// Test decoding IHDR chunk with asymmetric dimensions
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_AsymmetricDimensions_1235) {
  DataBuf data(8);
  data.write_uint32(0, 4096, bigEndian);
  data.write_uint32(4, 2048, bigEndian);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 4096u);
  EXPECT_EQ(height, 2048u);
}

// Test decoding IHDR chunk where width is zero but height is nonzero
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_ZeroWidthNonZeroHeight_1235) {
  DataBuf data(8);
  data.write_uint32(0, 0, bigEndian);
  data.write_uint32(4, 768, bigEndian);

  uint32_t width = 999;
  uint32_t height = 999;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 0u);
  EXPECT_EQ(height, 768u);
}

// Test decoding IHDR chunk where height is zero but width is nonzero
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_NonZeroWidthZeroHeight_1235) {
  DataBuf data(8);
  data.write_uint32(0, 1024, bigEndian);
  data.write_uint32(4, 0, bigEndian);

  uint32_t width = 999;
  uint32_t height = 999;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 1024u);
  EXPECT_EQ(height, 0u);
}

// Test decoding IHDR chunk with a large buffer (extra data after the 8 bytes)
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_LargerBuffer_1235) {
  // IHDR in PNG typically has 13 bytes of data; we only read first 8
  DataBuf data(13);
  data.write_uint32(0, 800, bigEndian);
  data.write_uint32(4, 600, bigEndian);
  // Extra bytes (bit depth, color type, etc.) — should not affect width/height
  data.write_uint8(8, 8);
  data.write_uint8(9, 2);
  data.write_uint8(10, 0);
  data.write_uint8(11, 0);
  data.write_uint8(12, 0);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 800u);
  EXPECT_EQ(height, 600u);
}

// Test decoding IHDR chunk with specific byte patterns to verify big-endian reading
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_BigEndianVerification_1235) {
  // Manually create bytes: width = 0x01020304, height = 0x05060708
  uint8_t rawData[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  DataBuf data(rawData, 8);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 0x01020304u);
  EXPECT_EQ(height, 0x05060708u);
}

// Test decoding IHDR chunk with power-of-two dimensions
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_PowerOfTwoDimensions_1235) {
  DataBuf data(8);
  data.write_uint32(0, 256, bigEndian);
  data.write_uint32(4, 512, bigEndian);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 256u);
  EXPECT_EQ(height, 512u);
}

// Test that width and height are independently read (no cross-contamination)
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_IndependentFields_1235) {
  DataBuf data(8);
  data.write_uint32(0, 0x00000001, bigEndian);
  data.write_uint32(4, 0x80000000, bigEndian);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 1u);
  EXPECT_EQ(height, 0x80000000u);
}

// Test with exactly 8 bytes buffer (boundary: minimum required size)
TEST_F(PngChunkTest_1235, DecodeIHDRChunk_ExactlyEightBytes_1235) {
  DataBuf data(8);
  data.write_uint32(0, 640, bigEndian);
  data.write_uint32(4, 480, bigEndian);

  uint32_t width = 0;
  uint32_t height = 0;
  PngChunk::decodeIHDRChunk(data, &width, &height);

  EXPECT_EQ(width, 640u);
  EXPECT_EQ(height, 480u);
}
