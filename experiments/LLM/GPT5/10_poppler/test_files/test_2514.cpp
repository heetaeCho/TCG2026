// File: poppler_permissions_test_2514.cc
#include <gtest/gtest.h>

#include "poppler-document.h" // Provides PopplerPermissions

namespace {

class PopplerPermissionsTest_2514 : public ::testing::Test {};

// Normal operation: verify the exact numeric values of each flag bit.
TEST_F(PopplerPermissionsTest_2514, EnumValuesMatchExpectedBits_2514) {
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT), 1);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_MODIFY), 2);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_COPY), 4);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ADD_NOTES), 8);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_FILL_FORM), 16);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS), 32);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ASSEMBLE), 64);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION), 128);
  EXPECT_EQ(static_cast<int>(POPPLER_PERMISSIONS_FULL), 255);
}

// Boundary condition: FULL should include all individual bits (1..128).
TEST_F(PopplerPermissionsTest_2514, FullIsBitwiseOrOfAllFlags_2514) {
  const int all =
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_MODIFY) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_COPY) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ADD_NOTES) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_FILL_FORM) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ASSEMBLE) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION);

  EXPECT_EQ(all, static_cast<int>(POPPLER_PERMISSIONS_FULL));
}

// Boundary condition: ensure flags are non-overlapping single bits.
TEST_F(PopplerPermissionsTest_2514, FlagsAreDistinctSingleBitValues_2514) {
  const int flags[] = {
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT),
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_MODIFY),
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_COPY),
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ADD_NOTES),
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_FILL_FORM),
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS),
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ASSEMBLE),
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION),
  };

  for (int i = 0; i < 8; ++i) {
    // Single-bit property: x & (x-1) == 0 and x != 0.
    EXPECT_NE(flags[i], 0);
    EXPECT_EQ((flags[i] & (flags[i] - 1)), 0) << "Not a single-bit flag at index " << i;

    for (int j = i + 1; j < 8; ++j) {
      EXPECT_EQ((flags[i] & flags[j]), 0) << "Flags overlap at indices " << i << " and " << j;
    }
  }
}

// Normal operation: combining permissions should preserve contained bits.
TEST_F(PopplerPermissionsTest_2514, CombiningFlagsPreservesMembership_2514) {
  const int combo =
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_COPY) |
      static_cast<int>(POPPLER_PERMISSIONS_OK_TO_FILL_FORM);

  EXPECT_NE((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT)), 0);
  EXPECT_NE((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_COPY)), 0);
  EXPECT_NE((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_FILL_FORM)), 0);

  EXPECT_EQ((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_MODIFY)), 0);
  EXPECT_EQ((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ADD_NOTES)), 0);
  EXPECT_EQ((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS)), 0);
  EXPECT_EQ((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_ASSEMBLE)), 0);
  EXPECT_EQ((combo & static_cast<int>(POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION)), 0);
}

// Boundary condition: a "no permissions" value (0) should be a subset of FULL.
TEST_F(PopplerPermissionsTest_2514, ZeroPermissionsIsSubsetOfFull_2514) {
  const int none = 0;
  const int full = static_cast<int>(POPPLER_PERMISSIONS_FULL);

  EXPECT_EQ((none & full), 0);
  EXPECT_EQ((full & none), 0);
}

// Boundary / error-ish case (observable via interface semantics):
// FULL mask should be exactly 8 lower bits (0xFF) and not include higher bits.
TEST_F(PopplerPermissionsTest_2514, FullMaskIsExactlyLowByte_2514) {
  const int full = static_cast<int>(POPPLER_PERMISSIONS_FULL);

  EXPECT_EQ((full & 0xFF), 0xFF);
  EXPECT_EQ((full & ~0xFF), 0) << "FULL unexpectedly has bits outside low byte";
}

}  // namespace