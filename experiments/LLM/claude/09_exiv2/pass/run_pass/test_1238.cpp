#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

// Include the implementation directly since it's provided inline
namespace Exiv2 {
namespace Internal {

class PngChunk {
 public:
  static DataBuf keyTXTChunk(const DataBuf& data, bool stripHeader) {
    const size_t offset = stripHeader ? 8ul : 0ul;
    if (data.size() <= offset)
      throw Error(ErrorCode::kerFailedToReadImageData);
    auto it = std::find(data.begin() + offset, data.end(), 0);
    if (it == data.end())
      throw Error(ErrorCode::kerFailedToReadImageData);
    return {data.c_data() + offset, std::distance(data.begin(), it) - offset};
  }
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::DataBuf;
using Exiv2::Internal::PngChunk;
using Exiv2::Error;
using Exiv2::ErrorCode;

class PngChunkKeyTXTChunkTest_1238 : public ::testing::Test {
 protected:
  PngChunk pngChunk;
};

// ========== Normal operation tests ==========

TEST_F(PngChunkKeyTXTChunkTest_1238, ExtractKeyWithoutStripHeader_1238) {
  // Data: "keyword\0value"
  const uint8_t raw[] = {'k', 'e', 'y', 'w', 'o', 'r', 'd', '\0', 'v', 'a', 'l', 'u', 'e'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), 7u);
  EXPECT_EQ(std::memcmp(result.c_data(), "keyword", 7), 0);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, ExtractKeyWithStripHeader_1238) {
  // 8 bytes header + "keyword\0value"
  const uint8_t raw[] = {'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H',
                          'k', 'e', 'y', 'w', 'o', 'r', 'd', '\0', 'v', 'a', 'l', 'u', 'e'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, true);
  
  ASSERT_EQ(result.size(), 7u);
  EXPECT_EQ(std::memcmp(result.c_data(), "keyword", 7), 0);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, SingleCharKeyNoStripHeader_1238) {
  // Data: "K\0rest"
  const uint8_t raw[] = {'K', '\0', 'r', 'e', 's', 't'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), 1u);
  EXPECT_EQ(result.c_data()[0], 'K');
}

TEST_F(PngChunkKeyTXTChunkTest_1238, SingleCharKeyWithStripHeader_1238) {
  // 8 bytes header + "K\0"
  const uint8_t raw[] = {'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'K', '\0'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, true);
  
  ASSERT_EQ(result.size(), 1u);
  EXPECT_EQ(result.c_data()[0], 'K');
}

TEST_F(PngChunkKeyTXTChunkTest_1238, NullByteAtStartNoStripHeader_1238) {
  // Data starts with null: "\0rest"
  const uint8_t raw[] = {'\0', 'r', 'e', 's', 't'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  EXPECT_EQ(result.size(), 0u);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, NullByteRightAfterHeaderWithStripHeader_1238) {
  // 8 bytes header followed by null byte
  const uint8_t raw[] = {'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', '\0'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, true);
  
  EXPECT_EQ(result.size(), 0u);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, LongerKeyExtraction_1238) {
  // "thisisalongkeyword\0somevalue"
  const char* str = "thisisalongkeyword";
  std::vector<uint8_t> raw;
  for (size_t i = 0; str[i]; ++i)
    raw.push_back(static_cast<uint8_t>(str[i]));
  raw.push_back(0);  // null terminator
  raw.push_back('v');
  raw.push_back('a');
  raw.push_back('l');
  
  DataBuf data(raw.data(), raw.size());
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), strlen(str));
  EXPECT_EQ(std::memcmp(result.c_data(), str, strlen(str)), 0);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, MultipleNullBytesReturnsFirstKey_1238) {
  // "abc\0def\0ghi"
  const uint8_t raw[] = {'a', 'b', 'c', '\0', 'd', 'e', 'f', '\0', 'g', 'h', 'i'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(std::memcmp(result.c_data(), "abc", 3), 0);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, StripHeaderFalseIgnoresFirst8Bytes_1238) {
  // When stripHeader is false, offset is 0, so entire data is searched from beginning
  const uint8_t raw[] = {'\0', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'k', 'e', 'y'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  // Key should be empty since first byte is null
  EXPECT_EQ(result.size(), 0u);
}

// ========== Boundary condition tests ==========

TEST_F(PngChunkKeyTXTChunkTest_1238, ExactlyOneByteNullNoStripHeader_1238) {
  // Single null byte
  const uint8_t raw[] = {'\0'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  EXPECT_EQ(result.size(), 0u);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, NineBytesWith9thNullStripHeader_1238) {
  // 8 header bytes + 1 null byte = 9 bytes
  const uint8_t raw[] = {'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', '\0'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, true);
  
  EXPECT_EQ(result.size(), 0u);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, KeyWithNullTerminatorOnlyNoStripHeader_1238) {
  // "key\0"
  const uint8_t raw[] = {'k', 'e', 'y', '\0'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(std::memcmp(result.c_data(), "key", 3), 0);
}

// ========== Error/exception tests ==========

TEST_F(PngChunkKeyTXTChunkTest_1238, EmptyDataNoStripHeaderThrows_1238) {
  DataBuf data;
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, false), Error);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, EmptyDataStripHeaderThrows_1238) {
  DataBuf data;
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, true), Error);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, DataSizeExactly8StripHeaderThrows_1238) {
  // With stripHeader=true, offset=8, data.size()<=8 throws
  const uint8_t raw[] = {'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H'};
  DataBuf data(raw, sizeof(raw));
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, true), Error);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, DataSizeLessThan8StripHeaderThrows_1238) {
  const uint8_t raw[] = {'H', 'H', 'H'};
  DataBuf data(raw, sizeof(raw));
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, true), Error);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, NoNullByteNoStripHeaderThrows_1238) {
  // Data with no null terminator
  const uint8_t raw[] = {'a', 'b', 'c', 'd'};
  DataBuf data(raw, sizeof(raw));
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, false), Error);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, NoNullByteStripHeaderThrows_1238) {
  // 8 header bytes + data with no null
  const uint8_t raw[] = {'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'a', 'b', 'c'};
  DataBuf data(raw, sizeof(raw));
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, true), Error);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, NullOnlyInHeaderPartStripHeaderThrows_1238) {
  // Header contains null bytes but after offset=8 there is no null
  const uint8_t raw[] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 'a', 'b', 'c'};
  DataBuf data(raw, sizeof(raw));
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, true), Error);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, SingleNonNullByteNoStripHeaderThrows_1238) {
  // Single byte, no null
  const uint8_t raw[] = {'a'};
  DataBuf data(raw, sizeof(raw));
  
  EXPECT_THROW(PngChunk::keyTXTChunk(data, false), Error);
}

// ========== Additional edge case tests ==========

TEST_F(PngChunkKeyTXTChunkTest_1238, BinaryDataInKeyNoStripHeader_1238) {
  // Binary data before null
  const uint8_t raw[] = {0xFF, 0xFE, 0x01, 0x02, '\0', 'v'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), 4u);
  EXPECT_EQ(result.c_data()[0], 0xFF);
  EXPECT_EQ(result.c_data()[1], 0xFE);
  EXPECT_EQ(result.c_data()[2], 0x01);
  EXPECT_EQ(result.c_data()[3], 0x02);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, TwoNullBytesConsecutiveNoStripHeader_1238) {
  // "ab\0\0cd"
  const uint8_t raw[] = {'a', 'b', '\0', '\0', 'c', 'd'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), 2u);
  EXPECT_EQ(std::memcmp(result.c_data(), "ab", 2), 0);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, StripHeaderFalseWith8PlusCharsAndNull_1238) {
  // When stripHeader=false, even with more than 8 chars, offset is 0
  const uint8_t raw[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '\0'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, false);
  
  ASSERT_EQ(result.size(), 9u);
  EXPECT_EQ(std::memcmp(result.c_data(), "abcdefghi", 9), 0);
}

TEST_F(PngChunkKeyTXTChunkTest_1238, HeaderContainsNullButStripHeaderTrue_1238) {
  // Header has nulls, but after skipping 8 bytes, there's a key and null
  const uint8_t raw[] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 'k', 'e', 'y', '\0'};
  DataBuf data(raw, sizeof(raw));
  
  DataBuf result = PngChunk::keyTXTChunk(data, true);
  
  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(std::memcmp(result.c_data(), "key", 3), 0);
}
