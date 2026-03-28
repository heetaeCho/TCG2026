#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2419 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that poppler_movie_get_rate returns 0 when passed NULL
TEST_F(PopplerMovieTest_2419, GetRateReturnsZeroForNull_2419)
{
    gdouble rate = poppler_movie_get_rate(nullptr);
    EXPECT_DOUBLE_EQ(rate, 0.0);
}

// Test that poppler_movie_get_rate returns 0 for an invalid (non-PopplerMovie) GObject
TEST_F(PopplerMovieTest_2419, GetRateReturnsZeroForInvalidObject_2419)
{
    // Passing a non-PopplerMovie object should trigger g_return_val_if_fail and return 0
    GObject *invalid_obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    gdouble rate = poppler_movie_get_rate((PopplerMovie *)invalid_obj);
    EXPECT_DOUBLE_EQ(rate, 0.0);
    g_object_unref(invalid_obj);
}
