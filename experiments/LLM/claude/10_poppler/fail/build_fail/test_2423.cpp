#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler-movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2423 : public ::testing::Test {
protected:
    PopplerMovie *movie = nullptr;

    void SetUp() override {
        // We need to create a PopplerMovie object for testing.
        // Since PopplerMovie is a GObject, we try to create one via g_object_new
        movie = static_cast<PopplerMovie *>(g_object_new(POPPLER_TYPE_MOVIE, nullptr));
    }

    void TearDown() override {
        if (movie) {
            g_object_unref(movie);
            movie = nullptr;
        }
    }
};

TEST_F(PopplerMovieTest_2423, GetAspectReturnsValidDimensions_2423)
{
    gint width = -1, height = -1;
    poppler_movie_get_aspect(movie, &width, &height);
    // After calling get_aspect, width and height should be set to some value
    // (default initialized values of the movie object)
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

TEST_F(PopplerMovieTest_2423, GetAspectWidthAndHeightAreIndependent_2423)
{
    gint width1 = -1, height1 = -1;
    gint width2 = -1, height2 = -1;

    poppler_movie_get_aspect(movie, &width1, &height1);
    poppler_movie_get_aspect(movie, &width2, &height2);

    // Calling twice should yield the same result
    EXPECT_EQ(width1, width2);
    EXPECT_EQ(height1, height2);
}

TEST_F(PopplerMovieTest_2423, MovieIsValidGObject_2423)
{
    ASSERT_TRUE(POPPLER_IS_MOVIE(movie));
}

TEST_F(PopplerMovieTest_2423, GetFilenameOnNewMovie_2423)
{
    // A newly created movie may or may not have a filename
    const gchar *filename = poppler_movie_get_filename(movie);
    // Just verify it doesn't crash; filename could be NULL for a default-constructed movie
    // No assertion on the value since we don't know the implementation details
    (void)filename;
}

TEST_F(PopplerMovieTest_2423, NeedPosterOnNewMovie_2423)
{
    gboolean needs_poster = poppler_movie_need_poster(movie);
    // Just verify it returns a valid boolean and doesn't crash
    EXPECT_TRUE(needs_poster == TRUE || needs_poster == FALSE);
}

TEST_F(PopplerMovieTest_2423, ShowControlsOnNewMovie_2423)
{
    gboolean show_controls = poppler_movie_show_controls(movie);
    EXPECT_TRUE(show_controls == TRUE || show_controls == FALSE);
}

TEST_F(PopplerMovieTest_2423, GetPlayModeOnNewMovie_2423)
{
    PopplerMoviePlayMode mode = poppler_movie_get_play_mode(movie);
    // Verify it returns a valid enum value
    EXPECT_GE(static_cast<int>(mode), 0);
}

TEST_F(PopplerMovieTest_2423, IsSynchronousOnNewMovie_2423)
{
    gboolean synchronous = poppler_movie_is_synchronous(movie);
    EXPECT_TRUE(synchronous == TRUE || synchronous == FALSE);
}

TEST_F(PopplerMovieTest_2423, GetVolumeOnNewMovie_2423)
{
    gdouble volume = poppler_movie_get_volume(movie);
    // Volume should be some reasonable value
    (void)volume; // Just ensure no crash
}

TEST_F(PopplerMovieTest_2423, GetRateOnNewMovie_2423)
{
    gdouble rate = poppler_movie_get_rate(movie);
    // Rate should be some value (typically 1.0 for normal speed)
    (void)rate; // Just ensure no crash
}

TEST_F(PopplerMovieTest_2423, GetRotationAngleOnNewMovie_2423)
{
    gushort angle = poppler_movie_get_rotation_angle(movie);
    // Rotation angle should be 0, 90, 180, or 270
    EXPECT_TRUE(angle == 0 || angle == 90 || angle == 180 || angle == 270);
}

TEST_F(PopplerMovieTest_2423, GetStartOnNewMovie_2423)
{
    guint64 start = poppler_movie_get_start(movie);
    (void)start; // Just ensure no crash
}

TEST_F(PopplerMovieTest_2423, GetDurationOnNewMovie_2423)
{
    guint64 duration = poppler_movie_get_duration(movie);
    (void)duration; // Just ensure no crash
}

TEST_F(PopplerMovieTest_2423, GetAspectConsistentResults_2423)
{
    gint w, h;
    poppler_movie_get_aspect(movie, &w, &h);

    gint w2, h2;
    poppler_movie_get_aspect(movie, &w2, &h2);

    EXPECT_EQ(w, w2);
    EXPECT_EQ(h, h2);
}
