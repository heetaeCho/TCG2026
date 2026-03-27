// StructElement_getTitle_test_1703.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

#include "GlobalParams.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "StructElement.h"
#include "GooString.h"

extern GlobalParams *globalParams;

namespace {

class StructElementGetTitleTest_1703 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Many Poppler entry points expect globalParams to exist.
    if (!globalParams) {
      globalParams = new GlobalParams(nullptr);
    }
  }

  static void TearDownTestSuite() {
    // Keep consistent with other Poppler tests: only delete if we created it.
    // If your harness owns globalParams elsewhere, feel free to remove this.
    delete globalParams;
    globalParams = nullptr;
  }

  static std::string WriteTempPdf(const std::string &contents) {
    // Create a deterministic-ish temp path.
    // If your harness provides a temp helper, you can replace this.
    std::string path = "/tmp/poppler_structelement_getTitle_1703.pdf";
    std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
    ofs.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    ofs.close();
    return path;
  }

  static std::unique_ptr<PDFDoc> OpenDoc(const std::string &path) {
    auto fileName = std::make_unique<GooString>(path.c_str());
    auto doc = std::make_unique<PDFDoc>(fileName.get());
    return doc;
  }

  // A minimal tagged PDF with:
  // - StructTreeRoot (6 0)
  // - A non-content StructElem with Title (5 0): /T (Title1)
  // - A child content reference (7 0) -> should be isContent() == true, getTitle() == nullptr
  // - A child non-content StructElem without title (8 0) -> getTitle() == nullptr
  static std::string BuildPdfWithStructTree() {
    // Note: This is intentionally small; it only needs to be parseable enough
    // for StructTree/StructElement to be created through public APIs.
    return
      "%PDF-1.7\n"
      "%\xE2\xE3\xCF\xD3\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 6 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources << >> /Contents 4 0 R >>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 44 >>\n"
      "stream\n"
      "/P << /MCID 0 >> BDC\n"
      "BT /F1 12 Tf (Hi) Tj ET\n"
      "EMC\n"
      "endstream\n"
      "endobj\n"
      "5 0 obj\n"
      "<< /Type /StructElem /S /P /T (Title1) /P 6 0 R /K [7 0 R 8 0 R] >>\n"
      "endobj\n"
      "6 0 obj\n"
      "<< /Type /StructTreeRoot /K [5 0 R] >>\n"
      "endobj\n"
      "7 0 obj\n"
      "<< /Type /MCR /Pg 3 0 R /MCID 0 >>\n"
      "endobj\n"
      "8 0 obj\n"
      "<< /Type /StructElem /S /Span /P 5 0 R /K 9 0 R >>\n"
      "endobj\n"
      "9 0 obj\n"
      "<< /Type /MCR /Pg 3 0 R /MCID 1 >>\n"
      "endobj\n"
      "xref\n"
      "0 10\n"
      "0000000000 65535 f \n"
      "0000000015 00000 n \n"
      "0000000083 00000 n \n"
      "0000000139 00000 n \n"
      "0000000246 00000 n \n"
      "0000000371 00000 n \n"
      "0000000457 00000 n \n"
      "0000000520 00000 n \n"
      "0000000576 00000 n \n"
      "0000000651 00000 n \n"
      "trailer\n"
      "<< /Size 10 /Root 1 0 R >>\n"
      "startxref\n"
      "0714\n"
      "%%EOF\n";
  }

  static StructTreeRoot *GetStructTreeRoot(PDFDoc *doc) {
    if (!doc) return nullptr;
    if (!doc->isOk()) return nullptr;
    Catalog *cat = doc->getCatalog();
    if (!cat) return nullptr;
    return cat->getStructTreeRoot();
  }

  // Assumes StructTreeRoot provides getNumChildren/getChild similar to StructElement.
  // This matches common Poppler API patterns; adjust if your tree root accessor differs.
  static const StructElement *GetRootChild(StructTreeRoot *root, int idx) {
    if (!root) return nullptr;
    if (idx < 0) return nullptr;
    if (static_cast<unsigned>(idx) >= root->getNumChildren()) return nullptr;
    return root->getChild(idx);
  }
};

TEST_F(StructElementGetTitleTest_1703, NonContentElementWithTitle_ReturnsTitle_1703) {
  const std::string path = WriteTempPdf(BuildPdfWithStructTree());
  auto doc = OpenDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  const StructElement *top = GetRootChild(root, 0);
  ASSERT_NE(top, nullptr);

  // Observable behavior: a non-content element should expose its title.
  ASSERT_FALSE(top->isContent());
  const GooString *title = top->getTitle();
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title->c_str(), "Title1");

  // Calling twice should be stable (no mutation, same observable content).
  const GooString *title2 = top->getTitle();
  ASSERT_NE(title2, nullptr);
  EXPECT_STREQ(title2->c_str(), "Title1");
}

TEST_F(StructElementGetTitleTest_1703, ContentElement_ReturnsNullptr_1703) {
  const std::string path = WriteTempPdf(BuildPdfWithStructTree());
  auto doc = OpenDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  const StructElement *top = GetRootChild(root, 0);
  ASSERT_NE(top, nullptr);

  // Child(0) is expected to be a content item (from /MCR).
  ASSERT_GT(top->getNumChildren(), 0u);
  const StructElement *contentChild = top->getChild(0);
  ASSERT_NE(contentChild, nullptr);

  ASSERT_TRUE(contentChild->isContent());
  EXPECT_EQ(contentChild->getTitle(), nullptr);
}

TEST_F(StructElementGetTitleTest_1703, NonContentElementWithoutTitle_ReturnsNullptr_1703) {
  const std::string path = WriteTempPdf(BuildPdfWithStructTree());
  auto doc = OpenDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  const StructElement *top = GetRootChild(root, 0);
  ASSERT_NE(top, nullptr);

  // Child(1) is expected to be a StructElem without /T.
  ASSERT_GT(top->getNumChildren(), 1u);
  const StructElement *noTitleChild = top->getChild(1);
  ASSERT_NE(noTitleChild, nullptr);

  ASSERT_FALSE(noTitleChild->isContent());
  EXPECT_EQ(noTitleChild->getTitle(), nullptr);
}

TEST_F(StructElementGetTitleTest_1703, NullRootOrOutOfRange_DoesNotCrash_1703) {
  // Boundary / error-ish: calling helper accessors with null or invalid indices.
  EXPECT_EQ(GetRootChild(nullptr, 0), nullptr);

  const std::string path = WriteTempPdf(BuildPdfWithStructTree());
  auto doc = OpenDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  EXPECT_EQ(GetRootChild(root, -1), nullptr);
  EXPECT_EQ(GetRootChild(root, static_cast<int>(root->getNumChildren())), nullptr);
}

} // namespace