// StructElement_appendChild_tests_1707.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "GlobalParams.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "StructElement.h"
#include "StructTreeRoot.h"

namespace {

// Poppler uses a global GlobalParams in many builds.
class PopplerGlobalParamsGuard {
public:
  PopplerGlobalParamsGuard() {
    if (!globalParams) {
      globalParams = new GlobalParams();
      owns_ = true;
    }
  }
  ~PopplerGlobalParamsGuard() {
    if (owns_) {
      delete globalParams;
      globalParams = nullptr;
    }
  }

private:
  bool owns_ = false;
};

static std::string WriteTempFileOrDie(const std::string &data) {
  // Create a reasonably-unique temp filename.
  // (Good enough for unit tests; avoids platform-specific APIs.)
  std::ostringstream oss;
  oss << "poppler_structelement_appendchild_"
      << std::to_string(static_cast<long long>(std::rand())) << "_"
      << std::to_string(static_cast<long long>(std::rand())) << ".pdf";
  const std::string path = oss.str();

  std::ofstream out(path, std::ios::binary);
  EXPECT_TRUE(out.is_open()) << "Failed to open temp file for writing: " << path;
  out.write(data.data(), static_cast<std::streamsize>(data.size()));
  out.close();

  // Ensure file exists and is non-empty.
  std::ifstream in(path, std::ios::binary);
  EXPECT_TRUE(in.is_open()) << "Failed to open temp file for reading: " << path;
  in.seekg(0, std::ios::end);
  EXPECT_GT(in.tellg(), 0) << "Temp PDF file is empty: " << path;
  in.close();

  return path;
}

static std::string BuildMinimalTaggedPdf() {
  // Build a minimal tagged PDF with a structure tree:
  //
  // StructTreeRoot -> Document (StructElem) -> P (StructElem) -> MCR (MCID=0 on page 1)
  //
  // This is only to obtain real StructElement instances through the public Poppler API.
  const std::string content =
      "q\n"
      "/P <</MCID 0>> BDC\n"
      "BT\n"
      "/F1 12 Tf\n"
      "72 720 Td\n"
      "(Hi) Tj\n"
      "ET\n"
      "EMC\n"
      "Q\n";

  std::vector<std::string> obj(11); // 0 unused; objects 1..10

  obj[1] =
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /StructTreeRoot 5 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      ">>\n"
      "endobj\n";

  obj[2] =
      "2 0 obj\n"
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>\n"
      "endobj\n";

  obj[3] =
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 612 792]\n"
      "   /Resources << /Font << /F1 6 0 R >> >>\n"
      "   /Contents 4 0 R\n"
      "   /StructParents 0\n"
      ">>\n"
      "endobj\n";

  {
    std::ostringstream s;
    s << "4 0 obj\n"
      << "<< /Length " << content.size() << " >>\n"
      << "stream\n"
      << content
      << "endstream\n"
      << "endobj\n";
    obj[4] = s.str();
  }

  obj[5] =
      "5 0 obj\n"
      "<< /Type /StructTreeRoot\n"
      "   /K 7 0 R\n"
      "   /ParentTree 10 0 R\n"
      ">>\n"
      "endobj\n";

  obj[6] =
      "6 0 obj\n"
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
      "endobj\n";

  obj[7] =
      "7 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /Document\n"
      "   /K [8 0 R]\n"
      ">>\n"
      "endobj\n";

  obj[8] =
      "8 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /P\n"
      "   /P 7 0 R\n"
      "   /K 9 0 R\n"
      ">>\n"
      "endobj\n";

  obj[9] =
      "9 0 obj\n"
      "<< /Type /MCR\n"
      "   /Pg 3 0 R\n"
      "   /MCID 0\n"
      ">>\n"
      "endobj\n";

  obj[10] =
      "10 0 obj\n"
      "<< /Nums [0 [9 0 R]] >>\n"
      "endobj\n";

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  // Record offsets for xref.
  std::vector<long long> offsets(11, 0);
  offsets[0] = 0;

  for (int i = 1; i <= 10; ++i) {
    offsets[i] = static_cast<long long>(pdf.tellp());
    pdf << obj[i];
  }

  const long long xrefPos = static_cast<long long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 11\n";
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i <= 10; ++i) {
    // Each xref entry is 10-digit offset, 5-digit generation, 'n'/'f'
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", offsets[i]);
    pdf << buf;
  }

  pdf << "trailer\n";
  pdf << "<< /Size 11\n";
  pdf << "   /Root 1 0 R\n";
  pdf << ">>\n";
  pdf << "startxref\n";
  pdf << xrefPos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static std::unique_ptr<PDFDoc> OpenDocOrDie(const std::string &path) {
  auto fname = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(fname));
  EXPECT_TRUE(doc->isOk()) << "Failed to open generated tagged PDF: " << path;
  return doc;
}

static StructTreeRoot *GetStructTreeRootOrDie(PDFDoc &doc) {
  StructTreeRoot *root = doc.getStructTreeRoot();
  EXPECT_NE(root, nullptr) << "StructTreeRoot is null";
  return root;
}

static StructElement *GetNonContentRootElementOrDie(StructTreeRoot &root) {
  ASSERT_GT(root.getNumChildren(), 0u) << "StructTreeRoot has no children";
  StructElement *e = root.getChild(0);
  ASSERT_NE(e, nullptr);
  EXPECT_TRUE(e->isOk());
  EXPECT_FALSE(e->isContent());
  return e;
}

} // namespace

class StructElementAppendChildTest_1707 : public ::testing::Test {
protected:
  PopplerGlobalParamsGuard guard_;
};

TEST_F(StructElementAppendChildTest_1707, AppendOkChildIncreasesChildCount_1707) {
  const std::string pdfData = BuildMinimalTaggedPdf();
  const std::string path = WriteTempFileOrDie(pdfData);
  auto cleanup = [&]() { std::remove(path.c_str()); };

  auto doc = OpenDocOrDie(path);
  StructTreeRoot *treeRoot = GetStructTreeRootOrDie(*doc);
  StructElement *documentElem = GetNonContentRootElementOrDie(*treeRoot);

  ASSERT_GT(documentElem->getNumChildren(), 0u);
  StructElement *pElem = documentElem->getChild(0);
  ASSERT_NE(pElem, nullptr);
  EXPECT_TRUE(pElem->isOk());

  const unsigned before = documentElem->getNumChildren();
  documentElem->appendChild(pElem);

  const unsigned after = documentElem->getNumChildren();
  EXPECT_EQ(after, before + 1);

  // Observable effect: last child is the one we appended.
  const StructElement *last = documentElem->getChild(static_cast<int>(after - 1));
  EXPECT_EQ(last, pElem);

  cleanup();
}

TEST_F(StructElementAppendChildTest_1707, AppendNullDoesNotChangeChildren_1707) {
  const std::string pdfData = BuildMinimalTaggedPdf();
  const std::string path = WriteTempFileOrDie(pdfData);
  auto cleanup = [&]() { std::remove(path.c_str()); };

  auto doc = OpenDocOrDie(path);
  StructTreeRoot *treeRoot = GetStructTreeRootOrDie(*doc);
  StructElement *documentElem = GetNonContentRootElementOrDie(*treeRoot);

  const unsigned before = documentElem->getNumChildren();
  documentElem->appendChild(nullptr);
  const unsigned after = documentElem->getNumChildren();

  EXPECT_EQ(after, before);

  cleanup();
}

TEST_F(StructElementAppendChildTest_1707, AppendOnContentElementHasNoEffect_1707) {
  const std::string pdfData = BuildMinimalTaggedPdf();
  const std::string path = WriteTempFileOrDie(pdfData);
  auto cleanup = [&]() { std::remove(path.c_str()); };

  auto doc = OpenDocOrDie(path);
  StructTreeRoot *treeRoot = GetStructTreeRootOrDie(*doc);
  StructElement *documentElem = GetNonContentRootElementOrDie(*treeRoot);

  ASSERT_GT(documentElem->getNumChildren(), 0u);
  StructElement *pElem = documentElem->getChild(0);
  ASSERT_NE(pElem, nullptr);
  EXPECT_FALSE(pElem->isContent());

  // P element should have a content child (MCID reference) in this PDF.
  ASSERT_GT(pElem->getNumChildren(), 0u);
  StructElement *contentElem = pElem->getChild(0);
  ASSERT_NE(contentElem, nullptr);
  EXPECT_TRUE(contentElem->isOk());
  EXPECT_TRUE(contentElem->isContent());

  const unsigned contentBefore = contentElem->getNumChildren();
  const unsigned pBefore = pElem->getNumChildren();

  // Even if we pass an OK element, appending to a content element should not add children.
  contentElem->appendChild(pElem);

  EXPECT_EQ(contentElem->getNumChildren(), contentBefore);
  EXPECT_EQ(pElem->getNumChildren(), pBefore);

  cleanup();
}

TEST_F(StructElementAppendChildTest_1707, BoundaryRepeatedAppendAddsAnotherReference_1707) {
  const std::string pdfData = BuildMinimalTaggedPdf();
  const std::string path = WriteTempFileOrDie(pdfData);
  auto cleanup = [&]() { std::remove(path.c_str()); };

  auto doc = OpenDocOrDie(path);
  StructTreeRoot *treeRoot = GetStructTreeRootOrDie(*doc);
  StructElement *documentElem = GetNonContentRootElementOrDie(*treeRoot);

  ASSERT_GT(documentElem->getNumChildren(), 0u);
  StructElement *pElem = documentElem->getChild(0);
  ASSERT_NE(pElem, nullptr);
  EXPECT_TRUE(pElem->isOk());

  const unsigned before = documentElem->getNumChildren();
  documentElem->appendChild(pElem);
  documentElem->appendChild(pElem);
  const unsigned after = documentElem->getNumChildren();

  EXPECT_EQ(after, before + 2);

  const StructElement *last = documentElem->getChild(static_cast<int>(after - 1));
  const StructElement *secondLast = documentElem->getChild(static_cast<int>(after - 2));
  EXPECT_EQ(last, pElem);
  EXPECT_EQ(secondLast, pElem);

  cleanup();
}