// File: test_image_byteswap8_1062.cpp
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::DataBuf;
using Exiv2::Image;

// Helper that builds the same "native" uint64_t value as the implementation does:
// it writes bytes into the in-memory representation of a uint64_t in increasing
// address order.
static uint64_t BuildNativeUint64From8Bytes(const Exiv2::byte* bytes8) {
  uint64_t v = 0;
  auto* p = reinterpret_cast<Exiv2::byte*>(&v);
  for (int i = 0; i < 8; ++i) {
    p[i] = bytes8[i];
  }
  return v;
}

static DataBuf MakeBufFromBytes(const std::vector<Exiv2::byte>& bytes) {
  return DataBuf(bytes.data(), bytes.size());
}

}  // namespace

// The TEST_ID is 1062

TEST(ImageByteSwap8Test_1062, Reads8BytesAtOffsetAndMatchesNativeNoSwap_1062) {
  std::vector<Exiv2::byte> bytes = {
      0xFF, 0xEE, 0xDD, 0xCC,  // padding
      0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  // payload (8 bytes)
      0x10, 0x20  // trailing
  };
  DataBuf buf = MakeBufFromBytes(bytes);

  const size_t offset = 4;
  const uint64_t expected_native = BuildNativeUint64From8Bytes(bytes.data() + offset);

  uint64_t out = 0;
  ASSERT_NO_THROW(out = Image::byteSwap8(buf, offset, /*bSwap=*/false));
  EXPECT_EQ(out, expected_native);
}

TEST(ImageByteSwap8Test_1062, SwapFlagMatchesByteSwapOnResult_1062) {
  std::vector<Exiv2::byte> bytes = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
  };
  DataBuf buf = MakeBufFromBytes(bytes);

  const size_t offset = 2;

  uint64_t noSwap = 0;
  uint64_t withSwap = 0;
  ASSERT_NO_THROW(noSwap = Image::byteSwap8(buf, offset, /*bSwap=*/false));
  ASSERT_NO_THROW(withSwap = Image::byteSwap8(buf, offset, /*bSwap=*/true));

  // Observable relationship through the public interface:
  // swapping the no-swap result should equal the swap result.
  EXPECT_EQ(Image::byteSwap(noSwap, /*bSwap=*/true), withSwap);

  // And swapping again should return to the original (involution property),
  // verified via the public byteSwap interface.
  EXPECT_EQ(Image::byteSwap(withSwap, /*bSwap=*/true), noSwap);
}

TEST(ImageByteSwap8Test_1062, WorksWhenOffsetIsZero_1062) {
  std::vector<Exiv2::byte> bytes = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x02, 0x03, 0x04};
  DataBuf buf = MakeBufFromBytes(bytes);

  const uint64_t expected_native = BuildNativeUint64From8Bytes(bytes.data());

  uint64_t out = 0;
  ASSERT_NO_THROW(out = Image::byteSwap8(buf, /*offset=*/0, /*bSwap=*/false));
  EXPECT_EQ(out, expected_native);
}

TEST(ImageByteSwap8Test_1062, WorksWhenBufferIsExactlyOffsetPlus8Bytes_1062) {
  // Boundary: minimal size for a given offset (size == offset + 8).
  const size_t offset = 3;
  std::vector<Exiv2::byte> bytes(offset + 8);
  // Fill deterministically.
  for (size_t i = 0; i < bytes.size(); ++i) bytes[i] = static_cast<Exiv2::byte>(i * 7u + 1u);

  DataBuf buf = MakeBufFromBytes(bytes);
  const uint64_t expected_native = BuildNativeUint64From8Bytes(bytes.data() + offset);

  uint64_t out = 0;
  ASSERT_NO_THROW(out = Image::byteSwap8(buf, offset, /*bSwap=*/false));
  EXPECT_EQ(out, expected_native);
}

TEST(ImageByteSwap8Test_1062, SwapTrueDiffersFromSwapFalseForNonPalindromicBytes_1062) {
  // Choose bytes that are very unlikely to be invariant under byte swapping.
  std::vector<Exiv2::byte> bytes = {
      0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18, 0x29, 0x3A,
  };
  DataBuf buf = MakeBufFromBytes(bytes);

  uint64_t noSwap = 0;
  uint64_t withSwap = 0;
  ASSERT_NO_THROW(noSwap = Image::byteSwap8(buf, /*offset=*/1, /*bSwap=*/false));
  ASSERT_NO_THROW(withSwap = Image::byteSwap8(buf, /*offset=*/1, /*bSwap=*/true));

  // If swapping is active, the output should match applying byteSwap(true) to the no-swap output.
  EXPECT_EQ(withSwap, Image::byteSwap(noSwap, /*bSwap=*/true));

  // And for this chosen pattern, it's expected they won't be equal (observable expectation).
  // If they are equal on some platform/config, this assertion would fail; however the relationship
  // above remains the primary contract check.
  EXPECT_NE(noSwap, withSwap);
}