#include <gtest/gtest.h>

#include "Movie.h"



class MovieTest : public ::testing::Test {

protected:

    Movie* movie;



    virtual void SetUp() {

        // Assuming a default constructor or mock setup for testing purposes

        movie = new Movie(nullptr);

    }



    virtual void TearDown() {

        delete movie;

    }

};



TEST_F(MovieTest_1431, IsOk_ReturnsTrue_1431) {

    EXPECT_TRUE(movie->isOk());

}



TEST_F(MovieTest_1431, GetShowPoster_ReturnsFalseByDefault_1431) {

    EXPECT_FALSE(movie->getShowPoster());

}



TEST_F(MovieTest_1431, GetRotationAngle_ReturnsZeroByDefault_1431) {

    EXPECT_EQ(movie->getRotationAngle(), 0);

}



TEST_F(MovieTest_1431, GetFileName_ReturnsNullptrByDefault_1431) {

    EXPECT_EQ(movie->getFileName(), nullptr);

}



TEST_F(MovieTest_1431, GetActivationParameters_ReturnsNullptrByDefault_1431) {

    EXPECT_EQ(movie->getActivationParameters(), nullptr);

}



TEST_F(MovieTest_1431, GetPoster_ReturnsValidObject_1431) {

    Object poster = movie->getPoster();

    // Assuming Object has a valid state that can be checked

    EXPECT_TRUE(poster.isOk());

}



TEST_F(MovieTest_1431, GetUseFloatingWindow_ReturnsFalseByDefault_1431) {

    EXPECT_FALSE(movie->getUseFloatingWindow());

}



TEST_F(MovieTest_1431, GetFloatingWindowSize_SetsWidthAndHeightToZeroByDefault_1431) {

    int width = -1, height = -1;

    movie->getFloatingWindowSize(&width, &height);

    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 0);

}



TEST_F(MovieTest_1431, GetAspect_SetsWidthAndHeightToZeroByDefault_1431) {

    int widthA = -1, heightA = -1;

    movie->getAspect(&widthA, &heightA);

    EXPECT_EQ(widthA, 0);

    EXPECT_EQ(heightA, 0);

}



TEST_F(MovieTest_1431, Copy_ReturnsPositiveValueIndicatingSuccess_1431) {

    EXPECT_GT(movie->copy(), 0);

}
