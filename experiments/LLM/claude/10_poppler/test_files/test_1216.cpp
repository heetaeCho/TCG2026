#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

class TextPageTest_1216 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly created TextPage with rawOrder=false has no flows
TEST_F(TextPageTest_1216, NewTextPageHasNullFlows_1216) {
    TextPage page(false, false);
    EXPECT_EQ(page.getFlows(), nullptr);
}

// Test that a newly created TextPage with rawOrder=true has no flows
TEST_F(TextPageTest_1216, NewTextPageRawOrderHasNullFlows_1216) {
    TextPage page(true, false);
    EXPECT_EQ(page.getFlows(), nullptr);
}

// Test that a newly created TextPage with discardDiag=true has no flows
TEST_F(TextPageTest_1216, NewTextPageDiscardDiagHasNullFlows_1216) {
    TextPage page(false, true);
    EXPECT_EQ(page.getFlows(), nullptr);
}

// Test that a newly created TextPage with both flags true has no flows
TEST_F(TextPageTest_1216, NewTextPageBothFlagsHasNullFlows_1216) {
    TextPage page(true, true);
    EXPECT_EQ(page.getFlows(), nullptr);
}

// Test startPage and endPage cycle - after endPage with no content, flows should be null
TEST_F(TextPageTest_1216, StartPageEndPageNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();
    EXPECT_EQ(page.getFlows(), nullptr);
}

// Test that getFlows returns const pointer
TEST_F(TextPageTest_1216, GetFlowsReturnsConstPointer_1216) {
    TextPage page(false, false);
    const TextFlow *flows = page.getFlows();
    EXPECT_EQ(flows, nullptr);
}

// Test getText with no content returns empty string
TEST_F(TextPageTest_1216, GetTextNoContentReturnsEmpty_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();
    std::optional<PDFRectangle> area;
    const GooString text = page.getText(area, eolUnix, false);
    EXPECT_EQ(text.getLength(), 0);
}

// Test getText with physical layout and no content
TEST_F(TextPageTest_1216, GetTextPhysLayoutNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();
    std::optional<PDFRectangle> area;
    const GooString text = page.getText(area, eolUnix, true);
    EXPECT_EQ(text.getLength(), 0);
}

// Test makeWordList with no content
TEST_F(TextPageTest_1216, MakeWordListNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();
    std::unique_ptr<TextWordList> wordList = page.makeWordList(false);
    ASSERT_NE(wordList, nullptr);
    EXPECT_EQ(wordList->getLength(), 0);
}

// Test makeWordList with physical layout and no content
TEST_F(TextPageTest_1216, MakeWordListPhysLayoutNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();
    std::unique_ptr<TextWordList> wordList = page.makeWordList(true);
    ASSERT_NE(wordList, nullptr);
    EXPECT_EQ(wordList->getLength(), 0);
}

// Test findText with no content returns false
TEST_F(TextPageTest_1216, FindTextNoContentReturnsFalse_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();

    Unicode searchStr[] = { 'h', 'e', 'l', 'l', 'o' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool result = page.findText(searchStr, 5,
                                true, true, false, false,
                                false, false, false,
                                &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(result);
}

// Test findText with ignoreDiacritics overload and no content
TEST_F(TextPageTest_1216, FindTextIgnoreDiacriticsNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();

    Unicode searchStr[] = { 't', 'e', 's', 't' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool result = page.findText(searchStr, 4,
                                true, true, false, false,
                                false, false, false, false,
                                &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(result);
}

// Test setMergeCombining doesn't crash
TEST_F(TextPageTest_1216, SetMergeCombiningNoCrash_1216) {
    TextPage page(false, false);
    page.setMergeCombining(true);
    page.setMergeCombining(false);
    // Just verifying no crash occurs
    SUCCEED();
}

// Test coalesce with no content doesn't crash
TEST_F(TextPageTest_1216, CoalesceNoContentNoCrash_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.coalesce(false, 0.0, false);
    page.endPage();
    SUCCEED();
}

// Test coalesce with physical layout and no content
TEST_F(TextPageTest_1216, CoalescePhysLayoutNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.coalesce(true, 0.0, false);
    page.endPage();
    SUCCEED();
}

// Test coalesce 4-arg overload with no content
TEST_F(TextPageTest_1216, Coalesce4ArgNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.coalesce(false, 0.0, false, 1.0);
    page.endPage();
    SUCCEED();
}

// Test findCharRange with no content
TEST_F(TextPageTest_1216, FindCharRangeNoContent_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();

    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool result = page.findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(result);
}

// Test incCharCount doesn't crash with no word
TEST_F(TextPageTest_1216, IncCharCountNoWord_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.incCharCount(5);
    page.endPage();
    SUCCEED();
}

// Test endWord with no active word doesn't crash
TEST_F(TextPageTest_1216, EndWordNoActiveWord_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endWord();
    page.endPage();
    SUCCEED();
}

// Test multiple startPage/endPage cycles
TEST_F(TextPageTest_1216, MultipleStartEndPageCycles_1216) {
    TextPage page(false, false);
    for (int i = 0; i < 5; i++) {
        page.startPage(nullptr);
        page.endPage();
    }
    EXPECT_EQ(page.getFlows(), nullptr);
}

// Test getSelectionText with empty selection on empty page
TEST_F(TextPageTest_1216, GetSelectionTextEmptyPage_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();

    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    GooString selText = page.getSelectionText(&selection, selectionStyleGlyph);
    EXPECT_EQ(selText.getLength(), 0);
}

// Test getSelectionRegion with empty page
TEST_F(TextPageTest_1216, GetSelectionRegionEmptyPage_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();

    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    std::vector<PDFRectangle *> *regions = page.getSelectionRegion(&selection, selectionStyleGlyph, 1.0);
    ASSERT_NE(regions, nullptr);
    EXPECT_EQ(regions->size(), 0u);
    delete regions;
}

// Test copy constructor is deleted (compile-time check, just documenting)
TEST_F(TextPageTest_1216, TextPageIsNotCopyable_1216) {
    EXPECT_FALSE(std::is_copy_constructible<TextPage>::value);
}

// Test assignment operator is deleted (compile-time check)
TEST_F(TextPageTest_1216, TextPageIsNotCopyAssignable_1216) {
    EXPECT_FALSE(std::is_copy_assignable<TextPage>::value);
}

// Test getText with different EOL kinds on empty page
TEST_F(TextPageTest_1216, GetTextDifferentEOLKinds_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();
    std::optional<PDFRectangle> area;

    const GooString textUnix = page.getText(area, eolUnix, false);
    EXPECT_EQ(textUnix.getLength(), 0);

    const GooString textDos = page.getText(area, eolDOS, false);
    EXPECT_EQ(textDos.getLength(), 0);

    const GooString textMac = page.getText(area, eolMac, false);
    EXPECT_EQ(textMac.getLength(), 0);
}

// Test addUnderline doesn't crash
TEST_F(TextPageTest_1216, AddUnderlineNoCrash_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.addUnderline(0.0, 0.0, 100.0, 1.0);
    page.endPage();
    SUCCEED();
}

// Test findText with empty search string
TEST_F(TextPageTest_1216, FindTextEmptyString_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();

    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool result = page.findText(nullptr, 0,
                                true, true, false, false,
                                false, false, false,
                                &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(result);
}

// Test getSelectionWords with empty page
TEST_F(TextPageTest_1216, GetSelectionWordsEmptyPage_1216) {
    TextPage page(false, false);
    page.startPage(nullptr);
    page.endPage();

    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    auto words = page.getSelectionWords(&selection, selectionStyleGlyph);
    EXPECT_EQ(words.size(), 0u);
}
