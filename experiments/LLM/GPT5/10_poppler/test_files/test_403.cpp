// TEST_ID: 403
// File: gfxcolorspace_usegetcmykline_test_403.cpp

#include <gtest/gtest.h>

#include "GfxState.h"

namespace {

class GfxColorSpaceTest_403 : public ::testing::Test {};

// A derived class to verify virtual dispatch (observable behavior via interface).
class DerivedGfxColorSpace_403 : public GfxColorSpace {
public:
  bool useGetCMYKLine() const override { return true; }
};

TEST_F(GfxColorSpaceTest_403, DefaultImplementationReturnsFalse_403) {
  const GfxColorSpace cs;
  EXPECT_FALSE(cs.useGetCMYKLine());
}

TEST_F(GfxColorSpaceTest_403, VirtualDispatchViaBasePointer_403) {
  const DerivedGfxColorSpace_403 derived;
  const GfxColorSpace *basePtr = &derived;

  // Observable behavior: the overridden method should be called through base ptr.
  EXPECT_TRUE(basePtr->useGetCMYKLine());
}

TEST_F(GfxColorSpaceTest_403, VirtualDispatchViaBaseReference_403) {
  const DerivedGfxColorSpace_403 derived;
  const GfxColorSpace &baseRef = derived;

  EXPECT_TRUE(baseRef.useGetCMYKLine());
}

TEST_F(GfxColorSpaceTest_403, CanBeCalledOnConstObject_403) {
  const GfxColorSpace cs;
  // Compile-time check (const-qualified member). Runtime expectation: still false.
  EXPECT_FALSE(cs.useGetCMYKLine());
}

} // namespace