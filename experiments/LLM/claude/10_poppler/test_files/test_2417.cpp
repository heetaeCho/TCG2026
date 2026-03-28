#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler movie header
extern "C" {
#include "poppler-movie.h"
}

// We need access to the PopplerMovie structure to set up test fixtures
// Based on the known dependencies, we know the structure layout
extern "C" {

// Forward declarations for GObject-based creation
// We'll use g_object_new to create PopplerMovie instances

class PopplerMovieTest_2417 : public ::testing::Test {
protected:
    PopplerMovie *movie = nullptr;

    void SetUp() override {
        movie = static_cast<PopplerMovie *>(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
    }

    void TearDown() override {
        if (movie) {
            g_object_unref(movie);
            movie = nullptr;
        }
    }
};

// Test that is_synchronous returns FALSE by default (default initialized)
TEST_F(PopplerMovieTest_2417, IsSynchronousDefaultValue_2417)
{
    gboolean result = poppler_movie_is_synchronous(movie);
    // Default value after g_object_new should be FALSE (0)
    EXPECT_EQ(result, FALSE);
}

// Test that passing NULL returns FALSE (g_return_val_if_fail behavior)
TEST_F(PopplerMovieTest_2417, IsSynchronousWithNull_2417)
{
    // g_return_val_if_fail with NULL should return FALSE
    // This will trigger a GLib warning, but should not crash
    gboolean result = poppler_movie_is_synchronous(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test that the movie object is valid after creation
TEST_F(PopplerMovieTest_2417, MovieObjectIsValid_2417)
{
    EXPECT_TRUE(POPPLER_IS_MOVIE(movie));
}

// Test that a non-movie GObject fails the type check
TEST_F(PopplerMovieTest_2417, IsSynchronousWithWrongType_2417)
{
    // Create a plain GObject (not a PopplerMovie)
    GObject *not_a_movie = static_cast<GObject *>(g_object_new(G_TYPE_OBJECT, nullptr));
    
    // g_return_val_if_fail should return FALSE for wrong type
    gboolean result = poppler_movie_is_synchronous(reinterpret_cast<PopplerMovie *>(not_a_movie));
    EXPECT_EQ(result, FALSE);
    
    g_object_unref(not_a_movie);
}

// Test poppler_movie_get_filename with a valid movie returns something (possibly NULL if not set)
TEST_F(PopplerMovieTest_2417, GetFilenameDefault_2417)
{
    const gchar *filename = poppler_movie_get_filename(movie);
    // Default filename may be NULL
    // We just verify it doesn't crash
    SUCCEED();
}

// Test poppler_movie_get_filename with NULL
TEST_F(PopplerMovieTest_2417, GetFilenameWithNull_2417)
{
    const gchar *filename = poppler_movie_get_filename(nullptr);
    EXPECT_EQ(filename, nullptr);
}

// Test poppler_movie_need_poster with default value
TEST_F(PopplerMovieTest_2417, NeedPosterDefault_2417)
{
    gboolean result = poppler_movie_need_poster(movie);
    // Default should be FALSE
    EXPECT_EQ(result, FALSE);
}

// Test poppler_movie_need_poster with NULL
TEST_F(PopplerMovieTest_2417, NeedPosterWithNull_2417)
{
    gboolean result = poppler_movie_need_poster(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test poppler_movie_get_play_mode with default value
TEST_F(PopplerMovieTest_2417, GetPlayModeDefault_2417)
{
    PopplerMoviePlayMode mode = poppler_movie_get_play_mode(movie);
    // Default play mode
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test poppler_movie_get_play_mode with NULL
TEST_F(PopplerMovieTest_2417, GetPlayModeWithNull_2417)
{
    PopplerMoviePlayMode mode = poppler_movie_get_play_mode(nullptr);
    // Should return a default/safe value
    SUCCEED();
}

// Test poppler_movie_get_rate with default value
TEST_F(PopplerMovieTest_2417, GetRateDefault_2417)
{
    gdouble rate = poppler_movie_get_rate(movie);
    // We just verify it doesn't crash and returns some value
    SUCCEED();
}

// Test poppler_movie_get_rotation_angle with default value
TEST_F(PopplerMovieTest_2417, GetRotationAngleDefault_2417)
{
    gushort angle = poppler_movie_get_rotation_angle(movie);
    // Default rotation angle
    EXPECT_GE(angle, 0);
}

// Test poppler_movie_get_duration with default
TEST_F(PopplerMovieTest_2417, GetDurationDefault_2417)
{
    guint64 duration = poppler_movie_get_duration(movie);
    SUCCEED();
}

// Test poppler_movie_get_aspect with default
TEST_F(PopplerMovieTest_2417, GetAspectDefault_2417)
{
    gint width = 0, height = 0;
    poppler_movie_get_aspect(movie, &width, &height);
    // Just verify no crash
    SUCCEED();
}

// Test poppler_movie_is_synchronous with NULL returns FALSE
TEST_F(PopplerMovieTest_2417, IsSynchronousReturnsFalseForNull_2417)
{
    EXPECT_FALSE(poppler_movie_is_synchronous(nullptr));
}

}  // extern "C"
#include <glib-object.h>
#include <gtest/gtest.h>
#include "poppler-movie.h"

class PopplerMovieTest_2417 : public ::testing::Test {
protected:
    PopplerMovie *movie = nullptr;

    void SetUp() override {
        movie = static_cast<PopplerMovie *>(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
    }

    void TearDown() override {
        if (movie) {
            g_object_unref(movie);
            movie = nullptr;
        }
    }
};

// Test that is_synchronous returns FALSE by default
TEST_F(PopplerMovieTest_2417, IsSynchronousDefaultValue_2417)
{
    gboolean result = poppler_movie_is_synchronous(movie);
    EXPECT_EQ(result, FALSE);
}

// Test that passing NULL returns FALSE (g_return_val_if_fail behavior)
TEST_F(PopplerMovieTest_2417, IsSynchronousWithNull_2417)
{
    gboolean result = poppler_movie_is_synchronous(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test that the movie object is valid after creation
TEST_F(PopplerMovieTest_2417, MovieObjectIsValid_2417)
{
    EXPECT_TRUE(POPPLER_IS_MOVIE(movie));
}

// Test that a non-movie GObject fails the type check
TEST_F(PopplerMovieTest_2417, IsSynchronousWithWrongType_2417)
{
    GObject *not_a_movie = static_cast<GObject *>(g_object_new(G_TYPE_OBJECT, nullptr));
    gboolean result = poppler_movie_is_synchronous(reinterpret_cast<PopplerMovie *>(not_a_movie));
    EXPECT_EQ(result, FALSE);
    g_object_unref(not_a_movie);
}

// Test poppler_movie_need_poster with default value
TEST_F(PopplerMovieTest_2417, NeedPosterDefault_2417)
{
    gboolean result = poppler_movie_need_poster(movie);
    EXPECT_EQ(result, FALSE);
}

// Test poppler_movie_need_poster with NULL
TEST_F(PopplerMovieTest_2417, NeedPosterWithNull_2417)
{
    gboolean result = poppler_movie_need_poster(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test poppler_movie_get_play_mode with default value
TEST_F(PopplerMovieTest_2417, GetPlayModeDefault_2417)
{
    PopplerMoviePlayMode mode = poppler_movie_get_play_mode(movie);
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test poppler_movie_get_filename with a valid movie
TEST_F(PopplerMovieTest_2417, GetFilenameDefault_2417)
{
    const gchar *filename = poppler_movie_get_filename(movie);
    // Default filename may be NULL - just verify no crash
    SUCCEED();
}

// Test poppler_movie_get_filename with NULL
TEST_F(PopplerMovieTest_2417, GetFilenameWithNull_2417)
{
    const gchar *filename = poppler_movie_get_filename(nullptr);
    EXPECT_EQ(filename, nullptr);
}

// Test poppler_movie_get_rotation_angle with default value
TEST_F(PopplerMovieTest_2417, GetRotationAngleDefault_2417)
{
    gushort angle = poppler_movie_get_rotation_angle(movie);
    EXPECT_GE(angle, 0);
}

// Test poppler_movie_is_synchronous returns FALSE consistently for NULL
TEST_F(PopplerMovieTest_2417, IsSynchronousReturnsFalseForNullConsistently_2417)
{
    EXPECT_FALSE(poppler_movie_is_synchronous(nullptr));
    EXPECT_FALSE(poppler_movie_is_synchronous(nullptr));
}
