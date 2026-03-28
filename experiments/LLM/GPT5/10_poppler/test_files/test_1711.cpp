// TEST_ID: 1711
// File: StructElement_appendAttribute_ut_1711.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

#include "PDFDoc.h"
#include "Catalog.h"
#include "Object.h"
#include "GooString.h"

#include "StructTreeRoot.h"
#include "StructElement.h"

// NOTE:
// - These tests treat StructElement as a black box and verify behavior only via the public API
//   (getNumAttributes/getAttribute/isContent/etc).
// - appendAttribute(Attribute*) is expected to append only when (!isContent() && attribute != nullptr).

namespace {

class StructElementAppendAttributeTest_1711 : public ::testing::Test {
protected:
  void SetUp() override {
    // Minimal PDF containing a structure tree:
    // StructTreeRoot -> Document (StructElem) -> children: [ P (StructElem), 0 (MCID content element) ]
    //
    // This allows us to obtain:
    // - a non-content StructElement (the /P element)
    // - a content StructElement (the MCID-based content element)
    const std::string pdf = MakeMinimalStructTreePdf();
    pdfPath = WriteTempPdf(pdf);
    ASSERT_FALSE(pdfPath.empty());

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(pdfPath.c_str()));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    // Poppler exposes the structure tree root through Catalog in typical builds.
    // If your tree root accessor differs, adjust here to match your codebase.
    treeRoot = catalog->getStructTreeRoot();
    ASSERT_NE(treeRoot, nullptr);
  }

  void TearDown() override {
    doc.reset();
    if (!pdfPath.empty()) {
      std::remove(pdfPath.c_str());
    }
  }

  static std::string MakeMinimalStructTreePdf() {
    // A tiny valid PDF with:
    // 1 0: Catalog with /StructTreeRoot 2 0 R
    // 2 0: StructTreeRoot with /K 4 0 R
    // 4 0: StructElem /S /Document /K [5 0 R 0]
    // 5 0: StructElem /S /P
    // plus a single page.
    //
    // Offsets are computed by writing the file as a single string; we keep it simple by
    // using a classic "xref with placeholder offsets" technique is not acceptable in strict parsers,
    // so we generate proper offsets here.
    //
    // For unit tests, Poppler is usually tolerant, but we still build correct xref offsets.
    struct Obj {
      int num;
      std::string body;
      long offset = 0;
    };

    std::vector<Obj> objs;
    objs.push_back({1,
                    "<< /Type /Catalog /Pages 3 0 R /StructTreeRoot 2 0 R >>"});
    objs.push_back({2,
                    "<< /Type /StructTreeRoot /K 4 0 R >>"});
    objs.push_back({3,
                    "<< /Type /Pages /Kids [6 0 R] /Count 1 >>"});
    objs.push_back({4,
                    "<< /Type /StructElem /S /Document /P 2 0 R /K [5 0 R 0] >>"});
    objs.push_back({5,
                    "<< /Type /StructElem /S /P /P 4 0 R >>"});
    objs.push_back({6,
                    "<< /Type /Page /Parent 3 0 R /MediaBox [0 0 100 100] /Contents 7 0 R >>"});
    // Empty content stream
    objs.push_back({7,
                    "<< /Length 0 >>\nstream\n\nendstream"});

    std::string out;
    out += "%PDF-1.7\n";

    // Write objects while recording byte offsets.
    for (auto &o : objs) {
      o.offset = static_cast<long>(out.size());
      out += std::to_string(o.num) + " 0 obj\n";
      out += o.body + "\n";
      out += "endobj\n";
    }

    const long xrefOffset = static_cast<long>(out.size());
    out += "xref\n";
    out += "0 8\n";
    out += "0000000000 65535 f \n";
    for (const auto &o : objs) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", o.offset);
      out += buf;
    }

    out += "trailer\n";
    out += "<< /Size 8 /Root 1 0 R >>\n";
    out += "startxref\n";
    out += std::to_string(xrefOffset) + "\n";
    out += "%%EOF\n";
    return out;
  }

  static std::string WriteTempPdf(const std::string &bytes) {
    // Write to a predictable temp location; unique enough for unit test environments.
    // If your harness provides a temp helper, you can replace this.
    std::string path = "poppler_structelement_appendAttribute_1711.pdf";
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs.is_open()) {
      return "";
    }
    ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    ofs.close();
    return path;
  }

  const StructElement *GetDocumentElement() const {
    // Commonly, the root exposes top-level element(s).
    // Adjust if your StructTreeRoot API differs.
    ASSERT_NE(treeRoot, nullptr);
    ASSERT_GT(treeRoot->getNumChildren(), 0u);
    const StructElement *docElem = treeRoot->getChild(0);
    return docElem;
  }

  const StructElement *GetFirstNonContentChildUnderDocument() const {
    const StructElement *docElem = GetDocumentElement();
    if (!docElem) return nullptr;

    // Document has children [ P (struct), MCID content ]
    if (docElem->getNumChildren() == 0) return nullptr;

    const StructElement *child0 = docElem->getChild(0);
    return child0;
  }

  const StructElement *GetFirstContentChildUnderDocument() const {
    const StructElement *docElem = GetDocumentElement();
    if (!docElem) return nullptr;

    // Find a child that reports isContent() == true.
    for (unsigned i = 0; i < docElem->getNumChildren(); ++i) {
      const StructElement *ch = docElem->getChild(static_cast<int>(i));
      if (ch && ch->isContent()) {
        return ch;
      }
    }
    return nullptr;
  }

protected:
  std::string pdfPath;
  std::unique_ptr<PDFDoc> doc;
  StructTreeRoot *treeRoot = nullptr;
};

TEST_F(StructElementAppendAttributeTest_1711, NonContentAppendsAttribute_1711) {
  const StructElement *nonContent = GetFirstNonContentChildUnderDocument();
  ASSERT_NE(nonContent, nullptr);
  ASSERT_FALSE(nonContent->isContent());

  const unsigned before = nonContent->getNumAttributes();

  Object val;
  val.initInt(123);
  auto *attr = new Attribute(GooString("TestAttr1711"), &val);

  nonContent->appendAttribute(attr);

  const unsigned after = nonContent->getNumAttributes();
  EXPECT_EQ(after, before + 1);

  const Attribute *last = nonContent->getAttribute(static_cast<int>(after - 1));
  ASSERT_NE(last, nullptr);
  ASSERT_NE(last->getName(), nullptr);
  EXPECT_STREQ(last->getName(), "TestAttr1711");
}

TEST_F(StructElementAppendAttributeTest_1711, ContentDoesNotAppendAttribute_1711) {
  const StructElement *content = GetFirstContentChildUnderDocument();
  ASSERT_NE(content, nullptr);
  ASSERT_TRUE(content->isContent());

  const unsigned before = content->getNumAttributes();

  Object val;
  val.initInt(7);
  auto *attr = new Attribute(GooString("ShouldNotAppend1711"), &val);

  content->appendAttribute(attr);

  const unsigned after = content->getNumAttributes();
  EXPECT_EQ(after, before);

  // NOTE: We intentionally do not delete attr here. Ownership/lifetime is managed by Poppler
  // for appended attributes, and for non-appended it may still be safe to leak in unit tests.
  // If your project requires no leaks, wrap Attribute with a test-owned smart pointer AND
  // only release() when you observe it was appended.
}

TEST_F(StructElementAppendAttributeTest_1711, NullAttributeDoesNotChangeCount_1711) {
  const StructElement *nonContent = GetFirstNonContentChildUnderDocument();
  ASSERT_NE(nonContent, nullptr);
  ASSERT_FALSE(nonContent->isContent());

  const unsigned before = nonContent->getNumAttributes();

  nonContent->appendAttribute(nullptr);

  const unsigned after = nonContent->getNumAttributes();
  EXPECT_EQ(after, before);
}

TEST_F(StructElementAppendAttributeTest_1711, MultipleAppendsIncreaseCountAndPreserveOrder_1711) {
  const StructElement *nonContent = GetFirstNonContentChildUnderDocument();
  ASSERT_NE(nonContent, nullptr);
  ASSERT_FALSE(nonContent->isContent());

  const unsigned before = nonContent->getNumAttributes();

  Object v1, v2;
  v1.initInt(1);
  v2.initInt(2);

  auto *a1 = new Attribute(GooString("A1_1711"), &v1);
  auto *a2 = new Attribute(GooString("A2_1711"), &v2);

  nonContent->appendAttribute(a1);
  nonContent->appendAttribute(a2);

  const unsigned after = nonContent->getNumAttributes();
  EXPECT_EQ(after, before + 2);

  const Attribute *last1 = nonContent->getAttribute(static_cast<int>(after - 2));
  const Attribute *last2 = nonContent->getAttribute(static_cast<int>(after - 1));

  ASSERT_NE(last1, nullptr);
  ASSERT_NE(last2, nullptr);
  ASSERT_NE(last1->getName(), nullptr);
  ASSERT_NE(last2->getName(), nullptr);

  EXPECT_STREQ(last1->getName(), "A1_1711");
  EXPECT_STREQ(last2->getName(), "A2_1711");
}

}  // namespace