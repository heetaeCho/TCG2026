#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>
#include <string>
#include "PDFDoc.h"

// Mocks or necessary helpers (if applicable)
class MockPDFDoc {};

class PDFDocTest_1853 : public ::testing::Test {
protected:
    // Setup and teardown if needed
    void SetUp() override {}
    void TearDown() override {}
};

// TEST CASE 1: Valid PDF subtype and version match (Normal Operation)
TEST_F(PDFDocTest_1853, ValidPDFX2001_1853) {
    // Prepare input
    PDFSubtype subtype = subtypePDFX;
    std::string pdfsubver = "PDF/X-1:2001";

    // Call the function under test
    PDFSubtypePart result = pdfPartFromString(subtype, pdfsubver);

    // Verify the behavior (expected output)
    EXPECT_EQ(result, subtypePart1);  // Based on the provided logic, PDF/X-1:2001 should map to subtypePart1
}

// TEST CASE 2: Valid PDF subtype and version match for a different part (Normal Operation)
TEST_F(PDFDocTest_1853, ValidPDFX2003_1853) {
    // Prepare input
    PDFSubtype subtype = subtypePDFX;
    std::string pdfsubver = "PDF/X-1:2003";

    // Call the function under test
    PDFSubtypePart result = pdfPartFromString(subtype, pdfsubver);

    // Verify the behavior (expected output)
    EXPECT_EQ(result, subtypePart4);  // PDF/X-1:2003 should map to subtypePart4
}

// TEST CASE 3: PDF version with an unmatched part number (Edge case)
TEST_F(PDFDocTest_1853, InvalidPDFXPart_1853) {
    // Prepare input
    PDFSubtype subtype = subtypePDFX;
    std::string pdfsubver = "PDF/X-99:2003";  // Invalid part number

    // Call the function under test
    PDFSubtypePart result = pdfPartFromString(subtype, pdfsubver);

    // Verify the behavior (expected output should be subtypePartNone for invalid part number)
    EXPECT_EQ(result, subtypePartNone);
}

// TEST CASE 4: Valid PDF subtype with no date (Normal Operation)
TEST_F(PDFDocTest_1853, ValidPDFXWithoutDate_1853) {
    // Prepare input
    PDFSubtype subtype = subtypePDFX;
    std::string pdfsubver = "PDF/X-1";  // No date specified

    // Call the function under test
    PDFSubtypePart result = pdfPartFromString(subtype, pdfsubver);

    // Verify the behavior (expected output for PDF/X-1 with no date should default to subtypePart1)
    EXPECT_EQ(result, subtypePart1);
}

// TEST CASE 5: Invalid PDF subtype string (Edge case)
TEST_F(PDFDocTest_1853, InvalidPDFSubtypeString_1853) {
    // Prepare input
    PDFSubtype subtype = subtypePDFX;
    std::string pdfsubver = "PDF/Unknown-1:2001";  // Unknown subtype

    // Call the function under test
    PDFSubtypePart result = pdfPartFromString(subtype, pdfsubver);

    // Verify the behavior (expected output should be subtypePartNone for invalid subtype)
    EXPECT_EQ(result, subtypePartNone);
}

// TEST CASE 6: Valid PDF/E version (Normal Operation)
TEST_F(PDFDocTest_1853, ValidPDFE_1853) {
    // Prepare input
    PDFSubtype subtype = subtypePDFE;
    std::string pdfsubver = "PDF/E-1:2001";  // PDF/E subtype with version

    // Call the function under test
    PDFSubtypePart result = pdfPartFromString(subtype, pdfsubver);

    // Verify the behavior (expected output for PDF/E-1:2001 should default to subtypePart1)
    EXPECT_EQ(result, subtypePart1);
}