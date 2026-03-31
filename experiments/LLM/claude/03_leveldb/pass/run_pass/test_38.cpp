#include "gtest/gtest.h"
#include "port/port_stdcxx.h"

#include <cstring>
#include <string>
#include <vector>

#if HAVE_SNAPPY
#include "snappy.h"
#endif

namespace leveldb {
namespace port {

// Test that Snappy_Uncompress handles null/empty input gracefully
TEST(SnappyUncompressTest_38, EmptyInputReturnsExpected_38) {
  char output[64] = {0};
#if HAVE_SNAPPY
  // Empty input is not valid snappy compressed data, should fail or behave gracefully
  bool result = Snappy_Uncompress("", 0, output);
  // We don't assert specific result since empty input behavior depends on snappy,
  // but we verify it doesn't crash.
  (void)result;
#else
  bool result = Snappy_Uncompress("", 0, output);
  EXPECT_FALSE(result);
#endif
}

// Test that Snappy_Uncompress returns false when snappy is not available
// or correctly decompresses when snappy is available
TEST(SnappyUncompressTest_38, NormalOperation_38) {
#if HAVE_SNAPPY
  // Compress some known data, then decompress it
  std::string original = "Hello, World! This is a test string for snappy compression.";
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  size_t uncompressed_length = 0;
  ASSERT_TRUE(snappy::GetUncompressedLength(compressed.data(), compressed.size(), &uncompressed_length));
  ASSERT_EQ(uncompressed_length, original.size());

  std::vector<char> output(uncompressed_length);
  bool result = Snappy_Uncompress(compressed.data(), compressed.size(), output.data());
  EXPECT_TRUE(result);

  std::string decompressed(output.data(), uncompressed_length);
  EXPECT_EQ(decompressed, original);
#else
  char output[64] = {0};
  bool result = Snappy_Uncompress("some data", 9, output);
  EXPECT_FALSE(result);
#endif
}

// Test with garbage/invalid compressed data
TEST(SnappyUncompressTest_38, InvalidCompressedData_38) {
  const char garbage[] = "This is not valid snappy data!!!!";
  char output[256] = {0};
#if HAVE_SNAPPY
  // Invalid compressed data should return false
  bool result = Snappy_Uncompress(garbage, sizeof(garbage) - 1, output);
  EXPECT_FALSE(result);
#else
  bool result = Snappy_Uncompress(garbage, sizeof(garbage) - 1, output);
  EXPECT_FALSE(result);
#endif
}

// Test that when snappy is not available, the function always returns false
// regardless of input
TEST(SnappyUncompressTest_38, NoSnappyAlwaysFalse_38) {
#if !HAVE_SNAPPY
  // With various inputs, should always return false
  char output[128] = {0};
  
  EXPECT_FALSE(Snappy_Uncompress(nullptr, 0, nullptr));
  EXPECT_FALSE(Snappy_Uncompress("abc", 3, output));
  EXPECT_FALSE(Snappy_Uncompress("", 0, output));
  
  const char data[] = {0x00, 0x01, 0x02, 0x03};
  EXPECT_FALSE(Snappy_Uncompress(data, sizeof(data), output));
#endif
}

// Test with a larger payload
TEST(SnappyUncompressTest_38, LargerPayload_38) {
#if HAVE_SNAPPY
  // Create a large string with repetitive content (compresses well with snappy)
  std::string original(10000, 'A');
  for (size_t i = 0; i < original.size(); i++) {
    original[i] = 'A' + (i % 26);
  }

  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  size_t uncompressed_length = 0;
  ASSERT_TRUE(snappy::GetUncompressedLength(compressed.data(), compressed.size(), &uncompressed_length));
  ASSERT_EQ(uncompressed_length, original.size());

  std::vector<char> output(uncompressed_length);
  bool result = Snappy_Uncompress(compressed.data(), compressed.size(), output.data());
  EXPECT_TRUE(result);

  std::string decompressed(output.data(), uncompressed_length);
  EXPECT_EQ(decompressed, original);
#else
  char output[64] = {0};
  std::string data(10000, 'X');
  bool result = Snappy_Uncompress(data.data(), data.size(), output);
  EXPECT_FALSE(result);
#endif
}

// Test with single byte input
TEST(SnappyUncompressTest_38, SingleByteInput_38) {
  char output[64] = {0};
  const char single_byte = 'A';
#if HAVE_SNAPPY
  // Single byte is not valid snappy data
  bool result = Snappy_Uncompress(&single_byte, 1, output);
  // Likely false since a single byte isn't valid compressed snappy data
  (void)result; // Just ensure it doesn't crash
#else
  bool result = Snappy_Uncompress(&single_byte, 1, output);
  EXPECT_FALSE(result);
#endif
}

// Test with truncated compressed data
TEST(SnappyUncompressTest_38, TruncatedCompressedData_38) {
#if HAVE_SNAPPY
  std::string original = "Test data for truncation test";
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  // Truncate the compressed data
  ASSERT_GT(compressed.size(), 2u);
  std::string truncated = compressed.substr(0, compressed.size() / 2);

  // Allocate a buffer large enough based on original size
  std::vector<char> output(original.size() + 100, 0);
  bool result = Snappy_Uncompress(truncated.data(), truncated.size(), output.data());
  // Truncated data should fail decompression
  EXPECT_FALSE(result);
#else
  char output[64] = {0};
  bool result = Snappy_Uncompress("trunc", 5, output);
  EXPECT_FALSE(result);
#endif
}

// Test round-trip with binary data containing null bytes
TEST(SnappyUncompressTest_38, BinaryDataWithNulls_38) {
#if HAVE_SNAPPY
  std::string original;
  original.resize(256);
  for (int i = 0; i < 256; i++) {
    original[i] = static_cast<char>(i);
  }

  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  size_t uncompressed_length = 0;
  ASSERT_TRUE(snappy::GetUncompressedLength(compressed.data(), compressed.size(), &uncompressed_length));
  ASSERT_EQ(uncompressed_length, original.size());

  std::vector<char> output(uncompressed_length);
  bool result = Snappy_Uncompress(compressed.data(), compressed.size(), output.data());
  EXPECT_TRUE(result);

  std::string decompressed(output.data(), uncompressed_length);
  EXPECT_EQ(decompressed, original);
#else
  char output[256] = {0};
  char input[256];
  for (int i = 0; i < 256; i++) input[i] = static_cast<char>(i);
  bool result = Snappy_Uncompress(input, 256, output);
  EXPECT_FALSE(result);
#endif
}

}  // namespace port
}  // namespace leveldb
