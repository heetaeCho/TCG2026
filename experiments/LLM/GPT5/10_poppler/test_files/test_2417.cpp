// File: poppler-movie-is-synchronous-test-2417.cc

#include <gtest/gtest.h>

#include <glib.h>

// Poppler GLib headers (the project’s include path should provide these)
#include <poppler.h>

// NOTE: We treat the implementation as a black box and only validate observable behavior
// through the public API. Where the struct fields are publicly exposed by the build,
// they are considered part of the available interface for constructing test inputs.

namespace {

class PopplerMovieTest_2417 : public ::testing::Test {
protected:
  void SetUp() override {
    // No global setup required for this API surface.
  }
};

TEST_F(PopplerMovieTest_2417, NullptrReturnsFalse_2417) {
  // Error case: g_return_val_if_fail should return FALSE for invalid instances.
  EXPECT_FALSE(poppler_movie_is_synchronous(nullptr));
}

TEST_F(PopplerMovieTest_2417, ReturnsTrueWhenSynchronousPlayIsTrue_2417) {
  // Construct a movie instance using the exposed struct definition (if available in this build).
  PopplerMovie movie{};
  movie.synchronous_play = TRUE;

  EXPECT_TRUE(poppler_movie_is_synchronous(&movie));
}

TEST_F(PopplerMovieTest_2417, ReturnsFalseWhenSynchronousPlayIsFalse_2417) {
  PopplerMovie movie{};
  movie.synchronous_play = FALSE;

  EXPECT_FALSE(poppler_movie_is_synchronous(&movie));
}

TEST_F(PopplerMovieTest_2417, NonZeroSynchronousPlayIsTreatedAsTrue_2417) {
  // Boundary-ish behavior: gboolean is an int; any non-zero value is truthy.
  PopplerMovie movie{};
  movie.synchronous_play = 2;

  EXPECT_TRUE(poppler_movie_is_synchronous(&movie));
}

TEST_F(PopplerMovieTest_2417, RepeatedCallsAreConsistent_2417) {
  PopplerMovie movie{};
  movie.synchronous_play = TRUE;

  const gboolean first = poppler_movie_is_synchronous(&movie);
  const gboolean second = poppler_movie_is_synchronous(&movie);

  EXPECT_TRUE(first);
  EXPECT_EQ(first, second);
}

}  // namespace