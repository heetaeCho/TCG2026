// File: test_types_read_uint64_1124.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>

#include "exiv2/types.hpp"

namespace {

class DataBufReadUint64Test_1124 : public ::testing::Test {};

TEST_F(DataBufReadUint64Test_1124, EmptyBufferThrowsOutOfRange_1124) {
  Exiv2::DataBuf buf;
  EXPECT_THROW((void)buf.read_uint64(0, Exiv2::littleEndian), std::out_of_range);
  EXPECT_THROW((void)buf.read_uint64(0, Exiv2::bigEndian), std::out_of_range);
}

TEST_F(DataBufReadUint64Test_1124, SmallerThanEightBytesThrowsOutOfRange_1124) {
  Exiv2::DataBuf buf(7);
  EXPECT_THROW((void)buf.read_uint64(0, Exiv2::littleEndian), std::out_of_range);
  EXPECT_THROW((void)buf.read_uint64(0, Exiv2::bigEndian), std::out_of_range);
}

TEST_F(DataBufReadUint64Test_1124, ExactEightBytesOffsetZeroSucceedsOffsetOneThrows_1124) {
  Exiv2::DataBuf buf(8);

  // Populate with a recognizable pattern.
  const uint8_t bytes[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  for (size_t i = 0; i < 8; ++i) buf.write_uint8(i, bytes[i]);

  EXPECT_NO_THROW((void)buf.read_uint64(0, Exiv2::bigEndian));
  EXPECT_NO_THROW((void)buf.read_uint64(0, Exiv2::littleEndian));

  // Boundary: offset > (size - 8) should throw. For size=8, only offset 0 is valid.
  EXPECT_THROW((void)buf.read_uint64(1, Exiv2::bigEndian), std::out_of_range);
  EXPECT_THROW((void)buf.read_uint64(1, Exiv2::littleEndian), std::out_of_range);
}

TEST_F(DataBufReadUint64Test_1124, EndiannessInterpretsSameBytesDifferently_1124) {
  Exiv2::DataBuf buf(8);

  const uint8_t bytes[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  for (size_t i = 0; i < 8; ++i) buf.write_uint8(i, bytes[i]);

  const uint64_t asBig = buf.read_uint64(0, Exiv2::bigEndian);
  const uint64_t asLittle = buf.read_uint64(0, Exiv2::littleEndian);

  EXPECT_EQ(asBig, 0x0123456789ABCDEFULL);
  EXPECT_EQ(asLittle, 0xEFCDAB8967452301ULL);
  EXPECT_NE(asBig, asLittle);
}

TEST_F(DataBufReadUint64Test_1124, ValidAtLastPossibleOffsetInLargerBuffer_1124) {
  Exiv2::DataBuf buf(16);

  // Write a known value at the last valid starting offset (size - 8 = 8).
  const uint64_t value = 0x1122334455667788ULL;
  buf.write_uint64(8, value, Exiv2::bigEndian);

  EXPECT_EQ(buf.read_uint64(8, Exiv2::bigEndian), value);

  // Boundary just past last valid start should throw: offset 9 for size 16.
  EXPECT_THROW((void)buf.read_uint64(9, Exiv2::bigEndian), std::out_of_range);
  EXPECT_THROW((void)buf.read_uint64(9, Exiv2::littleEndian), std::out_of_range);
}

TEST_F(DataBufReadUint64Test_1124, RoundTripWithWriteUint64AtNonZeroOffset_1124) {
  Exiv2::DataBuf buf(24);

  const size_t offset = 4;
  const uint64_t value = 0xFFEEDDCCBBAA0099ULL;

  buf.write_uint64(offset, value, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint64(offset, Exiv2::littleEndian), value);

  // Also verify that reading from the wrong offset fails when it would overflow.
  EXPECT_THROW((void)buf.read_uint64(buf.size() - 7, Exiv2::littleEndian), std::out_of_range);
}

}  // namespace