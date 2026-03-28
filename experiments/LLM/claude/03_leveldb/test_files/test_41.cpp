#include "port/port_stdcxx.h"

#include <cstring>
#include <string>
#include <vector>

#include "gtest/gtest.h"

// Conditionally include zstd if available
#if HAVE_ZSTD
#include <zstd.h>
#endif

namespace leveldb {
namespace port {

class ZstdUncompressTest_41 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

#if HAVE_ZSTD

// Helper to compress data with zstd for testing decompression
static std::string ZstdCompressHelper(const std::string& input) {
  size_t max_compressed = ZSTD_compressBound(input.size());
  std::string compressed(max_compressed, '\0');
  size_t compressed_size = ZSTD_compress(
      &compressed[0], max_compressed, input.data(), input.size(), 1);
  if (ZSTD_isError(compressed_size)) {
    return "";
  }
  compressed.resize(compressed_size);
  return compressed;
}

// Test: Normal decompression of a simple string
TEST_F(ZstdUncompressTest_41, NormalDecompression_41) {
  std::string original = "Hello, World! This is a test of zstd compression.";
  std::string compressed = ZstdCompressHelper(original);
  ASSERT_FALSE(compressed.empty());

  // Get uncompressed length first
  size_t uncompressed_len = 0;
  bool got_len =
      Zstd_GetUncompressedLength(compressed.data(), compressed.size(),
                                 &uncompressed_len);
  ASSERT_TRUE(got_len);
  ASSERT_EQ(uncompressed_len, original.size());

  std::vector<char> output(uncompressed_len);
  bool result =
      Zstd_Uncompress(compressed.data(), compressed.size(), output.data());
  EXPECT_TRUE(result);
  EXPECT_EQ(std::string(output.data(), uncompressed_len), original);
}

// Test: Decompression of empty string
TEST_F(ZstdUncompressTest_41, EmptyInput_41) {
  std::string original = "";
  std::string compressed = ZstdCompressHelper(original);
  ASSERT_FALSE(compressed.empty());

  size_t uncompressed_len = 0;
  bool got_len =
      Zstd_GetUncompressedLength(compressed.data(), compressed.size(),
                                 &uncompressed_len);
  ASSERT_TRUE(got_len);
  ASSERT_EQ(uncompressed_len, 0u);

  char dummy;
  bool result =
      Zstd_Uncompress(compressed.data(), compressed.size(), &dummy);
  EXPECT_TRUE(result);
}

// Test: Corrupt/invalid compressed data should fail
TEST_F(ZstdUncompressTest_41, CorruptData_41) {
  std::string garbage = "this is not valid zstd data at all!!!";
  char output[1024];
  bool result = Zstd_Uncompress(garbage.data(), garbage.size(), output);
  EXPECT_FALSE(result);
}

// Test: Truncated compressed data should fail
TEST_F(ZstdUncompressTest_41, TruncatedCompressedData_41) {
  std::string original = "Some data to compress for truncation test.";
  std::string compressed = ZstdCompressHelper(original);
  ASSERT_FALSE(compressed.empty());
  ASSERT_GT(compressed.size(), 4u);

  // Truncate the compressed data
  std::string truncated = compressed.substr(0, compressed.size() / 2);
  char output[1024];
  bool result = Zstd_Uncompress(truncated.data(), truncated.size(), output);
  EXPECT_FALSE(result);
}

// Test: Very small compressed input (just a few bytes)
TEST_F(ZstdUncompressTest_41, VerySmallInput_41) {
  std::string tiny = "A";
  // Not valid zstd data
  char output[64];
  bool result = Zstd_Uncompress(tiny.data(), tiny.size(), output);
  EXPECT_FALSE(result);
}

// Test: Zero-length input
TEST_F(ZstdUncompressTest_41, ZeroLengthInput_41) {
  char output[64];
  bool result = Zstd_Uncompress("", 0, output);
  EXPECT_FALSE(result);
}

// Test: Large data decompression
TEST_F(ZstdUncompressTest_41, LargeDataDecompression_41) {
  std::string original(100000, 'X');
  // Add some variation
  for (size_t i = 0; i < original.size(); i++) {
    original[i] = static_cast<char>('A' + (i % 26));
  }
  std::string compressed = ZstdCompressHelper(original);
  ASSERT_FALSE(compressed.empty());

  size_t uncompressed_len = 0;
  bool got_len =
      Zstd_GetUncompressedLength(compressed.data(), compressed.size(),
                                 &uncompressed_len);
  ASSERT_TRUE(got_len);
  ASSERT_EQ(uncompressed_len, original.size());

  std::vector<char> output(uncompressed_len);
  bool result =
      Zstd_Uncompress(compressed.data(), compressed.size(), output.data());
  EXPECT_TRUE(result);
  EXPECT_EQ(std::string(output.data(), uncompressed_len), original);
}

// Test: Compressed data with single byte modified (bit flip)
TEST_F(ZstdUncompressTest_41, BitFlipInCompressedData_41) {
  std::string original = "Test data for bit flip corruption scenario.";
  std::string compressed = ZstdCompressHelper(original);
  ASSERT_FALSE(compressed.empty());
  ASSERT_GT(compressed.size(), 10u);

  // Flip a bit in the middle of the compressed data
  compressed[compressed.size() / 2] ^= 0x01;

  // This should either fail or produce wrong output; we mainly check it doesn't crash
  size_t uncompressed_len = 0;
  bool got_len =
      Zstd_GetUncompressedLength(compressed.data(), compressed.size(),
                                 &uncompressed_len);
  if (got_len && uncompressed_len > 0) {
    std::vector<char> output(uncompressed_len + 64);  // extra buffer just in case
    bool result =
        Zstd_Uncompress(compressed.data(), compressed.size(), output.data());
    // Result may be true or false depending on where the bit was flipped
    // The key thing is it shouldn't crash
    (void)result;
  }
}

// Test: Binary data with null bytes
TEST_F(ZstdUncompressTest_41, BinaryDataWithNulls_41) {
  std::string original;
  original.resize(256);
  for (int i = 0; i < 256; i++) {
    original[i] = static_cast<char>(i);
  }
  std::string compressed = ZstdCompressHelper(original);
  ASSERT_FALSE(compressed.empty());

  size_t uncompressed_len = 0;
  bool got_len =
      Zstd_GetUncompressedLength(compressed.data(), compressed.size(),
                                 &uncompressed_len);
  ASSERT_TRUE(got_len);
  ASSERT_EQ(uncompressed_len, original.size());

  std::vector<char> output(uncompressed_len);
  bool result =
      Zstd_Uncompress(compressed.data(), compressed.size(), output.data());
  EXPECT_TRUE(result);
  EXPECT_EQ(std::string(output.data(), uncompressed_len), original);
}

#else  // !HAVE_ZSTD

// Test: When ZSTD is not available, Zstd_Uncompress should always return false
TEST_F(ZstdUncompressTest_41, ReturnsFailWhenZstdNotAvailable_41) {
  char output[64];
  bool result = Zstd_Uncompress("anything", 8, output);
  EXPECT_FALSE(result);
}

TEST_F(ZstdUncompressTest_41, ReturnsFailForEmptyInputNoZstd_41) {
  char output[64];
  bool result = Zstd_Uncompress("", 0, output);
  EXPECT_FALSE(result);
}

TEST_F(ZstdUncompressTest_41, ReturnsFailForNullptrInputNoZstd_41) {
  char output[64];
  bool result = Zstd_Uncompress(nullptr, 0, output);
  EXPECT_FALSE(result);
}

#endif  // HAVE_ZSTD

}  // namespace port
}  // namespace leveldb
