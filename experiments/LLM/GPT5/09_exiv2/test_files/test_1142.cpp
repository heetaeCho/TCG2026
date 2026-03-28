// =================================================================================================
// TEST_ID: 1142
// File: ./TestProjects/exiv2/src/types.cpp (unit tests)
//
// Covered interface:
//   Exiv2::Rational getRational(const Exiv2::byte* buf, Exiv2::ByteOrder byteOrder)
//
// Notes (black-box):
// - We only validate observable output (returned Rational fields) for known input buffers.
// - We exercise both byte orders and boundary-ish integer values.
// - We include a death test for nullptr (exceptional/error case) since behavior is otherwise not
//   observable via the interface. If your build disables death tests, you can drop that test.
// =================================================================================================

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <limits>

// Exiv2 headers (adjust include paths to your project layout if needed)
#include "exiv2/types.hpp"

namespace {

// Helpers to build 8-byte buffers representing two 32-bit signed integers.
std::array<Exiv2::byte, 8> MakeBufBE(int32_t nominator, int32_t denominator) {
  std::array<Exiv2::byte, 8> b{};
  const uint32_t n = static_cast<uint32_t>(nominator);
  const uint32_t d = static_cast<uint32_t>(denominator);

  b[0] = static_cast<Exiv2::byte>((n >> 24) & 0xFF);
  b[1] = static_cast<Exiv2::byte>((n >> 16) & 0xFF);
  b[2] = static_cast<Exiv2::byte>((n >> 8) & 0xFF);
  b[3] = static_cast<Exiv2::byte>((n >> 0) & 0xFF);

  b[4] = static_cast<Exiv2::byte>((d >> 24) & 0xFF);
  b[5] = static_cast<Exiv2::byte>((d >> 16) & 0xFF);
  b[6] = static_cast<Exiv2::byte>((d >> 8) & 0xFF);
  b[7] = static_cast<Exiv2::byte>((d >> 0) & 0xFF);

  return b;
}

std::array<Exiv2::byte, 8> MakeBufLE(int32_t nominator, int32_t denominator) {
  std::array<Exiv2::byte, 8> b{};
  const uint32_t n = static_cast<uint32_t>(nominator);
  const uint32_t d = static_cast<uint32_t>(denominator);

  b[0] = static_cast<Exiv2::byte>((n >> 0) & 0xFF);
  b[1] = static_cast<Exiv2::byte>((n >> 8) & 0xFF);
  b[2] = static_cast<Exiv2::byte>((n >> 16) & 0xFF);
  b[3] = static_cast<Exiv2::byte>((n >> 24) & 0xFF);

  b[4] = static_cast<Exiv2::byte>((d >> 0) & 0xFF);
  b[5] = static_cast<Exiv2::byte>((d >> 8) & 0xFF);
  b[6] = static_cast<Exiv2::byte>((d >> 16) & 0xFF);
  b[7] = static_cast<Exiv2::byte>((d >> 24) & 0xFF);

  return b;
}

class GetRationalTest_1142 : public ::testing::Test {};

}  // namespace

// ----------------------- Normal operation -----------------------

TEST_F(GetRationalTest_1142, ReadsBigEndianValues_1142) {
  const int32_t n = 1;
  const int32_t d = 2;
  const auto buf = MakeBufBE(n, d);

  const Exiv2::Rational r = Exiv2::getRational(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(r.first, n);
  EXPECT_EQ(r.second, d);
}

TEST_F(GetRationalTest_1142, ReadsLittleEndianValues_1142) {
  const int32_t n = 123456789;
  const int32_t d = -987654321;
  const auto buf = MakeBufLE(n, d);

  const Exiv2::Rational r = Exiv2::getRational(buf.data(), Exiv2::littleEndian);

  EXPECT_EQ(r.first, n);
  EXPECT_EQ(r.second, d);
}

// ----------------------- Boundary conditions -----------------------

TEST_F(GetRationalTest_1142, HandlesInt32MinAndMax_BigEndian_1142) {
  const int32_t n = std::numeric_limits<int32_t>::min();
  const int32_t d = std::numeric_limits<int32_t>::max();
  const auto buf = MakeBufBE(n, d);

  const Exiv2::Rational r = Exiv2::getRational(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(r.first, n);
  EXPECT_EQ(r.second, d);
}

TEST_F(GetRationalTest_1142, HandlesZerosAndNegatives_LittleEndian_1142) {
  const int32_t n = 0;
  const int32_t d = -1;
  const auto buf = MakeBufLE(n, d);

  const Exiv2::Rational r = Exiv2::getRational(buf.data(), Exiv2::littleEndian);

  EXPECT_EQ(r.first, n);
  EXPECT_EQ(r.second, d);
}

TEST_F(GetRationalTest_1142, DenominatorCanBeZero_1142) {
  // Division isn't performed here; we only verify the returned pair contains 0 as provided.
  const int32_t n = 42;
  const int32_t d = 0;
  const auto buf = MakeBufBE(n, d);

  const Exiv2::Rational r = Exiv2::getRational(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(r.first, n);
  EXPECT_EQ(r.second, d);
}

// ----------------------- Exceptional / error cases (observable) -----------------------

TEST_F(GetRationalTest_1142, NullptrBuffer_Death_1142) {
#if GTEST_HAS_DEATH_TEST
  // Behavior for nullptr is not specified by the interface; in practice this should crash due
  // to dereferencing in getLong/getRational. We assert death to cover this edge case.
  EXPECT_DEATH(
      {
        (void)Exiv2::getRational(nullptr, Exiv2::bigEndian);
      },
      "");
#else
  GTEST_SKIP() << "Death tests are not supported in this build configuration.";
#endif
}