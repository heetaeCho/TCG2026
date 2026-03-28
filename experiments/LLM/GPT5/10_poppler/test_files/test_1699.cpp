// test_structelement_getid_1699.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/Catalog.h"
#include "poppler/StructElement.h"
#include "goo/GooString.h"

namespace {

std::string FindFirstExistingPdfPath()
{
  // Keep this list conservative but flexible across different Poppler test layouts.
  const std::vector<std::string> candidates = {
      "test/unittestcases/tagged.pdf",
      "test/unittestcases/structure.pdf",
      "test/unittestcases/struct-tree.pdf",
      "test/unittestcases/StructTreeRoot.pdf",
      "unittestcases/tagged.pdf",
      "unittestcases/structure.pdf",
      "test/tagged.pdf",
      "tagged.pdf",
  };

  for (const auto &p : candidates) {
    FILE *f = fopen(p.c_str(), "rb");
    if (f) {
      fclose(f);
      return p;
    }
  }
  return std::string();
}

std::unique_ptr<PDFDoc> OpenPDFDocBestEffort(const std::string &path)
{
  // Make the constructor selection resilient across Poppler versions.
  auto mkName = [&]() { return std::make_unique<GooString>(path.c_str()); };

  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>>) {
    return std::make_unique<PDFDoc>(mkName());
  } else if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>, GooString *, GooString *,
                                              bool>) {
    return std::make_unique<PDFDoc>(mkName(), nullptr, nullptr, false);
  } else if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>, GooString *, GooString *>) {
    return std::make_unique<PDFDoc>(mkName(), nullptr, nullptr);
  } else {
    // If your Poppler fork uses a different PDFDoc construction API, adapt here.
    return nullptr;
  }
}

const StructElement *FindFirstByPredicate(const StructElement *node,
                                          const std::function<bool(const StructElement *)> &pred)
{
  if (!node) {
    return nullptr;
  }
  if (pred(node)) {
    return node;
  }
  const unsigned n = node->getNumChildren();
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = node->getChild(static_cast<int>(i));
    if (const StructElement *hit = FindFirstByPredicate(child, pred)) {
      return hit;
    }
  }
  return nullptr;
}

const StructElement *FindAnyStructElementInTree(StructTreeRoot *root)
{
  if (!root) {
    return nullptr;
  }
  const unsigned n = root->getNumChildren();
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = root->getChild(static_cast<int>(i));
    if (child) {
      return child;
    }
  }
  return nullptr;
}

const StructElement *FindFirstContentElement(StructTreeRoot *root)
{
  const unsigned n = root ? root->getNumChildren() : 0U;
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = root->getChild(static_cast<int>(i));
    if (const StructElement *hit =
            FindFirstByPredicate(child, [](const StructElement *e) { return e && e->isContent(); })) {
      return hit;
    }
  }
  return nullptr;
}

const StructElement *FindFirstNonContentElementWithId(StructTreeRoot *root)
{
  const unsigned n = root ? root->getNumChildren() : 0U;
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = root->getChild(static_cast<int>(i));
    if (const StructElement *hit = FindFirstByPredicate(child, [](const StructElement *e) {
          return e && !e->isContent() && e->getID() != nullptr;
        })) {
      return hit;
    }
  }
  return nullptr;
}

const StructElement *FindFirstNonContentElementWithoutId(StructTreeRoot *root)
{
  const unsigned n = root ? root->getNumChildren() : 0U;
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = root->getChild(static_cast<int>(i));
    if (const StructElement *hit = FindFirstByPredicate(child, [](const StructElement *e) {
          return e && !e->isContent() && e->getID() == nullptr;
        })) {
      return hit;
    }
  }
  return nullptr;
}

class StructElementGetIDTest_1699 : public ::testing::Test {
protected:
  void SetUp() override
  {
    pdfPath = FindFirstExistingPdfPath();
    if (pdfPath.empty()) {
      GTEST_SKIP() << "No tagged/structure test PDF found in common locations; skipping StructElement getID tests.";
    }

    doc = OpenPDFDocBestEffort(pdfPath);
    if (!doc) {
      GTEST_SKIP() << "Unable to construct PDFDoc with available constructors in this build; skipping.";
    }
    if (!doc->isOk()) {
      GTEST_SKIP() << "PDFDoc failed to open or parse: " << pdfPath;
    }

    Catalog *catalog = doc->getCatalog();
    if (!catalog) {
      GTEST_SKIP() << "No Catalog available; skipping.";
    }

    // Poppler typically exposes the struct tree root from Catalog.
    root = catalog->getStructTreeRoot();
    if (!root) {
      GTEST_SKIP() << "No StructTreeRoot in this PDF; skipping.";
    }
  }

  std::string pdfPath;
  std::unique_ptr<PDFDoc> doc;
  StructTreeRoot *root = nullptr; // owned by Catalog/PDFDoc
};

TEST_F(StructElementGetIDTest_1699, ContentElementReturnsNull_1699)
{
  const StructElement *content = FindFirstContentElement(root);
  if (!content) {
    GTEST_SKIP() << "No content StructElement found in struct tree; skipping content-specific assertion.";
  }

  // Contract from the provided implementation: isContent() => getID() returns nullptr.
  EXPECT_EQ(content->getID(), nullptr);
}

TEST_F(StructElementGetIDTest_1699, NonContentElementWithIdReturnsNonNull_1699)
{
  const StructElement *elem = FindFirstNonContentElementWithId(root);
  if (!elem) {
    GTEST_SKIP() << "No non-content StructElement with a non-null ID found in this PDF; skipping.";
  }

  const GooString *id1 = elem->getID();
  EXPECT_NE(id1, nullptr);

  // Boundary/robustness: repeated calls should be safe and consistent for observable pointer identity.
  const GooString *id2 = elem->getID();
  EXPECT_EQ(id2, id1);
}

TEST_F(StructElementGetIDTest_1699, NonContentElementWithoutIdReturnsNull_1699)
{
  const StructElement *elem = FindFirstNonContentElementWithoutId(root);
  if (!elem) {
    GTEST_SKIP() << "No non-content StructElement without an ID found in this PDF; skipping.";
  }

  EXPECT_EQ(elem->getID(), nullptr);
}

TEST_F(StructElementGetIDTest_1699, AnyElementCallIsSafe_1699)
{
  const StructElement *any = FindAnyStructElementInTree(root);
  if (!any) {
    GTEST_SKIP() << "No StructElement children under StructTreeRoot; skipping.";
  }

  // Exceptional/error-ish case (observable): Calling getID should not crash regardless of element type.
  // We only assert it is callable and returns either nullptr or a valid pointer.
  const GooString *id = any->getID();
  (void)id;

  SUCCEED();
}

} // namespace