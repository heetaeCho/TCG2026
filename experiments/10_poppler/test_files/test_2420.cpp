#include <gtest/gtest.h>

#include "poppler-movie.h"

#include <glib-object.h>



// Mock class for PopplerMovie if needed (not required in this case)

class MockPopplerMovie : public PopplerMovie {

public:

    MockPopplerMovie() {}

};



TEST_F(PopplerMovieTest_2420, NormalOperation_ZeroRotationAngle_2420) {

    PopplerMovie* movie = static_cast<PopplerMovie*>(g_object_new(POPPLER_TYPE_MOVIE, nullptr));

    g_assert_cmpint(poppler_movie_get_rotation_angle(movie), ==, 0);

    g_object_unref(movie);

}



TEST_F(PopplerMovieTest_2420, NormalOperation_NonZeroRotationAngle_2420) {

    PopplerMovie* movie = static_cast<PopplerMovie*>(g_object_new(POPPLER_TYPE_MOVIE, nullptr));

    movie->rotation_angle = 90;

    g_assert_cmpint(poppler_movie_get_rotation_angle(movie), ==, 90);

    g_object_unref(movie);

}



TEST_F(PopplerMovieTest_2420, BoundaryCondition_MaxRotationAngle_2420) {

    PopplerMovie* movie = static_cast<PopplerMovie*>(g_object_new(POPPLER_TYPE_MOVIE, nullptr));

    movie->rotation_angle = G_MAXUSHORT;

    g_assert_cmpint(poppler_movie_get_rotation_angle(movie), ==, G_MAXUSHORT);

    g_object_unref(movie);

}



TEST_F(PopplerMovieTest_2420, BoundaryCondition_MinRotationAngle_2420) {

    PopplerMovie* movie = static_cast<PopplerMovie*>(g_object_new(POPPLER_TYPE_MOVIE, nullptr));

    movie->rotation_angle = 0;

    g_assert_cmpint(poppler_movie_get_rotation_angle(movie), ==, 0);

    g_object_unref(movie);

}



TEST_F(PopplerMovieTest_2420, ErrorCase_NullPointer_2420) {

    g_assert_cmpint(poppler_movie_get_rotation_angle(nullptr), ==, 0);

}



// Assuming PopplerMovie is a valid GObject type and can be created using g_object_new

class PopplerMovieTest_2420 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary resources here if needed

    }



    void TearDown() override {

        // Clean up any resources here if needed

    }

};
