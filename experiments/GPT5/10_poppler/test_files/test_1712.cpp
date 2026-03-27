#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "GlobalParams.h"
#include "PDFDoc.h"
#include "StructTreeRoot.h"
#include "StructElement.h"
#include "GooString.h"

class StructElementGetAltTextTest_1712 : public ::testing::Test {
protected:
  void SetUp() override {
    // Many Poppler entry points expect globalParams to be initialized.
    globalParams = std::make_unique<GlobalParams>();
  }

  static std::string BuildPdfFromObjects(const std::vector<std::string> &objects) {
    // objects is 1-based logically: objects[0] is "1 0 obj ... endobj"
    std::ostringstream out;
    out << "%PDF-1.5\n";

    std::vector<long> offsets;
    offsets.reserve(objects.size() + 1);
    offsets.push_back(0); // object 0 is the free entry

    for (const auto &obj : objects) {
      offsets.push_back(static_cast<long>(out.tellp()));
      out << obj;
      if (!obj.empty() && obj.back() != '\n') {
        out << "\n";
      }
    }

    const long xrefPos = static_cast<long>(out.tellp());
    out << "xref\n";
    out << "0 " << (objects.size() + 1) << "\n";
    out << "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      // 10-digit, zero-padded offset as required by classic xref.
      std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
      out << buf << " 00000 n \n";
    }

    out << "trailer\n";
    out << "<< /Size " << (objects.size() + 1) << " /Root 1 0 R >>\n";
    out << "startxref\n";
    out << xrefPos << "\n";
    out << "%%EOF\n";
    return out.str();
  }

  static std::string MakeStreamObject(int objNum, const std::string &streamData) {
    std::ostringstream o;
    o << objNum << " 0 obj\n";
    o << "<< /Length " << streamData.size() << " >>\n";
    o << "stream\n";
    o << streamData;
    if (streamData.empty() || streamData.back() != '\n') {
      o << "\n";
    }
    o << "endstream\n";
    o << "endobj\n";
    return o.str();
  }

  static std::string WriteTempFile(const std::string &bytes, const std::string &suffix) {
    // Use a deterministic-ish filename per test run; sufficient for typical unit test sandboxes.
    std::ostringstream path;
    path << "structelement_getalttext_1712_" << ::getpid() << "_" << suffix << ".pdf";

    std::ofstream f(path.str(), std::ios::binary);
    f.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    f.close();
    return path.str();
  }

  static std::unique_ptr<PDFDoc> OpenDocFromPath(const std::string &path) {
    auto gooPath = std::make_unique<GooString>(path.c_str());
    auto doc = std::make_unique<PDFDoc>(gooPath.get());
    return doc;
  }
};

TEST_F(StructElementGetAltTextTest_1712, ReturnsAltTextForStructElementAndNullForContentChild_1712) {
  // Tagged PDF:
  // - StructTreeRoot -> one StructElem with /Alt (Figure Alt)
  // - StructElem has /K 0 (a marked-content reference), so Poppler exposes a "content" child element.
  const std::string contents =
      "/P <</MCID 0>> BDC\n"
      "EMC\n";

  std::vector<std::string> objs;
  objs.reserve(6);

  // 1: Catalog
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R >>\n"
      "endobj\n");

  // 2: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  // 3: Page
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R /Resources << >> /StructParents 0 >>\n"
      "endobj\n");

  // 4: Contents stream with marked-content sequence (MCID 0)
  objs.push_back(MakeStreamObject(4, contents));

  // 5: StructTreeRoot
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructTreeRoot /K [6 0 R] >>\n"
      "endobj\n");

  // 6: StructElem with Alt and a content item child (MCID 0)
  objs.push_back(
      "6 0 obj\n"
      "<< /Type /StructElem /S /Figure /Pg 3 0 R /Alt (Figure Alt) /K 0 >>\n"
      "endobj\n");

  const std::string pdfBytes = BuildPdfFromObjects(objs);
  const std::string path = WriteTempFile(pdfBytes, "with_alt_and_child");

  std::unique_ptr<PDFDoc> doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  const StructTreeRoot *root = doc->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_EQ(root->getNumChildren(), 1u);
  const StructElement *elem = root->getChild(0);
  ASSERT_NE(elem, nullptr);
  ASSERT_TRUE(elem->isOk());

  // Non-content StructElem: should return its /Alt.
  const GooString *alt = elem->getAltText();
  ASSERT_NE(alt, nullptr);
  EXPECT_STREQ(alt->c_str(), "Figure Alt");

  // Its child is a content item (from /K 0): getAltText() must return nullptr.
  ASSERT_GE(elem->getNumChildren(), 1u);
  const StructElement *child = elem->getChild(0);
  ASSERT_NE(child, nullptr);
  EXPECT_TRUE(child->isContent());
  EXPECT_EQ(child->getAltText(), nullptr);
}

TEST_F(StructElementGetAltTextTest_1712, ReturnsNullWhenAltIsMissingOnStructElement_1712) {
  // Same as above, but omit /Alt from the StructElem.
  const std::string contents =
      "/P <</MCID 0>> BDC\n"
      "EMC\n";

  std::vector<std::string> objs;
  objs.reserve(6);

  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R >>\n"
      "endobj\n");
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R /Resources << >> /StructParents 0 >>\n"
      "endobj\n");
  objs.push_back(MakeStreamObject(4, contents));
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructTreeRoot /K [6 0 R] >>\n"
      "endobj\n");
  objs.push_back(
      "6 0 obj\n"
      "<< /Type /StructElem /S /Figure /Pg 3 0 R /K 0 >>\n"
      "endobj\n");

  const std::string pdfBytes = BuildPdfFromObjects(objs);
  const std::string path = WriteTempFile(pdfBytes, "no_alt");

  std::unique_ptr<PDFDoc> doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  const StructTreeRoot *root = doc->getStructTreeRoot();
  ASSERT_NE(root, nullptr);

  ASSERT_EQ(root->getNumChildren(), 1u);
  const StructElement *elem = root->getChild(0);
  ASSERT_NE(elem, nullptr);
  ASSERT_TRUE(elem->isOk());

  // StructElem without /Alt should yield nullptr.
  EXPECT_EQ(elem->getAltText(), nullptr);
}

TEST_F(StructElementGetAltTextTest_1712, StructTreeRootAbsentOnUntaggedPdf_1712) {
  // Minimal untagged PDF: no /StructTreeRoot in the Catalog.
  const std::string contents = "q\nQ\n";

  std::vector<std::string> objs;
  objs.reserve(4);

  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R /Resources << >> >>\n"
      "endobj\n");
  objs.push_back(MakeStreamObject(4, contents));

  const std::string pdfBytes = BuildPdfFromObjects(objs);
  const std::string path = WriteTempFile(pdfBytes, "untagged");

  std::unique_ptr<PDFDoc> doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  // Observable error/boundary: no structure tree root present.
  EXPECT_EQ(doc->getStructTreeRoot(), nullptr);
}