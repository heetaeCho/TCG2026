#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Annot.h"

// Mock AnnotColor class
class MockAnnotColor : public AnnotColor {
public:
    MOCK_METHOD0(getColor, std::string());
};

// Test suite for DefaultAppearance class
class DefaultAppearanceTest_757 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup common to all tests
    }

    void TearDown() override {
        // Cleanup after each test if necessary
    }
};

// Test: DefaultAppearance constructor and getFontPtSize method
TEST_F(DefaultAppearanceTest_757, ConstructorAndGetFontPtSize_757) {
    // Create DefaultAppearance object
    DefaultAppearance da("Arial", 12.0, nullptr);
    
    // Assert the font size is correctly set and returned
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
}

// Test: setFontName and getFontName methods
TEST_F(DefaultAppearanceTest_757, SetAndGetFontName_757) {
    DefaultAppearance da("Arial", 12.0, nullptr);
    
    // Set font name and verify it
    da.setFontName("Helvetica");
    EXPECT_EQ(da.getFontName(), "Helvetica");
}

// Test: setFontPtSize and getFontPtSize methods
TEST_F(DefaultAppearanceTest_757, SetAndGetFontPtSize_757) {
    DefaultAppearance da("Arial", 12.0, nullptr);
    
    // Set font size and verify it
    da.setFontPtSize(14.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 14.0);
}

// Test: setFontColor (using unique_ptr) and getFontColor methods
TEST_F(DefaultAppearanceTest_757, SetAndGetFontColorWithUniquePtr_757) {
    auto mockColor = std::make_unique<MockAnnotColor>();
    DefaultAppearance da("Arial", 12.0, std::move(mockColor));

    // Verify that the font color is set correctly
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test: setFontColor with int value and getFontColor methods
TEST_F(DefaultAppearanceTest_757, SetAndGetFontColorWithInt_757) {
    DefaultAppearance da("Arial", 12.0, 0xFF00FF); // Set color as an integer
    EXPECT_EQ(da.getFontColor(), nullptr); // Color is stored as int
}

// Test: toAppearanceString method
TEST_F(DefaultAppearanceTest_757, ToAppearanceString_757) {
    DefaultAppearance da("Arial", 12.0, nullptr);
    EXPECT_EQ(da.toAppearanceString(), "Arial 12.0"); // Assuming a simple format
}

// Test: Exceptional case - setting a negative font size (boundary test)
TEST_F(DefaultAppearanceTest_757, SetNegativeFontSize_757) {
    DefaultAppearance da("Arial", 12.0, nullptr);
    
    // Set negative font size and check behavior (if any exception or special handling)
    da.setFontPtSize(-1.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), -1.0);
}

// Test: Exceptional case - setting invalid font name (boundary test)
TEST_F(DefaultAppearanceTest_757, SetInvalidFontName_757) {
    DefaultAppearance da("Arial", 12.0, nullptr);
    
    // Set invalid font name and verify it
    da.setFontName("");
    EXPECT_EQ(da.getFontName(), "");
}