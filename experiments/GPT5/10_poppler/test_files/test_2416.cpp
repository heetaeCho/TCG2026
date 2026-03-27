// poppler-movie-get-play-mode-test.cc
//
// Unit tests for poppler_movie_get_play_mode()
// TEST_ID: 2416

#include <gtest/gtest.h>

extern "C" {
#include <glib-object.h>
#include <poppler.h>
}

// Some environments treat GLib criticals as fatal; ensure g_return_val_if_fail()
// doesn't abort the process during negative tests.
class PopplerMovieGetPlayModeTest_2416 : public ::testing::Test {
protected:
  void SetUp() override {
    // Make CRITICAL/WARNING non-fatal for common domains so negative-path tests can run.
    // (If the domain doesn't exist, this is harmless.)
    g_log_set_fatal_mask(nullptr, (GLogLevelFlags)G_LOG_LEVEL_ERROR);
    g_log_set_fatal_mask("Poppler", (GLogLevelFlags)G_LOG_LEVEL_ERROR);
    g_log_set_fatal_mask("poppler", (GLogLevelFlags)G_LOG_LEVEL_ERROR);
    g_log_set_fatal_mask("GLib", (GLogLevelFlags)G_LOG_LEVEL_ERROR);
    g_log_set_fatal_mask("GLib-GObject", (GLogLevelFlags)G_LOG_LEVEL_ERROR);
  }

  static PopplerMovie* CreateMovieOrSkip() {
#ifdef POPPLER_TYPE_MOVIE
    GObject* obj = G_OBJECT(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
    if (!obj) {
      return nullptr;
    }
    return POPPLER_MOVIE(obj);
#else
    return nullptr;
#endif
  }
};

TEST_F(PopplerMovieGetPlayModeTest_2416, NullMovieReturnsDefault_2416) {
  // Error/exceptional case: null should return the documented fallback.
  PopplerMoviePlayMode mode = poppler_movie_get_play_mode(nullptr);
  EXPECT_EQ(mode, POPPLER_MOVIE_PLAY_MODE_ONCE);
}

TEST_F(PopplerMovieGetPlayModeTest_2416, NonMovieObjectReturnsDefault_2416) {
  // Error/exceptional case: passing a non-movie instance should return fallback.
  GObject* not_a_movie = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_movie, nullptr);

  PopplerMoviePlayMode mode =
      poppler_movie_get_play_mode(reinterpret_cast<PopplerMovie*>(not_a_movie));
  EXPECT_EQ(mode, POPPLER_MOVIE_PLAY_MODE_ONCE);

  g_object_unref(not_a_movie);
}

TEST_F(PopplerMovieGetPlayModeTest_2416, ValidMovieCallIsStableAcrossCalls_2416) {
  // Normal operation (best-effort): for a valid object, repeated calls should be stable
  // unless the object is externally mutated.
  PopplerMovie* movie = CreateMovieOrSkip();
  if (!movie) {
    GTEST_SKIP() << "POPPLER_TYPE_MOVIE not available or PopplerMovie cannot be constructed";
  }

  PopplerMoviePlayMode first = poppler_movie_get_play_mode(movie);
  PopplerMoviePlayMode second = poppler_movie_get_play_mode(movie);

  EXPECT_EQ(first, second);

  g_object_unref(movie);
}

TEST_F(PopplerMovieGetPlayModeTest_2416, ValidMovieReflectsPlayModePropertyIfPresent_2416) {
  // Boundary/normal operation: if PopplerMovie exposes a writable property for play mode,
  // setting it should be observable via the getter.
  PopplerMovie* movie = CreateMovieOrSkip();
  if (!movie) {
    GTEST_SKIP() << "POPPLER_TYPE_MOVIE not available or PopplerMovie cannot be constructed";
  }

  GObjectClass* klass = G_OBJECT_GET_CLASS(movie);
  ASSERT_NE(klass, nullptr);

  // Property name is not guaranteed; we only test if it's present.
  // Common GLib naming is "play-mode".
  GParamSpec* pspec = g_object_class_find_property(klass, "play-mode");
  if (!pspec) {
    g_object_unref(movie);
    GTEST_SKIP() << "PopplerMovie does not expose a 'play-mode' GObject property in this build";
  }

  // If it's not writable, we also skip (can't observe changes through the public interface).
  if ((pspec->flags & G_PARAM_WRITABLE) == 0) {
    g_object_unref(movie);
    GTEST_SKIP() << "'play-mode' property is not writable in this build";
  }

  // Try a couple of enum values as boundary-ish coverage.
  g_object_set(G_OBJECT(movie), "play-mode", POPPLER_MOVIE_PLAY_MODE_ONCE, nullptr);
  EXPECT_EQ(poppler_movie_get_play_mode(movie), POPPLER_MOVIE_PLAY_MODE_ONCE);

  g_object_set(G_OBJECT(movie), "play-mode", POPPLER_MOVIE_PLAY_MODE_REPEAT, nullptr);
  EXPECT_EQ(poppler_movie_get_play_mode(movie), POPPLER_MOVIE_PLAY_MODE_REPEAT);

  g_object_unref(movie);
}