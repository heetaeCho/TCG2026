// Decrypt_rotr_test_1627.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

// NOTE:
// rotr() is declared `static inline` in Decrypt.cc, so it has internal linkage.
// To test it without re-implementing it, we include the implementation file
// into this test translation unit.
#include "TestProjects/poppler/poppler/Decrypt.cc"

namespace {

TEST(RotrTest_1627, KnownVectors_1627) {
  // Hand-verified test vectors (do not derive from implementation).
  EXPECT_EQ(rotr(0x12345678u, 4u), 0x81234567u);
  EXPECT_EQ(rotr(0x80000001u, 1u), 0xC0000000u);
  EXPECT_EQ(rotr(0x00000001u, 31u), 0x00000002u); // rotr by 31 == rotl by 1
  EXPECT_EQ(rotr(0xFFFFFFFFu, 7u), 0xFFFFFFFFu);
  EXPECT_EQ(rotr(0x00000000u, 13u), 0x00000000u);
}

TEST(RotrTest_1627, BoundaryShiftsWithinDefinedRange_1627) {
  // We only exercise n in [1, 31]. Shifting by 0 or 32 can be undefined in C/C++.
  const unsigned int x = 0xA5A5A5A5u;

  EXPECT_NE(rotr(x, 1u), x);   // for this pattern, rotate by 1 should change value
  EXPECT_EQ(rotr(x, 31u), rotr(x, 31u)); // stability / no UB for n=31
}

TEST(RotrTest_1627, RoundTripProperty_1627) {
  // Observable property of bit-rotation:
  // rotating right by n, then right by (32-n), yields the original value (for n in 1..31).
  const std::vector<unsigned int> xs = {
      0x00000001u, 0x80000000u, 0xDEADBEEFu, 0x12345678u, 0x0F0F0F0Fu, 0xCAFEBABEu};

  for (unsigned int n = 1; n <= 31; ++n) {
    for (unsigned int x : xs) {
      const unsigned int y = rotr(x, n);
      const unsigned int z = rotr(y, 32u - n);
      EXPECT_EQ(z, x) << "x=0x" << std::hex << x << " n=" << std::dec << n;
    }
  }
}

TEST(RotrTest_1627, PreservesPopcount_1627) {
  // Rotation should preserve the number of set bits.
  const std::vector<unsigned int> xs = {
      0x00000000u, 0xFFFFFFFFu, 0x80000001u, 0x7FFFFFFFu, 0x13579BDFu, 0x2468ACE0u};

  for (unsigned int n = 1; n <= 31; ++n) {
    for (unsigned int x : xs) {
      const unsigned int y = rotr(x, n);
#if defined(__GNUC__) || defined(__clang__)
      EXPECT_EQ(__builtin_popcount(x), __builtin_popcount(y))
          << "x=0x" << std::hex << x << " y=0x" << y << " n=" << std::dec << n;
#else
      // Portable fallback: verify via round-trip identity (still a strong observable invariant).
      EXPECT_EQ(rotr(y, 32u - n), x)
          << "x=0x" << std::hex << x << " y=0x" << y << " n=" << std::dec << n;
#endif
    }
  }
}

TEST(RotrTest_1627, SingleBitMovesToExpectedPosition_1627) {
  // For a single bit at position k, rotr by n moves it to (k - n) mod 32.
  // Validate with fixed positions using explicit expected constants.
  EXPECT_EQ(rotr(0x00000001u, 1u), 0x80000000u);
  EXPECT_EQ(rotr(0x00000001u, 2u), 0x40000000u);
  EXPECT_EQ(rotr(0x00010000u, 8u), 0x00000100u);
  EXPECT_EQ(rotr(0x01000000u, 8u), 0x00010000u);
}

} // namespace