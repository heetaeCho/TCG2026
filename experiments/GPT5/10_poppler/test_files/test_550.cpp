// ============================================================================
// Unit tests for GfxSubpath::isClosed
// File: GfxSubpath_isClosed_550_test.cpp
//
// Constraints honored:
// - Treat implementation as black box (no internal state access)
// - Use only public interface
// - Cover normal, boundary, and observable error-ish cases (where possible)
// ============================================================================

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxSubpathTest_550 : public ::testing::Test {};

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, NewSubpath_IsInitiallyOpen_550) {
  GfxSubpath sp(0.0, 0.0);

  // Observable behavior: newly constructed subpath should not be closed.
  // (If the real implementation differs, this test will catch it.)
  EXPECT_FALSE(sp.isClosed());
}

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, Close_MakesSubpathClosed_550) {
  GfxSubpath sp(1.0, 2.0);

  sp.close();

  EXPECT_TRUE(sp.isClosed());
}

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, Close_IsIdempotent_550) {
  GfxSubpath sp(-3.0, 4.5);

  sp.close();
  EXPECT_TRUE(sp.isClosed());

  // Calling close again should keep it closed (no observable regression).
  sp.close();
  EXPECT_TRUE(sp.isClosed());
}

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, Operations_DoNotImplicitlyClose_550) {
  GfxSubpath sp(0.0, 0.0);

  // Perform typical operations without calling close().
  sp.lineTo(10.0, 10.0);
  sp.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
  sp.offset(5.0, -5.0);

  // Should remain open unless explicitly closed.
  EXPECT_FALSE(sp.isClosed());
}

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, AfterClose_OtherOperationsKeepClosed_550) {
  GfxSubpath sp(0.0, 0.0);

  sp.close();
  ASSERT_TRUE(sp.isClosed());

  // After being closed, further geometry operations should not "re-open" it.
  sp.offset(1.0, 1.0);
  EXPECT_TRUE(sp.isClosed());

  sp.lineTo(2.0, 2.0);
  EXPECT_TRUE(sp.isClosed());

  sp.curveTo(0.0, 0.0, 1.0, 0.0, 1.0, 1.0);
  EXPECT_TRUE(sp.isClosed());
}

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, Copy_PreservesClosedState_Open_550) {
  GfxSubpath sp(0.0, 0.0);
  ASSERT_FALSE(sp.isClosed());

  GfxSubpath *copy = sp.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_FALSE(copy->isClosed());

  delete copy;
}

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, Copy_PreservesClosedState_Closed_550) {
  GfxSubpath sp(0.0, 0.0);
  sp.close();
  ASSERT_TRUE(sp.isClosed());

  GfxSubpath *copy = sp.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->isClosed());

  delete copy;
}

// TEST_ID = 550
TEST_F(GfxSubpathTest_550, ExtremeCoordinates_DoNotAffectClosedFlag_550) {
  // Boundary-ish: large magnitude values.
  GfxSubpath sp(1e308, -1e308);

  EXPECT_FALSE(sp.isClosed());

  sp.lineTo(-1e308, 1e308);
  EXPECT_FALSE(sp.isClosed());

  sp.close();
  EXPECT_TRUE(sp.isClosed());
}

} // namespace