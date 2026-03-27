// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for AnnotCalloutLine (partial interface)
// File under test: ./TestProjects/poppler/poppler/Annot.h
//
// Constraints respected:
// - Black-box testing: only public interface used (ctor + getters).
// - No private/protected access.
// - No re-implementation of internal logic.
// - No mocks needed (no external collaborators exposed by this interface).

#include <gtest/gtest.h>

#include "poppler/Annot.h"

namespace {

class AnnotCalloutLineTest_737 : public ::testing::Test {};

TEST_F(AnnotCalloutLineTest_737, GetX1ReturnsConstructorX1_737) {
  const double x1 = 1.25;
  const double y1 = -2.5;
  const double x2 = 3.75;
  const double y2 = 4.0;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getX1(), x1);
}

TEST_F(AnnotCalloutLineTest_737, GetY1ReturnsConstructorY1_737) {
  const double x1 = 10.0;
  const double y1 = 20.0;
  const double x2 = 30.0;
  const double y2 = 40.0;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getY1(), y1);
}

TEST_F(AnnotCalloutLineTest_737, GetX2ReturnsConstructorX2_737) {
  const double x1 = -1.0;
  const double y1 = -2.0;
  const double x2 = -3.0;
  const double y2 = -4.0;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getX2(), x2);
}

TEST_F(AnnotCalloutLineTest_737, GetY2ReturnsConstructorY2_737) {
  const double x1 = 0.0;
  const double y1 = 1.0;
  const double x2 = 2.0;
  const double y2 = 3.0;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getY2(), y2);
}

TEST_F(AnnotCalloutLineTest_737, GettersAreConsistentAcrossMultipleCalls_737) {
  const double x1 = 123.456;
  const double y1 = -654.321;
  const double x2 = 0.001;
  const double y2 = -0.002;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getX1(), x1);
  EXPECT_DOUBLE_EQ(line.getX1(), x1);

  EXPECT_DOUBLE_EQ(line.getY1(), y1);
  EXPECT_DOUBLE_EQ(line.getY1(), y1);

  EXPECT_DOUBLE_EQ(line.getX2(), x2);
  EXPECT_DOUBLE_EQ(line.getX2(), x2);

  EXPECT_DOUBLE_EQ(line.getY2(), y2);
  EXPECT_DOUBLE_EQ(line.getY2(), y2);
}

TEST_F(AnnotCalloutLineTest_737, BoundaryZerosAreReturned_737) {
  const double x1 = 0.0;
  const double y1 = 0.0;
  const double x2 = 0.0;
  const double y2 = 0.0;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getX1(), 0.0);
  EXPECT_DOUBLE_EQ(line.getY1(), 0.0);
  EXPECT_DOUBLE_EQ(line.getX2(), 0.0);
  EXPECT_DOUBLE_EQ(line.getY2(), 0.0);
}

TEST_F(AnnotCalloutLineTest_737, BoundaryNegativeAndPositiveExtremesAreReturned_737) {
  // Use large finite magnitudes (avoid INF/NaN assumptions).
  const double x1 = -1e308;
  const double y1 = 1e308;
  const double x2 = 1e-308;
  const double y2 = -1e-308;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getX1(), x1);
  EXPECT_DOUBLE_EQ(line.getY1(), y1);
  EXPECT_DOUBLE_EQ(line.getX2(), x2);
  EXPECT_DOUBLE_EQ(line.getY2(), y2);
}

TEST_F(AnnotCalloutLineTest_737, DoesNotThrowOnConstructionAndAccess_737) {
  // "Exceptional/error cases (if observable)": here, the observable contract is
  // simply that construction and getters are usable for typical finite values.
  EXPECT_NO_THROW({
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    (void)line.getX1();
    (void)line.getY1();
    (void)line.getX2();
    (void)line.getY2();
  });
}

}  // namespace