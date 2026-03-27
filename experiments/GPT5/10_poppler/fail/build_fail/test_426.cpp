// TEST_ID: 426
// File: gfxdevicergbcolorspace_usegetdevicelnline_test_426.cpp

#include <gtest/gtest.h>

#include "GfxState.h" // ./TestProjects/poppler/poppler/GfxState.h

namespace {

class GfxDeviceRGBColorSpaceTest_426 : public ::testing::Test {};

TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetDeviceNLineReturnsTrue_426)
{
    GfxDeviceRGBColorSpace cs;
    EXPECT_TRUE(cs.useGetDeviceNLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetDeviceNLineCallableOnConstObject_426)
{
    const GfxDeviceRGBColorSpace cs;
    EXPECT_TRUE(cs.useGetDeviceNLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetDeviceNLineIsTrueViaBasePointerDispatch_426)
{
    // Verifies observable behavior through the public virtual interface.
    GfxColorSpace *base = new GfxDeviceRGBColorSpace();
    EXPECT_TRUE(base->useGetDeviceNLine());
    delete base;
}

TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetDeviceNLineRepeatedCallsRemainTrue_426)
{
    GfxDeviceRGBColorSpace cs;
    EXPECT_TRUE(cs.useGetDeviceNLine());
    EXPECT_TRUE(cs.useGetDeviceNLine());
    EXPECT_TRUE(cs.useGetDeviceNLine());
}

} // namespace