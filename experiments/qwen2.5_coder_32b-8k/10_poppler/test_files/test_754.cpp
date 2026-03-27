#include <gtest/gtest.h>

#include "Annot.h"



class AnnotColorTest_754 : public ::testing::Test {

protected:

    AnnotColor grayColor;

    AnnotColor rgbColor;

    AnnotColor cmykColor;



    AnnotColorTest_754() 

        : grayColor(0.5), 

          rgbColor(1.0, 0.0, 0.0),

          cmykColor(0.2, 0.3, 0.4, 0.5) {}

};



TEST_F(AnnotColorTest_754, GrayColorSpace_754) {

    EXPECT_EQ(grayColor.getSpace(), AnnotColorSpace::gray);

}



TEST_F(AnnotColorTest_754, RGBColorSpace_754) {

    EXPECT_EQ(rgbColor.getSpace(), AnnotColorSpace::rgb);

}



TEST_F(AnnotColorTest_754, CMYKColorSpace_754) {

    EXPECT_EQ(cmykColor.getSpace(), AnnotColorSpace::cmyk);

}



TEST_F(AnnotColorTest_754, DefaultConstructorGraySpace_754) {

    AnnotColor defaultColor;

    EXPECT_EQ(defaultColor.getSpace(), AnnotColorSpace::gray);

}



// Boundary conditions

TEST_F(AnnotColorTest_754, GrayBoundaryLow_754) {

    AnnotColor boundaryColor(-0.1);

    std::array<double, 4> expectedValues = {0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(boundaryColor.getSpace(), AnnotColorSpace::gray);

    EXPECT_EQ(boundaryColor.getValues(), expectedValues);

}



TEST_F(AnnotColorTest_754, GrayBoundaryHigh_754) {

    AnnotColor boundaryColor(1.1);

    std::array<double, 4> expectedValues = {1.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(boundaryColor.getSpace(), AnnotColorSpace::gray);

    EXPECT_EQ(boundaryColor.getValues(), expectedValues);

}



// Exceptional or error cases

// Note: Since the provided interface does not indicate any exceptions, we assume no exceptional behavior is observable.



// Verification of external interactions (none in this case)
