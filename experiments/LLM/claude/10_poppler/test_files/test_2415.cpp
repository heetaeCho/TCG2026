#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler-movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2415 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a PopplerMovie from a Movie object if possible
// Since we're treating the implementation as a black box, we need to use
// the public API to create PopplerMovie instances.

// Test that poppler_movie_show_controls returns FALSE for NULL input
TEST_F(PopplerMovieTest_2415, ShowControlsReturnsfalseForNull_2415) {
    // g_return_val_if_fail should return FALSE for NULL
    // This will produce a g_critical warning, so we suppress it
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    gboolean result = poppler_movie_show_controls(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, FALSE);
}

// Test that poppler_movie_show_controls returns FALSE for invalid (non-PopplerMovie) GObject
TEST_F(PopplerMovieTest_2415, ShowControlsReturnsFalseForInvalidObject_2415) {
    // Create a plain GObject which is not a PopplerMovie
    GObject *invalid_obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    gboolean result = poppler_movie_show_controls((PopplerMovie *)invalid_obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, FALSE);
    
    g_object_unref(invalid_obj);
}

// Test that PopplerMovie type is properly registered
TEST_F(PopplerMovieTest_2415, TypeIsRegistered_2415) {
    GType type = poppler_movie_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that poppler_movie_play_mode enum type exists and is valid
TEST_F(PopplerMovieTest_2415, PlayModeTypeExists_2415) {
    GType type = poppler_movie_play_mode_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}
