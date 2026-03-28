#include <gtest/gtest.h>

#include "poppler/Annot.h"

#include <memory>



class AnnotMovieTest_810 : public ::testing::Test {

protected:

    std::unique_ptr<Movie> movie;

    AnnotMovie *annotMovie;



    void SetUp() override {

        movie = std::make_unique<Movie>();

        annotMovie = new AnnotMovie(nullptr, nullptr, movie.get());

    }



    void TearDown() override {

        delete annotMovie;

    }

};



TEST_F(AnnotMovieTest_810, GetMovieReturnsCorrectPointer_810) {

    EXPECT_EQ(annotMovie->getMovie(), movie.get());

}



// Assuming Movie class has a default constructor and can be instantiated.

// If there are specific conditions or states for the Movie object,

// additional tests might be needed to cover those scenarios.



// Since there is no observable behavior other than getMovie(),

// we limit our tests to this function. Additional context about

// other member functions would allow for more comprehensive testing.
