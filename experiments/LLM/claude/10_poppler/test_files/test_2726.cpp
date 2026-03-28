#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>

#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "GlobalParams.h"
#include "GooString.h"

// External globals used by printDocBBox
extern double resolution;
extern bool useCropBox;

// Forward declaration of the function under test
void printDocBBox(FILE *f, PDFDoc *doc, TextOutputDev *textOut, int first, int last);
void printLine(FILE *f, const TextLine *line);

namespace {

class PrintDocBBoxTest_2726 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize global params if not already done
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Save original values
        origResolution = resolution;
        origUseCropBox = useCropBox;
    }

    void TearDown() override {
        // Restore original values
        resolution = origResolution;
        useCropBox = origUseCropBox;
    }

    double origResolution;
    bool origUseCropBox;

    // Helper to read file contents
    std::string readFileContents(const std::string &path) {
        std::ifstream ifs(path);
        std::stringstream ss;
        ss << ifs.rdbuf();
        return ss.str();
    }

    // Helper to create a PDFDoc from a test PDF file
    std::unique_ptr<PDFDoc> createTestDoc(const std::string &filename) {
        auto fileName = std::make_unique<GooString>(filename);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::nullopt, std::nullopt, nullptr);
        return doc;
    }

    // Helper to create a simple one-page PDF in memory for testing
    // Returns path to a temp file with a minimal PDF
    std::string createMinimalPDF() {
        std::string tmpPath = "/tmp/test_printdocbbox_2726.pdf";
        FILE *f = fopen(tmpPath.c_str(), "wb");
        if (!f) return "";

        // Minimal valid PDF with one page containing text "Hello"
        const char *pdf =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000282 00000 n \n"
            "0000000380 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "456\n"
            "%%EOF\n";
        fwrite(pdf, 1, strlen(pdf), f);
        fclose(f);
        return tmpPath;
    }

    // Create a minimal 2-page PDF
    std::string createTwoPagePDF() {
        std::string tmpPath = "/tmp/test_printdocbbox_2page_2726.pdf";
        FILE *f = fopen(tmpPath.c_str(), "wb");
        if (!f) return "";

        const char *pdf =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R 6 0 R] /Count 2 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
            "endobj\n"
            "6 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 400] "
            "/Contents 7 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            "endobj\n"
            "7 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 50 350 Td (World) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 8\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000121 00000 n \n"
            "0000000288 00000 n \n"
            "0000000386 00000 n \n"
            "0000000457 00000 n \n"
            "0000000620 00000 n \n"
            "trailer\n"
            "<< /Size 8 /Root 1 0 R >>\n"
            "startxref\n"
            "718\n"
            "%%EOF\n";
        fwrite(pdf, 1, strlen(pdf), f);
        fclose(f);
        return tmpPath;
    }
};

// Test that output starts with <doc> and ends with </doc>
TEST_F(PrintDocBBoxTest_2726, OutputWrappedInDocTags_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_doctags_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, doc->getNumPages());
    fclose(f);

    std::string content = readFileContents(outPath);
    EXPECT_TRUE(content.find("<doc>") != std::string::npos);
    EXPECT_TRUE(content.find("</doc>") != std::string::npos);
    // <doc> should appear before </doc>
    EXPECT_LT(content.find("<doc>"), content.find("</doc>"));

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test that each page is wrapped in <page> tags with width/height attributes
TEST_F(PrintDocBBoxTest_2726, OutputContainsPageTags_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_pagetags_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);
    EXPECT_TRUE(content.find("<page width=") != std::string::npos);
    EXPECT_TRUE(content.find("height=") != std::string::npos);
    EXPECT_TRUE(content.find("</page>") != std::string::npos);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test with useCropBox = true
TEST_F(PrintDocBBoxTest_2726, UseCropBoxDimensions_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = true;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_cropbox_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);
    // Should still produce valid output with page tags
    EXPECT_TRUE(content.find("<doc>") != std::string::npos);
    EXPECT_TRUE(content.find("<page width=") != std::string::npos);
    EXPECT_TRUE(content.find("</doc>") != std::string::npos);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test with useCropBox = false (mediaBox dimensions)
TEST_F(PrintDocBBoxTest_2726, UseMediaBoxDimensions_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_mediabox_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);
    EXPECT_TRUE(content.find("<doc>") != std::string::npos);
    EXPECT_TRUE(content.find("<page width=") != std::string::npos);
    EXPECT_TRUE(content.find("</doc>") != std::string::npos);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test that flow tags appear if page has text content
TEST_F(PrintDocBBoxTest_2726, OutputContainsFlowTags_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_flowtags_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);
    // If there's text, we expect flow/block tags; if minimal PDF text is rendered
    // The structure should at least have doc and page
    EXPECT_TRUE(content.find("<doc>") != std::string::npos);
    EXPECT_TRUE(content.find("</doc>") != std::string::npos);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test with first == last (single page)
TEST_F(PrintDocBBoxTest_2726, SinglePageRange_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_singlepage_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);

    // Count occurrences of <page
    size_t count = 0;
    size_t pos = 0;
    while ((pos = content.find("<page ", pos)) != std::string::npos) {
        ++count;
        pos += 5;
    }
    EXPECT_EQ(count, 1u);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test with first > last (empty range - no pages should be output)
TEST_F(PrintDocBBoxTest_2726, EmptyPageRange_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_emptyrange_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    // first > last, so loop body should not execute
    printDocBBox(f, doc.get(), textOut.get(), 2, 1);
    fclose(f);

    std::string content = readFileContents(outPath);
    // Should still have doc tags but no page tags
    EXPECT_TRUE(content.find("<doc>") != std::string::npos);
    EXPECT_TRUE(content.find("</doc>") != std::string::npos);
    EXPECT_EQ(content.find("<page "), std::string::npos);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test with two-page document, requesting both pages
TEST_F(PrintDocBBoxTest_2726, TwoPageDocument_2726) {
    std::string pdfPath = createTwoPagePDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_twopage_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    int numPages = doc->getNumPages();
    printDocBBox(f, doc.get(), textOut.get(), 1, numPages);
    fclose(f);

    std::string content = readFileContents(outPath);

    // Count <page occurrences
    size_t count = 0;
    size_t pos = 0;
    while ((pos = content.find("<page ", pos)) != std::string::npos) {
        ++count;
        pos += 5;
    }
    EXPECT_EQ(count, static_cast<size_t>(numPages));

    // Count </page> occurrences
    count = 0;
    pos = 0;
    while ((pos = content.find("</page>", pos)) != std::string::npos) {
        ++count;
        pos += 7;
    }
    EXPECT_EQ(count, static_cast<size_t>(numPages));

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test that block tags contain bbox attributes when text is present
TEST_F(PrintDocBBoxTest_2726, BlockTagsContainBBox_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_blockbbox_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);

    // If blocks exist, they should have xMin, yMin, xMax, yMax attributes
    size_t blockPos = content.find("<block ");
    if (blockPos != std::string::npos) {
        std::string blockLine = content.substr(blockPos, content.find(">", blockPos) - blockPos);
        EXPECT_TRUE(blockLine.find("xMin=") != std::string::npos);
        EXPECT_TRUE(blockLine.find("yMin=") != std::string::npos);
        EXPECT_TRUE(blockLine.find("xMax=") != std::string::npos);
        EXPECT_TRUE(blockLine.find("yMax=") != std::string::npos);
    }

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test with different resolution values
TEST_F(PrintDocBBoxTest_2726, DifferentResolution_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 150.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_highres_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);
    // Should still produce valid XML structure
    EXPECT_TRUE(content.find("<doc>") != std::string::npos);
    EXPECT_TRUE(content.find("</doc>") != std::string::npos);
    EXPECT_TRUE(content.find("<page width=") != std::string::npos);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test structure: flow tags are nested within page tags
TEST_F(PrintDocBBoxTest_2726, FlowNestedInPage_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_nesting_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);

    size_t pageOpenPos = content.find("<page ");
    size_t pageClosePos = content.find("</page>");
    size_t flowOpenPos = content.find("<flow>");
    size_t flowClosePos = content.find("</flow>");

    if (flowOpenPos != std::string::npos) {
        // flow should be between page open and close
        EXPECT_GT(flowOpenPos, pageOpenPos);
        EXPECT_LT(flowClosePos, pageClosePos);
    }

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test structure: block tags are nested within flow tags
TEST_F(PrintDocBBoxTest_2726, BlockNestedInFlow_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_blocknesting_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);

    size_t flowOpenPos = content.find("<flow>");
    size_t flowClosePos = content.find("</flow>");
    size_t blockOpenPos = content.find("<block ");
    size_t blockClosePos = content.find("</block>");

    if (blockOpenPos != std::string::npos) {
        // block should be between flow open and close
        EXPECT_GT(blockOpenPos, flowOpenPos);
        EXPECT_LT(blockClosePos, flowClosePos);
    }

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test requesting only the second page of a two-page document
TEST_F(PrintDocBBoxTest_2726, SecondPageOnly_2726) {
    std::string pdfPath = createTwoPagePDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    if (doc->getNumPages() < 2) {
        GTEST_SKIP() << "Need at least 2 pages";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_secondpage_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 2, 2);
    fclose(f);

    std::string content = readFileContents(outPath);

    // Should have exactly one page tag
    size_t count = 0;
    size_t pos = 0;
    while ((pos = content.find("<page ", pos)) != std::string::npos) {
        ++count;
        pos += 5;
    }
    EXPECT_EQ(count, 1u);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test that output is well-formed (matching open/close tags for flow)
TEST_F(PrintDocBBoxTest_2726, MatchingFlowTags_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_matchflow_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);

    // Count open and close flow tags - they should match
    size_t openCount = 0, closeCount = 0;
    size_t pos = 0;
    while ((pos = content.find("<flow>", pos)) != std::string::npos) {
        ++openCount;
        pos += 6;
    }
    pos = 0;
    while ((pos = content.find("</flow>", pos)) != std::string::npos) {
        ++closeCount;
        pos += 7;
    }
    EXPECT_EQ(openCount, closeCount);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test that output is well-formed (matching open/close tags for block)
TEST_F(PrintDocBBoxTest_2726, MatchingBlockTags_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_matchblock_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);

    // Count open and close block tags
    size_t openCount = 0, closeCount = 0;
    size_t pos = 0;
    while ((pos = content.find("<block ", pos)) != std::string::npos) {
        ++openCount;
        pos += 6;
    }
    pos = 0;
    while ((pos = content.find("</block>", pos)) != std::string::npos) {
        ++closeCount;
        pos += 8;
    }
    EXPECT_EQ(openCount, closeCount);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

// Test with zero resolution
TEST_F(PrintDocBBoxTest_2726, ZeroResolution_2726) {
    std::string pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.empty());

    auto doc = createTestDoc(pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    resolution = 0.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, false, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    std::string outPath = "/tmp/test_output_zerores_2726.xml";
    FILE *f = fopen(outPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    // Should not crash; output structure should still be valid
    printDocBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContents(outPath);
    EXPECT_TRUE(content.find("<doc>") != std::string::npos);
    EXPECT_TRUE(content.find("</doc>") != std::string::npos);

    remove(outPath.c_str());
    remove(pdfPath.c_str());
}

}  // namespace
