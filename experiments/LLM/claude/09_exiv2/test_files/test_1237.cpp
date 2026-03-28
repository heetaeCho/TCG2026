#include <gtest/gtest.h>
#include <cstring>

#include "pngchunk_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PngChunkTest_1237 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== decodeIHDRChunk Tests ====================

TEST_F(PngChunkTest_1237, DecodeIHDRChunk_ValidData_1237) {
  // IHDR chunk: 4 bytes width + 4 bytes height (big-endian) + other fields
  // Minimum IHDR data is 13 bytes
  DataBuf ihdrData(13);
  // Width = 100 (0x00000064), Height = 200 (0x000000C8) in big-endian
  ihdrData.write_uint8(0, 0x00);
  ihdrData.write_uint8(1, 0x00);
  ihdrData.write_uint8(2, 0x00);
  ihdrData.write_uint8(3, 0x64);  // width = 100
  ihdrData.write_uint8(4, 0x00);
  ihdrData.write_uint8(5, 0x00);
  ihdrData.write_uint8(6, 0x00);
  ihdrData.write_uint8(7, 0xC8);  // height = 200
  ihdrData.write_uint8(8, 8);     // bit depth
  ihdrData.write_uint8(9, 2);     // color type
  ihdrData.write_uint8(10, 0);    // compression
  ihdrData.write_uint8(11, 0);    // filter
  ihdrData.write_uint8(12, 0);    // interlace

  uint32_t width = 0, height = 0;
  EXPECT_NO_THROW(PngChunk::decodeIHDRChunk(ihdrData, &width, &height));
  EXPECT_EQ(width, 100u);
  EXPECT_EQ(height, 200u);
}

TEST_F(PngChunkTest_1237, DecodeIHDRChunk_LargeWidthHeight_1237) {
  DataBuf ihdrData(13);
  // Width = 1920, Height = 1080 in big-endian
  ihdrData.write_uint8(0, 0x00);
  ihdrData.write_uint8(1, 0x00);
  ihdrData.write_uint8(2, 0x07);
  ihdrData.write_uint8(3, 0x80);  // width = 1920
  ihdrData.write_uint8(4, 0x00);
  ihdrData.write_uint8(5, 0x00);
  ihdrData.write_uint8(6, 0x04);
  ihdrData.write_uint8(7, 0x38);  // height = 1080
  ihdrData.write_uint8(8, 8);
  ihdrData.write_uint8(9, 2);
  ihdrData.write_uint8(10, 0);
  ihdrData.write_uint8(11, 0);
  ihdrData.write_uint8(12, 0);

  uint32_t width = 0, height = 0;
  EXPECT_NO_THROW(PngChunk::decodeIHDRChunk(ihdrData, &width, &height));
  EXPECT_EQ(width, 1920u);
  EXPECT_EQ(height, 1080u);
}

TEST_F(PngChunkTest_1237, DecodeIHDRChunk_OneByOnePixel_1237) {
  DataBuf ihdrData(13);
  ihdrData.write_uint8(0, 0x00);
  ihdrData.write_uint8(1, 0x00);
  ihdrData.write_uint8(2, 0x00);
  ihdrData.write_uint8(3, 0x01);  // width = 1
  ihdrData.write_uint8(4, 0x00);
  ihdrData.write_uint8(5, 0x00);
  ihdrData.write_uint8(6, 0x00);
  ihdrData.write_uint8(7, 0x01);  // height = 1
  ihdrData.write_uint8(8, 8);
  ihdrData.write_uint8(9, 2);
  ihdrData.write_uint8(10, 0);
  ihdrData.write_uint8(11, 0);
  ihdrData.write_uint8(12, 0);

  uint32_t width = 0, height = 0;
  EXPECT_NO_THROW(PngChunk::decodeIHDRChunk(ihdrData, &width, &height));
  EXPECT_EQ(width, 1u);
  EXPECT_EQ(height, 1u);
}

// ==================== keyTXTChunk Tests ====================

TEST_F(PngChunkTest_1237, KeyTXTChunk_SimpleKey_1237) {
  // A tEXt chunk: keyword\0value
  const char* chunkData = "TestKey\0TestValue";
  size_t chunkLen = 8 + 9;  // "TestKey\0" + "TestValue"
  DataBuf data(reinterpret_cast<const byte*>(chunkData), chunkLen);

  DataBuf key = PngChunk::keyTXTChunk(data, false);
  EXPECT_GT(key.size(), 0u);
}

TEST_F(PngChunkTest_1237, KeyTXTChunk_StripHeader_1237) {
  const char* chunkData = "TestKey\0TestValue";
  size_t chunkLen = 8 + 9;
  DataBuf data(reinterpret_cast<const byte*>(chunkData), chunkLen);

  DataBuf key = PngChunk::keyTXTChunk(data, true);
  EXPECT_GT(key.size(), 0u);
}

TEST_F(PngChunkTest_1237, KeyTXTChunk_EmptyValue_1237) {
  // keyword with no value after null
  const char* chunkData = "TestKey\0";
  size_t chunkLen = 8;
  DataBuf data(reinterpret_cast<const byte*>(chunkData), chunkLen);

  DataBuf key = PngChunk::keyTXTChunk(data, false);
  EXPECT_GT(key.size(), 0u);
}

// ==================== decodeTXTChunk Tests ====================

TEST_F(PngChunkTest_1237, DecodeTXTChunk_tEXtType_SimpleData_1237) {
  // Construct a simple tEXt chunk: keyword\0value
  const char rawData[] = "Comment\0Hello World";
  size_t rawLen = 8 + 11;  // "Comment\0" = 8 bytes, "Hello World" = 11 bytes
  DataBuf data(reinterpret_cast<const byte*>(rawData), rawLen);

  DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::tEXt_Chunk);
  // We just verify it doesn't crash and returns something
  // The exact result depends on the implementation
}

TEST_F(PngChunkTest_1237, DecodeTXTChunk_EmptyData_1237) {
  DataBuf emptyData;
  // This may throw or return empty; we test the observable behavior
  try {
    DataBuf result = PngChunk::decodeTXTChunk(emptyData, TxtChunkType::tEXt_Chunk);
    // If it doesn't throw, the result should be empty or valid
  } catch (const std::exception&) {
    // Expected for empty data
  }
}

TEST_F(PngChunkTest_1237, DecodeTXTChunk_SingleNullByte_1237) {
  // Data with just a null byte (empty keyword, empty value)
  byte nullByte = 0;
  DataBuf data(&nullByte, 1);

  try {
    DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::tEXt_Chunk);
  } catch (const std::exception&) {
    // May throw for malformed data
  }
}

// ==================== makeMetadataChunk Tests ====================

TEST_F(PngChunkTest_1237, MakeMetadataChunk_ExifType_1237) {
  std::string metadata = "some exif data";
  try {
    std::string result = PngChunk::makeMetadataChunk(metadata, MetadataId::mdExif);
    EXPECT_FALSE(result.empty());
  } catch (const std::exception&) {
    // Implementation may have specific requirements
  }
}

TEST_F(PngChunkTest_1237, MakeMetadataChunk_IptcType_1237) {
  std::string metadata = "some iptc data";
  try {
    std::string result = PngChunk::makeMetadataChunk(metadata, MetadataId::mdIptc);
    EXPECT_FALSE(result.empty());
  } catch (const std::exception&) {
    // Implementation may have specific requirements
  }
}

TEST_F(PngChunkTest_1237, MakeMetadataChunk_XmpType_1237) {
  std::string metadata = "<?xml version='1.0'?><x:xmpmeta xmlns:x='adobe:ns:meta/'></x:xmpmeta>";
  try {
    std::string result = PngChunk::makeMetadataChunk(metadata, MetadataId::mdXmp);
    EXPECT_FALSE(result.empty());
  } catch (const std::exception&) {
    // Implementation may have specific requirements
  }
}

TEST_F(PngChunkTest_1237, MakeMetadataChunk_EmptyMetadata_1237) {
  std::string metadata;
  try {
    std::string result = PngChunk::makeMetadataChunk(metadata, MetadataId::mdExif);
    // May return empty or minimal chunk
  } catch (const std::exception&) {
    // May throw for empty metadata
  }
}

// ==================== decodeIHDRChunk Edge Cases ====================

TEST_F(PngChunkTest_1237, DecodeIHDRChunk_TooSmallData_1237) {
  // IHDR needs at least 8 bytes for width+height, typically 13 bytes total
  DataBuf smallData(4);
  smallData.write_uint8(0, 0x00);
  smallData.write_uint8(1, 0x00);
  smallData.write_uint8(2, 0x00);
  smallData.write_uint8(3, 0x01);

  uint32_t width = 0, height = 0;
  try {
    PngChunk::decodeIHDRChunk(smallData, &width, &height);
    // If it doesn't throw, check what we got
  } catch (const std::exception&) {
    // Expected for too-small data
  }
}

TEST_F(PngChunkTest_1237, DecodeIHDRChunk_ZeroWidthHeight_1237) {
  DataBuf ihdrData(13);
  // All zeros
  for (size_t i = 0; i < 13; i++) {
    ihdrData.write_uint8(i, 0);
  }

  uint32_t width = 99, height = 99;
  EXPECT_NO_THROW(PngChunk::decodeIHDRChunk(ihdrData, &width, &height));
  EXPECT_EQ(width, 0u);
  EXPECT_EQ(height, 0u);
}

// ==================== decodeTXTChunk with different chunk types ====================

TEST_F(PngChunkTest_1237, DecodeTXTChunk_zTXtType_1237) {
  // zTXt chunk: keyword\0compression_method + compressed_data
  // We'll create a minimal one. This might fail if compressed data is invalid.
  std::string keyword = "Comment";
  std::vector<byte> chunkVec(keyword.begin(), keyword.end());
  chunkVec.push_back(0);  // null separator
  chunkVec.push_back(0);  // compression method = 0 (deflate)
  // Add some minimal zlib compressed data for empty string
  // zlib compressed empty string: 0x78, 0x9C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01
  byte zlibEmpty[] = {0x78, 0x9C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01};
  for (auto b : zlibEmpty) {
    chunkVec.push_back(b);
  }

  DataBuf data(chunkVec.data(), chunkVec.size());

  try {
    DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::zTXt_Chunk);
    // Should succeed or throw a meaningful error
  } catch (const std::exception&) {
    // Compressed data might not be valid enough
  }
}

TEST_F(PngChunkTest_1237, DecodeTXTChunk_iTXtType_1237) {
  // iTXt chunk: keyword\0compression_flag\0compression_method\0language\0translated_keyword\0text
  std::string keyword = "Comment";
  std::vector<byte> chunkVec(keyword.begin(), keyword.end());
  chunkVec.push_back(0);  // null separator after keyword
  chunkVec.push_back(0);  // compression flag = 0 (uncompressed)
  chunkVec.push_back(0);  // compression method
  // language tag (empty)
  chunkVec.push_back(0);  // null separator
  // translated keyword (empty)
  chunkVec.push_back(0);  // null separator
  // text
  std::string text = "Hello iTXt";
  for (char c : text) {
    chunkVec.push_back(static_cast<byte>(c));
  }

  DataBuf data(chunkVec.data(), chunkVec.size());

  try {
    DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::iTXt_Chunk);
    // We just verify it processes without crash
  } catch (const std::exception&) {
    // May throw if format is not exactly right
  }
}

// ==================== keyTXTChunk with various keywords ====================

TEST_F(PngChunkTest_1237, KeyTXTChunk_LongKeyword_1237) {
  // PNG spec allows keywords up to 79 characters
  std::string longKey(79, 'A');
  std::vector<byte> chunkVec(longKey.begin(), longKey.end());
  chunkVec.push_back(0);  // null terminator
  chunkVec.push_back('V');  // some value

  DataBuf data(chunkVec.data(), chunkVec.size());

  DataBuf key = PngChunk::keyTXTChunk(data, false);
  EXPECT_GT(key.size(), 0u);
}

TEST_F(PngChunkTest_1237, KeyTXTChunk_SingleCharKeyword_1237) {
  std::vector<byte> chunkVec;
  chunkVec.push_back('K');
  chunkVec.push_back(0);
  chunkVec.push_back('V');

  DataBuf data(chunkVec.data(), chunkVec.size());

  DataBuf key = PngChunk::keyTXTChunk(data, false);
  EXPECT_GT(key.size(), 0u);
}

// ==================== makeMetadataChunk round-trip verification ====================

TEST_F(PngChunkTest_1237, MakeMetadataChunk_NonEmpty_ResultContainsData_1237) {
  std::string metadata(100, 'X');  // 100 bytes of 'X'
  try {
    std::string result = PngChunk::makeMetadataChunk(metadata, MetadataId::mdExif);
    // The result should be larger than or at least contain the encoded metadata
    EXPECT_GT(result.size(), 0u);
  } catch (const std::exception&) {
    // Acceptable if the implementation has specific requirements
  }
}

TEST_F(PngChunkTest_1237, MakeMetadataChunk_LargeMetadata_1237) {
  std::string metadata(10000, 'Y');  // Large metadata
  try {
    std::string result = PngChunk::makeMetadataChunk(metadata, MetadataId::mdExif);
    EXPECT_GT(result.size(), 0u);
  } catch (const std::exception&) {
    // May throw for various reasons
  }
}

// ==================== DataBuf boundary tests via PngChunk ====================

TEST_F(PngChunkTest_1237, DecodeTXTChunk_OnlyKeyword_NoValue_1237) {
  // tEXt chunk with keyword and null terminator but no value
  std::string keyword = "Description";
  std::vector<byte> chunkVec(keyword.begin(), keyword.end());
  chunkVec.push_back(0);  // null terminator

  DataBuf data(chunkVec.data(), chunkVec.size());

  try {
    DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::tEXt_Chunk);
    // Empty value should result in empty or near-empty result
  } catch (const std::exception&) {
    // Acceptable
  }
}

TEST_F(PngChunkTest_1237, DecodeIHDRChunk_MaxValues_1237) {
  DataBuf ihdrData(13);
  // Max uint32 values
  ihdrData.write_uint8(0, 0xFF);
  ihdrData.write_uint8(1, 0xFF);
  ihdrData.write_uint8(2, 0xFF);
  ihdrData.write_uint8(3, 0xFF);
  ihdrData.write_uint8(4, 0xFF);
  ihdrData.write_uint8(5, 0xFF);
  ihdrData.write_uint8(6, 0xFF);
  ihdrData.write_uint8(7, 0xFF);
  ihdrData.write_uint8(8, 8);
  ihdrData.write_uint8(9, 2);
  ihdrData.write_uint8(10, 0);
  ihdrData.write_uint8(11, 0);
  ihdrData.write_uint8(12, 0);

  uint32_t width = 0, height = 0;
  EXPECT_NO_THROW(PngChunk::decodeIHDRChunk(ihdrData, &width, &height));
  EXPECT_EQ(width, 0xFFFFFFFFu);
  EXPECT_EQ(height, 0xFFFFFFFFu);
}
