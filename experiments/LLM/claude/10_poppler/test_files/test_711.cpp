#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageGetTrimBoxTest_711 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void loadDocument(const char* filename) {
        doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that getTrimBox returns a non-null pointer for a valid page
TEST_F(PageGetTrimBoxTest_711, GetTrimBoxReturnsNonNull_711) {
    // Use a simple PDF file for testing
    // We create a minimal PDF in memory using PDFDoc
    loadDocument("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);

    Page* page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle* trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test that getTrimBox returns a rectangle with valid dimensions
TEST_F(PageGetTrimBoxTest_711, GetTrimBoxHasValidDimensions_711) {
    loadDocument("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);

    Page* page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle* trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);

    // TrimBox should have non-negative width and height
    EXPECT_LE(trimBox->x1, trimBox->x2);
    EXPECT_LE(trimBox->y1, trimBox->y2);
}

// Test that getTrimBox is consistent with getMediaBox when no explicit TrimBox is set
// (default behavior: trimBox defaults to cropBox which defaults to mediaBox)
TEST_F(PageGetTrimBoxTest_711, GetTrimBoxDefaultsToCropOrMediaBox_711) {
    loadDocument("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);

    Page* page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle* trimBox = page->getTrimBox();
    const PDFRectangle* cropBox = page->getCropBox();
    ASSERT_NE(trimBox, nullptr);
    ASSERT_NE(cropBox, nullptr);

    // When no explicit trim box is defined, it should default to crop box
    // The trim box should be within or equal to the crop box
    EXPECT_GE(trimBox->x1, cropBox->x1 - 0.001);
    EXPECT_GE(trimBox->y1, cropBox->y1 - 0.001);
    EXPECT_LE(trimBox->x2, cropBox->x2 + 0.001);
    EXPECT_LE(trimBox->y2, cropBox->y2 + 0.001);
}

// Test that getTrimBox is bounded by mediaBox
TEST_F(PageGetTrimBoxTest_711, GetTrimBoxBoundedByMediaBox_711) {
    loadDocument("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);

    Page* page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle* trimBox = page->getTrimBox();
    const PDFRectangle* mediaBox = page->getMediaBox();
    ASSERT_NE(trimBox, nullptr);
    ASSERT_NE(mediaBox, nullptr);

    // Trim box should be clipped to media box
    EXPECT_GE(trimBox->x1, mediaBox->x1 - 0.001);
    EXPECT_GE(trimBox->y1, mediaBox->y1 - 0.001);
    EXPECT_LE(trimBox->x2, mediaBox->x2 + 0.001);
    EXPECT_LE(trimBox->y2, mediaBox->y2 + 0.001);
}

// Test getTrimBox on multiple pages if available
TEST_F(PageGetTrimBoxTest_711, GetTrimBoxMultiplePages_711) {
    loadDocument("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    ASSERT_TRUE(doc->isOk());

    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page* page = doc->getPage(i);
        ASSERT_NE(page, nullptr) << "Page " << i << " is null";

        const PDFRectangle* trimBox = page->getTrimBox();
        ASSERT_NE(trimBox, nullptr) << "TrimBox for page " << i << " is null";

        // Basic validity check
        double width = trimBox->x2 - trimBox->x1;
        double height = trimBox->y2 - trimBox->y1;
        EXPECT_GE(width, 0.0) << "TrimBox width negative for page " << i;
        EXPECT_GE(height, 0.0) << "TrimBox height negative for page " << i;
    }
}

// Test that calling getTrimBox multiple times returns the same pointer (stability)
TEST_F(PageGetTrimBoxTest_711, GetTrimBoxCalledMultipleTimesReturnsSameResult_711) {
    loadDocument("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);

    Page* page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle* trimBox1 = page->getTrimBox();
    const PDFRectangle* trimBox2 = page->getTrimBox();

    ASSERT_NE(trimBox1, nullptr);
    ASSERT_NE(trimBox2, nullptr);

    // Should return the same pointer (same underlying data)
    EXPECT_EQ(trimBox1, trimBox2);

    // Values should be identical
    EXPECT_DOUBLE_EQ(trimBox1->x1, trimBox2->x1);
    EXPECT_DOUBLE_EQ(trimBox1->y1, trimBox2->y1);
    EXPECT_DOUBLE_EQ(trimBox1->x2, trimBox2->x2);
    EXPECT_DOUBLE_EQ(trimBox1->y2, trimBox2->y2);
}

// Test that getTrimBox is const-correct (can be called on const reference)
TEST_F(PageGetTrimBoxTest_711, GetTrimBoxIsConst_711) {
    loadDocument("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);

    Page* page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // getTrimBox is declared const, so this should compile and work
    const Page* constPage = page;
    const PDFRectangle* trimBox = constPage->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}
