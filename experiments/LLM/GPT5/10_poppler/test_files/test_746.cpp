// File: annotborder_test_746.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "Annot.h"

// These tests treat AnnotBorder as a black box and verify behavior only
// through its public interface (setWidth/getWidth) and virtual dispatch.

// AnnotBorder has a protected ctor, so we use a minimal derived type to
// instantiate it without re-implementing any AnnotBorder logic.
class TestableAnnotBorder_746 : public AnnotBorder {
public:
  TestableAnnotBorder_746() : AnnotBorder() {}
  ~TestableAnnotBorder_746() override = default;
};

class AnnotBorderTest_746 : public ::testing::Test {
protected:
  TestableAnnotBorder_746 border_;
};

TEST_F(AnnotBorderTest_746, SetWidthUpdatesGetWidth_ForTypicalPositiveValue_746) {
  border_.setWidth(1.25);
  EXPECT_DOUBLE_EQ(border_.getWidth(), 1.25);
}

TEST_F(AnnotBorderTest_746, SetWidthUpdatesGetWidth_WhenSetToZero_746) {
  border_.setWidth(0.0);
  EXPECT_DOUBLE_EQ(border_.getWidth(), 0.0);
}

TEST_F(AnnotBorderTest_746, SetWidthUpdatesGetWidth_ForNegativeValue_746) {
  border_.setWidth(-3.5);
  EXPECT_DOUBLE_EQ(border_.getWidth(), -3.5);
}

TEST_F(AnnotBorderTest_746, SetWidthUpdatesGetWidth_ForVeryLargeFiniteValue_746) {
  const double kLarge = 1e300; // finite (not inf)
  ASSERT_TRUE(std::isfinite(kLarge));

  border_.setWidth(kLarge);
  EXPECT_DOUBLE_EQ(border_.getWidth(), kLarge);
}

TEST_F(AnnotBorderTest_746, SetWidthViaBasePointerUsesVirtualDispatch_746) {
  AnnotBorder* basePtr = &border_;
  basePtr->setWidth(2.0);
  EXPECT_DOUBLE_EQ(border_.getWidth(), 2.0);
}

TEST_F(AnnotBorderTest_746, SetWidthAcceptsNaN_AndGetWidthIsNaN_746) {
  const double kNaN = std::numeric_limits<double>::quiet_NaN();
  ASSERT_TRUE(std::isnan(kNaN));

  border_.setWidth(kNaN);

  // Observable behavior: getWidth() reflects what was set; for NaN we can only
  // reliably check via isnan.
  EXPECT_TRUE(std::isnan(border_.getWidth()));
}

TEST_F(AnnotBorderTest_746, SetWidthAcceptsInfinity_AndGetWidthIsInfinity_746) {
  const double kInf = std::numeric_limits<double>::infinity();
  ASSERT_TRUE(std::isinf(kInf));

  border_.setWidth(kInf);
  EXPECT_TRUE(std::isinf(border_.getWidth()));
  EXPECT_GT(border_.getWidth(), 0.0);
}

TEST_F(AnnotBorderTest_746, SetWidthOverwritesPreviousValue_LastWriteWins_746) {
  border_.setWidth(0.5);
  EXPECT_DOUBLE_EQ(border_.getWidth(), 0.5);

  border_.setWidth(4.75);
  EXPECT_DOUBLE_EQ(border_.getWidth(), 4.75);
}