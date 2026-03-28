// ============================================================================
// TEST_ID: 968
// Unit tests for internal helper: Exiv2::zlibToDataBuf (src/pngimage.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include <zlib.h>

// Exiv2 types (DataBuf, byte, etc.)
#include "exiv2/types.hpp"

// NOTE: zlibToDataBuf is a TU-local (static) helper in pngimage.cpp.
// To test it without changing production code, we include the .cpp into this
// test translation unit so the static symbol is visible here.
//
// This follows the "black box" rule: tests only observe return values and
// public DataBuf effects, and do not re-implement the helper.
#include "pngimage.cpp"

namespace {

class ZlibToDataBufTest_968 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> CompressZlib(const std::vector<Exiv2::byte>& input, int level = Z_BEST_SPEED) {
    uLongf bound = compressBound(static_cast<uLong>(input.size()));
    std::vector<Exiv2::byte> out(bound);

    uLongf outLen = bound;
    const Bytef* src = input.empty() ? nullptr : reinterpret_cast<const Bytef*>(input.data());
    int rc = compress2(reinterpret_cast<Bytef*>(out.data()), &outLen, src, static_cast<uLong>(input.size()), level);
    EXPECT_EQ(rc, Z_OK);

    out.resize(static_cast<size_t>(outLen));
    return out;
  }

  static std::vector<Exiv2::byte> MakePatternBytes(size_t size) {
    std::vector<Exiv2::byte> v(size);
    for (size_t i = 0; i < size; ++i) {
      v[i] = static_cast<Exiv2::byte>((i * 131u + 17u) & 0xFFu);
    }
    return v;
  }

  static void ExpectDataBufEquals(const Exiv2::DataBuf& buf, const std::vector<Exiv2::byte>& expected) {
    ASSERT_EQ(buf.size(), expected.size());
    if (!expected.empty()) {
      ASSERT_NE(buf.c_data(0), nullptr);
      EXPECT_EQ(std::memcmp(buf.c_data(0), expected.data(), expected.size()), 0);
    }
  }
};

TEST_F(ZlibToDataBufTest_968, DecompressesRoundTripSmall_968) {
  const std::vector<Exiv2::byte> original = MakePatternBytes(256);
  const std::vector<Exiv2::byte> compressed = CompressZlib(original);

  Exiv2::DataBuf out;
  const bool ok = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), out);

  ASSERT_TRUE(ok);
  ExpectDataBufEquals(out, original);
}

TEST_F(ZlibToDataBufTest_968, DecompressesEmptyPayload_968) {
  const std::vector<Exiv2::byte> original;  // empty
  const std::vector<Exiv2::byte> compressed = CompressZlib(original);

  Exiv2::DataBuf out;
  const bool ok = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), out);

  ASSERT_TRUE(ok);
  EXPECT_EQ(out.size(), 0u);
  EXPECT_TRUE(out.empty());
}

TEST_F(ZlibToDataBufTest_968, DecompressesWhenUncompressedMuchLargerThanCompressed_968) {
  // Highly-compressible data to ensure the decompressor needs a larger output buffer
  // than the compressed input length.
  std::vector<Exiv2::byte> original(1u << 20, static_cast<Exiv2::byte>(0));  // 1 MiB of zeros
  const std::vector<Exiv2::byte> compressed = CompressZlib(original, Z_BEST_COMPRESSION);

  ASSERT_LT(compressed.size(), original.size());  // test setup sanity

  Exiv2::DataBuf out;
  const bool ok = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), out);

  ASSERT_TRUE(ok);
  ExpectDataBufEquals(out, original);
}

TEST_F(ZlibToDataBufTest_968, OverwritesExistingDataBufContentOnSuccess_968) {
  const std::vector<Exiv2::byte> original = MakePatternBytes(4096);
  const std::vector<Exiv2::byte> compressed = CompressZlib(original);

  Exiv2::DataBuf out;
  out.alloc(7);  // pre-allocate to a different size/content
  if (!out.empty()) {
    out.write_uint8(0, 0xAB);
  }

  const bool ok = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), out);

  ASSERT_TRUE(ok);
  ExpectDataBufEquals(out, original);
}

TEST_F(ZlibToDataBufTest_968, ReturnsFalseForInvalidCompressedStream_968) {
  // Not a valid zlib stream.
  const std::vector<Exiv2::byte> garbage = MakePatternBytes(128);

  Exiv2::DataBuf out;
  const bool ok = Exiv2::zlibToDataBuf(garbage.data(), static_cast<uLongf>(garbage.size()), out);

  EXPECT_FALSE(ok);
  // No assumptions about out's size/content on failure (black-box).
}

TEST_F(ZlibToDataBufTest_968, ReturnsFalseForTruncatedValidStream_968) {
  const std::vector<Exiv2::byte> original = MakePatternBytes(8192);
  std::vector<Exiv2::byte> compressed = CompressZlib(original, Z_BEST_COMPRESSION);

  ASSERT_GT(compressed.size(), 4u);
  compressed.resize(compressed.size() - 3u);  // truncate tail

  Exiv2::DataBuf out;
  const bool ok = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), out);

  EXPECT_FALSE(ok);
  // No assumptions about out's size/content on failure (black-box).
}

}  // namespace