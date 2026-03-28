#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler-movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2414 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_movie_need_poster returns FALSE when called with NULL
TEST_F(PopplerMovieTest_2414, NeedPosterWithNullReturnsDefault_2414)
{
    // g_return_val_if_fail should return FALSE for NULL input
    // This will generate a g_critical warning, but should not crash
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    gboolean result = poppler_movie_need_poster(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, FALSE);
}

// Test that poppler_movie_need_poster returns the correct value for a valid movie
// We create a movie using the public API if available, or test with a real PDF movie annotation
TEST_F(PopplerMovieTest_2414, NeedPosterWithInvalidObjectReturnsDefault_2414)
{
    // Passing a non-PopplerMovie GObject should trigger the type check and return FALSE
    GObject *not_a_movie = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MOVIE*");
    gboolean result = poppler_movie_need_poster((PopplerMovie *)not_a_movie);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, FALSE);
    g_object_unref(not_a_movie);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
