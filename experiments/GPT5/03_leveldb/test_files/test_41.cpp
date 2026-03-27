// File: zstd_uncompress_test.cc
#include <gtest/gtest.h>
#include <vector>
#include <cstring>

#include "port/port_stdcxx.h"

using leveldb::port::Zstd_Uncompress;

class ZstdUncompressTest_41 : public ::testing::Test {};

// ---------------------------------------------------------------
// When ZSTD support is NOT compiled in, the function must return false.
// ---------------------------------------------------------------
#if !HAVE_ZSTD
TEST_F(ZstdUncompressTest_41, ReturnsFalseWithoutZstd_41) {
  const char input[] = "any-bytes-here-ignored";
  char output[32] = {};
  bool ok = Zstd_Uncompress(input, sizeof(input), output);
  EXPECT_FALSE(ok);
}
#endif  // !HAVE_ZSTD

// ---------------------------------------------------------------
// Tests that apply only when ZSTD support is compiled in.
// We exercise observable behavior using real ZSTD compression
// (no internal logic assumptions).
// ---------------------------------------------------------------
#if HAVE_ZSTD
#include <zstd.h>

TEST_F(ZstdUncompressTest_41, InvalidInputReturnsFalse_41) {
  // Make a buffer that is not a valid Zstd frame.
  std::vector<char> bogus(64, static_cast<char>(0xFF));
  std::vector<char> out(64, 0);

  bool ok = Zstd_Uncompress(bogus.data(), bogus.size(), out.data());
  EXPECT_FALSE(ok);
}

TEST_F(ZstdUncompressTest_41, ValidRoundTripReturnsTrueAndWritesBytes_41) {
  // Source data
  const char* src = "The quick brown fox jumps over the lazy dog";
  const size_t src_len = std::strlen(src);

  // Compress using ZSTD so we can treat Zstd_Uncompress as a black box.
  size_t max_compressed = ZSTD_compressBound(src_len);
  std::vector<char> compressed(max_compressed);
  size_t csize = ZSTD_compress(
      compressed.data(), compressed.size(),
      src, src_len,
      /*compressionLevel=*/1);
  ASSERT_FALSE(ZSTD_isError(csize)) << ZSTD_getErrorName(csize);
  compressed.resize(csize);

  // Prepare output buffer exactly the size of original
  std::vector<char> out(src_len, 0);

  bool ok = Zstd_Uncompress(compressed.data(), compressed.size(), out.data());
  ASSERT_TRUE(ok);

  // Verify the decompressed bytes match the original.
  ASSERT_EQ(out.size(), src_len);
  EXPECT_EQ(0, std::memcmp(out.data(), src, src_len));
}

TEST_F(ZstdUncompressTest_41, ZeroLengthInputReturnsFalse_41) {
  // Pass a non-null pointer with zero length; output is a valid buffer.
  const char* empty = "";
  char out = 0;

  bool ok = Zstd_Uncompress(empty, 0, &out);
  EXPECT_FALSE(ok);
}
#endif  // HAVE_ZSTD
