// StructElement_getNumChildren_1705_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/Catalog.h"
#include "poppler/StructTreeRoot.h"
#include "poppler/StructElement.h"
#include "poppler/goo/GooString.h"

namespace {

// Writes `data` to a unique temp file and returns the path.
static std::string WriteTempFileOrDie_1705(const std::string &data) {
#ifdef _WIN32
  // Fallback for Windows-like environments (best-effort).
  char tmpPath[L_tmpnam];
  std::tmpnam(tmpPath);
  std::string path = std::string(tmpPath) + "_poppler_struct_1705.pdf";
  std::ofstream ofs(path, std::ios::binary);
  EXPECT_TRUE(ofs.good());
  ofs.write(data.data(), static_cast<std::streamsize>(data.size()));
  ofs.close();
  EXPECT_TRUE(ofs.good());
  return path;
#else
  std::string templ = "/tmp/poppler_struct_1705_XXXXXX.pdf";
  std::vector<char> buf(templ.begin(), templ.end());
  buf.push_back('\0');

  int fd = mkstemps(buf.data(), 4 /* ".pdf" */);
  EXPECT_NE(fd, -1);
  if (fd == -1) {
    return {};
  }

  FILE *f = fdopen(fd, "wb");
  EXPECT_NE(f, nullptr);
  if (!f) {
    close(fd);
    return {};
  }

  size_t written = fwrite(data.data(), 1, data.size(), f);
  EXPECT_EQ(written, data.size());
  fclose(f);

  return std::string(buf.data());
#endif
}

static std::string BuildTaggedPdf_1705(unsigned numKids, bool emptyKidsArray) {
  // Minimal tagged PDF with /StructTreeRoot and one parent StructElem containing `numKids` kids.
  // Each kid is a StructElem with /K N (MCID), so those kid elements are "content" elements.
  std::ostringstream pdf;
  std::vector<long> offsets;
  offsets.reserve(32);

  auto put = [&](int objNum, int gen, const std::string &body) {
    offsets.resize(std::max<size_t>(offsets.size(), static_cast<size_t>(objNum + 1)), -1);
    offsets[objNum] = static_cast<long>(pdf.tellp());
    pdf << objNum << " " << gen << " obj\n" << body << "\nendobj\n";
  };

  // PDF header
  pdf << "%PDF-1.5\n%\xE2\xE3\xCF\xD3\n";

  // 4 0 stream: add marked-content sequences to look realistic (MCID 0..numKids-1).
  std::ostringstream content;
  for (unsigned i = 0; i < numKids; ++i) {
    content << "/Span <</MCID " << i << ">> BDC\nEMC\n";
  }
  const std::string contentStr = content.str();

  // Objects:
  // 1 Catalog, 2 Pages, 3 Page, 4 Contents, 6 StructTreeRoot, 5 Parent StructElem, 7.. kids
  put(1, 0,
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /StructTreeRoot 6 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      ">>");

  put(2, 0,
      "<< /Type /Pages\n"
      "   /Count 1\n"
      "   /Kids [3 0 R]\n"
      ">>");

  put(3, 0,
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << >>\n"
      "   /StructParents 0\n"
      ">>");

  {
    std::ostringstream body;
    body << "<< /Length " << contentStr.size() << " >>\n"
         << "stream\n"
         << contentStr
         << "endstream";
    put(4, 0, body.str());
  }

  // StructTreeRoot: /K [5 0 R]
  put(6, 0,
      "<< /Type /StructTreeRoot\n"
      "   /K [5 0 R]\n"
      ">>");

  // Parent StructElem 5: /K [7 0 R ...]
  {
    std::ostringstream k;
    if (emptyKidsArray) {
      k << "   /K []\n";
    } else {
      k << "   /K [";
      for (unsigned i = 0; i < numKids; ++i) {
        int kidObj = 7 + static_cast<int>(i);
        k << kidObj << " 0 R";
        if (i + 1 < numKids) k << " ";
      }
      k << "]\n";
    }

    std::ostringstream body;
    body << "<< /Type /StructElem\n"
         << "   /S /P\n"
         << "   /P 6 0 R\n"
         << k.str()
         << ">>";
    put(5, 0, body.str());
  }

  // Kids 7..: StructElem with /K (MCID i) and /Pg 3 0 R
  if (!emptyKidsArray) {
    for (unsigned i = 0; i < numKids; ++i) {
      int kidObj = 7 + static_cast<int>(i);
      std::ostringstream body;
      body << "<< /Type /StructElem\n"
           << "   /S /Span\n"
           << "   /P 5 0 R\n"
           << "   /K " << i << "\n"
           << "   /Pg 3 0 R\n"
           << ">>";
      put(kidObj, 0, body.str());
    }
  }

  // xref
  long xrefPos = static_cast<long>(pdf.tellp());
  int maxObj = static_cast<int>(offsets.size()) - 1;
  if (maxObj < 6) maxObj = 6;

  pdf << "xref\n";
  pdf << "0 " << (maxObj + 1) << "\n";
  pdf << "0000000000 65535 f \n";

  for (int i = 1; i <= maxObj; ++i) {
    long off = (i < static_cast<int>(offsets.size())) ? offsets[i] : -1;
    if (off < 0) {
      // Unused object slot
      pdf << "0000000000 65535 f \n";
    } else {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off);
      pdf << buf;
    }
  }

  // trailer
  pdf << "trailer\n"
      << "<< /Size " << (maxObj + 1) << "\n"
      << "   /Root 1 0 R\n"
      << ">>\n"
      << "startxref\n"
      << xrefPos << "\n"
      << "%%EOF\n";

  return pdf.str();
}

static std::unique_ptr<PDFDoc> OpenDocOrNull_1705(const std::string &path) {
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  if (!doc || !doc->isOk()) {
    return nullptr;
  }
  return doc;
}

}  // namespace

class StructElementTest_1705 : public ::testing::Test {};

TEST_F(StructElementTest_1705, GetNumChildren_ForNonContentParentMatchesParsedKids_1705) {
  const std::string pdfData = BuildTaggedPdf_1705(/*numKids=*/2, /*emptyKidsArray=*/false);
  const std::string path = WriteTempFileOrDie_1705(pdfData);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocOrNull_1705(path);
  ASSERT_NE(doc, nullptr);

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  StructTreeRoot *root = catalog->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *parent = root->getChild(0);
  ASSERT_NE(parent, nullptr);

  // Parent is a non-content StructElem with 2 kids.
  EXPECT_EQ(parent->getNumChildren(), 2u);
}

TEST_F(StructElementTest_1705, GetNumChildren_ForContentChildIsZero_1705) {
  const std::string pdfData = BuildTaggedPdf_1705(/*numKids=*/1, /*emptyKidsArray=*/false);
  const std::string path = WriteTempFileOrDie_1705(pdfData);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocOrNull_1705(path);
  ASSERT_NE(doc, nullptr);

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  StructTreeRoot *root = catalog->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *parent = root->getChild(0);
  ASSERT_NE(parent, nullptr);
  ASSERT_EQ(parent->getNumChildren(), 1u);

  const StructElement *child = parent->getChild(0);
  ASSERT_NE(child, nullptr);

  // Child uses an MCID (/K N) and is expected to be treated as "content".
  ASSERT_TRUE(child->isContent());
  EXPECT_EQ(child->getNumChildren(), 0u);
}

TEST_F(StructElementTest_1705, GetNumChildren_WhenKidsArrayEmptyReturnsZero_1705) {
  const std::string pdfData = BuildTaggedPdf_1705(/*numKids=*/0, /*emptyKidsArray=*/true);
  const std::string path = WriteTempFileOrDie_1705(pdfData);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocOrNull_1705(path);
  ASSERT_NE(doc, nullptr);

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  StructTreeRoot *root = catalog->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *parent = root->getChild(0);
  ASSERT_NE(parent, nullptr);

  // Boundary: non-content element with no kids.
  EXPECT_EQ(parent->getNumChildren(), 0u);
}