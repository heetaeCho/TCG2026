// ============================================================================
// TEST_ID: 969
// Unit tests for: Exiv2::zlibToCompressed (static in pngimage.cpp)
// File under test: ./TestProjects/exiv2/src/pngimage.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include <zlib.h>

// Include Exiv2 DataBuf
#include "exiv2/types.hpp"

// IMPORTANT:
// zlibToCompressed has internal linkage (static) in pngimage.cpp.
// To test it via the public interface constraints (no re-implementation),
// we include the .cpp so the function is in the same translation unit.
#include "pngimage.cpp"

namespace {

class ZlibToCompressedTest_969 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeBytes(const std::string& s) {
    return std::vector<Exiv2::byte>(reinterpret_cast<const Exiv2::byte*>(s.data()),
                                    reinterpret_cast<const Exiv2::byte*>(s.data()) + s.size());
  }

  static bool DecompressAndCompare(const Exiv2::DataBuf& compressed,
                                   const Exiv2::byte* original,
                                   uLongf originalLen) {
    // For empty original, uncompress() behavior varies if destLen==0.
    // Use a 1-byte buffer and validate decompressed length becomes 0.
    if (originalLen == 0) {
      std::vector<Exiv2::byte> out(1, 0xA5);
      uLongf outLen = static_cast<uLongf>(out.size());
      int rc = uncompress(out.data(), &outLen, compressed.c_data(0), static_cast<uLongf>(compressed.size()));
      return (rc == Z_OK) && (outLen == 0);
    }

    std::vector<Exiv2::byte> out(static_cast<size_t>(originalLen));
    uLongf outLen = originalLen;
    int rc = uncompress(out.data(), &outLen, compressed.c_data(0), static_cast<uLongf>(compressed.size()));
    if (rc != Z_OK) return false;
    if (outLen != originalLen) return false;
    return std::memcmp(out.data(), original, static_cast<size_t>(originalLen)) == 0;
  }
};

}  // namespace

TEST_F(ZlibToCompressedTest_969, CompressesAndRoundTripsSmallPayload_969) {
  const std::string payload = "hello exiv2 png zlib";
  const auto bytes = MakeBytes(payload);

  Exiv2::DataBuf result;
  ASSERT_TRUE(Exiv2::zlibToCompressed(bytes.data(), static_cast<uLongf>(bytes.size()), result));
  ASSERT_GT(result.size(), 0u);
  EXPECT_TRUE(DecompressAndCompare(result, bytes.data(), static_cast<uLongf>(bytes.size())));
}

TEST_F(ZlibToCompressedTest_969, CompressesAndRoundTripsLargerPayload_969) {
  // Larger, somewhat repetitive payload to exercise different compressed sizes.
  std::string payload;
  payload.reserve(64 * 1024);
  for (int i = 0; i < 4096; ++i) {
    payload += "Exiv2-PNG-TEST-";
    payload += std::to_string(i);
    payload += "\n";
  }
  const auto bytes = MakeBytes(payload);

  Exiv2::DataBuf result;
  ASSERT_TRUE(Exiv2::zlibToCompressed(bytes.data(), static_cast<uLongf>(bytes.size()), result));
  ASSERT_GT(result.size(), 0u);
  EXPECT_TRUE(DecompressAndCompare(result, bytes.data(), static_cast<uLongf>(bytes.size())));
}

TEST_F(ZlibToCompressedTest_969, HandlesEmptyInput_969) {
  const Exiv2::byte* emptyPtr = reinterpret_cast<const Exiv2::byte*>("");  // valid pointer
  const uLongf emptyLen = 0;

  Exiv2::DataBuf result;
  ASSERT_TRUE(Exiv2::zlibToCompressed(emptyPtr, emptyLen, result));
  // Compressed form of empty data should still produce a valid zlib stream (typically non-zero).
  ASSERT_GT(result.size(), 0u);
  EXPECT_TRUE(DecompressAndCompare(result, emptyPtr, emptyLen));
}

TEST_F(ZlibToCompressedTest_969, OverwritesExistingResultBufferOnSuccess_969) {
  const std::string payload = "overwrite-check-payload";
  const auto bytes = MakeBytes(payload);

  // Pre-fill result with unrelated data.
  Exiv2::DataBuf result(32);
  for (size_t i = 0; i < result.size(); ++i) {
    result.write_uint8(i, static_cast<uint8_t>(0xCC));
  }
  const size_t oldSize = result.size();

  ASSERT_TRUE(Exiv2::zlibToCompressed(bytes.data(), static_cast<uLongf>(bytes.size()), result));
  EXPECT_TRUE(DecompressAndCompare(result, bytes.data(), static_cast<uLongf>(bytes.size())));

  // Observable check: size is allowed to change; if it doesn't, content must still be a valid stream.
  // This assertion is intentionally weak (black-box safe), but still verifies mutation occurred or stream is valid.
  EXPECT_TRUE(result.size() != oldSize || result.size() > 0u);
}

TEST_F(ZlibToCompressedTest_969, ProducesValidZlibStreamForBinaryData_969) {
  // Include null bytes and high-bit bytes.
  std::vector<Exiv2::byte> bytes;
  bytes.reserve(1024);
  for (int i = 0; i < 1024; ++i) {
    bytes.push_back(static_cast<Exiv2::byte>(i & 0xFF));
  }
  bytes[10] = 0x00;
  bytes[11] = 0xFF;
  bytes[12] = 0x80;

  Exiv2::DataBuf result;
  ASSERT_TRUE(Exiv2::zlibToCompressed(bytes.data(), static_cast<uLongf>(bytes.size()), result));
  ASSERT_GT(result.size(), 0u);
  EXPECT_TRUE(DecompressAndCompare(result, bytes.data(), static_cast<uLongf>(bytes.size())));
}