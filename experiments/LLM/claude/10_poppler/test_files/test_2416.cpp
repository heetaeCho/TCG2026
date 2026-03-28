#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMoviePlayModeTest_2416 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns POPPLER_MOVIE_PLAY_MODE_ONCE (default/error value)
TEST_F(PopplerMoviePlayModeTest_2416, NullMovieReturnsDefaultPlayMode_2416)
{
    // Passing NULL should trigger g_return_val_if_fail and return default
    // This will produce a GLib warning, but should return the default value
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    PopplerMoviePlayMode mode = poppler_movie_get_play_mode(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(mode, POPPLER_MOVIE_PLAY_MODE_ONCE);
}

// Test that an invalid GObject (not a PopplerMovie) returns default play mode
TEST_F(PopplerMoviePlayModeTest_2416, InvalidObjectReturnsDefaultPlayMode_2416)
{
    // Create a generic GObject that is not a PopplerMovie
    GObject *not_a_movie = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    PopplerMoviePlayMode mode = poppler_movie_get_play_mode((PopplerMovie *)not_a_movie);
    g_test_assert_expected_messages();
    EXPECT_EQ(mode, POPPLER_MOVIE_PLAY_MODE_ONCE);
    
    g_object_unref(not_a_movie);
}

// Test that the return type is PopplerMoviePlayMode enum
TEST_F(PopplerMoviePlayModeTest_2416, ReturnTypeIsPopplerMoviePlayMode_2416)
{
    // Verify that POPPLER_MOVIE_PLAY_MODE_ONCE is a valid enum value
    // by checking NULL case returns it
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    PopplerMoviePlayMode result = poppler_movie_get_play_mode(nullptr);
    g_test_assert_expected_messages();
    
    // The result should be a valid PopplerMoviePlayMode value
    EXPECT_GE((int)result, 0);
}
