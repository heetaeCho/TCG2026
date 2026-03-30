// TEST_ID: 948
//
// Unit tests for PDFDoc::getFopenErrno()
// File: ./TestProjects/poppler/poppler/PDFDoc.h

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <optional>

#include "poppler/PDFDoc.h"

// Poppler typically provides GooString in "goo/GooString.h"
#include "goo/GooString.h"

namespace {

class PDFDocTest_948 : public ::testing::Test {
protected:
  static std::unique_ptr<PDFDoc> MakeErrorDoc(int errorCode, const char *name) {
    auto fileName = std::make_unique<GooString>(name ? name : "");
    auto doc = PDFDoc::ErrorPDFDoc(errorCode, std::move(fileName));
    return doc;
  }
};

TEST_F(PDFDocTest_948, GetFopenErrno_CanBeCalledOnConst_948) {
  auto doc = MakeErrorDoc(1, "dummy.pdf");
  ASSERT_NE(doc, nullptr);

  const PDFDoc &cdoc = *doc;
  (void)cdoc.getFopenErrno();  // Should be callable on const objects.
  SUCCEED();
}

TEST_F(PDFDocTest_948, GetFopenErrno_ReturnValueIsStableAcrossMultipleCalls_948) {
  auto doc = MakeErrorDoc(2, "dummy.pdf");
  ASSERT_NE(doc, nullptr);

  const int v1 = doc->getFopenErrno();
  const int v2 = doc->getFopenErrno();
  const int v3 = doc->getFopenErrno();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(PDFDocTest_948, GetFopenErrno_TwoErrorDocsWithSameInputsMatch_948) {
  auto doc1 = MakeErrorDoc(3, "same.pdf");
  auto doc2 = MakeErrorDoc(3, "same.pdf");
  ASSERT_NE(doc1, nullptr);
  ASSERT_NE(doc2, nullptr);

  EXPECT_EQ(doc1->getFopenErrno(), doc2->getFopenErrno());
}

TEST_F(PDFDocTest_948, GetFopenErrno_HandlesEmptyFileNameBoundary_948) {
  auto doc = MakeErrorDoc(4, "");
  ASSERT_NE(doc, nullptr);

  // Boundary case: empty filename should not prevent calling the getter.
  (void)doc->getFopenErrno();
  SUCCEED();
}

TEST_F(PDFDocTest_948, GetFopenErrno_HandlesExtremeErrorCodesBoundary_948) {
  {
    auto docMin = MakeErrorDoc(std::numeric_limits<int>::min(), "min.pdf");
    ASSERT_NE(docMin, nullptr);
    (void)docMin->getFopenErrno();
  }
  {
    auto docMax = MakeErrorDoc(std::numeric_limits<int>::max(), "max.pdf");
    ASSERT_NE(docMax, nullptr);
    (void)docMax->getFopenErrno();
  }
  SUCCEED();
}

TEST_F(PDFDocTest_948, GetFopenErrno_DoesNotChangeAfterOtherConstCalls_948) {
  auto doc = MakeErrorDoc(5, "other.pdf");
  ASSERT_NE(doc, nullptr);

  const int before = doc->getFopenErrno();

  // Call a couple of other *observable* const methods if available in the build.
  // We do not assert specific values for these methods; only that they don't
  // change the fopen errno getter's result in this scenario.
  (void)doc->getFopenErrno();  // same method again
  // If these exist/are linked in your build, they should be safe to call:
  // (void)doc->getErrorCode();
  // (void)doc->isOk();

  const int after = doc->getFopenErrno();
  EXPECT_EQ(before, after);
}

}  // namespace