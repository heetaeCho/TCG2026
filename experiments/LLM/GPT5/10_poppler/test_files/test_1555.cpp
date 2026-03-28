#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <array>
#include "SplashFont.h" // Assuming the header file is included

// Mock class for SplashFontFile (assuming it's a dependency)
class MockSplashFontFile : public SplashFontFile {
public:
    MOCK_METHOD(void, someMethod, (), (override));  // Example method to mock
};

class SplashFontTest_1555 : public ::testing::Test {
protected:
    // Test Setup: Create a shared pointer to the SplashFontFile and necessary matrices
    std::shared_ptr<MockSplashFontFile> mockFontFile;
    std::array<SplashCoord, 4> mat = {{0, 0, 0, 0}};
    std::array<SplashCoord, 4> textMat = {{0, 0, 0, 0}};
    
    // Create SplashFont instance in setup
    SplashFont *splashFont;
    
    void SetUp() override {
        mockFontFile = std::make_shared<MockSplashFontFile>();
        splashFont = new SplashFont(mockFontFile, mat, textMat, false);
    }
    
    void TearDown() override {
        delete splashFont;
    }
};

// Normal operation test for getBBox
TEST_F(SplashFontTest_1555, GetBBox_Normal_1555) {
    int xMin, yMin, xMax, yMax;
    splashFont->getBBox(&xMin, &yMin, &xMax, &yMax);
    
    // Verify that the bounding box values are set correctly
    EXPECT_EQ(xMin, splashFont->xMin);
    EXPECT_EQ(yMin, splashFont->yMin);
    EXPECT_EQ(xMax, splashFont->xMax);
    EXPECT_EQ(yMax, splashFont->yMax);
}

// Boundary test for getBBox with extreme values
TEST_F(SplashFontTest_1555, GetBBox_Boundary_1555) {
    // Set extreme bounding box values
    splashFont->xMin = INT_MIN;
    splashFont->yMin = INT_MIN;
    splashFont->xMax = INT_MAX;
    splashFont->yMax = INT_MAX;

    int xMin, yMin, xMax, yMax;
    splashFont->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, INT_MIN);
    EXPECT_EQ(yMin, INT_MIN);
    EXPECT_EQ(xMax, INT_MAX);
    EXPECT_EQ(yMax, INT_MAX);
}

// Test exceptional case for getBBox with nullptr inputs
TEST_F(SplashFontTest_1555, GetBBox_Exceptional_1555) {
    // Pass nullptr for the bounding box pointers
    EXPECT_DEATH({
        splashFont->getBBox(nullptr, nullptr, nullptr, nullptr);
    }, ".*");
}

// Test the getFontFile method to ensure it returns the correct font file
TEST_F(SplashFontTest_1555, GetFontFile_1555) {
    std::shared_ptr<SplashFontFile> fontFile = splashFont->getFontFile();
    EXPECT_EQ(fontFile, mockFontFile);
}

// Test the matches method for comparing font file and matrices
TEST_F(SplashFontTest_1555, Matches_1555) {
    bool result = splashFont->matches(mockFontFile, mat, textMat);
    EXPECT_TRUE(result);
}