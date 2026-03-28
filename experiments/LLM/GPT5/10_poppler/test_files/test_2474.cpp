// File: poppler-quadrilateral-free-test_2474.cc
//
// Unit tests for:
//   void poppler_quadrilateral_free(PopplerQuadrilateral *quad);
//
// Constraints honored:
// - Treat implementation as black box (no internal logic assumptions beyond observable behavior).
// - No private state access.
// - Include normal + boundary (NULL) cases.
// - No mocks needed (no external collaborators).
//
// Note: This test uses GLib g_slice_alloc0/g_slice_new to obtain a compatible allocation
// for g_slice_free used by poppler_quadrilateral_free.

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-page.h"

// Function under test (provided by the codebase)
extern "C" void poppler_quadrilateral_free(PopplerQuadrilateral *quad);

namespace {

class PopplerQuadrilateralFreeTest_2474 : public ::testing::Test {};

TEST_F(PopplerQuadrilateralFreeTest_2474, FreesValidSliceAllocatedQuadrilateral_2474) {
  // Normal operation: freeing a valid, slice-allocated object should not crash.
  PopplerQuadrilateral *quad = g_slice_new0(PopplerQuadrilateral);
  ASSERT_NE(quad, nullptr);

  EXPECT_NO_THROW({
    poppler_quadrilateral_free(quad);
  });
}

TEST_F(PopplerQuadrilateralFreeTest_2474, FreeNullPointerIsNoOpOrDoesNotCrash_2474) {
  // Boundary / error-ish case: NULL input.
  // Observable requirement: should not crash the process.
  PopplerQuadrilateral *quad = nullptr;

  EXPECT_NO_THROW({
    poppler_quadrilateral_free(quad);
  });
}

TEST_F(PopplerQuadrilateralFreeTest_2474, FreesMultipleIndependentAllocations_2474) {
  // Normal operation: freeing multiple different objects should not crash.
  PopplerQuadrilateral *q1 = g_slice_new0(PopplerQuadrilateral);
  PopplerQuadrilateral *q2 = g_slice_new0(PopplerQuadrilateral);
  ASSERT_NE(q1, nullptr);
  ASSERT_NE(q2, nullptr);
  ASSERT_NE(q1, q2);

  EXPECT_NO_THROW(poppler_quadrilateral_free(q1));
  EXPECT_NO_THROW(poppler_quadrilateral_free(q2));
}

}  // namespace