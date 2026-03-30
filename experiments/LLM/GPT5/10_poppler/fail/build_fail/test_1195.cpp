#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Mock external dependencies (if necessary)
class MockTextFontInfo : public TextFontInfo {
public:
    MOCK_METHOD0(getFontSize, double());
    MOCK_METHOD0(getFontName, std::string());
};

// Test class for TextWord
class TextWordTest_1195 : public testing::Test {
protected:
    // Test fixture setup
    TextWord* textWord;
    
    // Set up method
    void SetUp() override {
        // Construct a basic TextWord instance for testing
        textWord = new TextWord(nullptr, 0, 12.0);  // Example with rotation 0 and font size 12.0
    }

    // Tear down method
    void TearDown() override {
        delete textWord;
    }
};

// Test case for normal operation of getBaseline()
TEST_F(TextWordTest_1195, GetBaseline_NormalOperation_1195) {
    double baseline = textWord->getBaseline();
    EXPECT_EQ(baseline, 0.0);  // Since base is initialized to 0.0 in the constructor
}

// Test case for boundary condition with edge cases
TEST_F(TextWordTest_1195, GetBaseline_BoundaryCondition_1195) {
    // Test with very large value
    TextWord largeBaseWord(nullptr, 0, 10000.0);
    EXPECT_EQ(largeBaseWord.getBaseline(), 0.0);  // Assuming that no change in baseline

    // Test with very small value
    TextWord smallBaseWord(nullptr, 0, 0.0001);
    EXPECT_EQ(smallBaseWord.getBaseline(), 0.0);  // Assuming that no change in baseline
}

// Test case for error condition - mocked TextFontInfo
TEST_F(TextWordTest_1195, GetFontInfo_ErrorCase_1195) {
    MockTextFontInfo mockFontInfo;
    EXPECT_CALL(mockFontInfo, getFontSize())
        .WillOnce(testing::Throw(std::runtime_error("Font size error")));
    
    try {
        textWord->getFontInfo(0);
        FAIL() << "Expected std::runtime_error";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Font size error");
    }
}

// Test case for getRotation method - verifying normal operation
TEST_F(TextWordTest_1195, GetRotation_1195) {
    EXPECT_EQ(textWord->getRotation(), 0);  // Default rotation is 0
}

// Test case for getFontSize method - checking return value
TEST_F(TextWordTest_1195, GetFontSize_1195) {
    EXPECT_EQ(textWord->getFontSize(), 12.0);  // fontSize initialized to 12.0
}

// Test case for verifying behavior when there is a next word
TEST_F(TextWordTest_1195, NextWord_Exists_1195) {
    TextWord* nextWord = new TextWord(nullptr, 0, 12.0);
    textWord->nextWord() = nextWord;
    
    EXPECT_EQ(textWord->nextWord(), nextWord);
}

// Test case for when no next word exists
TEST_F(TextWordTest_1195, NextWord_NotExists_1195) {
    EXPECT_EQ(textWord->nextWord(), nullptr);
}