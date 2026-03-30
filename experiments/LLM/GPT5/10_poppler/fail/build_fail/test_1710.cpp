//===----------------------------------------------------------------------===//
// StructElement_getNonConstAttribute_1710_test.cpp
// Unit tests for StructElement::getNonConstAttribute(int) using GoogleTest.
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Catalog.h"
#include "StructElement.h"

// Some Poppler builds expose StructTreeRoot in different headers / shapes.
// Try to include common header name if present in the build.
#if __has_include("StructTreeRoot.h")
#include "StructTreeRoot.h"
#endif

namespace {

static std::string WriteMinimalTaggedPdfToTemp_1710() {
  // Build a minimal tagged PDF that Poppler can parse into:
  // - A non-content StructElement (StructElem dict) with one attribute (/A ...)
  // - A content child element created from /K 0 (MCID=0)
  //
  // NOTE: This is a PDF *file* builder (xref + offsets) used only to obtain
  // real StructElement objects through Poppler's public API.

  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page (with StructParents)
  // 4 0 obj: StructTreeRoot
  // 5 0 obj: StructElem (non-content) with /A and /K 0
  // 6 0 obj: Contents stream with marked content MCID 0
  // 7 0 obj: (optional) ParentTree (minimal; not strictly needed for /K integer)
  //
  // Keep it as simple as possible but valid.

  objs.push_back({1,
                  "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 4 0 R >>"});
  objs.push_back({2, "<< /Type /Pages /Count 1 /Kids [3 0 R] >>"});

  // Page resources: a built-in font /Helvetica may work without embedding.
  // Add /StructParents 0 so tagged structures have a parent-tree index.
  objs.push_back(
      {3,
       "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
       "   /Resources << /Font << /F1 << /Type /Font /Subtype /Type1 /BaseFont "
       "/Helvetica >> >> >>\n"
       "   /Contents 6 0 R\n"
       "   /StructParents 0\n"
       ">>"});

  // StructTreeRoot: one kid (the non-content struct element).
  // ParentTree is included with a minimal structure.
  objs.push_back({4, "<< /Type /StructTreeRoot /K [5 0 R] /ParentTree 7 0 R >>"});

  // StructElem: /S /P, points to page, has child marked content id 0.
  // Include one attribute dictionary with /O /Layout so Poppler creates an
  // Attribute object (typically).
  objs.push_back(
      {5,
       "<< /Type /StructElem /S /P /Pg 3 0 R /K 0\n"
       "   /A << /O /Layout >>\n"
       ">>"});

  // Contents stream: Marked content sequence with MCID 0.
  // Use /P tag to match the struct element type; Poppler uses /K for linkage,
  // but this is a plausible content stream.
  const std::string streamData =
      "/P <</MCID 0>> BDC\n"
      "BT\n"
      "/F1 12 Tf\n"
      "72 720 Td\n"
      "(Hello) Tj\n"
      "ET\n"
      "EMC\n";

  {
    std::ostringstream oss;
    oss << "<< /Length " << streamData.size() << " >>\n"
        << "stream\n"
        << streamData << "endstream";
    objs.push_back({6, oss.str()});
  }

  // Minimal ParentTree (a number tree). Keep it valid and small.
  // Many parsers accept a minimal number tree even if not used directly here.
  objs.push_back({7, "<< /Nums [0 << /K [5 0 R] >>] >>"});

  // Write file with proper xref.
  std::string path;
#if __cpp_lib_filesystem
  {
    namespace fs = std::filesystem;
    auto tmp = fs::temp_directory_path();
    auto fname = std::string("poppler_structelement_1710_") +
                 std::to_string(::getpid()) + "_" + std::to_string(std::rand()) +
                 ".pdf";
    path = (tmp / fname).string();
  }
#else
  // Fallback: current directory
  path = "poppler_structelement_1710_temp.pdf";
#endif

  std::ofstream out(path, std::ios::binary);
  if (!out.is_open()) {
    // As a last resort, try a different name.
    path = "poppler_structelement_1710_temp_fallback.pdf";
    out.open(path, std::ios::binary);
  }
  EXPECT_TRUE(out.is_open());

  out << "%PDF-1.7\n";
  std::vector<long> offsets;
  offsets.resize(objs.size() + 1);
  offsets[0] = 0;

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[objs[i].num] = static_cast<long>(out.tellp());
    out << objs[i].num << " 0 obj\n" << objs[i].body << "\nendobj\n";
  }

  const long xrefPos = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 " << (objs.size() + 1) << "\n";
  out << "0000000000 65535 f \n";
  for (size_t i = 1; i <= objs.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    out << buf << " 00000 n \n";
  }
  out << "trailer\n";
  out << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
  out << "startxref\n" << xrefPos << "\n%%EOF\n";
  out.close();

  return path;
}

// Detection helpers to adapt to minor API differences without guessing internals.
template <typename T>
using has_getNumChildren_t = decltype(std::declval<const T*>()->getNumChildren());

template <typename T>
using has_getChild_t =
    decltype(std::declval<const T*>()->getChild(std::declval<int>()));

template <typename T, typename = void>
struct has_getNumChildren : std::false_type {};
template <typename T>
struct has_getNumChildren<T, std::void_t<has_getNumChildren_t<T>>> : std::true_type {};

template <typename T, typename = void>
struct has_getChild : std::false_type {};
template <typename T>
struct has_getChild<T, std::void_t<has_getChild_t<T>>> : std::true_type {};

// Try to get the first StructElement from the document's structure tree root.
// This stays strictly in public API territory.
static const StructElement* GetFirstTopLevelStructElement_1710(PDFDoc* doc) {
  if (!doc) return nullptr;
  Catalog* cat = doc->getCatalog();
  if (!cat) return nullptr;

  // Common Poppler API: Catalog::getStructTreeRoot()
  auto* root = cat->getStructTreeRoot();
  if (!root) return nullptr;

  // If StructTreeRoot exposes getNumChildren/getChild similarly to StructElement:
  if constexpr (has_getNumChildren<decltype(root)>::value && has_getChild<decltype(root)>::value) {
    const unsigned n = root->getNumChildren();
    if (n == 0) return nullptr;
    return root->getChild(0);
  } else {
    // Some builds may expose a "getRoot" or similar; if unavailable, return nullptr.
    return nullptr;
  }
}

class StructElementGetNonConstAttributeTest_1710 : public ::testing::Test {
 protected:
  void SetUp() override {
    globalParams = std::make_unique<GlobalParams>();

    pdfPath_ = WriteMinimalTaggedPdfToTemp_1710();
    auto gooPath = std::make_unique<GooString>(pdfPath_.c_str());
    doc_ = std::make_unique<PDFDoc>(std::move(gooPath));

    ASSERT_TRUE(doc_);
    ASSERT_TRUE(doc_->isOk());
  }

  void TearDown() override {
    doc_.reset();
    globalParams.reset();

    if (!pdfPath_.empty()) {
      std::remove(pdfPath_.c_str());
    }
  }

  std::unique_ptr<GlobalParams> globalParams;
  std::unique_ptr<PDFDoc> doc_;
  std::string pdfPath_;
};

// Normal operation: for a non-content element with at least one attribute,
// getNonConstAttribute(0) should return a non-null pointer and match getAttribute(0).
TEST_F(StructElementGetNonConstAttributeTest_1710,
       NonContentElementReturnsNonNullAndMatchesConstPointer_1710) {
  const StructElement* elem = GetFirstTopLevelStructElement_1710(doc_.get());
  ASSERT_NE(elem, nullptr);

  // Ensure this is the non-content struct element we built.
  ASSERT_FALSE(elem->isContent());

  const unsigned numAttr = elem->getNumAttributes();
  ASSERT_GE(numAttr, 1u);

  const Attribute* attrConst = elem->getAttribute(0);
  ASSERT_NE(attrConst, nullptr);

  Attribute* attrNonConst = elem->getNonConstAttribute(0);
  ASSERT_NE(attrNonConst, nullptr);

  // Observable relationship: non-const getter should refer to the same attribute object.
  EXPECT_EQ(attrNonConst, const_cast<Attribute*>(attrConst));
}

// Boundary/behavioral: content elements should yield nullptr regardless of index.
TEST_F(StructElementGetNonConstAttributeTest_1710,
       ContentElementReturnsNullForAnyIndex_1710) {
  const StructElement* parent = GetFirstTopLevelStructElement_1710(doc_.get());
  ASSERT_NE(parent, nullptr);
  ASSERT_FALSE(parent->isContent());

  ASSERT_GE(parent->getNumChildren(), 1u);
  const StructElement* contentChild = parent->getChild(0);
  ASSERT_NE(contentChild, nullptr);

  ASSERT_TRUE(contentChild->isContent());

  EXPECT_EQ(contentChild->getNonConstAttribute(0), nullptr);
  EXPECT_EQ(contentChild->getNonConstAttribute(123456), nullptr);
  EXPECT_EQ(contentChild->getNonConstAttribute(-1), nullptr);  // If accepted, should still be nullptr.
}

// Exceptional / error case (observable): for non-content element, out-of-range index
// should throw (std::out_of_range) due to bounds-checked access.
TEST_F(StructElementGetNonConstAttributeTest_1710,
       NonContentOutOfRangeIndexThrows_1710) {
  const StructElement* elem = GetFirstTopLevelStructElement_1710(doc_.get());
  ASSERT_NE(elem, nullptr);
  ASSERT_FALSE(elem->isContent());

  const unsigned numAttr = elem->getNumAttributes();
  ASSERT_GE(numAttr, 1u);

  // Using exactly numAttr should be out-of-range (valid indices are [0, numAttr-1]).
  EXPECT_THROW(
      {
        (void)elem->getNonConstAttribute(static_cast<int>(numAttr));
      },
      std::out_of_range);

  // Large positive out-of-range.
  EXPECT_THROW({ (void)elem->getNonConstAttribute(999999); }, std::out_of_range);
}

// Boundary/exception behavior: for content element, getNonConstAttribute should not throw
// even with out-of-range indices (it returns nullptr based on public behavior).
TEST_F(StructElementGetNonConstAttributeTest_1710,
       ContentOutOfRangeDoesNotThrowAndReturnsNull_1710) {
  const StructElement* parent = GetFirstTopLevelStructElement_1710(doc_.get());
  ASSERT_NE(parent, nullptr);
  ASSERT_FALSE(parent->isContent());

  ASSERT_GE(parent->getNumChildren(), 1u);
  const StructElement* contentChild = parent->getChild(0);
  ASSERT_NE(contentChild, nullptr);
  ASSERT_TRUE(contentChild->isContent());

  Attribute* ret = reinterpret_cast<Attribute*>(0x1);
  EXPECT_NO_THROW({ ret = contentChild->getNonConstAttribute(999999); });
  EXPECT_EQ(ret, nullptr);
}

}  // namespace