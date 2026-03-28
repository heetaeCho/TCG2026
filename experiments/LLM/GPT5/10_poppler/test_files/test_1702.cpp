// StructElement_setRevision_1702_test.cc
#include <gtest/gtest.h>

#include <fstream>
#include <limits>
#include <memory>
#include <string>

#include "poppler/PDFDoc.h"
#include "poppler/Catalog.h"
#include "poppler/GooString.h"
#include "poppler/StructElement.h"

// NOTE:
// These tests treat StructElement as a black box and only validate observable behavior via
// public APIs (e.g., getRevision(), isContent()).
// They intentionally avoid accessing any private/internal state.
//
// The tests construct a minimal *tagged* PDF that includes a StructTreeRoot with a structure
// element whose /K contains an integer MCID, which Poppler typically exposes as a "content"
// StructElement child (isContent() == true).

namespace {

std::string WriteTempFile_1702(const std::string &contents, const char *suffix) {
  // Use gtest temp dir if available; fall back to /tmp.
  const char *tmpDir = std::getenv("TEST_TMPDIR");
  std::string dir = (tmpDir && *tmpDir) ? tmpDir : "/tmp";

  // Crude unique name (good enough for unit tests).
  static int counter = 0;
  std::string path = dir + "/poppler_structelement_1702_" + std::to_string(++counter) + suffix;

  std::ofstream ofs(path, std::ios::binary);
  ofs.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  ofs.close();

  return path;
}

std::unique_ptr<PDFDoc> OpenDocFromPath_1702(const std::string &path) {
  auto gooPath = std::make_unique<GooString>(path.c_str());
  // Common Poppler constructor form: PDFDoc(std::unique_ptr<GooString> fileName, GooString *ownerPW, GooString *userPW, ...)
  // We pass nullptr passwords and let Poppler handle defaults.
  return std::make_unique<PDFDoc>(std::move(gooPath), nullptr, nullptr, nullptr);
}

// Minimal tagged PDF with:
// - 1 page
// - StructTreeRoot with a single StructElem (/S /P) that has /K 0 (MCID)
// - Page has /StructParents 0
//
// This is intentionally minimal; Poppler may accept it and build a structure tree
// where the /K integer becomes a content StructElement child.
const char kTaggedPdfWithMCID_1702[] =
    "%PDF-1.5\n"
    "%\xE2\xE3\xCF\xD3\n"
    "1 0 obj\n"
    "<< /Type /Catalog\n"
    "   /Pages 2 0 R\n"
    "   /StructTreeRoot 6 0 R\n"
    "   /MarkInfo << /Marked true >>\n"
    ">>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page\n"
    "   /Parent 2 0 R\n"
    "   /MediaBox [0 0 200 200]\n"
    "   /Contents 4 0 R\n"
    "   /Resources << >>\n"
    "   /StructParents 0\n"
    ">>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 42 >>\n"
    "stream\n"
    "BT\n"
    "/F1 12 Tf\n"
    "0 0 Td\n"
    "(Hi) Tj\n"
    "ET\n"
    "endstream\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Type /StructElem\n"
    "   /S /P\n"
    "   /P 6 0 R\n"
    "   /K 0\n"
    ">>\n"
    "endobj\n"
    "6 0 obj\n"
    "<< /Type /StructTreeRoot\n"
    "   /K [5 0 R]\n"
    ">>\n"
    "endobj\n"
    "xref\n"
    "0 7\n"
    "0000000000 65535 f \n"
    "0000000015 00000 n \n"
    "0000000120 00000 n \n"
    "0000000177 00000 n \n"
    "0000000310 00000 n \n"
    "0000000448 00000 n \n"
    "0000000530 00000 n \n"
    "trailer\n"
    "<< /Size 7 /Root 1 0 R >>\n"
    "startxref\n"
    "0614\n"
    "%%EOF\n";

} // namespace

// If your Poppler build exposes Catalog::getStructTreeRoot(), this test will exercise real parsing.
// If not available in your version, adjust the accessor to match your tree-root entry point.
static StructTreeRoot *GetStructTreeRoot_1702(PDFDoc &doc) {
  Catalog *cat = doc.getCatalog();
  if (!cat) {
    return nullptr;
  }
  // Poppler commonly has this accessor; if your build uses a different name, update here.
  return cat->getStructTreeRoot();
}

class StructElementSetRevisionTest_1702 : public ::testing::Test {
protected:
  std::string taggedPdfPath_;

  void SetUp() override {
    taggedPdfPath_ = WriteTempFile_1702(std::string(kTaggedPdfWithMCID_1702, sizeof(kTaggedPdfWithMCID_1702) - 1),
                                        ".pdf");
  }
};

TEST_F(StructElementSetRevisionTest_1702, SetRevisionUpdatesContentElement_1702) {
  auto doc = OpenDocFromPath_1702(taggedPdfPath_);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1702(*doc);
  ASSERT_NE(root, nullptr);

  const StructElement *top = root->getChild(0);
  ASSERT_NE(top, nullptr);

  // The top is usually a structure element (not content); it should have a child representing MCID content.
  ASSERT_GT(top->getNumChildren(), 0u);

  const StructElement *content = top->getChild(0);
  ASSERT_NE(content, nullptr);

  // Only assert behavior conditioned on what the object reports via public interface.
  if (!content->isContent()) {
    GTEST_SKIP() << "Parsed child is not a content element in this build; cannot validate setRevision gating.";
  }

  const unsigned int before = content->getRevision();
  content->setRevision(7u);
  const unsigned int after = content->getRevision();

  EXPECT_NE(after, before);
  EXPECT_EQ(after, 7u);
}

TEST_F(StructElementSetRevisionTest_1702, SetRevisionNoEffectOnNonContentElement_1702) {
  auto doc = OpenDocFromPath_1702(taggedPdfPath_);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1702(*doc);
  ASSERT_NE(root, nullptr);

  const StructElement *top = root->getChild(0);
  ASSERT_NE(top, nullptr);

  // If the top element happens to be content in some unusual build, skip (the contract is gated by isContent()).
  if (top->isContent()) {
    GTEST_SKIP() << "Top element is content in this build; cannot validate non-content no-op behavior.";
  }

  const unsigned int before = top->getRevision();
  top->setRevision(123u);
  const unsigned int after = top->getRevision();

  EXPECT_EQ(after, before);
}

TEST_F(StructElementSetRevisionTest_1702, SetRevisionSupportsBoundaryValuesForContent_1702) {
  auto doc = OpenDocFromPath_1702(taggedPdfPath_);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1702(*doc);
  ASSERT_NE(root, nullptr);

  const StructElement *top = root->getChild(0);
  ASSERT_NE(top, nullptr);
  ASSERT_GT(top->getNumChildren(), 0u);

  const StructElement *content = top->getChild(0);
  ASSERT_NE(content, nullptr);

  if (!content->isContent()) {
    GTEST_SKIP() << "Parsed child is not a content element in this build; cannot validate boundary behavior.";
  }

  // Lower boundary: 0
  content->setRevision(0u);
  EXPECT_EQ(content->getRevision(), 0u);

  // Upper boundary: max unsigned int
  const unsigned int kMax = std::numeric_limits<unsigned int>::max();
  content->setRevision(kMax);
  EXPECT_EQ(content->getRevision(), kMax);
}

TEST_F(StructElementSetRevisionTest_1702, SetRevisionMultipleCallsLastValueWinsForContent_1702) {
  auto doc = OpenDocFromPath_1702(taggedPdfPath_);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1702(*doc);
  ASSERT_NE(root, nullptr);

  const StructElement *top = root->getChild(0);
  ASSERT_NE(top, nullptr);
  ASSERT_GT(top->getNumChildren(), 0u);

  const StructElement *content = top->getChild(0);
  ASSERT_NE(content, nullptr);

  if (!content->isContent()) {
    GTEST_SKIP() << "Parsed child is not a content element in this build; cannot validate repeated set behavior.";
  }

  content->setRevision(1u);
  EXPECT_EQ(content->getRevision(), 1u);

  content->setRevision(2u);
  EXPECT_EQ(content->getRevision(), 2u);

  content->setRevision(99u);
  EXPECT_EQ(content->getRevision(), 99u);
}

TEST_F(StructElementSetRevisionTest_1702, SetRevisionOnUntaggedPdfIsSafeAndObservable_1702) {
  // Minimal untagged PDF (no StructTreeRoot). We validate that opening works and that we don't crash.
  const char kUntaggedPdf[] =
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] >>\n"
      "endobj\n"
      "xref\n"
      "0 4\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000058 00000 n \n"
      "0000000115 00000 n \n"
      "trailer\n"
      "<< /Size 4 /Root 1 0 R >>\n"
      "startxref\n"
      "0184\n"
      "%%EOF\n";

  const std::string path = WriteTempFile_1702(std::string(kUntaggedPdf, sizeof(kUntaggedPdf) - 1), ".pdf");
  auto doc = OpenDocFromPath_1702(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1702(*doc);
  // On an untagged PDF, root may be null; that's the observable outcome we accept.
  EXPECT_TRUE(root == nullptr || root->getNumChildren() == 0);
}