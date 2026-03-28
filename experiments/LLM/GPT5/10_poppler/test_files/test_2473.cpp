// poppler-quadrilateral-copy-test_2473.cc
//
// Unit tests for poppler_quadrilateral_copy() from poppler-page.cc
//
// Constraints honored:
// - Treat implementation as black box (test only observable behavior)
// - No private/internal state access
// - Boundary + error cases (nullptr)
// - Single file, GoogleTest
//
// NOTE: This test assumes GLib is available (for g_test, g_log, g_slice, etc.)
// and that poppler-page.h is reachable in include paths.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-page.h"

// Function under test (declared here to avoid needing additional headers)
PopplerQuadrilateral *poppler_quadrilateral_copy(PopplerQuadrilateral *quad);
}

namespace {

class PopplerQuadrilateralCopyTest_2473 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Ensure GLib's test/logging is initialized enough for g_test_expect_message.
    // g_test_init expects argc/argv pointers; provide dummies.
    int argc = 1;
    char prog[] = "poppler_quadrilateral_copy_test";
    char *argv[] = {prog, nullptr};
    char **pargv = argv;
    g_test_init(&argc, &pargv, nullptr);
  }
};

static PopplerQuadrilateral MakeQuad(double base = 0.0) {
  PopplerQuadrilateral q;
  // PopplerPoint fields are public; fill deterministic values.
  q.p1.x = base + 1.0;
  q.p1.y = base + 2.0;
  q.p2.x = base + 3.0;
  q.p2.y = base + 4.0;
  q.p3.x = base + 5.0;
  q.p3.y = base + 6.0;
  q.p4.x = base + 7.0;
  q.p4.y = base + 8.0;
  return q;
}

static void ExpectQuadEq(const PopplerQuadrilateral &a, const PopplerQuadrilateral &b) {
  EXPECT_DOUBLE_EQ(a.p1.x, b.p1.x);
  EXPECT_DOUBLE_EQ(a.p1.y, b.p1.y);
  EXPECT_DOUBLE_EQ(a.p2.x, b.p2.x);
  EXPECT_DOUBLE_EQ(a.p2.y, b.p2.y);
  EXPECT_DOUBLE_EQ(a.p3.x, b.p3.x);
  EXPECT_DOUBLE_EQ(a.p3.y, b.p3.y);
  EXPECT_DOUBLE_EQ(a.p4.x, b.p4.x);
  EXPECT_DOUBLE_EQ(a.p4.y, b.p4.y);
}

TEST_F(PopplerQuadrilateralCopyTest_2473, NullptrReturnsNullAndEmitsCritical_2473) {
  // The function uses g_return_val_if_fail(quad != nullptr, NULL).
  // Observable behavior:
  // - Return value is NULL
  // - GLib critical is logged
  //
  // Match message pattern used by g_return_* macros: "*assertion*failed*"
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*assertion*failed*");

  PopplerQuadrilateral *out = poppler_quadrilateral_copy(nullptr);
  EXPECT_EQ(out, nullptr);

  g_test_assert_expected_messages();
}

TEST_F(PopplerQuadrilateralCopyTest_2473, CopiesAllPointsForValidInput_2473) {
  PopplerQuadrilateral in = MakeQuad(0.0);

  PopplerQuadrilateral *out = poppler_quadrilateral_copy(&in);
  ASSERT_NE(out, nullptr);

  // Content should match input (deep copy of POD struct)
  ExpectQuadEq(*out, in);

  // Cleanup: allocation is via g_slice_dup, so free via g_slice_free.
  g_slice_free(PopplerQuadrilateral, out);
}

TEST_F(PopplerQuadrilateralCopyTest_2473, ReturnedPointerIsDifferentFromInputAddress_2473) {
  PopplerQuadrilateral in = MakeQuad(10.0);

  PopplerQuadrilateral *out = poppler_quadrilateral_copy(&in);
  ASSERT_NE(out, nullptr);

  // Observable: should not alias the original object on stack.
  EXPECT_NE(out, &in);

  // Still matches contents.
  ExpectQuadEq(*out, in);

  g_slice_free(PopplerQuadrilateral, out);
}

TEST_F(PopplerQuadrilateralCopyTest_2473, CopyIsIndependentFromSubsequentInputMutation_2473) {
  PopplerQuadrilateral in = MakeQuad(100.0);

  PopplerQuadrilateral *out = poppler_quadrilateral_copy(&in);
  ASSERT_NE(out, nullptr);

  PopplerQuadrilateral snapshot = *out;

  // Mutate input after copy; output should remain unchanged if it is a true copy.
  in.p1.x = -999.0;
  in.p2.y = -888.0;
  in.p3.x = -777.0;
  in.p4.y = -666.0;

  ExpectQuadEq(*out, snapshot);

  g_slice_free(PopplerQuadrilateral, out);
}

TEST_F(PopplerQuadrilateralCopyTest_2473, MultipleCopiesFromSameInputAreDistinctAndEqual_2473) {
  PopplerQuadrilateral in = MakeQuad(3.14);

  PopplerQuadrilateral *out1 = poppler_quadrilateral_copy(&in);
  PopplerQuadrilateral *out2 = poppler_quadrilateral_copy(&in);

  ASSERT_NE(out1, nullptr);
  ASSERT_NE(out2, nullptr);

  // Both should be equal in content to input and to each other.
  ExpectQuadEq(*out1, in);
  ExpectQuadEq(*out2, in);
  ExpectQuadEq(*out1, *out2);

  // But should be different allocations (distinct pointers).
  EXPECT_NE(out1, out2);

  g_slice_free(PopplerQuadrilateral, out1);
  g_slice_free(PopplerQuadrilateral, out2);
}

}  // namespace