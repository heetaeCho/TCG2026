// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_versionNumber_985.cpp
//
// Unit tests for Exiv2::versionNumber() from ./TestProjects/exiv2/src/version.cpp
//
// Constraints honored:
// - Treat implementation as black box: only assert observable outputs.
// - No reliance on private/internal state.
// - No mocking needed (no collaborators).
// - Include normal + boundary-ish checks (sanity + determinism + macro-consistency).

#include <gtest/gtest.h>

#include <cstdint>

// Exiv2 headers usually provide version macros and versionNumber() declaration.
#include <exiv2/exiv2.hpp>

// Some builds may expose these in version.hpp; include if available in your tree.
// (If your build fails due to missing header, you can remove this include.)
#include <exiv2/version.hpp>

namespace {

// TEST_ID = 985
class VersionNumberTest_985 : public ::testing::Test {};

}  // namespace

// Normal operation: should return a stable, non-zero version number.
TEST_F(VersionNumberTest_985, ReturnsNonZero_985) {
  const uint32_t v = Exiv2::versionNumber();
  EXPECT_NE(v, 0u);
}

// Normal operation: calling twice should return the same value (pure function behavior).
TEST_F(VersionNumberTest_985, IsDeterministicAcrossCalls_985) {
  const uint32_t v1 = Exiv2::versionNumber();
  const uint32_t v2 = Exiv2::versionNumber();
  EXPECT_EQ(v1, v2);
}

// Boundary/sanity: version should be within a 24-bit range if encoded as (major<<16 | minor<<8 | patch).
// We do not assume encoding beyond what is observable in public macros below; this is a loose sanity bound.
TEST_F(VersionNumberTest_985, FitsIn24BitsSanity_985) {
  const uint32_t v = Exiv2::versionNumber();
  EXPECT_LT(v, (1u << 24));  // very permissive sanity check
}

// Macro-consistency: versionNumber should match the library's own make-version macro based on the public macros.
TEST_F(VersionNumberTest_985, MatchesMakeVersionMacro_985) {
  const uint32_t expected =
      EXIV2_MAKE_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);

  EXPECT_EQ(Exiv2::versionNumber(), expected);
}

// Macro-consistency / boundary-ish: if patch is defined, ensure it is representable in the expected 0..255 range
// typically used by EXIV2_MAKE_VERSION. We don't enforce exact policy, just guard against obviously invalid values.
TEST_F(VersionNumberTest_985, PatchMacroIsByteSizedSanity_985) {
  // These macros are compile-time constants. If they are outside byte range, it's likely a configuration issue.
  EXPECT_GE(EXIV2_PATCH_VERSION, 0);
  EXPECT_LE(EXIV2_PATCH_VERSION, 255);
}

// Macro-consistency / boundary-ish: same for minor.
TEST_F(VersionNumberTest_985, MinorMacroIsByteSizedSanity_985) {
  EXPECT_GE(EXIV2_MINOR_VERSION, 0);
  EXPECT_LE(EXIV2_MINOR_VERSION, 255);
}

// Macro-consistency / boundary-ish: major should also be sane (byte-sized for the common encoding).
TEST_F(VersionNumberTest_985, MajorMacroIsByteSizedSanity_985) {
  EXPECT_GE(EXIV2_MAJOR_VERSION, 0);
  EXPECT_LE(EXIV2_MAJOR_VERSION, 255);
}