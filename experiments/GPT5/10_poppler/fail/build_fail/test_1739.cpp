// CairoImageOutputDev_useDrawChar_1739_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h"

namespace {

// Fixture to keep naming consistent and embed TEST_ID in every test name.
class CairoImageOutputDevTest_1739 : public ::testing::Test {
protected:
  CairoImageOutputDev dev_;
};

TEST_F(CairoImageOutputDevTest_1739, UseDrawCharReturnsFalse_1739) {
  // Normal operation: the public override is observable via its return value.
  EXPECT_FALSE(dev_.useDrawChar());
}

TEST_F(CairoImageOutputDevTest_1739, UseDrawCharIsStableAcrossMultipleCalls_1739) {
  // Boundary-ish behavior: repeated calls should remain consistent.
  EXPECT_FALSE(dev_.useDrawChar());
  EXPECT_FALSE(dev_.useDrawChar());
  EXPECT_FALSE(dev_.useDrawChar());
}

TEST_F(CairoImageOutputDevTest_1739, UseDrawCharReturnsFalseThroughBaseReference_1739) {
  // Verifies the override is effective polymorphically (external observable interaction).
  CairoOutputDev &base_ref = dev_;
  EXPECT_FALSE(base_ref.useDrawChar());
}

TEST_F(CairoImageOutputDevTest_1739, UseDrawCharReturnsFalseThroughBasePointer_1739) {
  // Same as above, but through a pointer.
  CairoOutputDev *base_ptr = &dev_;
  ASSERT_NE(base_ptr, nullptr);
  EXPECT_FALSE(base_ptr->useDrawChar());
}

} // namespace