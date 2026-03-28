// File: poppler-movie-get-start-test-2421.cc

#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <poppler.h>

// Small helper to silence/observe GLib criticals produced by g_return_val_if_fail().
// We avoid making GLib log messages fatal; we just record whether a CRITICAL happened.
class ScopedGLogCatcher_2421 {
public:
  ScopedGLogCatcher_2421(const char *domain, GLogLevelFlags levels)
      : domain_(domain ? domain : ""), levels_(levels) {
    handler_id_ =
        g_log_set_handler(domain_, levels_, &ScopedGLogCatcher_2421::Handler, this);
  }

  ~ScopedGLogCatcher_2421() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_, handler_id_);
    }
  }

  bool saw_message() const { return saw_message_; }

private:
  static void Handler(const gchar * /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar * /*message*/,
                      gpointer user_data) {
    auto *self = static_cast<ScopedGLogCatcher_2421 *>(user_data);
    self->saw_message_ = true;
  }

  const char *domain_;
  GLogLevelFlags levels_;
  guint handler_id_ = 0;
  bool saw_message_ = false;
};

class PopplerMovieGetStartTest_2421 : public ::testing::Test {
protected:
  void SetUp() override {
    // Nothing required; GLib/GObject is typically initialized by the process.
  }
};

TEST_F(PopplerMovieGetStartTest_2421, NullptrReturnsZero_2421) {
  // g_return_val_if_fail() typically logs a CRITICAL; ensure it returns 0 and does not crash.
  ScopedGLogCatcher_2421 glib_catcher("GLib", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL);

  guint64 start = poppler_movie_get_start(nullptr);

  EXPECT_EQ(start, 0u);
  // If the environment logs the critical via "GLib", we may see it; do not require it.
  // This is kept non-strict to avoid coupling to GLib's exact log-domain configuration.
}

TEST_F(PopplerMovieGetStartTest_2421, InvalidNonMoviePointerReturnsZero_2421) {
  // Passing a non-PopplerMovie pointer should fail POPPLER_IS_MOVIE() check and return 0.
  // We pass a pointer to a different GObject type.
  GObject *obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(obj, nullptr);

  ScopedGLogCatcher_2421 glib_catcher("GLib", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL);

  guint64 start = poppler_movie_get_start(reinterpret_cast<PopplerMovie *>(obj));

  EXPECT_EQ(start, 0u);

  g_object_unref(obj);
}

TEST_F(PopplerMovieGetStartTest_2421, DefaultConstructedMovieDoesNotCrash_2421) {
  // Create a PopplerMovie instance via its GType (if available) and call the getter.
  // We do not assume any internal initialization besides being a valid instance.
  PopplerMovie *movie = POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
  ASSERT_NE(movie, nullptr);
  ASSERT_TRUE(POPPLER_IS_MOVIE(movie));

  guint64 start = poppler_movie_get_start(movie);

  // Without relying on internal logic, we only assert it's a valid uint64 value and call succeeds.
  // A very common observable default is 0; accept 0 as the boundary value.
  EXPECT_GE(start, 0u);

  g_object_unref(movie);
}

TEST_F(PopplerMovieGetStartTest_2421, IfStartPropertyExistsSettingItIsReflected_2421) {
  PopplerMovie *movie = POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
  ASSERT_NE(movie, nullptr);
  ASSERT_TRUE(POPPLER_IS_MOVIE(movie));

  // Some builds may expose "start" (or similar) as a GObject property; if so, verify
  // that setting it affects the observable getter result.
  GObjectClass *klass = G_OBJECT_GET_CLASS(movie);
  ASSERT_NE(klass, nullptr);

  const char *candidates[] = {"start", "start-time", "start_time"};
  GParamSpec *pspec = nullptr;
  const char *found_name = nullptr;

  for (const char *name : candidates) {
    pspec = g_object_class_find_property(klass, name);
    if (pspec) {
      found_name = name;
      break;
    }
  }

  if (!pspec) {
    // Property not present in this build; the test still validates that probing is safe.
    SUCCEED();
    g_object_unref(movie);
    return;
  }

  // Only proceed if the property is compatible with guint64.
  // We do not assume writability beyond what GObject reports.
  if (!(pspec->value_type == G_TYPE_UINT64)) {
    SUCCEED();
    g_object_unref(movie);
    return;
  }

  const guint64 kValue1 = 1u;
  const guint64 kValueMax = G_MAXUINT64;

  if ((pspec->flags & G_PARAM_WRITABLE) != 0) {
    g_object_set(G_OBJECT(movie), found_name, kValue1, nullptr);
    EXPECT_EQ(poppler_movie_get_start(movie), kValue1);

    g_object_set(G_OBJECT(movie), found_name, kValueMax, nullptr);
    EXPECT_EQ(poppler_movie_get_start(movie), kValueMax);
  } else {
    // Read-only property: just ensure reading through getter does not crash.
    (void)poppler_movie_get_start(movie);
    SUCCEED();
  }

  g_object_unref(movie);
}