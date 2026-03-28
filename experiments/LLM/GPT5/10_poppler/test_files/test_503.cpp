// GfxShading_getColorSpace_503_test.cpp
#include <gtest/gtest.h>

#include "GfxState.h"

class GfxShadingTest_503 : public ::testing::Test {};

// Normal operation: calling getColorSpace() on a freshly-constructed object should be safe.
// We only assert observable behavior (no crash, and pointer consistency across repeated calls).
TEST_F(GfxShadingTest_503, GetColorSpace_DefaultConstruction_NoCrashAndStablePointer_503)
{
  // Use an arbitrary shading type value; we do not assume any specific meaning.
  GfxShading shading(/*typeA=*/0);

  GfxColorSpace *cs1 = shading.getColorSpace();
  GfxColorSpace *cs2 = shading.getColorSpace();

  // Observable requirement we can safely assert for a getter: repeated calls should be consistent
  // for the same object (regardless of whether the pointer is null or non-null).
  EXPECT_EQ(cs1, cs2);
}

// Boundary-ish: calling getColorSpace() many times should remain safe and consistent.
TEST_F(GfxShadingTest_503, GetColorSpace_RepeatedCalls_RemainConsistent_503)
{
  GfxShading shading(/*typeA=*/1);

  GfxColorSpace *first = shading.getColorSpace();
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(first, shading.getColorSpace());
  }
}

// Copy-like construction (from pointer): ensure getColorSpace() is callable on both objects.
// We do NOT assume whether the color space is shared, deep-copied, or null.
TEST_F(GfxShadingTest_503, GetColorSpace_AfterPointerCopyConstruction_NoCrash_503)
{
  GfxShading original(/*typeA=*/2);
  (void)original.getColorSpace(); // Should be callable.

  GfxShading copy(&original);
  GfxColorSpace *origCs = original.getColorSpace();
  GfxColorSpace *copyCs = copy.getColorSpace();

  // Only assert that the getter returns a well-formed pointer value (possibly null) and that
  // it is stable per-object across repeated calls.
  EXPECT_EQ(origCs, original.getColorSpace());
  EXPECT_EQ(copyCs, copy.getColorSpace());
}

// Boundary: getter should be safe even when the object is created/destroyed in a tight scope.
TEST_F(GfxShadingTest_503, GetColorSpace_ObjectLifetime_SafeToCallBeforeDestruction_503)
{
  for (int i = 0; i < 100; ++i) {
    GfxShading shading(/*typeA=*/i);
    GfxColorSpace *cs = shading.getColorSpace();
    EXPECT_EQ(cs, shading.getColorSpace());
  }
}