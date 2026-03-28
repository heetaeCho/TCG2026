// StructElement_getExpandedAbbr_1704_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/StructTreeRoot.h"
#include "poppler/StructElement.h"
#include "poppler/GooString.h"

namespace {

// Writes `content` to a unique temporary file and returns the file path.
static std::string WriteTempFile_1704(const std::string &content) {
  std::string pathTemplate;
#ifdef _WIN32
  // Fallback for environments where mkstemp isn't available.
  char tmpPath[L_tmpnam];
  std::tmpnam(tmpPath);
  pathTemplate = tmpPath;
  FILE *f = std::fopen(pathTemplate.c_str(), "wb");
  if (!f) {
    return std::string();
  }
  std::fwrite(content.data(), 1, content.size(), f);
  std::fclose(f);
  return pathTemplate;
#else
  pathTemplate = "/tmp/poppler_structelement_1704_XXXXXX";
  std::vector<char> buf(pathTemplate.begin(), pathTemplate.end());
  buf.push_back('\0');

  int fd = ::mkstemp(buf.data());
  if (fd < 0) {
    return std::string();
  }

  FILE *f = ::fdopen(fd, "wb");
  if (!f) {
    ::close(fd);
    return std::string();
  }
  std::fwrite(content.data(), 1, content.size(), f);
  std::fclose(f); // also closes fd
  return std::string(buf.data());
#endif
}

// Builds a minimal PDF with a StructTreeRoot containing two StructElem children:
//  - First StructElem has /E (ExpandedAbbr) and one content child (/K 0).
//  - Second StructElem has no /E and one content child (/K 1).
static std::string BuildTaggedPdfWithExpandedAbbr_1704(const std::string &expandedAbbrLiteral) {
  // PDF objects (1..7). We'll compute xref offsets.
  // NOTE: expandedAbbrLiteral should be a valid PDF literal string token like "(Foo)" or "()".
  std::vector<std::string> objs;
  objs.reserve(8);
  objs.push_back(""); // index 0 unused for convenience

  // 1 0: Catalog
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /StructTreeRoot 5 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      ">>\n"
      "endobj\n");

  // 2 0: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>\n"
      "endobj\n");

  // 3 0: Page
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << >>\n"
      ">>\n"
      "endobj\n");

  // 4 0: Contents stream with two marked-content sequences (MCID 0 and 1).
  const std::string stream =
      "/P <</MCID 0>> BDC\n"
      "EMC\n"
      "/P <</MCID 1>> BDC\n"
      "EMC\n";
  objs.push_back("4 0 obj\n"
                 "<< /Length " +
                 std::to_string(stream.size()) +
                 " >>\n"
                 "stream\n" +
                 stream +
                 "endstream\n"
                 "endobj\n");

  // 5 0: StructTreeRoot with two children
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructTreeRoot\n"
      "   /K [6 0 R 7 0 R]\n"
      ">>\n"
      "endobj\n");

  // 6 0: StructElem with /E and /K 0
  objs.push_back(std::string("6 0 obj\n")
                 << "<< /Type /StructElem\n"
                 << "   /S /P\n"
                 << "   /P 5 0 R\n"
                 << "   /Pg 3 0 R\n"
                 << "   /E " << expandedAbbrLiteral << "\n"
                 << "   /K 0\n"
                 << ">>\n"
                 << "endobj\n");

  // 7 0: StructElem without /E and /K 1
  objs.push_back(
      "7 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /P\n"
      "   /P 5 0 R\n"
      "   /Pg 3 0 R\n"
      "   /K 1\n"
      ">>\n"
      "endobj\n");

  std::string pdf;
  pdf += "%PDF-1.7\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // Offsets for xref. Entry 0 is the free object.
  std::vector<long> offsets(8, 0);

  for (int i = 1; i <= 7; ++i) {
    offsets[i] = static_cast<long>(pdf.size());
    pdf += objs[i];
  }

  const long xrefPos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 8\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 7; ++i) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", offsets[i]);
    pdf += line;
  }
  pdf += "trailer\n";
  pdf += "<< /Size 8 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefPos);
  pdf += "\n%%EOF\n";
  return pdf;
}

static std::unique_ptr<PDFDoc> OpenDocFromPdfString_1704(const std::string &pdfBytes) {
  const std::string path = WriteTempFile_1704(pdfBytes);
  if (path.empty()) {
    return nullptr;
  }
  auto fname = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(fname));
  if (!doc || !doc->isOk()) {
    return nullptr;
  }
  return doc;
}

} // namespace

class StructElementGetExpandedAbbrTest_1704 : public ::testing::Test {};

TEST_F(StructElementGetExpandedAbbrTest_1704, ReturnsExpandedAbbrForNonContentElement_1704) {
  auto doc = OpenDocFromPdfString_1704(BuildTaggedPdfWithExpandedAbbr_1704("(ExpandedAbbrValue)"));
  ASSERT_TRUE(doc);
  const StructTreeRoot *root = doc->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *elem = root->getChild(0);
  ASSERT_NE(elem, nullptr);

  // For a non-content StructElement, getExpandedAbbr() should reflect the /E entry if present.
  const GooString *abbr = elem->getExpandedAbbr();
  ASSERT_NE(abbr, nullptr);
  EXPECT_STREQ(abbr->c_str(), "ExpandedAbbrValue");
}

TEST_F(StructElementGetExpandedAbbrTest_1704, ReturnsNullWhenExpandedAbbrMissing_1704) {
  auto doc = OpenDocFromPdfString_1704(BuildTaggedPdfWithExpandedAbbr_1704("(HasEOnFirstOnly)"));
  ASSERT_TRUE(doc);
  const StructTreeRoot *root = doc->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  // Second element has no /E.
  ASSERT_GE(root->getNumChildren(), 2u);
  const StructElement *elemNoE = root->getChild(1);
  ASSERT_NE(elemNoE, nullptr);

  EXPECT_EQ(elemNoE->getExpandedAbbr(), nullptr);
}

TEST_F(StructElementGetExpandedAbbrTest_1704, ReturnsNullForContentElementsEvenIfParentHasExpandedAbbr_1704) {
  auto doc = OpenDocFromPdfString_1704(BuildTaggedPdfWithExpandedAbbr_1704("(ParentHasE)"));
  ASSERT_TRUE(doc);
  const StructTreeRoot *root = doc->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *parent = root->getChild(0);
  ASSERT_NE(parent, nullptr);

  // The parent is a StructElem dict; its first (and only) child is content (MCID 0).
  ASSERT_GE(parent->getNumChildren(), 1u);
  const StructElement *contentChild = parent->getChild(0);
  ASSERT_NE(contentChild, nullptr);

  // Content elements must not expose expanded abbreviation via getExpandedAbbr().
  EXPECT_EQ(contentChild->getExpandedAbbr(), nullptr);
}

TEST_F(StructElementGetExpandedAbbrTest_1704, HandlesEmptyExpandedAbbrString_1704) {
  auto doc = OpenDocFromPdfString_1704(BuildTaggedPdfWithExpandedAbbr_1704("()"));
  ASSERT_TRUE(doc);
  const StructTreeRoot *root = doc->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *elem = root->getChild(0);
  ASSERT_NE(elem, nullptr);

  const GooString *abbr = elem->getExpandedAbbr();
  ASSERT_NE(abbr, nullptr);
  EXPECT_STREQ(abbr->c_str(), "");
}