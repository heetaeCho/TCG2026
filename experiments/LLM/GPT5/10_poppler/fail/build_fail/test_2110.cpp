// poppler_annot_movie_get_movie_test.cpp
//
// Unit tests for poppler_annot_movie_get_movie().
//
// Constraints respected:
// - Treat implementation as black box (no internal logic inference).
// - No private/internal state access.
// - Use only observable behavior via public API (GObject properties if present).
// - Include normal, boundary, and error/exceptional (death) cases where observable.

#include <gtest/gtest.h>

#include <glib-object.h>

// Opaque forward declarations are sufficient for this unit test.
typedef struct _PopplerAnnotMovie PopplerAnnotMovie;
typedef struct _PopplerMovie PopplerMovie;

extern "C" {
PopplerMovie *poppler_annot_movie_get_movie(PopplerAnnotMovie *poppler_annot);
}

namespace {

class PopplerAnnotMovieGetMovieTest_2110 : public ::testing::Test {
protected:
  static GType GetTypeOrSkip(const char *type_name) {
    const GType t = g_type_from_name(type_name);
    if (t == 0) {
      GTEST_SKIP() << "Required GType not registered: " << type_name;
    }
    return t;
  }

  static GObject *NewObjectOrSkip(const char *type_name) {
    const GType t = GetTypeOrSkip(type_name);
    GObject *obj = G_OBJECT(g_object_new(t, nullptr));
    if (!obj) {
      GTEST_SKIP() << "Failed to construct GObject of type: " << type_name;
    }
    return obj;
  }

  static GParamSpec *FindPropertyOrNull(GObject *obj, const char *prop_name) {
    if (!obj) return nullptr;
    GObjectClass *klass = G_OBJECT_GET_CLASS(obj);
    if (!klass) return nullptr;
    return g_object_class_find_property(klass, prop_name);
  }
};

TEST_F(PopplerAnnotMovieGetMovieTest_2110, ReturnsNullForNewObjectWhenMovieUnset_2110) {
  // Normal/baseline: A freshly-constructed object should have a well-defined
  // default; if movie isn't set, we expect nullptr (common for unset pointers).
  // If the type isn't constructible in this build, we skip.
  GObject *annot_obj = NewObjectOrSkip("PopplerAnnotMovie");
  auto *annot = reinterpret_cast<PopplerAnnotMovie *>(annot_obj);

  PopplerMovie *movie = poppler_annot_movie_get_movie(annot);
  EXPECT_EQ(movie, nullptr);

  g_object_unref(annot_obj);
}

TEST_F(PopplerAnnotMovieGetMovieTest_2110, PropertyRoundTripMoviePointerWhenPropertyExists_2110) {
  // Observable external interaction: if PopplerAnnotMovie exposes a "movie"
  // GObject property, setting it should be reflected by the getter.
  GObject *annot_obj = NewObjectOrSkip("PopplerAnnotMovie");

  // Only run this test if the "movie" property exists; otherwise, skip instead
  // of assuming internal structure.
  if (!FindPropertyOrNull(annot_obj, "movie")) {
    g_object_unref(annot_obj);
    GTEST_SKIP() << "PopplerAnnotMovie does not expose a GObject property named 'movie' in this build.";
  }

  // Construct a PopplerMovie object if available; otherwise skip.
  GObject *movie_obj = NewObjectOrSkip("PopplerMovie");

  // Set property and verify getter returns the same pointer.
  g_object_set(annot_obj, "movie", movie_obj, nullptr);

  auto *annot = reinterpret_cast<PopplerAnnotMovie *>(annot_obj);
  PopplerMovie *got = poppler_annot_movie_get_movie(annot);

  EXPECT_EQ(got, reinterpret_cast<PopplerMovie *>(movie_obj));

  // Boundary: set to NULL and verify.
  g_object_set(annot_obj, "movie", nullptr, nullptr);
  got = poppler_annot_movie_get_movie(annot);
  EXPECT_EQ(got, nullptr);

  g_object_unref(movie_obj);
  g_object_unref(annot_obj);
}

TEST_F(PopplerAnnotMovieGetMovieTest_2110, NullPointerInputDeathOrSafeHandling_2110) {
  // Exceptional/error case: Passing nullptr may be invalid and could crash.
  // We accept either behavior as observable (some builds may add guards).
  //
  // If it crashes -> death test passes.
  // If it does not crash -> we also accept returning nullptr.
#if GTEST_HAS_DEATH_TEST
  // Try death test first; if it doesn't die, fall back to a normal expectation.
  // Note: We cannot "catch" a failed death test and continue, so we structure
  // this as an "either/or" by doing a non-death check when death tests aren't
  // supported.
  EXPECT_DEATH_IF_SUPPORTED(
      {
        (void)poppler_annot_movie_get_movie(nullptr);
      },
      ".*");
#else
  EXPECT_EQ(poppler_annot_movie_get_movie(nullptr), nullptr);
#endif
}

}  // namespace