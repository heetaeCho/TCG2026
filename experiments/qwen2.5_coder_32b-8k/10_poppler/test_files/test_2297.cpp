#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.cc"

#include "Link.h"

#include "Annot.h"

#include "poppler-private.h"



using namespace testing;



class PopplerActionTest_2297 : public ::testing::Test {

protected:

    PopplerDocument* document;

    PopplerAction action;

    LinkMovie link_movie_play;

    LinkMovie link_movie_pause;

    LinkMovie link_movie_resume;

    LinkMovie link_movie_stop;

    AnnotMovie* annot_movie;



    void SetUp() override {

        document = new PopplerDocument();

        memset(&action, 0, sizeof(PopplerAction));

        

        // Mocking the behavior of getOperation for different cases

        ON_CALL(link_movie_play, getOperation()).WillByDefault(Return(LinkMovie::operationTypePlay));

        ON_CALL(link_movie_pause, getOperation()).WillByDefault(Return(LinkMovie::operationTypePause));

        ON_CALL(link_movie_resume, getOperation()).WillByDefault(Return(LinkMovie::operationTypeResume));

        ON_CALL(link_movie_stop, getOperation()).WillByDefault(Return(LinkMovie::operationTypeStop));



        // Mocking find_annot_movie_for_action to return a valid AnnotMovie pointer

        annot_movie = new AnnotMovie(nullptr, nullptr, nullptr);

        EXPECT_CALL(*(document), find_annot_movie_for_action(_, _)).WillOnce(Return(annot_movie));

    }



    void TearDown() override {

        delete document;

        delete annot_movie;

    }

};



TEST_F(PopplerActionTest_2297, MoviePlayOperation_2297) {

    build_movie(document, &action, &link_movie_play);

    EXPECT_EQ(action.movie.operation, POPPLER_ACTION_MOVIE_PLAY);

}



TEST_F(PopplerActionTest_2297, MoviePauseOperation_2297) {

    build_movie(document, &action, &link_movie_pause);

    EXPECT_EQ(action.movie.operation, POPPLER_ACTION_MOVIE_PAUSE);

}



TEST_F(PopplerActionTest_2297, MovieResumeOperation_2297) {

    build_movie(document, &action, &link_movie_resume);

    EXPECT_EQ(action.movie.operation, POPPLER_ACTION_MOVIE_RESUME);

}



TEST_F(PopplerActionTest_2297, MovieStopOperation_2297) {

    build_movie(document, &action, &link_movie_stop);

    EXPECT_EQ(action.movie.operation, POPPLER_ACTION_MOVIE_STOP);

}



TEST_F(PopplerActionTest_2297, DefaultOperationTypePlay_2297) {

    ON_CALL(link_movie_play, getOperation()).WillByDefault(Return(static_cast<LinkMovie::OperationType>(-1)));

    build_movie(document, &action, &link_movie_play);

    EXPECT_EQ(action.movie.operation, POPPLER_ACTION_MOVIE_PLAY);

}



TEST_F(PopplerActionTest_2297, NoAnnotMovieFound_2297) {

    EXPECT_CALL(*(document), find_annot_movie_for_action(_, _)).WillOnce(Return(nullptr));

    build_movie(document, &action, &link_movie_play);

    EXPECT_EQ(action.movie.movie, nullptr);

}
