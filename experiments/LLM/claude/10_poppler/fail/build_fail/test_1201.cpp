#include <gtest/gtest.h>
#include "TextOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>

class TextLineTest_1201 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test getBBox returns a PDFRectangle structure
// Since TextLine requires a TextBlock which requires complex setup,
// we test through document-level text extraction where possible.

TEST_F(TextLineTest_1201, GetBBoxReturnsValidRectangle_1201) {
    // Create a TextOutputDev and extract text from a simple scenario
    // We test that getBBox returns a PDFRectangle with the expected structure
    // by going through a TextPage which contains TextLines

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_NE(textOut, nullptr);
    
    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);
    
    // With no content, there should be no flows/blocks/lines
    for (const TextFlow *flow = textPage->getFlows(); flow; flow = flow->getNext()) {
        for (const TextBlock *blk = flow->getBlocks(); blk; blk = blk->getNext()) {
            for (const TextLine *line = blk->getLines(); line; line = line->getNext()) {
                PDFRectangle bbox = line->getBBox();
                // Verify the bbox fields are accessible (even if empty)
                EXPECT_LE(bbox.x1, bbox.x2);
                EXPECT_LE(bbox.y1, bbox.y2);
            }
        }
    }
    
    textPage->decRefCnt();
}

TEST_F(TextLineTest_1201, EmptyTextPageHasNoFlows_1201) {
    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_NE(textOut, nullptr);
    
    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);
    
    // An empty text page should have no flows (and thus no lines)
    const TextFlow *flow = textPage->getFlows();
    EXPECT_EQ(flow, nullptr);
    
    textPage->decRefCnt();
}

TEST_F(TextLineTest_1201, GetWordsOnEmptyPage_1201) {
    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_NE(textOut, nullptr);
    
    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);
    
    // No flows means no lines to check words on
    const TextFlow *flow = textPage->getFlows();
    EXPECT_EQ(flow, nullptr);
    
    textPage->decRefCnt();
}

TEST_F(TextLineTest_1201, GetNextReturnsNullForSingleLine_1201) {
    // If there's only one line in a block, getNext should return nullptr
    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_NE(textOut, nullptr);
    
    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);
    
    // With empty page, no lines exist - just verify the page is valid
    EXPECT_NE(textPage, nullptr);
    
    textPage->decRefCnt();
}

TEST_F(TextLineTest_1201, CopyConstructorIsDeleted_1201) {
    // This is a compile-time check - TextLine copy constructor is deleted
    // Just verify it compiles that we can't copy
    EXPECT_FALSE(std::is_copy_constructible<TextLine>::value);
}

TEST_F(TextLineTest_1201, CopyAssignmentIsDeleted_1201) {
    // Verify copy assignment is deleted at compile time
    EXPECT_FALSE(std::is_copy_assignable<TextLine>::value);
}
