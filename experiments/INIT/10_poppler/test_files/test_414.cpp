// TEST_ID: 414
#include <gtest/gtest.h>

#include "GfxState.h"

class GfxCalGrayColorSpaceTest_414 : public ::testing::Test {};

TEST_F(GfxCalGrayColorSpaceTest_414, GetNCompsReturnsOne_Direct_414)
{
    GfxCalGrayColorSpace cs;
    EXPECT_EQ(cs.getNComps(), 1);
}

TEST_F(GfxCalGrayColorSpaceTest_414, GetNCompsReturnsOne_ConstObject_414)
{
    const GfxCalGrayColorSpace cs;
    EXPECT_EQ(cs.getNComps(), 1);
}

TEST_F(GfxCalGrayColorSpaceTest_414, GetNCompsReturnsOne_ViaBaseReference_414)
{
    GfxCalGrayColorSpace cs;
    const GfxColorSpace &baseRef = cs;

    EXPECT_EQ(baseRef.getNComps(), 1);
}

TEST_F(GfxCalGrayColorSpaceTest_414, GetNCompsIsStableAcrossMultipleCalls_414)
{
    GfxCalGrayColorSpace cs;

    EXPECT_EQ(cs.getNComps(), 1);
    EXPECT_EQ(cs.getNComps(), 1);
    EXPECT_EQ(cs.getNComps(), 1);
}