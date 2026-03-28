#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

#include "poppler-movie.h"

}



class PopplerMovieTest_2418 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_movie = reinterpret_cast<PopplerMovie*>(g_malloc0(sizeof(PopplerMovie)));

    }



    void TearDown() override {

        g_free(poppler_movie);

    }



    PopplerMovie* poppler_movie;

};



TEST_F(PopplerMovieTest_2418, GetVolume_DefaultValue_2418) {

    EXPECT_EQ(poppler_movie_get_volume(poppler_movie), 0.0);

}



TEST_F(PopplerMovieTest_2418, GetVolume_SetValue_2418) {

    poppler_movie->volume = 0.5;

    EXPECT_EQ(poppler_movie_get_volume(poppler_movie), 0.5);

}



TEST_F(PopplerMovieTest_2418, GetVolume_MaxValue_2418) {

    poppler_movie->volume = 1.0;

    EXPECT_EQ(poppler_movie_get_volume(poppler_movie), 1.0);

}



TEST_F(PopplerMovieTest_2418, GetVolume_MinValue_2418) {

    poppler_movie->volume = 0.0;

    EXPECT_EQ(poppler_movie_get_volume(poppler_movie), 0.0);

}



TEST_F(PopplerMovieTest_2418, GetVolume_NegativeValue_2418) {

    poppler_movie->volume = -0.5;

    EXPECT_EQ(poppler_movie_get_volume(poppler_movie), -0.5);

}



TEST_F(PopplerMovieTest_2418, GetVolume_OutOfBoundsHigh_2418) {

    poppler_movie->volume = 1.5;

    EXPECT_EQ(poppler_movie_get_volume(poppler_movie), 1.5);

}



TEST_F(PopplerMovieTest_2418, GetVolume_OutOfBoundsLow_2418) {

    poppler_movie->volume = -1.0;

    EXPECT_EQ(poppler_movie_get_volume(poppler_movie), -1.0);

}



TEST_F(PopplerMovieTest_2418, GetVolume_NullPointer_2418) {

    EXPECT_EQ(poppler_movie_get_volume(nullptr), 0.0);

}
