// LinkDest_getRight_tests_276.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "Link.h"

// These Poppler headers are typically required to construct Array/Object inputs
// for LinkDest's public constructor.
#include "Object.h"
#include "Array.h"

namespace {

// Helper to construct a destination array for /FitR.
// PDF dest format (commonly): [ page /FitR left bottom right top ]
static Array MakeFitRDestArray(double left, double bottom, double right, double top)
{
  Array a;

  // Page number (using 1 as a simple valid page index for tests that only care about coords).
  a.add(Object(1));

  // Destination kind name.
  a.add(Object(objName, "FitR"));

  // Coordinates.
  a.add(Object(left));
  a.add(Object(bottom));
  a.add(Object(right));
  a.add(Object(top));

  return a;
}

} // namespace

class LinkDestGetRightTest_276 : public ::testing::Test
{
};

// Normal operation: when constructed from a /FitR destination array, getRight()
// should reflect the destination's right coordinate.
TEST_F(LinkDestGetRightTest_276, FitRReturnsProvidedRight_276)
{
  const double expectedRight = 30.5;
  Array a = MakeFitRDestArray(/*left=*/10.0, /*bottom=*/20.0, /*right=*/expectedRight, /*top=*/40.0);

  LinkDest dest(a);

  // If parsing succeeds, right should match exactly (it is a stored double).
  EXPECT_TRUE(dest.isOk());
  EXPECT_DOUBLE_EQ(dest.getRight(), expectedRight);
}

// Boundary: negative coordinate should be observable (no assumptions about validation
// beyond that the public API returns a stored double if construction is accepted).
TEST_F(LinkDestGetRightTest_276, FitRAllowsNegativeRight_276)
{
  const double expectedRight = -123.0;
  Array a = MakeFitRDestArray(/*left=*/0.0, /*bottom=*/0.0, /*right=*/expectedRight, /*top=*/1.0);

  LinkDest dest(a);

  if (dest.isOk()) {
    EXPECT_DOUBLE_EQ(dest.getRight(), expectedRight);
  } else {
    // Even if the implementation rejects it, calling getRight() should still be safe.
    EXPECT_TRUE(std::isfinite(dest.getRight()));
  }
}

// Boundary: very large coordinate.
TEST_F(LinkDestGetRightTest_276, FitRHandlesVeryLargeRight_276)
{
  const double expectedRight = std::numeric_limits<double>::max() / 4.0;
  Array a = MakeFitRDestArray(/*left=*/0.0, /*bottom=*/0.0, /*right=*/expectedRight, /*top=*/1.0);

  LinkDest dest(a);

  if (dest.isOk()) {
    EXPECT_DOUBLE_EQ(dest.getRight(), expectedRight);
  } else {
    EXPECT_TRUE(std::isfinite(dest.getRight()));
  }
}

// Error/exceptional: empty array should produce a non-ok destination (or at least
// not crash). We only assert observable behavior through the public API.
TEST_F(LinkDestGetRightTest_276, EmptyArrayDoesNotCrashAndIsNotOkOrFinite_276)
{
  Array a;
  LinkDest dest(a);

  // Most implementations will consider this invalid.
  // We don't force isOk()==false, but we do verify safety and a sane return.
  (void)dest.isOk();
  EXPECT_TRUE(std::isfinite(dest.getRight()));
}

// Error/exceptional: wrong element types / insufficient elements.
// Use a minimal array that is unlikely to be a valid destination.
TEST_F(LinkDestGetRightTest_276, MalformedArrayDoesNotCrashAndRightIsFinite_276)
{
  Array a;
  a.add(Object(objName, "NotARealPage"));
  a.add(Object(objName, "FitR"));
  a.add(Object(objName, "left")); // wrong type for a numeric coordinate

  LinkDest dest(a);

  // Regardless of validity, the accessor should be safe to call.
  (void)dest.isOk();
  EXPECT_TRUE(std::isfinite(dest.getRight()));
}