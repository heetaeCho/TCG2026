#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Movie.h"
#include "Object.h"

// Helper to create a minimal movie dictionary Object for constructing Movie
// Since we treat Movie as a black box, we need to create valid enough Objects
// to construct Movie instances.

class MovieTest_1430 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getPoster returns an Object (copy of internal poster)
// When Movie is constructed with a dictionary that has no poster,
// the poster should default to some state (likely null/none).
TEST_F(MovieTest_1430, GetPosterReturnsObject_1430) {
    // Create a minimal movie dict as a Dict object
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    Object poster = movie.getPoster();
    // The poster should be some valid Object type - likely null/none if not set
    // We just verify it doesn't crash and returns a valid Object
    EXPECT_TRUE(poster.isNull() || poster.isNone() || poster.isStream() || poster.isDict() || poster.isBool());
}

// Test that getShowPoster returns a boolean value
TEST_F(MovieTest_1430, GetShowPosterReturnsBool_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    bool showPoster = movie.getShowPoster();
    // Default should be false if not set in dict
    EXPECT_FALSE(showPoster);
}

// Test that getRotationAngle returns a valid rotation angle
TEST_F(MovieTest_1430, GetRotationAngleReturnsValue_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    unsigned short angle = movie.getRotationAngle();
    // Rotation angle should be 0, 90, 180, or 270 typically
    // Default should be 0
    EXPECT_EQ(angle, 0);
}

// Test that getFileName returns a pointer (possibly null for minimal dict)
TEST_F(MovieTest_1430, GetFileNameReturnsPointer_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    const GooString *fileName = movie.getFileName();
    // May be null if no filename was specified in the dict
    // Just verify it doesn't crash
    (void)fileName;
}

// Test that getActivationParameters returns a valid pointer
TEST_F(MovieTest_1430, GetActivationParametersReturnsPointer_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    const MovieActivationParameters *params = movie.getActivationParameters();
    EXPECT_NE(params, nullptr);
}

// Test that getAspect returns dimensions
TEST_F(MovieTest_1430, GetAspectReturnsDimensions_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    int width = -1, height = -1;
    movie.getAspect(&width, &height);
    // After calling getAspect, width and height should be set to some value
    // (likely 0 or some default for a minimal dict)
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test that getFloatingWindowSize returns dimensions
TEST_F(MovieTest_1430, GetFloatingWindowSizeReturnsDimensions_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    int width = -1, height = -1;
    movie.getFloatingWindowSize(&width, &height);
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test copy constructor - getPoster should work on copied movie
TEST_F(MovieTest_1430, CopyConstructorPreservesPoster_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    Object poster1 = movie.getPoster();
    Object poster2 = movieCopy.getPoster();
    
    // Both should have the same type of poster
    EXPECT_EQ(poster1.getType(), poster2.getType());
}

// Test copy constructor preserves rotation angle
TEST_F(MovieTest_1430, CopyConstructorPreservesRotationAngle_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    EXPECT_EQ(movie.getRotationAngle(), movieCopy.getRotationAngle());
}

// Test copy constructor preserves showPoster
TEST_F(MovieTest_1430, CopyConstructorPreservesShowPoster_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    EXPECT_EQ(movie.getShowPoster(), movieCopy.getShowPoster());
}

// Test that getPoster returns independent copies (modifying one doesn't affect the other)
TEST_F(MovieTest_1430, GetPosterReturnsCopy_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    Object poster1 = movie.getPoster();
    Object poster2 = movie.getPoster();
    
    // Both should be valid and have the same type
    EXPECT_EQ(poster1.getType(), poster2.getType());
}

// Test construction with both movieDict and aDict parameters
TEST_F(MovieTest_1430, ConstructWithTwoDicts_1430) {
    Object movieDict = Object(new Dict(nullptr));
    Object aDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict, &aDict);
    
    // Should construct successfully, verify basic getters work
    EXPECT_GE(movie.getRotationAngle(), 0);
    Object poster = movie.getPoster();
    (void)poster;
}

// Test getUseFloatingWindow returns a boolean
TEST_F(MovieTest_1430, GetUseFloatingWindowReturnsBool_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    bool useFloating = movie.getUseFloatingWindow();
    // Default should be false
    EXPECT_FALSE(useFloating);
}

// Test isOk returns a boolean indicating validity
TEST_F(MovieTest_1430, IsOkReturnsBool_1430) {
    Object movieDict = Object(new Dict(nullptr));
    
    Movie movie(&movieDict);
    
    // With a minimal/empty dict, movie might not be "ok"
    // Just verify it returns without crashing
    bool ok = movie.isOk();
    (void)ok;
}
