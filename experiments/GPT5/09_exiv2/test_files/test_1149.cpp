// ============================================================================
// TEST_ID: 1149
// File: test_types_s2Data_1149.cpp
// Unit tests for Exiv2::s2Data (types.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

#include "exiv2/types.hpp"

// Forward declaration (function is defined in Exiv2 library; treat as black box)
namespace Exiv2 {
using byte = unsigned char;
size_t s2Data(byte* buf, int16_t s, ByteOrder byteOrder);
}  // namespace Exiv2

namespace {

class S2DataTest_1149 : public ::testing::Test {};

TEST_F(S2DataTest_1149, ReturnsTwoBytes_1149) {
  Exiv2::byte buf[2] = {0, 0};
  const size_t written = Exiv2::s2Data(buf, static_cast<int16_t>(0x1234), Exiv2::littleEndian);
  EXPECT_EQ(written, 2u);
}

TEST_F(S2DataTest_1149, LittleEndianWritesLowThenHigh_1149) {
  Exiv2::byte buf[2] = {0xAA, 0xBB};
  Exiv2::s2Data(buf, static_cast<int16_t>(0x1234), Exiv2::littleEndian);

  EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x34));
  EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x12));
}

TEST_F(S2DataTest_1149, BigEndianWritesHighThenLow_1149) {
  Exiv2::byte buf[2] = {0xAA, 0xBB};
  Exiv2::s2Data(buf, static_cast<int16_t>(0x1234), Exiv2::bigEndian);

  EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x12));
  EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x34));
}

TEST_F(S2DataTest_1149, ZeroValueSerializesToTwoZeroBytesBothOrders_1149) {
  {
    Exiv2::byte buf[2] = {0xFF, 0xFF};
    Exiv2::s2Data(buf, static_cast<int16_t>(0), Exiv2::littleEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x00));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x00));
  }
  {
    Exiv2::byte buf[2] = {0xFF, 0xFF};
    Exiv2::s2Data(buf, static_cast<int16_t>(0), Exiv2::bigEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x00));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x00));
  }
}

TEST_F(S2DataTest_1149, BoundaryMinInt16SerializesCorrectly_1149) {
  const int16_t v = std::numeric_limits<int16_t>::min();  // -32768 -> 0x8000

  {
    Exiv2::byte buf[2] = {0, 0};
    Exiv2::s2Data(buf, v, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x00));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x80));
  }
  {
    Exiv2::byte buf[2] = {0, 0};
    Exiv2::s2Data(buf, v, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x80));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x00));
  }
}

TEST_F(S2DataTest_1149, BoundaryMaxInt16SerializesCorrectly_1149) {
  const int16_t v = std::numeric_limits<int16_t>::max();  // 32767 -> 0x7FFF

  {
    Exiv2::byte buf[2] = {0, 0};
    Exiv2::s2Data(buf, v, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0xFF));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x7F));
  }
  {
    Exiv2::byte buf[2] = {0, 0};
    Exiv2::s2Data(buf, v, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x7F));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0xFF));
  }
}

TEST_F(S2DataTest_1149, NegativeOneSerializesToFFFFInBothOrders_1149) {
  const int16_t v = static_cast<int16_t>(-1);

  {
    Exiv2::byte buf[2] = {0, 0};
    Exiv2::s2Data(buf, v, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0xFF));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0xFF));
  }
  {
    Exiv2::byte buf[2] = {0, 0};
    Exiv2::s2Data(buf, v, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0xFF));
    EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0xFF));
  }
}

// "Exceptional or error cases (if observable)":
// From the provided interface, error reporting isn't exposed.
// Still, we can verify that non-littleEndian values follow the "else" branch behavior
// by checking observable output for invalidByteOrder.
TEST_F(S2DataTest_1149, InvalidByteOrderBehavesAsNonLittleEndian_1149) {
  Exiv2::byte buf[2] = {0xAA, 0xBB};
  Exiv2::s2Data(buf, static_cast<int16_t>(0x1234), Exiv2::invalidByteOrder);

  // Observable expectation based on interface usage: not littleEndian => big-endian style output.
  EXPECT_EQ(buf[0], static_cast<Exiv2::byte>(0x12));
  EXPECT_EQ(buf[1], static_cast<Exiv2::byte>(0x34));
}

}  // namespace