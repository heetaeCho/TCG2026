#include <gtest/gtest.h>

#include <string>



// Assuming a function getLensName(uint16_t id) that returns the lens name for a given ID

std::string getLensName(uint16_t id) {

    // This is a mock implementation for testing purposes

    switch (id) {

        case 769: return "smc PENTAX-FA 645 Macro 120mm F4";

        case 3348: return "HD PENTAX-D FA 645 90mm F2.8 ED AW SR";

        case 5377: return "01 Standard Prime 8.5mm F1.9";

        case 5635: return "03 Fish-eye 3.2mm F5.6";

        case 5636: return "04 Toy Lens Wide 6.3mm F7.1";

        case 5637: return "05 Toy Lens Telephoto 18mm F8";

        case 5382: return "06 Telephoto Zoom 15-45mm F2.8";

        case 5383: return "07 Mount Shield 11.5mm F9";

        case 5384: return "08 Wide Zoom 3.8-5.9mm F3.7-4";

        case 5609: return "Adapter Q for K-mount Lens";

        default: return "Unknown Lens";

    }

}



TEST(LensNameTest, KnownIDs) {

    EXPECT_EQ(getLensName(769), "smc PENTAX-FA 645 Macro 120mm F4");

    EXPECT_EQ(getLensName(3348), "HD PENTAX-D FA 645 90mm F2.8 ED AW SR");

    EXPECT_EQ(getLensName(5377), "01 Standard Prime 8.5mm F1.9");

    EXPECT_EQ(getLensName(5635), "03 Fish-eye 3.2mm F5.6");

    EXPECT_EQ(getLensName(5636), "04 Toy Lens Wide 6.3mm F7.1");

    EXPECT_EQ(getLensName(5637), "05 Toy Lens Telephoto 18mm F8");

    EXPECT_EQ(getLensName(5382), "06 Telephoto Zoom 15-45mm F2.8");

    EXPECT_EQ(getLensName(5383), "07 Mount Shield 11.5mm F9");

    EXPECT_EQ(getLensName(5384), "08 Wide Zoom 3.8-5.9mm F3.7-4");

    EXPECT_EQ(getLensName(5609), "Adapter Q for K-mount Lens");

}



TEST(LensNameTest, UnknownID) {

    EXPECT_EQ(getLensName(0), "Unknown Lens");

    EXPECT_EQ(getLensName(12345), "Unknown Lens");

}
