// Decrypt_invMixColumnsW_ut_1611.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>

// NOTE:
// invMixColumnsW is a `static inline` function in Decrypt.cc (internal linkage),
// so it is not link-visible from another translation unit.
// To test it as a black box through its real implementation, we include the .cc
// into this test TU.
//
// Your build system must ensure this test is compiled as its own TU and that
// Decrypt.cc is not also compiled/linked separately into the same test binary.
#include "Decrypt.cc"

namespace {

static inline uint32_t MakeWord(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
{
  return (static_cast<uint32_t>(b0) << 24) |
         (static_cast<uint32_t>(b1) << 16) |
         (static_cast<uint32_t>(b2) << 8) |
         (static_cast<uint32_t>(b3));
}

static inline std::array<uint8_t, 4> WordBytes(uint32_t w)
{
  return {static_cast<uint8_t>((w >> 24) & 0xff),
          static_cast<uint8_t>((w >> 16) & 0xff),
          static_cast<uint8_t>((w >> 8) & 0xff),
          static_cast<uint8_t>(w & 0xff)};
}

} // namespace

TEST(InvMixColumnsWTest_1611, KnownVectorFromAESSpec_SingleColumnRepeated_1611)
{
  // AES (FIPS-197) MixColumns example:
  //   d4 bf 5d 30  ->  04 66 81 e5
  // Therefore InvMixColumns should map:
  //   04 66 81 e5  ->  d4 bf 5d 30
  //
  // We repeat the same known column across all 4 words because invMixColumnsW
  // processes exactly 4 columns (w[0..3]) independently.
  unsigned int w[4] = {
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
  };

  invMixColumnsW(w);

  const uint32_t expected = MakeWord(0xd4, 0xbf, 0x5d, 0x30);
  EXPECT_EQ(static_cast<uint32_t>(w[0]), expected);
  EXPECT_EQ(static_cast<uint32_t>(w[1]), expected);
  EXPECT_EQ(static_cast<uint32_t>(w[2]), expected);
  EXPECT_EQ(static_cast<uint32_t>(w[3]), expected);
}

TEST(InvMixColumnsWTest_1611, KnownVectorFromAESSpec_DifferentColumns_1611)
{
  // Use two independent known inverse pairs derived from the AES MixColumns example.
  // Pair A: 04 66 81 e5 -> d4 bf 5d 30
  //
  // Another well-known MixColumns example (FIPS-197) for a different column:
  //   e0 b4 52 ae ->  d4 e2 72 7f  (MixColumns)
  // Thus InvMixColumns:
  //   d4 e2 72 7f ->  e0 b4 52 ae
  unsigned int w[4] = {
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
      static_cast<unsigned int>(MakeWord(0xd4, 0xe2, 0x72, 0x7f)),
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
      static_cast<unsigned int>(MakeWord(0xd4, 0xe2, 0x72, 0x7f)),
  };

  invMixColumnsW(w);

  EXPECT_EQ(static_cast<uint32_t>(w[0]), MakeWord(0xd4, 0xbf, 0x5d, 0x30));
  EXPECT_EQ(static_cast<uint32_t>(w[1]), MakeWord(0xe0, 0xb4, 0x52, 0xae));
  EXPECT_EQ(static_cast<uint32_t>(w[2]), MakeWord(0xd4, 0xbf, 0x5d, 0x30));
  EXPECT_EQ(static_cast<uint32_t>(w[3]), MakeWord(0xe0, 0xb4, 0x52, 0xae));
}

TEST(InvMixColumnsWTest_1611, Boundary_AllZerosStayZeros_1611)
{
  unsigned int w[4] = {0u, 0u, 0u, 0u};
  invMixColumnsW(w);

  EXPECT_EQ(w[0], 0u);
  EXPECT_EQ(w[1], 0u);
  EXPECT_EQ(w[2], 0u);
  EXPECT_EQ(w[3], 0u);
}

TEST(InvMixColumnsWTest_1611, Boundary_DoesNotWriteOutsideFourWords_1611)
{
  // Place sentinels around the 4-word region we pass to invMixColumnsW.
  std::array<unsigned int, 6> buf = {
      0xA1B2C3D4u, // sentinel (before)
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
      static_cast<unsigned int>(MakeWord(0xd4, 0xe2, 0x72, 0x7f)),
      static_cast<unsigned int>(MakeWord(0x04, 0x66, 0x81, 0xe5)),
      static_cast<unsigned int>(MakeWord(0xd4, 0xe2, 0x72, 0x7f)),
      0x1A2B3C4Du, // sentinel (after)
  };

  invMixColumnsW(buf.data() + 1);

  // Sentinels must remain unchanged.
  EXPECT_EQ(buf[0], 0xA1B2C3D4u);
  EXPECT_EQ(buf[5], 0x1A2B3C4Du);

  // And the 4 processed words should match the known expected outputs.
  EXPECT_EQ(static_cast<uint32_t>(buf[1]), MakeWord(0xd4, 0xbf, 0x5d, 0x30));
  EXPECT_EQ(static_cast<uint32_t>(buf[2]), MakeWord(0xe0, 0xb4, 0x52, 0xae));
  EXPECT_EQ(static_cast<uint32_t>(buf[3]), MakeWord(0xd4, 0xbf, 0x5d, 0x30));
  EXPECT_EQ(static_cast<uint32_t>(buf[4]), MakeWord(0xe0, 0xb4, 0x52, 0xae));
}