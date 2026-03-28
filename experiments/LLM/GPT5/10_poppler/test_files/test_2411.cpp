// poppler-movie-class-init-test_2411.cc
#include <gtest/gtest.h>

#if __has_include(<glib-object.h>)
#include <glib-object.h>
#endif

// -----------------------------------------------------------------------------
// Minimal compatibility shims (only when GLib headers are not available).
// We keep this strictly to "what's needed to compile and observe behavior".
// -----------------------------------------------------------------------------
#if !__has_include(<glib-object.h>)
extern "C" {

// Minimal GObjectClass containing only the observable field used by the code.
typedef void (*GObjectFinalizeFunc)(void *object);

typedef struct _GObjectClass {
  GObjectFinalizeFunc finalize;
} GObjectClass;

// The code under test uses G_OBJECT_CLASS(klass). Provide a compatible shim.
static inline GObjectClass *G_OBJECT_CLASS(void *klass) {
  return reinterpret_cast<GObjectClass *>(klass);
}

}  // extern "C"
#endif

// -----------------------------------------------------------------------------
// Ensure PopplerMovieClass is layout-compatible with how the code under test
// treats it: it is passed to G_OBJECT_CLASS(klass) and then its ->finalize is set.
// The simplest observable-compatible layout is "GObjectClass as first member".
// -----------------------------------------------------------------------------
extern "C" {
struct _PopplerMovieClass {
#if __has_include(<glib-object.h>)
  GObjectClass parent_class;
#else
  GObjectClass parent_class;
#endif
};
typedef struct _PopplerMovieClass PopplerMovieClass;
}  // extern "C"

// Include the .cc directly so the static function is in the same translation unit.
#include "./TestProjects/poppler/glib/poppler-movie.cc"

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

class PopplerMovieClassInitTest_2411 : public ::testing::Test {};

TEST_F(PopplerMovieClassInitTest_2411, SetsFinalizeToPopplerMovieFinalize_2411) {
  PopplerMovieClass klass{};
  klass.parent_class.finalize = reinterpret_cast<decltype(klass.parent_class.finalize)>(0x1);

  // Call the function under test (static, but visible because we included the .cc)
  poppler_movie_class_init(&klass);

  // Observable effect: finalize pointer is set to poppler_movie_finalize.
  EXPECT_EQ(klass.parent_class.finalize, poppler_movie_finalize);
}

TEST_F(PopplerMovieClassInitTest_2411, OverwritesExistingFinalizePointer_2411) {
  PopplerMovieClass klass{};

  // Set a distinct non-null value to ensure the assignment happens.
  auto previous =
      reinterpret_cast<decltype(klass.parent_class.finalize)>(0xDEADBEEF);
  klass.parent_class.finalize = previous;

  poppler_movie_class_init(&klass);

  EXPECT_NE(klass.parent_class.finalize, previous);
  EXPECT_EQ(klass.parent_class.finalize, poppler_movie_finalize);
}