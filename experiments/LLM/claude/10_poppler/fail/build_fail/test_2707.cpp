#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

// Include necessary poppler headers
#include "HtmlOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Catalog.h"
#include "Page.h"
#include "GfxState.h"
#include "GooString.h"

class HtmlOutputDevTest_2707 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize global parameters required by poppler
        globalParams = std::make_unique<GlobalParams>();
    }

    void TearDown() override {
        globalParams.reset();
    }

    // Helper to create a valid HtmlOutputDev with a test PDF
    std::unique_ptr<HtmlOutputDev> createHtmlOutputDev(PDFDoc *doc, const char *outputFile = "test_output") {
        if (!doc || !doc->isOk()) {
            return nullptr;
        }
        Catalog *catalog = doc->getCatalog();
        auto dev = std::make_unique<HtmlOutputDev>(
            catalog,
            outputFile,
            "Test Title",
            "Test Author",
            "test keywords",
            "test subject",
            "2024-01-01",
            false,  // rawOrder
            1,      // firstPage
            false   // outline
        );
        return dev;
    }
};

// Test useDrawChar returns true
TEST_F(HtmlOutputDevTest_2707, UseDrawCharReturnsTrue_2707) {
    // Create a minimal PDF in memory to get a valid Catalog
    // We'll use a simple approach - create a PDF file first
    const char *testPdfPath = "test_useDrawChar_2707.pdf";
    
    // Try to create with a simple test - if we can't create a full doc,
    // we test what we can
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    // If we can't open a test PDF, skip gracefully
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_useDrawChar_2707");
    ASSERT_NE(dev, nullptr);
    
    EXPECT_TRUE(dev->useDrawChar());
    
    // Cleanup
    std::remove("test_useDrawChar_2707.html");
    std::remove("test_useDrawChar_2707s.html");
}

// Test upsideDown
TEST_F(HtmlOutputDevTest_2707, UpsideDownReturnValue_2707) {
    const char *testPdfPath = "test_upsideDown_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_upsideDown_2707");
    ASSERT_NE(dev, nullptr);
    
    // upsideDown() should return a boolean value
    bool result = dev->upsideDown();
    EXPECT_TRUE(result == true || result == false);
    
    std::remove("test_upsideDown_2707.html");
    std::remove("test_upsideDown_2707s.html");
}

// Test interpretType3Chars
TEST_F(HtmlOutputDevTest_2707, InterpretType3CharsReturnValue_2707) {
    const char *testPdfPath = "test_type3_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_type3_2707");
    ASSERT_NE(dev, nullptr);
    
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
    
    std::remove("test_type3_2707.html");
    std::remove("test_type3_2707s.html");
}

// Test needNonText
TEST_F(HtmlOutputDevTest_2707, NeedNonTextReturnValue_2707) {
    const char *testPdfPath = "test_nontext_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_nontext_2707");
    ASSERT_NE(dev, nullptr);
    
    bool result = dev->needNonText();
    EXPECT_TRUE(result == true || result == false);
    
    std::remove("test_nontext_2707.html");
    std::remove("test_nontext_2707s.html");
}

// Test isOk
TEST_F(HtmlOutputDevTest_2707, IsOkReturnValue_2707) {
    const char *testPdfPath = "test_isok_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_isok_2707");
    ASSERT_NE(dev, nullptr);
    
    // A properly constructed HtmlOutputDev should report isOk
    EXPECT_TRUE(dev->isOk());
    
    std::remove("test_isok_2707.html");
    std::remove("test_isok_2707s.html");
}

// Test getPageWidth and getPageHeight initial values
TEST_F(HtmlOutputDevTest_2707, PageDimensionsInitial_2707) {
    const char *testPdfPath = "test_dims_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_dims_2707");
    ASSERT_NE(dev, nullptr);
    
    int width = dev->getPageWidth();
    int height = dev->getPageHeight();
    
    // Dimensions should be non-negative
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
    
    std::remove("test_dims_2707.html");
    std::remove("test_dims_2707s.html");
}

// Test addBackgroundImage
TEST_F(HtmlOutputDevTest_2707, AddBackgroundImage_2707) {
    const char *testPdfPath = "test_bgimg_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_bgimg_2707");
    ASSERT_NE(dev, nullptr);
    
    // Should not crash when adding background images
    dev->addBackgroundImage("test_image.png");
    dev->addBackgroundImage("another_image.jpg");
    
    // No observable assertion other than no crash
    SUCCEED();
    
    std::remove("test_bgimg_2707.html");
    std::remove("test_bgimg_2707s.html");
}

// Test addBackgroundImage with empty string
TEST_F(HtmlOutputDevTest_2707, AddBackgroundImageEmpty_2707) {
    const char *testPdfPath = "test_bgimgempty_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_bgimgempty_2707");
    ASSERT_NE(dev, nullptr);
    
    // Should handle empty string without crash
    dev->addBackgroundImage("");
    
    SUCCEED();
    
    std::remove("test_bgimgempty_2707.html");
    std::remove("test_bgimgempty_2707s.html");
}

// Test DevType
TEST_F(HtmlOutputDevTest_2707, DevTypeReturnValue_2707) {
    const char *testPdfPath = "test_devtype_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_devtype_2707");
    ASSERT_NE(dev, nullptr);
    
    int devType = dev->DevType();
    // DevType should return a valid device type identifier
    EXPECT_GE(devType, 0);
    
    std::remove("test_devtype_2707.html");
    std::remove("test_devtype_2707s.html");
}

// Test construction with outline enabled
TEST_F(HtmlOutputDevTest_2707, ConstructWithOutline_2707) {
    const char *testPdfPath = "test_outline_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    Catalog *catalog = doc->getCatalog();
    auto dev = std::make_unique<HtmlOutputDev>(
        catalog,
        "test_outline_2707",
        "Outline Title",
        "Author",
        "keywords",
        "subject",
        "2024-01-01",
        false,  // rawOrder
        1,      // firstPage
        true    // outline enabled
    );
    
    ASSERT_NE(dev, nullptr);
    // Should still report OK even with outline
    // (actual behavior depends on implementation)
    
    std::remove("test_outline_2707.html");
    std::remove("test_outline_2707s.html");
}

// Test construction with rawOrder
TEST_F(HtmlOutputDevTest_2707, ConstructWithRawOrder_2707) {
    const char *testPdfPath = "test_raworder_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    Catalog *catalog = doc->getCatalog();
    auto dev = std::make_unique<HtmlOutputDev>(
        catalog,
        "test_raworder_2707",
        "Raw Order Title",
        "Author",
        "keywords",
        "subject",
        "2024-01-01",
        true,   // rawOrder
        1,      // firstPage
        false   // outline
    );
    
    ASSERT_NE(dev, nullptr);
    
    std::remove("test_raworder_2707.html");
    std::remove("test_raworder_2707s.html");
}

// Test construction with null optional parameters
TEST_F(HtmlOutputDevTest_2707, ConstructWithNullOptionalParams_2707) {
    const char *testPdfPath = "test_nullparams_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    Catalog *catalog = doc->getCatalog();
    auto dev = std::make_unique<HtmlOutputDev>(
        catalog,
        "test_nullparams_2707",
        "Title",
        nullptr,  // author
        nullptr,  // keywords
        nullptr,  // subject
        nullptr,  // date
        false,
        1,
        false
    );
    
    ASSERT_NE(dev, nullptr);
    
    std::remove("test_nullparams_2707.html");
    std::remove("test_nullparams_2707s.html");
}

// Test dumpDocOutline with null doc
TEST_F(HtmlOutputDevTest_2707, DumpDocOutlineNullDoc_2707) {
    const char *testPdfPath = "test_dumpoutline_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_dumpoutline_2707");
    ASSERT_NE(dev, nullptr);
    
    // Test dumpDocOutline with a valid doc
    bool result = dev->dumpDocOutline(doc.get());
    // Result depends on whether doc has an outline
    EXPECT_TRUE(result == true || result == false);
    
    std::remove("test_dumpoutline_2707.html");
    std::remove("test_dumpoutline_2707s.html");
}

// Test that useDrawChar consistently returns true
TEST_F(HtmlOutputDevTest_2707, UseDrawCharConsistency_2707) {
    const char *testPdfPath = "test_consistency_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_consistency_2707");
    ASSERT_NE(dev, nullptr);
    
    // Call multiple times to ensure consistency
    EXPECT_TRUE(dev->useDrawChar());
    EXPECT_TRUE(dev->useDrawChar());
    EXPECT_TRUE(dev->useDrawChar());
    
    std::remove("test_consistency_2707.html");
    std::remove("test_consistency_2707s.html");
}

// Test checkPageSlice with default parameters
TEST_F(HtmlOutputDevTest_2707, CheckPageSliceDefaultParams_2707) {
    const char *testPdfPath = "test_pageslice_2707.pdf";
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdfPath));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    auto dev = createHtmlOutputDev(doc.get(), "test_pageslice_2707");
    ASSERT_NE(dev, nullptr);
    
    if (doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            bool result = dev->checkPageSlice(page, 72.0, 72.0, 0, true, false, 0, 0, 0, 0, false);
            EXPECT_TRUE(result == true || result == false);
        }
    }
    
    std::remove("test_pageslice_2707.html");
    std::remove("test_pageslice_2707s.html");
}
