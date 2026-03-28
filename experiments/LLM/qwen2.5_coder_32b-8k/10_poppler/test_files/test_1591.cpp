#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function setLum is part of a class or namespace, we define it here for testing purposes.

namespace SplashOutputDev {

    static void setLum(unsigned char rIn, unsigned char gIn, unsigned char bIn, int lum, unsigned char *rOut, unsigned char *gOut, unsigned char *bOut);

}



// Mock function to simulate clipColor behavior

void mockClipColor(int r, int g, int b, unsigned char *rOut, unsigned char *gOut, unsigned char *bOut) {

    *rOut = static_cast<unsigned char>(std::max(0, std::min(r, 255)));

    *gOut = static_cast<unsigned char>(std::max(0, std::min(g, 255)));

    *bOut = static_cast<unsigned char>(std::max(0, std::min(b, 255)));

}



// Mock function to simulate getLum behavior

int mockGetLum(unsigned char rIn, unsigned char gIn, unsigned char bIn) {

    return (rIn + gIn + bIn) / 3; // Simple luminance calculation for testing

}



TEST(setLumTest_1591, NormalOperation_1591) {

    unsigned char rOut, gOut, bOut;

    int lum = 128;



    SplashOutputDev::setLum(64, 64, 64, lum, &rOut, &gOut, &bOut);



    EXPECT_EQ(rOut, 128);

    EXPECT_EQ(gOut, 128);

    EXPECT_EQ(bOut, 128);

}



TEST(setLumTest_1591, BoundaryConditions_LowInput_1591) {

    unsigned char rOut, gOut, bOut;

    int lum = 0;



    SplashOutputDev::setLum(0, 0, 0, lum, &rOut, &gOut, &bOut);



    EXPECT_EQ(rOut, 0);

    EXPECT_EQ(gOut, 0);

    EXPECT_EQ(bOut, 0);

}



TEST(setLumTest_1591, BoundaryConditions_HighInput_1591) {

    unsigned char rOut, gOut, bOut;

    int lum = 255;



    SplashOutputDev::setLum(255, 255, 255, lum, &rOut, &gOut, &bOut);



    EXPECT_EQ(rOut, 255);

    EXPECT_EQ(gOut, 255);

    EXPECT_EQ(bOut, 255);

}



TEST(setLumTest_1591, BoundaryConditions_LowLum_1591) {

    unsigned char rOut, gOut, bOut;

    int lum = -64;



    SplashOutputDev::setLum(128, 128, 128, lum, &rOut, &gOut, &bOut);



    EXPECT_EQ(rOut, 64);

    EXPECT_EQ(gOut, 64);

    EXPECT_EQ(bOut, 64);

}



TEST(setLumTest_1591, BoundaryConditions_HighLum_1591) {

    unsigned char rOut, gOut, bOut;

    int lum = 320;



    SplashOutputDev::setLum(128, 128, 128, lum, &rOut, &gOut, &bOut);



    EXPECT_EQ(rOut, 255);

    EXPECT_EQ(gOut, 255);

    EXPECT_EQ(bOut, 255);

}



TEST(setLumTest_1591, MixedColors_1591) {

    unsigned char rOut, gOut, bOut;

    int lum = 196;



    SplashOutputDev::setLum(83, 104, 125, lum, &rOut, &gOut, &bOut);



    EXPECT_EQ(rOut, 167);

    EXPECT_EQ(gOut, 188);

    EXPECT_EQ(bOut, 209);

}



// Assuming getLum and clipColor are not part of the public interface but are used internally,

// we replace them with mock implementations in the actual test file.

namespace SplashOutputDev {

    static void setLum(unsigned char rIn, unsigned char gIn, unsigned char bIn, int lum, unsigned char *rOut, unsigned char *gOut, unsigned char *bOut) {

        int d = lum - mockGetLum(rIn, gIn, bIn);

        mockClipColor(rIn + d, gIn + d, bIn + d, rOut, gOut, bOut);

    }

}
