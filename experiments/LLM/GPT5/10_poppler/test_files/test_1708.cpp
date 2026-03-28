// StructElement_getNumAttributes_1708_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GlobalParams.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "StructTreeRoot.h"
#include "StructElement.h"

namespace {

// Builds a minimal tagged PDF with a structure tree:
// StructTreeRoot -> StructElem (non-content) -> MCID content item.
// The StructElem optionally carries /A (attributes) to exercise getNumAttributes().
enum class AttrMode {
  kNoAEntry,
  kEmptyArray,
  kTwoDicts,
};

static std::string BuildTaggedPdfWithAttrs(AttrMode mode) {
  auto obj = [&](int num, const std::string &body) {
    return std::to_string(num) + " 0 obj\n" + body + "\nendobj\n";
  };

  const std::string catalog =
      "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 3 0 R /MarkInfo << /Marked true >> >>";

  const std::string pages =
      "<< /Type /Pages /Count 1 /Kids [4 0 R] >>";

  const std::string structTreeRoot =
      "<< /Type /StructTreeRoot /K [5 0 R] >>";

  // Page content uses a marked-content sequence with /MCID 0.
  // Keep it simple (path ops only) to avoid font/resource requirements.
  const std::string streamData =
      "q\n"
      "/P <</MCID 0>> BDC\n"
      "0 0 m 10 10 l S\n"
      "EMC\n"
      "Q\n";

  std::string contents =
      "<< /Length " + std::to_string(streamData.size()) + " >>\n"
      "stream\n" + streamData + "endstream";

  const std::string page =
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 6 0 R /Resources << >> /StructParents 0 >>";

  // StructElem: /K [0] means its child is a content item (MCID 0).
  std::string aEntry;
  switch (mode) {
    case AttrMode::kNoAEntry:
      aEntry = "";
      break;
    case AttrMode::kEmptyArray:
      aEntry = " /A []";
      break;
    case AttrMode::kTwoDicts:
      // Two attribute dictionaries in an array (should parse as 2 attributes if supported).
      aEntry = " /A [<< /O /Layout >> << /O /Table >>]";
      break;
  }

  const std::string structElem =
      "<< /Type /StructElem /S /P /P 3 0 R /Pg 4 0 R /K [0]" + aEntry + " >>";

  // Assemble objects and compute xref offsets.
  std::vector<std::pair<int, std::string>> objects;
  objects.emplace_back(1, obj(1, catalog));
  objects.emplace_back(2, obj(2, pages));
  objects.emplace_back(3, obj(3, structTreeRoot));
  objects.emplace_back(4, obj(4, page));
  objects.emplace_back(5, obj(5, structElem));
  objects.emplace_back(6, obj(6, contents));

  std::string pdf;
  pdf += "%PDF-1.7\n";
  // PDF header line sometimes benefits from binary chars; keep plain for tests.

  // Offsets for xref: entry 0 is free.
  std::vector<long> offsets(7, 0);
  offsets[0] = 0;

  for (const auto &it : objects) {
    const int objNum = it.first;
    offsets[objNum] = static_cast<long>(pdf.size());
    pdf += it.second;
  }

  const long xrefPos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 7\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 6; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 7 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefPos) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static std::string WriteTempPdf(const std::string &bytes) {
  std::string templ = "/tmp/poppler_structelement_1708_XXXXXX.pdf";
  std::vector<char> path(templ.begin(), templ.end());
  path.push_back('\0');

  int fd = ::mkstemps(path.data(), 4 /* .pdf */);
  if (fd < 0) return "";

  FILE *f = ::fdopen(fd, "wb");
  if (!f) {
    ::close(fd);
    return "";
  }

  const size_t wrote = std::fwrite(bytes.data(), 1, bytes.size(), f);
  std::fclose(f);

  if (wrote != bytes.size()) {
    std::remove(path.data());
    return "";
  }
  return std::string(path.data());
}

struct DocAndRoot {
  std::unique_ptr<PDFDoc> doc;
  StructTreeRoot *root = nullptr;
};

static DocAndRoot OpenDocAndGetStructRoot(const std::string &path) {
  DocAndRoot out;

  auto fileName = std::make_unique<GooString>(path.c_str());
  out.doc = std::make_unique<PDFDoc>(std::move(fileName));

  if (!out.doc || !out.doc->isOk()) {
    out.root = nullptr;
    return out;
  }

  Catalog *cat = out.doc->getCatalog();
  if (!cat) {
    out.root = nullptr;
    return out;
  }

  out.root = cat->getStructTreeRoot();
  return out;
}

class StructElementGetNumAttributesTest_1708 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure globalParams exists (common requirement in Poppler tests).
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }
};

}  // namespace

TEST_F(StructElementGetNumAttributesTest_1708, ReturnsTwoForNonContentStructElemWithTwoAttributeDicts_1708) {
  const std::string pdfBytes = BuildTaggedPdfWithAttrs(AttrMode::kTwoDicts);
  const std::string path = WriteTempPdf(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto dr = OpenDocAndGetStructRoot(path);
  ASSERT_TRUE(dr.doc);
  ASSERT_TRUE(dr.doc->isOk());
  ASSERT_NE(dr.root, nullptr);

  // Root should have at least one child: our StructElem.
  ASSERT_GE(dr.root->getNumChildren(), 1u);
  const StructElement *elem = dr.root->getChild(0);
  ASSERT_NE(elem, nullptr);

  // Non-content element should expose the parsed attribute count.
  EXPECT_FALSE(elem->isContent());
  EXPECT_EQ(elem->getNumAttributes(), 2u);

  // Idempotence: repeated calls should be stable/observable.
  EXPECT_EQ(elem->getNumAttributes(), 2u);

  std::remove(path.c_str());
}

TEST_F(StructElementGetNumAttributesTest_1708, ReturnsZeroForNonContentStructElemWhenNoAEntry_1708) {
  const std::string pdfBytes = BuildTaggedPdfWithAttrs(AttrMode::kNoAEntry);
  const std::string path = WriteTempPdf(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto dr = OpenDocAndGetStructRoot(path);
  ASSERT_TRUE(dr.doc);
  ASSERT_TRUE(dr.doc->isOk());
  ASSERT_NE(dr.root, nullptr);

  ASSERT_GE(dr.root->getNumChildren(), 1u);
  const StructElement *elem = dr.root->getChild(0);
  ASSERT_NE(elem, nullptr);

  EXPECT_FALSE(elem->isContent());
  EXPECT_EQ(elem->getNumAttributes(), 0u);

  std::remove(path.c_str());
}

TEST_F(StructElementGetNumAttributesTest_1708, ReturnsZeroForNonContentStructElemWhenEmptyAttributesArray_1708) {
  const std::string pdfBytes = BuildTaggedPdfWithAttrs(AttrMode::kEmptyArray);
  const std::string path = WriteTempPdf(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto dr = OpenDocAndGetStructRoot(path);
  ASSERT_TRUE(dr.doc);
  ASSERT_TRUE(dr.doc->isOk());
  ASSERT_NE(dr.root, nullptr);

  ASSERT_GE(dr.root->getNumChildren(), 1u);
  const StructElement *elem = dr.root->getChild(0);
  ASSERT_NE(elem, nullptr);

  EXPECT_FALSE(elem->isContent());
  EXPECT_EQ(elem->getNumAttributes(), 0u);

  std::remove(path.c_str());
}

TEST_F(StructElementGetNumAttributesTest_1708, ReturnsZeroForContentChildEvenWhenParentHasAttributes_1708) {
  const std::string pdfBytes = BuildTaggedPdfWithAttrs(AttrMode::kTwoDicts);
  const std::string path = WriteTempPdf(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto dr = OpenDocAndGetStructRoot(path);
  ASSERT_TRUE(dr.doc);
  ASSERT_TRUE(dr.doc->isOk());
  ASSERT_NE(dr.root, nullptr);

  ASSERT_GE(dr.root->getNumChildren(), 1u);
  const StructElement *parent = dr.root->getChild(0);
  ASSERT_NE(parent, nullptr);
  ASSERT_FALSE(parent->isContent());

  // The StructElem /K [0] should create a content child element.
  ASSERT_GE(parent->getNumChildren(), 1u);
  const StructElement *child = parent->getChild(0);
  ASSERT_NE(child, nullptr);

  EXPECT_TRUE(child->isContent());
  EXPECT_EQ(child->getNumAttributes(), 0u);

  // Boundary: repeated calls remain consistent.
  EXPECT_EQ(child->getNumAttributes(), 0u);

  std::remove(path.c_str());
}

TEST_F(StructElementGetNumAttributesTest_1708, SafeToCallOnMultipleElementsAcrossTree_1708) {
  const std::string pdfBytes = BuildTaggedPdfWithAttrs(AttrMode::kTwoDicts);
  const std::string path = WriteTempPdf(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto dr = OpenDocAndGetStructRoot(path);
  ASSERT_TRUE(dr.doc);
  ASSERT_TRUE(dr.doc->isOk());
  ASSERT_NE(dr.root, nullptr);

  const unsigned rootKids = dr.root->getNumChildren();
  ASSERT_GE(rootKids, 1u);

  for (unsigned i = 0; i < rootKids; ++i) {
    const StructElement *e = dr.root->getChild(static_cast<int>(i));
    ASSERT_NE(e, nullptr);

    // Observable behavior only: content => 0, non-content => >= 0.
    const unsigned n = e->getNumAttributes();
    if (e->isContent()) {
      EXPECT_EQ(n, 0u);
    } else {
      EXPECT_GE(n, 0u);
    }
  }

  std::remove(path.c_str());
}