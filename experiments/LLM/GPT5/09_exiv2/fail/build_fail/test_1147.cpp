// File: test_types_ull2Data_1147.cpp
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

#include "exiv2/types.hpp"

namespace {

// Forward declaration of function under test (implemented in Exiv2 library/object files).
namespace Exiv2 {
using byte = unsigned char; // aligns with Exiv2's typical byte typedef in types.hpp
size_t ull2Data(byte* buf, uint64_t l, Exiv2::ByteOrder byteOrder);
}  // namespace Exiv2

class Ull2DataTest_1147 : public ::testing::Test {
 protected:
  static std::array<Exiv2::byte, 8> AllBytes(Exiv2::byte v) {
    std::array<Exiv2::byte, 8> a{};
    a.fill(v);
    return a;
  }
};

TEST_F(Ull2DataTest_1147, ReturnsEightForLittleEndian_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0xAA);
  const size_t written = Exiv2::ull2Data(buf.data(), 0ULL, Exiv2::littleEndian);
  EXPECT_EQ(8u, written);
}

TEST_F(Ull2DataTest_1147, ReturnsEightForBigEndian_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0xAA);
  const size_t written = Exiv2::ull2Data(buf.data(), 0ULL, Exiv2::bigEndian);
  EXPECT_EQ(8u, written);
}

TEST_F(Ull2DataTest_1147, LittleEndianWritesZeroValueAsAllZeros_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0xAA);

  Exiv2::ull2Data(buf.data(), 0ULL, Exiv2::littleEndian);

  const std::array<Exiv2::byte, 8> expected = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  EXPECT_EQ(expected, buf);
}

TEST_F(Ull2DataTest_1147, BigEndianWritesZeroValueAsAllZeros_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0xAA);

  Exiv2::ull2Data(buf.data(), 0ULL, Exiv2::bigEndian);

  const std::array<Exiv2::byte, 8> expected = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  EXPECT_EQ(expected, buf);
}

TEST_F(Ull2DataTest_1147, LittleEndianWritesMaxValueAllFF_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0x00);

  Exiv2::ull2Data(buf.data(), UINT64_MAX, Exiv2::littleEndian);

  const std::array<Exiv2::byte, 8> expected = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  EXPECT_EQ(expected, buf);
}

TEST_F(Ull2DataTest_1147, BigEndianWritesMaxValueAllFF_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0x00);

  Exiv2::ull2Data(buf.data(), UINT64_MAX, Exiv2::bigEndian);

  const std::array<Exiv2::byte, 8> expected = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  EXPECT_EQ(expected, buf);
}

TEST_F(Ull2DataTest_1147, LittleEndianWritesKnownPattern_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0x00);
  const uint64_t value = 0x0123456789ABCDEFULL;

  Exiv2::ull2Data(buf.data(), value, Exiv2::littleEndian);

  // Little-endian: least significant byte first.
  const std::array<Exiv2::byte, 8> expected = {0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01};
  EXPECT_EQ(expected, buf);
}

TEST_F(Ull2DataTest_1147, BigEndianWritesKnownPattern_1147) {
  auto buf = Ull2DataTest_1147::AllBytes(0x00);
  const uint64_t value = 0x0123456789ABCDEFULL;

  Exiv2::ull2Data(buf.data(), value, Exiv2::bigEndian);

  // Big-endian: most significant byte first.
  const std::array<Exiv2::byte, 8> expected = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  EXPECT_EQ(expected, buf);
}

TEST_F(Ull2DataTest_1147, LittleEndianOnlyTouchesFirstEightBytes_1147) {
  // Boundary: ensure exactly 8 bytes are written and nothing beyond.
  std::array<Exiv2::byte, 9> buf{};
  buf.fill(0xAA);
  const uint64_t value = 0x1122334455667788ULL;

  Exiv2::ull2Data(buf.data(), value, Exiv2::littleEndian);

  const std::array<Exiv2::byte, 8> expected_first8 = {0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};
  for (size_t i = 0; i < 8; ++i) {
    EXPECT_EQ(expected_first8[i], buf[i]) << "byte index " << i;
  }
  EXPECT_EQ(0xAA, buf[8]) << "Sentinel byte should remain unchanged";
}

TEST_F(Ull2DataTest_1147, BigEndianOnlyTouchesFirstEightBytes_1147) {
  // Boundary: ensure exactly 8 bytes are written and nothing beyond.
  std::array<Exiv2::byte, 9> buf{};
  buf.fill(0xAA);
  const uint64_t value = 0x1122334455667788ULL;

  Exiv2::ull2Data(buf.data(), value, Exiv2::bigEndian);

  const std::array<Exiv2::byte, 8> expected_first8 = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
  for (size_t i = 0; i < 8; ++i) {
    EXPECT_EQ(expected_first8[i], buf[i]) << "byte index " << i;
  }
  EXPECT_EQ(0xAA, buf[8]) << "Sentinel byte should remain unchanged";
}

TEST_F(Ull2DataTest_1147, InvalidByteOrderBehavesLikeBigEndian_1147) {
  // Exceptional/edge: interface allows invalidByteOrder. Observable behavior: it should still write 8 bytes.
  // We only assert stable, observable output for the current implementation: non-littleEndian path.
  auto buf = Ull2DataTest_1147::AllBytes(0x00);
  const uint64_t value = 0x0123456789ABCDEFULL;

  const size_t written = Exiv2::ull2Data(buf.data(), value, Exiv2::invalidByteOrder);
  EXPECT_EQ(8u, written);

  const std::array<Exiv2::byte, 8> expected = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  EXPECT_EQ(expected, buf);
}

}  // namespace