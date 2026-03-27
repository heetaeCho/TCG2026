// File: test_types_d2data_1153.cpp
#include <gtest/gtest.h>

#include <array>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <limits>

#include "exiv2/types.hpp"

// Forward declaration (implemented in the real codebase).
namespace Exiv2 {
size_t d2Data(byte* buf, double d, ByteOrder byteOrder);
}  // namespace Exiv2

namespace {

class D2DataTest_1153 : public ::testing::Test {
 protected:
  static std::array<Exiv2::byte, 8> ExpectedBytes(double d, Exiv2::ByteOrder order) {
    uint64_t bits = 0;
    static_assert(sizeof(double) == sizeof(uint64_t), "Unexpected double size");
    std::memcpy(&bits, &d, sizeof(bits));

    std::array<Exiv2::byte, 8> out{};
    if (order == Exiv2::littleEndian) {
      for (int i = 0; i < 8; ++i) {
        out[static_cast<size_t>(i)] = static_cast<Exiv2::byte>((bits >> (8 * i)) & 0xFFu);
      }
    } else {
      for (int i = 0; i < 8; ++i) {
        out[static_cast<size_t>(i)] = static_cast<Exiv2::byte>((bits >> (8 * (7 - i))) & 0xFFu);
      }
    }
    return out;
  }
};

TEST_F(D2DataTest_1153, ReturnsEightAndEncodesLittleEndian_1153) {
  std::array<Exiv2::byte, 8> buf;
  buf.fill(static_cast<Exiv2::byte>(0xAA));

  const double v = 1234.5;
  const auto expected = ExpectedBytes(v, Exiv2::littleEndian);

  ASSERT_EQ(8u, Exiv2::d2Data(buf.data(), v, Exiv2::littleEndian));
  EXPECT_TRUE(std::equal(buf.begin(), buf.end(), expected.begin()));
}

TEST_F(D2DataTest_1153, ReturnsEightAndEncodesBigEndian_1153) {
  std::array<Exiv2::byte, 8> buf;
  buf.fill(static_cast<Exiv2::byte>(0xAA));

  const double v = -42.25;
  const auto expected = ExpectedBytes(v, Exiv2::bigEndian);

  ASSERT_EQ(8u, Exiv2::d2Data(buf.data(), v, Exiv2::bigEndian));
  EXPECT_TRUE(std::equal(buf.begin(), buf.end(), expected.begin()));
}

TEST_F(D2DataTest_1153, LittleAndBigEndianOutputsAreByteReverses_1153) {
  std::array<Exiv2::byte, 8> le{};
  std::array<Exiv2::byte, 8> be{};

  const double v = 0.125;  // simple, exactly representable

  ASSERT_EQ(8u, Exiv2::d2Data(le.data(), v, Exiv2::littleEndian));
  ASSERT_EQ(8u, Exiv2::d2Data(be.data(), v, Exiv2::bigEndian));

  std::array<Exiv2::byte, 8> rev = le;
  std::reverse(rev.begin(), rev.end());
  EXPECT_TRUE(std::equal(rev.begin(), rev.end(), be.begin()));
}

TEST_F(D2DataTest_1153, PreservesNegativeZeroBitPattern_1153) {
  std::array<Exiv2::byte, 8> bufLe{};
  std::array<Exiv2::byte, 8> bufBe{};

  const double negZero = -0.0;

  const auto expectedLe = ExpectedBytes(negZero, Exiv2::littleEndian);
  const auto expectedBe = ExpectedBytes(negZero, Exiv2::bigEndian);

  ASSERT_EQ(8u, Exiv2::d2Data(bufLe.data(), negZero, Exiv2::littleEndian));
  ASSERT_EQ(8u, Exiv2::d2Data(bufBe.data(), negZero, Exiv2::bigEndian));

  EXPECT_TRUE(std::equal(bufLe.begin(), bufLe.end(), expectedLe.begin()));
  EXPECT_TRUE(std::equal(bufBe.begin(), bufBe.end(), expectedBe.begin()));
}

TEST_F(D2DataTest_1153, EncodesInfinityAndNaNDeterministicallyForGivenValue_1153) {
  std::array<Exiv2::byte, 8> infBuf{};
  std::array<Exiv2::byte, 8> nanBuf{};

  const double inf = std::numeric_limits<double>::infinity();
  const double nan = std::numeric_limits<double>::quiet_NaN();

  const auto expectedInf = ExpectedBytes(inf, Exiv2::bigEndian);
  const auto expectedNan = ExpectedBytes(nan, Exiv2::bigEndian);

  ASSERT_EQ(8u, Exiv2::d2Data(infBuf.data(), inf, Exiv2::bigEndian));
  ASSERT_EQ(8u, Exiv2::d2Data(nanBuf.data(), nan, Exiv2::bigEndian));

  EXPECT_TRUE(std::equal(infBuf.begin(), infBuf.end(), expectedInf.begin()));
  EXPECT_TRUE(std::equal(nanBuf.begin(), nanBuf.end(), expectedNan.begin()));
}

TEST_F(D2DataTest_1153, InvalidByteOrderBehavesSameAsBigEndianForSameInput_1153) {
  std::array<Exiv2::byte, 8> invalidBuf{};
  std::array<Exiv2::byte, 8> bigBuf{};

  const double v = 3.141592653589793;

  ASSERT_EQ(8u, Exiv2::d2Data(invalidBuf.data(), v, Exiv2::invalidByteOrder));
  ASSERT_EQ(8u, Exiv2::d2Data(bigBuf.data(), v, Exiv2::bigEndian));

  EXPECT_TRUE(std::equal(invalidBuf.begin(), invalidBuf.end(), bigBuf.begin()));
}

}  // namespace