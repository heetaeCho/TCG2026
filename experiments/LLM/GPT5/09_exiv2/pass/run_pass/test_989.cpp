// SPDX-License-Identifier: GPL-2.0-or-later
// File: version_test_989.cpp
//
// Unit tests for Exiv2::testVersion() from ./TestProjects/exiv2/src/version.cpp
//
// Constraints honored:
// - Treat implementation as black box (no re-implementation of logic beyond observable contract).
// - Use only public/visible interface (testVersion + version macros + versionNumber declaration).
// - No private state access.
// - Cover normal, boundary, and observable error-ish cases (e.g., extreme inputs).

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// Forward declarations / includes:
// In Exiv2, version-related APIs/macros are typically provided by <exiv2/version.hpp>.
// If your project uses a different header name, adjust accordingly.
#include <exiv2/version.hpp>

namespace {

// Helper to safely extract components from a packed version number created by EXIV2_MAKE_VERSION.
// This does NOT infer internal behavior of Exiv2::testVersion; it only uses the public macro
// encoding contract (as defined by EXIV2_MAKE_VERSION in headers).
//
// If EXIV2_MAKE_VERSION changes its bit layout, these tests should be updated accordingly.
// We keep this helper local to tests.
struct VersionTriplet {
  uint32_t major;
  uint32_t minor;
  uint32_t patch;
};

inline VersionTriplet DecomposeVersion(uint32_t v) {
  // Common Exiv2 scheme is (major<<16) | (minor<<8) | patch.
  // We rely on the public macro EXIV2_MAKE_VERSION encoding by round-tripping via masks.
  // This is used only to create boundary inputs around the current version.
  VersionTriplet t{};
  t.major = (v >> 16) & 0xFFFFu;
  t.minor = (v >> 8) & 0xFFu;
  t.patch = (v)&0xFFu;
  return t;
}

// Compute (currentVersion - 1) in packed form when possible, and decompose it.
// If currentVersion is 0 (unlikely), we return nullopt-like flag.
inline bool GetPreviousTriplet(VersionTriplet& out_prev) {
  const uint32_t curPacked = Exiv2::versionNumber();
  if (curPacked == 0u) return false;
  const uint32_t prevPacked = curPacked - 1u;
  out_prev = DecomposeVersion(prevPacked);
  return true;
}

}  // namespace

// Fixture mainly for consistent naming; no private state used.
class VersionTest_989 : public ::testing::Test {};

// Normal operation: querying exactly the current library version should succeed.
TEST_F(VersionTest_989, CurrentVersionIsSupported_989) {
  const uint32_t curPacked = Exiv2::versionNumber();
  const auto cur = DecomposeVersion(curPacked);

  EXPECT_TRUE(Exiv2::testVersion(cur.major, cur.minor, cur.patch));
}

// Boundary: querying one "tick" above the current packed version should fail (if increment doesn't overflow).
TEST_F(VersionTest_989, OneAboveCurrentPackedVersionIsNotSupported_989) {
  const uint32_t curPacked = Exiv2::versionNumber();

  // If we're at max uint32, can't add 1 safely.
  if (curPacked == std::numeric_limits<uint32_t>::max()) {
    GTEST_SKIP() << "Cannot test +1 boundary when versionNumber() == UINT32_MAX.";
  }

  const uint32_t nextPacked = curPacked + 1u;
  const auto next = DecomposeVersion(nextPacked);

  EXPECT_FALSE(Exiv2::testVersion(next.major, next.minor, next.patch));
}

// Boundary: querying one "tick" below current packed version should succeed (when possible).
TEST_F(VersionTest_989, OneBelowCurrentPackedVersionIsSupported_989) {
  VersionTriplet prev{};
  if (!GetPreviousTriplet(prev)) {
    GTEST_SKIP() << "Cannot test -1 boundary when versionNumber() == 0.";
  }

  EXPECT_TRUE(Exiv2::testVersion(prev.major, prev.minor, prev.patch));
}

// Normal: version 0.0.0 should always be supported because any non-negative current version >= 0.0.0.
TEST_F(VersionTest_989, ZeroVersionIsAlwaysSupported_989) {
  EXPECT_TRUE(Exiv2::testVersion(0u, 0u, 0u));
}

// Exceptional-ish / extreme inputs: very large requested version should not be supported.
// (Observable outcome: should return false, and must not crash.)
TEST_F(VersionTest_989, ExtremelyLargeRequestedVersionIsNotSupported_989) {
  const uint32_t max = std::numeric_limits<uint32_t>::max();

  // Using very large components; outcome should be false on any realistic library version.
  // This is an observable error-ish case (out-of-range request) without relying on internals.
  EXPECT_FALSE(Exiv2::testVersion(max, max, max));
}

// Consistency check: testVersion should agree with a direct comparison against EXIV2_MAKE_VERSION
// using the *public macro*, for a few representative points around the current version.
// This does not re-implement internals; it checks that the exported function is consistent with
// the public macro encoding and versionNumber value.
TEST_F(VersionTest_989, AgreesWithMacroComparisonAroundCurrent_989) {
  const uint32_t curPacked = Exiv2::versionNumber();
  const auto cur = DecomposeVersion(curPacked);

  // Exactly current:
  {
    const bool expected = curPacked >= EXIV2_MAKE_VERSION(cur.major, cur.minor, cur.patch);
    EXPECT_EQ(Exiv2::testVersion(cur.major, cur.minor, cur.patch), expected);
  }

  // One below (if possible):
  VersionTriplet prev{};
  if (GetPreviousTriplet(prev)) {
    const bool expected = curPacked >= EXIV2_MAKE_VERSION(prev.major, prev.minor, prev.patch);
    EXPECT_EQ(Exiv2::testVersion(prev.major, prev.minor, prev.patch), expected);
  }

  // One above (if possible):
  if (curPacked != std::numeric_limits<uint32_t>::max()) {
    const uint32_t nextPacked = curPacked + 1u;
    const auto next = DecomposeVersion(nextPacked);
    const bool expected = curPacked >= EXIV2_MAKE_VERSION(next.major, next.minor, next.patch);
    EXPECT_EQ(Exiv2::testVersion(next.major, next.minor, next.patch), expected);
  }
}