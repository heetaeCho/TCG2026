// StructElement_getAttribute_1709_test.cc
#include <gtest/gtest.h>

#include <climits>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "GlobalParams.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "StructElement.h"
#include "goo/GooString.h"

// NOTE: These tests treat StructElement as a black box and only validate
// observable behavior through the public interface.

namespace {

std::string BuildMinimalTaggedPdfWithStructTreeAndOneAttribute() {
  // We build a tiny, valid-enough PDF that contains a StructTreeRoot with:
  // - A top StructElem that has one attribute in /A
  // - A child content item represented as an MCID integer in /K
  //
  // The page content includes a marked-content sequence with MCID 0.
  struct Obj {
    int num;
    std::string body;  // WITHOUT "n 0 obj" and "endobj"
  };

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1,
                  "<< /Type /Catalog\n"
                  "   /Pages 2 0 R\n"
                  "   /StructTreeRoot 5 0 R\n"
                  ">>"});

  // 2: Pages
  objs.push_back({2,
                  "<< /Type /Pages\n"
                  "   /Kids [3 0 R]\n"
                  "   /Count 1\n"
                  ">>"});

  // 3: Page
  objs.push_back({3,
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 200 200]\n"
                  "   /Contents 4 0 R\n"
                  "   /Resources << >>\n"
                  ">>"});

  // 4: Contents stream with marked content /MCID 0
  const std::string content =
      "q\n"
      "/P << /MCID 0 >> BDC\n"
      "0 0 m\n"
      "0 0 l\n"
      "EMC\n"
      "Q\n";
  {
    std::ostringstream ss;
    ss << "<< /Length " << content.size() << " >>\n"
       << "stream\n"
       << content
       << "endstream";
    objs.push_back({4, ss.str()});
  }

  // 5: StructTreeRoot
  objs.push_back({5,
                  "<< /Type /StructTreeRoot\n"
                  "   /K [6 0 R]\n"
                  ">>"});

  // 6: StructElem with one attribute and one child MCID=0 in /K
  objs.push_back({6,
                  "<< /Type /StructElem\n"
                  "   /S /P\n"
                  "   /K [0]\n"
                  "   /A [8 0 R]\n"
                  ">>"});

  // 8: Attribute dictionary (keep it simple but plausible)
  objs.push_back({8,
                  "<< /O /Layout\n"
                  "   /Placement /Block\n"
                  ">>"});

  // Build full PDF with xref.
  std::ostringstream out;
  out << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.resize(9, 0);  // index by object number; 0 reserved

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.tellp());
    out << o.num << " 0 obj\n" << o.body << "\nendobj\n";
  }

  const long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 9\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 8; ++i) {
    // Some object numbers are unused (7), but we still emit entries.
    // For unused ones, point to 0 and mark as free-ish is not strictly correct,
    // so instead we ensure every number we used has an offset and unused remains 0.
    // Many parsers tolerate this for simple test PDFs.
    std::ostringstream line;
    line << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
    out << line.str();
  }

  out << "trailer\n";
  out << "<< /Size 9\n"
      << "   /Root 1 0 R\n"
      << ">>\n";
  out << "startxref\n" << xref_pos << "\n%%EOF\n";
  return out.str();
}

std::string WriteTempPdf(const std::string &pdf_bytes) {
  // Create a reasonably unique temp filename in the current working directory.
  // (Avoid platform-specific tmp APIs to keep it portable in CI.)
  static int counter = 0;
  std::ostringstream name;
  name << "structelement_getattribute_1709_" << counter++ << ".pdf";
  const std::string path = name.str();

  std::ofstream ofs(path, std::ios::binary);
  ofs.write(pdf_bytes.data(), static_cast<std::streamsize>(pdf_bytes.size()));
  ofs.close();
  return path;
}

// Attempts to retrieve the first top-level StructElement from the document.
// This uses only likely-public poppler APIs (Catalog -> StructTreeRoot -> child access).
StructElement *GetFirstTopStructElement(PDFDoc &doc) {
  Catalog *cat = doc.getCatalog();
  if (!cat) return nullptr;

  StructTreeRoot *root = cat->getStructTreeRoot();
  if (!root) return nullptr;

  // Common poppler API: StructTreeRoot derives from StructElement-like accessors,
  // or offers getNumChildren()/getChild(). We only use the latter here.
  if (root->getNumChildren() == 0) return nullptr;

  const StructElement *child0 = root->getChild(0);
  return const_cast<StructElement *>(child0);
}

class StructElementGetAttributeTest_1709 : public ::testing::Test {
 protected:
  void SetUp() override {
    globalParams = std::make_unique<GlobalParams>();

    const std::string pdf = BuildMinimalTaggedPdfWithStructTreeAndOneAttribute();
    pdf_path_ = WriteTempPdf(pdf);

    auto fn = std::make_unique<GooString>(pdf_path_.c_str());
    doc_ = std::make_unique<PDFDoc>(fn.release(), nullptr, nullptr);
    ASSERT_TRUE(doc_);
    ASSERT_TRUE(doc_->isOk());
  }

  void TearDown() override {
    doc_.reset();
    // Best-effort cleanup
    if (!pdf_path_.empty()) {
      std::remove(pdf_path_.c_str());
    }
    globalParams.reset();
  }

  std::string pdf_path_;
  std::unique_ptr<PDFDoc> doc_;
};

}  // namespace

TEST_F(StructElementGetAttributeTest_1709, NonContentValidIndexReturnsSamePointerAsNonConst_1709) {
  StructElement *elem = GetFirstTopStructElement(*doc_);
  ASSERT_NE(elem, nullptr);

  // Top-level StructElem should not be a content item.
  ASSERT_FALSE(elem->isContent());

  // We embedded exactly one attribute dictionary in /A.
  ASSERT_GE(elem->getNumAttributes(), 1u);

  const Attribute *a0 = elem->getAttribute(0);
  Attribute *na0 = elem->getNonConstAttribute(0);

  // Observable behavior: both accessors for index 0 should refer to the same attribute object.
  EXPECT_NE(a0, nullptr);
  EXPECT_NE(na0, nullptr);
  EXPECT_EQ(a0, na0);
}

TEST_F(StructElementGetAttributeTest_1709, ContentElementAlwaysReturnsNullptrAndDoesNotThrow_1709) {
  StructElement *elem = GetFirstTopStructElement(*doc_);
  ASSERT_NE(elem, nullptr);
  ASSERT_FALSE(elem->isContent());
  ASSERT_GE(elem->getNumChildren(), 1u);

  const StructElement *child0 = elem->getChild(0);
  ASSERT_NE(child0, nullptr);

  // Our /K contains an MCID integer, which should produce a content element.
  ASSERT_TRUE(child0->isContent());

  EXPECT_NO_THROW({
    EXPECT_EQ(child0->getAttribute(0), nullptr);
  });

  EXPECT_NO_THROW({
    EXPECT_EQ(child0->getAttribute(9999), nullptr);
  });

  EXPECT_NO_THROW({
    EXPECT_EQ(child0->getAttribute(-1), nullptr);
  });

  EXPECT_NO_THROW({
    EXPECT_EQ(child0->getAttribute(INT_MIN), nullptr);
  });
}

TEST_F(StructElementGetAttributeTest_1709, NonContentOutOfRangeThrowsStdOutOfRange_1709) {
  StructElement *elem = GetFirstTopStructElement(*doc_);
  ASSERT_NE(elem, nullptr);
  ASSERT_FALSE(elem->isContent());

  const unsigned int n = elem->getNumAttributes();
  ASSERT_GE(n, 1u);

  // Boundary: exactly at size should be out-of-range.
  EXPECT_THROW(elem->getAttribute(static_cast<int>(n)), std::out_of_range);

  // Negative index should also be out-of-range for non-content elements.
  EXPECT_THROW(elem->getAttribute(-1), std::out_of_range);
}

TEST_F(StructElementGetAttributeTest_1709, NonContentIndexZeroNullptrIsNotExpectedWhenAttributesExist_1709) {
  StructElement *elem = GetFirstTopStructElement(*doc_);
  ASSERT_NE(elem, nullptr);
  ASSERT_FALSE(elem->isContent());

  if (elem->getNumAttributes() == 0) {
    GTEST_SKIP() << "No attributes available in this document; cannot validate non-null behavior.";
  }

  // Normal operation: when attributes exist, index 0 should yield a non-null pointer.
  EXPECT_NE(elem->getAttribute(0), nullptr);
}