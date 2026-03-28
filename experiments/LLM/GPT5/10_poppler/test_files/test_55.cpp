// File: SignatureInfo_setSubFilterSupport_test_55.cpp
#include <gtest/gtest.h>

#include "poppler/SignatureInfo.h"

namespace {

// The TEST_ID is 55

TEST(SignatureInfoTest_55, SetSubFilterSupportTrueThenIsSupportedReturnsTrue_55)
{
    SignatureInfo info;

    info.setSubFilterSupport(true);

    EXPECT_TRUE(info.isSubfilterSupported());
}

TEST(SignatureInfoTest_55, SetSubFilterSupportFalseThenIsSupportedReturnsFalse_55)
{
    SignatureInfo info;

    info.setSubFilterSupport(false);

    EXPECT_FALSE(info.isSubfilterSupported());
}

TEST(SignatureInfoTest_55, ToggleSupportFlagTrueFalseTrueReflectsLatestValue_55)
{
    SignatureInfo info;

    info.setSubFilterSupport(true);
    EXPECT_TRUE(info.isSubfilterSupported());

    info.setSubFilterSupport(false);
    EXPECT_FALSE(info.isSubfilterSupported());

    info.setSubFilterSupport(true);
    EXPECT_TRUE(info.isSubfilterSupported());
}

TEST(SignatureInfoTest_55, RepeatedlySettingSameValueIsStable_55)
{
    SignatureInfo info;

    info.setSubFilterSupport(true);
    info.setSubFilterSupport(true);
    info.setSubFilterSupport(true);
    EXPECT_TRUE(info.isSubfilterSupported());

    info.setSubFilterSupport(false);
    info.setSubFilterSupport(false);
    EXPECT_FALSE(info.isSubfilterSupported());
}

TEST(SignatureInfoTest_55, MultipleInstancesMaintainIndependentSupportFlags_55)
{
    SignatureInfo a;
    SignatureInfo b;

    a.setSubFilterSupport(true);
    b.setSubFilterSupport(false);

    EXPECT_TRUE(a.isSubfilterSupported());
    EXPECT_FALSE(b.isSubfilterSupported());

    // Flip one and ensure the other is unaffected.
    b.setSubFilterSupport(true);
    EXPECT_TRUE(a.isSubfilterSupported());
    EXPECT_TRUE(b.isSubfilterSupported());
}

} // namespace