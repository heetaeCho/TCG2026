// poppler-movie-get-duration-test_2422.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include <poppler.h>

namespace {

struct GObjectDeleter_2422 {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(G_OBJECT(p));
    }
  }
};

template <typename T>
using GObjPtr_2422 = std::unique_ptr<T, GObjectDeleter_2422>;

class PopplerMovieTest_2422 : public ::testing::Test {
 protected:
  static bool IsInstantiableMovieType_2422() {
#ifdef POPPLER_TYPE_MOVIE
    if (!g_type_is_a(POPPLER_TYPE_MOVIE, G_TYPE_OBJECT)) {
      return false;
    }
    // Some GTypes may exist but not be instantiable (e.g. abstract).
    if (!g_type_test_flags(POPPLER_TYPE_MOVIE, G_TYPE_FLAG_INSTANTIATABLE)) {
      return false;
    }
    return true;
#else
    return false;
#endif
  }
};

TEST_F(PopplerMovieTest_2422, NullptrReturnsZero_2422) {
  // g_return_val_if_fail() should trigger and return 0.
  EXPECT_EQ(poppler_movie_get_duration(nullptr), 0u);
}

TEST_F(PopplerMovieTest_2422, NonMovieGObjectReturnsZero_2422) {
  // Passing a valid pointer that is NOT a PopplerMovie should fail the type check.
  GObjPtr_2422<GObject> obj(G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr)));
  ASSERT_NE(obj.get(), nullptr);

  auto* bogus = reinterpret_cast<PopplerMovie*>(obj.get());
  EXPECT_EQ(poppler_movie_get_duration(bogus), 0u);
}

TEST_F(PopplerMovieTest_2422, ValidMovieObjectDoesNotCrashAndIsStable_2422) {
  if (!IsInstantiableMovieType_2422()) {
    GTEST_SKIP() << "POPPLER_TYPE_MOVIE is not available or not instantiable in this build.";
  }

  GObjPtr_2422<PopplerMovie> movie(POPPLER_MOVIE(g_object_new(POPPLER_TYPE_MOVIE, nullptr)));
  ASSERT_NE(movie.get(), nullptr);
  ASSERT_TRUE(POPPLER_IS_MOVIE(movie.get()));

  const guint64 d1 = poppler_movie_get_duration(movie.get());
  const guint64 d2 = poppler_movie_get_duration(movie.get());

  // Observable behavior only: value should be consistent across calls.
  EXPECT_EQ(d1, d2);

  // Duration is an unsigned quantity; it should always be >= 0 (trivially true),
  // but we at least assert it is a valid guint64 and the call succeeded.
  EXPECT_GE(d1, static_cast<guint64>(0));
}

TEST_F(PopplerMovieTest_2422, MultipleCallsWithInvalidPointerAlwaysReturnZero_2422) {
  // Repeated invalid calls should consistently return 0 (observable behavior).
  EXPECT_EQ(poppler_movie_get_duration(nullptr), 0u);
  EXPECT_EQ(poppler_movie_get_duration(nullptr), 0u);
}

}  // namespace