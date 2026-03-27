// File: test_types_databuf_read_uint32_1122.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

#include "exiv2/types.hpp"

namespace {

class DataBufReadUint32Test_1122 : public ::testing::Test {
 protected:
  static constexpr uint32_t kValue1 = 0x01020304u;
  static constexpr uint32_t kValue2 = 0xA1B2C3D4u;

  // These enumerators are expected to exist in Exiv2's public API.
  // If your codebase uses different names (e.g., ByteOrder::littleEndian),
  // adjust these two constants accordingly.
  static constexpr Exiv2::ByteOrder kLittle = Exiv2::littleEndian;
  static constexpr Exiv2::ByteOrder kBig = Exiv2::bigEndian;
};

TEST_F(DataBufReadUint32Test_1122, RoundTripLittleEndianAtZero_1122) {
  Exiv2::DataBuf buf(4);
  buf.write_uint32(/*offset=*/0, kValue1, kLittle);

  EXPECT_NO_THROW({
    const uint32_t v = buf.read_uint32(/*offset=*/0, kLittle);
    EXPECT_EQ(v, kValue1);
  });
}

TEST_F(DataBufReadUint32Test_1122, RoundTripBigEndianAtZero_1122) {
  Exiv2::DataBuf buf(4);
  buf.write_uint32(/*offset=*/0, kValue2, kBig);

  EXPECT_NO_THROW({
    const uint32_t v = buf.read_uint32(/*offset=*/0, kBig);
    EXPECT_EQ(v, kValue2);
  });
}

TEST_F(DataBufReadUint32Test_1122, BoundarySizeExactlyFourOffsetZeroSucceeds_1122) {
  Exiv2::DataBuf buf(4);
  buf.write_uint32(/*offset=*/0, kValue1, kBig);

  EXPECT_NO_THROW({
    const uint32_t v = buf.read_uint32(/*offset=*/0, kBig);
    EXPECT_EQ(v, kValue1);
  });
}

TEST_F(DataBufReadUint32Test_1122, BoundaryOffsetAtSizeMinusFourSucceeds_1122) {
  // size=5 => size-4=1, so offset=1 is the last valid offset for reading 4 bytes.
  Exiv2::DataBuf buf(5);
  buf.write_uint32(/*offset=*/1, kValue2, kLittle);

  EXPECT_NO_THROW({
    const uint32_t v = buf.read_uint32(/*offset=*/1, kLittle);
    EXPECT_EQ(v, kValue2);
  });
}

TEST_F(DataBufReadUint32Test_1122, ErrorDefaultConstructedEmptyThrowsOutOfRange_1122) {
  Exiv2::DataBuf buf;  // empty

  EXPECT_THROW(
      {
        (void)buf.read_uint32(/*offset=*/0, kLittle);
      },
      std::out_of_range);
}

TEST_F(DataBufReadUint32Test_1122, ErrorSizeLessThanFourThrowsOutOfRange_1122) {
  Exiv2::DataBuf buf(3);

  EXPECT_THROW(
      {
        (void)buf.read_uint32(/*offset=*/0, kBig);
      },
      std::out_of_range);
}

TEST_F(DataBufReadUint32Test_1122, ErrorOffsetGreaterThanSizeMinusFourThrowsOutOfRange_1122) {
  Exiv2::DataBuf buf(4);
  buf.write_uint32(/*offset=*/0, kValue1, kLittle);

  // For size=4, size-4=0; offset=1 is invalid and should throw.
  EXPECT_THROW(
      {
        (void)buf.read_uint32(/*offset=*/1, kLittle);
      },
      std::out_of_range);
}

TEST_F(DataBufReadUint32Test_1122, ErrorLargeOffsetPastEndThrowsOutOfRange_1122) {
  Exiv2::DataBuf buf(8);
  buf.write_uint32(/*offset=*/0, kValue1, kBig);

  // For size=8, valid offsets are 0..4 for 4-byte reads; offset=5 should throw.
  EXPECT_THROW(
      {
        (void)buf.read_uint32(/*offset=*/5, kBig);
      },
      std::out_of_range);
}

}  // namespace