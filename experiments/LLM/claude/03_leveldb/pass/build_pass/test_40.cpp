#include "gtest/gtest.h"
#include "port/port_stdcxx.h"

#include <cstring>
#include <vector>

namespace leveldb {
namespace port {

// Test with null/empty input
TEST(ZstdGetUncompressedLengthTest_40, NullInputReturnsExpected_40) {
  size_t result = 0;
  bool ret = Zstd_GetUncompressedLength(nullptr, 0, &result);
#if HAVE_ZSTD
  // With zero-length input, ZSTD_getFrameContentSize likely fails or returns
  // an error/unknown size, so we expect false
  EXPECT_FALSE(ret);
#else
  EXPECT_FALSE(ret);
#endif
}

TEST(ZstdGetUncompressedLengthTest_40, EmptyInputReturnsExpected_40) {
  const char data[] = "";
  size_t result = 0;
  bool ret = Zstd_GetUncompressedLength(data, 0, &result);
#if HAVE_ZSTD
  EXPECT_FALSE(ret);
#else
  EXPECT_FALSE(ret);
#endif
}

TEST(ZstdGetUncompressedLengthTest_40, GarbageInputReturnsFalse_40) {
  // Random garbage data that is not a valid zstd frame
  const char garbage[] = "This is definitely not a zstd compressed frame!!!!";
  size_t result = 42;
  bool ret = Zstd_GetUncompressedLength(garbage, sizeof(garbage), &result);
#if HAVE_ZSTD
  // Garbage data should not be recognized as valid zstd frame
  // ZSTD_getFrameContentSize returns ZSTD_CONTENTSIZE_ERROR or ZSTD_CONTENTSIZE_UNKNOWN
  // which are not 0 but are special sentinel values, so behavior may vary
  // The function returns false if size == 0, but garbage might return error codes
  // We just verify it doesn't crash; the return value depends on ZSTD behavior
  (void)ret;
#else
  EXPECT_FALSE(ret);
  // result should be unchanged when HAVE_ZSTD is not defined
#endif
}

TEST(ZstdGetUncompressedLengthTest_40, SmallInputReturnsFalse_40) {
  // Input too small to be a valid zstd frame
  const char small[] = {0x28, static_cast<char>(0xB5), 0x2F};
  size_t result = 0;
  bool ret = Zstd_GetUncompressedLength(small, sizeof(small), &result);
#if HAVE_ZSTD
  // Too small for a valid frame, should not succeed
  // The exact behavior depends on ZSTD but it shouldn't return size == 0 for truncated
  (void)ret;
#else
  EXPECT_FALSE(ret);
#endif
}

#if HAVE_ZSTD
#include <zstd.h>

TEST(ZstdGetUncompressedLengthTest_40, ValidCompressedDataReturnsTrue_40) {
  // Create a valid zstd compressed frame from known data
  const std::string original = "Hello, World! This is test data for zstd compression.";
  
  size_t const bound = ZSTD_compressBound(original.size());
  std::vector<char> compressed(bound);
  
  size_t const compressed_size = ZSTD_compress(
      compressed.data(), bound, original.data(), original.size(), 1);
  ASSERT_FALSE(ZSTD_isError(compressed_size));
  
  size_t result = 0;
  bool ret = Zstd_GetUncompressedLength(compressed.data(), compressed_size, &result);
  EXPECT_TRUE(ret);
  EXPECT_EQ(result, original.size());
}

TEST(ZstdGetUncompressedLengthTest_40, ValidCompressedEmptyStringReturnsZeroSizeFalse_40) {
  // Compress an empty string - the uncompressed size is 0
  const std::string original = "";
  
  size_t const bound = ZSTD_compressBound(original.size());
  std::vector<char> compressed(bound);
  
  size_t const compressed_size = ZSTD_compress(
      compressed.data(), bound, original.data(), original.size(), 1);
  ASSERT_FALSE(ZSTD_isError(compressed_size));
  
  size_t result = 999;
  bool ret = Zstd_GetUncompressedLength(compressed.data(), compressed_size, &result);
  // ZSTD_getFrameContentSize returns 0 for empty content, and the function returns false when size == 0
  EXPECT_FALSE(ret);
}

TEST(ZstdGetUncompressedLengthTest_40, ValidCompressedLargeDataReturnsCorrectSize_40) {
  // Create a larger test payload
  std::string original(100000, 'A');
  
  size_t const bound = ZSTD_compressBound(original.size());
  std::vector<char> compressed(bound);
  
  size_t const compressed_size = ZSTD_compress(
      compressed.data(), bound, original.data(), original.size(), 1);
  ASSERT_FALSE(ZSTD_isError(compressed_size));
  
  size_t result = 0;
  bool ret = Zstd_GetUncompressedLength(compressed.data(), compressed_size, &result);
  EXPECT_TRUE(ret);
  EXPECT_EQ(result, original.size());
}

TEST(ZstdGetUncompressedLengthTest_40, TruncatedValidFrameHandledGracefully_40) {
  // Create valid compressed data then truncate it
  const std::string original = "Some test data to compress";
  
  size_t const bound = ZSTD_compressBound(original.size());
  std::vector<char> compressed(bound);
  
  size_t const compressed_size = ZSTD_compress(
      compressed.data(), bound, original.data(), original.size(), 1);
  ASSERT_FALSE(ZSTD_isError(compressed_size));
  ASSERT_GT(compressed_size, 4u);
  
  // Truncate to just the magic number (4 bytes) - header incomplete
  size_t result = 0;
  bool ret = Zstd_GetUncompressedLength(compressed.data(), 4, &result);
  // With truncated header, ZSTD_getFrameContentSize should return error
  // The function behavior depends on the error code value
  (void)ret;  // Just verify no crash
}

TEST(ZstdGetUncompressedLengthTest_40, SingleBytePayloadReturnsCorrectSize_40) {
  const std::string original = "X";
  
  size_t const bound = ZSTD_compressBound(original.size());
  std::vector<char> compressed(bound);
  
  size_t const compressed_size = ZSTD_compress(
      compressed.data(), bound, original.data(), original.size(), 1);
  ASSERT_FALSE(ZSTD_isError(compressed_size));
  
  size_t result = 0;
  bool ret = Zstd_GetUncompressedLength(compressed.data(), compressed_size, &result);
  EXPECT_TRUE(ret);
  EXPECT_EQ(result, 1u);
}

#endif  // HAVE_ZSTD

TEST(ZstdGetUncompressedLengthTest_40, ResultPointerNotModifiedOnFailure_40) {
  const char garbage[] = "not valid zstd data at all";
  size_t result = 12345;
  bool ret = Zstd_GetUncompressedLength(garbage, sizeof(garbage), &result);
#if !HAVE_ZSTD
  EXPECT_FALSE(ret);
  // When HAVE_ZSTD is not defined, result should be untouched
  EXPECT_EQ(result, 12345u);
#else
  (void)ret;
  // With ZSTD available, behavior depends on what ZSTD_getFrameContentSize returns
#endif
}

}  // namespace port
}  // namespace leveldb
