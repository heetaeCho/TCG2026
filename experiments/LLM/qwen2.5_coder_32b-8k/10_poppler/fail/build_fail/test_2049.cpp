#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "Annot.h"



using namespace testing;



// Mocking external collaborators if necessary

class MockMovie {

public:

    MOCK_METHOD(Movie*, getMovie, (), (const));

};



TEST_F(PopplerAnnotTest_2049, MovieAnnotationCreation_2049) {

    // Arrange

    auto mock_movie = std::make_unique<StrictMock<MockMovie>>();

    AnnotMovie* annot_movie = new AnnotMovie(nullptr, nullptr, mock_movie.get());

    std::shared_ptr<Annot> shared_annot(annot_movie);



    // Act

    PopplerAnnot* poppler_annot = _poppler_annot_movie_new(shared_annot);



    // Assert

    EXPECT_NE(poppler_annot, nullptr);

    EXPECT_EQ(poppler_annot->type, POPPLER_TYPE_ANNOT_MOVIE);

    delete poppler_annot;

}



TEST_F(PopplerAnnotTest_2049, MovieAnnotationMovieRetrieval_2049) {

    // Arrange

    auto mock_movie = std::make_unique<StrictMock<MockMovie>>();

    AnnotMovie* annot_movie = new AnnotMovie(nullptr, nullptr, mock_movie.get());

    std::shared_ptr<Annot> shared_annot(annot_movie);



    EXPECT_CALL(*mock_movie, getMovie()).WillOnce(Return(mock_movie.get()));



    // Act

    PopplerAnnot* poppler_annot = _poppler_annot_movie_new(shared_annot);

    Movie* movie = POPPLER_ANNOT_MOVIE(poppler_annot)->movie;



    // Assert

    EXPECT_EQ(movie, mock_movie.get());

    delete poppler_annot;

}
