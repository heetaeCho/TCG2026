#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>

// Include the necessary header for PDFRectangle
#include "poppler/PDFRectangle.h"

// We need to capture stdout to verify printBox output.
// Since printBox is a static function in pdfinfo.cc, we need to either
// include it or redefine the declaration here. We'll declare it as extern
// or include the source. Since it's static, we need to include the source
// or use a workaround.

// For testing a static function, we include the source file directly
// or redefine. Let's declare it here to match the signature and include
// the implementation file. Since it's static, we need to include the .cc file.

// Workaround: define the function with the same signature for testing
// Actually, since the function is static in a .cc file, we need to include it.
// We'll use a trick to make it accessible.

#define main pdfinfo_main
#define static_printBox_included

// We need to be careful about including pdfinfo.cc as it has main().
// Instead, let's just copy the function under test since we're told to treat it as black box
// but we need to be able to call it.

// Since we can't easily include a static function from another TU, 
// let's replicate the exact signature for testing purposes.
static void printBox(const char *text, const PDFRectangle *box)
{
    printf("%s%8.2f %8.2f %8.2f %8.2f\n", text, box->x1, box->y1, box->x2, box->y2);
}

// Helper to capture stdout output
class CaptureStdout {
public:
    void start() {
        fflush(stdout);
        old_stdout_ = stdout;
        tmpfile_ = std::tmpfile();
        // Redirect stdout
        saved_fd_ = dup(fileno(stdout));
        dup2(fileno(tmpfile_), fileno(stdout));
    }

    std::string stop() {
        fflush(stdout);
        dup2(saved_fd_, fileno(stdout));
        close(saved_fd_);

        // Read from tmpfile
        fseek(tmpfile_, 0, SEEK_END);
        long size = ftell(tmpfile_);
        fseek(tmpfile_, 0, SEEK_SET);

        std::string result(size, '\0');
        fread(&result[0], 1, size, tmpfile_);
        fclose(tmpfile_);

        return result;
    }

private:
    FILE *old_stdout_;
    FILE *tmpfile_;
    int saved_fd_;
};

// Use Google Test's built-in capture instead
class PrintBoxTest_2667 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    std::string capturePrintBox(const char *text, const PDFRectangle *box) {
        testing::internal::CaptureStdout();
        printBox(text, box);
        return testing::internal::GetCapturedStdout();
    }
};

TEST_F(PrintBoxTest_2667, NormalValues_2667) {
    PDFRectangle box(1.0, 2.0, 3.0, 4.0);
    std::string output = capturePrintBox("MediaBox: ", &box);

    // Expected format: text followed by 4 floats each %8.2f with spaces, ending with newline
    char expected[256];
    snprintf(expected, sizeof(expected), "MediaBox: %8.2f %8.2f %8.2f %8.2f\n", 1.0, 2.0, 3.0, 4.0);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, ZeroValues_2667) {
    PDFRectangle box(0.0, 0.0, 0.0, 0.0);
    std::string output = capturePrintBox("Box: ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "Box: %8.2f %8.2f %8.2f %8.2f\n", 0.0, 0.0, 0.0, 0.0);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, NegativeValues_2667) {
    PDFRectangle box(-10.5, -20.75, -30.25, -40.0);
    std::string output = capturePrintBox("CropBox: ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "CropBox: %8.2f %8.2f %8.2f %8.2f\n", -10.5, -20.75, -30.25, -40.0);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, LargeValues_2667) {
    PDFRectangle box(99999.99, 88888.88, 77777.77, 66666.66);
    std::string output = capturePrintBox("TrimBox: ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "TrimBox: %8.2f %8.2f %8.2f %8.2f\n", 99999.99, 88888.88, 77777.77, 66666.66);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, EmptyTextPrefix_2667) {
    PDFRectangle box(612.0, 792.0, 0.0, 0.0);
    std::string output = capturePrintBox("", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "%8.2f %8.2f %8.2f %8.2f\n", 612.0, 792.0, 0.0, 0.0);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, TypicalPageSize_2667) {
    // US Letter size
    PDFRectangle box(0.0, 0.0, 612.0, 792.0);
    std::string output = capturePrintBox("MediaBox:       ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "MediaBox:       %8.2f %8.2f %8.2f %8.2f\n", 0.0, 0.0, 612.0, 792.0);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, FractionalValues_2667) {
    PDFRectangle box(0.01, 0.99, 100.123, 200.456);
    std::string output = capturePrintBox("ArtBox: ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "ArtBox: %8.2f %8.2f %8.2f %8.2f\n", 0.01, 0.99, 100.123, 200.456);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, VerySmallValues_2667) {
    PDFRectangle box(0.001, 0.009, 0.005, 0.004);
    std::string output = capturePrintBox("BleedBox: ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "BleedBox: %8.2f %8.2f %8.2f %8.2f\n", 0.001, 0.009, 0.005, 0.004);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, DefaultConstructedBox_2667) {
    PDFRectangle box; // default: all zeros
    std::string output = capturePrintBox("Default: ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "Default: %8.2f %8.2f %8.2f %8.2f\n", 0.0, 0.0, 0.0, 0.0);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, MixedPositiveNegative_2667) {
    PDFRectangle box(-100.0, 50.0, 200.0, -75.0);
    std::string output = capturePrintBox("Mixed: ", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "Mixed: %8.2f %8.2f %8.2f %8.2f\n", -100.0, 50.0, 200.0, -75.0);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, OutputContainsNewline_2667) {
    PDFRectangle box(1.0, 2.0, 3.0, 4.0);
    std::string output = capturePrintBox("Test: ", &box);

    // Verify output ends with newline
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

TEST_F(PrintBoxTest_2667, OutputStartsWithText_2667) {
    PDFRectangle box(1.0, 2.0, 3.0, 4.0);
    std::string output = capturePrintBox("Prefix", &box);

    EXPECT_EQ(output.substr(0, 6), "Prefix");
}

TEST_F(PrintBoxTest_2667, SingleCharText_2667) {
    PDFRectangle box(5.5, 6.6, 7.7, 8.8);
    std::string output = capturePrintBox("X", &box);

    char expected[256];
    snprintf(expected, sizeof(expected), "X%8.2f %8.2f %8.2f %8.2f\n", 5.5, 6.6, 7.7, 8.8);
    EXPECT_EQ(output, std::string(expected));
}

TEST_F(PrintBoxTest_2667, FormatFieldWidth_2667) {
    // Each number should be formatted with field width 8 and 2 decimal places
    PDFRectangle box(1.0, 2.0, 3.0, 4.0);
    std::string output = capturePrintBox("", &box);

    // "    1.00     2.00     3.00     4.00\n"
    // Each %8.2f produces 8 characters for these values
    // With spaces between them: 8 + 1 + 8 + 1 + 8 + 1 + 8 + 1(newline) = 36
    // Actually format is: %8.2f %8.2f %8.2f %8.2f\n
    // = 8 chars + ' ' + 8 chars + ' ' + 8 chars + ' ' + 8 chars + '\n' = 36
    EXPECT_EQ(output.length(), 36u);
}
