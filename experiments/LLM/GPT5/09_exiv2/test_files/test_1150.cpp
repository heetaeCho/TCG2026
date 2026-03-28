// -------------------------------------------------------------------------------------------------
// TEST_ID: 1150
// Unit tests for Exiv2::l2Data (./TestProjects/exiv2/src/types.cpp)
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

#include "exiv2/types.hpp"

namespace {

// Local alias to match the implementation signature without depending on other Exiv2 headers.
using byte = unsigned char;

class L2DataTest_1150 : public ::testing::Test {
 protected:
  static void Fill(byte* buf, size_t n, byte v) {
    for (size_t i = 0; i < n; ++i) buf[i] = v;
  }
};

TEST_F(L2DataTest_1150, ReturnsFourBytes_1150) {
  byte buf[8];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  const size_t written = Exiv2::l2Data(buf, 0, Exiv2::littleEndian);

  EXPECT_EQ(written, 4u);
}

TEST_F(L2DataTest_1150, LittleEndianEncodesBytesInExpectedOrder_PositiveValue_1150) {
  byte buf[8];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  const int32_t v = 0x01020304;
  (void)Exiv2::l2Data(buf, v, Exiv2::littleEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0x04));
  EXPECT_EQ(buf[1], static_cast<byte>(0x03));
  EXPECT_EQ(buf[2], static_cast<byte>(0x02));
  EXPECT_EQ(buf[3], static_cast<byte>(0x01));

  // Ensure only first 4 bytes are written.
  EXPECT_EQ(buf[4], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[5], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[6], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[7], static_cast<byte>(0xAA));
}

TEST_F(L2DataTest_1150, BigEndianEncodesBytesInExpectedOrder_PositiveValue_1150) {
  byte buf[8];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  const int32_t v = 0x01020304;
  (void)Exiv2::l2Data(buf, v, Exiv2::bigEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0x01));
  EXPECT_EQ(buf[1], static_cast<byte>(0x02));
  EXPECT_EQ(buf[2], static_cast<byte>(0x03));
  EXPECT_EQ(buf[3], static_cast<byte>(0x04));

  // Ensure only first 4 bytes are written.
  EXPECT_EQ(buf[4], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[5], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[6], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[7], static_cast<byte>(0xAA));
}

TEST_F(L2DataTest_1150, LittleEndianZeroWritesAllZeroBytes_1150) {
  byte buf[4];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  (void)Exiv2::l2Data(buf, 0, Exiv2::littleEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0x00));
  EXPECT_EQ(buf[1], static_cast<byte>(0x00));
  EXPECT_EQ(buf[2], static_cast<byte>(0x00));
  EXPECT_EQ(buf[3], static_cast<byte>(0x00));
}

TEST_F(L2DataTest_1150, BigEndianZeroWritesAllZeroBytes_1150) {
  byte buf[4];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  (void)Exiv2::l2Data(buf, 0, Exiv2::bigEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0x00));
  EXPECT_EQ(buf[1], static_cast<byte>(0x00));
  EXPECT_EQ(buf[2], static_cast<byte>(0x00));
  EXPECT_EQ(buf[3], static_cast<byte>(0x00));
}

TEST_F(L2DataTest_1150, LittleEndianMinInt32_1150) {
  byte buf[4];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  const int32_t v = static_cast<int32_t>(0x80000000u);
  (void)Exiv2::l2Data(buf, v, Exiv2::littleEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0x00));
  EXPECT_EQ(buf[1], static_cast<byte>(0x00));
  EXPECT_EQ(buf[2], static_cast<byte>(0x00));
  EXPECT_EQ(buf[3], static_cast<byte>(0x80));
}

TEST_F(L2DataTest_1150, BigEndianMinInt32_1150) {
  byte buf[4];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  const int32_t v = static_cast<int32_t>(0x80000000u);
  (void)Exiv2::l2Data(buf, v, Exiv2::bigEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0x80));
  EXPECT_EQ(buf[1], static_cast<byte>(0x00));
  EXPECT_EQ(buf[2], static_cast<byte>(0x00));
  EXPECT_EQ(buf[3], static_cast<byte>(0x00));
}

TEST_F(L2DataTest_1150, LittleEndianMinusOneWritesAllFF_1150) {
  byte buf[4];
  Fill(buf, sizeof(buf), static_cast<byte>(0x00));

  (void)Exiv2::l2Data(buf, -1, Exiv2::littleEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0xFF));
  EXPECT_EQ(buf[1], static_cast<byte>(0xFF));
  EXPECT_EQ(buf[2], static_cast<byte>(0xFF));
  EXPECT_EQ(buf[3], static_cast<byte>(0xFF));
}

TEST_F(L2DataTest_1150, BigEndianMinusOneWritesAllFF_1150) {
  byte buf[4];
  Fill(buf, sizeof(buf), static_cast<byte>(0x00));

  (void)Exiv2::l2Data(buf, -1, Exiv2::bigEndian);

  EXPECT_EQ(buf[0], static_cast<byte>(0xFF));
  EXPECT_EQ(buf[1], static_cast<byte>(0xFF));
  EXPECT_EQ(buf[2], static_cast<byte>(0xFF));
  EXPECT_EQ(buf[3], static_cast<byte>(0xFF));
}

TEST_F(L2DataTest_1150, NonLittleEndianBehavesAsBigEndian_InvalidByteOrder_1150) {
  byte buf[8];
  Fill(buf, sizeof(buf), static_cast<byte>(0xAA));

  const int32_t v = 0x01020304;
  (void)Exiv2::l2Data(buf, v, Exiv2::invalidByteOrder);

  // Observable behavior from the interface: anything other than littleEndian follows the else-branch.
  EXPECT_EQ(buf[0], static_cast<byte>(0x01));
  EXPECT_EQ(buf[1], static_cast<byte>(0x02));
  EXPECT_EQ(buf[2], static_cast<byte>(0x03));
  EXPECT_EQ(buf[3], static_cast<byte>(0x04));

  // Ensure only first 4 bytes are written.
  EXPECT_EQ(buf[4], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[5], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[6], static_cast<byte>(0xAA));
  EXPECT_EQ(buf[7], static_cast<byte>(0xAA));
}

}  // namespace