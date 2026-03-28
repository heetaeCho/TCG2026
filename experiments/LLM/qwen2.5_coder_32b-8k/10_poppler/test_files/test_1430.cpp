#include <gtest/gtest.h>

#include "Movie.h"

#include "Object.h"



class MovieTest : public ::testing::Test {

protected:

    Object movieDict;

    Object aDict;

    Movie* movie;



    void SetUp() override {

        movie = new Movie(&movieDict, &aDict);

    }



    void TearDown() override {

        delete movie;

    }

};



TEST_F(MovieTest_1430, IsOk_ReturnsTrue_1430) {

    EXPECT_TRUE(movie->isOk());

}



TEST_F(MovieTest_1430, GetRotationAngle_ReturnsDefaultValue_1430) {

    EXPECT_EQ(0, movie->getRotationAngle());

}



TEST_F(MovieTest_1430, GetShowPoster_ReturnsFalseByDefault_1430) {

    EXPECT_FALSE(movie->getShowPoster());

}



TEST_F(MovieTest_1430, GetUseFloatingWindow_ReturnsFalseByDefault_1430) {

    EXPECT_FALSE(movie->getUseFloatingWindow());

}



TEST_F(MovieTest_1430, GetFileName_ReturnsNullByDefault_1430) {

    EXPECT_EQ(nullptr, movie->getFileName());

}



TEST_F(MovieTest_1430, GetActivationParameters_ReturnsNonNullPointer_1430) {

    EXPECT_NE(nullptr, movie->getActivationParameters());

}



TEST_F(MovieTest_1430, GetFloatingWindowSize_DoesNotCrashWithNullPointers_1430) {

    int width = 0;

    int height = 0;

    EXPECT_NO_FATAL_FAILURE(movie->getFloatingWindowSize(&width, &height));

}



TEST_F(MovieTest_1430, GetAspect_DoesNotCrashWithNullPointers_1430) {

    int widthA = 0;

    int heightA = 0;

    EXPECT_NO_FATAL_FAILURE(movie->getAspect(&widthA, &heightA));

}



TEST_F(MovieTest_1430, Copy_ReturnsNonNegativeValue_1430) {

    EXPECT_GE(movie->copy(), 0);

}



TEST_F(MovieTest_1430, GetPoster_ReturnsValidObject_1430) {

    Object poster = movie->getPoster();

    EXPECT_TRUE(poster.isNone());

}
