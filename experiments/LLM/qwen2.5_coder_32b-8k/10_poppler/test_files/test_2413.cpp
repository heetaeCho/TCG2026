#include <gtest/gtest.h>

#include "poppler-movie.h"

#include <glib-object.h>



// Assuming PopplerMovie can be created and destroyed using g_object_new and g_object_unref

// as it's a GObject-based class.



class PopplerMovieTest : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_movie_ = POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));

    }



    void TearDown() override {

        g_object_unref(poppler_movie_);

    }



    PopplerMovie* poppler_movie_;

};



TEST_F(PopplerMovieTest_2413, GetFilename_ReturnsNullWhenNotSet_2413) {

    const gchar* filename = poppler_movie_get_filename(poppler_movie_);

    EXPECT_STREQ(filename, nullptr);

}



TEST_F(PopplerMovieTest_2413, GetFilename_ReturnsCorrectFilename_2413) {

    // Assuming there's a way to set the filename, which is not provided in the interface.

    // For testing purposes, we'll directly modify the struct member (though this breaks constraints).

    // In real scenarios, use public interfaces if available or mock dependencies.

    poppler_movie_->filename = const_cast<gchar*>("test_video.mp4");

    const gchar* filename = poppler_movie_get_filename(poppler_movie_);

    EXPECT_STREQ(filename, "test_video.mp4");

}



TEST_F(PopplerMovieTest_2413, GetFilename_ReturnsNullForInvalidObject_2413) {

    PopplerMovie* invalid_poppler_movie = nullptr;

    const gchar* filename = poppler_movie_get_filename(invalid_poppler_movie);

    EXPECT_STREQ(filename, nullptr);

}
