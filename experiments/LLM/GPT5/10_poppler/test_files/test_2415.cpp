// File: poppler-movie-show-controls-test_2415.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// A small helper to catch GLib log messages (including g_return_val_if_fail()).
class GlibLogCatcher_2415 {
public:
  GlibLogCatcher_2415() {
    prev_ = g_log_set_default_handler(&GlibLogCatcher_2415::Handler, this);
  }

  ~GlibLogCatcher_2415() {
    g_log_set_default_handler(prev_, nullptr);
  }

  void Reset() {
    critical_count_ = 0;
    warning_count_ = 0;
    last_domain_.clear();
    last_message_.clear();
  }

  int critical_count() const { return critical_count_; }
  int warning_count() const { return warning_count_; }
  const std::string &last_domain() const { return last_domain_; }
  const std::string &last_message() const { return last_message_; }

private:
  static void Handler(const gchar *log_domain,
                      GLogLevelFlags log_level,
                      const gchar *message,
                      gpointer user_data) {
    auto *self = static_cast<GlibLogCatcher_2415 *>(user_data);

    // Record some info for assertions/debugging.
    self->last_domain_ = log_domain ? log_domain : "";
    self->last_message_ = message ? message : "";

    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->critical_count_++;
      return; // swallow
    }
    if (log_level & G_LOG_LEVEL_WARNING) {
      self->warning_count_++;
      return; // swallow
    }

    // For other levels, keep default behavior muted (swallow).
  }

  GLogFunc prev_ = nullptr;
  int critical_count_ = 0;
  int warning_count_ = 0;
  std::string last_domain_;
  std::string last_message_;
};

class PopplerMovieTest_2415 : public ::testing::Test {
protected:
  void SetUp() override { catcher_.Reset(); }
  void TearDown() override {}

  static GParamSpec *FindShowControlsProperty_2415(GObject *obj) {
    if (!obj) {
      return nullptr;
    }
    GObjectClass *klass = G_OBJECT_GET_CLASS(obj);
    if (!klass) {
      return nullptr;
    }

    // Try a couple of plausible public property spellings (no internal access).
    if (auto *ps = g_object_class_find_property(klass, "show-controls")) {
      return ps;
    }
    if (auto *ps = g_object_class_find_property(klass, "show_controls")) {
      return ps;
    }
    return nullptr;
  }

  GlibLogCatcher_2415 catcher_;
};

TEST_F(PopplerMovieTest_2415, NullPointerReturnsFalseAndLogsCritical_2415) {
  // Boundary/error case: NULL input should trigger g_return_val_if_fail and return FALSE.
  catcher_.Reset();
  gboolean ret = poppler_movie_show_controls(nullptr);
  EXPECT_EQ(ret, FALSE);
  EXPECT_GE(catcher_.critical_count(), 1) << "Expected a CRITICAL log for NULL input.";
}

TEST_F(PopplerMovieTest_2415, InvalidTypeReturnsFalseAndLogsCritical_2415) {
  // Boundary/error case: non-PopplerMovie instance should fail POPPLER_IS_MOVIE check.
  catcher_.Reset();

  GObject *not_a_movie = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_movie, nullptr);

  gboolean ret = poppler_movie_show_controls(reinterpret_cast<PopplerMovie *>(not_a_movie));
  EXPECT_EQ(ret, FALSE);
  EXPECT_GE(catcher_.critical_count(), 1) << "Expected a CRITICAL log for invalid type.";

  g_object_unref(not_a_movie);
}

TEST_F(PopplerMovieTest_2415, ValidObjectDoesNotLogCritical_2415) {
  // Normal operation (as observable): calling with a valid object should not hit g_return checks.
  // We avoid assuming any specific default return value.
  catcher_.Reset();

  PopplerMovie *movie = POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
  ASSERT_NE(movie, nullptr);

  (void)poppler_movie_show_controls(movie);
  EXPECT_EQ(catcher_.critical_count(), 0) << "Did not expect CRITICAL logs for valid object.";

  g_object_unref(movie);
}

TEST_F(PopplerMovieTest_2415, ReturnValueIsStableAcrossRepeatedCalls_2415) {
  // Boundary-ish: repeated calls without mutation should be consistent.
  catcher_.Reset();

  PopplerMovie *movie = POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
  ASSERT_NE(movie, nullptr);

  gboolean first = poppler_movie_show_controls(movie);
  gboolean second = poppler_movie_show_controls(movie);

  EXPECT_EQ(catcher_.critical_count(), 0);
  EXPECT_EQ(first, second);

  g_object_unref(movie);
}

TEST_F(PopplerMovieTest_2415, ShowControlsReflectsPublicPropertyIfAvailable_2415) {
  // Normal operation: if the type publicly exposes a boolean property for show-controls,
  // setting it via GObject should be reflected by poppler_movie_show_controls().
  //
  // If such a property doesn't exist in this build/version, skip (no inference of internals).
  catcher_.Reset();

  PopplerMovie *movie = POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
  ASSERT_NE(movie, nullptr);

  GParamSpec *pspec = FindShowControlsProperty_2415(G_OBJECT(movie));
  if (!pspec) {
    g_object_unref(movie);
    GTEST_SKIP() << "PopplerMovie has no public 'show-controls' property in this build.";
  }

  // Ensure it's a boolean property before using it.
  if (!G_IS_PARAM_SPEC_BOOLEAN(pspec)) {
    g_object_unref(movie);
    GTEST_SKIP() << "PopplerMovie 'show-controls' property is not boolean in this build.";
  }

  const char *prop_name =
      g_strcmp0(pspec->name, "show-controls") == 0 ? "show-controls" : pspec->name;

  // Set TRUE -> expect TRUE
  catcher_.Reset();
  g_object_set(G_OBJECT(movie), prop_name, TRUE, nullptr);
  EXPECT_EQ(catcher_.critical_count(), 0);

  gboolean ret_true = poppler_movie_show_controls(movie);
  EXPECT_EQ(ret_true, TRUE);

  // Set FALSE -> expect FALSE
  catcher_.Reset();
  g_object_set(G_OBJECT(movie), prop_name, FALSE, nullptr);
  EXPECT_EQ(catcher_.critical_count(), 0);

  gboolean ret_false = poppler_movie_show_controls(movie);
  EXPECT_EQ(ret_false, FALSE);

  g_object_unref(movie);
}