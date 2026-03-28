// TEST_ID: 390
//
// Unit tests for dblToByte(double) from poppler/GfxState.h
//
// Constraints note:
// - We treat dblToByte as a black box: we only test observable output for given inputs.
// - We do not assume any internal clamping/rounding beyond what is observable from the signature and return type.
// - The function is defined as `static inline`, so we include the header and call it directly.

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "GfxState.h"

namespace {

// Helper to express expected behavior for finite inputs based on the *observable* cast semantics
// of returning an `unsigned char` after multiplying by 255.0.
//
// NOTE: This does not access any internal state of the production code; it just computes
// what the C++ expression result would be for finite values on the current platform.
// If the implementation changes (e.g., adds clamping), these tests will catch it.
static unsigned char ReferenceFinite(double x) {
  const double y = x * 255.0;
  return static_cast<unsigned char>(y);
}

}  // namespace

// Normal operation: simple known points
TEST(DblToByteTest_390, ZeroMapsToZero_390) {
  EXPECT_EQ(dblToByte(0.0), static_cast<unsigned char>(0));
}

TEST(DblToByteTest_390, OneMapsTo255_390) {
  EXPECT_EQ(dblToByte(1.0), static_cast<unsigned char>(255));
}

TEST(DblToByteTest_390, HalfProducesSomeByteValue_390) {
  // We don't assume rounding; we only assert consistency with the observable cast semantics.
  EXPECT_EQ(dblToByte(0.5), ReferenceFinite(0.5));
}

TEST(DblToByteTest_390, QuarterProducesSomeByteValue_390) {
  EXPECT_EQ(dblToByte(0.25), ReferenceFinite(0.25));
}

// Boundary-ish finite cases around 0 and 1
TEST(DblToByteTest_390, JustBelowOneMatchesCastSemantics_390) {
  const double x = std::nextafter(1.0, 0.0);
  EXPECT_EQ(dblToByte(x), ReferenceFinite(x));
}

TEST(DblToByteTest_390, JustAboveZeroMatchesCastSemantics_390) {
  const double x = std::nextafter(0.0, 1.0);
  EXPECT_EQ(dblToByte(x), ReferenceFinite(x));
}

TEST(DblToByteTest_390, JustBelowZeroMatchesCastSemantics_390) {
  const double x = std::nextafter(0.0, -1.0);
  EXPECT_EQ(dblToByte(x), ReferenceFinite(x));
}

TEST(DblToByteTest_390, JustAboveOneMatchesCastSemantics_390) {
  const double x = std::nextafter(1.0, 2.0);
  EXPECT_EQ(dblToByte(x), ReferenceFinite(x));
}

// Error/exceptional-ish inputs: negative, large, infinities, NaN.
// These are "observable" only via return value and "does not crash".
TEST(DblToByteTest_390, NegativeInputDoesNotCrashAndMatchesCastSemantics_390) {
  const double x = -0.1;
  EXPECT_EQ(dblToByte(x), ReferenceFinite(x));
}

TEST(DblToByteTest_390, LargeFiniteInputDoesNotCrashAndMatchesCastSemantics_390) {
  const double x = 12345.6789;
  EXPECT_EQ(dblToByte(x), ReferenceFinite(x));
}

TEST(DblToByteTest_390, NegativeLargeFiniteInputDoesNotCrashAndMatchesCastSemantics_390) {
  const double x = -12345.6789;
  EXPECT_EQ(dblToByte(x), ReferenceFinite(x));
}

TEST(DblToByteTest_390, PositiveInfinityDoesNotCrash_390) {
  const double x = std::numeric_limits<double>::infinity();

  // Conversion from infinity to integer types is implementation-defined/unspecified territory.
  // We only assert the function call is safe and returns *some* unsigned char.
  const unsigned char r = dblToByte(x);
  (void)r;
  SUCCEED();
}

TEST(DblToByteTest_390, NegativeInfinityDoesNotCrash_390) {
  const double x = -std::numeric_limits<double>::infinity();
  const unsigned char r = dblToByte(x);
  (void)r;
  SUCCEED();
}

TEST(DblToByteTest_390, NaNDoesNotCrash_390) {
  const double x = std::numeric_limits<double>::quiet_NaN();
  const unsigned char r = dblToByte(x);
  (void)r;
  SUCCEED();
}

// Basic monotonic sanity check in a safe range (finite, away from wrap/UB concerns).
// This does not assume exact increments; it only checks non-decreasing behavior for
// a small set where cast semantics should be stable.
TEST(DblToByteTest_390, NonDecreasingForIncreasingInputsInRange_390) {
  const double xs[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

  unsigned char prev = dblToByte(xs[0]);
  for (size_t i = 1; i < sizeof(xs) / sizeof(xs[0]); ++i) {
    const unsigned char cur = dblToByte(xs[i]);
    // For typical cast semantics on [0,1], this should be non-decreasing.
    // If implementation changes to something non-monotonic, this will detect it.
    EXPECT_LE(prev, cur) << "at i=" << i << " x=" << xs[i];
    prev = cur;
  }
}