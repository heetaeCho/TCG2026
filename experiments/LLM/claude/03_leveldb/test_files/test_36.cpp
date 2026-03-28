#include "gtest/gtest.h"
#include "port/port.h"

#include <string>
#include <cstring>

namespace leveldb {
namespace port {

// Test normal compression of a simple string
TEST(SnappyCompressTest_36, CompressSimpleString_36) {
  const std::string input = "Hello, World!";
  std::string output;
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression of an empty input
TEST(SnappyCompressTest_36, CompressEmptyInput_36) {
  const std::string input = "";
  std::string output;
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  // Even empty input should produce some compressed output (snappy header)
  // output may or may not be empty depending on snappy format
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression of a single byte
TEST(SnappyCompressTest_36, CompressSingleByte_36) {
  const char input = 'A';
  std::string output;
  bool result = Snappy_Compress(&input, 1, &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression of a large input
TEST(SnappyCompressTest_36, CompressLargeInput_36) {
  std::string input(1000000, 'X');  // 1MB of repeated character
  std::string output;
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
  // Highly repetitive data should compress well
  EXPECT_LT(output.size(), input.size());
#else
  EXPECT_FALSE(result);
#endif
}

// Test that compressed output is different from input (for non-trivial input)
TEST(SnappyCompressTest_36, CompressedOutputDiffersFromInput_36) {
  const std::string input = "This is a test string that should be compressed by Snappy.";
  std::string output;
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  EXPECT_NE(input, output);
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression of binary data (including null bytes)
TEST(SnappyCompressTest_36, CompressBinaryData_36) {
  std::string input(256, '\0');
  for (int i = 0; i < 256; ++i) {
    input[i] = static_cast<char>(i);
  }
  std::string output;
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
#else
  EXPECT_FALSE(result);
#endif
}

// Test that output string is properly resized (not containing extra data)
TEST(SnappyCompressTest_36, OutputProperlyResized_36) {
  const std::string input = "Some data to compress";
  std::string output = "pre-existing content that should be overwritten";
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  // The output should have been resized; it should not contain old content
  // We can verify by checking output size is reasonable
  EXPECT_GT(output.size(), 0u);
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with highly compressible data
TEST(SnappyCompressTest_36, HighlyCompressibleData_36) {
  std::string input(10000, 'a');
  std::string output;
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  // Highly repetitive data should compress significantly
  EXPECT_LT(output.size(), input.size() / 2);
#else
  EXPECT_FALSE(result);
#endif
}

// Test compression with incompressible (random-like) data
TEST(SnappyCompressTest_36, IncompressibleData_36) {
  std::string input;
  input.reserve(1000);
  // Generate pseudo-random data
  unsigned int seed = 42;
  for (int i = 0; i < 1000; ++i) {
    seed = seed * 1103515245 + 12345;
    input.push_back(static_cast<char>((seed >> 16) & 0xFF));
  }
  std::string output;
  bool result = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result);
  EXPECT_FALSE(output.empty());
  // Random data may not compress well but should still succeed
#else
  EXPECT_FALSE(result);
#endif
}

// Test calling compress multiple times reuses output correctly
TEST(SnappyCompressTest_36, MultipleCompressions_36) {
  std::string output;

  const std::string input1 = "First string";
  bool result1 = Snappy_Compress(input1.data(), input1.size(), &output);

  std::string first_output = output;

  const std::string input2 = "Second different string with more content";
  bool result2 = Snappy_Compress(input2.data(), input2.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  // Different inputs should produce different compressed outputs
  EXPECT_NE(first_output, output);
#else
  EXPECT_FALSE(result1);
  EXPECT_FALSE(result2);
#endif
}

}  // namespace port
}  // namespace leveldb
