// File: zstd_compress_test_39.cc
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Ensure the production header is included as-is.
#include "port/port_stdcxx.h"

#if HAVE_ZSTD
// Only include zstd headers when available to validate round-trip behavior.
#include <zstd.h>
#endif

using leveldb::port::Zstd_Compress;

class PortZstdCompressTest_39 : public ::testing::Test {};

#if !HAVE_ZSTD
// ------------------------------
// Tests for environments WITHOUT Zstd
// ------------------------------

TEST_F(PortZstdCompressTest_39, ReturnsFalseWhenZstdUnavailable_39) {
  const std::string input = "any data";
  std::string out = "preexisting";
  const std::string before = out;

  const bool ok = Zstd_Compress(/*level=*/3, input.data(), input.size(), &out);

  EXPECT_FALSE(ok);
  // Since the function returns immediately in the !HAVE_ZSTD branch, verify it
  // does not modify the output buffer (observable effect).
  EXPECT_EQ(out, before);
}

#else  // HAVE_ZSTD

// ------------------------------
// Tests for environments WITH Zstd
// ------------------------------

static void DecompressAndExpectEqual(const std::string& compressed,
                                     const std::string& original) {
  // Allocate a buffer with the expected original size and decompress into it.
  std::vector<char> buf(original.size());
  const size_t decompressed_size =
      ZSTD_decompress(buf.data(), buf.size(), compressed.data(), compressed.size());
  ASSERT_FALSE(ZSTD_isError(decompressed_size)) << ZSTD_getErrorName(decompressed_size);
  ASSERT_EQ(decompressed_size, original.size());
  EXPECT_EQ(std::string(buf.data(), buf.data() + decompressed_size), original);
}

TEST_F(PortZstdCompressTest_39, CompressesNonEmptyInput_Success_39) {
  // Use a compressible payload.
  std::string input;
  for (int i = 0; i < 1000; ++i) input += "The quick brown fox jumps over the lazy dog.\n";

  std::string out;
  const bool ok = Zstd_Compress(/*level=*/3, input.data(), input.size(), &out);

  ASSERT_TRUE(ok);
  ASSERT_FALSE(out.empty());  // Observable: returns some compressed bytes.
  DecompressAndExpectEqual(out, input);
}

TEST_F(PortZstdCompressTest_39, CompressesEmptyInput_Success_39) {
  const std::string input;  // empty
  std::string out;

  const bool ok = Zstd_Compress(/*level=*/1, input.data(), input.size(), &out);

  ASSERT_TRUE(ok);
  // For empty input, Zstd still produces a valid (small) frame.
  ASSERT_FALSE(out.empty());
  DecompressAndExpectEqual(out, input);  // round-trip should be empty string
}

TEST_F(PortZstdCompressTest_39, OverwritesExistingOutputBuffer_39) {
  const std::string input = "Hello Zstandard!";
  std::string out = "garbage-garbage-garbage";  // pre-filled

  const bool ok = Zstd_Compress(/*level=*/5, input.data(), input.size(), &out);

  ASSERT_TRUE(ok);
  // Observable behavior: output contains compressed data (not old contents).
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out, "garbage-garbage-garbage");
  DecompressAndExpectEqual(out, input);
}

TEST_F(PortZstdCompressTest_39, HandlesLargeInput_1MB_Success_39) {
  // 1 MiB of repetitive data to remain fast and compressible.
  const size_t kSize = 1 << 20;
  std::string input;
  input.reserve(kSize);
  for (size_t i = 0; i < kSize; ++i) input.push_back(static_cast<char>('A' + (i % 3)));

  std::string out;
  const bool ok = Zstd_Compress(/*level=*/9, input.data(), input.size(), &out);

  ASSERT_TRUE(ok);
  ASSERT_FALSE(out.empty());
  DecompressAndExpectEqual(out, input);
}

TEST_F(PortZstdCompressTest_39, AcceptsExtremeLevelWithoutCrash_39) {
  // We do not assert a specific compression ratio or internal parameter behavior.
  // Only verify that the call succeeds and round-trips, treating internals as a black box.
  const std::string input = "level-boundary-check " + std::string(1024, 'x');

  std::string out_default;
  std::string out_extreme;

  ASSERT_TRUE(Zstd_Compress(/*level=*/1, input.data(), input.size(), &out_default));
  ASSERT_TRUE(Zstd_Compress(/*level=*/22, input.data(), input.size(), &out_extreme));

  ASSERT_FALSE(out_default.empty());
  ASSERT_FALSE(out_extreme.empty());

  DecompressAndExpectEqual(out_default, input);
  DecompressAndExpectEqual(out_extreme, input);
  // It's fine if sizes differ; we don't assume a particular outcome beyond validity.
}

#endif  // HAVE_ZSTD
