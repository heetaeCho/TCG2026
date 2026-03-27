#include <gtest/gtest.h>

#include "poppler-movie.h"

#include <gmock/gmock.h>



// Mocking external collaborators or dependencies if needed (none in this case)



class PopplerMovieTest_2423 : public ::testing::Test {

protected:

    PopplerMovie *movie;



    void SetUp() override {

        movie = static_cast<PopplerMovie*>(g_malloc0(sizeof(PopplerMovie)));

        // Initialize with some default values if necessary

        movie->width = 1920;

        movie->height = 1080;

    }



    void TearDown() override {

        g_free(movie);

    }

};



TEST_F(PopplerMovieTest_2423, GetAspect_NormalOperation_2423) {

    gint width, height;

    poppler_movie_get_aspect(movie, &width, &height);

    EXPECT_EQ(width, 1920);

    EXPECT_EQ(height, 1080);

}



TEST_F(PopplerMovieTest_2423, GetAspect_BoundaryConditionZeroWidth_2423) {

    movie->width = 0;

    gint width, height;

    poppler_movie_get_aspect(movie, &width, &height);

    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 1080);

}



TEST_F(PopplerMovieTest_2423, GetAspect_BoundaryConditionZeroHeight_2423) {

    movie->height = 0;

    gint width, height;

    poppler_movie_get_aspect(movie, &width, &height);

    EXPECT_EQ(width, 1920);

    EXPECT_EQ(height, 0);

}



TEST_F(PopplerMovieTest_2423, GetAspect_BoundaryConditionZeroWidthAndHeight_2423) {

    movie->width = 0;

    movie->height = 0;

    gint width, height;

    poppler_movie_get_aspect(movie, &width, &height);

    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 0);

}



TEST_F(PopplerMovieTest_2423, GetAspect_ExceptionalCaseInvalidPointer_2423) {

    // This test assumes that the g_return_if_fail macro will prevent the function from executing with invalid pointers

    gint width = -1, height = -1;

    poppler_movie_get_aspect(nullptr, &width, &height);

    EXPECT_EQ(width, -1); // Unchanged

    EXPECT_EQ(height, -1); // Unchanged



    width = -1, height = -1;

    poppler_movie_get_aspect(movie, nullptr, &height);

    EXPECT_EQ(width, -1); // Unchanged

    EXPECT_EQ(height, 1080);



    width = -1, height = -1;

    poppler_movie_get_aspect(movie, &width, nullptr);

    EXPECT_EQ(width, 1920);

    EXPECT_EQ(height, -1); // Unchanged

}
