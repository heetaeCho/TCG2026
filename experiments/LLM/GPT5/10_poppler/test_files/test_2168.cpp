// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for convert_pdf_subtype_part()
// TEST_ID: 2168

#include <gtest/gtest.h>

// Include the enums used by the conversion helper.
#include "poppler/PDFDoc.h"
#include "glib/poppler-document.h"

// NOTE:
// The function under test is a file-local (static) helper implemented in
// ./glib/poppler-document.cc. These tests are intended to be compiled in the
// same translation unit by including that implementation file, so the static
// symbol is visible here.
//
// This pattern is commonly used for testing file-local helpers without
// changing production code.
#include "glib/poppler-document.cc"

namespace {

class ConvertPdfSubtypePartTest_2168 : public ::testing::Test {};

TEST_F(ConvertPdfSubtypePartTest_2168, MapsPart1To8_2168) {
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart1), POPPLER_PDF_SUBTYPE_PART_1);
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart2), POPPLER_PDF_SUBTYPE_PART_2);
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart3), POPPLER_PDF_SUBTYPE_PART_3);
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart4), POPPLER_PDF_SUBTYPE_PART_4);
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart5), POPPLER_PDF_SUBTYPE_PART_5);
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart6), POPPLER_PDF_SUBTYPE_PART_6);
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart7), POPPLER_PDF_SUBTYPE_PART_7);
  EXPECT_EQ(convert_pdf_subtype_part(subtypePart8), POPPLER_PDF_SUBTYPE_PART_8);
}

TEST_F(ConvertPdfSubtypePartTest_2168, MapsNone_2168) {
  EXPECT_EQ(convert_pdf_subtype_part(subtypePartNone), POPPLER_PDF_SUBTYPE_PART_NONE);
}

TEST_F(ConvertPdfSubtypePartTest_2168, MapsNullToUnset_2168) {
  EXPECT_EQ(convert_pdf_subtype_part(subtypePartNull), POPPLER_PDF_SUBTYPE_PART_UNSET);
}

TEST_F(ConvertPdfSubtypePartTest_2168, UnknownEnumValueReturnsUnset_Positive_2168) {
  // Boundary / exceptional: value outside defined enum range.
  const auto unknown = static_cast<PDFSubtypePart>(999);
  EXPECT_EQ(convert_pdf_subtype_part(unknown), POPPLER_PDF_SUBTYPE_PART_UNSET);
}

TEST_F(ConvertPdfSubtypePartTest_2168, UnknownEnumValueReturnsUnset_Negative_2168) {
  // Boundary / exceptional: negative value cast into enum type.
  const auto unknown = static_cast<PDFSubtypePart>(-1);
  EXPECT_EQ(convert_pdf_subtype_part(unknown), POPPLER_PDF_SUBTYPE_PART_UNSET);
}

}  // namespace