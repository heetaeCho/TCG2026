#include <gtest/gtest.h>

#include "./TestProjects/poppler/utils/pdfsig.cc"



TEST(locationToString_2685, Unknown_ReturnsEmptyString_2685) {

    EXPECT_EQ(locationToString(KeyLocation::Unknown), "");

}



TEST(locationToString_2685, Other_ReturnsOtherInParentheses_2685) {

    EXPECT_EQ(locationToString(KeyLocation::Other), "(Other)");

}



TEST(locationToString_2685, Computer_ReturnsComputerInParentheses_2685) {

    EXPECT_EQ(locationToString(KeyLocation::Computer), "(Computer)");

}



TEST(locationToString_2685, HardwareToken_ReturnsHardwareTokenInParentheses_2685) {

    EXPECT_EQ(locationToString(KeyLocation::HardwareToken), "(Hardware Token)");

}
