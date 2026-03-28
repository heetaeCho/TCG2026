// TEST_ID: 428
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxDeviceRGBAColorSpaceTest_428 : public ::testing::Test {};

TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeReturnsDeviceRGBA_428) {
  GfxDeviceRGBAColorSpace cs;
  EXPECT_EQ(cs.getMode(), csDeviceRGBA);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeViaBaseReferenceReturnsDeviceRGBA_428) {
  GfxDeviceRGBAColorSpace derived;
  const GfxColorSpace& baseRef = derived;
  EXPECT_EQ(baseRef.getMode(), csDeviceRGBA);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeIsStableAcrossCalls_428) {
  GfxDeviceRGBAColorSpace cs;
  const auto m1 = cs.getMode();
  const auto m2 = cs.getMode();
  const auto m3 = cs.getMode();
  EXPECT_EQ(m1, csDeviceRGBA);
  EXPECT_EQ(m2, csDeviceRGBA);
  EXPECT_EQ(m3, csDeviceRGBA);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_428, CopyProducesNonNullAndPreservesMode_428) {
  GfxDeviceRGBAColorSpace cs;

  std::unique_ptr<GfxColorSpace> copy = cs.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_EQ(copy->getMode(), csDeviceRGBA);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetARGBPremultipliedLineLengthZeroDoesNotCrash_428) {
  // Boundary: length == 0 should be safe (no-op), regardless of implementation details.
  unsigned char in[4] = {0, 0, 0, 0};
  unsigned int out[1] = {0};

  EXPECT_NO_THROW(GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 0));
}

}  // namespace