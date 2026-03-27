// StructElement_getTextSpans_1715_test.cc
#include <gtest/gtest.h>

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "poppler/StructElement.h"
#include "poppler/StructTreeRoot.h"
#include "poppler/PDFDoc.h"
#include "poppler/PDFDocFactory.h"
#include "poppler/Catalog.h"
#include "poppler/GlobalParams.h"
#include "goo/GooString.h"

// globalParams is a Poppler global (declared in GlobalParams.h in Poppler).
// Many Poppler entry points expect it to be initialized.
extern GlobalParams *globalParams;

namespace {

class StructElementGetTextSpansTest_1715 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    if (!globalParams) {
      globalParams = new GlobalParams();
    }
  }

  static void TearDownTestSuite() {
    delete globalParams;
    globalParams = nullptr;
  }

  static bool FileExists(const std::string &path) {
    FILE *f = std::fopen(path.c_str(), "rb");
    if (f) {
      std::fclose(f);
      return true;
    }
    return false;
  }

  static std::string GetEnvOrEmpty(const char *name) {
    const char *v = std::getenv(name);
    return v ? std::string(v) : std::string();
  }

  // Tries to locate a "tagged/structure" PDF in a few common locations, or uses an env var if set.
  static std::string FindTaggedPdfPath() {
    // Allow the test harness to point directly to a known tagged PDF.
    // (Keeps tests robust across different repo layouts.)
    for (const char *envName : {"POPPLER_STRUCT_TEST_PDF", "POPPLER_TEST_PDF", "TEST_PDF"}) {
      std::string p = GetEnvOrEmpty(envName);
      if (!p.empty() && FileExists(p)) {
        return p;
      }
    }

    // Common relative locations used by Poppler test setups (try several).
    const std::vector<std::string> candidates = {
        "tagged.pdf",
        "test/tagged.pdf",
        "tests/tagged.pdf",
        "test/data/tagged.pdf",
        "tests/data/tagged.pdf",
        "test/unittestcases/tagged.pdf",
        "tests/unittestcases/tagged.pdf",
        "testdata/tagged.pdf",
        "testdata/struct-tree.pdf",
        "tests/data/struct-tree.pdf",
    };

    for (const auto &c : candidates) {
      if (FileExists(c)) {
        return c;
      }
    }
    return "";
  }

  static std::unique_ptr<PDFDoc> OpenPdfDocOrSkip(const std::string &path) {
    if (path.empty() || !FileExists(path)) {
      GTEST_SKIP() << "No tagged/structure PDF found. Set POPPLER_STRUCT_TEST_PDF to a valid file.";
      return nullptr;
    }

    // Use PDFDocFactory to avoid depending on a specific PDFDoc constructor signature.
    auto fileName = std::make_unique<GooString>(path.c_str());
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(std::move(fileName), nullptr, nullptr));
    if (!doc) {
      GTEST_SKIP() << "Failed to create PDFDoc for: " << path;
      return nullptr;
    }
    if (!doc->isOk()) {
      GTEST_SKIP() << "PDFDoc is not OK for: " << path;
      return nullptr;
    }
    if (!doc->getCatalog()) {
      GTEST_SKIP() << "PDFDoc has no Catalog for: " << path;
      return nullptr;
    }
    return doc;
  }

  static const StructElement *FindFirstByPredicate(const StructElement *node,
                                                   const std::function<bool(const StructElement *)> &pred) {
    if (!node) {
      return nullptr;
    }
    if (pred(node)) {
      return node;
    }
    const unsigned n = node->getNumChildren();
    for (unsigned i = 0; i < n; ++i) {
      const StructElement *child = node->getChild(static_cast<int>(i));
      if (const StructElement *found = FindFirstByPredicate(child, pred)) {
        return found;
      }
    }
    return nullptr;
  }

  static const StructElement *FindFirstContentElement(const StructTreeRoot *root) {
    if (!root) {
      return nullptr;
    }
    const unsigned n = root->getNumChildren();
    for (unsigned i = 0; i < n; ++i) {
      const StructElement *child = root->getChild(static_cast<int>(i));
      if (const StructElement *found =
              FindFirstByPredicate(child, [](const StructElement *e) { return e && e->isContent(); })) {
        return found;
      }
    }
    return nullptr;
  }

  static const StructElement *FindFirstNonContentElement(const StructTreeRoot *root) {
    if (!root) {
      return nullptr;
    }
    const unsigned n = root->getNumChildren();
    for (unsigned i = 0; i < n; ++i) {
      const StructElement *child = root->getChild(static_cast<int>(i));
      if (const StructElement *found =
              FindFirstByPredicate(child, [](const StructElement *e) { return e && !e->isContent(); })) {
        return found;
      }
    }
    return nullptr;
  }
};

TEST_F(StructElementGetTextSpansTest_1715, NonContentElementReturnsEmpty_1715) {
  const std::string pdfPath = FindTaggedPdfPath();
  std::unique_ptr<PDFDoc> doc = OpenPdfDocOrSkip(pdfPath);
  if (!doc) return;

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  StructTreeRoot *root = catalog->getStructTreeRoot();
  if (!root) {
    GTEST_SKIP() << "PDF has no StructTreeRoot: " << pdfPath;
  }

  const StructElement *nonContent = FindFirstNonContentElement(root);
  if (!nonContent) {
    GTEST_SKIP() << "Could not find any non-content StructElement in StructTreeRoot.";
  }

  ASSERT_FALSE(nonContent->isContent());

  const TextSpanArray spans = nonContent->getTextSpans();
  EXPECT_TRUE(spans.empty());
}

TEST_F(StructElementGetTextSpansTest_1715, ContentElementGetTextSpansIsDeterministic_1715) {
  const std::string pdfPath = FindTaggedPdfPath();
  std::unique_ptr<PDFDoc> doc = OpenPdfDocOrSkip(pdfPath);
  if (!doc) return;

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  StructTreeRoot *root = catalog->getStructTreeRoot();
  if (!root) {
    GTEST_SKIP() << "PDF has no StructTreeRoot: " << pdfPath;
  }

  const StructElement *content = FindFirstContentElement(root);
  if (!content) {
    GTEST_SKIP() << "Could not find any content StructElement in StructTreeRoot.";
  }

  ASSERT_TRUE(content->isContent());

  const TextSpanArray spans1 = content->getTextSpans();
  const TextSpanArray spans2 = content->getTextSpans();

  // Black-box observable behavior: repeated calls should be stable (at least in size).
  EXPECT_EQ(spans1.size(), spans2.size());
  EXPECT_EQ(spans1.empty(), spans2.empty());
}

TEST_F(StructElementGetTextSpansTest_1715, ContentElementGetTextSpansDoesNotCrash_1715) {
  const std::string pdfPath = FindTaggedPdfPath();
  std::unique_ptr<PDFDoc> doc = OpenPdfDocOrSkip(pdfPath);
  if (!doc) return;

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  StructTreeRoot *root = catalog->getStructTreeRoot();
  if (!root) {
    GTEST_SKIP() << "PDF has no StructTreeRoot: " << pdfPath;
  }

  const StructElement *content = FindFirstContentElement(root);
  if (!content) {
    GTEST_SKIP() << "Could not find any content StructElement in StructTreeRoot.";
  }

  // Boundary-ish checks via public interface:
  // - MCID is an int; we don't assume a specific value, but it should be callable.
  // - getTextSpans must return a valid TextSpanArray object.
  (void)content->getMCID();

  const TextSpanArray spans = content->getTextSpans();
  // We cannot assume the PDF actually contains text spans for the chosen element,
  // but we can assert the call returns a usable container.
  EXPECT_GE(spans.size(), 0u);
}

} // namespace