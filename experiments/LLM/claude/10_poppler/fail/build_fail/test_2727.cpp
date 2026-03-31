#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <sstream>
#include <vector>

#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "GooString.h"
#include "GlobalParams.h"

// External globals used by printTSVBBox
extern double resolution;
extern bool useCropBox;

// Declaration of the function under test
void printTSVBBox(FILE *f, PDFDoc *doc, TextOutputDev *textOut, int first, int last);

namespace {

// Helper to read entire file content into a string
std::string readFileContent(const std::string &path) {
    FILE *f = fopen(path.c_str(), "r");
    if (!f) return "";
    std::string content;
    char buf[4096];
    while (size_t n = fread(buf, 1, sizeof(buf), f)) {
        content.append(buf, n);
    }
    fclose(f);
    return content;
}

// Helper to count lines in a string
int countLines(const std::string &s) {
    int count = 0;
    for (char c : s) {
        if (c == '\n') count++;
    }
    return count;
}

// Helper to get a specific line from content
std::string getLine(const std::string &content, int lineNum) {
    std::istringstream iss(content);
    std::string line;
    for (int i = 0; i <= lineNum; i++) {
        if (!std::getline(iss, line)) return "";
    }
    return line;
}

class PrintTSVBBoxTest_2727 : public ::testing::Test {
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
        // Restore globals
        resolution = origResolution;
        useCropBox = origUseCropBox;
    }

    double origResolution;
    bool origUseCropBox;

    // Helper to create a temporary file path
    std::string getTempFilePath() {
        char tmpPath[] = "/tmp/tsv_test_XXXXXX";
        int fd = mkstemp(tmpPath);
        if (fd >= 0) close(fd);
        return std::string(tmpPath);
    }
};

// Test that the header line is always output correctly
TEST_F(PrintTSVBBoxTest_2727, HeaderLineIsCorrect_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    // Load a simple PDF for testing
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    // Use page range where first > last so no pages are processed, only header
    printTSVBBox(f, doc.get(), textOut.get(), 2, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    // Check header
    std::string header = getLine(content, 0);
    EXPECT_EQ(header, "level\tpage_num\tpar_num\tblock_num\tline_num\tword_num\tleft\ttop\twidth\theight\tconf\ttext");
}

// Test that when first > last, only header is output (no page data)
TEST_F(PrintTSVBBoxTest_2727, NoPageDataWhenFirstGreaterThanLast_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 5, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    // Should only have the header line
    EXPECT_EQ(countLines(content), 1);
}

// Test that a single page produces at least the header and a PAGE line
TEST_F(PrintTSVBBoxTest_2727, SinglePageProducesPageLine_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    // Should have at least 2 lines: header + page line
    EXPECT_GE(countLines(content), 2);

    // Check the page line contains ###PAGE###
    std::string pageLine = getLine(content, 1);
    EXPECT_NE(pageLine.find("###PAGE###"), std::string::npos);

    // Page level should be 1
    EXPECT_EQ(pageLine.substr(0, 1), "1");
}

// Test that page line has correct page number
TEST_F(PrintTSVBBoxTest_2727, PageLineContainsCorrectPageNumber_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    // Page line: level=1, page_num=1
    std::string pageLine = getLine(content, 1);
    // Parse first two tab-separated fields
    std::istringstream iss(pageLine);
    std::string level, pageNum;
    std::getline(iss, level, '\t');
    std::getline(iss, pageNum, '\t');
    EXPECT_EQ(level, "1");
    EXPECT_EQ(pageNum, "1");
}

// Test that the page line uses media box dimensions when useCropBox is false
TEST_F(PrintTSVBBoxTest_2727, PageLineUsesMediaBoxWhenNotCropBox_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    double expectedWidth = doc->getPageMediaWidth(1);
    double expectedHeight = doc->getPageMediaHeight(1);

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::string pageLine = getLine(content, 1);
    // The width and height are in columns 8 and 9 (0-indexed: fields 8,9)
    std::istringstream iss(pageLine);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(iss, field, '\t')) {
        fields.push_back(field);
    }
    ASSERT_GE(fields.size(), 10u);

    double width = std::stod(fields[8]);
    double height = std::stod(fields[9]);
    EXPECT_NEAR(width, expectedWidth, 0.01);
    EXPECT_NEAR(height, expectedHeight, 0.01);
}

// Test that the page line uses crop box dimensions when useCropBox is true
TEST_F(PrintTSVBBoxTest_2727, PageLineUsesCropBoxWhenCropBoxSet_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = true;

    double expectedWidth = doc->getPageCropWidth(1);
    double expectedHeight = doc->getPageCropHeight(1);

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::string pageLine = getLine(content, 1);
    std::istringstream iss(pageLine);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(iss, field, '\t')) {
        fields.push_back(field);
    }
    ASSERT_GE(fields.size(), 10u);

    double width = std::stod(fields[8]);
    double height = std::stod(fields[9]);
    EXPECT_NEAR(width, expectedWidth, 0.01);
    EXPECT_NEAR(height, expectedHeight, 0.01);
}

// Test that the page line has conf=-1
TEST_F(PrintTSVBBoxTest_2727, PageLineHasMetaConfMinusOne_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::string pageLine = getLine(content, 1);
    std::istringstream iss(pageLine);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(iss, field, '\t')) {
        fields.push_back(field);
    }
    ASSERT_GE(fields.size(), 12u);
    EXPECT_EQ(fields[10], "-1");
}

// Test that FLOW lines have level 3
TEST_F(PrintTSVBBoxTest_2727, FlowLinesHaveLevelThree_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::istringstream iss(content);
    std::string line;
    bool foundFlow = false;
    while (std::getline(iss, line)) {
        if (line.find("###FLOW###") != std::string::npos) {
            foundFlow = true;
            EXPECT_EQ(line.substr(0, 1), "3");
        }
    }
    // It's okay if no flows are found (empty page), but if found, they must be level 3
    if (!foundFlow) {
        GTEST_SKIP() << "No flow blocks found in test PDF";
    }
}

// Test that LINE lines have level 4
TEST_F(PrintTSVBBoxTest_2727, LineLinesHaveLevelFour_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::istringstream iss(content);
    std::string line;
    bool foundLine = false;
    while (std::getline(iss, line)) {
        if (line.find("###LINE###") != std::string::npos) {
            foundLine = true;
            EXPECT_EQ(line.substr(0, 1), "4");
        }
    }
    if (!foundLine) {
        GTEST_SKIP() << "No text lines found in test PDF";
    }
}

// Test that word lines have level 5
TEST_F(PrintTSVBBoxTest_2727, WordLinesHaveLevelFive_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::istringstream iss(content);
    std::string line;
    bool foundWord = false;
    while (std::getline(iss, line)) {
        if (line.empty() || line[0] == 'l') continue; // skip header
        if (line.find("###") != std::string::npos) continue; // skip meta lines

        // Remaining lines should be word lines
        std::istringstream lineIss(line);
        std::string level;
        std::getline(lineIss, level, '\t');
        if (level == "5") {
            foundWord = true;
            // Word conf should be 100
            std::vector<std::string> fields;
            std::istringstream fieldIss(line);
            std::string field;
            while (std::getline(fieldIss, field, '\t')) {
                fields.push_back(field);
            }
            if (fields.size() >= 11) {
                EXPECT_EQ(fields[10], "100");
            }
        }
    }
    if (!foundWord) {
        GTEST_SKIP() << "No words found in test PDF";
    }
}

// Test output contains proper TSV structure (tab-separated with 12 fields)
TEST_F(PrintTSVBBoxTest_2727, OutputHasProperTSVStructure_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::istringstream iss(content);
    std::string line;
    int lineNum = 0;
    while (std::getline(iss, line)) {
        if (line.empty()) continue;
        // Count tabs: should have 11 tabs (12 fields)
        int tabCount = 0;
        for (char c : line) {
            if (c == '\t') tabCount++;
        }
        EXPECT_EQ(tabCount, 11) << "Line " << lineNum << " has wrong number of fields: " << line;
        lineNum++;
    }
    EXPECT_GT(lineNum, 0);
}

// Test that page left and top are 0.0 in the PAGE line
TEST_F(PrintTSVBBoxTest_2727, PageLineLeftAndTopAreZero_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::string pageLine = getLine(content, 1);
    std::istringstream iss(pageLine);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(iss, field, '\t')) {
        fields.push_back(field);
    }
    ASSERT_GE(fields.size(), 8u);
    EXPECT_DOUBLE_EQ(std::stod(fields[6]), 0.0); // left
    EXPECT_DOUBLE_EQ(std::stod(fields[7]), 0.0); // top
}

// Test page line zeroed par_num, block_num, line_num, word_num
TEST_F(PrintTSVBBoxTest_2727, PageLineHasZeroedCounts_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::string pageLine = getLine(content, 1);
    std::istringstream iss(pageLine);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(iss, field, '\t')) {
        fields.push_back(field);
    }
    ASSERT_GE(fields.size(), 6u);
    EXPECT_EQ(fields[2], "0"); // par_num
    EXPECT_EQ(fields[3], "0"); // block_num
    EXPECT_EQ(fields[4], "0"); // line_num
    EXPECT_EQ(fields[5], "0"); // word_num
}

// Test ordering: PAGE comes before FLOW, FLOW before LINE, LINE before words
TEST_F(PrintTSVBBoxTest_2727, CorrectHierarchicalOrdering_2727) {
    std::string tmpPath = getTempFilePath();
    FILE *f = fopen(tmpPath.c_str(), "w");
    ASSERT_NE(f, nullptr);

    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());

    if (!doc->isOk()) {
        fclose(f);
        unlink(tmpPath.c_str());
        GTEST_SKIP() << "Test PDF not available";
    }

    resolution = 72.0;
    useCropBox = false;

    auto textOut = std::make_unique<TextOutputDev>(nullptr, true, 0, false, false, false);
    ASSERT_TRUE(textOut->isOk());

    printTSVBBox(f, doc.get(), textOut.get(), 1, 1);
    fclose(f);

    std::string content = readFileContent(tmpPath);
    unlink(tmpPath.c_str());

    std::istringstream iss(content);
    std::string line;
    bool seenPage = false;
    bool seenFlow = false;
    bool seenLine = false;
    bool seenWord = false;

    // Skip header
    std::getline(iss, line);

    while (std::getline(iss, line)) {
        if (line.find("###PAGE###") != std::string::npos) {
            seenPage = true;
        } else if (line.find("###FLOW###") != std::string::npos) {
            EXPECT_TRUE(seenPage) << "FLOW before PAGE";
            seenFlow = true;
        } else if (line.find("###LINE###") != std::string::npos) {
            EXPECT_TRUE(seenFlow) << "LINE before FLOW";
            seenLine = true;
        } else if (!line.empty() && line[0] == '5') {
            // Word line - but note words come right after their LINE marker
            seenWord = true;
        }
    }

    EXPECT_TRUE(seenPage);
}

} // namespace
