// StructElement_getRevision_1701_test.cc
#include <gtest/gtest.h>

#include <climits>
#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "PDFDoc.h"
#include "Catalog.h"
#include "StructElement.h"
#include "GlobalParams.h"
#include "goo/GooString.h"

namespace {

// Poppler typically uses a global `globalParams`.
std::unique_ptr<GlobalParams> g_globalParams;

// ---------- Tiny tagged PDF builder (test resource) ----------
// Creates a PDF with a StructTreeRoot containing:
//  - a non-content StructElem (Document)
//  - a child StructElem (P) whose /K is an integer MCID (content item)
// This is enough to obtain both a non-content StructElement and a content StructElement.
std::string BuildTaggedPdfBytes()
{
  struct Obj {
    int num;
    std::string body; // includes "obj ... endobj\n" content without the header/trailer
  };

  // Note: Keep bodies deterministic; xref offsets are computed from the final bytes.
  const std::vector<Obj> objs = {
      {1,
       "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R /MarkInfo << /Marked true >> >>\n"},
      {2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"},
      {3,
       "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>\n"},
      {4,
       "<< /Length 0 >>\nstream\n\nendstream\n"},
      {5, "<< /Type /StructTreeRoot /K 6 0 R >>\n"},
      // Non-content StructElem (Document)
      {6, "<< /Type /StructElem /S /Document /K [7 0 R] /R 7 >>\n"},
      // Child StructElem with /K integer => content item created by parser
      {7, "<< /Type /StructElem /S /P /P 6 0 R /Pg 3 0 R /K 0 /R 9 >>\n"},
  };

  std::string out;
  out += "%PDF-1.7\n";
  out += "%\xE2\xE3\xCF\xD3\n";

  // xref requires offsets for objects 0..N
  const int maxObjNum = 7;
  std::vector<long> offsets(maxObjNum + 1, 0);
  offsets[0] = 0;

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.size());
    out += std::to_string(o.num) + " 0 obj\n";
    out += o.body;
    out += "endobj\n";
  }

  const long xrefPos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 " + std::to_string(maxObjNum + 1) + "\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= maxObjNum; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size " + std::to_string(maxObjNum + 1) + " /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xrefPos) + "\n";
  out += "%%EOF\n";

  return out;
}

std::string WriteTempPdf(const std::string &bytes)
{
  // Unique-ish filename per test run.
  // (Using PID is usually enough for unit tests.)
#if defined(_WIN32)
  const char *tmpDir = ".";
#else
  const char *tmpDir = "/tmp";
#endif
  std::string path = std::string(tmpDir) + "/poppler_structelement_getrevision_1701.pdf";

  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  os.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  os.close();
  return path;
}

// ---------- Detection helpers to avoid hard-coding exact Poppler accessor names ----------
template <typename T, typename = void>
struct has_getStructTreeRoot : std::false_type { };
template <typename T>
struct has_getStructTreeRoot<T, std::void_t<decltype(std::declval<T *>()->getStructTreeRoot())>>
    : std::true_type { };

template <typename T, typename = void>
struct has_catalog_getStructTreeRoot : std::false_type { };
template <typename T>
struct has_catalog_getStructTreeRoot<
    T, std::void_t<decltype(std::declval<T *>()->getCatalog()->getStructTreeRoot())>> : std::true_type { };

template <typename T, typename = void>
struct has_getNumChildren : std::false_type { };
template <typename T>
struct has_getNumChildren<T, std::void_t<decltype(std::declval<const T *>()->getNumChildren())>>
    : std::true_type { };

template <typename T, typename = void>
struct has_getChild : std::false_type { };
template <typename T>
struct has_getChild<T, std::void_t<decltype(std::declval<const T *>()->getChild(0))>> : std::true_type { };

StructTreeRoot *GetStructTreeRootFromDoc(PDFDoc *doc)
{
  if (!doc) {
    return nullptr;
  }

  if constexpr (has_getStructTreeRoot<PDFDoc>::value) {
    return doc->getStructTreeRoot();
  } else if constexpr (has_catalog_getStructTreeRoot<PDFDoc>::value) {
    auto *cat = doc->getCatalog();
    return cat ? cat->getStructTreeRoot() : nullptr;
  } else {
    return nullptr;
  }
}

// Try to obtain the first StructElement reachable from the StructTreeRoot.
// If the concrete API differs, we safely skip the tests at runtime.
StructElement *TryGetFirstStructElement(StructTreeRoot *root)
{
  if (!root) {
    return nullptr;
  }

  // Many Poppler versions expose children via getNumChildren/getChild.
  if constexpr (has_getNumChildren<StructTreeRoot>::value && has_getChild<StructTreeRoot>::value) {
    const auto n = root->getNumChildren();
    if (n > 0) {
      // getChild is often "const StructElement *" – cast away const only for calling
      // const-qualified APIs we test (getRevision/setRevision are const).
      return const_cast<StructElement *>(root->getChild(0));
    }
  }
  return nullptr;
}

StructElement *FindFirstMatching(StructElement *start, bool wantContent)
{
  if (!start) {
    return nullptr;
  }

  // Check this node first.
  if (start->isContent() == wantContent) {
    return start;
  }

  // Depth-first traversal via public child accessors.
  const unsigned n = start->getNumChildren();
  for (unsigned i = 0; i < n; ++i) {
    auto *child = const_cast<StructElement *>(start->getChild(static_cast<int>(i)));
    if (!child) {
      continue;
    }
    if (auto *found = FindFirstMatching(child, wantContent)) {
      return found;
    }
  }
  return nullptr;
}

} // namespace

class StructElementGetRevisionTest_1701 : public ::testing::Test {
protected:
  static void SetUpTestSuite()
  {
    // Ensure Poppler global parameters are initialized.
    if (!g_globalParams) {
      g_globalParams = std::make_unique<GlobalParams>();
    }
  }

  static void TearDownTestSuite()
  {
    g_globalParams.reset();
  }

  void SetUp() override
  {
    const std::string pdfBytes = BuildTaggedPdfBytes();
    pdfPath = WriteTempPdf(pdfBytes);

    auto gs = std::make_unique<GooString>(pdfPath.c_str());
    doc = std::make_unique<PDFDoc>(std::move(gs));
  }

  void TearDown() override
  {
    doc.reset();
    // Best-effort cleanup.
    std::remove(pdfPath.c_str());
  }

  StructElement *GetRootStructElementOrSkip()
  {
    if (!doc) {
      GTEST_SKIP() << "PDFDoc not constructed.";
    }
    if (!doc->isOk()) {
      GTEST_SKIP() << "PDFDoc reported not ok; cannot exercise StructElement.";
    }

    StructTreeRoot *root = GetStructTreeRootFromDoc(doc.get());
    if (!root) {
      GTEST_SKIP() << "StructTreeRoot not available in this build.";
    }

    StructElement *first = TryGetFirstStructElement(root);
    if (!first) {
      GTEST_SKIP() << "Unable to obtain a first StructElement from StructTreeRoot using public API.";
    }
    return first;
  }

  std::string pdfPath;
  std::unique_ptr<PDFDoc> doc;
};

// ---- Tests for StructElement::getRevision() ----

TEST_F(StructElementGetRevisionTest_1701, NonContentRevisionRoundTripsAfterSet_1701)
{
  StructElement *rootElem = GetRootStructElementOrSkip();

  // We want a non-content element.
  StructElement *nonContent = FindFirstMatching(rootElem, /*wantContent=*/false);
  if (!nonContent) {
    GTEST_SKIP() << "No non-content StructElement found in test PDF.";
  }

  nonContent->setRevision(123u);
  EXPECT_EQ(nonContent->getRevision(), 123u);

  nonContent->setRevision(0u);
  EXPECT_EQ(nonContent->getRevision(), 0u);
}

TEST_F(StructElementGetRevisionTest_1701, NonContentRevisionHandlesMaxUnsigned_1701)
{
  StructElement *rootElem = GetRootStructElementOrSkip();

  StructElement *nonContent = FindFirstMatching(rootElem, /*wantContent=*/false);
  if (!nonContent) {
    GTEST_SKIP() << "No non-content StructElement found in test PDF.";
  }

  nonContent->setRevision(UINT_MAX);
  EXPECT_EQ(nonContent->getRevision(), UINT_MAX);
}

TEST_F(StructElementGetRevisionTest_1701, ContentRevisionIsAlwaysZero_1701)
{
  StructElement *rootElem = GetRootStructElementOrSkip();

  // We want a content element (created from /K integer MCID).
  StructElement *content = FindFirstMatching(rootElem, /*wantContent=*/true);
  if (!content) {
    GTEST_SKIP() << "No content StructElement found in test PDF.";
  }

  // Observable behavior from the provided implementation snippet:
  // getRevision() returns 0 for content.
  EXPECT_EQ(content->getRevision(), 0u);

  // Boundary/robustness: even if setRevision is called, content getRevision remains 0.
  content->setRevision(777u);
  EXPECT_EQ(content->getRevision(), 0u);
}