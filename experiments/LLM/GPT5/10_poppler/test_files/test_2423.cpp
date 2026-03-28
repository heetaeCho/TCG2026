// File: poppler-movie-get-aspect-test.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include <poppler.h>
}

// Simple GLib log capture helper to verify g_return_if_fail() behavior without
// depending on internal state.
class ScopedGLogCapture {
public:
  ScopedGLogCapture() {
    // Capture CRITICAL logs from both default domain (NULL) and "Poppler" domain
    // (commonly used in Poppler GLib code).
    handler_id_default_ = g_log_set_handler(
        /*log_domain=*/nullptr,
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
        &ScopedGLogCapture::LogHandler, this);

    handler_id_poppler_ = g_log_set_handler(
        /*log_domain=*/"Poppler",
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
        &ScopedGLogCapture::LogHandler, this);
  }

  ~ScopedGLogCapture() {
    if (handler_id_default_ != 0) {
      g_log_remove_handler(nullptr, handler_id_default_);
    }
    if (handler_id_poppler_ != 0) {
      g_log_remove_handler("Poppler", handler_id_poppler_);
    }
  }

  int critical_count() const { return critical_count_; }

  bool saw_assertion_for_movie() const { return saw_movie_assertion_; }

private:
  static void LogHandler(const gchar* /*log_domain*/,
                         GLogLevelFlags log_level,
                         const gchar* message,
                         gpointer user_data) {
    auto* self = static_cast<ScopedGLogCapture*>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      self->critical_count_++;
      if (message && g_strrstr(message, "POPPLER_IS_MOVIE") != nullptr) {
        self->saw_movie_assertion_ = true;
      }
    }
  }

  guint handler_id_default_ = 0;
  guint handler_id_poppler_ = 0;

  int critical_count_ = 0;
  bool saw_movie_assertion_ = false;
};

class PopplerMovieTest_2423 : public ::testing::Test {};

TEST_F(PopplerMovieTest_2423, GetAspectReturnsWidthAndHeight_2423) {
  // Normal operation: when given a valid PopplerMovie, it should write out the
  // stored width/height into the output parameters.
  PopplerMovie* movie = g_new0(PopplerMovie, 1);
  ASSERT_NE(movie, nullptr);

  // The implementation reads poppler_movie->width/height directly.
  movie->width = 640;
  movie->height = 480;

  gint w = -1;
  gint h = -1;
  poppler_movie_get_aspect(movie, &w, &h);

  EXPECT_EQ(w, 640);
  EXPECT_EQ(h, 480);

  g_free(movie);
}

TEST_F(PopplerMovieTest_2423, GetAspectBoundaryZeroDimensions_2423) {
  // Boundary: zero values should be returned as-is.
  PopplerMovie* movie = g_new0(PopplerMovie, 1);
  ASSERT_NE(movie, nullptr);

  movie->width = 0;
  movie->height = 0;

  gint w = 123;
  gint h = 456;
  poppler_movie_get_aspect(movie, &w, &h);

  EXPECT_EQ(w, 0);
  EXPECT_EQ(h, 0);

  g_free(movie);
}

TEST_F(PopplerMovieTest_2423, GetAspectBoundaryNegativeDimensions_2423) {
  // Boundary: negative dimensions are still observable values through the API
  // (function does not document clamping), so verify they pass through.
  PopplerMovie* movie = g_new0(PopplerMovie, 1);
  ASSERT_NE(movie, nullptr);

  movie->width = -10;
  movie->height = -20;

  gint w = 0;
  gint h = 0;
  poppler_movie_get_aspect(movie, &w, &h);

  EXPECT_EQ(w, -10);
  EXPECT_EQ(h, -20);

  g_free(movie);
}

TEST_F(PopplerMovieTest_2423, GetAspectNullMovieEmitsCriticalAndDoesNotWriteOutputs_2423) {
  // Error case: g_return_if_fail(POPPLER_IS_MOVIE(poppler_movie)) should emit a
  // CRITICAL and return early. Outputs should remain unchanged.
  ScopedGLogCapture capture;

  gint w = 11;
  gint h = 22;

  poppler_movie_get_aspect(nullptr, &w, &h);

  // Observable behavior: a CRITICAL should have been logged.
  EXPECT_GE(capture.critical_count(), 1);
  // Message typically mentions the failed assertion.
  EXPECT_TRUE(capture.saw_assertion_for_movie());

  // Since the function returns early, it should not write outputs.
  EXPECT_EQ(w, 11);
  EXPECT_EQ(h, 22);
}

TEST_F(PopplerMovieTest_2423, GetAspectNullMovieAllowsNullOutputPointers_2423) {
  // Boundary/error-adjacent: because the function checks poppler_movie first,
  // passing NULL output pointers should still be safe when poppler_movie is NULL
  // (it returns early before dereferencing output pointers).
  ScopedGLogCapture capture;

  poppler_movie_get_aspect(nullptr, /*width=*/nullptr, /*height=*/nullptr);

  EXPECT_GE(capture.critical_count(), 1);
  EXPECT_TRUE(capture.saw_assertion_for_movie());
}