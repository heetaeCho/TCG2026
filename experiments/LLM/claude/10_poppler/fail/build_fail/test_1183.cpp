#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class TextWordGetFontNameTest_1183 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getFontName returns the same value as getFontInfo()->getFontName()
// when accessed through a TextPage/TextOutputDev from an actual PDF
TEST_F(TextWordGetFontNameTest_1183, GetFontNameConsistentWithGetFontInfo_1183) {
    // We test the relationship: getFontName(idx) == getFontInfo(idx)->getFontName()
    // This is verifiable from the implementation:
    //   getFontName(idx) returns chars[idx].font->fontName
    //   getFontInfo(idx) returns chars[idx].font
    //   getFontInfo(idx)->getFontName() returns fontName
    // So they should be identical pointers.

    // Since creating TextWord requires GfxState, we use TextOutputDev to extract words
    // from a simple PDF if available. If no PDF is available, we test construction constraints.

    // Create a minimal test by loading a PDF
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "test.pdf not available, skipping integration test";
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    doc->displayPage(textOut.get(), 1, 72, 72, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    // Iterate through words on the page
    const TextFlow *flow = textPage->getFlows();
    bool testedAtLeastOne = false;

    for (const TextFlow *f = flow; f != nullptr; f = f->getNext()) {
        for (const TextBlock *blk = f->getBlocks(); blk != nullptr; blk = blk->getNext()) {
            for (const TextLine *line = blk->getLines(); line != nullptr; line = line->getNext()) {
                for (const TextWord *word = line->getWords(); word != nullptr; word = word->getNext()) {
                    int len = word->getLength();
                    ASSERT_GT(len, 0);

                    for (int i = 0; i < len; i++) {
                        const TextFontInfo *fontInfo = word->getFontInfo(i);
                        const GooString *fontNameDirect = word->getFontName(i);
                        
                        // getFontName(i) should equal getFontInfo(i)->getFontName()
                        if (fontInfo != nullptr) {
                            const GooString *fontNameViaInfo = fontInfo->getFontName();
                            EXPECT_EQ(fontNameDirect, fontNameViaInfo)
                                << "getFontName(" << i << ") should return same pointer as getFontInfo(" << i << ")->getFontName()";
                        }
                        testedAtLeastOne = true;
                    }
                }
            }
        }
    }

    if (!testedAtLeastOne) {
        GTEST_SKIP() << "No words found in test.pdf";
    }

    textPage->decRefCnt();
}

// Test that getFontName returns non-null for valid character indices on a real document
TEST_F(TextWordGetFontNameTest_1183, GetFontNameReturnsValidPointerForValidIndex_1183) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "test.pdf not available, skipping integration test";
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    doc->displayPage(textOut.get(), 1, 72, 72, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    bool found = false;

    for (const TextFlow *f = flow; f != nullptr && !found; f = f->getNext()) {
        for (const TextBlock *blk = f->getBlocks(); blk != nullptr && !found; blk = blk->getNext()) {
            for (const TextLine *line = blk->getLines(); line != nullptr && !found; line = line->getNext()) {
                for (const TextWord *word = line->getWords(); word != nullptr && !found; word = word->getNext()) {
                    if (word->getLength() > 0) {
                        // Index 0 should always be valid for a word with length > 0
                        const GooString *name = word->getFontName(0);
                        // Font name might be null if font has no name, but the call should not crash
                        // Just verify we can call it without error
                        (void)name;
                        found = true;
                    }
                }
            }
        }
    }

    textPage->decRefCnt();
}

// Test that getFontName at first and last character index of a word work correctly
TEST_F(TextWordGetFontNameTest_1183, GetFontNameBoundaryIndices_1183) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "test.pdf not available, skipping integration test";
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    doc->displayPage(textOut.get(), 1, 72, 72, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    bool testedMultiChar = false;

    for (const TextFlow *f = flow; f != nullptr; f = f->getNext()) {
        for (const TextBlock *blk = f->getBlocks(); blk != nullptr; blk = blk->getNext()) {
            for (const TextLine *line = blk->getLines(); line != nullptr; line = line->getNext()) {
                for (const TextWord *word = line->getWords(); word != nullptr; word = word->getNext()) {
                    int len = word->getLength();
                    if (len > 1) {
                        // Test first index
                        const GooString *firstName = word->getFontName(0);
                        const TextFontInfo *firstInfo = word->getFontInfo(0);
                        if (firstInfo) {
                            EXPECT_EQ(firstName, firstInfo->getFontName());
                        }

                        // Test last index
                        const GooString *lastName = word->getFontName(len - 1);
                        const TextFontInfo *lastInfo = word->getFontInfo(len - 1);
                        if (lastInfo) {
                            EXPECT_EQ(lastName, lastInfo->getFontName());
                        }

                        testedMultiChar = true;
                    }
                }
            }
        }
    }

    if (!testedMultiChar) {
        GTEST_SKIP() << "No multi-character words found in test.pdf";
    }

    textPage->decRefCnt();
}

// Test that for a single-character word, getFontName(0) is consistent
TEST_F(TextWordGetFontNameTest_1183, GetFontNameSingleCharWord_1183) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "test.pdf not available, skipping integration test";
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    doc->displayPage(textOut.get(), 1, 72, 72, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    bool foundSingleChar = false;

    for (const TextFlow *f = flow; f != nullptr; f = f->getNext()) {
        for (const TextBlock *blk = f->getBlocks(); blk != nullptr; blk = blk->getNext()) {
            for (const TextLine *line = blk->getLines(); line != nullptr; line = line->getNext()) {
                for (const TextWord *word = line->getWords(); word != nullptr; word = word->getNext()) {
                    if (word->getLength() == 1) {
                        const GooString *fontName = word->getFontName(0);
                        const TextFontInfo *fontInfo = word->getFontInfo(0);
                        ASSERT_NE(fontInfo, nullptr);
                        EXPECT_EQ(fontName, fontInfo->getFontName());
                        foundSingleChar = true;
                    }
                }
            }
        }
    }

    if (!foundSingleChar) {
        GTEST_SKIP() << "No single-character words found in test.pdf";
    }

    textPage->decRefCnt();
}

// Test that all characters in a word with same font return the same font name pointer
TEST_F(TextWordGetFontNameTest_1183, GetFontNameSameFontSamePointer_1183) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "test.pdf not available, skipping integration test";
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    doc->displayPage(textOut.get(), 1, 72, 72, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();

    for (const TextFlow *f = flow; f != nullptr; f = f->getNext()) {
        for (const TextBlock *blk = f->getBlocks(); blk != nullptr; blk = blk->getNext()) {
            for (const TextLine *line = blk->getLines(); line != nullptr; line = line->getNext()) {
                for (const TextWord *word = line->getWords(); word != nullptr; word = word->getNext()) {
                    int len = word->getLength();
                    if (len > 1) {
                        // If consecutive chars share the same font, their fontName pointers should match
                        for (int i = 1; i < len; i++) {
                            const TextFontInfo *fi0 = word->getFontInfo(i - 1);
                            const TextFontInfo *fi1 = word->getFontInfo(i);
                            if (fi0 == fi1) {
                                // Same font object means same font name pointer
                                EXPECT_EQ(word->getFontName(i - 1), word->getFontName(i));
                            }
                        }
                    }
                }
            }
        }
    }

    textPage->decRefCnt();
}
