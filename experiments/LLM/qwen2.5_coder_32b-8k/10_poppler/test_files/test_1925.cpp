#include <gtest/gtest.h>



// Assuming luminocity function is part of a class or namespace, we'll mock it as a static method for testing.

// Since there's no actual class provided, we'll wrap it in a struct for clarity.



struct CairoOutputDev {

    static int luminosity(uint32_t x);

};



// Test cases for the luminosity function



TEST(CairoOutputDevTest_1925, Luminosity_ReturnsCorrectValueForWhite_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0xFFFFFF), 255);

}



TEST(CairoOutputDevTest_1925, Luminosity_ReturnsCorrectValueForBlack_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0x000000), 0);

}



TEST(CairoOutputDevTest_1925, Luminosity_ReturnsCorrectValueForGray_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0x808080), 128);

}



TEST(CairoOutputDevTest_1925, Luminosity_ReturnsCorrectValueForRed_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0xFF0000), 54);

}



TEST(CairoOutputDevTest_1925, Luminosity_ReturnsCorrectValueForGreen_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0x00FF00), 182);

}



TEST(CairoOutputDevTest_1925, Luminosity_ReturnsCorrectValueForBlue_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0x0000FF), 15);

}



TEST(CairoOutputDevTest_1925, Luminosity_BoundaryCondition_Zero_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0x000000), 0);

}



TEST(CairoOutputDevTest_1925, Luminosity_BoundaryCondition_MaxValue_1925) {

    EXPECT_EQ(CairoOutputDev::luminosity(0xFFFFFF), 255);

}

```


