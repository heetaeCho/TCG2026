// TEST_ID: 946
// File: PDFDoc_isOk_946_test.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <climits>
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <system_error>

#include "PDFDoc.h"

// Poppler typically provides GooString via PDFDoc.h includes, but include explicitly if needed.
// #include "goo/GooString.h"

namespace {

class PDFDocTest_946 : public ::testing::Test {
protected:
  static std::unique_ptr<GooString> MakeGooString(const std::string &s) {
    // GooString in Poppler commonly has a ctor from const char*.
    return std::make_unique<GooString>(s.c_str());
  }

  static std::string MakeDefinitelyNonexistentPath() {
    std::error_code ec;
    const auto tmp = std::filesystem::temp_directory_path(ec);
    const std::filesystem::path base = ec ? std::filesystem::current_path() : tmp;

    const std::filesystem::path p =
        base / "poppler_pdfdoc_isok_946__this_file_should_not_exist__9b0d0f54-77e0-4d7b-9d9e-acdeff01f2c3.pdf";

    // Ensure it doesn't exist even if something odd created it.
    std::filesystem::remove(p, ec);
    return p.string();
  }
};

TEST_F(PDFDocTest_946, ErrorPDFDocReturnsNotOk_946) {
  auto fileName = MakeGooString("error_doc_946.pdf");
  auto doc = PDFDoc::ErrorPDFDoc(123, std::move(fileName));

  ASSERT_NE(doc, nullptr);
  EXPECT_FALSE(doc->isOk());
}

TEST_F(PDFDocTest_946, ConstructWithNonexistentFileIsNotOk_946) {
  const std::string path = MakeDefinitelyNonexistentPath();

  std::unique_ptr<PDFDoc> doc;
  EXPECT_NO_THROW({
    doc = std::make_unique<PDFDoc>(
        MakeGooString(path),
        std::optional<GooString>{}, // ownerPassword
        std::optional<GooString>{}, // userPassword
        []() {}                     // xrefReconstructedCallback
    );
  });

  ASSERT_NE(doc, nullptr);
  EXPECT_FALSE(doc->isOk());
}

TEST_F(PDFDocTest_946, IsOkIsStableAcrossMultipleCalls_946) {
  auto doc = PDFDoc::ErrorPDFDoc(7, MakeGooString("stable_946.pdf"));
  ASSERT_NE(doc, nullptr);

  const bool first = doc->isOk();
  const bool second = doc->isOk();
  const bool third = doc->isOk();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(PDFDocTest_946, ErrorPDFDocAcceptsBoundaryErrorCodes_946) {
  const int codes[] = {0, -1, INT_MAX, INT_MIN};

  for (int code : codes) {
    auto doc = PDFDoc::ErrorPDFDoc(code, MakeGooString("boundary_946.pdf"));
    ASSERT_NE(doc, nullptr);
    // Observable behavior via interface: should be callable without crashing.
    (void)doc->isOk();
  }
}

TEST_F(PDFDocTest_946, IsOkCallableOnConstObject_946) {
  auto doc = PDFDoc::ErrorPDFDoc(55, MakeGooString("const_946.pdf"));
  ASSERT_NE(doc, nullptr);

  const PDFDoc &cref = *doc;
  EXPECT_FALSE(cref.isOk());
}

} // namespace