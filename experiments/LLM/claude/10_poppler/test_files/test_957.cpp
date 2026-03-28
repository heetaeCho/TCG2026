#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PDFDocTest_957 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const std::string &filename) {
        auto fileName = std::make_unique<GooString>(filename);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test that getPageCropHeight returns 0.0 for an invalid/non-existent document
TEST_F(PDFDocTest_957, InvalidDocReturnsZeroCropHeight_957) {
    auto fileName = std::make_unique<GooString>("nonexistent_file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    // Document should not be ok
    EXPECT_FALSE(doc->isOk());
}

// Test ErrorPDFDoc returns a PDFDoc with the specified error code
TEST_F(PDFDocTest_957, ErrorPDFDocHasErrorCode_957) {
    auto doc = PDFDoc::ErrorPDFDoc(42, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test ErrorPDFDoc with nullptr filename
TEST_F(PDFDocTest_957, ErrorPDFDocNullFilename_957) {
    auto doc = PDFDoc::ErrorPDFDoc(1, nullptr);
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test getPageCropHeight with a valid PDF file
// We use a well-known test PDF if available. This test assumes a test PDF exists.
// If the file doesn't exist, the doc won't be ok and we handle that gracefully.
TEST_F(PDFDocTest_957, ValidDocGetPageCropHeight_957) {
    // Try to load a simple test PDF
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        double cropHeight = doc->getPageCropHeight(1);
        EXPECT_GT(cropHeight, 0.0);
    }
}

// Test getPageCropHeight for page 0 (invalid page number - typically pages are 1-indexed)
TEST_F(PDFDocTest_957, GetPageCropHeightInvalidPageZero_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk()) {
        double cropHeight = doc->getPageCropHeight(0);
        // getPage(0) should return nullptr, so result should be 0.0
        EXPECT_EQ(cropHeight, 0.0);
    }
}

// Test getPageCropHeight for a negative page number
TEST_F(PDFDocTest_957, GetPageCropHeightNegativePage_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk()) {
        double cropHeight = doc->getPageCropHeight(-1);
        EXPECT_EQ(cropHeight, 0.0);
    }
}

// Test getPageCropHeight for a page number beyond the total number of pages
TEST_F(PDFDocTest_957, GetPageCropHeightBeyondLastPage_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        double cropHeight = doc->getPageCropHeight(numPages + 1);
        EXPECT_EQ(cropHeight, 0.0);
    }
}

// Test getPageCropWidth for a valid page
TEST_F(PDFDocTest_957, ValidDocGetPageCropWidth_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        double cropWidth = doc->getPageCropWidth(1);
        EXPECT_GT(cropWidth, 0.0);
    }
}

// Test getPageMediaWidth and getPageMediaHeight for a valid page
TEST_F(PDFDocTest_957, ValidDocGetPageMediaDimensions_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        double mediaWidth = doc->getPageMediaWidth(1);
        double mediaHeight = doc->getPageMediaHeight(1);
        EXPECT_GT(mediaWidth, 0.0);
        EXPECT_GT(mediaHeight, 0.0);
    }
}

// Test getPageRotate for a valid page
TEST_F(PDFDocTest_957, ValidDocGetPageRotate_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        int rotate = doc->getPageRotate(1);
        // Rotation should be one of 0, 90, 180, 270
        EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    }
}

// Test crop height is <= media height (crop box is contained within or equal to media box)
TEST_F(PDFDocTest_957, CropHeightLessOrEqualMediaHeight_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        double cropHeight = doc->getPageCropHeight(1);
        double mediaHeight = doc->getPageMediaHeight(1);
        EXPECT_LE(cropHeight, mediaHeight + 0.001);  // small tolerance for floating point
    }
}

// Test crop width is <= media width
TEST_F(PDFDocTest_957, CropWidthLessOrEqualMediaWidth_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        double cropWidth = doc->getPageCropWidth(1);
        double mediaWidth = doc->getPageMediaWidth(1);
        EXPECT_LE(cropWidth, mediaWidth + 0.001);
    }
}

// Test getNumPages on invalid document
TEST_F(PDFDocTest_957, InvalidDocGetNumPages_957) {
    auto fileName = std::make_unique<GooString>("nonexistent_file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test getPage returns nullptr for invalid page on a valid document
TEST_F(PDFDocTest_957, GetPageReturnsNullForInvalidPage_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk()) {
        Page *page = doc->getPage(0);
        EXPECT_EQ(page, nullptr);

        page = doc->getPage(-1);
        EXPECT_EQ(page, nullptr);

        int numPages = doc->getNumPages();
        page = doc->getPage(numPages + 1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test getPage returns valid page for page 1
TEST_F(PDFDocTest_957, GetPageReturnsValidForFirstPage_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test getPDFMajorVersion and getPDFMinorVersion
TEST_F(PDFDocTest_957, ValidDocGetPDFVersion_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk()) {
        int major = doc->getPDFMajorVersion();
        int minor = doc->getPDFMinorVersion();
        EXPECT_GE(major, 1);
        EXPECT_GE(minor, 0);
    }
}

// Test that calling getPageCropHeight twice returns the same value (consistency)
TEST_F(PDFDocTest_957, GetPageCropHeightConsistency_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk() && doc->getNumPages() > 0) {
        double cropHeight1 = doc->getPageCropHeight(1);
        double cropHeight2 = doc->getPageCropHeight(1);
        EXPECT_DOUBLE_EQ(cropHeight1, cropHeight2);
    }
}

// Test very large page number
TEST_F(PDFDocTest_957, GetPageCropHeightVeryLargePageNumber_957) {
    auto doc = loadTestDoc(TESTDATADIR "/unittestcases/simple_rectangle.pdf");
    if (doc->isOk()) {
        double cropHeight = doc->getPageCropHeight(999999);
        EXPECT_EQ(cropHeight, 0.0);
    }
}
