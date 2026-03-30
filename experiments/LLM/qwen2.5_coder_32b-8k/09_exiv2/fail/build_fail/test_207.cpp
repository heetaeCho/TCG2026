#include <gtest/gtest.h>

#include "LensInfo.h" // Assuming there's a class or struct named LensInfo in this header



// Test case to verify known lens information

TEST(LensInfoTest, KnownLenses) {

    EXPECT_EQ(getLensName(770), "smc PENTAX-FA 645 150mm F2.8 [IF]");

    EXPECT_EQ(getLensName(3346), "smc PENTAX-D FA 645 55mm F2.8 AL [IF] SDM AW");

    EXPECT_EQ(getLensName(5377), "01 Standard Prime 8.5mm F1.9");

    EXPECT_EQ(getLensName(2063), "Sigma 18-200mm F3.5-6.3 II DC HSM");

}



// Test case to verify unknown lens information

TEST(LensInfoTest, UnknownLenses) {

    EXPECT_EQ(getLensName(9999), "Unknown Lens"); // Assuming this is how the function handles unknown IDs

    EXPECT_EQ(getLensName(0), "Unknown Lens");

}



// Test case for edge cases

TEST(LensInfoTest, EdgeCases) {

    EXPECT_EQ(getLensName(1537), "smc PENTAX-FA* 85mm F1.4[IF]");

    EXPECT_EQ(getLensName(2833), "smc PENTAX-FA 645 150-300mm F5.6 ED [IF]");

}



// Test case for special lenses

TEST(LensInfoTest, SpecialLenses) {

    EXPECT_EQ(getLensName(5635), "03 Fish-eye 3.2mm F5.6");

    EXPECT_EQ(getLensName(5637), "05 Toy Lens Telephoto 18mm F8");

}



// Test case for adapters

TEST(LensInfoTest, Adapters) {

    EXPECT_EQ(getLensName(5609), "Adapter Q for K-mount Lens");

}

```


