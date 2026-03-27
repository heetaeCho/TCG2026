// File: poppler-movie-get-filename-test-2413.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include <cstring>
#include <string>
#include <vector>

// Poppler GLib headers
#include <poppler.h>

// ----------------------------------------------------------------------------
// Small helper to capture/silence GLib criticals produced by g_return_val_if_fail
// ----------------------------------------------------------------------------
class ScopedGLogHandler_2413 {
public:
  ScopedGLogHandler_2413(const char *domain, GLogLevelFlags levels)
      : domain_(domain ? domain : ""), levels_(levels) {
    handler_id_ = g_log_set_handler(domain ? domain : nullptr, levels_, &Handler, this);
  }

  ~ScopedGLogHandler_2413() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_.empty() ? nullptr : domain_.c_str(), handler_id_);
    }
  }

  ScopedGLogHandler_2413(const ScopedGLogHandler_2413 &) = delete;
  ScopedGLogHandler_2413 &operator=(const ScopedGLogHandler_2413 &) = delete;

  const std::vector<std::string> &messages() const { return messages_; }

private:
  static void Handler(const gchar *log_domain,
                      GLogLevelFlags log_level,
                      const gchar *message,
                      gpointer user_data) {
    auto *self = static_cast<ScopedGLogHandler_2413 *>(user_data);
    (void)log_domain;
    (void)log_level;
    self->messages_.emplace_back(message ? message : "");
    // swallow message (prevents noisy stderr during tests)
  }

  std::string domain_;
  GLogLevelFlags levels_;
  guint handler_id_{0};
  std::vector<std::string> messages_;
};

// ----------------------------------------------------------------------------

class PopplerMovieTest_2413 : public ::testing::Test {
protected:
  static bool HasFilenameProperty_2413() {
    if (POPPLER_TYPE_MOVIE == 0) {
      return false;
    }
    GObjectClass *klass = G_OBJECT_CLASS(g_type_class_ref(POPPLER_TYPE_MOVIE));
    if (!klass) {
      return false;
    }
    GParamSpec *pspec = g_object_class_find_property(klass, "filename");
    g_type_class_unref(klass);
    return pspec != nullptr;
  }

  static PopplerMovie *NewMovie_2413() {
    // POPPLER_IS_MOVIE implies a GType-based object. Create via g_object_new.
    return POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
  }

  static PopplerMovie *NewMovieWithFilename_2413(const char *filename) {
    // Prefer setting property at construction time when supported.
    if (!HasFilenameProperty_2413()) {
      return nullptr;
    }
    return POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, "filename", filename, nullptr));
  }
};

TEST_F(PopplerMovieTest_2413, Nullptr_ReturnsNull_2413) {
  // g_return_val_if_fail should make this return NULL.
  ScopedGLogHandler_2413 catcher_default(nullptr, G_LOG_LEVEL_CRITICAL);
  const gchar *ret = poppler_movie_get_filename(nullptr);
  EXPECT_EQ(ret, nullptr);

  // Verify observable external interaction: a critical was logged (at least once).
  EXPECT_GE(catcher_default.messages().size(), 1u);
}

TEST_F(PopplerMovieTest_2413, WrongTypePointer_ReturnsNullAndLogsCritical_2413) {
  // Create a plain GObject (not a PopplerMovie), then cast and call.
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  ScopedGLogHandler_2413 catcher_default(nullptr, G_LOG_LEVEL_CRITICAL);
  const gchar *ret = poppler_movie_get_filename(reinterpret_cast<PopplerMovie *>(obj));
  EXPECT_EQ(ret, nullptr);

  // Verify a critical was emitted and (best-effort) contains the type-check expression.
  ASSERT_GE(catcher_default.messages().size(), 1u);
  bool mentions_typecheck = false;
  for (const auto &m : catcher_default.messages()) {
    if (m.find("POPPLER_IS_MOVIE") != std::string::npos) {
      mentions_typecheck = true;
      break;
    }
  }
  EXPECT_TRUE(mentions_typecheck);

  g_object_unref(obj);
}

TEST_F(PopplerMovieTest_2413, ValidObject_ReturnsFilenameSetViaProperty_2413) {
  if (!HasFilenameProperty_2413()) {
    GTEST_SKIP() << "PopplerMovie has no 'filename' GObject property in this build; "
                    "cannot set up an instance with a known filename via public API.";
  }

  PopplerMovie *movie = NewMovieWithFilename_2413("sample_movie.mp4");
  ASSERT_NE(movie, nullptr);
  ASSERT_TRUE(POPPLER_IS_MOVIE(movie));

  const gchar *ret = poppler_movie_get_filename(movie);
  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret, "sample_movie.mp4");

  g_object_unref(movie);
}

TEST_F(PopplerMovieTest_2413, ValidObject_EmptyFilenameBoundary_2413) {
  if (!HasFilenameProperty_2413()) {
    GTEST_SKIP() << "PopplerMovie has no 'filename' GObject property in this build.";
  }

  PopplerMovie *movie = NewMovieWithFilename_2413("");
  ASSERT_NE(movie, nullptr);

  const gchar *ret = poppler_movie_get_filename(movie);
  // Boundary behavior: empty string should round-trip as empty (non-null) if stored.
  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret, "");

  g_object_unref(movie);
}

TEST_F(PopplerMovieTest_2413, GetFilename_IsStableAcrossCalls_2413) {
  if (!HasFilenameProperty_2413()) {
    GTEST_SKIP() << "PopplerMovie has no 'filename' GObject property in this build.";
  }

  PopplerMovie *movie = NewMovieWithFilename_2413("x.avi");
  ASSERT_NE(movie, nullptr);

  const gchar *ret1 = poppler_movie_get_filename(movie);
  const gchar *ret2 = poppler_movie_get_filename(movie);

  ASSERT_NE(ret1, nullptr);
  ASSERT_NE(ret2, nullptr);
  EXPECT_STREQ(ret1, "x.avi");
  EXPECT_STREQ(ret2, "x.avi");
  // Observable behavior: returned pointer is the same internal string pointer.
  EXPECT_EQ(ret1, ret2);

  g_object_unref(movie);
}