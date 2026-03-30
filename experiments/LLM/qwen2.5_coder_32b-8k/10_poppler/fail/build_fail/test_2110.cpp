#include <gtest/gtest.h>

#include "poppler-annot.h"



class PopplerAnnotMovieTest_2110 : public ::testing::Test {

protected:

    PopplerAnnotMovie* poppler_annot_movie;



    void SetUp() override {

        // Assuming there's a way to create an instance of PopplerAnnotMovie

        poppler_annot_movie = new PopplerAnnotMovie();

        // Initialize movie for the annotation if needed

        poppler_annot_movie->movie = nullptr; // Default state

    }



    void TearDown() override {

        delete poppler_annot_movie;

    }

};



TEST_F(PopplerAnnotMovieTest_2110, GetMovie_ReturnsNullptr_WhenNoMovieSet_2110) {

    EXPECT_EQ(poppler_annot_movie_get_movie(poppler_annot_movie), nullptr);

}



TEST_F(PopplerAnnotMovieTest_2110, GetMovie_ReturnsCorrectPointer_WhenMovieIsSet_2110) {

    PopplerMovie* expected_movie = new PopplerMovie();

    poppler_annot_movie->movie = expected_movie;

    EXPECT_EQ(poppler_annot_movie_get_movie(poppler_annot_movie), expected_movie);

    delete expected_movie; // Clean up

}
