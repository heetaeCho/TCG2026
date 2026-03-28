// TEST_ID: 401
// File: gfxcolorspace_usegetrgbline_test_401.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"  // Adjust include path if needed

namespace {

class GfxColorSpaceTest_401 : public ::testing::Test {};

// A derived type to verify virtual dispatch via base pointers/references.
class AlwaysUseRGBLineColorSpace_401 : public GfxColorSpace {
public:
  bool useGetRGBLine() const override { return true; }
};

// Another derived type to verify overriding to false still behaves as expected.
class NeverUseRGBLineColorSpace_401 : public GfxColorSpace {
public:
  bool useGetRGBLine() const override { return false; }
};

} // namespace

TEST_F(GfxColorSpaceTest_401, DefaultImplementationReturnsFalse_401) {
  GfxColorSpace cs;
  EXPECT_FALSE(cs.useGetRGBLine());
}

TEST_F(GfxColorSpaceTest_401, WorksThroughConstReference_401) {
  const GfxColorSpace cs;
  EXPECT_FALSE(cs.useGetRGBLine());
}

TEST_F(GfxColorSpaceTest_401, VirtualDispatchReturnsDerivedOverrideTrue_401) {
  AlwaysUseRGBLineColorSpace_401 derived;
  const GfxColorSpace &baseRef = derived;

  EXPECT_TRUE(baseRef.useGetRGBLine());
}

TEST_F(GfxColorSpaceTest_401, VirtualDispatchReturnsDerivedOverrideFalse_401) {
  NeverUseRGBLineColorSpace_401 derived;
  const GfxColorSpace *basePtr = &derived;

  ASSERT_NE(basePtr, nullptr);
  EXPECT_FALSE(basePtr->useGetRGBLine());
}

TEST_F(GfxColorSpaceTest_401, RepeatedCallsAreConsistentForSameObject_401) {
  GfxColorSpace cs;
  const bool first = cs.useGetRGBLine();
  const bool second = cs.useGetRGBLine();
  const bool third = cs.useGetRGBLine();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_FALSE(first);
}