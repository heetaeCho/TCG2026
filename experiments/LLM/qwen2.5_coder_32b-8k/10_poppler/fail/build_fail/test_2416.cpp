#include <gtest/gtest.h>

#include "poppler-movie.h"

#include "gmock/gmock.h"



// Mocking the necessary external collaborators or dependencies if needed.

class PopplerMovieMock : public _PopplerMovie {

public:

    PopplerMovieMock(int mode) {

        this->mode = mode;

    }

};



TEST(PopplerMoviePlayModeTest_2416, GetPlayMode_NormalOperation_2416) {

    // Arrange

    int test_mode = POPPLER_MOVIE_PLAY_MODE_LOOP;  // Example mode value

    PopplerMovieMock movie(test_mode);



    // Act

    PopplerMoviePlayMode result = poppler_movie_get_play_mode(&movie);



    // Assert

    EXPECT_EQ(result, test_mode);

}



TEST(PopplerMoviePlayModeTest_2416, GetPlayMode_BoundaryCondition_DefaultValue_2416) {

    // Arrange

    int test_mode = POPPLER_MOVIE_PLAY_MODE_ONCE;  // Default mode value

    PopplerMovieMock movie(test_mode);



    // Act

    PopplerMoviePlayMode result = poppler_movie_get_play_mode(&movie);



    // Assert

    EXPECT_EQ(result, test_mode);

}



TEST(PopplerMoviePlayModeTest_2416, GetPlayMode_ExceptionalCase_NullPointer_2416) {

    // Arrange & Act

    PopplerMoviePlayMode result = poppler_movie_get_play_mode(nullptr);



    // Assert

    EXPECT_EQ(result, POPPLER_MOVIE_PLAY_MODE_ONCE);  // Default value expected when null is passed

}
