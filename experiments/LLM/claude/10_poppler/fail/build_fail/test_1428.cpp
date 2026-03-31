#include <gtest/gtest.h>
#include "Movie.h"
#include "Object.h"

class MovieTest_1428 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a Movie constructed from a minimal valid movie dictionary is okay or handles gracefully
TEST_F(MovieTest_1428, ConstructFromMovieDict_1428) {
    // Create a minimal movie dict object (empty dict)
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    // We can at least call isOk and check it doesn't crash
    // With an empty dict, movie likely won't be ok
    EXPECT_FALSE(movie.isOk());
}

// Test that a Movie constructed with both movieDict and aDict handles empty dicts
TEST_F(MovieTest_1428, ConstructFromMovieDictAndADict_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    Object aDict;
    aDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict, &aDict);
    // With empty dicts, isOk should be false since no file specified
    EXPECT_FALSE(movie.isOk());
}

// Test copy constructor
TEST_F(MovieTest_1428, CopyConstructor_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    EXPECT_EQ(movie.isOk(), movieCopy.isOk());
    EXPECT_EQ(movie.getRotationAngle(), movieCopy.getRotationAngle());
    EXPECT_EQ(movie.getShowPoster(), movieCopy.getShowPoster());
    EXPECT_EQ(movie.getUseFloatingWindow(), movieCopy.getUseFloatingWindow());
}

// Test getRotationAngle returns a value (default should be 0 for empty dict)
TEST_F(MovieTest_1428, GetRotationAngleDefault_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    unsigned short angle = movie.getRotationAngle();
    // Rotation angle should be one of 0, 90, 180, 270
    EXPECT_TRUE(angle == 0 || angle == 90 || angle == 180 || angle == 270);
}

// Test getFileName for a movie with no file specified
TEST_F(MovieTest_1428, GetFileNameEmpty_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    const GooString *fileName = movie.getFileName();
    // With empty dict, fileName might be nullptr
    // Just ensure it doesn't crash
    if (fileName != nullptr) {
        EXPECT_GE(fileName->getLength(), 0);
    }
}

// Test getAspect returns dimensions
TEST_F(MovieTest_1428, GetAspectDefault_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    int width = -1, height = -1;
    movie.getAspect(&width, &height);
    // Aspect values should be non-negative for a valid default
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test getShowPoster default
TEST_F(MovieTest_1428, GetShowPosterDefault_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    // Default showPoster should be false
    bool showPoster = movie.getShowPoster();
    EXPECT_FALSE(showPoster);
}

// Test getUseFloatingWindow default
TEST_F(MovieTest_1428, GetUseFloatingWindowDefault_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    bool useFloating = movie.getUseFloatingWindow();
    // Default should be false for empty dict
    EXPECT_FALSE(useFloating);
}

// Test getFloatingWindowSize
TEST_F(MovieTest_1428, GetFloatingWindowSizeDefault_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    int width = -1, height = -1;
    movie.getFloatingWindowSize(&width, &height);
    // Should set some default values
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test getActivationParameters is not null
TEST_F(MovieTest_1428, GetActivationParametersNotNull_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    const MovieActivationParameters *params = movie.getActivationParameters();
    EXPECT_NE(params, nullptr);
}

// Test getPoster returns an object
TEST_F(MovieTest_1428, GetPosterDefault_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Object poster = movie.getPoster();
    // For empty dict, poster should likely be null type
    EXPECT_TRUE(poster.isNull() || poster.isNone());
}

// Test copy method
TEST_F(MovieTest_1428, CopyMethod_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Movie *movieCopy = reinterpret_cast<Movie *>(movie.copy());
    // The copy() returns an int which seems unusual - may be a unique ID
    // Just test it doesn't crash
    (void)movieCopy;
}

// Test that copy constructor preserves aspect ratio
TEST_F(MovieTest_1428, CopyPreservesAspect_1428) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    int w1, h1, w2, h2;
    movie.getAspect(&w1, &h1);
    movieCopy.getAspect(&w2, &h2);
    
    EXPECT_EQ(w1, w2);
    EXPECT_EQ(h1, h2);
}
