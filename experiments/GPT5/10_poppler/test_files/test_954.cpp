// PDFDoc_getPageMediaWidth_954_test.cpp

#include <gtest/gtest.h>

#include "poppler/PDFDoc.h"
#include "goo/GooString.h"

#include <climits>
#include <memory>

namespace {

std::unique_ptr<PDFDoc> makeErrorDoc_954(int errCode = 1) {
  // ErrorPDFDoc is part of the public interface and should create a valid
  // PDFDoc instance representing an error state (no assumptions beyond that).
  return PDFDoc::ErrorPDFDoc(errCode, std::make_unique<GooString>("dummy.pdf"));
}

} // namespace

TEST(PDFDocTest_954, ReturnsZeroForTypicalInvalidPages_954) {
  auto doc = makeErrorDoc_954();
  ASSERT_NE(doc, nullptr);

  // For an error doc, getPage(page) is expected to be nullptr for page indices,
  // so getPageMediaWidth(page) should return 0.0 per the interface implementation.
  EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 0.0);
  EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(0), 0.0);
  EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(-1), 0.0);
}

TEST(PDFDocTest_954, ReturnsZeroForExtremePageNumbers_954) {
  auto doc = makeErrorDoc_954();
  ASSERT_NE(doc, nullptr);

  EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(INT_MAX), 0.0);
  EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(INT_MIN), 0.0);
}

TEST(PDFDocTest_954, MultipleCallsAreStableForSameInput_954) {
  auto doc = makeErrorDoc_954();
  ASSERT_NE(doc, nullptr);

  // Observable behavior: repeated calls with the same input should return the same value.
  const double first = doc->getPageMediaWidth(1);
  const double second = doc->getPageMediaWidth(1);
  EXPECT_DOUBLE_EQ(first, second);
  EXPECT_DOUBLE_EQ(first, 0.0);
}

TEST(PDFDocTest_954, DifferentInvalidInputsAllReturnZero_954) {
  auto doc = makeErrorDoc_954();
  ASSERT_NE(doc, nullptr);

  // Boundary-ish coverage across a small set of representative invalid values.
  const int pages[] = {-100, -2, -1, 0, 1, 2, 100, 1000};
  for (int p : pages) {
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(p), 0.0) << "page=" << p;
  }
}