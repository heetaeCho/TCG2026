// PDFDoc_getXRef_950_test.cpp
//
// Unit tests for: PDFDoc::getXRef() const
// File: ./TestProjects/poppler/poppler/PDFDoc.h
//
// Constraints note:
// - Treat PDFDoc as a black box.
// - Only test observable behavior via public interface.
// - No access to private state (e.g., xref).
// - Use public factory (ErrorPDFDoc) to obtain instances without relying on filesystem parsing.

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Poppler headers (paths may vary slightly in your build).
#include "PDFDoc.h"
#include "goo/GooString.h"

namespace {

class PDFDocTest_950 : public ::testing::Test {
protected:
  static std::unique_ptr<GooString> MakeDummyFileName(const char *name = "dummy.pdf") {
    return std::make_unique<GooString>(name);
  }

  static std::unique_ptr<PDFDoc> MakeErrorDoc(int errorCode) {
    // Use the public factory to avoid depending on file IO / parsing behavior.
    return PDFDoc::ErrorPDFDoc(errorCode, MakeDummyFileName());
  }
};

TEST_F(PDFDocTest_950, GetXRef_IsCallableOnConstObject_950) {
  auto doc = MakeErrorDoc(1);
  ASSERT_NE(doc, nullptr);

  const PDFDoc &constDoc = *doc;
  // Only verifying that the call is well-formed and does not crash.
  XRef *xref = constDoc.getXRef();
  (void)xref;
}

TEST_F(PDFDocTest_950, GetXRef_ReturnsSamePointerAcrossCalls_950) {
  auto doc = MakeErrorDoc(2);
  ASSERT_NE(doc, nullptr);

  XRef *first = doc->getXRef();
  XRef *second = doc->getXRef();

  // Observable behavior: repeated calls should be stable for the same object instance.
  EXPECT_EQ(first, second);
}

TEST_F(PDFDocTest_950, GetXRef_DoesNotThrow_OnErrorDocFactory_950) {
  // Even if ErrorPDFDoc creates a minimal/invalid document, getXRef should remain callable.
  auto doc = MakeErrorDoc(3);
  ASSERT_NE(doc, nullptr);

  EXPECT_NO_THROW({
    XRef *xref = doc->getXRef();
    (void)xref;
  });
}

TEST_F(PDFDocTest_950, GetXRef_HandlesDifferentErrorCodes_BoundaryValues_950) {
  // Boundary-ish values for the factory input; we do not assume semantics beyond creation.
  const int kCodes[] = {0, -1, 1, 2147483647};

  for (int code : kCodes) {
    auto doc = MakeErrorDoc(code);
    ASSERT_NE(doc, nullptr) << "ErrorPDFDoc returned null for errorCode=" << code;

    // Must be callable; value itself is implementation-defined (could be nullptr or non-null).
    XRef *xref1 = doc->getXRef();
    XRef *xref2 = doc->getXRef();
    EXPECT_EQ(xref1, xref2) << "getXRef not stable for errorCode=" << code;
  }
}

} // namespace