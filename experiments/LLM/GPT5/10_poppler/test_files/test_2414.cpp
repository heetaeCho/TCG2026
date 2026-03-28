// poppler-movie_need_poster_test.cc
#include <gtest/gtest.h>

#include <climits>

// The function under test is in poppler-movie.cc (GLib Poppler bindings).
// In this test project, PopplerMovie's struct layout is provided (see prompt),
// so we can construct minimal instances to exercise observable behavior.
extern "C" {
#include "poppler-movie.h"
}

// Forward declare the function under test (in case the header doesn't declare it
// in this test harness).
extern "C" gboolean poppler_movie_need_poster(PopplerMovie *poppler_movie);

class PopplerMovieTest_2414 : public ::testing::Test {
protected:
  static PopplerMovie MakeMovieWithNeedPoster(int need_poster_value) {
    PopplerMovie m{};
    // Only set the field relevant to the tested observable return value.
    // Other fields are left as zero-initialized.
    m.need_poster = need_poster_value;
    return m;
  }
};

TEST_F(PopplerMovieTest_2414, ReturnsFalseWhenNeedPosterIsZero_2414) {
  PopplerMovie movie = MakeMovieWithNeedPoster(0);
  gboolean result = poppler_movie_need_poster(&movie);
  EXPECT_FALSE(result);
}

TEST_F(PopplerMovieTest_2414, ReturnsTrueWhenNeedPosterIsOne_2414) {
  PopplerMovie movie = MakeMovieWithNeedPoster(1);
  gboolean result = poppler_movie_need_poster(&movie);
  EXPECT_TRUE(result);
}

TEST_F(PopplerMovieTest_2414, ReturnsTrueWhenNeedPosterIsNegative_2414) {
  PopplerMovie movie = MakeMovieWithNeedPoster(-1);
  gboolean result = poppler_movie_need_poster(&movie);
  EXPECT_TRUE(result);
}

TEST_F(PopplerMovieTest_2414, ReturnsTrueWhenNeedPosterIsLargeNonZero_2414) {
  PopplerMovie movie = MakeMovieWithNeedPoster(INT_MAX);
  gboolean result = poppler_movie_need_poster(&movie);
  EXPECT_TRUE(result);
}

TEST_F(PopplerMovieTest_2414, ReturnsFalseForNullMoviePointer_2414) {
  // Error/exceptional case observable through the interface: the function
  // returns FALSE when given an invalid instance pointer.
  gboolean result = poppler_movie_need_poster(nullptr);
  EXPECT_FALSE(result);
}