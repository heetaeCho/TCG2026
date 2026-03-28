#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

#include "./TestProjects/poppler/glib/poppler-movie.h"

}



class PopplerMovieTest_2415 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_movie = static_cast<PopplerMovie*>(g_malloc0(sizeof(PopplerMovie)));

    }



    void TearDown() override {

        g_free(poppler_movie);

    }



    PopplerMovie* poppler_movie;

};



TEST_F(PopplerMovieTest_2415, ShowControlsReturnsFalseWhenNotSet_2415) {

    EXPECT_EQ(FALSE, poppler_movie_show_controls(poppler_movie));

}



TEST_F(PopplerMovieTest_2415, ShowControlsReturnsTrueWhenSet_2415) {

    poppler_movie->show_controls = TRUE;

    EXPECT_EQ(TRUE, poppler_movie_show_controls(poppler_movie));

}



TEST_F(PopplerMovieTest_2415, ShowControlsHandlesNullPointer_2415) {

    EXPECT_EQ(FALSE, poppler_movie_show_controls(nullptr));

}
