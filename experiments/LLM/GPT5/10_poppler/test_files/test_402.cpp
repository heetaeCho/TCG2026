// TEST_ID: 402
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// The interface under test (from provided partial code):
// class GfxColorSpace { public: virtual bool useGetGrayLine() const { return false; } };

namespace {

class GfxColorSpaceUseGetGrayLineTest_402 : public ::testing::Test {};

class TestColorSpaceDefault_402 : public GfxColorSpace {
  // Inherits default implementation.
};

class TestColorSpaceOverrideTrue_402 : public GfxColorSpace {
public:
  bool useGetGrayLine() const override { return true; }
};

class TestColorSpaceOverrideFalse_402 : public GfxColorSpace {
public:
  bool useGetGrayLine() const override { return false; }
};

} // namespace

TEST_F(GfxColorSpaceUseGetGrayLineTest_402, DefaultReturnsFalse_402) {
  TestColorSpaceDefault_402 cs;
  EXPECT_FALSE(cs.useGetGrayLine());
}

TEST_F(GfxColorSpaceUseGetGrayLineTest_402, PolymorphicCallDispatchesToOverrideTrue_402) {
  TestColorSpaceOverrideTrue_402 derived;
  const GfxColorSpace *basePtr = &derived;

  EXPECT_TRUE(basePtr->useGetGrayLine());
  EXPECT_TRUE(derived.useGetGrayLine());
}

TEST_F(GfxColorSpaceUseGetGrayLineTest_402, PolymorphicCallDispatchesToOverrideFalse_402) {
  TestColorSpaceOverrideFalse_402 derived;
  const GfxColorSpace *basePtr = &derived;

  EXPECT_FALSE(basePtr->useGetGrayLine());
  EXPECT_FALSE(derived.useGetGrayLine());
}

TEST_F(GfxColorSpaceUseGetGrayLineTest_402, ConstObjectCallableAndStable_402) {
  const TestColorSpaceDefault_402 cs;
  EXPECT_FALSE(cs.useGetGrayLine());
  EXPECT_FALSE(cs.useGetGrayLine()); // repeated call boundary: should remain consistent
}