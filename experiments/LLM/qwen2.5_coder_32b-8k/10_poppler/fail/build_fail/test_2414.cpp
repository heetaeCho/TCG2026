#include <gtest/gtest.h>

#include "poppler-movie.hh"  // Adjust include as necessary



// Mocking any external collaborators if needed (None in this case)



class PopplerMovieTest : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_movie = reinterpret_cast<PopplerMovie*>(g_malloc0(sizeof(PopplerMovie)));

    }



    void TearDown() override {

        g_free(poppler_movie);

    }



    PopplerMovie* poppler_movie;

};



TEST_F(PopplerMovieTest_2414, NeedPoster_ReturnsTrue_WhenNeedPosterIsSet_2414) {

    poppler_movie->need_poster = TRUE;

    EXPECT_EQ(TRUE, poppler_movie_need_poster(poppler_movie));

}



TEST_F(PopplerMovieTest_2414, NeedPoster_ReturnsFalse_WhenNeedPosterIsNotSet_2414) {

    poppler_movie->need_poster = FALSE;

    EXPECT_EQ(FALSE, poppler_movie_need_poster(poppler_movie));

}



TEST_F(PopplerMovieTest_2414, NeedPoster_ReturnsFalse_WhenPopplerMovieIsNull_2414) {

    EXPECT_EQ(FALSE, poppler_movie_need_poster(nullptr));

}
