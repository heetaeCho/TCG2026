// File: poppler-rectangle-new-from-pdf-rectangle-test_2463.cc

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/PDFRectangle.h"

// poppler glib headers (PopplerRectangle is a public struct with x1,y1,x2,y2)
extern "C" {
#include <glib.h>
#include <poppler.h>
}

// Function under test (implemented in poppler-page.cc)
extern "C" PopplerRectangle *poppler_rectangle_new_from_pdf_rectangle(const PDFRectangle *rect);

namespace {

class PopplerRectangleNewFromPdfRectangleTest_2463 : public ::testing::Test {
protected:
  static void FreeRect(PopplerRectangle *r) {
    // In Poppler GLib, rectangles are typically heap-allocated and freed with g_free().
    // Use g_free to avoid depending on additional helper APIs.
    g_free(r);
  }
};

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, CopiesAllCoordinates_NormalValues_2463) {
  const PDFRectangle in(1.25, -2.5, 100.0, 42.75);

  PopplerRectangle *out = poppler_rectangle_new_from_pdf_rectangle(&in);
  ASSERT_NE(out, nullptr);

  EXPECT_DOUBLE_EQ(out->x1, in.x1);
  EXPECT_DOUBLE_EQ(out->y1, in.y1);
  EXPECT_DOUBLE_EQ(out->x2, in.x2);
  EXPECT_DOUBLE_EQ(out->y2, in.y2);

  FreeRect(out);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, HandlesAllZeros_Boundary_2463) {
  const PDFRectangle in(0.0, 0.0, 0.0, 0.0);

  PopplerRectangle *out = poppler_rectangle_new_from_pdf_rectangle(&in);
  ASSERT_NE(out, nullptr);

  EXPECT_DOUBLE_EQ(out->x1, 0.0);
  EXPECT_DOUBLE_EQ(out->y1, 0.0);
  EXPECT_DOUBLE_EQ(out->x2, 0.0);
  EXPECT_DOUBLE_EQ(out->y2, 0.0);

  FreeRect(out);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, HandlesNegativeCoordinates_Boundary_2463) {
  const PDFRectangle in(-10.0, -20.5, -0.125, -9999.0);

  PopplerRectangle *out = poppler_rectangle_new_from_pdf_rectangle(&in);
  ASSERT_NE(out, nullptr);

  EXPECT_DOUBLE_EQ(out->x1, in.x1);
  EXPECT_DOUBLE_EQ(out->y1, in.y1);
  EXPECT_DOUBLE_EQ(out->x2, in.x2);
  EXPECT_DOUBLE_EQ(out->y2, in.y2);

  FreeRect(out);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, HandlesLargeMagnitudeCoordinates_Boundary_2463) {
  const double big = std::numeric_limits<double>::max() / 4.0;
  const PDFRectangle in(big, -big, big / 2.0, -big / 2.0);

  PopplerRectangle *out = poppler_rectangle_new_from_pdf_rectangle(&in);
  ASSERT_NE(out, nullptr);

  EXPECT_DOUBLE_EQ(out->x1, in.x1);
  EXPECT_DOUBLE_EQ(out->y1, in.y1);
  EXPECT_DOUBLE_EQ(out->x2, in.x2);
  EXPECT_DOUBLE_EQ(out->y2, in.y2);

  FreeRect(out);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, CopiesSpecialFloatingPointValues_NaNAndInf_2463) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  const double inf = std::numeric_limits<double>::infinity();

  const PDFRectangle in(nan, inf, -inf, 3.0);

  PopplerRectangle *out = poppler_rectangle_new_from_pdf_rectangle(&in);
  ASSERT_NE(out, nullptr);

  EXPECT_TRUE(std::isnan(out->x1));
  EXPECT_TRUE(std::isinf(out->y1));
  EXPECT_GT(out->y1, 0.0);

  EXPECT_TRUE(std::isinf(out->x2));
  EXPECT_LT(out->x2, 0.0);

  EXPECT_DOUBLE_EQ(out->y2, 3.0);

  FreeRect(out);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, ReturnedRectangleIsIndependentFromInputAfterCall_2463) {
  PDFRectangle in(1.0, 2.0, 3.0, 4.0);

  PopplerRectangle *out = poppler_rectangle_new_from_pdf_rectangle(&in);
  ASSERT_NE(out, nullptr);

  // Mutate input after creation; output should remain as originally copied.
  in.x1 = 10.0;
  in.y1 = 20.0;
  in.x2 = 30.0;
  in.y2 = 40.0;

  EXPECT_DOUBLE_EQ(out->x1, 1.0);
  EXPECT_DOUBLE_EQ(out->y1, 2.0);
  EXPECT_DOUBLE_EQ(out->x2, 3.0);
  EXPECT_DOUBLE_EQ(out->y2, 4.0);

  FreeRect(out);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, ReturnsDistinctAllocationsForSeparateCalls_2463) {
  const PDFRectangle in(5.0, 6.0, 7.0, 8.0);

  PopplerRectangle *a = poppler_rectangle_new_from_pdf_rectangle(&in);
  PopplerRectangle *b = poppler_rectangle_new_from_pdf_rectangle(&in);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_NE(a, b);

  // Both should carry identical observable data.
  EXPECT_DOUBLE_EQ(a->x1, in.x1);
  EXPECT_DOUBLE_EQ(a->y1, in.y1);
  EXPECT_DOUBLE_EQ(a->x2, in.x2);
  EXPECT_DOUBLE_EQ(a->y2, in.y2);

  EXPECT_DOUBLE_EQ(b->x1, in.x1);
  EXPECT_DOUBLE_EQ(b->y1, in.y1);
  EXPECT_DOUBLE_EQ(b->x2, in.x2);
  EXPECT_DOUBLE_EQ(b->y2, in.y2);

  FreeRect(a);
  FreeRect(b);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, NullInputPointer_DeathTest_2463) {
  // Observable error case: the interface takes a raw pointer with no documented nullability.
  // If implementation dereferences null, it should crash; this is still observable behavior.
  ASSERT_DEATH(
      {
        volatile PopplerRectangle *r = poppler_rectangle_new_from_pdf_rectangle(nullptr);
        (void)r;
      },
      "");
}

} // namespace