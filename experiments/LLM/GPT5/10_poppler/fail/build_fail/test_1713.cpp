// StructElement_getActualText_1713_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "GlobalParams.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "GooString.h"

// Depending on poppler version, StructTreeRoot may be declared in one of these headers.
// Keep includes minimal and rely on the project include paths.
#include "StructTreeRoot.h"
#include "StructElement.h"

extern GlobalParams *globalParams;

namespace {

std::string WriteTempFile_1713(const std::string &contents, const std::string &basename)
{
  // Use a simple deterministic temp pattern; tests run in controlled environment.
  // If collisions occur, caller can vary basename.
  std::string path = std::string("structelement_1713_") + basename + ".pdf";
  std::ofstream out(path, std::ios::binary);
  out.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  out.close();
  return path;
}

std::string BuildTaggedPdf_1713(bool includeActualText, const std::string &actualTextValue)
{
  // Build a minimal tagged PDF with a StructTreeRoot and a single StructElem whose /K is an MCID.
  // Object layout:
  // 1: Catalog
  // 2: Pages
  // 3: Page (StructParents 0)
  // 4: Contents stream with marked-content using MCID 0
  // 5: ParentTree mapping 0 -> [6 0 R]
  // 6: StructElem (/ActualText optional)
  // 7: StructTreeRoot (K [6 0 R], ParentTree 5 0 R)
  struct Obj {
    int num;
    std::string body;
  };

  const std::string streamData =
      "q\n"
      "/Span <</MCID 0>> BDC\n"
      "0 0 m 10 10 l S\n"
      "EMC\n"
      "Q\n";

  std::vector<Obj> objs;
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 7 0 R /MarkInfo << /Marked true >> >>"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});
  objs.push_back({3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> /StructParents 0 >>"});

  {
    std::ostringstream ss;
    ss << "<< /Length " << streamData.size() << " >>\n"
       << "stream\n"
       << streamData
       << "endstream";
    objs.push_back({4, ss.str()});
  }

  objs.push_back({5, "<< /Nums [ 0 [ 6 0 R ] ] >>"});

  {
    std::ostringstream ss;
    ss << "<< /Type /StructElem /S /Span /P 7 0 R /Pg 3 0 R /K 0";
    if (includeActualText) {
      // Use literal string; keep it simple (no escaping needed for our test values).
      ss << " /ActualText (" << actualTextValue << ")";
    }
    ss << " >>";
    objs.push_back({6, ss.str()});
  }

  objs.push_back({7, "<< /Type /StructTreeRoot /K [ 6 0 R ] /ParentTree 5 0 R >>"});

  // Assemble PDF with correct xref offsets.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<long> offsets(8, 0);
  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(pdf.tellp());
    pdf << o.num << " 0 obj\n" << o.body << "\nendobj\n";
  }

  const long xrefPos = static_cast<long>(pdf.tellp());
  pdf << "xref\n0 8\n";
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i <= 7; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf << buf;
  }
  pdf << "trailer\n<< /Size 8 /Root 1 0 R >>\nstartxref\n" << xrefPos << "\n%%EOF\n";
  return pdf.str();
}

std::unique_ptr<PDFDoc> OpenPdfDoc_1713(const std::string &path)
{
  // PDFDoc historically takes ownership of the GooString* filename in many builds.
  auto *fileName = new GooString(path.c_str());
  auto doc = std::make_unique<PDFDoc>(fileName, nullptr, nullptr);
  return doc;
}

StructTreeRoot *GetStructTreeRoot_1713(PDFDoc *doc)
{
  if (!doc) {
    return nullptr;
  }
  Catalog *cat = doc->getCatalog();
  if (!cat) {
    return nullptr;
  }
  return cat->getStructTreeRoot();
}

} // namespace

class StructElementGetActualTextTest_1713 : public ::testing::Test {
protected:
  static void SetUpTestSuite()
  {
    // Many poppler APIs require globalParams to be initialized.
    if (!globalParams) {
      globalParams = new GlobalParams(nullptr);
    }
  }
};

TEST_F(StructElementGetActualTextTest_1713, NonContentWithActualTextReturnsPointer_1713)
{
  const std::string pdf = BuildTaggedPdf_1713(/*includeActualText=*/true, "ACTUAL_TEXT_1713");
  const std::string path = WriteTempFile_1713(pdf, "with_actualtext");

  auto doc = OpenPdfDoc_1713(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1713(doc.get());
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *elem = root->getChild(0);
  ASSERT_NE(elem, nullptr);

  // For non-content elements, getActualText() should expose the stored ActualText (if present).
  ASSERT_FALSE(elem->isContent());
  const GooString *actual = elem->getActualText();
  ASSERT_NE(actual, nullptr);
  EXPECT_STREQ(actual->c_str(), "ACTUAL_TEXT_1713");
}

TEST_F(StructElementGetActualTextTest_1713, ContentElementAlwaysReturnsNullptr_1713)
{
  const std::string pdf = BuildTaggedPdf_1713(/*includeActualText=*/true, "ACTUAL_TEXT_1713");
  const std::string path = WriteTempFile_1713(pdf, "content_child");

  auto doc = OpenPdfDoc_1713(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1713(doc.get());
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *parent = root->getChild(0);
  ASSERT_NE(parent, nullptr);

  // The StructElem in our PDF uses /K 0 (MCID). Poppler should expose a content child element.
  ASSERT_GE(parent->getNumChildren(), 1u);
  const StructElement *child = parent->getChild(0);
  ASSERT_NE(child, nullptr);

  EXPECT_TRUE(child->isContent());
  EXPECT_EQ(child->getActualText(), nullptr);

  // Repeated calls should remain nullptr (observable stability).
  EXPECT_EQ(child->getActualText(), nullptr);
}

TEST_F(StructElementGetActualTextTest_1713, NonContentWithoutActualTextReturnsNullptr_1713)
{
  const std::string pdf = BuildTaggedPdf_1713(/*includeActualText=*/false, "");
  const std::string path = WriteTempFile_1713(pdf, "without_actualtext");

  auto doc = OpenPdfDoc_1713(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1713(doc.get());
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *elem = root->getChild(0);
  ASSERT_NE(elem, nullptr);

  ASSERT_FALSE(elem->isContent());
  EXPECT_EQ(elem->getActualText(), nullptr);
}

TEST_F(StructElementGetActualTextTest_1713, NonContentActualTextPointerIsStableAcrossCalls_1713)
{
  const std::string pdf = BuildTaggedPdf_1713(/*includeActualText=*/true, "STABLE_PTR_1713");
  const std::string path = WriteTempFile_1713(pdf, "stable_ptr");

  auto doc = OpenPdfDoc_1713(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRoot_1713(doc.get());
  ASSERT_NE(root, nullptr);

  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *elem = root->getChild(0);
  ASSERT_NE(elem, nullptr);

  ASSERT_FALSE(elem->isContent());

  const GooString *a1 = elem->getActualText();
  const GooString *a2 = elem->getActualText();
  ASSERT_NE(a1, nullptr);
  ASSERT_NE(a2, nullptr);

  // Observable behavior: repeated calls should not unexpectedly change result.
  EXPECT_EQ(a1, a2);
  EXPECT_STREQ(a1->c_str(), "STABLE_PTR_1713");
}