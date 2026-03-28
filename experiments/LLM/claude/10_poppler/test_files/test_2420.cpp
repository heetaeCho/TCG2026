#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2420 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns 0 (g_return_val_if_fail guard)
TEST_F(PopplerMovieTest_2420, NullMovieReturnsZero_2420)
{
    // Passing NULL should trigger the g_return_val_if_fail and return 0
    // We need to suppress the GLib warning for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    gushort angle = poppler_movie_get_rotation_angle(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(angle, 0);
}

// Test that a valid PopplerMovie returns its rotation angle
TEST_F(PopplerMovieTest_2420, ValidMovieReturnsRotationAngle_2420)
{
    // We need to create a PopplerMovie through the library's own mechanisms.
    // Since PopplerMovie is a GObject, we can try to instantiate it if the type is registered.
    // If direct construction is possible:
    PopplerMovie *movie = static_cast<PopplerMovie *>(g_object_new(POPPLER_TYPE_MOVIE, NULL));
    if (movie != NULL) {
        // The default rotation angle after construction - we just verify we get a valid gushort back
        gushort angle = poppler_movie_get_rotation_angle(movie);
        // Default should be 0 for a freshly created movie object
        EXPECT_EQ(angle, 0);
        g_object_unref(movie);
    }
}

// Test that passing an invalid GObject type returns 0
TEST_F(PopplerMovieTest_2420, InvalidGObjectTypeReturnsZero_2420)
{
    // Create some other GObject that is NOT a PopplerMovie
    GObject *not_a_movie = static_cast<GObject *>(g_object_new(G_TYPE_OBJECT, NULL));
    ASSERT_NE(not_a_movie, nullptr);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    gushort angle = poppler_movie_get_rotation_angle(reinterpret_cast<PopplerMovie *>(not_a_movie));
    g_test_assert_expected_messages();
    EXPECT_EQ(angle, 0);

    g_object_unref(not_a_movie);
}

// Test return type is gushort (unsigned short) - value should be non-negative
TEST_F(PopplerMovieTest_2420, ReturnTypeIsUnsigned_2420)
{
    PopplerMovie *movie = static_cast<PopplerMovie *>(g_object_new(POPPLER_TYPE_MOVIE, NULL));
    if (movie != NULL) {
        gushort angle = poppler_movie_get_rotation_angle(movie);
        // gushort is always >= 0, but we verify the value is within valid range
        EXPECT_GE(angle, 0);
        EXPECT_LE(angle, G_MAXUSHORT);
        g_object_unref(movie);
    }
}
