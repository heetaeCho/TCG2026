// File: test_types_databuf_write_uint32_1123.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

#include "exiv2/types.hpp"

namespace {

// NOTE: We only test observable behavior through the public interface.
// We avoid assuming internal byte layout beyond what is already exposed by
// read_uint32/write_uint32 with a given ByteOrder.

class DataBufWriteUint32Test_1123 : public ::testing::Test {
 protected:
  static constexpr uint32_t kValue1 = 0x01020304u;
  static constexpr uint32_t kValue2 = 0xA1B2C3D4u;
};

TEST_F(DataBufWriteUint32Test_1123, ThrowsWhenBufferTooSmall_1123) {
  Exiv2::DataBuf buf(0);
  EXPECT_THROW(buf.write_uint32(/*offset=*/0, /*x=*/kValue1, Exiv2::littleEndian),
               std::out_of_range);

  Exiv2::DataBuf buf3(3);
  EXPECT_THROW(buf3.write_uint32(/*offset=*/0, /*x=*/kValue1, Exiv2::littleEndian),
               std::out_of_range);
}

TEST_F(DataBufWriteUint32Test_1123, WritesAtOffsetZeroAndReadBackLittleEndian_1123) {
  Exiv2::DataBuf buf(4);

  EXPECT_NO_THROW(buf.write_uint32(/*offset=*/0, /*x=*/kValue1, Exiv2::littleEndian));
  EXPECT_EQ(buf.read_uint32(/*offset=*/0, Exiv2::littleEndian), kValue1);
}

TEST_F(DataBufWriteUint32Test_1123, WritesAtOffsetZeroAndReadBackBigEndian_1123) {
  Exiv2::DataBuf buf(4);

  EXPECT_NO_THROW(buf.write_uint32(/*offset=*/0, /*x=*/kValue1, Exiv2::bigEndian));
  EXPECT_EQ(buf.read_uint32(/*offset=*/0, Exiv2::bigEndian), kValue1);
}

TEST_F(DataBufWriteUint32Test_1123, WritesAtLastValidOffsetAndReadBack_1123) {
  Exiv2::DataBuf buf(8);
  const size_t last_valid = buf.size() - 4;  // boundary offset

  EXPECT_NO_THROW(buf.write_uint32(last_valid, kValue2, Exiv2::littleEndian));
  EXPECT_EQ(buf.read_uint32(last_valid, Exiv2::littleEndian), kValue2);

  // Also verify we can write/read in the other byte order at the same boundary.
  EXPECT_NO_THROW(buf.write_uint32(last_valid, kValue1, Exiv2::bigEndian));
  EXPECT_EQ(buf.read_uint32(last_valid, Exiv2::bigEndian), kValue1);
}

TEST_F(DataBufWriteUint32Test_1123, ThrowsWhenOffsetPastLastValid_1123) {
  Exiv2::DataBuf buf(8);
  const size_t last_valid = buf.size() - 4;

  // offset == last_valid is OK (tested elsewhere); offset == last_valid + 1 must throw.
  EXPECT_THROW(buf.write_uint32(last_valid + 1, kValue1, Exiv2::littleEndian),
               std::out_of_range);

  // Also test a far-out offset.
  EXPECT_THROW(buf.write_uint32(static_cast<size_t>(1000), kValue1, Exiv2::bigEndian),
               std::out_of_range);
}

TEST_F(DataBufWriteUint32Test_1123, OverwritesExistingValueAtSameOffset_1123) {
  Exiv2::DataBuf buf(4);

  ASSERT_NO_THROW(buf.write_uint32(0, kValue1, Exiv2::littleEndian));
  EXPECT_EQ(buf.read_uint32(0, Exiv2::littleEndian), kValue1);

  ASSERT_NO_THROW(buf.write_uint32(0, kValue2, Exiv2::littleEndian));
  EXPECT_EQ(buf.read_uint32(0, Exiv2::littleEndian), kValue2);
}

TEST_F(DataBufWriteUint32Test_1123, MultipleWritesAtDifferentOffsetsDoNotInterfere_1123) {
  Exiv2::DataBuf buf(12);

  const size_t off0 = 0;
  const size_t off1 = 4;
  const size_t off2 = 8;

  ASSERT_NO_THROW(buf.write_uint32(off0, kValue1, Exiv2::littleEndian));
  ASSERT_NO_THROW(buf.write_uint32(off1, kValue2, Exiv2::littleEndian));
  ASSERT_NO_THROW(buf.write_uint32(off2, kValue1, Exiv2::bigEndian));

  EXPECT_EQ(buf.read_uint32(off0, Exiv2::littleEndian), kValue1);
  EXPECT_EQ(buf.read_uint32(off1, Exiv2::littleEndian), kValue2);
  EXPECT_EQ(buf.read_uint32(off2, Exiv2::bigEndian), kValue1);
}

}  // namespace