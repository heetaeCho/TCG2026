// StructElement_getText_1714_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "GlobalParams.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "StructTreeRoot.h"
#include "StructElement.h"
#include "goo/GooString.h"

namespace {

// Minimal PDF writer (creates a tiny *tagged* PDF with a simple structure tree):
// StructTreeRoot -> StructElem(Sect) -> StructElem(P, MCID 0) -> marked content "Hello"
static std::string CreateTaggedPdfWithText(const std::string &path, const std::string &text) {
  // NOTE: This helper only writes a file; it does NOT interpret Poppler internals.
  // Tests treat Poppler as black-box and only verify observable behavior via public APIs.

  auto escPdfString = [](const std::string &in) -> std::string {
    std::string out;
    out.reserve(in.size());
    for (char c : in) {
      if (c == '\\' || c == '(' || c == ')') out.push_back('\\');
      out.push_back(c);
    }
    return out;
  };

  const std::string escText = escPdfString(text);

  // Build objects (1..9). We'll compute xref offsets precisely.
  // Objects:
  // 1  Catalog with /StructTreeRoot 6 0 R and /MarkInfo marked
  // 2  Pages
  // 3  Page (with /StructParents 0)
  // 4  Font (Helvetica)
  // 5  Contents (marked content with MCID 0 and text)
  // 6  StructTreeRoot (/K [8 0 R], /ParentTree 7 0 R)
  // 7  ParentTree number tree (/Nums [0 [9 0 R]])
  // 8  StructElem /Sect (child [9 0 R])
  // 9  StructElem /P (MCID 0, /Pg 3 0 R, parent 8 0 R)

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  std::vector<long long> offsets;
  offsets.reserve(10);
  offsets.push_back(0);  // xref entry 0

  auto emitObj = [&](int objNum, const std::string &body) {
    offsets.push_back(static_cast<long long>(pdf.tellp()));
    pdf << objNum << " 0 obj\n" << body << "\nendobj\n";
  };

  emitObj(1,
          "<< /Type /Catalog\n"
          "   /Pages 2 0 R\n"
          "   /MarkInfo << /Marked true >>\n"
          "   /StructTreeRoot 6 0 R\n"
          ">>");

  emitObj(2,
          "<< /Type /Pages\n"
          "   /Count 1\n"
          "   /Kids [3 0 R]\n"
          ">>");

  emitObj(3,
          "<< /Type /Page\n"
          "   /Parent 2 0 R\n"
          "   /MediaBox [0 0 612 792]\n"
          "   /Resources << /Font << /F1 4 0 R >> >>\n"
          "   /Contents 5 0 R\n"
          "   /StructParents 0\n"
          ">>");

  emitObj(4,
          "<< /Type /Font\n"
          "   /Subtype /Type1\n"
          "   /BaseFont /Helvetica\n"
          ">>");

  {
    std::ostringstream stream;
    stream << "/P <</MCID 0>> BDC\n"
           << "BT\n"
           << "/F1 12 Tf\n"
           << "72 720 Td\n"
           << "(" << escText << ") Tj\n"
           << "ET\n"
           << "EMC\n";
    const std::string s = stream.str();
    std::ostringstream body;
    body << "<< /Length " << s.size() << " >>\n"
         << "stream\n"
         << s
         << "endstream";
    emitObj(5, body.str());
  }

  emitObj(6,
          "<< /Type /StructTreeRoot\n"
          "   /K [8 0 R]\n"
          "   /ParentTree 7 0 R\n"
          ">>");

  emitObj(7,
          "<< /Nums [ 0 [9 0 R] ] >>");

  emitObj(8,
          "<< /Type /StructElem\n"
          "   /S /Sect\n"
          "   /K [9 0 R]\n"
          ">>");

  emitObj(9,
          "<< /Type /StructElem\n"
          "   /S /P\n"
          "   /P 8 0 R\n"
          "   /Pg 3 0 R\n"
          "   /K 0\n"
          ">>");

  const long long xrefPos = static_cast<long long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (offsets.size()) << "\n";
  // obj 0
  pdf << "0000000000 65535 f \n";
  // objs 1..9
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld", offsets[i]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n"
         "<< /Size "
      << offsets.size()
      << "\n"
         "   /Root 1 0 R\n"
         ">>\n"
         "startxref\n"
      << xrefPos
      << "\n"
         "%%EOF\n";

  std::ofstream out(path, std::ios::binary);
  out << pdf.str();
  out.close();
  return path;
}

static std::string TempPath(const std::string &baseName) {
  // Put in current working directory (portable for typical unit test runs).
  return baseName;
}

static std::string GooToStdString(const GooString *gs) {
  if (!gs) return std::string();
  return std::string(gs->c_str());
}

class StructElementGetTextTest_1714 : public ::testing::Test {
protected:
  void SetUp() override {
    // Many Poppler entry points expect globalParams to exist.
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
      globalParams->setErrQuiet(true);
    }
  }
};

static const StructElement *GetFirstStructElementOrNull(PDFDoc &doc) {
  Catalog *cat = doc.getCatalog();
  if (!cat) return nullptr;

  StructTreeRoot *root = cat->getStructTreeRoot();
  if (!root) return nullptr;

  if (root->getNumChildren() == 0) return nullptr;

  // root->getChild(i) returns const StructElement* in Poppler.
  return root->getChild(0);
}

static const StructElement *FindFirstLeaf(const StructElement *node) {
  if (!node) return nullptr;
  if (node->getNumChildren() == 0) return node;
  for (unsigned i = 0; i < node->getNumChildren(); ++i) {
    const StructElement *child = node->getChild(static_cast<int>(i));
    const StructElement *leaf = FindFirstLeaf(child);
    if (leaf) return leaf;
  }
  return nullptr;
}

}  // namespace

TEST_F(StructElementGetTextTest_1714, GetTextRecursiveReturnsTextContainingHello_1714) {
  const std::string pdfPath = TempPath("structelement_gettext_1714_1.pdf");
  CreateTaggedPdfWithText(pdfPath, "Hello");

  PDFDoc doc(new GooString(pdfPath.c_str()));
  ASSERT_TRUE(doc.isOk());

  const StructElement *elem = GetFirstStructElementOrNull(doc);
  ASSERT_NE(elem, nullptr);

  GooString *txt = elem->getText(true);
  // Observable behavior: should not crash; may return nullptr if no text could be extracted.
  ASSERT_NE(txt, nullptr);

  const std::string s = GooToStdString(txt);
  delete txt;

  // Black-box assertion: Our generated tagged content contains "Hello".
  // If Poppler extracts structure text, it should include that substring.
  EXPECT_NE(s.find("Hello"), std::string::npos);
}

TEST_F(StructElementGetTextTest_1714, GetTextNonRecursiveIsNotLongerThanRecursive_1714) {
  const std::string pdfPath = TempPath("structelement_gettext_1714_2.pdf");
  CreateTaggedPdfWithText(pdfPath, "Hello");

  PDFDoc doc(new GooString(pdfPath.c_str()));
  ASSERT_TRUE(doc.isOk());

  const StructElement *elem = GetFirstStructElementOrNull(doc);
  ASSERT_NE(elem, nullptr);

  GooString *rec = elem->getText(true);
  GooString *nonrec = elem->getText(false);

  // Either pointer may be nullptr depending on what Poppler can extract,
  // but the call must be safe and repeatable.
  const std::string sRec = GooToStdString(rec);
  const std::string sNon = GooToStdString(nonrec);

  delete rec;
  delete nonrec;

  // With recursive=true, it should include at least as much as non-recursive.
  EXPECT_GE(sRec.size(), sNon.size());
  // And recursive should still contain the marked text from our PDF if extraction works.
  if (!sRec.empty()) {
    EXPECT_NE(sRec.find("Hello"), std::string::npos);
  }
}

TEST_F(StructElementGetTextTest_1714, GetTextOnLeafHasSameResultRecursiveAndNonRecursive_1714) {
  const std::string pdfPath = TempPath("structelement_gettext_1714_3.pdf");
  CreateTaggedPdfWithText(pdfPath, "Hello");

  PDFDoc doc(new GooString(pdfPath.c_str()));
  ASSERT_TRUE(doc.isOk());

  const StructElement *rootChild = GetFirstStructElementOrNull(doc);
  ASSERT_NE(rootChild, nullptr);

  const StructElement *leaf = FindFirstLeaf(rootChild);
  ASSERT_NE(leaf, nullptr);
  ASSERT_EQ(leaf->getNumChildren(), 0u);

  GooString *t1 = leaf->getText(true);
  GooString *t2 = leaf->getText(false);

  const std::string s1 = GooToStdString(t1);
  const std::string s2 = GooToStdString(t2);

  delete t1;
  delete t2;

  // Boundary: leaf has no subtree, so recursive flag should not change observable output.
  EXPECT_EQ(s1, s2);
}

TEST_F(StructElementGetTextTest_1714, GetTextIsRepeatableAcrossCalls_1714) {
  const std::string pdfPath = TempPath("structelement_gettext_1714_4.pdf");
  CreateTaggedPdfWithText(pdfPath, "Hello");

  PDFDoc doc(new GooString(pdfPath.c_str()));
  ASSERT_TRUE(doc.isOk());

  const StructElement *elem = GetFirstStructElementOrNull(doc);
  ASSERT_NE(elem, nullptr);

  GooString *a = elem->getText(true);
  GooString *b = elem->getText(true);

  const std::string sa = GooToStdString(a);
  const std::string sb = GooToStdString(b);

  delete a;
  delete b;

  // Observable expectation: repeated calls yield the same extracted text.
  EXPECT_EQ(sa, sb);
}

TEST_F(StructElementGetTextTest_1714, GetTextDoesNotCrashWhenNoStructTreeRoot_1714) {
  // Create an untagged minimal PDF: no /StructTreeRoot, so we can't obtain an element,
  // but the test verifies that the lookup path is safe and does not produce invalid access.
  const std::string pdfPath = TempPath("structelement_gettext_1714_5.pdf");

  {
    // Minimal valid PDF (catalog + pages + page + empty content)
    std::ostringstream pdf;
    pdf << "%PDF-1.4\n";
    std::vector<long long> offsets;
    offsets.push_back(0);

    auto emitObj = [&](int objNum, const std::string &body) {
      offsets.push_back(static_cast<long long>(pdf.tellp()));
      pdf << objNum << " 0 obj\n" << body << "\nendobj\n";
    };

    emitObj(1, "<< /Type /Catalog /Pages 2 0 R >>");
    emitObj(2, "<< /Type /Pages /Count 1 /Kids [3 0 R] >>");
    emitObj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>");

    const long long xrefPos = static_cast<long long>(pdf.tellp());
    pdf << "xref\n0 " << offsets.size() << "\n";
    pdf << "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010lld", offsets[i]);
      pdf << buf << " 00000 n \n";
    }
    pdf << "trailer\n<< /Size " << offsets.size() << " /Root 1 0 R >>\n";
    pdf << "startxref\n" << xrefPos << "\n%%EOF\n";

    std::ofstream out(pdfPath, std::ios::binary);
    out << pdf.str();
  }

  PDFDoc doc(new GooString(pdfPath.c_str()));
  ASSERT_TRUE(doc.isOk());

  // No struct tree -> no element; ensure our traversal doesn't crash and returns nullptr.
  const StructElement *elem = GetFirstStructElementOrNull(doc);
  EXPECT_EQ(elem, nullptr);
}