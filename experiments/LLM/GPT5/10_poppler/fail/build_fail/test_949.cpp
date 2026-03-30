// File: PDFDoc_getFileName_test_949.cpp
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"

namespace {

class PDFDocTest_949 : public ::testing::Test {
protected:
  static std::unique_ptr<GooString> MakeGooString(const std::string &s) {
    return std::make_unique<GooString>(s.c_str());
  }
};

// Normal operation: a non-empty filename provided to ErrorPDFDoc is observable via getFileName().
TEST_F(PDFDocTest_949, GetFileNameReturnsSameStringContent_949) {
  auto doc = PDFDoc::ErrorPDFDoc(/*errorCode=*/1, MakeGooString("sample.pdf"));
  ASSERT_TRUE(doc);

  const GooString *name = doc->getFileName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name->c_str(), "sample.pdf");
}

// Normal operation: pointer returned by getFileName is stable across repeated calls.
TEST_F(PDFDocTest_949, GetFileNamePointerStableAcrossCalls_949) {
  auto doc = PDFDoc::ErrorPDFDoc(/*errorCode=*/2, MakeGooString("stable.pdf"));
  ASSERT_TRUE(doc);

  const GooString *name1 = doc->getFileName();
  const GooString *name2 = doc->getFileName();

  ASSERT_NE(name1, nullptr);
  ASSERT_NE(name2, nullptr);
  EXPECT_EQ(name1, name2);
  EXPECT_STREQ(name1->c_str(), "stable.pdf");
}

// Boundary condition: empty filename should be handled and observable.
TEST_F(PDFDocTest_949, GetFileNameHandlesEmptyString_949) {
  auto doc = PDFDoc::ErrorPDFDoc(/*errorCode=*/3, MakeGooString(""));
  ASSERT_TRUE(doc);

  const GooString *name = doc->getFileName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name->c_str(), "");
}

// Boundary condition: long filename should be preserved.
TEST_F(PDFDocTest_949, GetFileNameHandlesLongString_949) {
  const std::string longName(4096, 'a');
  auto doc = PDFDoc::ErrorPDFDoc(/*errorCode=*/4, MakeGooString(longName));
  ASSERT_TRUE(doc);

  const GooString *name = doc->getFileName();
  ASSERT_NE(name, nullptr);
  EXPECT_EQ(std::string(name->c_str()), longName);
}

// Exceptional / error case (observable): passing a null filename unique_ptr should not crash;
// getFileName should return nullptr (or at least be safely callable).
TEST_F(PDFDocTest_949, GetFileNameWithNullFilenameDoesNotCrash_949) {
  std::unique_ptr<GooString> nullName;
  auto doc = PDFDoc::ErrorPDFDoc(/*errorCode=*/5, std::move(nullName));
  ASSERT_TRUE(doc);

  const GooString *name = doc->getFileName();
  EXPECT_EQ(name, nullptr);
}

} // namespace