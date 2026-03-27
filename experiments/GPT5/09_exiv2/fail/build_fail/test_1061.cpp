// ============================================================================
// TestProjects/exiv2/tests/test_image_byteswap4_1061.cpp
// Unit tests for Exiv2::Image::byteSwap4(const DataBuf&, size_t, bool)
// TEST_ID: 1061
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::DataBuf;
using Exiv2::Image;

// Helper: compute the packed uint32_t value as constructed by byteSwap4,
// using only public API (DataBuf::read_uint32 + Image::isLittleEndianPlatform()).
static uint32_t packedHostOrderU32(const DataBuf& buf, size_t offset) {
  const Exiv2::ByteOrder hostOrder =
      Image::isLittleEndianPlatform() ? Exiv2::littleEndian : Exiv2::bigEndian;
  return buf.read_uint32(offset, hostOrder);
}

class ImageByteSwap4Test_1061 : public ::testing::Test {
 protected:
  static DataBuf makeBufWithPattern(size_t size) {
    DataBuf b(size);
    // Fill with a deterministic pattern (no reliance on internal storage).
    for (size_t i = 0; i < size; ++i) {
      b.write_uint8(i, static_cast<uint8_t>((0xA0u + i) & 0xFFu));
    }
    return b;
  }
};

TEST_F(ImageByteSwap4Test_1061, NoSwapMatchesByteSwapOfPackedHostValue_1061) {
  DataBuf buf(8);
  buf.write_uint8(0, 0x01);
  buf.write_uint8(1, 0x23);
  buf.write_uint8(2, 0x45);
  buf.write_uint8(3, 0x67);

  const uint32_t packed = packedHostOrderU32(buf, 0);
  const uint32_t expected = Image::byteSwap(packed, /*bSwap=*/false);

  EXPECT_EQ(Image::byteSwap4(buf, 0, /*bSwap=*/false), expected);
}

TEST_F(ImageByteSwap4Test_1061, SwapTrueMatchesByteSwapOfPackedHostValue_1061) {
  DataBuf buf(8);
  buf.write_uint8(0, 0x89);
  buf.write_uint8(1, 0xAB);
  buf.write_uint8(2, 0xCD);
  buf.write_uint8(3, 0xEF);

  const uint32_t packed = packedHostOrderU32(buf, 0);
  const uint32_t expected = Image::byteSwap(packed, /*bSwap=*/true);

  EXPECT_EQ(Image::byteSwap4(buf, 0, /*bSwap=*/true), expected);
}

TEST_F(ImageByteSwap4Test_1061, NonZeroOffsetReadsCorrectFourBytes_1061) {
  DataBuf buf = makeBufWithPattern(16);

  const size_t offset = 5;  // choose a non-zero offset
  const uint32_t packed = packedHostOrderU32(buf, offset);

  EXPECT_EQ(Image::byteSwap4(buf, offset, /*bSwap=*/false), Image::byteSwap(packed, false));
  EXPECT_EQ(Image::byteSwap4(buf, offset, /*bSwap=*/true), Image::byteSwap(packed, true));
}

TEST_F(ImageByteSwap4Test_1061, BoundaryOffsetAtSizeMinus4IsValid_1061) {
  DataBuf buf = makeBufWithPattern(12);
  const size_t offset = buf.size() - 4;

  const uint32_t packed = packedHostOrderU32(buf, offset);

  EXPECT_NO_THROW({
    const uint32_t r0 = Image::byteSwap4(buf, offset, /*bSwap=*/false);
    const uint32_t r1 = Image::byteSwap4(buf, offset, /*bSwap=*/true);
    EXPECT_EQ(r0, Image::byteSwap(packed, false));
    EXPECT_EQ(r1, Image::byteSwap(packed, true));
  });
}

TEST_F(ImageByteSwap4Test_1061, DoesNotModifyUnderlyingBytes_1061) {
  DataBuf buf(8);
  // Place a recognizable 4-byte window starting at offset 2.
  buf.write_uint8(0, 0xFF);
  buf.write_uint8(1, 0xEE);
  buf.write_uint8(2, 0x10);
  buf.write_uint8(3, 0x20);
  buf.write_uint8(4, 0x30);
  buf.write_uint8(5, 0x40);
  buf.write_uint8(6, 0xDD);
  buf.write_uint8(7, 0xCC);

  // Snapshot the relevant bytes before.
  const uint8_t before2 = buf.read_uint8(2);
  const uint8_t before3 = buf.read_uint8(3);
  const uint8_t before4 = buf.read_uint8(4);
  const uint8_t before5 = buf.read_uint8(5);

  (void)Image::byteSwap4(buf, 2, /*bSwap=*/false);
  (void)Image::byteSwap4(buf, 2, /*bSwap=*/true);

  // Verify unchanged after calls.
  EXPECT_EQ(buf.read_uint8(2), before2);
  EXPECT_EQ(buf.read_uint8(3), before3);
  EXPECT_EQ(buf.read_uint8(4), before4);
  EXPECT_EQ(buf.read_uint8(5), before5);
}

}  // namespace