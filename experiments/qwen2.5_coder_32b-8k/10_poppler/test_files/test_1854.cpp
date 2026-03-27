#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "GooString.h"



using namespace ::testing;



TEST(pdfConformanceFromStringTest_1854, ValidInputA_1854) {

    EXPECT_EQ(subtypeConfA, pdfConformanceFromString("PDF/A-1a"));

}



TEST(pdfConformanceFromStringTest_1854, ValidInputB_1854) {

    EXPECT_EQ(subtypeConfB, pdfConformanceFromString("PDF/X-2b"));

}



TEST(pdfConformanceFromStringTest_1854, ValidInputG_1854) {

    EXPECT_EQ(subtypeConfG, pdfConformanceFromString("PDF/VT-3g"));

}



TEST(pdfConformanceFromStringTest_1854, ValidInputN_1854) {

    EXPECT_EQ(subtypeConfN, pdfConformanceFromString("PDF/E-4n"));

}



TEST(pdfConformanceFromStringTest_1854, ValidInputP_1854) {

    EXPECT_EQ(subtypeConfP, pdfConformanceFromString("PDF/UA-5p"));

}



TEST(pdfConformanceFromStringTest_1854, ValidInputPG_1854) {

    EXPECT_EQ(subtypeConfPG, pdfConformanceFromString("PDF/A-6pg"));

}



TEST(pdfConformanceFromStringTest_1854, ValidInputU_1854) {

    EXPECT_EQ(subtypeConfU, pdfConformanceFromString("PDF/E-7u"));

}



TEST(pdfConformanceFromStringTest_1854, InvalidInputEmptyString_1854) {

    EXPECT_EQ(subtypeConfNone, pdfConformanceFromString(""));

}



TEST(pdfConformanceFromStringTest_1854, InvalidInputNoVersionNumber_1854) {

    EXPECT_EQ(subtypeConfNone, pdfConformanceFromString("PDF/A-"));

}



TEST(pdfConformanceFromStringTest_1854, InvalidInputExtraCharacters_1854) {

    EXPECT_EQ(subtypeConfNone, pdfConformanceFromString("PDF/A-1aextra"));

}



TEST(pdfConformanceFromStringTest_1854, InvalidInputWrongFormat_1854) {

    EXPECT_EQ(subtypeConfNone, pdfConformanceFromString("A-1a"));

}



TEST(pdfConformanceFromStringTest_1854, InvalidInputUnknownSubtype_1854) {

    EXPECT_EQ(subtypeConfNone, pdfConformanceFromString("PDF/A-1z"));

}
