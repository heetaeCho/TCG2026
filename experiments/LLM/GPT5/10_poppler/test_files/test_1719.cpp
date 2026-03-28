// StructTreeRoot_appendChild_1719_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "StructTreeRoot.h"
#include "StructElement.h"

#include "PDFDoc.h"
#include "Catalog.h"
#include "goo/GooString.h"

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

namespace {

// ---------- Small helper: write a minimal, valid PDF with a StructTreeRoot + 1 StructElem ----------
static std::string WriteMinimalStructTreePdf_1719(const std::string &filePath) {
  // Objects:
  // 1 0: Catalog (Pages 3 0 R, StructTreeRoot 2 0 R, MarkInfo)
  // 2 0: StructTreeRoot (K [4 0 R])
  // 3 0: Pages
  // 5 0: Page
  // 4 0: StructElem (S /P, P 2 0 R, Pg 5 0 R)
  //
  // Note: This is intentionally minimal; if a given Poppler build requires more,
  // tests will skip when the structure tree isn't available.

  std::ofstream out(filePath, std::ios::binary);
  if (!out.is_open()) return "";

  auto write = [&](const std::string &s) { out.write(s.data(), static_cast<std::streamsize>(s.size())); };

  write("%PDF-1.4\n");
  // Binary comment (recommended)
  write("%\xE2\xE3\xCF\xD3\n");

  struct ObjInfo {
    int objNum;
    std::streamoff offset;
  };
  std::vector<ObjInfo> offsets;
  offsets.reserve(6);

  auto beginObj = [&](int n) {
    offsets.push_back({n, out.tellp()});
    write(std::to_string(n) + " 0 obj\n");
  };
  auto endObj = [&]() { write("endobj\n"); };

  beginObj(1);
  write("<< /Type /Catalog /Pages 3 0 R /StructTreeRoot 2 0 R /MarkInfo << /Marked true >> >>\n");
  endObj();

  beginObj(2);
  write("<< /Type /StructTreeRoot /K [4 0 R] >>\n");
  endObj();

  beginObj(3);
  write("<< /Type /Pages /Count 1 /Kids [5 0 R] >>\n");
  endObj();

  beginObj(4);
  // StructElem parent is StructTreeRoot (2 0 R). Use /S /P (a common structure type).
  // No kids required for existence.
  write("<< /Type /StructElem /S /P /P 2 0 R /Pg 5 0 R >>\n");
  endObj();

  beginObj(5);
  // Minimal page (no contents)
  write("<< /Type /Page /Parent 3 0 R /MediaBox [0 0 200 200] >>\n");
  endObj();

  const std::streamoff xrefPos = out.tellp();
  write("xref\n");
  write("0 6\n");
  write("0000000000 65535 f \n");

  auto fmt10 = [](std::streamoff v) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld", static_cast<long long>(v));
    return std::string(buf);
  };

  // Offsets must be ordered by object number 1..5; ensure we place them correctly.
  // offsets vector is in creation order already (1..5).
  for (int i = 1; i <= 5; ++i) {
    std::streamoff off = 0;
    for (const auto &oi : offsets) {
      if (oi.objNum == i) {
        off = oi.offset;
        break;
      }
    }
    write(fmt10(off) + " 00000 n \n");
  }

  write("trailer\n");
  write("<< /Size 6 /Root 1 0 R >>\n");
  write("startxref\n");
  write(std::to_string(static_cast<long long>(xrefPos)) + "\n");
  write("%%EOF\n");

  out.close();
  return filePath;
}

// ---------- PDFDoc construction helpers (handle common signature variations) ----------
template <typename T, typename = void>
struct HasMakePDFDocUniquePtr_1719 : std::false_type {};

template <typename T>
struct HasMakePDFDocUniquePtr_1719<
    T, std::void_t<decltype(T(std::unique_ptr<GooString>(nullptr)))>> : std::true_type {};

static std::unique_ptr<PDFDoc> OpenPdf_1719(const std::string &path) {
  // Most Poppler builds support PDFDoc(std::unique_ptr<GooString>).
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  return doc;
}

// ---------- StructTreeRoot acquisition helpers (try common access paths) ----------
template <typename T, typename = void>
struct HasDocGetStructTreeRoot_1719 : std::false_type {};
template <typename T>
struct HasDocGetStructTreeRoot_1719<T, std::void_t<decltype(std::declval<T*>()->getStructTreeRoot())>>
    : std::true_type {};

template <typename T, typename = void>
struct HasCatalogGetStructTreeRoot_1719 : std::false_type {};
template <typename T>
struct HasCatalogGetStructTreeRoot_1719<
    T, std::void_t<decltype(std::declval<T*>()->getCatalog()->getStructTreeRoot())>> : std::true_type {};

static StructTreeRoot *GetStructTreeRootFromDoc_1719(PDFDoc *doc) {
  if (!doc) return nullptr;

  if constexpr (HasDocGetStructTreeRoot_1719<PDFDoc>::value) {
    return doc->getStructTreeRoot();
  } else if constexpr (HasCatalogGetStructTreeRoot_1719<PDFDoc>::value) {
    auto *cat = doc->getCatalog();
    if (!cat) return nullptr;
    return cat->getStructTreeRoot();
  } else {
    return nullptr;
  }
}

static const StructElement *GetFirstRootChild_1719(const StructTreeRoot *root) {
  if (!root) return nullptr;
  if (root->getNumChildren() == 0) return nullptr;
  return root->getChild(0);
}

class StructTreeRootAppendChildTest_1719 : public ::testing::Test {
 protected:
  void SetUp() override {
#if defined(fs)
    const auto dir = fs::temp_directory_path();
    const auto file = dir / fs::path("poppler_structtree_1719.pdf");
    pdfPath = file.string();
#else
    pdfPath = "poppler_structtree_1719.pdf";
#endif
    ASSERT_FALSE(WriteMinimalStructTreePdf_1719(pdfPath).empty());

    doc = OpenPdf_1719(pdfPath);
    ASSERT_TRUE(doc);

    // If doc parsing fails in this build, tests will skip where needed.
    root = GetStructTreeRootFromDoc_1719(doc.get());
  }

  void TearDown() override {
    doc.reset();
#if defined(fs)
    std::error_code ec;
    fs::remove(pdfPath, ec);
#else
    std::remove(pdfPath.c_str());
#endif
  }

  std::string pdfPath;
  std::unique_ptr<PDFDoc> doc;
  StructTreeRoot *root = nullptr;
};

TEST_F(StructTreeRootAppendChildTest_1719, AppendOkElementIncreasesChildCount_1719) {
  if (!doc || !root) {
    GTEST_SKIP() << "StructTreeRoot is not available in this build or PDF parsing failed.";
  }

  const unsigned before = root->getNumChildren();

  const StructElement *existingChild = GetFirstRootChild_1719(root);
  if (!existingChild) {
    GTEST_SKIP() << "No existing StructElement found in minimal test PDF; cannot obtain an isOk() element.";
  }

  // appendChild expects non-const pointer; we do not modify through it here.
  auto *elem = const_cast<StructElement *>(existingChild);

  root->appendChild(elem);

  const unsigned after = root->getNumChildren();
  EXPECT_EQ(after, before + 1u);

  // Observable behavior: new child should be present at the end.
  ASSERT_GT(after, 0u);
  EXPECT_EQ(root->getChild(static_cast<int>(after - 1u)), existingChild);
}

TEST_F(StructTreeRootAppendChildTest_1719, AppendNullDoesNotChangeChildCount_1719) {
  if (!doc || !root) {
    GTEST_SKIP() << "StructTreeRoot is not available in this build or PDF parsing failed.";
  }

  const unsigned before = root->getNumChildren();
  root->appendChild(nullptr);
  EXPECT_EQ(root->getNumChildren(), before);
}

TEST_F(StructTreeRootAppendChildTest_1719, AppendSameOkElementTwiceAppendsTwice_1719) {
  if (!doc || !root) {
    GTEST_SKIP() << "StructTreeRoot is not available in this build or PDF parsing failed.";
  }

  const StructElement *existingChild = GetFirstRootChild_1719(root);
  if (!existingChild) {
    GTEST_SKIP() << "No existing StructElement found in minimal test PDF; cannot obtain an isOk() element.";
  }
  auto *elem = const_cast<StructElement *>(existingChild);

  const unsigned before = root->getNumChildren();

  root->appendChild(elem);
  root->appendChild(elem);

  const unsigned after = root->getNumChildren();
  EXPECT_EQ(after, before + 2u);

  // Both appended entries should be observable via getChild at the tail.
  ASSERT_GE(after, 2u);
  EXPECT_EQ(root->getChild(static_cast<int>(after - 2u)), existingChild);
  EXPECT_EQ(root->getChild(static_cast<int>(after - 1u)), existingChild);
}

}  // namespace