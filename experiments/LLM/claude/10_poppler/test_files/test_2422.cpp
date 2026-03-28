#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler movie header
extern "C" {
#include "poppler-movie.h"
}

// We need access to the PopplerMovie type and its creation functions
// Since we're treating this as a black box, we use the public API

class PopplerMovieTest_2422 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup if needed
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

// Test that passing NULL returns 0 (the g_return_val_if_fail guard)
TEST_F(PopplerMovieTest_2422, GetDurationWithNullReturnsZero_2422) {
    guint64 result = poppler_movie_get_duration(nullptr);
    EXPECT_EQ(result, 0L);
}

// Test that passing an invalid (non-PopplerMovie) GObject returns 0
TEST_F(PopplerMovieTest_2422, GetDurationWithInvalidObjectReturnsZero_2422) {
    // Create a plain GObject which is not a PopplerMovie
    GObject *not_a_movie = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    ASSERT_NE(not_a_movie, nullptr);

    // This should fail the POPPLER_IS_MOVIE check and return 0
    guint64 result = poppler_movie_get_duration((PopplerMovie *)not_a_movie);
    EXPECT_EQ(result, 0L);

    g_object_unref(not_a_movie);
}

// If we can create a PopplerMovie from a Movie object, test normal operation
// Since PopplerMovie is typically created internally from PDF parsing,
// and we may not have a public constructor, we test what we can through the API.

// Test that the function is callable and doesn't crash with proper type checking
TEST_F(PopplerMovieTest_2422, GetDurationTypeCheckGuard_2422) {
    // Verify the g_return_val_if_fail guard works for NULL
    // Testing the boundary: the function should safely handle NULL input
    guint64 duration = poppler_movie_get_duration(NULL);
    EXPECT_EQ(duration, static_cast<guint64>(0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
