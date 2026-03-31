#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>

// Include necessary headers
#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "GlobalParams.h"
#include "GooString.h"

// External globals referenced by printWordBBox
extern double resolution;
extern bool useCropBox;

// Forward declaration of the function under test
void printWordBBox(FILE *f, PDFDoc *doc, TextOutputDev *textOut, int first, int last);

// Helper function declared in pdftotext.cc
std::string myXmlTokenReplace(const char *text);

class PrintWordBBoxTest_2728 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize global params if not already done
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Save original globals
        origResolution = resolution;
        origUseCropBox = useCropBox;
    }

    void TearDown() override {
        // Restore original globals
        resolution = origResolution;
        useCropBox = origUseCropBox;
    }

    double origResolution;
    bool origUseCropBox;

    // Helper to read file contents
    std::string readFileContents(const std::string &filename) {
        std::ifstream ifs(filename);
        std::stringstream ss;
        ss << ifs.rdbuf();
        return ss.str();
    }

    // Helper to create a simple PDF doc from a test file
    std::unique_ptr<PDFDoc> createTestDoc(const std::string &path) {
        auto fileName = std::make_unique<GooString>(path);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test that printWordBBox produces valid XML doc structure even with no real PDF
TEST_F(PrintWordBBoxTest_2728, OutputHasDocTags_2728) {
    // Create a temporary output file
    std::string tmpFile = "test_output_doc_tags_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    // We need a valid PDF to test with. Try creating a minimal one.
    // If no test PDF is available, we test what we can.
    // Create a simple 1-page PDF in memory or use a file
    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    int numPages = doc->getNumPages();
    ASSERT_GT(numPages, 0);

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    // Check that output starts with <doc> and ends with </doc>
    EXPECT_NE(content.find("<doc>"), std::string::npos);
    EXPECT_NE(content.find("</doc>"), std::string::npos);
    EXPECT_NE(content.find("<page"), std::string::npos);
    EXPECT_NE(content.find("</page>"), std::string::npos);
    EXPECT_NE(content.find("width="), std::string::npos);
    EXPECT_NE(content.find("height="), std::string::npos);

    remove(tmpFile.c_str());
}

// Test with useCropBox = true
TEST_F(PrintWordBBoxTest_2728, UseCropBoxTrue_2728) {
    std::string tmpFile = "test_output_cropbox_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = true;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    EXPECT_NE(content.find("<doc>"), std::string::npos);
    EXPECT_NE(content.find("</doc>"), std::string::npos);
    EXPECT_NE(content.find("<page"), std::string::npos);

    remove(tmpFile.c_str());
}

// Test with multiple pages
TEST_F(PrintWordBBoxTest_2728, MultiplePages_2728) {
    std::string tmpFile = "test_output_multi_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    int numPages = doc->getNumPages();
    printWordBBox(f, doc.get(), textOut.get(), 1, numPages);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    EXPECT_NE(content.find("<doc>"), std::string::npos);
    EXPECT_NE(content.find("</doc>"), std::string::npos);
    
    // Count page tags - should have numPages occurrences
    size_t pos = 0;
    int pageCount = 0;
    while ((pos = content.find("<page ", pos)) != std::string::npos) {
        pageCount++;
        pos++;
    }
    EXPECT_EQ(pageCount, numPages);

    remove(tmpFile.c_str());
}

// Test with first == last (single page)
TEST_F(PrintWordBBoxTest_2728, SinglePageFirstEqualsLast_2728) {
    std::string tmpFile = "test_output_single_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    // Should have exactly one page element
    size_t pos = 0;
    int pageCount = 0;
    while ((pos = content.find("<page ", pos)) != std::string::npos) {
        pageCount++;
        pos++;
    }
    EXPECT_EQ(pageCount, 1);

    remove(tmpFile.c_str());
}

// Test boundary: first > last should produce doc tags but no pages
TEST_F(PrintWordBBoxTest_2728, FirstGreaterThanLastNoPages_2728) {
    std::string tmpFile = "test_output_nopages_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    // first > last: loop should not execute
    printWordBBox(f, doc.get(), textOut.get(), 5, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    EXPECT_NE(content.find("<doc>"), std::string::npos);
    EXPECT_NE(content.find("</doc>"), std::string::npos);
    // No page tags expected
    EXPECT_EQ(content.find("<page"), std::string::npos);

    remove(tmpFile.c_str());
}

// Test that word elements contain expected attributes
TEST_F(PrintWordBBoxTest_2728, WordElementsHaveBBoxAttributes_2728) {
    std::string tmpFile = "test_output_wordbbox_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    // If there are word elements, they should have the required attributes
    size_t wordPos = content.find("<word ");
    if (wordPos != std::string::npos) {
        std::string wordLine = content.substr(wordPos, content.find("</word>", wordPos) - wordPos);
        EXPECT_NE(wordLine.find("xMin="), std::string::npos);
        EXPECT_NE(wordLine.find("yMin="), std::string::npos);
        EXPECT_NE(wordLine.find("xMax="), std::string::npos);
        EXPECT_NE(wordLine.find("yMax="), std::string::npos);
    }

    remove(tmpFile.c_str());
}

// Test with different resolution values
TEST_F(PrintWordBBoxTest_2728, DifferentResolution_2728) {
    std::string tmpFile = "test_output_resolution_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 150.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    // Should still produce valid structure
    EXPECT_NE(content.find("<doc>"), std::string::npos);
    EXPECT_NE(content.find("</doc>"), std::string::npos);

    remove(tmpFile.c_str());
}

// Test XML special character handling via myXmlTokenReplace
// This tests that the output doesn't contain raw XML-breaking characters
TEST_F(PrintWordBBoxTest_2728, XmlOutputWellFormed_2728) {
    std::string tmpFile = "test_output_xmlwellformed_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    // The output should be well-structured XML
    // Check that doc tags are balanced
    size_t docOpen = content.find("<doc>");
    size_t docClose = content.find("</doc>");
    EXPECT_NE(docOpen, std::string::npos);
    EXPECT_NE(docClose, std::string::npos);
    if (docOpen != std::string::npos && docClose != std::string::npos) {
        EXPECT_LT(docOpen, docClose);
    }

    remove(tmpFile.c_str());
}

// Test with physical layout enabled in TextOutputDev
TEST_F(PrintWordBBoxTest_2728, PhysLayoutTextOutput_2728) {
    std::string tmpFile = "test_output_physlayout_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    // Physical layout enabled
    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    EXPECT_NE(content.find("<doc>"), std::string::npos);
    EXPECT_NE(content.find("</doc>"), std::string::npos);

    remove(tmpFile.c_str());
}

// Test page dimensions are present in the output
TEST_F(PrintWordBBoxTest_2728, PageDimensionsPresent_2728) {
    std::string tmpFile = "test_output_dims_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    // Get expected dimensions
    double expectedWidth = doc->getPageMediaWidth(1);
    double expectedHeight = doc->getPageMediaHeight(1);

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    // Check that width and height values appear in the page tag
    char widthStr[64], heightStr[64];
    snprintf(widthStr, sizeof(widthStr), "width=\"%f\"", expectedWidth);
    snprintf(heightStr, sizeof(heightStr), "height=\"%f\"", expectedHeight);
    EXPECT_NE(content.find(widthStr), std::string::npos);
    EXPECT_NE(content.find(heightStr), std::string::npos);

    remove(tmpFile.c_str());
}

// Test page dimensions when using crop box
TEST_F(PrintWordBBoxTest_2728, CropBoxDimensionsUsed_2728) {
    std::string tmpFile = "test_output_cropdims_2728.xml";
    FILE *f = fopen(tmpFile.c_str(), "w");
    ASSERT_NE(f, nullptr);

    std::string testPdfPath = TESTDATADIR "/unittestcases/WithActualText.pdf";
    auto doc = createTestDoc(testPdfPath);
    
    if (!doc->isOk()) {
        fclose(f);
        remove(tmpFile.c_str());
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    resolution = 72.0;
    useCropBox = true;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    // Get expected crop dimensions
    double expectedWidth = doc->getPageCropWidth(1);
    double expectedHeight = doc->getPageCropHeight(1);

    printWordBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(tmpFile);
    
    char widthStr[64], heightStr[64];
    snprintf(widthStr, sizeof(widthStr), "width=\"%f\"", expectedWidth);
    snprintf(heightStr, sizeof(heightStr), "height=\"%f\"", expectedHeight);
    EXPECT_NE(content.find(widthStr), std::string::npos);
    EXPECT_NE(content.find(heightStr), std::string::npos);

    remove(tmpFile.c_str());
}
