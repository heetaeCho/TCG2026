#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Mock dependencies
class MockTextSelectionVisitor : public TextSelectionVisitor {
public:
    MOCK_METHOD(void, visit, (TextWord* word, const PDFRectangle* selection), (override));
};

TEST_F(TextWordTest_1181, GetLength_1181) {
    // Test normal operation: validate the behavior of getLength().
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);  // Initially, no chars added.
}

TEST_F(TextWordTest_1182, AddChar_1182) {
    // Test normal operation: validate addChar method and length increase.
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    word.addChar(&fontInfo, 0.0, 0.0, 1.0, 1.0, 0, 1, 65, 0, Matrix());
    
    EXPECT_EQ(word.getLength(), 1);  // After adding a character, length should be 1.
}

TEST_F(TextWordTest_1183, AddCombiningChar_1183) {
    // Test adding a combining character.
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    bool result = word.addCombining(&fontInfo, 12.0, 0.0, 0.0, 1.0, 1.0, 0, 1, 65, 0, Matrix());
    
    EXPECT_TRUE(result);  // Expect addCombining to return true (successful operation).
    EXPECT_EQ(word.getLength(), 1);  // Length should still increase after adding the combining character.
}

TEST_F(TextWordTest_1184, MergeWords_1184) {
    // Test merging two words together.
    TextWord word1(nullptr, 0, 12.0);
    TextWord word2(nullptr, 0, 12.0);
    
    TextFontInfo fontInfo;
    word1.addChar(&fontInfo, 0.0, 0.0, 1.0, 1.0, 0, 1, 65, 0, Matrix());
    word2.addChar(&fontInfo, 0.0, 0.0, 1.0, 1.0, 0, 1, 66, 0, Matrix());
    
    word1.merge(&word2);
    
    EXPECT_EQ(word1.getLength(), 2);  // After merging, word1 should contain both characters.
}

TEST_F(TextWordTest_1185, GetFontInfo_1185) {
    // Test retrieving font info for the word.
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    word.addChar(&fontInfo, 0.0, 0.0, 1.0, 1.0, 0, 1, 65, 0, Matrix());
    
    EXPECT_EQ(word.getFontInfo(0), &fontInfo);  // Should return the font info of the first character.
}

TEST_F(TextWordTest_1186, GetText_1186) {
    // Test the getText method, which should return the combined text as a string.
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    word.addChar(&fontInfo, 0.0, 0.0, 1.0, 1.0, 0, 1, 65, 0, Matrix());
    
    auto text = word.getText();
    EXPECT_EQ(*text, "A");  // The word should contain the character 'A'.
}

TEST_F(TextWordTest_1187, GetCharBBox_1187) {
    // Test getting the bounding box of a specific character.
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    word.addChar(&fontInfo, 0.0, 0.0, 1.0, 1.0, 0, 1, 65, 0, Matrix());
    
    double xMin, yMin, xMax, yMax;
    word.getCharBBox(0, &xMin, &yMin, &xMax, &yMax);
    
    EXPECT_EQ(xMin, 0.0);  // Expect the bounding box to start at the character's position.
    EXPECT_EQ(yMin, 0.0);
    EXPECT_EQ(xMax, 1.0);  // Expect the bounding box to be 1 unit wide.
    EXPECT_EQ(yMax, 1.0);  // Expect the bounding box to be 1 unit high.
}

TEST_F(TextWordTest_1188, IsUnderlined_1188) {
    // Test the isUnderlined method.
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    word.addChar(&fontInfo, 0.0, 0.0, 1.0, 1.0, 0, 1, 65, 0, Matrix());
    
    EXPECT_FALSE(word.isUnderlined());  // By default, text should not be underlined.
}

TEST_F(TextWordTest_1189, VisitSelection_1189) {
    // Test the visitSelection method with a mock selection visitor.
    MockTextSelectionVisitor visitor;
    TextWord word(nullptr, 0, 12.0);
    PDFRectangle selection;
    
    EXPECT_CALL(visitor, visit(&word, &selection)).Times(1);
    
    word.visitSelection(&visitor, &selection);  // This should invoke the visit method on the visitor.
}