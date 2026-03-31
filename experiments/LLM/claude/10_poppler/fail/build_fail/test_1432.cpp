#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Movie.h"
#include "Object.h"

class MovieTest_1432 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a minimal movie dictionary Object
static Object createMinimalMovieDict() {
    Object movieDict;
    movieDict = Object(new Dict(nullptr));
    return movieDict;
}

// Test that a Movie constructed from a movieDict alone can be queried
TEST_F(MovieTest_1432, ConstructFromMovieDictOnly_1432) {
    Object movieDict;
    movieDict.initNull();
    // Construction with null/empty dict - movie may not be "ok" but should not crash
    Movie movie(&movieDict);
    // We can at least call isOk and get a result
    bool ok = movie.isOk();
    // Just verify no crash; ok status depends on dict content
    (void)ok;
}

// Test that a Movie constructed with both movieDict and aDict doesn't crash
TEST_F(MovieTest_1432, ConstructFromMovieDictAndADict_1432) {
    Object movieDict;
    movieDict.initNull();
    Object aDict;
    aDict.initNull();
    Movie movie(&movieDict, &aDict);
    bool ok = movie.isOk();
    (void)ok;
}

// Test getUseFloatingWindow returns a bool value
TEST_F(MovieTest_1432, GetUseFloatingWindow_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    bool floatingWindow = movie.getUseFloatingWindow();
    // Default should be false for MovieActivationParameters default construction
    EXPECT_FALSE(floatingWindow);
}

// Test getRotationAngle returns a value
TEST_F(MovieTest_1432, GetRotationAngle_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    unsigned short angle = movie.getRotationAngle();
    // Default rotation angle should be 0
    EXPECT_EQ(angle, 0);
}

// Test getShowPoster returns a bool
TEST_F(MovieTest_1432, GetShowPoster_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    bool showPoster = movie.getShowPoster();
    // Just verify it returns without crashing
    (void)showPoster;
}

// Test getAspect returns dimensions
TEST_F(MovieTest_1432, GetAspect_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    int width = -1, height = -1;
    movie.getAspect(&width, &height);
    // Values should be set (possibly to 0 or some default)
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test getFloatingWindowSize returns dimensions
TEST_F(MovieTest_1432, GetFloatingWindowSize_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    int width = -1, height = -1;
    movie.getFloatingWindowSize(&width, &height);
    // Values should be set to some default
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test getActivationParameters returns a non-null pointer
TEST_F(MovieTest_1432, GetActivationParameters_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    const MovieActivationParameters *params = movie.getActivationParameters();
    EXPECT_NE(params, nullptr);
}

// Test getFileName - may return nullptr for empty dict
TEST_F(MovieTest_1432, GetFileName_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    const GooString *fileName = movie.getFileName();
    // With null dict, filename may be nullptr
    (void)fileName;
}

// Test getPoster returns an Object
TEST_F(MovieTest_1432, GetPoster_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    Object poster = movie.getPoster();
    // Just verify no crash
    (void)poster;
}

// Test copy constructor
TEST_F(MovieTest_1432, CopyConstructor_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    // Copied movie should have same properties
    EXPECT_EQ(movie.getRotationAngle(), movieCopy.getRotationAngle());
    EXPECT_EQ(movie.getShowPoster(), movieCopy.getShowPoster());
    EXPECT_EQ(movie.getUseFloatingWindow(), movieCopy.getUseFloatingWindow());
}

// Test that isOk reflects validity of construction
TEST_F(MovieTest_1432, IsOkWithNullDict_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    // With a null dict, movie is likely not ok
    EXPECT_FALSE(movie.isOk());
}

// Test activation parameters default values
TEST_F(MovieTest_1432, ActivationParametersDefaults_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    const MovieActivationParameters *params = movie.getActivationParameters();
    ASSERT_NE(params, nullptr);
    // Default floating window should be false
    EXPECT_FALSE(params->floatingWindow);
}

// Test that getUseFloatingWindow matches activation parameters
TEST_F(MovieTest_1432, UseFloatingWindowConsistentWithParams_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    const MovieActivationParameters *params = movie.getActivationParameters();
    ASSERT_NE(params, nullptr);
    EXPECT_EQ(movie.getUseFloatingWindow(), params->floatingWindow);
}

// Test copy preserves floating window size
TEST_F(MovieTest_1432, CopyPreservesFloatingWindowSize_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    int w1, h1, w2, h2;
    movie.getFloatingWindowSize(&w1, &h1);
    movieCopy.getFloatingWindowSize(&w2, &h2);
    EXPECT_EQ(w1, w2);
    EXPECT_EQ(h1, h2);
}

// Test copy preserves aspect ratio
TEST_F(MovieTest_1432, CopyPreservesAspect_1432) {
    Object movieDict;
    movieDict.initNull();
    Movie movie(&movieDict);
    Movie movieCopy(movie);
    
    int w1, h1, w2, h2;
    movie.getAspect(&w1, &h1);
    movieCopy.getAspect(&w2, &h2);
    EXPECT_EQ(w1, w2);
    EXPECT_EQ(h1, h2);
}
