// =================================================================================================
// TEST_ID: 1152
// File: test_types_f2Data_1152.cpp
//
// Unit tests for Exiv2::f2Data (from ./TestProjects/exiv2/src/types.cpp)
//
// Constraints respected:
// - Treat implementation as black box (no internal logic re-implementation).
// - Use only observable behavior through public interface.
// - Boundary + error-ish cases (as observable) included.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

#include "exiv2/types.hpp"  // Expected to provide: Exiv2::byte, Exiv2::ByteOrder, Exiv2::f2Data

namespace {

// Helper: check host endianness for memcpy-based expectations.
inline bool hostIsLittleEndian() {
  const uint16_t x = 0x0102;
  const unsigned char* p = reinterpret_cast<const unsigned char*>(&x);
  return p[1] == 0x01;  // memory: 02 01 => little
}

// Helper: write uint32_t to buffer as little/big endian.
inline void writeU32LE(Exiv2::byte* buf, uint32_t v) {
  buf[0] = static_cast<Exiv2::byte>(v & 0xFFu);
  buf[1] = static_cast<Exiv2::byte>((v >> 8) & 0xFFu);
  buf[2] = static_cast<Exiv2::byte>((v >> 16) & 0xFFu);
  buf[3] = static_cast<Exiv2::byte>((v >> 24) & 0xFFu);
}
inline void writeU32BE(Exiv2::byte* buf, uint32_t v) {
  buf[0] = static_cast<Exiv2::byte>((v >> 24) & 0xFFu);
  buf[1] = static_cast<Exiv2::byte>((v >> 16) & 0xFFu);
  buf[2] = static_cast<Exiv2::byte>((v >> 8) & 0xFFu);
  buf[3] = static_cast<Exiv2::byte>(v & 0xFFu);
}

// Helper: bit-pattern of float without assuming std::bit_cast availability.
inline uint32_t floatBits(float f) {
  static_assert(sizeof(float) == sizeof(uint32_t), "Unexpected float size");
  uint32_t u = 0;
  std::memcpy(&u, &f, sizeof(u));
  return u;
}

class F2DataTest_1152 : public ::testing::Test {
 protected:
  Exiv2::byte buf_[8]{};
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation: returns size written
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, ReturnsFourBytesWritten_1152) {
  std::memset(buf_, 0xAA, sizeof(buf_));
  const size_t n = Exiv2::f2Data(buf_, 1.0f, Exiv2::littleEndian);
  EXPECT_EQ(4u, n);
}

// -------------------------------------------------------------------------------------------------
// Normal operation: little endian encodes the float bit pattern in LE order.
// We compute expected bytes from the float bit representation (observable, not internal logic).
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, WritesLittleEndianBytesForKnownValue_1152) {
  std::memset(buf_, 0x00, sizeof(buf_));
  const float v = 1.0f;  // IEEE-754: 0x3F800000 on typical platforms
  const uint32_t bits = floatBits(v);

  Exiv2::byte expected[4]{};
  writeU32LE(expected, bits);

  const size_t n = Exiv2::f2Data(buf_, v, Exiv2::littleEndian);
  ASSERT_EQ(4u, n);
  EXPECT_EQ(0, std::memcmp(buf_, expected, 4));
}

// -------------------------------------------------------------------------------------------------
// Normal operation: big endian encodes the float bit pattern in BE order.
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, WritesBigEndianBytesForKnownValue_1152) {
  std::memset(buf_, 0x00, sizeof(buf_));
  const float v = 1.0f;
  const uint32_t bits = floatBits(v);

  Exiv2::byte expected[4]{};
  writeU32BE(expected, bits);

  const size_t n = Exiv2::f2Data(buf_, v, Exiv2::bigEndian);
  ASSERT_EQ(4u, n);
  EXPECT_EQ(0, std::memcmp(buf_, expected, 4));
}

// -------------------------------------------------------------------------------------------------
// Boundary-ish: +0.0 and -0.0 have different bit patterns; verify f2Data preserves the sign bit.
// (Observable: produced bytes differ appropriately from the float's raw bits.)
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, PreservesNegativeZeroBitPattern_1152) {
  std::memset(buf_, 0x00, sizeof(buf_));

  const float pz = 0.0f;
  const float nz = -0.0f;

  const uint32_t pzBits = floatBits(pz);
  const uint32_t nzBits = floatBits(nz);

  // If platform doesn't distinguish, this test still remains valid by checking equality to bits.
  Exiv2::byte expectedPz[4]{};
  Exiv2::byte expectedNz[4]{};
  writeU32LE(expectedPz, pzBits);
  writeU32LE(expectedNz, nzBits);

  Exiv2::byte outPz[4]{};
  Exiv2::byte outNz[4]{};

  ASSERT_EQ(4u, Exiv2::f2Data(outPz, pz, Exiv2::littleEndian));
  ASSERT_EQ(4u, Exiv2::f2Data(outNz, nz, Exiv2::littleEndian));

  EXPECT_EQ(0, std::memcmp(outPz, expectedPz, 4));
  EXPECT_EQ(0, std::memcmp(outNz, expectedNz, 4));

  if (pzBits != nzBits) {
    EXPECT_NE(0, std::memcmp(outPz, outNz, 4));
  }
}

// -------------------------------------------------------------------------------------------------
// Exceptional/error-ish: NaN and Infinity are special IEEE values.
// We don't assume any canonical NaN payload; we verify the exact bit pattern is preserved.
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, WritesInfinityBitPattern_1152) {
  std::memset(buf_, 0xCC, sizeof(buf_));

  const float inf = std::numeric_limits<float>::infinity();
  const uint32_t bits = floatBits(inf);

  Exiv2::byte expected[4]{};
  writeU32BE(expected, bits);

  const size_t n = Exiv2::f2Data(buf_, inf, Exiv2::bigEndian);
  ASSERT_EQ(4u, n);
  EXPECT_EQ(0, std::memcmp(buf_, expected, 4));
}

TEST_F(F2DataTest_1152, WritesNaNBitPattern_1152) {
  std::memset(buf_, 0xCC, sizeof(buf_));

  const float nan = std::numeric_limits<float>::quiet_NaN();
  const uint32_t bits = floatBits(nan);

  Exiv2::byte expected[4]{};
  writeU32LE(expected, bits);

  const size_t n = Exiv2::f2Data(buf_, nan, Exiv2::littleEndian);
  ASSERT_EQ(4u, n);
  EXPECT_EQ(0, std::memcmp(buf_, expected, 4));
}

// -------------------------------------------------------------------------------------------------
// Boundary: ensure only first 4 bytes are written (no overwrite beyond).
// This is observable by sentinel bytes after the first 4.
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, DoesNotOverwriteBeyondFourBytes_1152) {
  std::memset(buf_, 0xAB, sizeof(buf_));
  const Exiv2::byte sentinel4 = buf_[4];
  const Exiv2::byte sentinel5 = buf_[5];
  const Exiv2::byte sentinel6 = buf_[6];
  const Exiv2::byte sentinel7 = buf_[7];

  ASSERT_EQ(4u, Exiv2::f2Data(buf_, 3.1415926f, Exiv2::littleEndian));

  EXPECT_EQ(sentinel4, buf_[4]);
  EXPECT_EQ(sentinel5, buf_[5]);
  EXPECT_EQ(sentinel6, buf_[6]);
  EXPECT_EQ(sentinel7, buf_[7]);
}

// -------------------------------------------------------------------------------------------------
// Consistency: big endian output should be byte-reversal of little endian output for same float,
// independent of host endianness (observable relation between outputs).
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, BigEndianIsReverseOfLittleEndianForSameValue_1152) {
  Exiv2::byte le[4]{};
  Exiv2::byte be[4]{};

  const float v = -12.5f;
  ASSERT_EQ(4u, Exiv2::f2Data(le, v, Exiv2::littleEndian));
  ASSERT_EQ(4u, Exiv2::f2Data(be, v, Exiv2::bigEndian));

  EXPECT_EQ(le[0], be[3]);
  EXPECT_EQ(le[1], be[2]);
  EXPECT_EQ(le[2], be[1]);
  EXPECT_EQ(le[3], be[0]);
}

// -------------------------------------------------------------------------------------------------
// Host sanity check: on any host, f2Data in "native" order (if exposed as such) is not assumed.
// Instead, we verify that one of the explicit orders matches host float byte layout.
// This test is resilient and does not require knowing Exiv2 internals beyond f2Data behavior.
// -------------------------------------------------------------------------------------------------
TEST_F(F2DataTest_1152, OneEndianMatchesHostMemcpyLayout_1152) {
  const float v = 0.25f;
  const uint32_t bits = floatBits(v);

  unsigned char hostBytes[4]{};
  std::memcpy(hostBytes, &bits, 4);  // bytes of the uint32_t value in host endianness

  Exiv2::byte outLE[4]{};
  Exiv2::byte outBE[4]{};
  ASSERT_EQ(4u, Exiv2::f2Data(outLE, v, Exiv2::littleEndian));
  ASSERT_EQ(4u, Exiv2::f2Data(outBE, v, Exiv2::bigEndian));

  const bool hostLE = hostIsLittleEndian();
  if (hostLE) {
    EXPECT_EQ(0, std::memcmp(outLE, hostBytes, 4));
  } else {
    EXPECT_EQ(0, std::memcmp(outBE, hostBytes, 4));
  }
}