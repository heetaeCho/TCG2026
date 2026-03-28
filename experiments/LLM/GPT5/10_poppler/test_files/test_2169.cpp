// File: poppler-document-convert-pdf-subtype-conformance-test_2169.cc

#include <gtest/gtest.h>

// Pull in the enum definitions used by the helper.
#include "poppler/PDFDoc.h"
#include "glib/poppler-document.h"

// NOTE:
// convert_pdf_subtype_conformance() is a file-local (static) helper in
// poppler-document.cc. To test it without re-implementing its logic, we include
// the .cc so the function is compiled into this test translation unit.
#include "glib/poppler-document.cc"

namespace {

class ConvertPdfSubtypeConformanceTest_2169 : public ::testing::Test {};

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfA_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfA), POPPLER_PDF_SUBTYPE_CONF_A);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfB_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfB), POPPLER_PDF_SUBTYPE_CONF_B);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfG_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfG), POPPLER_PDF_SUBTYPE_CONF_G);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfN_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfN), POPPLER_PDF_SUBTYPE_CONF_N);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfP_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfP), POPPLER_PDF_SUBTYPE_CONF_P);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfPG_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfPG), POPPLER_PDF_SUBTYPE_CONF_PG);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfU_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfU), POPPLER_PDF_SUBTYPE_CONF_U);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfNone_2169) {
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfNone), POPPLER_PDF_SUBTYPE_CONF_NONE);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsSubtypeConfNullToUnset_2169) {
  // Boundary/edge: explicit "Null" value.
  EXPECT_EQ(convert_pdf_subtype_conformance(subtypeConfNull), POPPLER_PDF_SUBTYPE_CONF_UNSET);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsUnknownValueToUnset_2169) {
  // Exceptional/error-like: value outside the declared enum range.
  const auto unknown = static_cast<PDFSubtypeConformance>(999);
  EXPECT_EQ(convert_pdf_subtype_conformance(unknown), POPPLER_PDF_SUBTYPE_CONF_UNSET);
}

TEST_F(ConvertPdfSubtypeConformanceTest_2169, MapsNegativeValueToUnset_2169) {
  // Boundary: negative enum cast.
  const auto negative = static_cast<PDFSubtypeConformance>(-1);
  EXPECT_EQ(convert_pdf_subtype_conformance(negative), POPPLER_PDF_SUBTYPE_CONF_UNSET);
}

}  // namespace