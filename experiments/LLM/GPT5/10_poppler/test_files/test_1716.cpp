// StructTreeRoot_getDoc_1716_test.cc
#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <memory>
#include <string>

#include "StructTreeRoot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "XRef.h"

namespace {

std::string WriteMinimalPdfToTempFile_1716() {
  // A tiny, valid PDF (one empty page).
  static const char kPdf[] =
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n"
      "xref\n"
      "0 5\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000058 00000 n \n"
      "0000000115 00000 n \n"
      "0000000202 00000 n \n"
      "trailer\n"
      "<< /Size 5 /Root 1 0 R >>\n"
      "startxref\n"
      "0274\n"
      "%%EOF\n";

  const auto dir = std::filesystem::temp_directory_path();
  const auto path =
      dir / std::filesystem::path("poppler_structtreeroot_getdoc_1716.pdf");

  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(kPdf, static_cast<std::streamsize>(sizeof(kPdf) - 1));
  out.close();

  return path.string();
}

std::unique_ptr<PDFDoc> OpenDoc_1716(const std::string &path) {
  auto gooPath = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(gooPath.get());
  if (!doc->isOk()) {
    return nullptr;
  }
  return doc;
}

Dict MakeEmptyDictForDoc_1716(PDFDoc *doc) {
  // Prefer Dict(XRef*) when available; otherwise fall back to default ctor.
  if constexpr (std::is_constructible_v<Dict, XRef *>) {
    XRef *xref = doc ? doc->getXRef() : nullptr;
    return Dict(xref);
  } else if constexpr (std::is_default_constructible_v<Dict>) {
    return Dict();
  } else {
    static_assert(std::is_default_constructible_v<Dict>,
                  "Dict must be constructible for this test.");
  }
}

class StructTreeRootTest_1716 : public ::testing::Test {
 protected:
  void SetUp() override {
    pdfPath_ = WriteMinimalPdfToTempFile_1716();
    doc_ = OpenDoc_1716(pdfPath_);
  }

  void TearDown() override {
    doc_.reset();
    std::error_code ec;
    std::filesystem::remove(pdfPath_, ec);
  }

  std::string pdfPath_;
  std::unique_ptr<PDFDoc> doc_;
};

}  // namespace

TEST_F(StructTreeRootTest_1716, GetDocReturnsSamePointer_1716) {
  ASSERT_NE(doc_, nullptr);

  Dict rootDict = MakeEmptyDictForDoc_1716(doc_.get());
  StructTreeRoot root(doc_.get(), rootDict);

  EXPECT_EQ(root.getDoc(), doc_.get());
}

TEST_F(StructTreeRootTest_1716, GetDocIsStableAcrossMultipleCalls_1716) {
  ASSERT_NE(doc_, nullptr);

  Dict rootDict = MakeEmptyDictForDoc_1716(doc_.get());
  StructTreeRoot root(doc_.get(), rootDict);

  PDFDoc *first = root.getDoc();
  PDFDoc *second = root.getDoc();
  EXPECT_EQ(first, second);
  EXPECT_EQ(first, doc_.get());
}

TEST_F(StructTreeRootTest_1716, GetDocDifferentInstancesReturnTheirOwnDoc_1716) {
  ASSERT_NE(doc_, nullptr);

  // Open a second document instance from the same file.
  auto doc2 = OpenDoc_1716(pdfPath_);
  ASSERT_NE(doc2, nullptr);
  ASSERT_NE(doc2.get(), doc_.get());

  Dict rootDict1 = MakeEmptyDictForDoc_1716(doc_.get());
  Dict rootDict2 = MakeEmptyDictForDoc_1716(doc2.get());

  StructTreeRoot root1(doc_.get(), rootDict1);
  StructTreeRoot root2(doc2.get(), rootDict2);

  EXPECT_EQ(root1.getDoc(), doc_.get());
  EXPECT_EQ(root2.getDoc(), doc2.get());
  EXPECT_NE(root1.getDoc(), root2.getDoc());
}