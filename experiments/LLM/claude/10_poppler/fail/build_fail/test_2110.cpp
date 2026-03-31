#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal struct definitions needed for testing
// Based on the known/inferred dependencies

extern "C" {

typedef struct _PopplerMovie PopplerMovie;
typedef struct _PopplerAnnotMovie PopplerAnnotMovie;

// The function under test
PopplerMovie *poppler_annot_movie_get_movie(PopplerAnnotMovie *poppler_annot);

}

// We need to define the struct to be able to create test instances
// Based on the inferred dependency, _PopplerAnnotMovie contains a movie field
struct _PopplerMovie {
    int dummy; // placeholder
};

struct _PopplerAnnotMovie {
    // Based on the implementation: return poppler_annot->movie;
    // The struct must have a 'movie' member of type PopplerMovie*
    PopplerMovie *movie;
};

class PopplerAnnotMovieTest_2110 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get_movie returns the movie pointer stored in the annotation
TEST_F(PopplerAnnotMovieTest_2110, ReturnsMoviePointer_2110) {
    PopplerMovie movie_instance;
    movie_instance.dummy = 42;

    PopplerAnnotMovie annot;
    annot.movie = &movie_instance;

    PopplerMovie *result = poppler_annot_movie_get_movie(&annot);
    EXPECT_EQ(result, &movie_instance);
}

// Test that get_movie returns nullptr when movie is null
TEST_F(PopplerAnnotMovieTest_2110, ReturnsNullWhenMovieIsNull_2110) {
    PopplerAnnotMovie annot;
    annot.movie = nullptr;

    PopplerMovie *result = poppler_annot_movie_get_movie(&annot);
    EXPECT_EQ(result, nullptr);
}

// Test that the returned pointer is the exact same object (identity check)
TEST_F(PopplerAnnotMovieTest_2110, ReturnsSamePointerIdentity_2110) {
    PopplerMovie movie1;
    movie1.dummy = 1;
    PopplerMovie movie2;
    movie2.dummy = 2;

    PopplerAnnotMovie annot;
    annot.movie = &movie1;

    PopplerMovie *result = poppler_annot_movie_get_movie(&annot);
    EXPECT_EQ(result, &movie1);
    EXPECT_NE(result, &movie2);
}

// Test that changing the movie pointer in the annotation is reflected
TEST_F(PopplerAnnotMovieTest_2110, ReflectsUpdatedMoviePointer_2110) {
    PopplerMovie movie1;
    movie1.dummy = 10;
    PopplerMovie movie2;
    movie2.dummy = 20;

    PopplerAnnotMovie annot;
    annot.movie = &movie1;

    EXPECT_EQ(poppler_annot_movie_get_movie(&annot), &movie1);

    annot.movie = &movie2;
    EXPECT_EQ(poppler_annot_movie_get_movie(&annot), &movie2);
}

// Test with multiple annotations having different movies
TEST_F(PopplerAnnotMovieTest_2110, MultipleAnnotationsReturnDifferentMovies_2110) {
    PopplerMovie movieA;
    movieA.dummy = 100;
    PopplerMovie movieB;
    movieB.dummy = 200;

    PopplerAnnotMovie annotA;
    annotA.movie = &movieA;

    PopplerAnnotMovie annotB;
    annotB.movie = &movieB;

    EXPECT_EQ(poppler_annot_movie_get_movie(&annotA), &movieA);
    EXPECT_EQ(poppler_annot_movie_get_movie(&annotB), &movieB);
    EXPECT_NE(poppler_annot_movie_get_movie(&annotA), poppler_annot_movie_get_movie(&annotB));
}

// Test calling get_movie multiple times returns consistent result
TEST_F(PopplerAnnotMovieTest_2110, ConsistentReturnOnMultipleCalls_2110) {
    PopplerMovie movie;
    movie.dummy = 55;

    PopplerAnnotMovie annot;
    annot.movie = &movie;

    PopplerMovie *result1 = poppler_annot_movie_get_movie(&annot);
    PopplerMovie *result2 = poppler_annot_movie_get_movie(&annot);
    PopplerMovie *result3 = poppler_annot_movie_get_movie(&annot);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}
