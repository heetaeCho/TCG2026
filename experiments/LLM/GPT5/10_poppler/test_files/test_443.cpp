// TEST_ID=443
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxDeviceCMYKColorSpaceTest_443 : public ::testing::Test {};

TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetRGBLineReturnsTrue_443) {
  GfxDeviceCMYKColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetRGBLineWorksOnConstObject_443) {
  const GfxDeviceCMYKColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetRGBLineReturnsTrueRepeatedly_443) {
  GfxDeviceCMYKColorSpace cs;
  EXPECT_TRUE(cs.useGetRGBLine());
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetRGBLineReturnsTrueViaBasePointer_443) {
  GfxDeviceCMYKColorSpace cs;
  GfxColorSpace* base = &cs;  // Verifies virtual dispatch through the public base interface.
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useGetRGBLine());
}

}  // namespace