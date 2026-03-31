#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cmath>

#include "Page.h"
#include "PDFDoc.h"
#include "PDFRectangle.h"
#include "GlobalParams.h"
#include "GooString.h"

class PageTest_708 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test getCropWidth with a standard PDF document
TEST_F(PageTest_708, GetCropWidthReturnsPositiveValue_708) {
    // Create a minimal PDF in memory or load from a known test file
    // Using Poppler's PDFDoc to create from a file
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        double cropWidth = page->getCropWidth();
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);
        
        double expectedWidth = cropBox->x2 - cropBox->x1;
        EXPECT_DOUBLE_EQ(cropWidth, expectedWidth);
    }
}

// Test getCropHeight returns correct value
TEST_F(PageTest_708, GetCropHeightReturnsCorrectValue_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        double cropHeight = page->getCropHeight();
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);
        
        double expectedHeight = cropBox->y2 - cropBox->y1;
        EXPECT_DOUBLE_EQ(cropHeight, expectedHeight);
    }
}

// Test getMediaWidth returns correct value
TEST_F(PageTest_708, GetMediaWidthReturnsCorrectValue_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        double mediaWidth = page->getMediaWidth();
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        
        double expectedWidth = mediaBox->x2 - mediaBox->x1;
        EXPECT_DOUBLE_EQ(mediaWidth, expectedWidth);
    }
}

// Test getMediaHeight returns correct value
TEST_F(PageTest_708, GetMediaHeightReturnsCorrectValue_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        double mediaHeight = page->getMediaHeight();
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        
        double expectedHeight = mediaBox->y2 - mediaBox->y1;
        EXPECT_DOUBLE_EQ(mediaHeight, expectedHeight);
    }
}

// Test getCropWidth is consistent with getCropBox
TEST_F(PageTest_708, CropWidthConsistentWithCropBox_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        // getCropWidth should always equal x2 - x1 of getCropBox
        EXPECT_DOUBLE_EQ(page->getCropWidth(), page->getCropBox()->x2 - page->getCropBox()->x1);
        EXPECT_DOUBLE_EQ(page->getCropHeight(), page->getCropBox()->y2 - page->getCropBox()->y1);
    }
}

// Test that crop dimensions are less than or equal to media dimensions when cropped
TEST_F(PageTest_708, CropDimensionsRelativeToMedia_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        // Crop box should be clipped to media box, so crop dims <= media dims
        EXPECT_LE(page->getCropWidth(), page->getMediaWidth() + 1e-9);
        EXPECT_LE(page->getCropHeight(), page->getMediaHeight() + 1e-9);
    }
}

// Test getNum returns correct page number
TEST_F(PageTest_708, GetNumReturnsPageNumber_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getNum(), 1);
    }
}

// Test getRotate returns valid rotation value
TEST_F(PageTest_708, GetRotateReturnsValidValue_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        int rotate = page->getRotate();
        // Rotation should be 0, 90, 180, or 270
        EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    }
}

// Test isOk returns true for valid page
TEST_F(PageTest_708, IsOkReturnsTrueForValidPage_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_TRUE(page->isOk());
    }
}

// Test getMediaBox returns non-null
TEST_F(PageTest_708, GetMediaBoxReturnsNonNull_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_NE(page->getMediaBox(), nullptr);
    }
}

// Test getCropBox returns non-null
TEST_F(PageTest_708, GetCropBoxReturnsNonNull_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_NE(page->getCropBox(), nullptr);
    }
}

// Test getBleedBox returns non-null
TEST_F(PageTest_708, GetBleedBoxReturnsNonNull_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_NE(page->getBleedBox(), nullptr);
    }
}

// Test getTrimBox returns non-null
TEST_F(PageTest_708, GetTrimBoxReturnsNonNull_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_NE(page->getTrimBox(), nullptr);
    }
}

// Test getArtBox returns non-null
TEST_F(PageTest_708, GetArtBoxReturnsNonNull_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_NE(page->getArtBox(), nullptr);
    }
}

// Test getDuration returns non-negative or -1 (no duration)
TEST_F(PageTest_708, GetDurationReturnsReasonableValue_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        double duration = page->getDuration();
        // Duration is typically -1 if not set, or positive
        EXPECT_TRUE(duration >= 0.0 || duration == -1.0);
    }
}

// Test getDoc returns the owning document
TEST_F(PageTest_708, GetDocReturnsOwningDocument_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getDoc(), doc.get());
    }
}

// Test getCropWidth is non-negative for valid page
TEST_F(PageTest_708, CropWidthIsNonNegative_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_GE(page->getCropWidth(), 0.0);
    }
}

// Test getCropHeight is non-negative for valid page
TEST_F(PageTest_708, CropHeightIsNonNegative_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_GE(page->getCropHeight(), 0.0);
    }
}

// Test multiple pages if available
TEST_F(PageTest_708, MultiplePagesCropWidthConsistency_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        for (int i = 1; i <= doc->getNumPages(); ++i) {
            Page *page = doc->getPage(i);
            ASSERT_NE(page, nullptr) << "Page " << i << " is null";
            EXPECT_EQ(page->getNum(), i);
            EXPECT_DOUBLE_EQ(page->getCropWidth(), page->getCropBox()->x2 - page->getCropBox()->x1)
                << "CropWidth mismatch on page " << i;
        }
    }
}

// Test getStructParents returns a valid value
TEST_F(PageTest_708, GetStructParentsReturnsValue_708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"));
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // structParents can be -1 if not set, or a non-negative integer
        int sp = page->getStructParents();
        EXPECT_GE(sp, -1);
    }
}

// Test PDFRectangle basic properties
TEST_F(PageTest_708, PDFRectangleDefaultConstruction_708) {
    PDFRectangle rect;
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

TEST_F(PageTest_708, PDFRectangleParameterizedConstruction_708) {
    PDFRectangle rect(10.0, 20.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(rect.x1, 10.0);
    EXPECT_DOUBLE_EQ(rect.y1, 20.0);
    EXPECT_DOUBLE_EQ(rect.x2, 300.0);
    EXPECT_DOUBLE_EQ(rect.y2, 400.0);
}

TEST_F(PageTest_708, PDFRectangleWidthCalculation_708) {
    PDFRectangle rect(10.0, 20.0, 310.0, 420.0);
    double width = rect.x2 - rect.x1;
    EXPECT_DOUBLE_EQ(width, 300.0);
}

TEST_F(PageTest_708, PDFRectangleEquality_708) {
    PDFRectangle rect1(10.0, 20.0, 310.0, 420.0);
    PDFRectangle rect2(10.0, 20.0, 310.0, 420.0);
    EXPECT_TRUE(rect1 == rect2);
}

TEST_F(PageTest_708, PDFRectangleInequality_708) {
    PDFRectangle rect1(10.0, 20.0, 310.0, 420.0);
    PDFRectangle rect2(10.0, 20.0, 310.0, 421.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PageTest_708, PDFRectangleIsEmptyDefault_708) {
    PDFRectangle rect;
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PageTest_708, PDFRectangleIsNotEmptyWhenSet_708) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    EXPECT_FALSE(rect.isEmpty());
}

TEST_F(PageTest_708, PDFRectangleContainsPoint_708) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    EXPECT_TRUE(rect.contains(50.0, 50.0));
    EXPECT_FALSE(rect.contains(150.0, 50.0));
}

TEST_F(PageTest_708, PDFRectangleContainsBoundary_708) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    // Test boundary points
    EXPECT_TRUE(rect.contains(0.0, 0.0));
    EXPECT_TRUE(rect.contains(100.0, 100.0));
}

TEST_F(PageTest_708, PDFRectangleZeroWidthCropWidth_708) {
    // Simulating zero-width scenario
    PDFRectangle rect(50.0, 0.0, 50.0, 100.0);
    double width = rect.x2 - rect.x1;
    EXPECT_DOUBLE_EQ(width, 0.0);
}
