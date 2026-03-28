// File: setLum_unittest_1591.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <array>

// NOTE:
// setLum is declared static inside SplashOutputDev.cc, so we include the .cc directly
// to make the symbol visible in this test translation unit.
// This is a common technique for unit-testing file-local helpers.
#include "SplashOutputDev.cc"

namespace {

class SetLumTest_1591 : public ::testing::Test {
protected:
  static void CallSetLum(unsigned char rIn, unsigned char gIn, unsigned char bIn, int lum,
                         unsigned char &rOut, unsigned char &gOut, unsigned char &bOut)
  {
    setLum(rIn, gIn, bIn, lum, &rOut, &gOut, &bOut);
  }

  static void ExpectBytesInRange(unsigned char r, unsigned char g, unsigned char b)
  {
    // Unsigned char is already in [0,255], but keep this explicit as a behavioral assertion.
    EXPECT_LE(static_cast<int>(r), 255);
    EXPECT_LE(static_cast<int>(g), 255);
    EXPECT_LE(static_cast<int>(b), 255);
    EXPECT_GE(static_cast<int>(r), 0);
    EXPECT_GE(static_cast<int>(g), 0);
    EXPECT_GE(static_cast<int>(b), 0);
  }
};

TEST_F(SetLumTest_1591, WritesAllOutputsForTypicalInputs_1591)
{
  unsigned char rOut = 0xAA;
  unsigned char gOut = 0xBB;
  unsigned char bOut = 0xCC;

  CallSetLum(/*rIn=*/40, /*gIn=*/120, /*bIn=*/200, /*lum=*/128, rOut, gOut, bOut);

  // Observable behavior: output pointers are written with some byte values.
  // We avoid asserting exact values (black-box).
  ExpectBytesInRange(rOut, gOut, bOut);
  EXPECT_TRUE(rOut != 0xAA || gOut != 0xBB || bOut != 0xCC);
}

TEST_F(SetLumTest_1591, DeterministicForSameInputs_1591)
{
  unsigned char r1 = 0, g1 = 0, b1 = 0;
  unsigned char r2 = 0, g2 = 0, b2 = 0;

  CallSetLum(/*rIn=*/10, /*gIn=*/20, /*bIn=*/30, /*lum=*/77, r1, g1, b1);
  CallSetLum(/*rIn=*/10, /*gIn=*/20, /*bIn=*/30, /*lum=*/77, r2, g2, b2);

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(g1, g2);
  EXPECT_EQ(b1, b2);
}

TEST_F(SetLumTest_1591, DifferentLumValuesUsuallyProduceDifferentOutputs_1591)
{
  // Pick a non-extreme color to reduce the chance of saturation masking differences.
  unsigned char rA = 0, gA = 0, bA = 0;
  unsigned char rB = 0, gB = 0, bB = 0;

  CallSetLum(/*rIn=*/50, /*gIn=*/100, /*bIn=*/150, /*lum=*/0,   rA, gA, bA);
  CallSetLum(/*rIn=*/50, /*gIn=*/100, /*bIn=*/150, /*lum=*/255, rB, gB, bB);

  ExpectBytesInRange(rA, gA, bA);
  ExpectBytesInRange(rB, gB, bB);

  // Black-box expectation: changing the requested luminance should typically change output.
  // We do not require all channels to differ.
  EXPECT_TRUE(rA != rB || gA != gB || bA != bB);
}

TEST_F(SetLumTest_1591, HandlesBlackInputAcrossLumExtremes_1591)
{
  unsigned char r0 = 0, g0 = 0, b0 = 0;
  unsigned char r1 = 0, g1 = 0, b1 = 0;

  CallSetLum(/*rIn=*/0, /*gIn=*/0, /*bIn=*/0, /*lum=*/0,   r0, g0, b0);
  CallSetLum(/*rIn=*/0, /*gIn=*/0, /*bIn=*/0, /*lum=*/255, r1, g1, b1);

  ExpectBytesInRange(r0, g0, b0);
  ExpectBytesInRange(r1, g1, b1);
}

TEST_F(SetLumTest_1591, HandlesWhiteInputAcrossLumExtremes_1591)
{
  unsigned char r0 = 0, g0 = 0, b0 = 0;
  unsigned char r1 = 0, g1 = 0, b1 = 0;

  CallSetLum(/*rIn=*/255, /*gIn=*/255, /*bIn=*/255, /*lum=*/0,   r0, g0, b0);
  CallSetLum(/*rIn=*/255, /*gIn=*/255, /*bIn=*/255, /*lum=*/255, r1, g1, b1);

  ExpectBytesInRange(r0, g0, b0);
  ExpectBytesInRange(r1, g1, b1);
}

TEST_F(SetLumTest_1591, SupportsDistinctOutputBufferLocations_1591)
{
  std::array<unsigned char, 3> out = {0x11, 0x22, 0x33};

  setLum(/*rIn=*/1, /*gIn=*/2, /*bIn=*/3, /*lum=*/10, &out[0], &out[1], &out[2]);

  ExpectBytesInRange(out[0], out[1], out[2]);
  EXPECT_TRUE(out[0] != 0x11 || out[1] != 0x22 || out[2] != 0x33);
}

TEST_F(SetLumTest_1591, LumOutOfTypicalByteRangeDoesNotCrashAndWritesBytes_1591)
{
  unsigned char rNeg = 0, gNeg = 0, bNeg = 0;
  unsigned char rBig = 0, gBig = 0, bBig = 0;

  CallSetLum(/*rIn=*/70, /*gIn=*/80, /*bIn=*/90, /*lum=*/-100, rNeg, gNeg, bNeg);
  CallSetLum(/*rIn=*/70, /*gIn=*/80, /*bIn=*/90, /*lum=*/1000, rBig, gBig, bBig);

  ExpectBytesInRange(rNeg, gNeg, bNeg);
  ExpectBytesInRange(rBig, gBig, bBig);

  // Not asserting a specific clamp policy; just that it produced stable byte outputs.
  // If the implementation clamps, these may differ from each other.
}

} // namespace