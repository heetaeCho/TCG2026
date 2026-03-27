#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Mock for the TextFontInfo class to be used in testing
class MockTextFontInfo : public TextFontInfo {
public:
    MOCK_CONST_METHOD0(getFontName, const GooString*());
    MOCK_CONST_METHOD0(isFixedWidth, bool());
    MOCK_CONST_METHOD0(isSerif, bool());
    MOCK_CONST_METHOD0(isSymbolic, bool());
    MOCK_CONST_METHOD0(isItalic, bool());
    MOCK_CONST_METHOD0(isBold, bool());
};

class TextWordTest_1183 : public ::testing::Test {
protected:
    // Test fixture can be used to set up common state for the tests
    const GfxState* gfxState = nullptr;  // Use appropriate state initialization as needed
    TextWord* textWord = nullptr;

    virtual void SetUp() override {
        textWord = new TextWord(gfxState, 0, 12.0);  // Assuming rotation 0 and font size 12.0 for testing
    }

    virtual void TearDown() override {
        delete textWord;
    }
};

// Normal operation: Testing getFontName() functionality
TEST_F(TextWordTest_1183, GetFontName_1183) {
    MockTextFontInfo mockFontInfo;
    GooString expectedFontName("Arial");

    EXPECT_CALL(mockFontInfo, getFontName())
        .WillOnce(testing::Return(&expectedFontName));

    // Simulate the addition of a character
    textWord->addChar(&mockFontInfo, 0.0, 0.0, 0.0, 0.0, 0, 1, 0, 0, Matrix());

    const GooString* fontName = textWord->getFontName(0);
    EXPECT_EQ(*fontName, expectedFontName);
}

// Boundary condition: Test the case when the index is out of range
TEST_F(TextWordTest_1183, GetFontName_OutOfRange_1183) {
    MockTextFontInfo mockFontInfo;
    GooString expectedFontName("Arial");

    EXPECT_CALL(mockFontInfo, getFontName())
        .WillOnce(testing::Return(&expectedFontName));

    // Simulate the addition of a character
    textWord->addChar(&mockFontInfo, 0.0, 0.0, 0.0, 0.0, 0, 1, 0, 0, Matrix());

    // Test out of range index
    const GooString* fontName = textWord->getFontName(1);  // Index 1 does not exist
    EXPECT_EQ(fontName, nullptr);  // Should return nullptr as the index is out of range
}

// Boundary condition: Test when the TextWord is empty (i.e., no characters added)
TEST_F(TextWordTest_1183, GetFontName_EmptyTextWord_1183) {
    const GooString* fontName = textWord->getFontName(0);  // No characters have been added yet
    EXPECT_EQ(fontName, nullptr);  // Should return nullptr
}

// Exceptional case: Test for invisible TextWord
TEST_F(TextWordTest_1183, IsInvisible_1183) {
    textWord->setInitialBounds(nullptr, 0.0, 0.0);  // Initialize with dummy data
    textWord->invisible = true;  // Simulate the TextWord being invisible
    EXPECT_TRUE(textWord->isUnderlined());  // Underlined should return true, based on current state
}

// Testing getFontInfo() with proper index
TEST_F(TextWordTest_1183, GetFontInfo_1183) {
    MockTextFontInfo mockFontInfo;
    EXPECT_CALL(mockFontInfo, isFixedWidth())
        .WillOnce(testing::Return(true));

    textWord->addChar(&mockFontInfo, 0.0, 0.0, 0.0, 0.0, 0, 1, 0, 0, Matrix());

    const TextFontInfo* fontInfo = textWord->getFontInfo(0);
    EXPECT_TRUE(fontInfo->isFixedWidth());  // Verifying that the font is fixed width
}

// Exceptional case: Test for getting CharCode and Unicode when the TextWord is empty
TEST_F(TextWordTest_1183, GetChar_EmptyTextWord_1183) {
    const Unicode* charUnicode = textWord->getChar(0);  // No characters have been added yet
    EXPECT_EQ(charUnicode, nullptr);  // Should return nullptr

    const CharCode* charCode = textWord->getChar(0);  // No characters have been added yet
    EXPECT_EQ(charCode, nullptr);  // Should return nullptr
}

// Testing the behavior of merge() method
TEST_F(TextWordTest_1183, MergeTextWords_1183) {
    TextWord* anotherTextWord = new TextWord(gfxState, 0, 12.0);  // Another TextWord to merge with

    // Simulate merging of TextWords
    textWord->merge(anotherTextWord);

    // Verify merge functionality if applicable
    EXPECT_TRUE(textWord->nextWord() != nullptr);  // Assuming that nextWord should point to the merged TextWord
    delete anotherTextWord;
}

// Verification of external interaction: Testing visitSelection() using mock
TEST_F(TextWordTest_1183, VisitSelection_1183) {
    TextSelectionVisitor mockVisitor;
    PDFRectangle selectionRect(0.0, 0.0, 100.0, 100.0);

    EXPECT_CALL(mockVisitor, visit(testing::_)).Times(1);  // Mocking the visit function

    textWord->visitSelection(&mockVisitor, &selectionRect);  // Invoking the visit method
}