#include <gtest/gtest.h>



class CairoImageTest_1721 : public ::testing::Test {

protected:

    double x1 = 0.0;

    double y1 = 0.0;

    double x2 = 10.0;

    double y2 = 10.0;



    CairoImage image;



    CairoImageTest_1721() : image(x1, y1, x2, y2) {}

};



TEST_F(CairoImageTest_1721, GetRect_ReturnsCorrectCoordinates_1721) {

    double xa1, ya1, xa2, ya2;

    image.getRect(&xa1, &ya1, &xa2, &ya2);

    EXPECT_EQ(xa1, x1);

    EXPECT_EQ(ya1, y1);

    EXPECT_EQ(xa2, x2);

    EXPECT_EQ(ya2, y2);

}



TEST_F(CairoImageTest_1721, GetRect_BoundaryConditions_ZeroCoordinates_1721) {

    double xa1, ya1, xa2, ya2;

    CairoImage zero_image(0.0, 0.0, 0.0, 0.0);

    zero_image.getRect(&xa1, &ya1, &xa2, &ya2);

    EXPECT_EQ(xa1, 0.0);

    EXPECT_EQ(ya1, 0.0);

    EXPECT_EQ(xa2, 0.0);

    EXPECT_EQ(ya2, 0.0);

}



TEST_F(CairoImageTest_1721, GetRect_BoundaryConditions_NegativeCoordinates_1721) {

    double xa1, ya1, xa2, ya2;

    CairoImage negative_image(-5.0, -5.0, -1.0, -1.0);

    negative_image.getRect(&xa1, &ya1, &xa2, &ya2);

    EXPECT_EQ(xa1, -5.0);

    EXPECT_EQ(ya1, -5.0);

    EXPECT_EQ(xa2, -1.0);

    EXPECT_EQ(ya2, -1.0);

}



TEST_F(CairoImageTest_1721, GetRect_BoundaryConditions_LargeCoordinates_1721) {

    double xa1, ya1, xa2, ya2;

    CairoImage large_image(1e6, 1e6, 1e9, 1e9);

    large_image.getRect(&xa1, &ya1, &xa2, &ya2);

    EXPECT_EQ(xa1, 1e6);

    EXPECT_EQ(ya1, 1e6);

    EXPECT_EQ(xa2, 1e9);

    EXPECT_EQ(ya2, 1e9);

}



TEST_F(CairoImageTest_1721, GetRect_BoundaryConditions_EqualCoordinates_1721) {

    double xa1, ya1, xa2, ya2;

    CairoImage equal_image(5.0, 5.0, 5.0, 5.0);

    equal_image.getRect(&xa1, &ya1, &xa2, &ya2);

    EXPECT_EQ(xa1, 5.0);

    EXPECT_EQ(ya1, 5.0);

    EXPECT_EQ(xa2, 5.0);

    EXPECT_EQ(ya2, 5.0);

}
