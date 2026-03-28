#include <gtest/gtest.h>

#include "poppler-movie.h"

#include <glib-object.h>



class PopplerMovieTest_2422 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_movie = POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));

    }



    void TearDown() override {

        g_clear_object(&poppler_movie);

    }



    PopplerMovie* poppler_movie;

};



TEST_F(PopplerMovieTest_2422, GetDuration_ReturnsZeroForNullPointer_2422) {

    EXPECT_EQ(poppler_movie_get_duration(nullptr), 0L);

}



TEST_F(PopplerMovieTest_2422, GetDuration_ReturnsInitializedValue_2422) {

    guint64 expected_duration = 12345;

    poppler_movie->duration = expected_duration;

    EXPECT_EQ(poppler_movie_get_duration(poppler_movie), expected_duration);

}



TEST_F(PopplerMovieTest_2422, GetDuration_ReturnsZeroForInvalidObject_2422) {

    GObject* invalid_object = g_object_new(G_TYPE_OBJECT, nullptr);

    EXPECT_EQ(poppler_movie_get_duration(POPPLER_MOVIE(invalid_object)), 0L);

    g_clear_object(&invalid_object);

}
