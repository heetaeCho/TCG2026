// File: test_image_byteswap2_1060.cpp
// TEST_ID: 1060

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include <exiv2/image.hpp>
#include <exiv2/types.hpp>

namespace {

class ImageByteSwap2Test_1060 : public ::testing::Test {
 protected:
  static Exiv2::DataBuf makeBuf(std::initializer_list<uint8_t> bytes) {
    Exiv2::DataBuf buf(bytes.size());
    size_t i = 0;
    for (auto b : bytes) {
      buf.write_uint8(i++, b);
    }
    return buf;
  }
};

TEST_F(ImageByteSwap2Test_1060, ReadsTwoBytesAtOffsetZero_NoThrow_1060) {
  const auto buf = makeBuf({0x01, 0x02});
  EXPECT_NO_THROW({
    (void)Exiv2::Image::byteSwap2(buf, 0, false);
    (void)Exiv2::Image::byteSwap2(buf, 0, true);
  });
}

TEST_F(ImageByteSwap2Test_1060, ReadsTwoBytesAtNonZeroOffset_NoThrow_1060) {
  const auto buf = makeBuf({0xAA, 0x10, 0x20, 0xBB});
  EXPECT_NO_THROW({
    (void)Exiv2::Image::byteSwap2(buf, 1, false);  // reads 0x10,0x20
    (void)Exiv2::Image::byteSwap2(buf, 1, true);
  });
}

TEST_F(ImageByteSwap2Test_1060, Boundary_LastValidOffset_NoThrow_1060) {
  const auto buf = makeBuf({0x11, 0x22, 0x33});
  // size=3, last valid offset for 2 bytes is 1
  EXPECT_NO_THROW({
    (void)Exiv2::Image::byteSwap2(buf, 1, false);
    (void)Exiv2::Image::byteSwap2(buf, 1, true);
  });
}

TEST_F(ImageByteSwap2Test_1060, OutOfRange_ThrowsWhenBufferTooSmall_1060) {
  const auto buf = makeBuf({0xAB});  // only 1 byte; reading 2 bytes must fail
  EXPECT_ANY_THROW((void)Exiv2::Image::byteSwap2(buf, 0, false));
  EXPECT_ANY_THROW((void)Exiv2::Image::byteSwap2(buf, 0, true));
}

TEST_F(ImageByteSwap2Test_1060, OutOfRange_ThrowsWhenOffsetAtEnd_1060) {
  const auto buf = makeBuf({0xDE, 0xAD});
  // offset==size is invalid; also offset==size-1 invalid for 2-byte read
  EXPECT_ANY_THROW((void)Exiv2::Image::byteSwap2(buf, 2, false));
  EXPECT_ANY_THROW((void)Exiv2::Image::byteSwap2(buf, 2, true));
  EXPECT_ANY_THROW((void)Exiv2::Image::byteSwap2(buf, 1, false));
  EXPECT_ANY_THROW((void)Exiv2::Image::byteSwap2(buf, 1, true));
}

TEST_F(ImageByteSwap2Test_1060, Deterministic_SameInputSameOutput_1060) {
  const auto buf = makeBuf({0x01, 0xFE, 0x10, 0x20});

  const auto a1 = Exiv2::Image::byteSwap2(buf, 0, false);
  const auto a2 = Exiv2::Image::byteSwap2(buf, 0, false);
  EXPECT_EQ(a1, a2);

  const auto b1 = Exiv2::Image::byteSwap2(buf, 2, true);
  const auto b2 = Exiv2::Image::byteSwap2(buf, 2, true);
  EXPECT_EQ(b1, b2);
}

TEST_F(ImageByteSwap2Test_1060, SwapFlag_ConsistentWithByteSwapOnReturnedValue_1060) {
  // This test only relies on the public interface relation:
  // byteSwap2(buf, off, true) should match applying Image::byteSwap(..., true)
  // to the value returned by byteSwap2(buf, off, false) (common contract:
  // byteSwap(value, false) returns value unchanged).
  const auto buf = makeBuf({0x12, 0x34, 0xAB, 0xCD});

  const uint16_t v_no_swap = Exiv2::Image::byteSwap2(buf, 0, false);
  const uint16_t v_swap = Exiv2::Image::byteSwap2(buf, 0, true);

  EXPECT_EQ(v_swap, Exiv2::Image::byteSwap(v_no_swap, true));

  const uint16_t v_no_swap_2 = Exiv2::Image::byteSwap2(buf, 2, false);
  const uint16_t v_swap_2 = Exiv2::Image::byteSwap2(buf, 2, true);

  EXPECT_EQ(v_swap_2, Exiv2::Image::byteSwap(v_no_swap_2, true));
}

}  // namespace