// File: poppler-document-convert-pdf-subtype-test-2167.cc

#include <gtest/gtest.h>

// Include the implementation unit so we can call the file-local (static)
// helper directly from the same translation unit, without re-implementing it.
#include "./TestProjects/poppler/glib/poppler-document.cc"

namespace {

class ConvertPdfSubtypeTest_2167 : public ::testing::Test {};

TEST_F(ConvertPdfSubtypeTest_2167, MapsSubtypePDFA_2167) {
    EXPECT_EQ(convert_pdf_subtype(subtypePDFA), POPPLER_PDF_SUBTYPE_PDF_A);
}

TEST_F(ConvertPdfSubtypeTest_2167, MapsSubtypePDFE_2167) {
    EXPECT_EQ(convert_pdf_subtype(subtypePDFE), POPPLER_PDF_SUBTYPE_PDF_E);
}

TEST_F(ConvertPdfSubtypeTest_2167, MapsSubtypePDFUA_2167) {
    EXPECT_EQ(convert_pdf_subtype(subtypePDFUA), POPPLER_PDF_SUBTYPE_PDF_UA);
}

TEST_F(ConvertPdfSubtypeTest_2167, MapsSubtypePDFVT_2167) {
    EXPECT_EQ(convert_pdf_subtype(subtypePDFVT), POPPLER_PDF_SUBTYPE_PDF_VT);
}

TEST_F(ConvertPdfSubtypeTest_2167, MapsSubtypePDFX_2167) {
    EXPECT_EQ(convert_pdf_subtype(subtypePDFX), POPPLER_PDF_SUBTYPE_PDF_X);
}

TEST_F(ConvertPdfSubtypeTest_2167, MapsSubtypeNone_2167) {
    EXPECT_EQ(convert_pdf_subtype(subtypeNone), POPPLER_PDF_SUBTYPE_NONE);
}

TEST_F(ConvertPdfSubtypeTest_2167, MapsSubtypeNullToUnset_2167) {
    EXPECT_EQ(convert_pdf_subtype(subtypeNull), POPPLER_PDF_SUBTYPE_UNSET);
}

TEST_F(ConvertPdfSubtypeTest_2167, MapsUnknownEnumValueToUnset_2167) {
    // Boundary / error-style case: value outside the known enum range.
    const auto unknown = static_cast<PDFSubtype>(999);
    EXPECT_EQ(convert_pdf_subtype(unknown), POPPLER_PDF_SUBTYPE_UNSET);
}

} // namespace