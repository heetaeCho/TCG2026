#include <gtest/gtest.h>

// Include the necessary headers for the enums
#include "poppler/PDFDoc.h"
#include "glib/poppler-document.h"

// Since convert_pdf_subtype_part is a static function in the .cc file,
// we need to either include it or redefine access. We'll include the source
// to get access to the static function for testing purposes.
// Alternatively, we declare it as extern for testing.

// We need access to the static function. Since it's static in the .cc file,
// we include the .cc file directly for testing purposes.
#include "glib/poppler-document.cc"

class ConvertPdfSubtypePartTest_2168 : public ::testing::Test {
protected:
};

// Test normal operation: subtypePart1 maps to POPPLER_PDF_SUBTYPE_PART_1
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart1_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_1, convert_pdf_subtype_part(subtypePart1));
}

// Test normal operation: subtypePart2 maps to POPPLER_PDF_SUBTYPE_PART_2
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart2_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_2, convert_pdf_subtype_part(subtypePart2));
}

// Test normal operation: subtypePart3 maps to POPPLER_PDF_SUBTYPE_PART_3
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart3_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_3, convert_pdf_subtype_part(subtypePart3));
}

// Test normal operation: subtypePart4 maps to POPPLER_PDF_SUBTYPE_PART_4
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart4_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_4, convert_pdf_subtype_part(subtypePart4));
}

// Test normal operation: subtypePart5 maps to POPPLER_PDF_SUBTYPE_PART_5
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart5_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_5, convert_pdf_subtype_part(subtypePart5));
}

// Test normal operation: subtypePart6 maps to POPPLER_PDF_SUBTYPE_PART_6
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart6_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_6, convert_pdf_subtype_part(subtypePart6));
}

// Test normal operation: subtypePart7 maps to POPPLER_PDF_SUBTYPE_PART_7
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart7_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_7, convert_pdf_subtype_part(subtypePart7));
}

// Test normal operation: subtypePart8 maps to POPPLER_PDF_SUBTYPE_PART_8
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePart8_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_8, convert_pdf_subtype_part(subtypePart8));
}

// Test boundary: subtypePartNone maps to POPPLER_PDF_SUBTYPE_PART_NONE
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePartNone_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_NONE, convert_pdf_subtype_part(subtypePartNone));
}

// Test boundary: subtypePartNull maps to POPPLER_PDF_SUBTYPE_PART_UNSET
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertSubtypePartNull_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_UNSET, convert_pdf_subtype_part(subtypePartNull));
}

// Test error/default case: an out-of-range value should map to POPPLER_PDF_SUBTYPE_PART_UNSET
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertUnknownValueReturnsUnset_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_UNSET, convert_pdf_subtype_part(static_cast<PDFSubtypePart>(100)));
}

// Test error/default case: negative value should map to POPPLER_PDF_SUBTYPE_PART_UNSET
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertNegativeValueReturnsUnset_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_UNSET, convert_pdf_subtype_part(static_cast<PDFSubtypePart>(-1)));
}

// Test that subtypePartNull (which is 0) specifically returns UNSET
TEST_F(ConvertPdfSubtypePartTest_2168, SubtypePartNullIsZeroReturnsUnset_2168) {
    EXPECT_EQ(0, subtypePartNull);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_UNSET, convert_pdf_subtype_part(subtypePartNull));
}

// Verify the numeric values of the output match expected enum values
TEST_F(ConvertPdfSubtypePartTest_2168, OutputEnumValuesMatchExpected_2168) {
    EXPECT_EQ(1, static_cast<int>(convert_pdf_subtype_part(subtypePart1)));
    EXPECT_EQ(2, static_cast<int>(convert_pdf_subtype_part(subtypePart2)));
    EXPECT_EQ(3, static_cast<int>(convert_pdf_subtype_part(subtypePart3)));
    EXPECT_EQ(4, static_cast<int>(convert_pdf_subtype_part(subtypePart4)));
    EXPECT_EQ(5, static_cast<int>(convert_pdf_subtype_part(subtypePart5)));
    EXPECT_EQ(6, static_cast<int>(convert_pdf_subtype_part(subtypePart6)));
    EXPECT_EQ(7, static_cast<int>(convert_pdf_subtype_part(subtypePart7)));
    EXPECT_EQ(8, static_cast<int>(convert_pdf_subtype_part(subtypePart8)));
    EXPECT_EQ(9, static_cast<int>(convert_pdf_subtype_part(subtypePartNone)));
    EXPECT_EQ(0, static_cast<int>(convert_pdf_subtype_part(subtypePartNull)));
}

// Test another large out-of-range value for default case
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertLargeValueReturnsUnset_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_UNSET, convert_pdf_subtype_part(static_cast<PDFSubtypePart>(999)));
}

// Test value just beyond the valid range (10) hits default
TEST_F(ConvertPdfSubtypePartTest_2168, ConvertValueTenReturnsUnset_2168) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PART_UNSET, convert_pdf_subtype_part(static_cast<PDFSubtypePart>(10)));
}
