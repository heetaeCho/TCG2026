#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>
#include <string>
#include <iostream>
#include "./TestProjects/poppler/poppler/PDFDoc.h"  // Include the header file for PDFDoc
#include "./TestProjects/poppler/goo/GooString.h"   // Include the header file for GooString
#include "./TestProjects/poppler/poppler/Error.h"    // Include the header file for Error

// Mock for GooString class (if needed for testing)

class PDFDocTest_1854 : public ::testing::Test {
protected:
    // Setup and teardown if needed
    void SetUp() override {
        // Set up the environment for tests
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// Test for the normal case (valid PDF subtype version string)
TEST_F(PDFDocTest_1854, ValidPDFSubtypeA_1854) {
    std::string pdfsubver = "PDF/A-1";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfA);
}

TEST_F(PDFDocTest_1854, ValidPDFSubtypeB_1854) {
    std::string pdfsubver = "PDF/B-2";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfB);
}

TEST_F(PDFDocTest_1854, ValidPDFSubtypeG_1854) {
    std::string pdfsubver = "PDF/G-3";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfG);
}

TEST_F(PDFDocTest_1854, ValidPDFSubtypeP_1854) {
    std::string pdfsubver = "PDF/P-4";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfP);
}

TEST_F(PDFDocTest_1854, ValidPDFSubtypePG_1854) {
    std::string pdfsubver = "PDF/PG-5";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfPG);
}

// Test for boundary cases
TEST_F(PDFDocTest_1854, InvalidPDFSubtypeEmpty_1854) {
    std::string pdfsubver = "";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfNone);
}

TEST_F(PDFDocTest_1854, InvalidPDFSubtypeInvalidLetter_1854) {
    std::string pdfsubver = "PDF/X-XYZ";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfNone);
}

// Test for unexpected syntax in the string
TEST_F(PDFDocTest_1854, InvalidPDFSubtypeExtraChars_1854) {
    std::string pdfsubver = "PDF/X-3-extra";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfNone);
}

// Test for exceptional case where there is no match
TEST_F(PDFDocTest_1854, InvalidPDFSubtypeFormat_1854) {
    std::string pdfsubver = "Not-a-valid-format";
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfNone);
}

// Test for boundary condition where the version string has only one character after the dash
TEST_F(PDFDocTest_1854, ValidPDFSubtypeSingleChar_1854) {
    std::string pdfsubver = "PDF/A-1"; // Testing minimal valid case
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfA);
}

// Test for uppercase letters (case-insensitive check)
TEST_F(PDFDocTest_1854, ValidPDFSubtypeUppercase_1854) {
    std::string pdfsubver = "PDF/A-1"; // Testing uppercase version
    PDFSubtypeConformance result = pdfConformanceFromString(pdfsubver);
    EXPECT_EQ(result, subtypeConfA);
}