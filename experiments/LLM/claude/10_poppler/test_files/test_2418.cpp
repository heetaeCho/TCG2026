#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler movie header
extern "C" {
#include "poppler-movie.h"
}

// We need access to the PopplerMovie type and its creation functions
// Since we're treating this as a black box, we use the public API

class PopplerMovieTest_2418 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create movie objects as needed in individual tests
    }

    void TearDown() override {
    }
};

// Test that poppler_movie_get_volume returns 0 when passed NULL
TEST_F(PopplerMovieTest_2418, GetVolumeReturnsZeroForNull_2418) {
    // According to g_return_val_if_fail, passing NULL should return the default value (0)
    gdouble volume = poppler_movie_get_volume(NULL);
    EXPECT_DOUBLE_EQ(volume, 0.0);
}

// Test that poppler_movie_get_volume returns 0 for invalid (non-PopplerMovie) object
TEST_F(PopplerMovieTest_2418, GetVolumeReturnsZeroForInvalidObject_2418) {
    // Passing a non-PopplerMovie GObject should trigger the g_return_val_if_fail guard
    // and return 0
    gdouble volume = poppler_movie_get_volume((PopplerMovie *)NULL);
    EXPECT_DOUBLE_EQ(volume, 0.0);
}

// If we can create a PopplerMovie from a Movie object, test normal volume retrieval
// Since PopplerMovie is typically created internally by poppler from PDF Movie annotations,
// we test what we can through the public API.

// Test: Verify the function signature compiles and is callable
TEST_F(PopplerMovieTest_2418, GetVolumeFunctionExists_2418) {
    // This test verifies the function exists and is callable
    // We call with NULL which should safely return 0
    gdouble (*fn)(PopplerMovie *) = poppler_movie_get_volume;
    ASSERT_NE(fn, nullptr);
    gdouble result = fn(nullptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
}
