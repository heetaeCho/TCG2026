// TEST_ID: 473
#include <gtest/gtest.h>

#include <limits>
#include <memory>

#include "GfxState.h"

// A minimal concrete GfxColorSpace that lets us control the observable
// getOverprintMask() result via the protected member in the base class.
class TestColorSpace_473 : public GfxColorSpace {
public:
  explicit TestColorSpace_473(unsigned int mask) { overprintMask = mask; }
  ~TestColorSpace_473() override = default;
};

class GfxIndexedColorSpaceTest_473 : public ::testing::Test {};

TEST_F(GfxIndexedColorSpaceTest_473, ForwardsOverprintMaskFromBase_473) {
  auto base = std::make_unique<TestColorSpace_473>(0xA5A5u);
  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/0);

  EXPECT_EQ(cs.getOverprintMask(), 0xA5A5u);
}

TEST_F(GfxIndexedColorSpaceTest_473, ForwardsZeroMask_473) {
  auto base = std::make_unique<TestColorSpace_473>(0u);
  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/0);

  EXPECT_EQ(cs.getOverprintMask(), 0u);
}

TEST_F(GfxIndexedColorSpaceTest_473, ForwardsMaxUnsignedMask_473) {
  const unsigned int kMax = std::numeric_limits<unsigned int>::max();
  auto base = std::make_unique<TestColorSpace_473>(kMax);
  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/0);

  EXPECT_EQ(cs.getOverprintMask(), kMax);
}

TEST_F(GfxIndexedColorSpaceTest_473, ForwardsAfterConstructionWithDifferentIndexHigh_473) {
  auto base = std::make_unique<TestColorSpace_473>(1234u);
  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/255);

  EXPECT_EQ(cs.getOverprintMask(), 1234u);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GfxIndexedColorSpaceTest_473, GetOverprintMaskWithNullBaseDies_473) {
  // Observable error case: if constructed with a null base, dereferencing base is expected
  // to terminate (crash/assert). We verify this via a death test.
  std::unique_ptr<GfxColorSpace> nullBase;
  GfxIndexedColorSpace cs(std::move(nullBase), /*indexHighA=*/0);

  EXPECT_DEATH(
      {
        (void)cs.getOverprintMask();
      },
      ".*");
}
#endif