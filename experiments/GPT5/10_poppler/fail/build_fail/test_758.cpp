#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "Annot.h"  // Assuming the file is included here.

class MockAnnotColor : public AnnotColor {
public:
    MOCK_CONST_METHOD0(getColor, std::string());  // Mocking the getColor method.
};

// Test fixture for DefaultAppearance
class DefaultAppearanceTest : public ::testing::Test {
protected:
    // Default constructor for setting up test cases
    DefaultAppearanceTest() {
        // Optional: Initialize any resources needed for all tests
    }

    // Helper function to create a DefaultAppearance with a mock fontColor
    std::unique_ptr<DefaultAppearance> createDefaultAppearance(const std::string& fontName, double fontPtSize, std::unique_ptr<AnnotColor> fontColor) {
        return std::make_unique<DefaultAppearance>(fontName, fontPtSize, std::move(fontColor));
    }

    // Helper function to create DefaultAppearance with an integer fontColor
    std::unique_ptr<DefaultAppearance> createDefaultAppearanceWithIntColor(const std::string& fontName, double fontPtSize, int fontColor) {
        return std::make_unique<DefaultAppearance>(fontName, fontPtSize, std::move(fontColor));
    }
};

// Test for DefaultAppearance constructor and getter methods
TEST_F(DefaultAppearanceTest, ConstructorAndGetters_758) {
    std::string fontName = "Arial";
    double fontPtSize = 12.0;
    auto mockColor = std::make_unique<MockAnnotColor>();
    EXPECT_CALL(*mockColor, getColor()).WillOnce(testing::Return("Red"));

    auto defaultAppearance = createDefaultAppearance(fontName, fontPtSize, std::move(mockColor));

    EXPECT_EQ(defaultAppearance->getFontName(), fontName);
    EXPECT_EQ(defaultAppearance->getFontPtSize(), fontPtSize);
    EXPECT_EQ(defaultAppearance->getFontColor()->getColor(), "Red");
}

// Test for setFontName method
TEST_F(DefaultAppearanceTest, SetFontName_758) {
    std::string fontName = "Times New Roman";
    double fontPtSize = 14.0;
    auto mockColor = std::make_unique<MockAnnotColor>();

    auto defaultAppearance = createDefaultAppearance("Arial", fontPtSize, std::move(mockColor));

    defaultAppearance->setFontName(fontName);

    EXPECT_EQ(defaultAppearance->getFontName(), fontName);
}

// Test for setFontPtSize method
TEST_F(DefaultAppearanceTest, SetFontPtSize_758) {
    std::string fontName = "Helvetica";
    double fontPtSize = 10.0;
    auto mockColor = std::make_unique<MockAnnotColor>();

    auto defaultAppearance = createDefaultAppearance(fontName, fontPtSize, std::move(mockColor));

    double newFontPtSize = 16.0;
    defaultAppearance->setFontPtSize(newFontPtSize);

    EXPECT_EQ(defaultAppearance->getFontPtSize(), newFontPtSize);
}

// Test for setFontColor with unique_ptr
TEST_F(DefaultAppearanceTest, SetFontColorWithUniquePtr_758) {
    std::string fontName = "Courier";
    double fontPtSize = 11.0;
    auto mockColor = std::make_unique<MockAnnotColor>();
    EXPECT_CALL(*mockColor, getColor()).WillOnce(testing::Return("Blue"));

    auto defaultAppearance = createDefaultAppearance(fontName, fontPtSize, std::move(mockColor));

    auto newColor = std::make_unique<MockAnnotColor>();
    EXPECT_CALL(*newColor, getColor()).WillOnce(testing::Return("Green"));
    defaultAppearance->setFontColor(std::move(newColor));

    EXPECT_EQ(defaultAppearance->getFontColor()->getColor(), "Green");
}

// Test for setFontColor with int
TEST_F(DefaultAppearanceTest, SetFontColorWithInt_758) {
    std::string fontName = "Georgia";
    double fontPtSize = 15.0;
    int fontColor = 0xFF00FF;  // Purple color as int

    auto defaultAppearance = createDefaultAppearanceWithIntColor(fontName, fontPtSize, fontColor);
    
    // Assuming the setter directly sets the color integer
    defaultAppearance->setFontColor(0x00FF00);  // Green color
    
    // Check that the font color has been set to green (represented as an int)
    EXPECT_EQ(defaultAppearance->getFontColor()->getColor(), "Green");
}

// Test for toAppearanceString method
TEST_F(DefaultAppearanceTest, ToAppearanceString_758) {
    std::string fontName = "Verdana";
    double fontPtSize = 18.0;
    auto mockColor = std::make_unique<MockAnnotColor>();
    EXPECT_CALL(*mockColor, getColor()).WillOnce(testing::Return("Yellow"));

    auto defaultAppearance = createDefaultAppearance(fontName, fontPtSize, std::move(mockColor));

    std::string appearanceString = defaultAppearance->toAppearanceString();

    EXPECT_TRUE(appearanceString.find(fontName) != std::string::npos);
    EXPECT_TRUE(appearanceString.find("Yellow") != std::string::npos);
}

// Test for exceptional case with invalid font color
TEST_F(DefaultAppearanceTest, SetFontColor_InvalidColor_758) {
    std::string fontName = "Comic Sans";
    double fontPtSize = 9.0;
    
    // Testing with an invalid color (assuming the constructor can handle this case)
    try {
        auto defaultAppearance = createDefaultAppearanceWithIntColor(fontName, fontPtSize, -1);  // Invalid color
        FAIL() << "Expected exception for invalid color";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Invalid color value");
    }
}

// Test for boundary condition with maximum font size
TEST_F(DefaultAppearanceTest, MaxFontSize_758) {
    std::string fontName = "Arial";
    double fontPtSize = 1000.0;  // Assuming 1000 is a valid boundary for font size
    auto mockColor = std::make_unique<MockAnnotColor>();

    auto defaultAppearance = createDefaultAppearance(fontName, fontPtSize, std::move(mockColor));

    EXPECT_EQ(defaultAppearance->getFontPtSize(), fontPtSize);
}

// Test for boundary condition with minimum font size
TEST_F(DefaultAppearanceTest, MinFontSize_758) {
    std::string fontName = "Arial";
    double fontPtSize = 0.0;  // Assuming 0 is a valid minimum for font size
    auto mockColor = std::make_unique<MockAnnotColor>();

    auto defaultAppearance = createDefaultAppearance(fontName, fontPtSize, std::move(mockColor));

    EXPECT_EQ(defaultAppearance->getFontPtSize(), fontPtSize);
}