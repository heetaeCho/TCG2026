#include <gtest/gtest.h>

#include "poppler-private.h"



using namespace Poppler;



class FontInfoDataTest : public ::testing::Test {

protected:

    FontInfoData fontInfoData;

};



TEST_F(FontInfoDataTest_2762, DefaultConstructorInitializesValues_2762) {

    EXPECT_FALSE(fontInfoData.isEmbedded);

    EXPECT_FALSE(fontInfoData.isSubset);

    EXPECT_EQ(fontInfoData.type, FontInfo::unknown);

}



TEST_F(FontInfoDataTest_2762, CopyConstructorPreservesValues_2762) {

    fontInfoData.isEmbedded = true;

    fontInfoData.isSubset = true;

    fontInfoData.type = FontInfo::type1;



    FontInfoData copy(fontInfoData);



    EXPECT_TRUE(copy.isEmbedded);

    EXPECT_TRUE(copy.isSubset);

    EXPECT_EQ(copy.type, FontInfo::type1);

}



TEST_F(FontInfoDataTest_2762, AssignmentOperatorPreservesValues_2762) {

    fontInfoData.isEmbedded = true;

    fontInfoData.isSubset = true;

    fontInfoData.type = FontInfo::truetype;



    FontInfoData anotherFontInfoData;

    anotherFontInfoData = fontInfoData;



    EXPECT_TRUE(anotherFontInfoData.isEmbedded);

    EXPECT_TRUE(anotherFontInfoData.isSubset);

    EXPECT_EQ(anotherFontInfoData.type, FontInfo::truetype);

}



TEST_F(FontInfoDataTest_2762, DefaultValuesAreConsistentWithKnownDependencies_2762) {

    EXPECT_FALSE(fontInfoData.isEmbedded);

    EXPECT_FALSE(fontInfoData.isSubset);

    EXPECT_EQ(fontInfoData.type, FontInfo::unknown);

}
