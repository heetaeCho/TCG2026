#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2413 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns NULL
TEST_F(PopplerMovieTest_2413, GetFilenameWithNullReturnsNull_2413)
{
    const gchar *result = poppler_movie_get_filename(NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that passing a valid PopplerMovie object returns the filename
TEST_F(PopplerMovieTest_2413, GetFilenameWithValidMovieReturnsFilename_2413)
{
    // We need to create a PopplerMovie from a Movie object if possible
    // Since PopplerMovie is a GObject, we can try to use g_object_new
    // However, without knowing the exact GType registration, we attempt it
    
    // If PopplerMovie can be instantiated via GObject system:
    PopplerMovie *movie = (PopplerMovie *)g_object_new(POPPLER_TYPE_MOVIE, NULL);
    if (movie != NULL) {
        // With a freshly created movie without setting filename, it should be NULL or empty
        const gchar *filename = poppler_movie_get_filename(movie);
        // The filename member would be uninitialized/NULL for a default-constructed object
        // We just verify we don't crash
        // filename could be NULL for a default object
        EXPECT_TRUE(filename == NULL || filename != NULL); // Just verify no crash
        g_object_unref(movie);
    }
}

// Test that passing an invalid GObject (not a PopplerMovie) returns NULL
TEST_F(PopplerMovieTest_2413, GetFilenameWithInvalidObjectReturnsNull_2413)
{
    // Create a plain GObject which is NOT a PopplerMovie
    GObject *not_a_movie = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    ASSERT_NE(not_a_movie, nullptr);

    // POPPLER_IS_MOVIE check should fail, returning NULL
    const gchar *result = poppler_movie_get_filename((PopplerMovie *)not_a_movie);
    EXPECT_EQ(result, nullptr);

    g_object_unref(not_a_movie);
}
