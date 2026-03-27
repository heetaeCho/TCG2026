#include <gtest/gtest.h>

#include "PDFRectangle.h"



class PDFRectangleTest_681 : public ::testing::Test {

protected:

    PDFRectangle rectDefault;

    PDFRectangle rectValid;

    PDFRectangle rectEmpty;



    void SetUp() override {

        rectDefault = PDFRectangle();

        rectValid = PDFRectangle(1.0, 2.0, 3.0, 4.0);

        rectEmpty = PDFRectangle(0.0, 0.0, 0.0, 0.0);

    }

};



TEST_F(PDFRectangleTest_681, DefaultConstructorCreatesInvalidRectangle_681) {

    EXPECT_FALSE(rectDefault.isValid());

}



TEST_F(PDFRectangleTest_681, ParameterizedConstructorCreatesValidRectangle_681) {

    EXPECT_TRUE(rectValid.isValid());

}



TEST_F(PDFRectangleTest_681, RectangleWithAllZerosIsEmpty_681) {

    EXPECT_TRUE(rectEmpty.isEmpty());

}



TEST_F(PDFRectangleTest_681, RectangleWithNonZeroValuesIsNotEmpty_681) {

    EXPECT_FALSE(rectValid.isEmpty());

}



TEST_F(PDFRectangleTest_681, ValidRectangleContainsPointInsideIt_681) {

    EXPECT_TRUE(rectValid.contains(2.0, 3.0));

}



TEST_F(PDFRectangleTest_681, ValidRectangleDoesNotContainPointOutsideIt_681) {

    EXPECT_FALSE(rectValid.contains(-1.0, -1.0));

}



TEST_F(PDFRectangleTest_681, RectanglesAreEqualWhenAllCoordinatesMatch_681) {

    PDFRectangle rectAnother(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(rectValid == rectAnother);

}



TEST_F(PDFRectangleTest_681, RectanglesAreNotEqualWhenAnyCoordinateDiffers_681) {

    PDFRectangle rectDifferent(1.0, 2.0, 5.0, 4.0);

    EXPECT_FALSE(rectValid == rectDifferent);

}
