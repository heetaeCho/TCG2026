// TEST_ID: 412
// File: GfxDeviceGrayColorSpace_test.cpp
//
// Unit tests for GfxDeviceGrayColorSpace (Poppler: GfxState.h)
//
// Constraints honored:
// - Treat implementation as black box (no internal assumptions)
// - Test only via public interface / observable behavior
// - No private state access
// - Include normal + boundary + (observable) error cases
//
// NOTE: The provided partial code guarantees getNComps() returns 1.
// Other methods are declared in the “Known or Inferred Dependencies” section,
// but their behavior is not specified here, so tests focus on what is observable
// from the given partial implementation.

#include <gtest/gtest.h>

// Include the real header from your project layout.
#include "poppler/GfxState.h"

namespace {

class GfxDeviceGrayColorSpaceTest_412 : public ::testing::Test {
protected:
  // Keep as pointer to avoid assuming copy/move behavior.
  GfxDeviceGrayColorSpace *cs = nullptr;

  void SetUp() override { cs = new GfxDeviceGrayColorSpace(); }
  void TearDown() override {
    delete cs;
    cs = nullptr;
  }
};

TEST_F(GfxDeviceGrayColorSpaceTest_412, GetNComps_ReturnsOne_412) {
  ASSERT_NE(cs, nullptr);
  EXPECT_EQ(cs->getNComps(), 1);
}

TEST_F(GfxDeviceGrayColorSpaceTest_412, GetNComps_IsStableAcrossRepeatedCalls_412) {
  ASSERT_NE(cs, nullptr);
  // Boundary-ish: multiple invocations should remain consistent.
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(cs->getNComps(), 1);
  }
}

TEST_F(GfxDeviceGrayColorSpaceTest_412, GetNComps_WorksThroughBasePointer_412) {
  ASSERT_NE(cs, nullptr);

  // Verify override behavior is visible via the base type.
  // This is an observable interface property (polymorphic dispatch).
  GfxColorSpace *base = cs;
  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getNComps(), 1);
}

// Error/exceptional cases:
// getNComps() is const and returns an int; no error channel is visible.
// We avoid UB such as calling methods on nullptr or deleted objects.

}  // namespace