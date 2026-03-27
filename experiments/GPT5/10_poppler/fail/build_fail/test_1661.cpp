// PreScanOutputDev_isGray_test_1661.cpp
#include <gtest/gtest.h>

#include <limits>

#include "PreScanOutputDev.h"

namespace {

class PreScanOutputDevTest_1661 : public ::testing::Test {};

TEST_F(PreScanOutputDevTest_1661, ConstructAndCallIsGrayDoesNotThrow_1661) {
  EXPECT_NO_THROW({
    PreScanOutputDev dev(PSLevel{});
    (void)dev.isGray();
  });
}

TEST_F(PreScanOutputDevTest_1661, IsGrayCallableOnConstReference_1661) {
  PreScanOutputDev dev(PSLevel{});
  const PreScanOutputDev &cdev = dev;

  // Compile-time/ABI surface check: callable on const object, returns bool.
  const bool gray = cdev.isGray();
  (void)gray;
}

TEST_F(PreScanOutputDevTest_1661, IsGrayStableAcrossMultipleCallsWithoutOtherInteractions_1661) {
  PreScanOutputDev dev(PSLevel{});

  const bool v1 = dev.isGray();
  const bool v2 = dev.isGray();
  const bool v3 = dev.isGray();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(PreScanOutputDevTest_1661, ConstructWithDifferentPSLevelValuesIsGrayCallable_1661) {
  // Boundary-ish construction values: default, small non-zero, and a large cast.
  PreScanOutputDev dev_default(PSLevel{});
  PreScanOutputDev dev_one(static_cast<PSLevel>(1));
  PreScanOutputDev dev_max(static_cast<PSLevel>(std::numeric_limits<int>::max()));

  // Observable behavior we can safely assert: method is callable and returns a bool.
  (void)dev_default.isGray();
  (void)dev_one.isGray();
  (void)dev_max.isGray();
}

}  // namespace