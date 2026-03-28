// TEST_ID: 405
// File: GfxColorSpace_isNonMarking_405_test.cpp

#include <gtest/gtest.h>

#include "GfxState.h"

// A simple derived class to verify virtual dispatch behavior of isNonMarking().
class NonMarkingColorSpace_405 final : public GfxColorSpace {
public:
  bool isNonMarking() const override { return true; }
};

class GfxColorSpaceTest_405 : public ::testing::Test {};

TEST_F(GfxColorSpaceTest_405, DefaultIsNonMarkingReturnsFalse_405) {
  GfxColorSpace cs;
  EXPECT_FALSE(cs.isNonMarking());
}

TEST_F(GfxColorSpaceTest_405, ConstObjectCallReturnsFalse_405) {
  const GfxColorSpace cs;
  EXPECT_FALSE(cs.isNonMarking());
}

TEST_F(GfxColorSpaceTest_405, RepeatedCallsAreConsistent_405) {
  GfxColorSpace cs;
  EXPECT_FALSE(cs.isNonMarking());
  EXPECT_FALSE(cs.isNonMarking());
  EXPECT_FALSE(cs.isNonMarking());
}

TEST_F(GfxColorSpaceTest_405, VirtualDispatchWorksThroughBaseReference_405) {
  NonMarkingColorSpace_405 derived;
  const GfxColorSpace &baseRef = derived;

  EXPECT_TRUE(derived.isNonMarking());
  EXPECT_TRUE(baseRef.isNonMarking());
}

TEST_F(GfxColorSpaceTest_405, VirtualDispatchWorksThroughBasePointer_405) {
  NonMarkingColorSpace_405 derived;
  const GfxColorSpace *basePtr = &derived;

  ASSERT_NE(basePtr, nullptr);
  EXPECT_TRUE(basePtr->isNonMarking());
}