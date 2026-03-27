// poppler-movie-get-rate-test.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Poppler GLib headers
#include <poppler.h>

namespace {

class PopplerMovieTest_2419 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure type system is ready (mostly harmless on newer GLib).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerMovieTest_2419, NullMovieReturnsZero_2419) {
  EXPECT_DOUBLE_EQ(poppler_movie_get_rate(nullptr), 0.0);
}

TEST_F(PopplerMovieTest_2419, NonMovieInstanceReturnsZero_2419) {
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Intentionally pass a non-PopplerMovie pointer; function should defensively return 0.
  EXPECT_DOUBLE_EQ(poppler_movie_get_rate(reinterpret_cast<PopplerMovie *>(obj)), 0.0);

  g_object_unref(obj);
}

TEST_F(PopplerMovieTest_2419, ValidMovieReturnsStoredRate_2419) {
  // If PopplerMovie is not instantiable in this build, skip rather than guessing internals.
  GType movie_type = POPPLER_TYPE_MOVIE;
  if (g_type_test_flags(movie_type, G_TYPE_FLAG_ABSTRACT)) {
    GTEST_SKIP() << "POPPLER_TYPE_MOVIE is abstract in this build; cannot instantiate to verify rate.";
  }

  PopplerMovie *movie = POPPLER_MOVIE(g_object_new(movie_type, nullptr));
  ASSERT_NE(movie, nullptr);
  ASSERT_TRUE(POPPLER_IS_MOVIE(movie));

  // The provided dependency snippet shows the instance has a public 'rate' field.
  // We only validate observable behavior: getter reflects the value stored on the instance.
  movie->rate = 1;
  EXPECT_DOUBLE_EQ(poppler_movie_get_rate(movie), 1.0);

  movie->rate = 0;
  EXPECT_DOUBLE_EQ(poppler_movie_get_rate(movie), 0.0);

  movie->rate = -3;
  EXPECT_DOUBLE_EQ(poppler_movie_get_rate(movie), -3.0);

  g_object_unref(movie);
}

TEST_F(PopplerMovieTest_2419, LargeRateValueIsReturnedAsDouble_2419) {
  GType movie_type = POPPLER_TYPE_MOVIE;
  if (g_type_test_flags(movie_type, G_TYPE_FLAG_ABSTRACT)) {
    GTEST_SKIP() << "POPPLER_TYPE_MOVIE is abstract in this build; cannot instantiate to verify rate.";
  }

  PopplerMovie *movie = POPPLER_MOVIE(g_object_new(movie_type, nullptr));
  ASSERT_NE(movie, nullptr);
  ASSERT_TRUE(POPPLER_IS_MOVIE(movie));

  // Boundary-ish: large positive int value (within int range).
  movie->rate = 1000000;
  EXPECT_DOUBLE_EQ(poppler_movie_get_rate(movie), 1000000.0);

  g_object_unref(movie);
}

}  // namespace