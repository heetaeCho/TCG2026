// File: Mul02Table_test_2779.cc
#include <gtest/gtest.h>

#include <cstdint>

// Include the production header that declares Mul02Table.
// If Mul02Table is only available via a .cc in this project layout,
// replace this include with the appropriate public header used by the codebase.
#include "Decrypt.h"  // <-- adjust as needed for your build

// Compile-time checks (observable through the public interface).
static_assert(Mul02Table{}(uint8_t{0x00}) == 0x00, "Mul02Table mapping mismatch for 0x00");
static_assert(Mul02Table{}(uint8_t{0x01}) == 0x02, "Mul02Table mapping mismatch for 0x01");
static_assert(Mul02Table{}(uint8_t{0x80}) == 0x1B, "Mul02Table mapping mismatch for 0x80");
static_assert(Mul02Table{}(uint8_t{0xFF}) == 0xE5, "Mul02Table mapping mismatch for 0xFF");

class Mul02TableTest_2779 : public ::testing::Test {};

TEST_F(Mul02TableTest_2779, OperatorMatchesPublicValuesArrayForAllBytes_2779) {
  const Mul02Table tbl;

  for (int i = 0; i < 256; ++i) {
    const auto u8 = static_cast<uint8_t>(i);
    EXPECT_EQ(tbl(u8), tbl.values[i]) << "Mismatch at byte 0x" << std::hex << i;
  }
}

TEST_F(Mul02TableTest_2779, KnownVector_ZeroAndOne_2779) {
  const Mul02Table tbl;

  EXPECT_EQ(tbl(uint8_t{0x00}), 0x00);
  EXPECT_EQ(tbl(uint8_t{0x01}), 0x02);
}

TEST_F(Mul02TableTest_2779, KnownVector_BoundaryAroundMsb_2779) {
  const Mul02Table tbl;

  // Boundary conditions around the MSB behavior (0x7F vs 0x80).
  EXPECT_EQ(tbl(uint8_t{0x7F}), 0xFE);
  EXPECT_EQ(tbl(uint8_t{0x80}), 0x1B);
}

TEST_F(Mul02TableTest_2779, KnownVector_MaxByte_2779) {
  const Mul02Table tbl;

  EXPECT_EQ(tbl(uint8_t{0xFF}), 0xE5);
}

TEST_F(Mul02TableTest_2779, PublicValuesArrayIsDeterministicAcrossInstances_2779) {
  const Mul02Table a;
  const Mul02Table b;

  for (int i = 0; i < 256; ++i) {
    EXPECT_EQ(a.values[i], b.values[i]) << "Different instances differ at index " << i;
  }
}