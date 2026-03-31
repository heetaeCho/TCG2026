#include "port/port_stdcxx.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace leveldb {
namespace port {

// Test normal compression of a simple string
TEST(ZstdCompressTest_39, CompressSimpleString_39) {
  std::string input = "Hello, World! This is a test string for compression.";
  std::string output;
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
  // Compressed output should be produced (may or may not be smaller for short strings)
  EXPECT_GT(output.size(), 0u);
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with empty input
TEST(ZstdCompressTest_39, CompressEmptyInput_39) {
  std::string input = "";
  std::string output;
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  // Empty input should still succeed in zstd (produces a frame with no content)
  EXPECT_TRUE(result);
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with a single byte
TEST(ZstdCompressTest_39, CompressSingleByte_39) {
  std::string input = "A";
  std::string output;
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with different compression levels
TEST(ZstdCompressTest_39, CompressWithDifferentLevels_39) {
  std::string input(1000, 'A');  // Highly compressible data
  std::string output_low, output_high;

  bool result_low = Zstd_Compress(1, input.data(), input.size(), &output_low);
  bool result_high = Zstd_Compress(19, input.data(), input.size(), &output_high);

#if HAVE_ZSTD
  EXPECT_TRUE(result_low);
  EXPECT_TRUE(result_high);
  EXPECT_FALSE(output_low.empty());
  EXPECT_FALSE(output_high.empty());
  // Higher compression level should produce same or smaller output for compressible data
  EXPECT_LE(output_high.size(), output_low.size());
#else
  EXPECT_FALSE(result_low);
  EXPECT_FALSE(result_high);
#endif
}

// Test compression of large data
TEST(ZstdCompressTest_39, CompressLargeData_39) {
  std::string input(100000, 'B');
  std::string output;
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
  // Highly repetitive data should compress significantly
  EXPECT_LT(output.size(), input.size());
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression of random-like (incompressible) data
TEST(ZstdCompressTest_39, CompressIncompressibleData_39) {
  std::vector<char> data(10000);
  // Fill with pseudo-random data
  for (size_t i = 0; i < data.size(); ++i) {
    data[i] = static_cast<char>((i * 73 + 97) % 256);
  }
  std::string output;
  bool result = Zstd_Compress(1, data.data(), data.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test that compression produces valid output that differs from input
TEST(ZstdCompressTest_39, CompressedOutputDiffersFromInput_39) {
  std::string input = "This is some test data that should be compressed properly.";
  std::string output;
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  // The compressed output should not be identical to the input
  // (zstd adds frame headers at minimum)
  EXPECT_NE(output, input);
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with binary data including null bytes
TEST(ZstdCompressTest_39, CompressBinaryDataWithNulls_39) {
  std::string input(100, '\0');
  input[50] = 'X';
  input[99] = 'Y';
  std::string output;
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test that output string is properly resized (not left at compress bound size)
TEST(ZstdCompressTest_39, OutputIsResizedToActualCompressedSize_39) {
  std::string input(10000, 'Z');  // Very compressible
  std::string output;
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  // The output should be much smaller than the ZSTD_compressBound for compressible data
  EXPECT_LT(output.size(), input.size());
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with level 0 (default level in zstd)
TEST(ZstdCompressTest_39, CompressWithDefaultLevel_39) {
  std::string input = "Test data for default compression level";
  std::string output;
  bool result = Zstd_Compress(0, input.data(), input.size(), &output);

#if HAVE_ZSTD
  // Level 0 maps to default level in zstd, should succeed
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with minimum level (negative levels are valid in zstd for fast compression)
TEST(ZstdCompressTest_39, CompressWithNegativeLevel_39) {
  std::string input(500, 'Q');
  std::string output;
  bool result = Zstd_Compress(-1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  // Negative levels should work in zstd (fast compression modes)
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test that compressing the same input twice produces the same output
TEST(ZstdCompressTest_39, DeterministicCompression_39) {
  std::string input = "Deterministic compression test input data";
  std::string output1, output2;

  bool result1 = Zstd_Compress(3, input.data(), input.size(), &output1);
  bool result2 = Zstd_Compress(3, input.data(), input.size(), &output2);

#if HAVE_ZSTD
  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_EQ(output1, output2);
#else
  EXPECT_FALSE(result1);
  EXPECT_FALSE(result2);
#endif
}

// Test that output parameter is overwritten (pre-existing content)
TEST(ZstdCompressTest_39, OutputOverwritesExistingContent_39) {
  std::string input = "Some data to compress";
  std::string output = "pre-existing content that should be overwritten";
  bool result = Zstd_Compress(1, input.data(), input.size(), &output);

#if HAVE_ZSTD
  EXPECT_TRUE(result);
  EXPECT_NE(output, "pre-existing content that should be overwritten");
#else
  EXPECT_FALSE(result);
#endif
}

}  // namespace port
}  // namespace leveldb
