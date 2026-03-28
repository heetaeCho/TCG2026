// File: ./TestProjects/poppler/glib/poppler-page-image_draw_decide_cb-test.cc
//
// Unit tests for:
//   static bool image_draw_decide_cb(int image_id, void *data)
//
// Constraints respected:
// - Treat as black-box: only test observable return value given inputs.
// - No access to internal state.
// - No re-implementation of production logic beyond invoking the function.
// - Boundary + error-ish cases (as observable via interface).

#include <gtest/gtest.h>

#include <glib.h> // GPOINTER_TO_INT, GINT_TO_POINTER

// The function under test lives in poppler-page.cc and is declared static there.
// In this codebase's unit-test pattern, we include the .cc to access static helpers.
#include "poppler-page.cc"

namespace {

class ImageDrawDecideCbTest_2449 : public ::testing::Test {};

TEST_F(ImageDrawDecideCbTest_2449, ReturnsTrueWhenImageIdMatchesDataPointerInt_2449) {
  const int kId = 7;
  void* data = GINT_TO_POINTER(kId);

  EXPECT_TRUE(image_draw_decide_cb(kId, data));
}

TEST_F(ImageDrawDecideCbTest_2449, ReturnsFalseWhenImageIdDoesNotMatchDataPointerInt_2449) {
  void* data = GINT_TO_POINTER(7);

  EXPECT_FALSE(image_draw_decide_cb(8, data));
}

TEST_F(ImageDrawDecideCbTest_2449, HandlesZeroIdAndNullDataMatch_2449) {
  // In GLib, GPOINTER_TO_INT(NULL) yields 0 on typical platforms.
  // This is an observable behavior via GLib macro usage and is safe to validate here.
  EXPECT_TRUE(image_draw_decide_cb(0, nullptr));
}

TEST_F(ImageDrawDecideCbTest_2449, ZeroIdDoesNotMatchNonZeroData_2449) {
  void* data = GINT_TO_POINTER(1);
  EXPECT_FALSE(image_draw_decide_cb(0, data));
}

TEST_F(ImageDrawDecideCbTest_2449, NegativeIdMatchesWhenDataEncodesSameNegativeInt_2449) {
  const int kNeg = -123;
  void* data = GINT_TO_POINTER(kNeg);

  EXPECT_TRUE(image_draw_decide_cb(kNeg, data));
}

TEST_F(ImageDrawDecideCbTest_2449, NegativeIdDoesNotMatchDifferentNegativeInt_2449) {
  void* data = GINT_TO_POINTER(-5);
  EXPECT_FALSE(image_draw_decide_cb(-6, data));
}

TEST_F(ImageDrawDecideCbTest_2449, LargePositiveIdRoundTripThroughGlibPointerMacros_2449) {
  // Use a large-ish value that should still round-trip with GINT_TO_POINTER/GPOINTER_TO_INT
  // on the target platform used by this project. We assert based on observable behavior
  // of these macros in this environment.
  const int kLarge = 1 << 20; // 1048576
  void* data = GINT_TO_POINTER(kLarge);

  EXPECT_TRUE(image_draw_decide_cb(kLarge, data));
  EXPECT_FALSE(image_draw_decide_cb(kLarge + 1, data));
}

TEST_F(ImageDrawDecideCbTest_2449, IgnoresPointerIdentityOnlyUsesIntConversion_2449) {
  // Two different pointers can map to the same int after GPOINTER_TO_INT conversion in some cases.
  // Here we simply validate that the callback's decision is fully determined by the int value
  // encoded in 'data' (as observable through behavior with GINT_TO_POINTER).
  const int kId = 42;
  void* data1 = GINT_TO_POINTER(kId);
  void* data2 = GINT_TO_POINTER(kId);

  // Even if data1 and data2 are the same (or not), behavior should match for same encoded int.
  EXPECT_TRUE(image_draw_decide_cb(kId, data1));
  EXPECT_TRUE(image_draw_decide_cb(kId, data2));
  EXPECT_FALSE(image_draw_decide_cb(kId + 1, data1));
  EXPECT_FALSE(image_draw_decide_cb(kId + 1, data2));
}

}  // namespace