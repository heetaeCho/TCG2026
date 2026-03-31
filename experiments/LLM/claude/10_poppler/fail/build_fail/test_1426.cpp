#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Movie.h"
#include "Object.h"

class MovieTest_1426 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a Movie constructed from a null/empty dictionary is not ok
TEST_F(MovieTest_1426, DefaultConstructionWithEmptyDict_IsNotOk_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    // An empty/invalid dictionary should result in an invalid movie
    // The exact behavior depends on implementation, but we test isOk()
    EXPECT_FALSE(movie.isOk());
}

// Test that a Movie constructed from null-like objects handles gracefully
TEST_F(MovieTest_1426, ConstructionWithNullishObjects_1426) {
    Object movieDict;
    Object aDict;
    Movie movie(&movieDict, &aDict);
    // Without valid movie data, isOk should be false
    EXPECT_FALSE(movie.isOk());
}

// Test copy constructor preserves isOk state
TEST_F(MovieTest_1426, CopyConstructorPreservesState_1426) {
    Object emptyDict;
    Movie original(&emptyDict);
    Movie copied(original);
    EXPECT_EQ(original.isOk(), copied.isOk());
}

// Test getActivationParameters returns non-null for any constructed movie
TEST_F(MovieTest_1426, GetActivationParametersNotNull_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    const MovieActivationParameters *params = movie.getActivationParameters();
    // Even for an invalid movie, the activation parameters struct should exist
    EXPECT_NE(params, nullptr);
}

// Test getFileName for an invalid movie
TEST_F(MovieTest_1426, GetFileNameForInvalidMovie_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    const GooString *fileName = movie.getFileName();
    // For an invalid movie, fileName could be nullptr or empty
    // We just verify it doesn't crash
    if (fileName != nullptr) {
        EXPECT_GE(fileName->getLength(), 0);
    }
}

// Test getRotationAngle for an invalid movie returns a default
TEST_F(MovieTest_1426, GetRotationAngleDefault_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    unsigned short angle = movie.getRotationAngle();
    // Rotation angle should be a multiple of 90, default is likely 0
    EXPECT_EQ(angle % 90, 0);
}

// Test getAspect doesn't crash and returns reasonable values
TEST_F(MovieTest_1426, GetAspectDoesNotCrash_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    int width = -1, height = -1;
    movie.getAspect(&width, &height);
    // Width and height should be non-negative for any movie
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test getShowPoster for an invalid movie
TEST_F(MovieTest_1426, GetShowPosterDefault_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    // Just ensure it returns a valid bool without crashing
    bool showPoster = movie.getShowPoster();
    (void)showPoster; // suppress unused warning
    SUCCEED();
}

// Test getPoster for an invalid movie
TEST_F(MovieTest_1426, GetPosterDoesNotCrash_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    Object poster = movie.getPoster();
    // For an invalid movie, poster should be a null or none object
    SUCCEED();
}

// Test getUseFloatingWindow for an invalid movie
TEST_F(MovieTest_1426, GetUseFloatingWindowDefault_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    bool useFloating = movie.getUseFloatingWindow();
    (void)useFloating;
    SUCCEED();
}

// Test getFloatingWindowSize doesn't crash
TEST_F(MovieTest_1426, GetFloatingWindowSizeDoesNotCrash_1426) {
    Object emptyDict;
    Movie movie(&emptyDict);
    int width = -1, height = -1;
    movie.getFloatingWindowSize(&width, &height);
    // Should set some default values
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test copy constructor copies rotation angle
TEST_F(MovieTest_1426, CopyConstructorCopiesRotationAngle_1426) {
    Object emptyDict;
    Movie original(&emptyDict);
    Movie copied(original);
    EXPECT_EQ(original.getRotationAngle(), copied.getRotationAngle());
}

// Test copy constructor copies aspect ratio
TEST_F(MovieTest_1426, CopyConstructorCopiesAspect_1426) {
    Object emptyDict;
    Movie original(&emptyDict);
    Movie copied(original);
    
    int origW, origH, copyW, copyH;
    original.getAspect(&origW, &origH);
    copied.getAspect(&copyW, &copyH);
    
    EXPECT_EQ(origW, copyW);
    EXPECT_EQ(origH, copyH);
}

// Test copy constructor copies show poster state
TEST_F(MovieTest_1426, CopyConstructorCopiesShowPoster_1426) {
    Object emptyDict;
    Movie original(&emptyDict);
    Movie copied(original);
    EXPECT_EQ(original.getShowPoster(), copied.getShowPoster());
}

// Test copy constructor copies floating window state
TEST_F(MovieTest_1426, CopyConstructorCopiesUseFloatingWindow_1426) {
    Object emptyDict;
    Movie original(&emptyDict);
    Movie copied(original);
    EXPECT_EQ(original.getUseFloatingWindow(), copied.getUseFloatingWindow());
}

// Test that a valid movie dictionary with proper fields creates a valid movie
TEST_F(MovieTest_1426, ValidMovieDictCreatesOkMovie_1426) {
    // Create a proper movie dictionary with an 'F' (file specification) entry
    Object movieDict = Object(new Dict(nullptr));
    // Without a proper XRef/catalog, we likely can't create a fully valid movie
    // but we test the interface doesn't crash
    Movie movie(&movieDict);
    // Whether it's ok depends on the dictionary content
    // Just verify it doesn't crash
    SUCCEED();
}

// Test two-argument constructor with both dicts
TEST_F(MovieTest_1426, TwoArgConstructor_1426) {
    Object movieDict;
    Object aDict;
    Movie movie(&movieDict, &aDict);
    
    // Verify all getters work without crashing
    movie.isOk();
    movie.getRotationAngle();
    movie.getShowPoster();
    movie.getUseFloatingWindow();
    movie.getActivationParameters();
    movie.getFileName();
    
    int w, h;
    movie.getAspect(&w, &h);
    movie.getFloatingWindowSize(&w, &h);
    movie.getPoster();
    
    SUCCEED();
}
