#include <gtest/gtest.h>
#include "CairoOutputDev.h"

class CairoImageTest_1721 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(CairoImageTest_1721, GetRectReturnsCorrectValues_1721) {
    CairoImage img(1.0, 2.0, 3.0, 4.0);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 1.0);
    EXPECT_DOUBLE_EQ(ya1, 2.0);
    EXPECT_DOUBLE_EQ(xa2, 3.0);
    EXPECT_DOUBLE_EQ(ya2, 4.0);
}

TEST_F(CairoImageTest_1721, GetRectWithZeroValues_1721) {
    CairoImage img(0.0, 0.0, 0.0, 0.0);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 0.0);
    EXPECT_DOUBLE_EQ(ya1, 0.0);
    EXPECT_DOUBLE_EQ(xa2, 0.0);
    EXPECT_DOUBLE_EQ(ya2, 0.0);
}

TEST_F(CairoImageTest_1721, GetRectWithNegativeValues_1721) {
    CairoImage img(-10.5, -20.3, -5.1, -1.7);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, -10.5);
    EXPECT_DOUBLE_EQ(ya1, -20.3);
    EXPECT_DOUBLE_EQ(xa2, -5.1);
    EXPECT_DOUBLE_EQ(ya2, -1.7);
}

TEST_F(CairoImageTest_1721, GetRectWithLargeValues_1721) {
    CairoImage img(1e15, 1e15, 1e16, 1e16);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 1e15);
    EXPECT_DOUBLE_EQ(ya1, 1e15);
    EXPECT_DOUBLE_EQ(xa2, 1e16);
    EXPECT_DOUBLE_EQ(ya2, 1e16);
}

TEST_F(CairoImageTest_1721, GetRectWithFractionalValues_1721) {
    CairoImage img(0.123456789, 0.987654321, 1.111111111, 2.222222222);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 0.123456789);
    EXPECT_DOUBLE_EQ(ya1, 0.987654321);
    EXPECT_DOUBLE_EQ(xa2, 1.111111111);
    EXPECT_DOUBLE_EQ(ya2, 2.222222222);
}

TEST_F(CairoImageTest_1721, GetRectWithMixedSignValues_1721) {
    CairoImage img(-100.0, 200.0, 300.0, -400.0);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, -100.0);
    EXPECT_DOUBLE_EQ(ya1, 200.0);
    EXPECT_DOUBLE_EQ(xa2, 300.0);
    EXPECT_DOUBLE_EQ(ya2, -400.0);
}

TEST_F(CairoImageTest_1721, GetRectCalledMultipleTimes_1721) {
    CairoImage img(5.0, 10.0, 15.0, 20.0);
    double xa1, ya1, xa2, ya2;

    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 5.0);
    EXPECT_DOUBLE_EQ(ya1, 10.0);
    EXPECT_DOUBLE_EQ(xa2, 15.0);
    EXPECT_DOUBLE_EQ(ya2, 20.0);

    // Call again to ensure consistency
    double bx1, by1, bx2, by2;
    img.getRect(&bx1, &by1, &bx2, &by2);
    EXPECT_DOUBLE_EQ(bx1, 5.0);
    EXPECT_DOUBLE_EQ(by1, 10.0);
    EXPECT_DOUBLE_EQ(bx2, 15.0);
    EXPECT_DOUBLE_EQ(by2, 20.0);
}

TEST_F(CairoImageTest_1721, GetRectWithVerySmallValues_1721) {
    CairoImage img(1e-300, 1e-300, 1e-300, 1e-300);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 1e-300);
    EXPECT_DOUBLE_EQ(ya1, 1e-300);
    EXPECT_DOUBLE_EQ(xa2, 1e-300);
    EXPECT_DOUBLE_EQ(ya2, 1e-300);
}

TEST_F(CairoImageTest_1721, GetImageReturnsNullInitially_1721) {
    CairoImage img(0.0, 0.0, 100.0, 100.0);
    cairo_surface_t *surface = img.getImage();
    // Without calling setImage, the image should be null
    EXPECT_EQ(surface, nullptr);
}

TEST_F(CairoImageTest_1721, GetRectX1EqualsX2_1721) {
    CairoImage img(50.0, 10.0, 50.0, 100.0);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 50.0);
    EXPECT_DOUBLE_EQ(ya1, 10.0);
    EXPECT_DOUBLE_EQ(xa2, 50.0);
    EXPECT_DOUBLE_EQ(ya2, 100.0);
}

TEST_F(CairoImageTest_1721, GetRectY1EqualsY2_1721) {
    CairoImage img(10.0, 50.0, 100.0, 50.0);
    double xa1, ya1, xa2, ya2;
    img.getRect(&xa1, &ya1, &xa2, &ya2);
    EXPECT_DOUBLE_EQ(xa1, 10.0);
    EXPECT_DOUBLE_EQ(ya1, 50.0);
    EXPECT_DOUBLE_EQ(xa2, 100.0);
    EXPECT_DOUBLE_EQ(ya2, 50.0);
}
