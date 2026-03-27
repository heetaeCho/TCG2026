#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-movie.hh"

#include "./TestProjects/poppler/poppler/Movie.hh"



using namespace testing;

using namespace MovieActivationParameters;



class PopplerMovieTest : public ::testing::Test {

protected:

    void SetUp() override {

        movieDict = std::make_unique<Object>();

        activationDict = std::make_unique<Object>();

        movie = std::make_unique<Movie>(movieDict.get(), activationDict.get());

    }



    std::unique_ptr<Object> movieDict;

    std::unique_ptr<Object> activationDict;

    std::unique_ptr<Movie> movie;

};



TEST_F(PopplerMovieTest, NormalOperation_2412) {

    EXPECT_CALL(*movie, getFileName()).WillOnce(Return(std::make_unique<GooString>("testfile.mp4")));

    EXPECT_CALL(*movie, getShowPoster()).WillOnce(Return(true));

    Object posterObject("poster");

    EXPECT_CALL(*movie, getPoster()).WillOnce(Return(posterObject));

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModeRepeat;

    ma->showControls = true;

    ma->synchronousPlay = false;

    ma->volume = 50;

    ma->rate = 1.0f;

    ma->start.units_per_second = 1;

    ma->start.units = 5;

    ma->duration.units_per_second = 1;

    ma->duration.units = 30;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));

    EXPECT_CALL(*movie, getRotationAngle()).WillOnce(Return(90));

    int width = 640, height = 480;

    EXPECT_CALL(*movie, getAspect(_, _)).WillOnce(DoAll(SetArgReferee<0>(width), SetArgReferee<1>(height)));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    ASSERT_STREQ(popplerMovie->filename, "testfile.mp4");

    EXPECT_TRUE(popplerMovie->need_poster);

    EXPECT_EQ(popplerMovie->mode, POPPLER_MOVIE_PLAY_MODE_REPEAT);

    EXPECT_TRUE(popplerMovie->show_controls);

    EXPECT_FALSE(popplerMovie->synchronous_play);

    EXPECT_DOUBLE_EQ(popplerMovie->volume, 0.5);

    EXPECT_DOUBLE_EQ(popplerMovie->rate, 1.0f);

    EXPECT_EQ(popplerMovie->start, 5000000000L);

    EXPECT_EQ(popplerMovie->duration, 30000000000L);

    EXPECT_EQ(popplerMovie->rotation_angle, 90);

    EXPECT_EQ(popplerMovie->width, 640);

    EXPECT_EQ(popplerMovie->height, 480);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, NullMovie_2412) {

    ASSERT_DEATH(_poppler_movie_new(nullptr), ".*assertion.*failed.*");

}



TEST_F(PopplerMovieTest, PosterNotRefOrStream_2412) {

    EXPECT_CALL(*movie, getFileName()).WillOnce(Return(std::make_unique<GooString>("testfile.mp4")));

    EXPECT_CALL(*movie, getShowPoster()).WillOnce(Return(true));

    Object posterObject("poster");

    EXPECT_CALL(*movie, getPoster()).WillOnce(Return(posterObject));

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModeRepeat;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_TRUE(popplerMovie->need_poster);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, PosterRef_2412) {

    EXPECT_CALL(*movie, getFileName()).WillOnce(Return(std::make_unique<GooString>("testfile.mp4")));

    EXPECT_CALL(*movie, getShowPoster()).WillOnce(Return(true));

    Object posterObject;

    posterObject.setRef(1, 0);

    EXPECT_CALL(*movie, getPoster()).WillOnce(Return(posterObject));

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModeRepeat;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_FALSE(popplerMovie->need_poster);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, PosterStream_2412) {

    EXPECT_CALL(*movie, getFileName()).WillOnce(Return(std::make_unique<GooString>("testfile.mp4")));

    EXPECT_CALL(*movie, getShowPoster()).WillOnce(Return(true));

    Object posterObject;

    Stream* stream = nullptr; // Assuming a null Stream pointer

    posterObject.setStream(stream);

    EXPECT_CALL(*movie, getPoster()).WillOnce(Return(posterObject));

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModeRepeat;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_FALSE(popplerMovie->need_poster);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, RepeatModeOnce_2412) {

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModeOnce;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_EQ(popplerMovie->mode, POPPLER_MOVIE_PLAY_MODE_ONCE);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, RepeatModeOpen_2412) {

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModeOpen;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_EQ(popplerMovie->mode, POPPLER_MOVIE_PLAY_MODE_OPEN);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, RepeatModeRepeat_2412) {

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModeRepeat;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_EQ(popplerMovie->mode, POPPLER_MOVIE_PLAY_MODE_REPEAT);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, RepeatModePalindrome_2412) {

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->repeatMode = repeatModePalindrome;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_EQ(popplerMovie->mode, POPPLER_MOVIE_PLAY_MODE_PALINDROME);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, StartUnitsOverflow_2412) {

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->start.units_per_second = 1;

    ma->start.units = G_MAXUINT64 / 1000000000 + 1;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_EQ(popplerMovie->start, 0L);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}



TEST_F(PopplerMovieTest, DurationUnitsOverflow_2412) {

    MovieActivationParameters* ma = new MovieActivationParameters();

    ma->duration.units_per_second = 1;

    ma->duration.units = G_MAXUINT64 / 1000000000 + 1;

    EXPECT_CALL(*movie, getActivationParameters()).WillOnce(Return(ma));



    PopplerMovie* popplerMovie = _poppler_movie_new(movie.get());



    EXPECT_EQ(popplerMovie->duration, 0L);



    g_free(popplerMovie->filename);

    g_object_unref(popplerMovie);

}
