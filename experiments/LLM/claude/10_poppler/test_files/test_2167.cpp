#include <gtest/gtest.h>

// Include necessary headers
#include "poppler/PDFDoc.h"

// We need the enum definitions
// From poppler-document.h
typedef enum {
    POPPLER_PDF_SUBTYPE_UNSET = 0,
    POPPLER_PDF_SUBTYPE_PDF_A = 1,
    POPPLER_PDF_SUBTYPE_PDF_E = 2,
    POPPLER_PDF_SUBTYPE_PDF_UA = 3,
    POPPLER_PDF_SUBTYPE_PDF_VT = 4,
    POPPLER_PDF_SUBTYPE_PDF_X = 5,
    POPPLER_PDF_SUBTYPE_NONE = 6
} PopplerPDFSubtype;

// Since convert_pdf_subtype is a static function in the .cc file, we need to
// either include the source or redeclare it for testing purposes.
// We'll include the function declaration to test it.
// In practice, we'd need access to this function. Since it's static, we
// include the source file directly for testing.
static PopplerPDFSubtype convert_pdf_subtype(PDFSubtype pdfSubtype);

// Include the implementation to get access to the static function
#include "poppler-document.cc"

class ConvertPdfSubtypeTest_2167 : public ::testing::Test {
protected:
};

// Test normal operation: subtypePDFA maps to POPPLER_PDF_SUBTYPE_PDF_A
TEST_F(ConvertPdfSubtypeTest_2167, ConvertSubtypePDFA_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PDF_A, convert_pdf_subtype(subtypePDFA));
}

// Test normal operation: subtypePDFE maps to POPPLER_PDF_SUBTYPE_PDF_E
TEST_F(ConvertPdfSubtypeTest_2167, ConvertSubtypePDFE_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PDF_E, convert_pdf_subtype(subtypePDFE));
}

// Test normal operation: subtypePDFUA maps to POPPLER_PDF_SUBTYPE_PDF_UA
TEST_F(ConvertPdfSubtypeTest_2167, ConvertSubtypePDFUA_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PDF_UA, convert_pdf_subtype(subtypePDFUA));
}

// Test normal operation: subtypePDFVT maps to POPPLER_PDF_SUBTYPE_PDF_VT
TEST_F(ConvertPdfSubtypeTest_2167, ConvertSubtypePDFVT_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PDF_VT, convert_pdf_subtype(subtypePDFVT));
}

// Test normal operation: subtypePDFX maps to POPPLER_PDF_SUBTYPE_PDF_X
TEST_F(ConvertPdfSubtypeTest_2167, ConvertSubtypePDFX_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_PDF_X, convert_pdf_subtype(subtypePDFX));
}

// Test normal operation: subtypeNone maps to POPPLER_PDF_SUBTYPE_NONE
TEST_F(ConvertPdfSubtypeTest_2167, ConvertSubtypeNone_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_NONE, convert_pdf_subtype(subtypeNone));
}

// Test boundary: subtypeNull maps to POPPLER_PDF_SUBTYPE_UNSET
TEST_F(ConvertPdfSubtypeTest_2167, ConvertSubtypeNull_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_UNSET, convert_pdf_subtype(subtypeNull));
}

// Test exceptional case: unknown/invalid enum value defaults to POPPLER_PDF_SUBTYPE_UNSET
TEST_F(ConvertPdfSubtypeTest_2167, ConvertUnknownSubtypeReturnsUnset_2167)
{
    // Cast an out-of-range integer to PDFSubtype to test the default case
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_UNSET, convert_pdf_subtype(static_cast<PDFSubtype>(99)));
}

// Test exceptional case: negative value defaults to POPPLER_PDF_SUBTYPE_UNSET
TEST_F(ConvertPdfSubtypeTest_2167, ConvertNegativeValueReturnsUnset_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_UNSET, convert_pdf_subtype(static_cast<PDFSubtype>(-1)));
}

// Test that subtypeNull (value 0) specifically hits the subtypeNull case, not default
TEST_F(ConvertPdfSubtypeTest_2167, SubtypeNullIsZero_2167)
{
    EXPECT_EQ(0, static_cast<int>(subtypeNull));
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_UNSET, convert_pdf_subtype(subtypeNull));
}

// Test boundary: value just beyond the valid enum range
TEST_F(ConvertPdfSubtypeTest_2167, ConvertValueBeyondMaxEnumReturnsUnset_2167)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_UNSET, convert_pdf_subtype(static_cast<PDFSubtype>(7)));
}

// Verify that each valid subtype produces a distinct result
TEST_F(ConvertPdfSubtypeTest_2167, AllValidSubtypesProduceDistinctResults_2167)
{
    PopplerPDFSubtype results[] = {
        convert_pdf_subtype(subtypePDFA),
        convert_pdf_subtype(subtypePDFE),
        convert_pdf_subtype(subtypePDFUA),
        convert_pdf_subtype(subtypePDFVT),
        convert_pdf_subtype(subtypePDFX),
        convert_pdf_subtype(subtypeNone)
    };

    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            EXPECT_NE(results[i], results[j])
                << "Results at index " << i << " and " << j << " should differ";
        }
    }
}
