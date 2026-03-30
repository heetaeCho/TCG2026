// =================================================================================================
// TEST_ID: 1151
// File: test_types_r2Data_1151.cpp
// Unit tests for Exiv2::r2Data (./TestProjects/exiv2/src/types.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/types.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

namespace {

class R2DataTest_1151 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeFilledBuffer(std::size_t n, Exiv2::byte fill) {
    return std::vector<Exiv2::byte>(n, fill);
  }

  static void ExpectSameBytes(const std::vector<Exiv2::byte>& a, const std::vector<Exiv2::byte>& b,
                              std::size_t n) {
    ASSERT_GE(a.size(), n);
    ASSERT_GE(b.size(), n);
    EXPECT_EQ(0, std::memcmp(a.data(), b.data(), n));
  }
};

TEST_F(R2DataTest_1151, WritesSameAsTwoL2Data_LittleEndian_1151) {
  const Exiv2::Rational r{123, 456};
  const Exiv2::ByteOrder order = Exiv2::littleEndian;

  auto actual = MakeFilledBuffer(32, static_cast<Exiv2::byte>(0xA5));
  auto expected = MakeFilledBuffer(32, static_cast<Exiv2::byte>(0xA5));

  const std::size_t a = Exiv2::r2Data(actual.data(), r, order);

  std::size_t o = 0;
  o += Exiv2::l2Data(expected.data() + o, r.first, order);
  o += Exiv2::l2Data(expected.data() + o, r.second, order);

  EXPECT_EQ(o, a);
  ExpectSameBytes(actual, expected, a);

  // Ensure bytes after the returned size are untouched.
  for (std::size_t i = a; i < actual.size(); ++i) {
    EXPECT_EQ(static_cast<Exiv2::byte>(0xA5), actual[i]);
  }
}

TEST_F(R2DataTest_1151, WritesSameAsTwoL2Data_BigEndian_1151) {
  const Exiv2::Rational r{-10, 42};
  const Exiv2::ByteOrder order = Exiv2::bigEndian;

  auto actual = MakeFilledBuffer(32, static_cast<Exiv2::byte>(0x5A));
  auto expected = MakeFilledBuffer(32, static_cast<Exiv2::byte>(0x5A));

  const std::size_t a = Exiv2::r2Data(actual.data(), r, order);

  std::size_t o = 0;
  o += Exiv2::l2Data(expected.data() + o, r.first, order);
  o += Exiv2::l2Data(expected.data() + o, r.second, order);

  EXPECT_EQ(o, a);
  ExpectSameBytes(actual, expected, a);

  for (std::size_t i = a; i < actual.size(); ++i) {
    EXPECT_EQ(static_cast<Exiv2::byte>(0x5A), actual[i]);
  }
}

TEST_F(R2DataTest_1151, BoundaryValues_MatchesTwoL2Data_1151) {
  const Exiv2::Rational r{std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()};

  for (auto order : {Exiv2::littleEndian, Exiv2::bigEndian}) {
    auto actual = MakeFilledBuffer(32, static_cast<Exiv2::byte>(0xCC));
    auto expected = MakeFilledBuffer(32, static_cast<Exiv2::byte>(0xCC));

    const std::size_t a = Exiv2::r2Data(actual.data(), r, order);

    std::size_t o = 0;
    o += Exiv2::l2Data(expected.data() + o, r.first, order);
    o += Exiv2::l2Data(expected.data() + o, r.second, order);

    EXPECT_EQ(o, a);
    ExpectSameBytes(actual, expected, a);

    for (std::size_t i = a; i < actual.size(); ++i) {
      EXPECT_EQ(static_cast<Exiv2::byte>(0xCC), actual[i]);
    }
  }
}

TEST_F(R2DataTest_1151, ReturnSizeEqualsSumOfComponentWrites_1151) {
  // Use a few representative rationals; validate size math via observable l2Data behavior.
  const Exiv2::Rational cases[] = {
      {0, 1},
      {1, 0},
      {-1, -1},
      {123456, -654321},
  };

  for (auto order : {Exiv2::littleEndian, Exiv2::bigEndian}) {
    for (const auto& r : cases) {
      auto buf = MakeFilledBuffer(32, static_cast<Exiv2::byte>(0x11));

      const std::size_t total = Exiv2::r2Data(buf.data(), r, order);

      // Compute expected size using only the public collaborator function.
      std::vector<Exiv2::byte> tmp(32, static_cast<Exiv2::byte>(0x22));
      std::size_t expectedSize = 0;
      expectedSize += Exiv2::l2Data(tmp.data() + expectedSize, r.first, order);
      expectedSize += Exiv2::l2Data(tmp.data() + expectedSize, r.second, order);

      EXPECT_EQ(expectedSize, total);
    }
  }
}

}  // namespace