#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>

// We need to test TextBlock's public interface, specifically getBBox() which returns PDFRectangle.
// Since TextBlock requires a TextPage and has complex dependencies, we focus on what we can
// test through the public interface.

class TextBlockTest_1208 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test: getBBox returns a PDFRectangle with the expected structure
// Since we can't easily construct a TextBlock without internal dependencies,
// we test through document loading if possible, or verify interface consistency.

// We'll test by loading a real PDF and extracting text blocks from a page.
class TextBlockFromDocTest_1208 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getBBox() (PDFRectangle version) returns consistent values with
// getBBox(double*, double*, double*, double*) version
TEST_F(TextBlockFromDocTest_1208, GetBBoxReturnsValidRectangle_1208)
{
    // Create a simple PDF document for testing
    // We use a known test PDF if available, otherwise we test the interface contract
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);

    if (!doc->isOk()) {
        // Try alternative path
        GooString fileName2("test/unittestcases/WithActualText.pdf");
        doc = std::make_unique<PDFDoc>(&fileName2);
    }

    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_TRUE(textOut->isOk());

    doc->displayPage(textOut.get(), 1, 72.0, 72.0, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    // Get flows and blocks
    const TextFlow *flow = textPage->getFlows();
    if (flow != nullptr) {
        const TextBlock *block = flow->getBlocks();
        if (block != nullptr) {
            // Test PDFRectangle version of getBBox
            PDFRectangle rect = block->getBBox();

            // Test double* version of getBBox
            double xMin, yMin, xMax, yMax;
            block->getBBox(&xMin, &yMin, &xMax, &yMax);

            // Both versions should return the same values
            EXPECT_DOUBLE_EQ(rect.x1, xMin);
            EXPECT_DOUBLE_EQ(rect.y1, yMin);
            EXPECT_DOUBLE_EQ(rect.x2, xMax);
            EXPECT_DOUBLE_EQ(rect.y2, yMax);

            // Bounding box should be valid (max >= min)
            EXPECT_LE(xMin, xMax);
            EXPECT_LE(yMin, yMax);
        }
    }

    textPage->decRefCnt();
}

// Test that getLines() returns non-null for blocks with content
TEST_F(TextBlockFromDocTest_1208, GetLinesReturnsLinesForNonEmptyBlock_1208)
{
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);

    if (!doc->isOk()) {
        GooString fileName2("test/unittestcases/WithActualText.pdf");
        doc = std::make_unique<PDFDoc>(&fileName2);
    }

    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_TRUE(textOut->isOk());

    doc->displayPage(textOut.get(), 1, 72.0, 72.0, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    if (flow != nullptr) {
        const TextBlock *block = flow->getBlocks();
        if (block != nullptr) {
            // A block from a real PDF should have at least one line
            const TextLine *lines = block->getLines();
            EXPECT_NE(lines, nullptr);

            // Line count should be positive
            int lineCount = block->getLineCount();
            EXPECT_GT(lineCount, 0);
        }
    }

    textPage->decRefCnt();
}

// Test getNext() for block traversal
TEST_F(TextBlockFromDocTest_1208, GetNextTraversesBlocks_1208)
{
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);

    if (!doc->isOk()) {
        GooString fileName2("test/unittestcases/WithActualText.pdf");
        doc = std::make_unique<PDFDoc>(&fileName2);
    }

    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_TRUE(textOut->isOk());

    doc->displayPage(textOut.get(), 1, 72.0, 72.0, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    if (flow != nullptr) {
        const TextBlock *block = flow->getBlocks();
        int blockCount = 0;
        while (block != nullptr) {
            blockCount++;
            // Each block should have a valid bounding box
            PDFRectangle rect = block->getBBox();
            EXPECT_LE(rect.x1, rect.x2);
            EXPECT_LE(rect.y1, rect.y2);
            block = block->getNext();
        }
        // We traversed at least one block
        EXPECT_GT(blockCount, 0);
    }

    textPage->decRefCnt();
}

// Test that getBBox values are non-negative for typical page coordinates
TEST_F(TextBlockFromDocTest_1208, GetBBoxValuesAreNonNegative_1208)
{
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);

    if (!doc->isOk()) {
        GooString fileName2("test/unittestcases/WithActualText.pdf");
        doc = std::make_unique<PDFDoc>(&fileName2);
    }

    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_TRUE(textOut->isOk());

    doc->displayPage(textOut.get(), 1, 72.0, 72.0, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    if (flow != nullptr) {
        const TextBlock *block = flow->getBlocks();
        if (block != nullptr) {
            double xMin, yMin, xMax, yMax;
            block->getBBox(&xMin, &yMin, &xMax, &yMax);

            // For a standard page, coordinates should be non-negative
            EXPECT_GE(xMin, 0.0);
            EXPECT_GE(yMin, 0.0);
            EXPECT_GE(xMax, 0.0);
            EXPECT_GE(yMax, 0.0);
        }
    }

    textPage->decRefCnt();
}

// Test getLineCount consistency with iterating lines
TEST_F(TextBlockFromDocTest_1208, GetLineCountMatchesLineIteration_1208)
{
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);

    if (!doc->isOk()) {
        GooString fileName2("test/unittestcases/WithActualText.pdf");
        doc = std::make_unique<PDFDoc>(&fileName2);
    }

    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_TRUE(textOut->isOk());

    doc->displayPage(textOut.get(), 1, 72.0, 72.0, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    if (flow != nullptr) {
        const TextBlock *block = flow->getBlocks();
        if (block != nullptr) {
            int reportedCount = block->getLineCount();

            // Count lines manually
            int manualCount = 0;
            const TextLine *line = block->getLines();
            while (line != nullptr) {
                manualCount++;
                line = line->getNext();
            }

            EXPECT_EQ(reportedCount, manualCount);
        }
    }

    textPage->decRefCnt();
}

// Test that PDFRectangle getBBox and pointer getBBox are consistent across multiple blocks
TEST_F(TextBlockFromDocTest_1208, BothGetBBoxVersionsConsistentAcrossBlocks_1208)
{
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);

    if (!doc->isOk()) {
        GooString fileName2("test/unittestcases/WithActualText.pdf");
        doc = std::make_unique<PDFDoc>(&fileName2);
    }

    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false);
    ASSERT_TRUE(textOut->isOk());

    doc->displayPage(textOut.get(), 1, 72.0, 72.0, 0, true, false, false);

    TextPage *textPage = textOut->takeText();
    ASSERT_NE(textPage, nullptr);

    const TextFlow *flow = textPage->getFlows();
    while (flow != nullptr) {
        const TextBlock *block = flow->getBlocks();
        while (block != nullptr) {
            PDFRectangle rect = block->getBBox();
            double xMin, yMin, xMax, yMax;
            block->getBBox(&xMin, &yMin, &xMax, &yMax);

            EXPECT_DOUBLE_EQ(rect.x1, xMin);
            EXPECT_DOUBLE_EQ(rect.y1, yMin);
            EXPECT_DOUBLE_EQ(rect.x2, xMax);
            EXPECT_DOUBLE_EQ(rect.y2, yMax);

            block = block->getNext();
        }
        flow = flow->getNext();
    }

    textPage->decRefCnt();
}
