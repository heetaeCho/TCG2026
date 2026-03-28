#include <gtest/gtest.h>
#include "poppler-document.h"
#include "PDFDoc.h"

// Since convert_pdf_subtype_conformance is a static function in the .cc file,
// we need to either include the .cc or declare it extern for testing.
// We'll include the implementation file to access the static function.
// In practice, this might require removing the 'static' keyword or using a test helper.

// Forward declaration - assuming we can access the function for testing
// If the function is static, we include the .cc file directly
#include "poppler-document.cc"

class ConvertPdfSubtypeConformanceTest_2169 : public ::testing::Test {
protected:
};

// Test normal mapping: subtypeConfA -> POPPLER_PDF_SUBTYPE_CONF_A
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfA_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_A, convert_pdf_subtype_conformance(subtypeConfA));
}

// Test normal mapping: subtypeConfB -> POPPLER_PDF_SUBTYPE_CONF_B
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfB_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_B, convert_pdf_subtype_conformance(subtypeConfB));
}

// Test normal mapping: subtypeConfG -> POPPLER_PDF_SUBTYPE_CONF_G
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfG_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_G, convert_pdf_subtype_conformance(subtypeConfG));
}

// Test normal mapping: subtypeConfN -> POPPLER_PDF_SUBTYPE_CONF_N
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfN_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_N, convert_pdf_subtype_conformance(subtypeConfN));
}

// Test normal mapping: subtypeConfP -> POPPLER_PDF_SUBTYPE_CONF_P
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfP_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_P, convert_pdf_subtype_conformance(subtypeConfP));
}

// Test normal mapping: subtypeConfPG -> POPPLER_PDF_SUBTYPE_CONF_PG
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfPG_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_PG, convert_pdf_subtype_conformance(subtypeConfPG));
}

// Test normal mapping: subtypeConfU -> POPPLER_PDF_SUBTYPE_CONF_U
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfU_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_U, convert_pdf_subtype_conformance(subtypeConfU));
}

// Test normal mapping: subtypeConfNone -> POPPLER_PDF_SUBTYPE_CONF_NONE
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfNone_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_NONE, convert_pdf_subtype_conformance(subtypeConfNone));
}

// Test boundary: subtypeConfNull -> POPPLER_PDF_SUBTYPE_CONF_UNSET
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertSubtypeConfNull_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_UNSET, convert_pdf_subtype_conformance(subtypeConfNull));
}

// Test default case: unknown/invalid enum value should return POPPLER_PDF_SUBTYPE_CONF_UNSET
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertUnknownValueReturnsUnset_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_UNSET, convert_pdf_subtype_conformance(static_cast<PDFSubtypeConformance>(99)));
}

// Test default case: negative value should return POPPLER_PDF_SUBTYPE_CONF_UNSET
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertNegativeValueReturnsUnset_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_UNSET, convert_pdf_subtype_conformance(static_cast<PDFSubtypeConformance>(-1)));
}

// Test that all valid enum values produce distinct results
TEST_F(ConvertPdfSubtypeConformanceTest_2169, AllValidValuesProduceDistinctResults_2169) {
    PopplerPDFConformance results[] = {
        convert_pdf_subtype_conformance(subtypeConfA),
        convert_pdf_subtype_conformance(subtypeConfB),
        convert_pdf_subtype_conformance(subtypeConfG),
        convert_pdf_subtype_conformance(subtypeConfN),
        convert_pdf_subtype_conformance(subtypeConfP),
        convert_pdf_subtype_conformance(subtypeConfPG),
        convert_pdf_subtype_conformance(subtypeConfU),
        convert_pdf_subtype_conformance(subtypeConfNone),
    };
    
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            EXPECT_NE(results[i], results[j]) << "Results at index " << i << " and " << j << " should be distinct";
        }
    }
}

// Test that subtypeConfNull maps to same value as default case
TEST_F(ConvertPdfSubtypeConformanceTest_2169, NullAndDefaultMapToSameValue_2169) {
    EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfNull),
              convert_pdf_subtype_conformance(static_cast<PDFSubtypeConformance>(100)));
}

// Test boundary: value just beyond the valid enum range
TEST_F(ConvertPdfSubtypeConformanceTest_2169, ConvertValueBeyondEnumRange_2169) {
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_UNSET, convert_pdf_subtype_conformance(static_cast<PDFSubtypeConformance>(9)));
}
