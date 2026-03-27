#include <gtest/gtest.h>

#include "TestProjects/poppler/glib/poppler-document.cc"



TEST(ConvertPDFSubtypePartTest_2168, NormalOperation_ConvertEachEnumValue_2168) {

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart1), POPPLER_PDF_SUBTYPE_PART_1);

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart2), POPPLER_PDF_SUBTYPE_PART_2);

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart3), POPPLER_PDF_SUBTYPE_PART_3);

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart4), POPPLER_PDF_SUBTYPE_PART_4);

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart5), POPPLER_PDF_SUBTYPE_PART_5);

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart6), POPPLER_PDF_SUBTYPE_PART_6);

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart7), POPPLER_PDF_SUBTYPE_PART_7);

    EXPECT_EQ(convert_pdf_subtype_part(subtypePart8), POPPLER_PDF_SUBTYPE_PART_8);

}



TEST(ConvertPDFSubtypePartTest_2168, BoundaryCondition_Convert subtypePartNone_2168) {

    EXPECT_EQ(convert_pdf_subtype_part(subtypePartNone), POPPLER_PDF_SUBTYPE_PART_NONE);

}



TEST(ConvertPDFSubtypePartTest_2168, BoundaryCondition_Convert subtypePartNull_2168) {

    EXPECT_EQ(convert_pdf_subtype_part(subtypePartNull), POPPLER_PDF_SUBTYPE_PART_UNSET);

}



TEST(ConvertPDFSubtypePartTest_2168, ExceptionalCase_DefaultValueForUnknownEnum_2168) {

    PDFSubtypePart unknownValue = static_cast<PDFSubtypePart>(10); // Assuming 10 is not a defined enum value

    EXPECT_EQ(convert_pdf_subtype_part(unknownValue), POPPLER_PDF_SUBTYPE_PART_UNSET);

}
