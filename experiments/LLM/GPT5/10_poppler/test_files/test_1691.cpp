// StructElement_isContent_1691_test.cc
#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "PDFDoc.h"
#include "Catalog.h"
#include "StructElement.h"

// Note: This test treats Poppler as a black box and only uses public APIs.
// It creates small on-disk PDFs so PDFDoc can open them.

namespace {

static std::string WriteTempPdf_1691(const std::string &fileName, const std::string &contents) {
  const std::string path = std::string("structelement_iscontent_1691_") + fileName;
  std::ofstream out(path, std::ios::binary);
  out.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  out.close();
  return path;
}

static std::unique_ptr<PDFDoc> OpenPdf_1691(const std::string &path) {
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  return doc;
}

// Minimal PDF with 1 page, NO StructTreeRoot.
static const char *kPdfNoStructTree_1691 =
    "%PDF-1.7\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 0 >>\n"
    "stream\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 5\n"
    "0000000000 65535 f \n"
    "0000000010 00000 n \n"
    "0000000060 00000 n \n"
    "0000000120 00000 n \n"
    "0000000200 00000 n \n"
    "trailer\n"
    "<< /Size 5 /Root 1 0 R >>\n"
    "startxref\n"
    "270\n"
    "%%EOF\n";

// PDF with StructTreeRoot containing a structure element /P whose kids are:
// - an MCR dict (MCID-based content item)
// - an OBJR dict (object-ref content item)
// Also includes a second structure element child with no kids.
// NOTE: Offsets in xref are dummy; Poppler is typically tolerant with rebuild-xref,
// but if your build is strict, replace with a correctly offset xref PDF builder.
static const char *kPdfWithStructTree_1691 =
    "%PDF-1.7\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 10 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 0 >>\n"
    "stream\n"
    "endstream\n"
    "endobj\n"
    // An arbitrary referenced object for OBJR (/Obj 5 0 R)
    "5 0 obj\n"
    "<< /Type /XObject /Subtype /Form /Length 0 >>\n"
    "stream\n"
    "endstream\n"
    "endobj\n"
    // StructTreeRoot
    "10 0 obj\n"
    "<< /Type /StructTreeRoot /K [11 0 R 12 0 R] >>\n"
    "endobj\n"
    // Struct element /P with kids [MCR, OBJR]
    "11 0 obj\n"
    "<< /Type /StructElem /S /P /K [13 0 R 14 0 R] >>\n"
    "endobj\n"
    // Second struct element (non-content)
    "12 0 obj\n"
    "<< /Type /StructElem /S /Span >>\n"
    "endobj\n"
    // MCR (marked-content reference)
    "13 0 obj\n"
    "<< /Type /MCR /Pg 3 0 R /MCID 0 >>\n"
    "endobj\n"
    // OBJR (object reference)
    "14 0 obj\n"
    "<< /Type /OBJR /Pg 3 0 R /Obj 5 0 R >>\n"
    "endobj\n"
    "xref\n"
    "0 15\n"
    "0000000000 65535 f \n"
    "0000000010 00000 n \n"
    "0000000075 00000 n \n"
    "0000000145 00000 n \n"
    "0000000230 00000 n \n"
    "0000000300 00000 n \n"
    "0000000380 00000 n \n"
    "0000000460 00000 n \n"
    "0000000540 00000 n \n"
    "0000000620 00000 n \n"
    "0000000700 00000 n \n"
    "0000000780 00000 n \n"
    "0000000860 00000 n \n"
    "0000000940 00000 n \n"
    "0000001020 00000 n \n"
    "trailer\n"
    "<< /Size 15 /Root 1 0 R >>\n"
    "startxref\n"
    "1100\n"
    "%%EOF\n";

static StructTreeRoot *GetStructTreeRootOrNull_1691(PDFDoc *doc) {
  if (!doc) return nullptr;
  Catalog *cat = doc->getCatalog();
  if (!cat) return nullptr;
  // Poppler Catalog typically exposes StructTreeRoot via getStructTreeRoot().
  return cat->getStructTreeRoot();
}

}  // namespace

class StructElementIsContentTest_1691 : public ::testing::Test {};

TEST_F(StructElementIsContentTest_1691, NoStructTreeRootReturnsNull_1691) {
  const std::string path = WriteTempPdf_1691("no_struct_tree.pdf", kPdfNoStructTree_1691);
  auto doc = OpenPdf_1691(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRootOrNull_1691(doc.get());
  // Observable behavior: for PDFs without a structure tree, there should be no root object.
  EXPECT_EQ(root, nullptr);
}

TEST_F(StructElementIsContentTest_1691, McrAndObjrAreContentButStructElemIsNot_1691) {
  const std::string path = WriteTempPdf_1691("with_struct_tree.pdf", kPdfWithStructTree_1691);
  auto doc = OpenPdf_1691(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRootOrNull_1691(doc.get());
  ASSERT_NE(root, nullptr);

  // StructTreeRoot is expected to have children that are StructElement* (structure elements).
  // We avoid relying on internal details; we only traverse through public child APIs.
  ASSERT_GE(root->getNumChildren(), 1u);

  const StructElement *structElemP = root->getChild(0);
  ASSERT_NE(structElemP, nullptr);

  // A /StructElem node itself is not a content item; isContent() should be false.
  EXPECT_FALSE(structElemP->isContent());

  // Its children are MCR and OBJR content items.
  ASSERT_GE(structElemP->getNumChildren(), 2u);

  const StructElement *mcr = structElemP->getChild(0);
  const StructElement *objr = structElemP->getChild(1);
  ASSERT_NE(mcr, nullptr);
  ASSERT_NE(objr, nullptr);

  EXPECT_TRUE(mcr->isContent());
  EXPECT_TRUE(objr->isContent());

  // Sanity: MCR should have an MCID; OBJR should be an object ref. These are observable via public APIs.
  EXPECT_GE(mcr->getMCID(), 0);

  EXPECT_TRUE(objr->isObjectRef());
  Ref r = objr->getObjectRef();
  // We don't assume exact values, just that an object reference looks non-nullish.
  EXPECT_NE(r.num, 0);
}

TEST_F(StructElementIsContentTest_1691, BoundaryChildTraversalDoesNotCrash_1691) {
  const std::string path = WriteTempPdf_1691("with_struct_tree_boundary.pdf", kPdfWithStructTree_1691);
  auto doc = OpenPdf_1691(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  StructTreeRoot *root = GetStructTreeRootOrNull_1691(doc.get());
  ASSERT_NE(root, nullptr);

  // Boundary: access the second top-level child (we wrote two).
  ASSERT_GE(root->getNumChildren(), 2u);
  const StructElement *structElemSpan = root->getChild(1);
  ASSERT_NE(structElemSpan, nullptr);

  // A plain structure element (no /K) should not be a content item.
  EXPECT_FALSE(structElemSpan->isContent());

  // Boundary: an element with zero children should report 0 and not crash when queried.
  // (We do not assume what getChild(out-of-range) returns; we only check count.)
  EXPECT_EQ(structElemSpan->getNumChildren(), 0u);
}