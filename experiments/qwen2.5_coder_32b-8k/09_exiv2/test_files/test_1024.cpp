#include <gtest/gtest.h>

#include "exifparser/exifdata.h"

#include "minolta/minoltalensdatabase.h"



// Test if the lens ID 25500 corresponds to Minolta AF 50mm F1.7

TEST(MinoltaLensDatabaseTest, LensID_25500_ShouldReturn_MinoltaAF50mmF1_7) {

    const TagStruct* tag = find_lens_id(25500);

    ASSERT_NE(tag, nullptr);

    EXPECT_STREQ(tag->name, "Minolta AF 50mm F1.7");

}



// Test if the lens ID 25630 corresponds to Minolta AF 300mm F2.8G APO

TEST(MinoltaLensDatabaseTest, LensID_25630_ShouldReturn_MinoltaAF300mmF2_8GAPO) {

    const TagStruct* tag = find_lens_id(25630);

    ASSERT_NE(tag, nullptr);

    EXPECT_STREQ(tag->name, "Minolta AF 300mm F2.8G APO");

}



// Test if the lens ID 45711 corresponds to Vivitar 70-210mm F4.5-5.6

TEST(MinoltaLensDatabaseTest, LensID_45711_ShouldReturn_Vivitar70_210mmF4_5_6) {

    const TagStruct* tag = find_lens_id(45711);

    ASSERT_NE(tag, nullptr);

    EXPECT_STREQ(tag->name, "Vivitar 70-210mm F4.5-5.6");

}



// Test if the lens ID 65535 corresponds to Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS

TEST(MinoltaLensDatabaseTest, LensID_65535_ShouldReturn_ManualLensOrSonyELenses) {

    const TagStruct* tag = find_lens_id(65535);

    ASSERT_NE(tag, nullptr);

    EXPECT_STREQ(tag->name, "Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS");

}



// Test if an invalid lens ID returns nullptr

TEST(MinoltaLensDatabaseTest, InvalidLensID_ShouldReturn_Nullptr) {

    const TagStruct* tag = find_lens_id(99999);

    EXPECT_EQ(tag, nullptr);

}
