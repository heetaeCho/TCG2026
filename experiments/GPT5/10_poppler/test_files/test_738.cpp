// AnnotCalloutLine_test.cpp
// Unit tests for AnnotCalloutLine::getY1 (and related observable behavior via public getters)
// TEST_ID = 738

#include <gtest/gtest.h>

#include "Annot.h" // from ./TestProjects/poppler/poppler/Annot.h

// Poppler headers typically live in the global namespace; if your build wraps them,
// adjust namespaces accordingly.

class AnnotCalloutLineTest_738 : public ::testing::Test {};

// Normal operation: constructor stores y1 and getter returns it.
TEST_F(AnnotCalloutLineTest_738, GetY1ReturnsConstructorY1_738) {
  const double x1 = 10.5;
  const double y1 = 20.25;
  const double x2 = -3.0;
  const double y2 = 99.0;

  AnnotCalloutLine line(x1, y1, x2, y2);
  EXPECT_DOUBLE_EQ(line.getY1(), y1);
}

// Boundary-ish: zero coordinates (also aligns with default-like values).
TEST_F(AnnotCalloutLineTest_738, GetY1ReturnsZeroWhenConstructedWithZero_738) {
  AnnotCalloutLine line(0.0, 0.0, 0.0, 0.0);
  EXPECT_DOUBLE_EQ(line.getY1(), 0.0);
}

// Boundary-ish: negative y1 should be returned unchanged.
TEST_F(AnnotCalloutLineTest_738, GetY1ReturnsNegativeValue_738) {
  const double y1 = -1234.5;
  AnnotCalloutLine line(1.0, y1, 2.0, 3.0);
  EXPECT_DOUBLE_EQ(line.getY1(), y1);
}

// Boundary-ish: very large magnitude y1 should round-trip through the getter.
TEST_F(AnnotCalloutLineTest_738, GetY1ReturnsLargeMagnitudeValue_738) {
  const double y1 = 1e300; // large but typically finite for double
  AnnotCalloutLine line(0.0, y1, 0.0, 0.0);
  EXPECT_DOUBLE_EQ(line.getY1(), y1);
}

// Consistency: calling getY1 multiple times returns the same value.
TEST_F(AnnotCalloutLineTest_738, GetY1IsStableAcrossMultipleCalls_738) {
  const double y1 = 42.0;
  AnnotCalloutLine line(7.0, y1, 8.0, 9.0);

  const double first = line.getY1();
  const double second = line.getY1();
  const double third = line.getY1();

  EXPECT_DOUBLE_EQ(first, y1);
  EXPECT_DOUBLE_EQ(second, y1);
  EXPECT_DOUBLE_EQ(third, y1);
}

// Cross-check with other public getters (still black-box): ensure getY1 corresponds
// to the first endpoint and differs from y2 when y1 != y2.
TEST_F(AnnotCalloutLineTest_738, GetY1CorrespondsToFirstEndpointNotSecond_738) {
  const double y1 = 5.5;
  const double y2 = -6.5;
  AnnotCalloutLine line(1.0, y1, 2.0, y2);

  EXPECT_DOUBLE_EQ(line.getY1(), y1);
  EXPECT_DOUBLE_EQ(line.getY2(), y2);
  EXPECT_NE(line.getY1(), line.getY2());
}

// Exceptional/error cases:
// - None are observable via this interface: constructor and getters do not expose
//   error returns/exceptions in the provided signature. Therefore, no error-case
//   assertions are included beyond boundary values above.

// External interactions:
// - None are present/observable: no callbacks, handlers, or dependencies are exposed
//   through the given interface, so Google Mock is not used.