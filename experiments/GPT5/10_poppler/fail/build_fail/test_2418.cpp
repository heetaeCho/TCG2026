// File: poppler-movie-get-volume-test_2418.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include <cmath>

// Poppler GLib headers (available in the real codebase build).
// Keep include flexible across distros/trees.
#if __has_include(<poppler.h>)
#include <poppler.h>
#elif __has_include(<poppler/glib/poppler.h>)
#include <poppler/glib/poppler.h>
#else
#include "poppler.h"
#endif

namespace {

class PopplerMovieTest_2418 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    // Ensure GType system is initialized for older GLib (newer GLib does this automatically).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  static bool HasPopplerMovieType() {
#ifdef POPPLER_TYPE_MOVIE
    // Force type registration if needed.
    (void)POPPLER_TYPE_MOVIE;
    return g_type_from_name("PopplerMovie") != 0 || POPPLER_TYPE_MOVIE != 0;
#else
    return false;
#endif
  }

  static PopplerMovie* TryCreateMovie() {
#ifdef POPPLER_TYPE_MOVIE
    if (!HasPopplerMovieType())
      return nullptr;

    GObject* obj = G_OBJECT(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
    if (!obj)
      return nullptr;
    return POPPLER_MOVIE(obj);
#else
    return nullptr;
#endif
  }

  // Returns nullptr if property doesn't exist or isn't a double property.
  static GParamSpecDouble* FindDoubleProperty(GObject* obj, const char* name) {
    if (!obj || !name)
      return nullptr;

    GObjectClass* klass = G_OBJECT_GET_CLASS(obj);
    if (!klass)
      return nullptr;

    GParamSpec* pspec = g_object_class_find_property(klass, name);
    if (!pspec)
      return nullptr;

    if (G_IS_PARAM_SPEC_DOUBLE(pspec))
      return G_PARAM_SPEC_DOUBLE(pspec);

    return nullptr;
  }
};

TEST_F(PopplerMovieTest_2418, NullMovieReturnsZero_2418) {
  // Verify g_return_val_if_fail observable behavior: return value is 0.
  EXPECT_DOUBLE_EQ(poppler_movie_get_volume(nullptr), 0.0);
}

TEST_F(PopplerMovieTest_2418, WrongTypeReturnsZero_2418) {
  // Pass a non-PopplerMovie GObject to trigger POPPLER_IS_MOVIE() failure.
  GObject* not_movie = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_movie, nullptr);

  EXPECT_DOUBLE_EQ(poppler_movie_get_volume(reinterpret_cast<PopplerMovie*>(not_movie)), 0.0);

  g_object_unref(not_movie);
}

TEST_F(PopplerMovieTest_2418, NullMovieEmitsCriticalLog_2418) {
  // Verify external interaction (GLib critical log) from g_return_val_if_fail.
  // log_domain == NULL matches any domain.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
  (void)poppler_movie_get_volume(nullptr);
  g_test_assert_expected_messages();
}

TEST_F(PopplerMovieTest_2418, WrongTypeEmitsCriticalLog_2418) {
  GObject* not_movie = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_movie, nullptr);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
  (void)poppler_movie_get_volume(reinterpret_cast<PopplerMovie*>(not_movie));
  g_test_assert_expected_messages();

  g_object_unref(not_movie);
}

TEST_F(PopplerMovieTest_2418, ValidMovieReturnsFiniteValue_2418) {
  PopplerMovie* movie = TryCreateMovie();
  if (!movie) {
    GTEST_SKIP() << "PopplerMovie GType not available in this build.";
  }

  const gdouble vol = poppler_movie_get_volume(movie);
  EXPECT_TRUE(std::isfinite(static_cast<double>(vol)));

  g_object_unref(movie);
}

TEST_F(PopplerMovieTest_2418, VolumeMatchesGObjectPropertyWhenAvailable_2418) {
  PopplerMovie* movie = TryCreateMovie();
  if (!movie) {
    GTEST_SKIP() << "PopplerMovie GType not available in this build.";
  }

  // Some builds may expose "volume" as a GObject property. If it does, verify that
  // setting it changes what poppler_movie_get_volume() returns (observable behavior).
  GParamSpecDouble* pspec = FindDoubleProperty(G_OBJECT(movie), "volume");
  if (!pspec) {
    g_object_unref(movie);
    GTEST_SKIP() << "PopplerMovie does not expose a double 'volume' GObject property.";
  }

  // Choose a safe in-range value based on the property spec (no assumptions about range).
  const gdouble minv = pspec->minimum;
  const gdouble maxv = pspec->maximum;
  ASSERT_LE(minv, maxv);

  const gdouble mid = (minv / 2.0) + (maxv / 2.0);  // avoids overflow vs (min+max)/2
  g_object_set(G_OBJECT(movie), "volume", mid, nullptr);

  EXPECT_DOUBLE_EQ(poppler_movie_get_volume(movie), mid);

  g_object_unref(movie);
}

TEST_F(PopplerMovieTest_2418, VolumePropertyBoundaryValuesWhenAvailable_2418) {
  PopplerMovie* movie = TryCreateMovie();
  if (!movie) {
    GTEST_SKIP() << "PopplerMovie GType not available in this build.";
  }

  GParamSpecDouble* pspec = FindDoubleProperty(G_OBJECT(movie), "volume");
  if (!pspec) {
    g_object_unref(movie);
    GTEST_SKIP() << "PopplerMovie does not expose a double 'volume' GObject property.";
  }

  const gdouble minv = pspec->minimum;
  const gdouble maxv = pspec->maximum;
  ASSERT_LE(minv, maxv);

  // Boundary: minimum
  g_object_set(G_OBJECT(movie), "volume", minv, nullptr);
  EXPECT_DOUBLE_EQ(poppler_movie_get_volume(movie), minv);

  // Boundary: maximum
  g_object_set(G_OBJECT(movie), "volume", maxv, nullptr);
  EXPECT_DOUBLE_EQ(poppler_movie_get_volume(movie), maxv);

  g_object_unref(movie);
}

}  // namespace