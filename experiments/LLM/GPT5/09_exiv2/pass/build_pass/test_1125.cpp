// File: test_types_databuf_write_uint64_1125.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>

#include "exiv2/types.hpp"

namespace {

using Exiv2::DataBuf;

// Helper to avoid relying on internal state: verify via public read_uint64 and public c_data().
static void ExpectBytesEq(const DataBuf& buf, size_t offset, const uint8_t* expected, size_t n) {
  const auto* p = buf.c_data(offset);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(0, std::memcmp(p, expected, n));
}

}  // namespace

TEST(DataBufWriteUint64Test_1125, WritesAndReadsLittleEndian_1125) {
  DataBuf buf(8);

  const uint64_t value = 0x0102030405060708ULL;
  buf.write_uint64(0, value, Exiv2::littleEndian);

  EXPECT_EQ(buf.read_uint64(0, Exiv2::littleEndian), value);

  // Also validate the raw byte layout through the public c_data() API.
  const uint8_t expected[8] = {0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
  ExpectBytesEq(buf, 0, expected, sizeof(expected));
}

TEST(DataBufWriteUint64Test_1125, WritesAndReadsBigEndian_1125) {
  DataBuf buf(8);

  const uint64_t value = 0x0102030405060708ULL;
  buf.write_uint64(0, value, Exiv2::bigEndian);

  EXPECT_EQ(buf.read_uint64(0, Exiv2::bigEndian), value);

  const uint8_t expected[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  ExpectBytesEq(buf, 0, expected, sizeof(expected));
}

TEST(DataBufWriteUint64Test_1125, WritesAtLastValidOffset_1125) {
  DataBuf buf(16);

  const uint64_t v0 = 0x1111111111111111ULL;
  const uint64_t v1 = 0xAABBCCDDEEFF0011ULL;

  // Boundary: offset == size - 8 is allowed.
  buf.write_uint64(0, v0, Exiv2::bigEndian);
  buf.write_uint64(8, v1, Exiv2::bigEndian);

  EXPECT_EQ(buf.read_uint64(0, Exiv2::bigEndian), v0);
  EXPECT_EQ(buf.read_uint64(8, Exiv2::bigEndian), v1);
}

TEST(DataBufWriteUint64Test_1125, ThrowsWhenBufferTooSmall_1125) {
  DataBuf buf(7);

  try {
    buf.write_uint64(0, 0x0ULL, Exiv2::littleEndian);
    FAIL() << "Expected std::out_of_range";
  } catch (const std::out_of_range& e) {
    EXPECT_NE(std::string(e.what()).find("Overflow in Exiv2::DataBuf::write_uint64"), std::string::npos);
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TEST(DataBufWriteUint64Test_1125, ThrowsWhenOffsetWouldOverflow_1125) {
  DataBuf buf(8);

  // For size==8, only offset==0 is valid; offset==1 must throw.
  EXPECT_THROW(buf.write_uint64(1, 0x0ULL, Exiv2::littleEndian), std::out_of_range);
}

TEST(DataBufWriteUint64Test_1125, ThrowsWhenOffsetGreaterThanSizeMinus8_1125) {
  DataBuf buf(16);

  // size - 8 == 8, so offset 9 must throw.
  try {
    buf.write_uint64(9, 0x1234ULL, Exiv2::bigEndian);
    FAIL() << "Expected std::out_of_range";
  } catch (const std::out_of_range& e) {
    EXPECT_NE(std::string(e.what()).find("Overflow in Exiv2::DataBuf::write_uint64"), std::string::npos);
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TEST(DataBufWriteUint64Test_1125, DoesNotThrowAtOffsetEqualSizeMinus8_1125) {
  DataBuf buf(16);

  EXPECT_NO_THROW(buf.write_uint64(8, 0x0102030405060708ULL, Exiv2::littleEndian));
  EXPECT_EQ(buf.read_uint64(8, Exiv2::littleEndian), 0x0102030405060708ULL);
}