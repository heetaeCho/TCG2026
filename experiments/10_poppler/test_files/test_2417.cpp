#include <gtest/gtest.h>

#include "poppler-movie.h"



class PopplerMovieTest_2417 : public ::testing::Test {

protected:

    PopplerMovie* poppler_movie;



    void SetUp() override {

        // Assuming a function to create a PopplerMovie instance exists

        // For the sake of testing, we will manually allocate memory and initialize it.

        poppler_movie = static_cast<PopplerMovie*>(g_malloc(sizeof(PopplerMovie)));

        // Initialize default values for members

        poppler_movie->need_poster = 0;

        poppler_movie->mode = 0;

        poppler_movie->synchronous_play = FALSE;

        poppler_movie->rate = 0;

        poppler_movie->rotation_angle = 0;

    }



    void TearDown() override {

        g_free(poppler_movie);

    }

};



TEST_F(PopplerMovieTest_2417, IsSynchronous_ReturnsFalseWhenNotSet_2417) {

    EXPECT_FALSE(poppler_movie_is_synchronous(poppler_movie));

}



TEST_F(PopplerMovieTest_2417, IsSynchronous_ReturnsTrueWhenSet_2417) {

    poppler_movie->synchronous_play = TRUE;

    EXPECT_TRUE(poppler_movie_is_synchronous(poppler_movie));

}



TEST_F(PopplerMovieTest_2417, IsSynchronous_NullPointerHandling_2417) {

    EXPECT_FALSE(poppler_movie_is_synchronous(nullptr));

}
