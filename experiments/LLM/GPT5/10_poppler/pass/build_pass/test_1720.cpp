// StructTreeRoot_findParentElement_1720_test.cc
#include <gtest/gtest.h>

#include <climits>
#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "PDFDoc.h"
#include "Catalog.h"
#include "StructTreeRoot.h"
#include "goo/GooString.h"

// NOTE:
// - These tests treat Poppler as a black box.
// - We only construct minimal PDF files to exercise the public interface.

namespace {

std::string BuildPdfWithXref(const std::vector<std::pair<int, std::string>> &objects, int rootObjNum, int sizeObjNumPlus1)
{
  std::string pdf;
  pdf += "%PDF-1.7\n";
  pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment

  std::vector<long> offsets(sizeObjNumPlus1, 0);

  for (const auto &kv : objects) {
    const int objNum = kv.first;
    const std::string &body = kv.second;

    offsets[objNum] = static_cast<long>(pdf.size());
    pdf += std::to_string(objNum) + " 0 obj\n";
    pdf += body;
    if (!pdf.empty() && pdf.back() != '\n') {
      pdf += "\n";
    }
    pdf += "endobj\n";
  }

  const long xrefPos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(sizeObjNumPlus1) + "\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i < sizeObjNumPlus1; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<<\n";
  pdf += "/Size " + std::to_string(sizeObjNumPlus1) + "\n";
  pdf += "/Root " + std::to_string(rootObjNum) + " 0 R\n";
  pdf += ">>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefPos) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

// Tagged PDF with StructTreeRoot + ParentTree mapping key 0 -> [ StructElem (4 0 R) ]
std::string BuildTaggedPdfWithParentTree()
{
  // Object layout:
  // 1: Catalog (/StructTreeRoot 2 0 R, /Pages 3 0 R)
  // 2: StructTreeRoot dict (/K [4 0 R], /ParentTree 5 0 R)
  // 3: Pages
  // 4: StructElem child of 2
  // 5: ParentTree number tree (/Nums [0 [4 0 R]])
  // 6: Page
  // 7: Contents stream
  const std::string streamData = "BT /F1 12 Tf ET\n";
  const std::string obj7 =
      "<< /Length " + std::to_string(streamData.size()) + " >>\n"
      "stream\n" +
      streamData +
      "endstream";

  std::vector<std::pair<int, std::string>> objs;
  objs.emplace_back(1, "<< /Type /Catalog /Pages 3 0 R /StructTreeRoot 2 0 R >>");
  objs.emplace_back(2,
                    "<< /Type /StructTreeRoot "
                    "/K [ 4 0 R ] "
                    "/ParentTree 5 0 R >>");
  objs.emplace_back(3, "<< /Type /Pages /Kids [ 6 0 R ] /Count 1 >>");
  objs.emplace_back(4,
                    "<< /Type /StructElem "
                    "/S /P "
                    "/P 2 0 R "
                    "/K 0 >>");
  objs.emplace_back(5, "<< /Nums [ 0 [ 4 0 R ] ] >>");
  objs.emplace_back(6,
                    "<< /Type /Page /Parent 3 0 R "
                    "/MediaBox [0 0 100 100] "
                    "/Contents 7 0 R >>");
  objs.emplace_back(7, obj7);

  return BuildPdfWithXref(objs, /*rootObjNum=*/1, /*size=*/8);
}

// Minimal untagged PDF with just Catalog+Pages+Page+Contents
std::string BuildUntaggedPdf()
{
  const std::string streamData = "BT /F1 12 Tf ET\n";
  const std::string obj4 =
      "<< /Length " + std::to_string(streamData.size()) + " >>\n"
      "stream\n" +
      streamData +
      "endstream";

  std::vector<std::pair<int, std::string>> objs;
  objs.emplace_back(1, "<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back(2, "<< /Type /Pages /Kids [ 3 0 R ] /Count 1 >>");
  objs.emplace_back(3,
                    "<< /Type /Page /Parent 2 0 R "
                    "/MediaBox [0 0 100 100] "
                    "/Contents 4 0 R >>");
  objs.emplace_back(4, obj4);

  return BuildPdfWithXref(objs, /*rootObjNum=*/1, /*size=*/5);
}

std::string WriteTempPdf(const std::string &bytes)
{
  // Create a unique-ish temp filename in the working directory.
  // (Avoid platform-specific mkstemp usage for portability in this test harness.)
  static int counter = 0;
  const std::string path = "poppler_structtreeroot_test_1720_" + std::to_string(counter++) + ".pdf";

  std::ofstream out(path, std::ios::binary);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();
  return path;
}

std::unique_ptr<PDFDoc> LoadDocFromFile(const std::string &path)
{
  auto fname = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(fname));
  if (!doc || !doc->isOk()) {
    return nullptr;
  }
  return doc;
}

const StructTreeRoot *GetStructTreeRootFromDoc(PDFDoc *doc)
{
  if (!doc) {
    return nullptr;
  }
  Catalog *cat = doc->getCatalog();
  if (!cat) {
    return nullptr;
  }
  // Poppler commonly exposes this accessor on Catalog.
  return cat->getStructTreeRoot();
}

class StructTreeRootFindParentElementTest_1720 : public ::testing::Test {
protected:
  void TearDown() override
  {
    for (const auto &p : createdFiles) {
      std::remove(p.c_str());
    }
    createdFiles.clear();
  }

  std::string MakeTemp(const std::string &pdfBytes)
  {
    std::string path = WriteTempPdf(pdfBytes);
    createdFiles.push_back(path);
    return path;
  }

private:
  std::vector<std::string> createdFiles;
};

} // namespace

TEST_F(StructTreeRootFindParentElementTest_1720, ReturnsMatchingElementForExistingKeyAndMcid_1720)
{
  const std::string path = MakeTemp(BuildTaggedPdfWithParentTree());
  auto doc = LoadDocFromFile(path);
  ASSERT_NE(doc, nullptr);

  const StructTreeRoot *root = GetStructTreeRootFromDoc(doc.get());
  ASSERT_NE(root, nullptr);

  // Observable behavior via public API: child exists and parent lookup returns same pointer.
  ASSERT_GE(root->getNumChildren(), 1u);
  const StructElement *child0 = root->getChild(0);
  ASSERT_NE(child0, nullptr);

  const StructElement *found = root->findParentElement(/*key=*/0, /*mcid=*/0);
  EXPECT_EQ(found, child0);
}

TEST_F(StructTreeRootFindParentElementTest_1720, ReturnsNullWhenMcidOutOfRange_1720)
{
  const std::string path = MakeTemp(BuildTaggedPdfWithParentTree());
  auto doc = LoadDocFromFile(path);
  ASSERT_NE(doc, nullptr);

  const StructTreeRoot *root = GetStructTreeRootFromDoc(doc.get());
  ASSERT_NE(root, nullptr);

  // ParentTree maps key 0 to an array of size 1, so mcid 1 and larger must return nullptr.
  EXPECT_EQ(root->findParentElement(/*key=*/0, /*mcid=*/1), nullptr);
  EXPECT_EQ(root->findParentElement(/*key=*/0, /*mcid=*/1000), nullptr);
}

TEST_F(StructTreeRootFindParentElementTest_1720, ReturnsNullWhenKeyNotPresent_1720)
{
  const std::string path = MakeTemp(BuildTaggedPdfWithParentTree());
  auto doc = LoadDocFromFile(path);
  ASSERT_NE(doc, nullptr);

  const StructTreeRoot *root = GetStructTreeRootFromDoc(doc.get());
  ASSERT_NE(root, nullptr);

  EXPECT_EQ(root->findParentElement(/*key=*/1, /*mcid=*/0), nullptr);
  EXPECT_EQ(root->findParentElement(/*key=*/12345, /*mcid=*/0), nullptr);
  EXPECT_EQ(root->findParentElement(/*key=*/-1, /*mcid=*/0), nullptr);
}

TEST_F(StructTreeRootFindParentElementTest_1720, BoundaryKeyValuesDoNotCrashAndReturnNull_1720)
{
  const std::string path = MakeTemp(BuildTaggedPdfWithParentTree());
  auto doc = LoadDocFromFile(path);
  ASSERT_NE(doc, nullptr);

  const StructTreeRoot *root = GetStructTreeRootFromDoc(doc.get());
  ASSERT_NE(root, nullptr);

  EXPECT_EQ(root->findParentElement(INT_MIN, 0), nullptr);
  EXPECT_EQ(root->findParentElement(INT_MAX, 0), nullptr);
}

TEST_F(StructTreeRootFindParentElementTest_1720, UntaggedPdfHasNoStructTreeRoot_1720)
{
  const std::string path = MakeTemp(BuildUntaggedPdf());
  auto doc = LoadDocFromFile(path);
  ASSERT_NE(doc, nullptr);

  const StructTreeRoot *root = GetStructTreeRootFromDoc(doc.get());
  // Observable: no StructTreeRoot present in catalog for untagged PDF.
  EXPECT_EQ(root, nullptr);
}