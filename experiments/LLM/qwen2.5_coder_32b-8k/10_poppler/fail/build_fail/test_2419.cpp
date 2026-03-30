#include <gtest/gtest.h>

#include "poppler-movie.h"

#include <gmock/gmock.h>



// Mocking external dependencies if needed (none in this case)



class PopplerMovieTest : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_movie = static_cast<PopplerMovie*>(g_malloc0(sizeof(PopplerMovie)));

        g_assert(poppler_movie != nullptr);

    }



    void TearDown() override {

        g_free(poppler_movie);

    }



    PopplerMovie* poppler_movie;

};



TEST_F(PopplerMovieTest_2419, GetRate_ReturnsZeroForNullPointer_2419) {

    EXPECT_EQ(poppler_movie_get_rate(nullptr), 0.0);

}



TEST_F(PopplerMovieTest_2419, GetRate_ReturnsCorrectRate_2419) {

    poppler_movie->rate = 30;

    EXPECT_EQ(poppler_movie_get_rate(poppler_movie), 30.0);

}



TEST_F(PopplerMovieTest_2419, GetRate_ReturnsZeroForInvalidObject_2419) {

    // Assuming invalid object means setting a field to an unexpected value

    poppler_movie->mode = -1; // Invalid mode as an example

    EXPECT_EQ(poppler_movie_get_rate(poppler_movie), 0.0);

}



TEST_F(PopplerMovieTest_2419, GetRate_BoundaryConditionZeroRate_2419) {

    poppler_movie->rate = 0;

    EXPECT_EQ(poppler_movie_get_rate(poppler_movie), 0.0);

}



TEST_F(PopplerMovieTest_2419, GetRate_BoundaryConditionMaxIntRate_2419) {

    poppler_movie->rate = G_MAXINT;

    EXPECT_EQ(poppler_movie_get_rate(poppler_movie), static_cast<gdouble>(G_MAXINT));

}
