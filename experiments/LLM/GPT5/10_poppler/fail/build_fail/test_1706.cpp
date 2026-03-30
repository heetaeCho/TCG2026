// StructElement_getChild_1706_test.cc
#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "poppler/StructElement.h"
#include "poppler/PDFDoc.h"
#include "poppler/Catalog.h"
#include "poppler/GooString.h"

namespace {

// ---- Small helpers to keep the test robust across Poppler API variations ----

template <typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename T, typename = void>
struct has_getCatalog : std::false_type {};
template <typename T>
struct has_getCatalog<T, std::void_t<decltype(std::declval<T*>()->getCatalog())>> : std::true_type {};

template <typename T, typename = void>
struct has_getStructTreeRoot_on_catalog : std::false_type {};
template <typename T>
struct has_getStructTreeRoot_on_catalog<
    T, std::void_t<decltype(std::declval<T*>()->getStructTreeRoot())>> : std::true_type {};

template <typename T, typename = void>
struct has_getStructTreeRoot_on_doc : std::false_type {};
template <typename T>
struct has_getStructTreeRoot_on_doc<
    T, std::void_t<decltype(std::declval<T*>()->getStructTreeRoot())>> : std::true_type {};

template <typename T, typename = void>
struct has_getChild0 : std::false_type {};
template <typename T>
struct has_getChild0<T, std::void_t<decltype(std::declval<T*>()->getChild(0))>> : std::true_type {};

template <typename T, typename = void>
struct has_getRoot : std::false_type {};
template <typename T>
struct has_getRoot<T, std::void_t<decltype(std::declval<T*>()->getRoot())>> : std::true_type {};

// Try to obtain a StructTreeRoot pointer from PDFDoc in a version-tolerant way.
template <typename DocT>
auto GetStructTreeRootFromDoc(DocT* doc) {
  if constexpr (has_getCatalog<DocT>::value) {
    auto* catalog = doc->getCatalog();
    if constexpr (has_getStructTreeRoot_on_catalog<remove_cvref_t<decltype(*catalog)>>::value) {
      return catalog ? catalog->getStructTreeRoot() : nullptr;
    }
  }
  if constexpr (has_getStructTreeRoot_on_doc<DocT>::value) {
    return doc->getStructTreeRoot();
  }
  return nullptr;
}

// Try to obtain a *StructElement from StructTreeRoot in a version-tolerant way.
template <typename RootT>
const StructElement* GetFirstStructElementFromRoot(RootT* root) {
  if (!root) return nullptr;

  // Common patterns: root->getChild(0) or root->getRoot()
  if constexpr (has_getChild0<RootT>::value) {
    auto child0 = root->getChild(0);
    // Ensure the return type is compatible with StructElement*
    if constexpr (std::is_convertible_v<decltype(child0), const StructElement*>) {
      return static_cast<const StructElement*>(child0);
    }
  }
  if constexpr (has_getRoot<RootT>::value) {
    auto r = root->getRoot();
    if constexpr (std::is_convertible_v<decltype(r), const StructElement*>) {
      return static_cast<const StructElement*>(r);
    }
  }
  return nullptr;
}

// Construct a PDFDoc from a temporary file, accommodating common constructor signatures.
std::unique_ptr<PDFDoc> MakePDFDocFromFile(const std::string& path) {
  auto* fileName = new GooString(path.c_str());

  // Most Poppler versions support: PDFDoc(const GooString*, GooString*, GooString*, void*, bool)
  if constexpr (std::is_constructible_v<PDFDoc, const GooString*, GooString*, GooString*, void*, bool>) {
    return std::unique_ptr<PDFDoc>(new PDFDoc(fileName, nullptr, nullptr, nullptr, /*quiet=*/true));
  }
  // Fallback: PDFDoc(const GooString*, GooString*, GooString*)
  if constexpr (std::is_constructible_v<PDFDoc, const GooString*, GooString*, GooString*>) {
    return std::unique_ptr<PDFDoc>(new PDFDoc(fileName, nullptr, nullptr));
  }
  // Fallback: PDFDoc(const GooString*)
  if constexpr (std::is_constructible_v<PDFDoc, const GooString*>) {
    return std::unique_ptr<PDFDoc>(new PDFDoc(fileName));
  }

  // If none match, avoid leaking.
  delete fileName;
  return nullptr;
}

// Build a minimal *tagged* PDF with a structure tree where:
// - Root StructElem has /K [ 0 <ref-to-child-structelem> ]
//   => child(0) is a *content* StructElement (MCID), child(1) is a non-content StructElement.
// This enables black-box testing of StructElement::getChild().
std::string BuildTaggedPdfBytes() {
  struct Obj {
    int num;
    std::string body;  // includes "obj ... endobj"
  };

  std::vector<Obj> objs;

  // 1 0: Catalog
  objs.push_back({1,
                  "1 0 obj\n"
                  "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R >>\n"
                  "endobj\n"});

  // 2 0: Pages
  objs.push_back({2,
                  "2 0 obj\n"
                  "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
                  "endobj\n"});

  // 3 0: Page
  objs.push_back({3,
                  "3 0 obj\n"
                  "<< /Type /Page /Parent 2 0 R\n"
                  "   /MediaBox [0 0 300 300]\n"
                  "   /Contents 4 0 R\n"
                  "   /Resources << >>\n"
                  "   /StructParents 0\n"
                  ">>\n"
                  "endobj\n"});

  // 4 0: Contents (empty)
  objs.push_back({4,
                  "4 0 obj\n"
                  "<< /Length 0 >>\n"
                  "stream\n"
                  "\n"
                  "endstream\n"
                  "endobj\n"});

  // 5 0: StructTreeRoot -> /K 6 0 R
  objs.push_back({5,
                  "5 0 obj\n"
                  "<< /Type /StructTreeRoot /K 6 0 R >>\n"
                  "endobj\n"});

  // 6 0: Root StructElem with two children:
  //   - integer 0 (MCID content element)
  //   - 8 0 R (non-content StructElem)
  objs.push_back({6,
                  "6 0 obj\n"
                  "<< /Type /StructElem /S /Document /P 5 0 R /Pg 3 0 R\n"
                  "   /K [ 0 8 0 R ]\n"
                  ">>\n"
                  "endobj\n"});

  // 8 0: Child StructElem (non-content) with empty /K
  objs.push_back({8,
                  "8 0 obj\n"
                  "<< /Type /StructElem /S /Span /P 6 0 R /Pg 3 0 R /K [ ] >>\n"
                  "endobj\n"});

  std::string pdf;
  pdf += "%PDF-1.5\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";  // binary comment

  std::vector<long> offsets;
  offsets.resize(9, 0);

  for (const auto& o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    pdf += o.body;
  }

  const long xref_pos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 9\n";
  pdf += "0000000000 65535 f \n";

  auto fmt10 = [](long v) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", v);
    return std::string(buf);
  };

  for (int i = 1; i <= 8; ++i) {
    // We did not define object 7; mark it as free.
    if (i == 7) {
      pdf += "0000000000 65535 f \n";
      continue;
    }
    pdf += fmt10(offsets[i]) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size 9 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

std::string WriteTempPdfFile(const std::string& bytes) {
  const auto dir = std::filesystem::temp_directory_path();
  const auto path = dir / ("poppler_structelement_getchild_1706.pdf");

  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();

  return path.string();
}

const StructElement* GetRootStructElement(PDFDoc* doc) {
  auto* root = GetStructTreeRootFromDoc(doc);
  if (!root) return nullptr;
  return GetFirstStructElementFromRoot(root);
}

}  // namespace

// ------------------------------------------------------------

class StructElementGetChildTest_1706 : public ::testing::Test {
protected:
  void SetUp() override {
    const std::string pdfBytes = BuildTaggedPdfBytes();
    pdfPath_ = WriteTempPdfFile(pdfBytes);
    doc_ = MakePDFDocFromFile(pdfPath_);
  }

  std::string pdfPath_;
  std::unique_ptr<PDFDoc> doc_;
};

TEST_F(StructElementGetChildTest_1706, ReturnsChildrenForNonContentElement_1706) {
  ASSERT_NE(doc_, nullptr);
  ASSERT_TRUE(doc_->isOk());

  const StructElement* rootElem = GetRootStructElement(doc_.get());
  ASSERT_NE(rootElem, nullptr);
  ASSERT_FALSE(rootElem->isContent());

  // The test PDF builds /K [ 0 8 0 R ] => 2 children for the non-content root element.
  const StructElement* child0 = rootElem->getChild(0);
  const StructElement* child1 = rootElem->getChild(1);

  ASSERT_NE(child0, nullptr);
  ASSERT_NE(child1, nullptr);
  EXPECT_NE(child0, child1);

  // First child is the MCID content element (created from integer in /K).
  EXPECT_TRUE(child0->isContent());
  // Second child is a referenced StructElem dictionary.
  EXPECT_FALSE(child1->isContent());
}

TEST_F(StructElementGetChildTest_1706, ReturnsNullptrWhenCalledOnContentElement_1706) {
  ASSERT_NE(doc_, nullptr);
  ASSERT_TRUE(doc_->isOk());

  const StructElement* rootElem = GetRootStructElement(doc_.get());
  ASSERT_NE(rootElem, nullptr);

  const StructElement* contentChild = rootElem->getChild(0);
  ASSERT_NE(contentChild, nullptr);
  ASSERT_TRUE(contentChild->isContent());

  // getChild() on a content element returns nullptr (observable behavior from the interface).
  EXPECT_EQ(contentChild->getChild(0), nullptr);
  EXPECT_EQ(contentChild->getChild(1), nullptr);
  // Also verify with a negative index (should still return nullptr due to early isContent() check).
  EXPECT_EQ(contentChild->getChild(-1), nullptr);
}

TEST_F(StructElementGetChildTest_1706, OutOfRangeIndexThrowsForNonContentElement_1706) {
  ASSERT_NE(doc_, nullptr);
  ASSERT_TRUE(doc_->isOk());

  const StructElement* rootElem = GetRootStructElement(doc_.get());
  ASSERT_NE(rootElem, nullptr);
  ASSERT_FALSE(rootElem->isContent());

  // The test PDF root element has exactly 2 children; index 2 is out of range.
  EXPECT_THROW((void)rootElem->getChild(2), std::out_of_range);

  // Negative index converts to a very large size_t for vector::at; behavior is an exception.
  EXPECT_THROW((void)rootElem->getChild(-1), std::out_of_range);
}