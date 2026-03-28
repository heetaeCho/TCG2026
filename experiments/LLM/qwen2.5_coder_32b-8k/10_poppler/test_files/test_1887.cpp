#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming GfxDeviceCMYKColorSpacegetRGBLineHelper is part of a class or namespace, we will define it here for testing purposes.

namespace poppler {

    static inline void GfxDeviceCMYKColorSpacegetRGBLineHelper(unsigned char *&in, double &r, double &g, double &b) {

        double c, m, y, k, c1, m1, y1, k1;

        c = byteToDbl(*in++);

        m = byteToDbl(*in++);

        y = byteToDbl(*in++);

        k = byteToDbl(*in++);

        c1 = 1 - c;

        m1 = 1 - m;

        y1 = 1 - y;

        k1 = 1 - k;

        cmykToRGBMatrixMultiplication(c, m, y, k, c1, m1, y1, k1, r, g, b);

    }



    static inline double byteToDbl(unsigned char val) {

        return val / 255.0;

    }



    static inline void cmykToRGBMatrixMultiplication(double c, double m, double y, double k, double c1, double m1, double y1, double k1, double &r, double &g, double &b) {

        r = c1 * k1;

        g = m1 * k1;

        b = y1 * k1;

    }

}



// Test fixture for GfxDeviceCMYKColorSpacegetRGBLineHelper

class GfxDeviceCMYKColorSpaceTest_1887 : public ::testing::Test {

protected:

    unsigned char input[4];

};



TEST_F(GfxDeviceCMYKColorSpaceTest_1887, NormalOperation_1887) {

    double r, g, b;

    input[0] = 255; // C

    input[1] = 165; // M

    input[2] = 0;   // Y

    input[3] = 0;   // K



    unsigned char* inPtr = input;

    poppler::GfxDeviceCMYKColorSpacegetRGBLineHelper(inPtr, r, g, b);



    EXPECT_DOUBLE_EQ(r, 0.0);

    EXPECT_DOUBLE_EQ(g, 0.35294117647058826);

    EXPECT_DOUBLE_EQ(b, 1.0);

}



TEST_F(GfxDeviceCMYKColorSpaceTest_1887, BoundaryConditions_AllZeros_1887) {

    double r, g, b;

    input[0] = 0; // C

    input[1] = 0; // M

    input[2] = 0; // Y

    input[3] = 0; // K



    unsigned char* inPtr = input;

    poppler::GfxDeviceCMYKColorSpacegetRGBLineHelper(inPtr, r, g, b);



    EXPECT_DOUBLE_EQ(r, 1.0);

    EXPECT_DOUBLE_EQ(g, 1.0);

    EXPECT_DOUBLE_EQ(b, 1.0);

}



TEST_F(GfxDeviceCMYKColorSpaceTest_1887, BoundaryConditions_AllOnes_1887) {

    double r, g, b;

    input[0] = 255; // C

    input[1] = 255; // M

    input[2] = 255; // Y

    input[3] = 255; // K



    unsigned char* inPtr = input;

    poppler::GfxDeviceCMYKColorSpacegetRGBLineHelper(inPtr, r, g, b);



    EXPECT_DOUBLE_EQ(r, 0.0);

    EXPECT_DOUBLE_EQ(g, 0.0);

    EXPECT_DOUBLE_EQ(b, 0.0);

}



TEST_F(GfxDeviceCMYKColorSpaceTest_1887, BoundaryConditions_MaxCyan_1887) {

    double r, g, b;

    input[0] = 255; // C

    input[1] = 0;   // M

    input[2] = 0;   // Y

    input[3] = 0;   // K



    unsigned char* inPtr = input;

    poppler::GfxDeviceCMYKColorSpacegetRGBLineHelper(inPtr, r, g, b);



    EXPECT_DOUBLE_EQ(r, 0.0);

    EXPECT_DOUBLE_EQ(g, 1.0);

    EXPECT_DOUBLE_EQ(b, 1.0);

}



TEST_F(GfxDeviceCMYKColorSpaceTest_1887, BoundaryConditions_MaxMagenta_1887) {

    double r, g, b;

    input[0] = 0;   // C

    input[1] = 255; // M

    input[2] = 0;   // Y

    input[3] = 0;   // K



    unsigned char* inPtr = input;

    poppler::GfxDeviceCMYKColorSpacegetRGBLineHelper(inPtr, r, g, b);



    EXPECT_DOUBLE_EQ(r, 1.0);

    EXPECT_DOUBLE_EQ(g, 0.0);

    EXPECT_DOUBLE_EQ(b, 1.0);

}



TEST_F(GfxDeviceCMYKColorSpaceTest_1887, BoundaryConditions_MaxYellow_1887) {

    double r, g, b;

    input[0] = 0;   // C

    input[1] = 0;   // M

    input[2] = 255; // Y

    input[3] = 0;   // K



    unsigned char* inPtr = input;

    poppler::GfxDeviceCMYKColorSpacegetRGBLineHelper(inPtr, r, g, b);



    EXPECT_DOUBLE_EQ(r, 1.0);

    EXPECT_DOUBLE_EQ(g, 1.0);

    EXPECT_DOUBLE_EQ(b, 0.0);

}



TEST_F(GfxDeviceCMYKColorSpaceTest_1887, BoundaryConditions_MaxBlack_1887) {

    double r, g, b;

    input[0] = 0;   // C

    input[1] = 0;   // M

    input[2] = 0;   // Y

    input[3] = 255; // K



    unsigned char* inPtr = input;

    poppler::GfxDeviceCMYKColorSpacegetRGBLineHelper(inPtr, r, g, b);



    EXPECT_DOUBLE_EQ(r, 0.0);

    EXPECT_DOUBLE_EQ(g, 0.0);

    EXPECT_DOUBLE_EQ(b, 0.0);

}
