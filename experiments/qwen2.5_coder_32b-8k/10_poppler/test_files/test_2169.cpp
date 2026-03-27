#include <gtest/gtest.h>



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_A_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfA), POPPLER_PDF_SUBTYPE_CONF_A);

}



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_B_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfB), POPPLER_PDF_SUBTYPE_CONF_B);

}



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_G_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfG), POPPLER_PDF_SUBTYPE_CONF_G);

}



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_N_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfN), POPPLER_PDF_SUBTYPE_CONF_N);

}



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_P_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfP), POPPLER_PDF_SUBTYPE_CONF_P);

}



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_PG_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfPG), POPPLER_PDF_SUBTYPE_CONF_PG);

}



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_U_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfU), POPPLER_PDF_SUBTYPE_CONF_U);

}



TEST(convert_pdf_subtype_conformance_2169, NormalOperation_None_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfNone), POPPLER_PDF_SUBTYPE_CONF_NONE);

}



TEST(convert_pdf_subtype_conformance_2169, BoundaryCondition_Null_2169) {

    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfNull), POPPLER_PDF_SUBTYPE_CONF_UNSET);

}



TEST(convert_pdf_subtype_conformance_2169, Exceptional_DefaultCase_2169) {

    // Assuming default case acts as an exceptional case for undefined values

    int undefinedValue = 9; // This value is not defined in the enum

    EXPECT_EQ(convert_pdf_subtype_conformance(static_cast<PDFSubtypeConformance>(undefinedValue)), POPPLER_PDF_SUBTYPE_CONF_UNSET);

}
