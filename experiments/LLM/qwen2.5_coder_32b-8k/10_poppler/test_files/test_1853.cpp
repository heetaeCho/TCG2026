#include <gtest/gtest.h>

#include <string>

#include "PDFDoc.h"



using namespace std;



// Test fixture class for PDFSubtypePart tests

class PDFSubtypePartTest_1853 : public ::testing::Test {

protected:

    // Helper function to call the function under test

    PDFSubtypePart GetPDFSubtypePart(PDFSubtype subtype, const string& pdfsubver) {

        return pdfPartFromString(subtype, pdfsubver);

    }

};



// Test normal operation for subtypePDFA with valid version

TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFA_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFA, "PDF/A-1a"), subtypePart1);

}



// Test normal operation for subtypePDFX with valid versions

TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFX_2001_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFX, "PDF/X-1a:2001"), subtypePart1);

}



TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFX_2003_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFX, "PDF/X-1b:2003"), subtypePart4);

}



TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFX_Part2_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFX, "PDF/X-2a"), subtypePart5);

}



TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFX_Part3_2002_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFX, "PDF/X-3b:2002"), subtypePart3);

}



TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFX_Part3_2003_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFX, "PDF/X-3a:2003"), subtypePart6);

}



TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFX_Part4_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFX, "PDF/X-4a"), subtypePart7);

}



TEST_F(PDFSubtypePartTest_1853, NormalOperation_PDFX_Part5_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFX, "PDF/X-5a"), subtypePart8);

}



// Test boundary conditions with minimal and maximal values

TEST_F(PDFSubtypePartTest_1853, BoundaryCondition_Minimal_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFA, "PDF/A-0a:2000"), subtypePartNone);

}



// Test boundary conditions with invalid format strings

TEST_F(PDFSubtypePartTest_1853, InvalidFormat_NoVersion_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFA, "PDF/A-1"), subtypePartNone);

}



TEST_F(PDFSubtypePartTest_1853, InvalidFormat_ExtraColon_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFA, "PDF/A-1a::2001"), subtypePartNone);

}



// Test exceptional or error cases with invalid part numbers

TEST_F(PDFSubtypePartTest_1853, InvalidPartNumber_Large_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFA, "PDF/A-9a:2001"), subtypePartNone);

}



// Test exceptional or error cases with invalid date

TEST_F(PDFSubtypePartTest_1853, InvalidDate_1853) {

    EXPECT_EQ(GetPDFSubtypePart(subtypePDFA, "PDF/A-1a:abcd"), subtypePartNone);

}
