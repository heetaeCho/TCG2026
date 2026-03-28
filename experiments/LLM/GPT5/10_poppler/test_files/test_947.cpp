// PDFDoc_getErrorCode_test_947.cpp
//
// Unit tests for PDFDoc::getErrorCode() based strictly on the public interface.
// TEST_ID: 947

#include <gtest/gtest.h>

#include <limits>
#include <memory>

#include "PDFDoc.h"

// Poppler typically provides GooString in one of these locations depending on build layout.
#if __has_include("goo/GooString.h")
#include "goo/GooString.h"
#elif __has_include("GooString.h")
#include "GooString.h"
#endif

namespace {

class PDFDocGetErrorCodeTest_947 : public ::testing::Test {
protected:
  static std::unique_ptr<GooString> MakeFileName(const char *name) {
    // Use a minimal, deterministic file name for the ErrorPDFDoc factory.
    return std::make_unique<GooString>(name);
  }
};

TEST_F(PDFDocGetErrorCodeTest_947, ReturnsProvidedErrorCode_947) {
  const int kErr = 123;

  auto doc = PDFDoc::ErrorPDFDoc(kErr, MakeFileName("dummy_947.pdf"));
  ASSERT_NE(doc, nullptr);

  // Observable behavior: getter reflects the error code of the created error document.
  EXPECT_EQ(doc->getErrorCode(), kErr);
}

TEST_F(PDFDocGetErrorCodeTest_947, ReturnsZeroErrorCode_947) {
  const int kErr = 0;

  auto doc = PDFDoc::ErrorPDFDoc(kErr, MakeFileName("dummy_947.pdf"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(doc->getErrorCode(), kErr);
}

TEST_F(PDFDocGetErrorCodeTest_947, ReturnsNegativeErrorCode_947) {
  const int kErr = -1;

  auto doc = PDFDoc::ErrorPDFDoc(kErr, MakeFileName("dummy_947.pdf"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(doc->getErrorCode(), kErr);
}

TEST_F(PDFDocGetErrorCodeTest_947, ReturnsMaxIntErrorCode_947) {
  const int kErr = (std::numeric_limits<int>::max)();

  auto doc = PDFDoc::ErrorPDFDoc(kErr, MakeFileName("dummy_947.pdf"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(doc->getErrorCode(), kErr);
}

TEST_F(PDFDocGetErrorCodeTest_947, CallableOnConstReference_947) {
  const int kErr = 77;

  auto doc = PDFDoc::ErrorPDFDoc(kErr, MakeFileName("dummy_947.pdf"));
  ASSERT_NE(doc, nullptr);

  const PDFDoc &constDoc = *doc;
  EXPECT_EQ(constDoc.getErrorCode(), kErr);
}

} // namespace