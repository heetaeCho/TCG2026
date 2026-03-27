#include <gtest/gtest.h>

#include <string>



// Assuming a function `getLensNameById` that takes an integer ID and returns the corresponding lens name.

std::string getLensNameById(int id);



TEST(LensNameTest, TestManualLens)

{

    EXPECT_EQ(getLensNameById(0), "645 Manual Lens");

}



TEST(LensNameTest, TestASeriesLens)

{

    EXPECT_EQ(getLensNameById(2560), "645 A Series Lens");

}



TEST(LensNameTest, TestSpecificLensNames)

{

    EXPECT_EQ(getLensNameById(2817), "smc PENTAX-FA 645 75mm F2.8");

    EXPECT_EQ(getLensNameById(2818), "smc PENTAX-FA 645 45mm F2.8");

    EXPECT_EQ(getLensNameById(2819), "smc PENTAX-FA* 645 300mm F4 ED [IF]");

}



TEST(LensNameTest, TestPentaxQLenses)

{

    EXPECT_EQ(getLensNameById(5377), "01 Standard Prime 8.5mm F1.9");

    EXPECT_EQ(getLensNameById(5635), "03 Fish-eye 3.2mm F5.6");

    EXPECT_EQ(getLensNameById(5636), "04 Toy Lens Wide 6.3mm F7.1");

}



TEST(LensNameTest, TestSigmaLenses)

{

    EXPECT_EQ(getLensNameById(2069), "Sigma 17-50mm F2.8 EX DC OS HSM");

    EXPECT_EQ(getLensNameById(2070), "Sigma 85mm F1.4 EX DG HSM");

    EXPECT_EQ(getLensNameById(2303), "Sigma Lens"); // This is a generic entry, might need more specific tests for individual Sigma lenses.

}



TEST(LensNameTest, TestNonExistentLens)

{

    EXPECT_EQ(getLensNameById(-1), ""); // Assuming an empty string or some error handling for non-existent IDs

}
