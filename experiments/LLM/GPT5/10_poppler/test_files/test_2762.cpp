// File: fontinfodata_test_2762.cpp

#include <gtest/gtest.h>

// Poppler Qt6 internal header that declares Poppler::FontInfoData.
#include "poppler-private.h"

namespace {

class FontInfoDataTest_2762 : public ::testing::Test {};

TEST_F(FontInfoDataTest_2762, DefaultConstructorInitializesFlagsAndType_2762)
{
    Poppler::FontInfoData fid;

    // Observable behavior from the provided constructor body.
    EXPECT_FALSE(fid.isEmbedded);
    EXPECT_FALSE(fid.isSubset);
    EXPECT_EQ(fid.type, Poppler::FontInfo::unknown);
}

TEST_F(FontInfoDataTest_2762, DefaultConstructorIsDeterministicAcrossInstances_2762)
{
    Poppler::FontInfoData a;
    Poppler::FontInfoData b;

    EXPECT_EQ(a.isEmbedded, b.isEmbedded);
    EXPECT_EQ(a.isSubset, b.isSubset);
    EXPECT_EQ(a.type, b.type);

    EXPECT_FALSE(a.isEmbedded);
    EXPECT_FALSE(a.isSubset);
    EXPECT_EQ(a.type, Poppler::FontInfo::unknown);
}

TEST_F(FontInfoDataTest_2762, CopyConstructorPreservesPublicState_2762)
{
    Poppler::FontInfoData original;
    original.isEmbedded = true;
    original.isSubset = true;
    original.type = Poppler::FontInfo::unknown; // keep within observable enum values

    Poppler::FontInfoData copy(original);

    EXPECT_EQ(copy.isEmbedded, original.isEmbedded);
    EXPECT_EQ(copy.isSubset, original.isSubset);
    EXPECT_EQ(copy.type, original.type);
}

TEST_F(FontInfoDataTest_2762, CopyAssignmentPreservesPublicState_2762)
{
    Poppler::FontInfoData source;
    source.isEmbedded = true;
    source.isSubset = false;
    source.type = Poppler::FontInfo::unknown;

    Poppler::FontInfoData dest;
    dest.isEmbedded = false;
    dest.isSubset = true;
    dest.type = Poppler::FontInfo::unknown;

    dest = source;

    EXPECT_EQ(dest.isEmbedded, source.isEmbedded);
    EXPECT_EQ(dest.isSubset, source.isSubset);
    EXPECT_EQ(dest.type, source.type);
}

TEST_F(FontInfoDataTest_2762, SelfAssignmentDoesNotChangePublicState_2762)
{
    Poppler::FontInfoData fid;
    fid.isEmbedded = true;
    fid.isSubset = true;
    fid.type = Poppler::FontInfo::unknown;

    fid = fid;

    EXPECT_TRUE(fid.isEmbedded);
    EXPECT_TRUE(fid.isSubset);
    EXPECT_EQ(fid.type, Poppler::FontInfo::unknown);
}

} // namespace