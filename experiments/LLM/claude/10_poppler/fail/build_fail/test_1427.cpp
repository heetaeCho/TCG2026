#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Movie.h"
#include "Object.h"

// Helper to create a minimal movie dictionary Object for testing
// Since we're treating Movie as a black box, we need to construct valid Objects
// that the Movie constructor can parse.

class MovieTest_1427 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing a Movie with a minimal valid movie dict doesn't crash
// and isOk returns a meaningful value
TEST_F(MovieTest_1427, ConstructWithNullDict_ReturnsNotOk_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    // A null/empty object should likely result in an invalid movie
    EXPECT_FALSE(movie.isOk());
}

// Test that getActivationParameters returns a non-null pointer
TEST_F(MovieTest_1427, GetActivationParametersReturnsNonNull_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    const MovieActivationParameters *params = movie.getActivationParameters();
    EXPECT_NE(params, nullptr);
}

// Test that getFileName returns something (possibly null for invalid movie)
TEST_F(MovieTest_1427, GetFileNameForInvalidMovie_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    // For an invalid movie, getFileName may return nullptr or an empty string
    const GooString *fileName = movie.getFileName();
    // We just check it doesn't crash; fileName could be nullptr for invalid movie
    // No assertion on value since behavior depends on implementation
}

// Test getRotationAngle for a default/invalid movie
TEST_F(MovieTest_1427, GetRotationAngleDefault_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    unsigned short angle = movie.getRotationAngle();
    // Rotation angle should be one of 0, 90, 180, 270 typically
    // For a default case, 0 is expected
    EXPECT_TRUE(angle == 0 || angle == 90 || angle == 180 || angle == 270);
}

// Test getAspect for a default/invalid movie
TEST_F(MovieTest_1427, GetAspectDefault_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    int width = -1, height = -1;
    movie.getAspect(&width, &height);
    // For an invalid movie, aspect should be some default (likely 0 or -1)
    // Just ensure it doesn't crash and sets some values
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test getShowPoster for a default/invalid movie
TEST_F(MovieTest_1427, GetShowPosterDefault_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    bool showPoster = movie.getShowPoster();
    // Default should be false for invalid movie
    EXPECT_FALSE(showPoster);
}

// Test getPoster for a default/invalid movie doesn't crash
TEST_F(MovieTest_1427, GetPosterDefault_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    Object poster = movie.getPoster();
    // Just ensure it doesn't crash
}

// Test getUseFloatingWindow for a default/invalid movie
TEST_F(MovieTest_1427, GetUseFloatingWindowDefault_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    bool useFloating = movie.getUseFloatingWindow();
    EXPECT_FALSE(useFloating);
}

// Test getFloatingWindowSize for a default/invalid movie
TEST_F(MovieTest_1427, GetFloatingWindowSizeDefault_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    int width = -1, height = -1;
    movie.getFloatingWindowSize(&width, &height);
    // Should set some default values without crashing
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test copy constructor
TEST_F(MovieTest_1427, CopyConstructor_1427)
{
    Object nullObj;
    Movie movie1(&nullObj);
    Movie movie2(movie1);

    // Both should have the same properties
    EXPECT_EQ(movie1.isOk(), movie2.isOk());
    EXPECT_EQ(movie1.getRotationAngle(), movie2.getRotationAngle());
    EXPECT_EQ(movie1.getShowPoster(), movie2.getShowPoster());
    EXPECT_EQ(movie1.getUseFloatingWindow(), movie2.getUseFloatingWindow());

    int w1, h1, w2, h2;
    movie1.getAspect(&w1, &h1);
    movie2.getAspect(&w2, &h2);
    EXPECT_EQ(w1, w2);
    EXPECT_EQ(h1, h2);
}

// Test that constructing with both movieDict and aDict (two-arg constructor)
TEST_F(MovieTest_1427, ConstructWithTwoDicts_1427)
{
    Object nullObj1;
    Object nullObj2;
    Movie movie(&nullObj1, &nullObj2);
    // Should not crash; check activation parameters exist
    const MovieActivationParameters *params = movie.getActivationParameters();
    EXPECT_NE(params, nullptr);
}

// Test with a proper movie dictionary containing an F (file) entry
TEST_F(MovieTest_1427, ConstructWithFileSpecDict_1427)
{
    // Create a dictionary object with an "F" key for the file specification
    Object movieDict(new Dict(nullptr));
    
    // Without a valid XRef, this may not work perfectly, but we test it doesn't crash
    Movie movie(&movieDict);
    // The movie may or may not be valid depending on internal parsing
    const MovieActivationParameters *params = movie.getActivationParameters();
    EXPECT_NE(params, nullptr);
}

// Test that activation parameters are consistent across multiple calls
TEST_F(MovieTest_1427, ActivationParametersConsistent_1427)
{
    Object nullObj;
    Movie movie(&nullObj);
    const MovieActivationParameters *params1 = movie.getActivationParameters();
    const MovieActivationParameters *params2 = movie.getActivationParameters();
    EXPECT_EQ(params1, params2);
}
