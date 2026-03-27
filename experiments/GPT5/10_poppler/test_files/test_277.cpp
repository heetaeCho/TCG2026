// TEST_ID = 277
//
// Unit tests for LinkDest::getTop()
// File: LinkDest_getTop_277_test.cpp

#include <gtest/gtest.h>

#include "Link.h"    // LinkDest
#include "Object.h"  // Array, Object (Poppler core)

namespace {

constexpr double kEps_277 = 1e-12;

// Helper: build an Array that represents a PDF destination.
// Common PDF forms include:
//   [page /XYZ left top zoom]
//   [page /FitR left bottom right top]
// We only assert behavior that is observable through the public interface:
//  - dest.isOk()
//  - dest.getTop()
static Array MakeDestArray_XYZ_277(int pageNum, double left, double top, double zoom) {
  Array a(nullptr);

  Object o1;
  o1.initInt(pageNum);
  a.add(std::move(o1));

  Object o2;
  o2.initName("XYZ");
  a.add(std::move(o2));

  Object o3;
  o3.initReal(left);
  a.add(std::move(o3));

  Object o4;
  o4.initReal(top);
  a.add(std::move(o4));

  Object o5;
  o5.initReal(zoom);
  a.add(std::move(o5));

  return a;
}

static Array MakeDestArray_FitR_277(int pageNum, double left, double bottom, double right, double top) {
  Array a(nullptr);

  Object o1;
  o1.initInt(pageNum);
  a.add(std::move(o1));

  Object o2;
  o2.initName("FitR");
  a.add(std::move(o2));

  Object o3;
  o3.initReal(left);
  a.add(std::move(o3));

  Object o4;
  o4.initReal(bottom);
  a.add(std::move(o4));

  Object o5;
  o5.initReal(right);
  a.add(std::move(o5));

  Object o6;
  o6.initReal(top);
  a.add(std::move(o6));

  return a;
}

}  // namespace

class LinkDestGetTopTest_277 : public ::testing::Test {};

TEST_F(LinkDestGetTopTest_277, ReturnsTopForValidXYZDestination_277) {
  const double expectedTop = 456.25;
  Array a = MakeDestArray_XYZ_277(/*pageNum=*/1, /*left=*/12.5, /*top=*/expectedTop, /*zoom=*/1.0);

  LinkDest dest(a);
  ASSERT_TRUE(dest.isOk());

  EXPECT_NEAR(dest.getTop(), expectedTop, kEps_277);
}

TEST_F(LinkDestGetTopTest_277, ReturnsTopForValidFitRDestination_277) {
  const double expectedTop = 999.0;
  Array a = MakeDestArray_FitR_277(/*pageNum=*/2, /*left=*/10.0, /*bottom=*/20.0, /*right=*/300.0,
                                  /*top=*/expectedTop);

  LinkDest dest(a);
  ASSERT_TRUE(dest.isOk());

  EXPECT_NEAR(dest.getTop(), expectedTop, kEps_277);
}

TEST_F(LinkDestGetTopTest_277, HandlesBoundaryTopValuesWhenOk_277) {
  {
    const double expectedTop = 0.0;
    Array a = MakeDestArray_XYZ_277(/*pageNum=*/1, /*left=*/0.0, /*top=*/expectedTop, /*zoom=*/1.0);
    LinkDest dest(a);
    ASSERT_TRUE(dest.isOk());
    EXPECT_NEAR(dest.getTop(), expectedTop, kEps_277);
  }
  {
    const double expectedTop = -12345.6789;  // negative coordinate boundary
    Array a = MakeDestArray_XYZ_277(/*pageNum=*/1, /*left=*/0.0, /*top=*/expectedTop, /*zoom=*/1.0);
    LinkDest dest(a);
    ASSERT_TRUE(dest.isOk());
    EXPECT_NEAR(dest.getTop(), expectedTop, kEps_277);
  }
  {
    const double expectedTop = 1e12;  // very large coordinate boundary
    Array a = MakeDestArray_XYZ_277(/*pageNum=*/1, /*left=*/0.0, /*top=*/expectedTop, /*zoom=*/1.0);
    LinkDest dest(a);
    ASSERT_TRUE(dest.isOk());
    EXPECT_NEAR(dest.getTop(), expectedTop, 1e-6);  // looser epsilon for huge magnitude
  }
}

TEST_F(LinkDestGetTopTest_277, InvalidArrayIsNotOkAndGetTopIsCallable_277) {
  // Minimal/invalid destination array (missing required elements)
  Array a(nullptr);

  LinkDest dest(a);
  EXPECT_FALSE(dest.isOk());

  // We do not assume what value getTop() returns in an invalid state,
  // only that it is callable (no crash) and returns a double.
  EXPECT_NO_THROW({
    volatile double t = dest.getTop();
    (void)t;
  });
}