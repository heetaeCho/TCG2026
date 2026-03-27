//===----------------------------------------------------------------------===//
// Unit tests for GfxDeviceCMYKColorSpace::useGetDeviceNLine
// File: GfxDeviceCMYKColorSpace_useGetDeviceNLine_445_test.cc
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// The TEST_ID is 445

namespace {

class GfxDeviceCMYKColorSpaceTest_445 : public ::testing::Test {};

TEST_F(GfxDeviceCMYKColorSpaceTest_445, UseGetDeviceNLine_ReturnsTrue_445) {
  // Normal operation: the override is observable via return value.
  GfxDeviceCMYKColorSpace cs;
  EXPECT_TRUE(cs.useGetDeviceNLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_445, UseGetDeviceNLine_ConstObject_ReturnsTrue_445) {
  // Boundary-ish: const correctness / callable on const instance.
  const GfxDeviceCMYKColorSpace cs;
  EXPECT_TRUE(cs.useGetDeviceNLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_445, UseGetDeviceNLine_PolymorphicDispatch_ReturnsTrue_445) {
  // Verification of external interaction / observable behavior via base pointer dispatch.
  // (Not mocking internals; just ensuring the override is reached through the interface.)
  const GfxDeviceCMYKColorSpace derived;
  const GfxColorSpace* base = &derived;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useGetDeviceNLine());
}

}  // namespace