#include <gtest/gtest.h>

#include "poppler-movie.h"

#include <gmock/gmock.h>



// Assuming PopplerMovie can be created and destroyed properly in these tests.

// Mocking any external dependencies if necessary (though none are apparent here).



class PopplerMovieTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a valid PopplerMovie instance for testing

        poppler_movie = g_object_new(POPPLER_TYPE_MOVIE, nullptr);

    }



    void TearDown() override {

        // Clean up the PopplerMovie instance after each test

        if (poppler_movie) {

            g_object_unref(poppler_movie);

            poppler_movie = nullptr;

        }

    }



    PopplerMovie* poppler_movie;

};



// Test normal operation of getting start time with a valid PopplerMovie object

TEST_F(PopplerMovieTest_2421, GetStart_NormalOperation_2421) {

    guint64 start_time = 100L;

    poppler_movie->start = start_time; // Directly set for testing purposes



    EXPECT_EQ(poppler_movie_get_start(poppler_movie), start_time);

}



// Test boundary condition where the PopplerMovie object is null

TEST_F(PopplerMovieTest_2421, GetStart_NullPointer_2421) {

    EXPECT_EQ(poppler_movie_get_start(nullptr), 0L);

}



// Since there are no apparent exceptional or error cases from the given interface,

// and no external interactions to verify, we stop here.


