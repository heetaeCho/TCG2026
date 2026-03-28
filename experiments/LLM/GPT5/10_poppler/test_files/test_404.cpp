// TEST_ID: 404
// File: gfxcolorspace_useGetDeviceNLine_test_404.cpp
//
// Unit tests for GfxColorSpace::useGetDeviceNLine().
//
// Notes:
// - These tests treat GfxColorSpace as a black box and only validate observable behavior
//   through the public virtual interface.
// - Adjust the include path below to match your build setup.

#include <gtest/gtest.h>

#include "poppler/GfxState.h"  // or "GfxState.h"

// ---- Test helpers (external collaborators / derived types) ----

namespace {

class GfxColorSpaceAlwaysTrue final : public GfxColorSpace {
public:
  bool useGetDeviceNLine() const override { return true; }
};

class GfxColorSpaceAlwaysFalse final : public GfxColorSpace {
public:
  bool useGetDeviceNLine() const override { return false; }
};

} // namespace

// ---- Tests ----

TEST(GfxColorSpaceTest_404, DefaultImplementationReturnsFalse_404) {
  GfxColorSpace cs;
  EXPECT_FALSE(cs.useGetDeviceNLine());
}

TEST(GfxColorSpaceTest_404, VirtualDispatchViaBasePointerCallsOverrideTrue_404) {
  GfxColorSpaceAlwaysTrue derived;
  const GfxColorSpace *basePtr = &derived;

  EXPECT_TRUE(basePtr->useGetDeviceNLine());
}

TEST(GfxColorSpaceTest_404, VirtualDispatchViaBaseReferenceCallsOverrideTrue_404) {
  GfxColorSpaceAlwaysTrue derived;
  const GfxColorSpace &baseRef = derived;

  EXPECT_TRUE(baseRef.useGetDeviceNLine());
}

TEST(GfxColorSpaceTest_404, VirtualDispatchViaBasePointerCallsOverrideFalse_404) {
  GfxColorSpaceAlwaysFalse derived;
  const GfxColorSpace *basePtr = &derived;

  EXPECT_FALSE(basePtr->useGetDeviceNLine());
}

TEST(GfxColorSpaceTest_404, ConstCorrectnessCallableOnConstObject_404) {
  const GfxColorSpace cs;
  EXPECT_FALSE(cs.useGetDeviceNLine());
}

TEST(GfxColorSpaceTest_404, ConstCorrectnessCallableOnConstDerivedObject_404) {
  const GfxColorSpaceAlwaysTrue derived;
  EXPECT_TRUE(derived.useGetDeviceNLine());
}