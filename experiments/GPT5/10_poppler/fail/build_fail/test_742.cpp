// TEST_ID: 742
// File: test_annotcalloutmultiline_gety3_742.cpp

#include <gtest/gtest.h>

#include "Annot.h" // AnnotCalloutMultiLine

// The implementation is treated as a black box. We only test observable behavior
// through the public interface.

namespace {

class AnnotCalloutMultiLineTest_742 : public ::testing::Test {};

TEST_F(AnnotCalloutMultiLineTest_742, GetY3_ReturnsConstructorY3_742) {
  const double x1 = 1.0, y1 = 2.0;
  const double x2 = 3.0, y2 = 4.0;
  const double x3 = 5.0, y3 = 6.5;

  AnnotCalloutMultiLine obj(x1, y1, x2, y2, x3, y3);

  EXPECT_DOUBLE_EQ(obj.getY3(), y3);
}

TEST_F(AnnotCalloutMultiLineTest_742, GetY3_HandlesNegativeY3_742) {
  const double x1 = 0.0, y1 = 0.0;
  const double x2 = 10.0, y2 = 10.0;
  const double x3 = -3.0, y3 = -42.25;

  AnnotCalloutMultiLine obj(x1, y1, x2, y2, x3, y3);

  EXPECT_DOUBLE_EQ(obj.getY3(), y3);
}

TEST_F(AnnotCalloutMultiLineTest_742, GetY3_HandlesZeroY3_742) {
  AnnotCalloutMultiLine obj(/*x1*/ 1.0, /*y1*/ 1.0,
                            /*x2*/ 2.0, /*y2*/ 2.0,
                            /*x3*/ 3.0, /*y3*/ 0.0);

  EXPECT_DOUBLE_EQ(obj.getY3(), 0.0);
}

TEST_F(AnnotCalloutMultiLineTest_742, GetY3_StableAcrossMultipleCalls_742) {
  const double y3 = 123.0;
  AnnotCalloutMultiLine obj(/*x1*/ 1.0, /*y1*/ 2.0,
                            /*x2*/ 3.0, /*y2*/ 4.0,
                            /*x3*/ 5.0, /*y3*/ y3);

  const double first = obj.getY3();
  const double second = obj.getY3();
  const double third = obj.getY3();

  EXPECT_DOUBLE_EQ(first, y3);
  EXPECT_DOUBLE_EQ(second, y3);
  EXPECT_DOUBLE_EQ(third, y3);
}

TEST_F(AnnotCalloutMultiLineTest_742, GetY3_HandlesLargeMagnitudeY3_742) {
  // Use a large but representable finite double value (avoid inf).
  const double y3 = 1.0e308;

  AnnotCalloutMultiLine obj(/*x1*/ 0.0, /*y1*/ 0.0,
                            /*x2*/ 1.0, /*y2*/ 1.0,
                            /*x3*/ 2.0, /*y3*/ y3);

  EXPECT_DOUBLE_EQ(obj.getY3(), y3);
}

TEST_F(AnnotCalloutMultiLineTest_742, GetY3_DoesNotDependOnOtherCoordinates_742) {
  // Same y3, change other coordinates: getY3 should still reflect the provided y3.
  const double y3 = 9.75;

  AnnotCalloutMultiLine a(/*x1*/ 0.0, /*y1*/ 0.0,
                          /*x2*/ 0.0, /*y2*/ 0.0,
                          /*x3*/ 0.0, /*y3*/ y3);

  AnnotCalloutMultiLine b(/*x1*/ -100.0, /*y1*/ 200.0,
                          /*x2*/ 300.0,  /*y2*/ -400.0,
                          /*x3*/ 500.0,  /*y3*/ y3);

  EXPECT_DOUBLE_EQ(a.getY3(), y3);
  EXPECT_DOUBLE_EQ(b.getY3(), y3);
}

} // namespace