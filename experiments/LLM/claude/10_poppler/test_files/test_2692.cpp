#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>

// Include necessary headers
#include "goo/GooString.h"

// External global variables declared in pdftocairo.cc
extern bool ps;
extern bool eps;
extern bool pdf;
extern bool printToWin32;
extern bool svg;
extern bool printing;
extern FILE *output_file;
extern cairo_surface_t *surface;
extern bool level2;
extern bool duplex;

// Declaration of the function under test
void beginDocument(GooString *inputFileName, GooString *outputFileName, double w, double h);

class BeginDocumentTest_2692 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset all global state to defaults
        ps = false;
        eps = false;
        pdf = false;
        printToWin32 = false;
        svg = false;
        printing = false;
        output_file = nullptr;
        surface = nullptr;
        level2 = false;
        duplex = false;
    }

    void TearDown() override {
        // Clean up any surfaces created
        if (surface) {
            cairo_surface_destroy(surface);
            surface = nullptr;
        }
        // Close output file if it was opened (and not stdout)
        if (output_file && output_file != stdout) {
            fclose(output_file);
            output_file = nullptr;
        }
        // Remove any temp files
        std::remove(temp_output_.c_str());
    }

    std::string temp_output_ = "test_output_2692.tmp";
};

// Test: When printing is false, beginDocument should do nothing
TEST_F(BeginDocumentTest_2692, NotPrintingDoesNothing_2692) {
    printing = false;
    GooString inputName("input.pdf");
    GooString outputName("output.pdf");

    beginDocument(&inputName, &outputName, 100.0, 200.0);

    EXPECT_EQ(output_file, nullptr);
    EXPECT_EQ(surface, nullptr);
}

// Test: When printing is true and output is fd://0 (stdout), output_file should be stdout
TEST_F(BeginDocumentTest_2692, PrintingToStdout_2692) {
    printing = true;
    pdf = true;
    GooString inputName("input.pdf");
    GooString outputName("fd://0");

    beginDocument(&inputName, &outputName, 100.0, 200.0);

    EXPECT_EQ(output_file, stdout);
    EXPECT_NE(surface, nullptr);
}

// Test: When printing and pdf, surface is created for a file output
TEST_F(BeginDocumentTest_2692, PrintingPdfToFile_2692) {
    printing = true;
    pdf = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 200.0, 300.0);

    EXPECT_NE(output_file, nullptr);
    EXPECT_NE(output_file, stdout);
    EXPECT_NE(surface, nullptr);
}

#ifdef CAIRO_HAS_PS_SURFACE
// Test: When printing and ps, PS surface is created
TEST_F(BeginDocumentTest_2692, PrintingPsToFile_2692) {
    printing = true;
    ps = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 200.0, 300.0);

    EXPECT_NE(output_file, nullptr);
    EXPECT_NE(surface, nullptr);
}

// Test: When printing, eps mode, EPS surface is created
TEST_F(BeginDocumentTest_2692, PrintingEpsToFile_2692) {
    printing = true;
    eps = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 150.0, 250.0);

    EXPECT_NE(output_file, nullptr);
    EXPECT_NE(surface, nullptr);
}

// Test: When printing, ps with level2 restriction
TEST_F(BeginDocumentTest_2692, PrintingPsLevel2_2692) {
    printing = true;
    ps = true;
    level2 = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 200.0, 300.0);

    EXPECT_NE(surface, nullptr);
}

// Test: When printing, ps with duplex
TEST_F(BeginDocumentTest_2692, PrintingPsDuplex_2692) {
    printing = true;
    ps = true;
    duplex = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 200.0, 300.0);

    EXPECT_NE(surface, nullptr);
}
#endif

#ifdef CAIRO_HAS_SVG_SURFACE
// Test: When printing and svg, SVG surface is created
TEST_F(BeginDocumentTest_2692, PrintingSvgToFile_2692) {
    printing = true;
    svg = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 200.0, 300.0);

    EXPECT_NE(output_file, nullptr);
    EXPECT_NE(surface, nullptr);
}
#endif

// Test: Boundary - zero dimensions
TEST_F(BeginDocumentTest_2692, ZeroDimensions_2692) {
    printing = true;
    pdf = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 0.0, 0.0);

    EXPECT_NE(output_file, nullptr);
    // Surface may or may not be valid with zero dimensions, but should not crash
}

// Test: Boundary - very large dimensions
TEST_F(BeginDocumentTest_2692, LargeDimensions_2692) {
    printing = true;
    pdf = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 100000.0, 100000.0);

    EXPECT_NE(output_file, nullptr);
    EXPECT_NE(surface, nullptr);
}

// Test: printToWin32 sets output_file to nullptr
TEST_F(BeginDocumentTest_2692, PrintToWin32SetsOutputFileNull_2692) {
    printing = true;
    printToWin32 = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    // On non-Win32 platforms this may not create a surface via win32BeginDocument
    // but output_file should be nullptr
    beginDocument(&inputName, &outputName, 200.0, 300.0);

    EXPECT_EQ(output_file, nullptr);
}

// Test: Negative dimensions
TEST_F(BeginDocumentTest_2692, NegativeDimensions_2692) {
    printing = true;
    pdf = true;
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    // Should not crash with negative dimensions
    beginDocument(&inputName, &outputName, -100.0, -200.0);

    EXPECT_NE(output_file, nullptr);
}

// Test: When no format flags are set but printing is true, no surface created
TEST_F(BeginDocumentTest_2692, PrintingNoFormatFlags_2692) {
    printing = true;
    // none of ps, eps, pdf, svg, printToWin32 set
    GooString inputName("input.pdf");
    GooString outputName(temp_output_);

    beginDocument(&inputName, &outputName, 200.0, 300.0);

    // File should be opened but no surface created
    EXPECT_NE(output_file, nullptr);
    EXPECT_EQ(surface, nullptr);
}
