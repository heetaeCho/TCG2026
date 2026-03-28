#include <gtest/gtest.h>
#include "Movie.h"
#include "Object.h"

class MovieTest_1429 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test getAspect returns width and height values
TEST_F(MovieTest_1429, GetAspectReturnsValues_1429) {
    // Create a minimal movie dict object
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    int width = -1, height = -1;
    movie.getAspect(&width, &height);
    
    // After construction (even with empty dict), getAspect should set some values
    // Default aspect values should be non-negative or zero
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test isOk reflects whether the movie was properly constructed
TEST_F(MovieTest_1429, IsOkWithEmptyDict_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    // With an empty dictionary (no valid movie file reference), isOk may return false
    // We just verify the method is callable and returns a boolean
    bool ok = movie.isOk();
    (void)ok; // Just ensure it doesn't crash
}

// Test getRotationAngle returns a valid rotation
TEST_F(MovieTest_1429, GetRotationAngle_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    unsigned short angle = movie.getRotationAngle();
    // Rotation angle should be 0, 90, 180, or 270
    EXPECT_TRUE(angle == 0 || angle == 90 || angle == 180 || angle == 270);
}

// Test getShowPoster returns a boolean value
TEST_F(MovieTest_1429, GetShowPoster_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    bool showPoster = movie.getShowPoster();
    (void)showPoster; // Ensure callable without crash
}

// Test getUseFloatingWindow returns a boolean value
TEST_F(MovieTest_1429, GetUseFloatingWindow_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    bool useFloating = movie.getUseFloatingWindow();
    (void)useFloating;
}

// Test getActivationParameters returns non-null pointer
TEST_F(MovieTest_1429, GetActivationParameters_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    const MovieActivationParameters *params = movie.getActivationParameters();
    EXPECT_NE(params, nullptr);
}

// Test getFloatingWindowSize returns values
TEST_F(MovieTest_1429, GetFloatingWindowSize_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    int width = -1, height = -1;
    movie.getFloatingWindowSize(&width, &height);
    // Should set some values
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test copy constructor
TEST_F(MovieTest_1429, CopyConstructor_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    int w1, h1, w2, h2;
    movie.getAspect(&w1, &h1);
    movieCopy.getAspect(&w2, &h2);
    
    EXPECT_EQ(w1, w2);
    EXPECT_EQ(h1, h2);
    EXPECT_EQ(movie.getRotationAngle(), movieCopy.getRotationAngle());
    EXPECT_EQ(movie.getShowPoster(), movieCopy.getShowPoster());
    EXPECT_EQ(movie.getUseFloatingWindow(), movieCopy.getUseFloatingWindow());
}

// Test getPoster returns an Object
TEST_F(MovieTest_1429, GetPoster_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    Object poster = movie.getPoster();
    // Just ensure it doesn't crash and returns something
    (void)poster;
}

// Test getFileName
TEST_F(MovieTest_1429, GetFileName_1429) {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    const GooString *fileName = movie.getFileName();
    // With empty dict, fileName might be null or empty
    (void)fileName;
}
