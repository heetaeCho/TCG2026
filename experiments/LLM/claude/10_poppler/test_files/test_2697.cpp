#include <gtest/gtest.h>
#include <memory>
#include <cstdlib>
#include <cstring>

// Include the GooString header
#include "goo/GooString.h"

// Declare the external global variables used by getOutputFileName
extern bool ps;
extern bool eps;
extern bool pdf;
extern bool printToWin32;
extern bool svg;
extern bool printing;
extern bool singleFile;

// Declare the function under test
static std::unique_ptr<GooString> getOutputFileName(GooString *fileName, GooString *outputName);

// We need to include the actual implementation
#include "utils/pdftocairo.cc"

class GetOutputFileNameTest_2697 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset all global flags to default (false) before each test
        ps = false;
        eps = false;
        pdf = false;
        printToWin32 = false;
        svg = false;
        printing = false;
        singleFile = false;
    }

    void TearDown() override {
        // Reset globals after each test
        ps = false;
        eps = false;
        pdf = false;
        printToWin32 = false;
        svg = false;
        printing = false;
        singleFile = false;
    }
};

// Test: When outputName is provided (non-dash), it should return a copy of outputName
TEST_F(GetOutputFileNameTest_2697, OutputNameProvided_ReturnsCopy_2697) {
    GooString fileName("input.pdf");
    GooString outputName("myoutput");
    auto result = getOutputFileName(&fileName, &outputName);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "myoutput");
}

// Test: When outputName is "-" and singleFile is true, return "fd://0"
TEST_F(GetOutputFileNameTest_2697, OutputNameDashSingleFile_ReturnsFd_2697) {
    singleFile = true;
    GooString fileName("input.pdf");
    GooString outputName("-");
    auto result = getOutputFileName(&fileName, &outputName);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "fd://0");
}

// Test: When outputName is "-" and printing is true (ps mode), return "fd://0"
TEST_F(GetOutputFileNameTest_2697, OutputNameDashPrinting_ReturnsFd_2697) {
    printing = true;
    ps = true;
    GooString fileName("input.pdf");
    GooString outputName("-");
    auto result = getOutputFileName(&fileName, &outputName);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "fd://0");
}

// Test: When outputName is "-" and not printing, not singleFile, not printToWin32 -> exit(99)
TEST_F(GetOutputFileNameTest_2697, OutputNameDashNoSingleFileNoPrinting_ExitsWithError_2697) {
    singleFile = false;
    printing = false;
    printToWin32 = false;
    GooString fileName("input.pdf");
    GooString outputName("-");
    EXPECT_EXIT(getOutputFileName(&fileName, &outputName), ::testing::ExitedWithCode(99), "");
}

// Test: When printToWin32 is true and no outputName, return nullptr
TEST_F(GetOutputFileNameTest_2697, PrintToWin32NoOutputName_ReturnsNull_2697) {
    printToWin32 = true;
    GooString fileName("input.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test: When fileName is "fd://0" and no outputName -> exit(99)
TEST_F(GetOutputFileNameTest_2697, StdinFileNameNoOutputName_ExitsWithError_2697) {
    GooString fileName("fd://0");
    EXPECT_EXIT(getOutputFileName(&fileName, nullptr), ::testing::ExitedWithCode(99), "");
}

// Test: When pdf mode and local fileName without outputName -> exit(99)
TEST_F(GetOutputFileNameTest_2697, PdfModeLocalFileNoOutputName_ExitsWithError_2697) {
    pdf = true;
    GooString fileName("input.pdf");
    EXPECT_EXIT(getOutputFileName(&fileName, nullptr), ::testing::ExitedWithCode(99), "");
}

// Test: When pdf mode and http fileName without outputName -> uses basename logic
TEST_F(GetOutputFileNameTest_2697, PdfModeHttpFileNoOutputName_UsesBasename_2697) {
    pdf = true;
    GooString fileName("http://example.com/document.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document.pdf");
}

// Test: When pdf mode and https fileName without outputName -> uses basename logic
TEST_F(GetOutputFileNameTest_2697, PdfModeHttpsFileNoOutputName_UsesBasename_2697) {
    pdf = true;
    GooString fileName("https://example.com/document.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document.pdf");
}

// Test: Simple filename with .pdf extension, no output format set -> strips .pdf
TEST_F(GetOutputFileNameTest_2697, SimpleFileNameStripsPdfExtension_2697) {
    GooString fileName("document.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document");
}

// Test: Simple filename with .PDF extension (case insensitive) -> strips .PDF
TEST_F(GetOutputFileNameTest_2697, SimpleFileNameStripsPdfExtensionCaseInsensitive_2697) {
    GooString fileName("document.PDF");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document");
}

// Test: Filename with path, strips directory and .pdf, appends .ps when ps=true
TEST_F(GetOutputFileNameTest_2697, FileNameWithPathPsMode_2697) {
    ps = true;
    GooString fileName("/path/to/document.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document.ps");
}

// Test: eps mode appends .eps
TEST_F(GetOutputFileNameTest_2697, EpsMode_AppendsEpsExtension_2697) {
    eps = true;
    GooString fileName("document.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document.eps");
}

// Test: svg mode appends .svg
TEST_F(GetOutputFileNameTest_2697, SvgMode_AppendsSvgExtension_2697) {
    svg = true;
    GooString fileName("document.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document.svg");
}

// Test: Filename without .pdf extension, no format set
TEST_F(GetOutputFileNameTest_2697, FileNameWithoutPdfExtension_2697) {
    GooString fileName("document.txt");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "document.txt");
}

// Test: Filename ending with slash -> exit(99)
TEST_F(GetOutputFileNameTest_2697, FileNameEndingWithSlash_ExitsWithError_2697) {
    GooString fileName("/path/to/");
    EXPECT_EXIT(getOutputFileName(&fileName, nullptr), ::testing::ExitedWithCode(99), "");
}

// Test: Filename with no directory separator
TEST_F(GetOutputFileNameTest_2697, FileNameNoDirectory_2697) {
    GooString fileName("simple.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "simple");
}

// Test: Filename with multiple dots, only last .pdf is stripped
TEST_F(GetOutputFileNameTest_2697, FileNameMultipleDots_2697) {
    GooString fileName("my.document.name.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "my.document.name");
}

// Test: outputName "-" with printToWin32 -> exit(99) (printToWin32 && not printing && not singleFile)
TEST_F(GetOutputFileNameTest_2697, OutputNameDashPrintToWin32_ExitsWithError_2697) {
    printToWin32 = true;
    printing = false;
    singleFile = false;
    GooString fileName("input.pdf");
    GooString outputName("-");
    EXPECT_EXIT(getOutputFileName(&fileName, &outputName), ::testing::ExitedWithCode(99), "");
}

// Test: Filename with path and non-pdf extension in ps mode
TEST_F(GetOutputFileNameTest_2697, FileNameWithPathNonPdfExtPsMode_2697) {
    ps = true;
    GooString fileName("/some/path/file.doc");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "file.doc.ps");
}

// Test: Filename that is just the name "test" with no extension
TEST_F(GetOutputFileNameTest_2697, FileNameNoExtension_2697) {
    svg = true;
    GooString fileName("test");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "test.svg");
}

// Test: pdf mode with https URL, .pdf extension stripped, .pdf appended
TEST_F(GetOutputFileNameTest_2697, PdfModeHttpsUrl_StripAndAppendPdf_2697) {
    pdf = true;
    GooString fileName("https://example.com/doc.pdf");
    auto result = getOutputFileName(&fileName, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "doc.pdf");
}
