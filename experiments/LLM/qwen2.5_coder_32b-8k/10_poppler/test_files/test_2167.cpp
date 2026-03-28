#include <gtest/gtest.h>

#include "./TestProjects/poppler/glib/poppler-document.cc"



// Test Suite for convert_pdf_subtype function

class ConvertPDFSubtypeTest_2167 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ConvertPDFSubtypeTest_2167, ConvertPDFA_2167) {

    EXPECT_EQ(convert_pdf_subtype(subtypePDFA), POPPLER_PDF_SUBTYPE_PDF_A);

}



TEST_F(ConvertPDFSubtypeTest_2167, ConvertPDFE_2167) {

    EXPECT_EQ(convert_pdf_subtype(subtypePDFE), POPPLER_PDF_SUBTYPE_PDF_E);

}



TEST_F(ConvertPDFSubtypeTest_2167, ConvertPDFUA_2167) {

    EXPECT_EQ(convert_pdf_subtype(subtypePDFUA), POPPLER_PDF_SUBTYPE_PDF_UA);

}



TEST_F(ConvertPDFSubtypeTest_2167, ConvertPDFVT_2167) {

    EXPECT_EQ(convert_pdf_subtype(subtypePDFVT), POPPLER_PDF_SUBTYPE_PDF_VT);

}



TEST_F(ConvertPDFSubtypeTest_2167, ConvertPDFX_2167) {

    EXPECT_EQ(convert_pdf_subtype(subtypePDFX), POPPLER_PDF_SUBTYPE_PDF_X);

}



TEST_F(ConvertPDFSubtypeTest_2167, ConvertNone_2167) {

    EXPECT_EQ(convert_pdf_subtype(subtypeNone), POPPLER_PDF_SUBTYPE_NONE);

}



TEST_F(ConvertPDFSubtypeTest_2167, ConvertNull_2167) {

    EXPECT_EQ(convert_pdf_subtype(subtypeNull), POPPLER_PDF_SUBTYPE_UNSET);

}



TEST_F(ConvertPDFSubtypeTest_2167, ConvertDefaultCase_2167) {

    EXPECT_EQ(convert_pdf_subtype(static_cast<PDFSubtype>(-1)), POPPLER_PDF_SUBTYPE_UNSET);

}
