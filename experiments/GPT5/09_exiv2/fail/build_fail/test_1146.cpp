// TEST_ID 1146
// File: test_types_ul2data_1146.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

#include "exiv2/types.hpp"

namespace {
// Forward declaration (implemented in the real codebase)
namespace Exiv2 {
using byte = unsigned char;  // matches typical Exiv2 byte typedef usage in tests
size_t ul2Data(byte* buf, uint32_t l, Exiv2::ByteOrder byteOrder);
}  // namespace Exiv2

class Ul2DataTest_1146 : public ::testing::Test {
 protected:
  static std::array<Exiv2::byte, 4> Call(uint32_t value, Exiv2::ByteOrder order, size_t* outSize = nullptr) {
    std::array<Exiv2::byte, 4> buf{};
    const size_t n = Exiv2::ul2Data(buf.data(), value, order);
    if (outSize) *outSize = n;
    return buf;
  }

  static void ExpectBytes(const std::array<Exiv2::byte, 4>& got,
                          Exiv2::byte b0, Exiv2::byte b1, Exiv2::byte b2, Exiv2::byte b3) {
    EXPECT_EQ(got[0], b0);
    EXPECT_EQ(got[1], b1);
    EXPECT_EQ(got[2], b2);
    EXPECT_EQ(got[3], b3);
  }
};
}  // namespace

TEST_F(Ul2DataTest_1146, ReturnsFourBytes_1146) {
  size_t n = 0;
  (void)Call(0u, Exiv2::littleEndian, &n);
  EXPECT_EQ(n, 4u);

  (void)Call(0u, Exiv2::bigEndian, &n);
  EXPECT_EQ(n, 4u);
}

TEST_F(Ul2DataTest_1146, EncodesZeroLittleEndian_1146) {
  const auto buf = Call(0x00000000u, Exiv2::littleEndian);
  ExpectBytes(buf, 0x00, 0x00, 0x00, 0x00);
}

TEST_F(Ul2DataTest_1146, EncodesZeroBigEndian_1146) {
  const auto buf = Call(0x00000000u, Exiv2::bigEndian);
  ExpectBytes(buf, 0x00, 0x00, 0x00, 0x00);
}

TEST_F(Ul2DataTest_1146, EncodesMaxUint32LittleEndian_1146) {
  const auto buf = Call(0xFFFFFFFFu, Exiv2::littleEndian);
  ExpectBytes(buf, 0xFF, 0xFF, 0xFF, 0xFF);
}

TEST_F(Ul2DataTest_1146, EncodesMaxUint32BigEndian_1146) {
  const auto buf = Call(0xFFFFFFFFu, Exiv2::bigEndian);
  ExpectBytes(buf, 0xFF, 0xFF, 0xFF, 0xFF);
}

TEST_F(Ul2DataTest_1146, EncodesKnownPatternLittleEndian_1146) {
  // Boundary-ish: distinct bytes to validate ordering
  const auto buf = Call(0x01020304u, Exiv2::littleEndian);
  // least significant byte first
  ExpectBytes(buf, 0x04, 0x03, 0x02, 0x01);
}

TEST_F(Ul2DataTest_1146, EncodesKnownPatternBigEndian_1146) {
  const auto buf = Call(0x01020304u, Exiv2::bigEndian);
  // most significant byte first
  ExpectBytes(buf, 0x01, 0x02, 0x03, 0x04);
}

TEST_F(Ul2DataTest_1146, EncodesSingleBitBoundaries_1146) {
  // Validate extremes in each byte position without assuming internal details beyond output.
  {
    const auto buf = Call(0x00000001u, Exiv2::littleEndian);
    ExpectBytes(buf, 0x01, 0x00, 0x00, 0x00);
  }
  {
    const auto buf = Call(0x80000000u, Exiv2::littleEndian);
    ExpectBytes(buf, 0x00, 0x00, 0x00, 0x80);
  }
  {
    const auto buf = Call(0x00000001u, Exiv2::bigEndian);
    ExpectBytes(buf, 0x00, 0x00, 0x00, 0x01);
  }
  {
    const auto buf = Call(0x80000000u, Exiv2::bigEndian);
    ExpectBytes(buf, 0x80, 0x00, 0x00, 0x00);
  }
}

TEST_F(Ul2DataTest_1146, TreatsInvalidByteOrderAsNonLittle_1146) {
  // Observable behavior through interface: any non-littleEndian order should produce the "else" layout.
  // This verifies an error-ish case without relying on private state or throwing behavior.
  const auto bufInvalid = Call(0x01020304u, Exiv2::invalidByteOrder);
  const auto bufBig = Call(0x01020304u, Exiv2::bigEndian);
  EXPECT_EQ(bufInvalid, bufBig);
}

TEST_F(Ul2DataTest_1146, WritesExactlyFourBytesDoesNotClobberNeighbors_1146) {
  // Boundary / safety: ensure only 4 bytes are written (observable via surrounding sentinels).
  std::array<Exiv2::byte, 6> mem{};
  mem[0] = 0xAA;
  mem[5] = 0xBB;
  // Fill middle with a pattern to ensure changes are only in [1..4].
  mem[1] = 0x11;
  mem[2] = 0x22;
  mem[3] = 0x33;
  mem[4] = 0x44;

  const size_t n = Exiv2::ul2Data(&mem[1], 0x01020304u, Exiv2::bigEndian);
  EXPECT_EQ(n, 4u);

  EXPECT_EQ(mem[0], 0xAA);
  EXPECT_EQ(mem[5], 0xBB);

  // Confirm the intended 4 bytes changed to the expected output.
  EXPECT_EQ(mem[1], 0x01);
  EXPECT_EQ(mem[2], 0x02);
  EXPECT_EQ(mem[3], 0x03);
  EXPECT_EQ(mem[4], 0x04);
}