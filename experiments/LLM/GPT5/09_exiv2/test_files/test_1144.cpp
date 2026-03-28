// ============================================================================
// TestProjects/exiv2/tests/test_getdouble_1144.cpp
// Unit tests for Exiv2::getDouble (./TestProjects/exiv2/src/types.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <array>
#include <bit>
#include <cstdint>
#include <limits>

#include "exiv2/types.hpp"

namespace {

using Exiv2::bigEndian;
using Exiv2::ByteOrder;
using Exiv2::getDouble;
using Exiv2::littleEndian;

using byte = unsigned char;

// Convert a double to its IEEE-754 bit pattern (uint64_t) without depending on
// implementation details beyond standard facilities.
static uint64_t DoubleToBits(double d) {
#if defined(__cpp_lib_bit_cast) && (__cpp_lib_bit_cast >= 201806L)
  return std::bit_cast<uint64_t>(d);
#else
  uint64_t u = 0;
  static_assert(sizeof(u) == sizeof(d), "double must be 64-bit");
  std::memcpy(&u, &d, sizeof(u));
  return u;
#endif
}

// Convert a bit pattern (uint64_t) into a double.
static double BitsToDouble(uint64_t u) {
#if defined(__cpp_lib_bit_cast) && (__cpp_lib_bit_cast >= 201806L)
  return std::bit_cast<double>(u);
#else
  double d = 0.0;
  static_assert(sizeof(u) == sizeof(d), "double must be 64-bit");
  std::memcpy(&d, &u, sizeof(d));
  return d;
#endif
}

static std::array<byte, 8> BitsToBufLittle(uint64_t bits) {
  std::array<byte, 8> buf{};
  for (int i = 0; i < 8; ++i) {
    buf[static_cast<size_t>(i)] = static_cast<byte>((bits >> (8 * i)) & 0xFFu);
  }
  return buf;
}

static std::array<byte, 8> BitsToBufBig(uint64_t bits) {
  std::array<byte, 8> buf{};
  for (int i = 0; i < 8; ++i) {
    buf[static_cast<size_t>(i)] = static_cast<byte>((bits >> (8 * (7 - i))) & 0xFFu);
  }
  return buf;
}

static void ExpectSameBits(double expected, double actual) {
  // Compare bit patterns (handles -0.0, NaN payloads, infinities).
  EXPECT_EQ(DoubleToBits(expected), DoubleToBits(actual));
}

class GetDoubleTest_1144 : public ::testing::Test {};

}  // namespace

// --------------------------- Normal operation -------------------------------

TEST_F(GetDoubleTest_1144, ReadsKnownValueLittleEndian_1144) {
  const double expected = 1.0;
  const auto buf = BitsToBufLittle(DoubleToBits(expected));

  const double actual = getDouble(reinterpret_cast<const Exiv2::byte*>(buf.data()), littleEndian);

  ExpectSameBits(expected, actual);
}

TEST_F(GetDoubleTest_1144, ReadsKnownValueBigEndian_1144) {
  const double expected = 1.0;
  const auto buf = BitsToBufBig(DoubleToBits(expected));

  const double actual = getDouble(reinterpret_cast<const Exiv2::byte*>(buf.data()), bigEndian);

  ExpectSameBits(expected, actual);
}

TEST_F(GetDoubleTest_1144, ReadsNegativeValueLittleEndian_1144) {
  const double expected = -123.456;
  const auto buf = BitsToBufLittle(DoubleToBits(expected));

  const double actual = getDouble(reinterpret_cast<const Exiv2::byte*>(buf.data()), littleEndian);

  ExpectSameBits(expected, actual);
}

TEST_F(GetDoubleTest_1144, ReadsNegativeValueBigEndian_1144) {
  const double expected = -123.456;
  const auto buf = BitsToBufBig(DoubleToBits(expected));

  const double actual = getDouble(reinterpret_cast<const Exiv2::byte*>(buf.data()), bigEndian);

  ExpectSameBits(expected, actual);
}

// -------------------------- Boundary conditions -----------------------------

TEST_F(GetDoubleTest_1144, PreservesPositiveZero_1144) {
  const double expected = 0.0;
  const auto bufLE = BitsToBufLittle(DoubleToBits(expected));
  const auto bufBE = BitsToBufBig(DoubleToBits(expected));

  ExpectSameBits(expected, getDouble(reinterpret_cast<const Exiv2::byte*>(bufLE.data()), littleEndian));
  ExpectSameBits(expected, getDouble(reinterpret_cast<const Exiv2::byte*>(bufBE.data()), bigEndian));
}

TEST_F(GetDoubleTest_1144, PreservesNegativeZero_1144) {
  const double expected = -0.0;
  const auto bufLE = BitsToBufLittle(DoubleToBits(expected));
  const auto bufBE = BitsToBufBig(DoubleToBits(expected));

  ExpectSameBits(expected, getDouble(reinterpret_cast<const Exiv2::byte*>(bufLE.data()), littleEndian));
  ExpectSameBits(expected, getDouble(reinterpret_cast<const Exiv2::byte*>(bufBE.data()), bigEndian));
}

TEST_F(GetDoubleTest_1144, PreservesInfinityAndNegInfinity_1144) {
  const double posInf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();

  const auto posLE = BitsToBufLittle(DoubleToBits(posInf));
  const auto posBE = BitsToBufBig(DoubleToBits(posInf));
  const auto negLE = BitsToBufLittle(DoubleToBits(negInf));
  const auto negBE = BitsToBufBig(DoubleToBits(negInf));

  ExpectSameBits(posInf, getDouble(reinterpret_cast<const Exiv2::byte*>(posLE.data()), littleEndian));
  ExpectSameBits(posInf, getDouble(reinterpret_cast<const Exiv2::byte*>(posBE.data()), bigEndian));
  ExpectSameBits(negInf, getDouble(reinterpret_cast<const Exiv2::byte*>(negLE.data()), littleEndian));
  ExpectSameBits(negInf, getDouble(reinterpret_cast<const Exiv2::byte*>(negBE.data()), bigEndian));
}

TEST_F(GetDoubleTest_1144, PreservesQuietNaNBitPattern_1144) {
  // Use a fixed NaN payload to verify exact bit preservation.
  const uint64_t qnanBits = 0x7ff8000000001234ULL;  // quiet NaN with payload
  const double expected = BitsToDouble(qnanBits);

  const auto bufLE = BitsToBufLittle(qnanBits);
  const auto bufBE = BitsToBufBig(qnanBits);

  const double actualLE = getDouble(reinterpret_cast<const Exiv2::byte*>(bufLE.data()), littleEndian);
  const double actualBE = getDouble(reinterpret_cast<const Exiv2::byte*>(bufBE.data()), bigEndian);

  // For NaN, compare bits (not value).
  EXPECT_EQ(qnanBits, DoubleToBits(actualLE));
  EXPECT_EQ(qnanBits, DoubleToBits(actualBE));
}

TEST_F(GetDoubleTest_1144, ReadsDenormalMin_1144) {
  // Smallest positive subnormal
  const double expected = std::numeric_limits<double>::denorm_min();
  const uint64_t bits = DoubleToBits(expected);

  const auto bufLE = BitsToBufLittle(bits);
  const auto bufBE = BitsToBufBig(bits);

  ExpectSameBits(expected, getDouble(reinterpret_cast<const Exiv2::byte*>(bufLE.data()), littleEndian));
  ExpectSameBits(expected, getDouble(reinterpret_cast<const Exiv2::byte*>(bufBE.data()), bigEndian));
}

// -------------------- Error / exceptional (observable) ----------------------
//
// The interface does not specify behavior for invalid byte order and does not
// signal errors (no status/exception documented). We can still assert a basic,
// observable property: the function is pure in the sense that it returns a
// deterministic double for a given 8-byte input, and does not modify the input
// buffer (buffer is const). Those are exercised above.
//
// Here we include an "invalid byte order" smoke test that avoids assuming which
// branch is taken; it only checks the call is well-formed and returns some
// double value (including NaN is allowed).

TEST_F(GetDoubleTest_1144, InvalidByteOrderDoesNotCrash_1144) {
  const uint64_t bits = DoubleToBits(42.0);
  const auto buf = BitsToBufLittle(bits);

  const double actual = getDouble(reinterpret_cast<const Exiv2::byte*>(buf.data()),
                                  Exiv2::invalidByteOrder);

  // Only require that a double is returned; no further behavior is specified.
  (void)actual;
  SUCCEED();
}