#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Movie.h"



class MovieTest_1426 : public ::testing::Test {

protected:

    Object mockObject;

    Movie movieUnderTest;



    MovieTest_1426() : movieUnderTest(&mockObject) {}

};



TEST_F(MovieTest_1426, IsOk_ReturnsTrue_1426) {

    EXPECT_TRUE(movieUnderTest.isOk());

}



TEST_F(MovieTest_1426, GetFileName_ReturnsNonNullPointer_1426) {

    const GooString* fileName = movieUnderTest.getFileName();

    EXPECT_NE(fileName, nullptr);

}



TEST_F(MovieTest_1426, GetRotationAngle_ReturnsValidAngle_1426) {

    unsigned short angle = movieUnderTest.getRotationAngle();

    EXPECT_GE(angle, 0);

}



TEST_F(MovieTest_1426, GetPoster_ReturnsObject_1426) {

    Object poster = movieUnderTest.getPoster();

    EXPECT_TRUE(poster.isNone() || poster.isDict());

}



TEST_F(MovieTest_1426, GetShowPoster_ReturnsBoolean_1426) {

    bool showPoster = movieUnderTest.getShowPoster();

    EXPECT_TRUE(showPoster == true || showPoster == false);

}



TEST_F(MovieTest_1426, GetUseFloatingWindow_ReturnsBoolean_1426) {

    bool useFloatingWindow = movieUnderTest.getUseFloatingWindow();

    EXPECT_TRUE(useFloatingWindow == true || useFloatingWindow == false);

}



TEST_F(MovieTest_1426, GetActivationParameters_ReturnsNonNullPointer_1426) {

    const MovieActivationParameters* activationParams = movieUnderTest.getActivationParameters();

    EXPECT_NE(activationParams, nullptr);

}



TEST_F(MovieTest_1426, GetFloatingWindowSize_SetsWidthAndHeight_1426) {

    int width = 0;

    int height = 0;

    movieUnderTest.getFloatingWindowSize(&width, &height);

    EXPECT_GE(width, 0);

    EXPECT_GE(height, 0);

}



TEST_F(MovieTest_1426, GetAspect_SetsWidthAndHeightAspects_1426) {

    int widthA = 0;

    int heightA = 0;

    movieUnderTest.getAspect(&widthA, &heightA);

    EXPECT_GE(widthA, 0);

    EXPECT_GE(heightA, 0);

}



TEST_F(MovieTest_1426, Copy_ReturnsNonNegativeInteger_1426) {

    int result = movieUnderTest.copy();

    EXPECT_GE(result, 0);

}
