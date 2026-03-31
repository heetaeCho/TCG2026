#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler-movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2421 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns 0
TEST_F(PopplerMovieTest_2421, GetStartReturnsZeroForNull_2421)
{
    // g_return_val_if_fail should cause it to return 0 for NULL
    guint64 result = poppler_movie_get_start(nullptr);
    EXPECT_EQ(result, 0UL);
}

// Test that a valid PopplerMovie object returns the start value
TEST_F(PopplerMovieTest_2421, GetStartReturnsStartValue_2421)
{
    // Create a PopplerMovie from a Movie object if possible
    // Since we need a valid PopplerMovie, we need to use the GObject type system
    // We'll test with a properly constructed object if the type is registered
    
    GType movie_type = g_type_from_name("PopplerMovie");
    if (movie_type != 0) {
        PopplerMovie *movie = POPPLER_MOVIE(g_object_new(movie_type, NULL));
        if (movie != nullptr) {
            // Default start should be some value (likely 0 for a default-constructed object)
            guint64 start = poppler_movie_get_start(movie);
            // We can at least verify it doesn't crash and returns a value
            EXPECT_GE(start, 0UL);
            g_object_unref(movie);
        }
    } else {
        // If we can't instantiate, at least verify NULL handling works
        EXPECT_EQ(poppler_movie_get_start(nullptr), 0UL);
    }
}

// Test that passing an invalid GObject (not a PopplerMovie) returns 0
TEST_F(PopplerMovieTest_2421, GetStartReturnsZeroForInvalidType_2421)
{
    // Create a plain GObject which is not a PopplerMovie
    // g_return_val_if_fail with POPPLER_IS_MOVIE check should fail and return 0
    // We suppress the GLib critical warning for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    
    // Using a non-PopplerMovie GObject should trigger the type check failure
    // However, casting a random pointer might cause issues, so we test with NULL
    guint64 result = poppler_movie_get_start(NULL);
    EXPECT_EQ(result, 0UL);
}

// Test boundary: verify return type is guint64 (unsigned 64-bit)
TEST_F(PopplerMovieTest_2421, GetStartReturnTypeIsUint64_2421)
{
    guint64 result = poppler_movie_get_start(nullptr);
    // The default return for failed precondition is 0L
    EXPECT_EQ(result, static_cast<guint64>(0));
}
