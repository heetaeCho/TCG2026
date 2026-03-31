#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <climits>
#include <cstring>

// Include necessary poppler headers
#include "poppler-movie.h"
#include "Object.h"
#include "Movie.h"

// We need access to the internal creation function
extern "C" {
PopplerMovie *_poppler_movie_new(const Movie *poppler_movie);
}

class PopplerMovieTest_2412 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a minimal Movie object from dictionaries
// Since Movie requires Object dictionaries, we create them appropriately

TEST_F(PopplerMovieTest_2412, NullMovieShouldAssert_2412)
{
    // Passing nullptr should trigger g_assert
    // This is expected to abort, so we test with EXPECT_DEATH if available
    EXPECT_DEATH(_poppler_movie_new(nullptr), "");
}

TEST_F(PopplerMovieTest_2412, BasicMovieCreation_2412)
{
    // Create a basic movie dict with a file specification
    Dict *movieDict = new Dict(nullptr);
    // Movie requires an "F" entry for filename
    movieDict->set("F", Object(new GooString("test_movie.mp4")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        // If we can't create a valid Movie this way, skip
        GTEST_SKIP() << "Cannot create valid Movie object for testing";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    // Test filename
    const gchar *filename = poppler_movie_get_filename(pMovie);
    EXPECT_STREQ(filename, "test_movie.mp4");
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, DefaultPlayModeIsOnce_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("video.avi")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    // Default repeat mode should be "once"
    PopplerMoviePlayMode mode = poppler_movie_get_play_mode(pMovie);
    EXPECT_EQ(mode, POPPLER_MOVIE_PLAY_MODE_ONCE);
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, DefaultShowControlsFalse_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("video.avi")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    gboolean show_controls = poppler_movie_show_controls(pMovie);
    // Default should be FALSE
    EXPECT_FALSE(show_controls);
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, DefaultStartAndDurationAreZero_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("clip.mp4")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    // With default MovieTime (units_per_second likely 0), start and duration should be 0
    guint64 start = poppler_movie_get_start(pMovie);
    guint64 duration = poppler_movie_get_duration(pMovie);
    
    EXPECT_EQ(start, 0UL);
    EXPECT_EQ(duration, 0UL);
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, DefaultRotationAngle_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("movie.mp4")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    gushort angle = poppler_movie_get_rotation_angle(pMovie);
    EXPECT_EQ(angle, movie.getRotationAngle());
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, MovieNeedPosterDefault_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("test.avi")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    gboolean need_poster = poppler_movie_need_poster(pMovie);
    // Default showPoster is likely false, so need_poster should be false
    EXPECT_FALSE(need_poster);
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, MovieWithActivationDict_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("activated.mp4")));
    
    // Create activation dictionary
    Dict *aDict = new Dict(nullptr);
    aDict->set("ShowControls", Object(true));
    aDict->set("Mode", Object(new GooString("Repeat")));
    aDict->set("Synchronous", Object(true));
    aDict->set("Volume", Object(0.5));
    aDict->set("Rate", Object(2.0));
    
    Object movieObj(movieDict);
    Object aObj(aDict);
    Movie movie(&movieObj, &aObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object with activation params";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    const gchar *filename = poppler_movie_get_filename(pMovie);
    EXPECT_STREQ(filename, "activated.mp4");
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, MovieAspectRatio_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("aspect_test.mp4")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    gint width = 0, height = 0;
    poppler_movie_get_aspect(pMovie, &width, &height);
    
    // Verify aspect matches what the Movie object reports
    int mw = 0, mh = 0;
    movie.getAspect(&mw, &mh);
    EXPECT_EQ(width, mw);
    EXPECT_EQ(height, mh);
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, MovieVolumeAndRate_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("vol_rate.mp4")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    // Volume should be MA.volume / 100.0
    gdouble volume = poppler_movie_get_volume(pMovie);
    double expected_volume = movie.getActivationParameters()->volume / 100.0;
    EXPECT_DOUBLE_EQ(volume, expected_volume);
    
    // Rate should match
    gdouble rate = poppler_movie_get_rate(pMovie);
    EXPECT_DOUBLE_EQ(rate, movie.getActivationParameters()->rate);
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, MovieIsSynchronous_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("sync.mp4")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    gboolean sync = poppler_movie_is_synchronous(pMovie);
    EXPECT_EQ(sync, movie.getActivationParameters()->synchronousPlay ? TRUE : FALSE);
    
    g_object_unref(pMovie);
}

TEST_F(PopplerMovieTest_2412, ObjectIsGObject_2412)
{
    Dict *movieDict = new Dict(nullptr);
    movieDict->set("F", Object(new GooString("gobject_test.mp4")));
    
    Object movieObj(movieDict);
    Movie movie(&movieObj);
    
    if (!movie.isOk()) {
        GTEST_SKIP() << "Cannot create valid Movie object";
    }
    
    PopplerMovie *pMovie = _poppler_movie_new(&movie);
    ASSERT_NE(pMovie, nullptr);
    
    // Verify it's a valid GObject
    EXPECT_TRUE(G_IS_OBJECT(pMovie));
    EXPECT_TRUE(POPPLER_IS_MOVIE(pMovie));
    
    g_object_unref(pMovie);
}
