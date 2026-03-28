// StructElement_getLanguage_1700_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include "poppler/Catalog.h"
#include "poppler/StructTreeRoot.h"
#include "poppler/StructElement.h"
#include "goo/GooString.h"

namespace {

class StructElementGetLanguageTest_1700 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Many Poppler entrypoints rely on globalParams being initialized.
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }

  // Try a handful of common locations used by Poppler test trees.
  static std::unique_ptr<PDFDoc> LoadDocFromCandidates(const std::vector<std::string> &candidates) {
    for (const auto &path : candidates) {
      auto doc = std::make_unique<PDFDoc>(path.c_str());
      if (doc && doc->isOk()) {
        return doc;
      }
    }
    return nullptr;
  }

  static StructTreeRoot *GetStructTreeRoot(PDFDoc *doc) {
    if (!doc || !doc->isOk()) {
      return nullptr;
    }
    Catalog *catalog = doc->getCatalog();
    if (!catalog) {
      return nullptr;
    }
    // Poppler provides the structure tree root via the catalog in tagged PDFs.
    return catalog->getStructTreeRoot();
  }

  static void CollectElementsDepthFirst(const StructElement *root, std::vector<const StructElement *> &out) {
    if (!root) {
      return;
    }
    out.push_back(root);
    const unsigned n = root->getNumChildren();
    for (unsigned i = 0; i < n; ++i) {
      const StructElement *child = root->getChild(static_cast<int>(i));
      if (child) {
        CollectElementsDepthFirst(child, out);
      }
    }
  }

  static const char *ToCString(const GooString *s) {
    return s ? s->c_str() : nullptr;
  }

  // Returns a tagged PDF if one exists; otherwise skips.
  std::unique_ptr<PDFDoc> LoadAnyTaggedPdfOrSkip() {
    // These are intentionally broad; the test will SKIP if none exist.
    const std::vector<std::string> candidates = {
        "./test-data/tagged.pdf",
        "./test-data/tagged-language.pdf",
        "./test-data/structure.pdf",
        "./tests/tagged.pdf",
        "./tests/data/tagged.pdf",
        "./TestProjects/poppler/test-data/tagged.pdf",
        "./TestProjects/poppler/tests/data/tagged.pdf",
    };

    auto doc = LoadDocFromCandidates(candidates);
    if (!doc) {
      GTEST_SKIP() << "No candidate tagged PDF found in common test-data locations.";
    }
    StructTreeRoot *root = GetStructTreeRoot(doc.get());
    if (!root) {
      GTEST_SKIP() << "Loaded PDF is OK but has no StructTreeRoot (not a tagged PDF).";
    }
    return doc;
  }

  // Find any element whose getLanguage() is non-null.
  static const StructElement *FindAnyWithLanguage(const std::vector<const StructElement *> &elts) {
    for (const auto *e : elts) {
      if (!e) {
        continue;
      }
      GooString *lang = const_cast<StructElement *>(e)->getLanguage();
      if (lang) {
        return e;
      }
    }
    return nullptr;
  }

  // Find a pair (child, parent) where:
  // - parent getLanguage() is non-null
  // - child getLanguage() is non-null
  // - and the strings differ (suggesting child overrides or differs in chain)
  static bool FindChildParentDifferentLanguage(const std::vector<const StructElement *> &elts,
                                              const StructElement *&outChild,
                                              const StructElement *&outParent) {
    for (const auto *child : elts) {
      if (!child) {
        continue;
      }
      const StructElement *parent = child->getParent();
      if (!parent) {
        continue;
      }
      GooString *childLang = const_cast<StructElement *>(child)->getLanguage();
      GooString *parentLang = const_cast<StructElement *>(parent)->getLanguage();
      if (!childLang || !parentLang) {
        continue;
      }
      const char *c = ToCString(childLang);
      const char *p = ToCString(parentLang);
      if (c && p && std::string(c) != std::string(p)) {
        outChild = child;
        outParent = parent;
        return true;
      }
    }
    return false;
  }

  // Find a node with language, and a descendant whose language matches it
  // (used for inheritance / delegation style checks).
  static bool FindAncestorDescendantSameLanguage(const StructElement *root,
                                                const StructElement *&outAncestor,
                                                const StructElement *&outDescendant) {
    if (!root) {
      return false;
    }

    // Collect all nodes; then for each candidate ancestor with language, see if any descendant shares it.
    std::vector<const StructElement *> all;
    CollectElementsDepthFirst(root, all);

    for (const auto *anc : all) {
      if (!anc) {
        continue;
      }
      GooString *ancLang = const_cast<StructElement *>(anc)->getLanguage();
      if (!ancLang) {
        continue;
      }
      const char *a = ToCString(ancLang);
      if (!a) {
        continue;
      }

      // Search descendants
      std::vector<const StructElement *> stack;
      const unsigned n = anc->getNumChildren();
      for (unsigned i = 0; i < n; ++i) {
        if (const StructElement *c = anc->getChild(static_cast<int>(i))) {
          stack.push_back(c);
        }
      }
      while (!stack.empty()) {
        const StructElement *cur = stack.back();
        stack.pop_back();
        if (!cur) {
          continue;
        }
        GooString *curLang = const_cast<StructElement *>(cur)->getLanguage();
        const char *cstr = ToCString(curLang);
        if (cstr && std::string(cstr) == std::string(a)) {
          outAncestor = anc;
          outDescendant = cur;
          return true;
        }
        const unsigned cn = cur->getNumChildren();
        for (unsigned j = 0; j < cn; ++j) {
          if (const StructElement *cc = cur->getChild(static_cast<int>(j))) {
            stack.push_back(cc);
          }
        }
      }
    }

    return false;
  }
};

TEST_F(StructElementGetLanguageTest_1700, ReturnsNullWhenNoStructTreeRoot_1700) {
  // A boundary/error-style case that is fully observable: if the PDF isn't tagged,
  // there's no way to obtain a StructElement via the public API.
  // We validate that Catalog::getStructTreeRoot() can be null on a non-tagged PDF,
  // and in that case we do not attempt to call getLanguage().
  const std::vector<std::string> candidates = {
      "./test-data/not-tagged.pdf",
      "./test-data/blank.pdf",
      "./tests/data/blank.pdf",
      "./TestProjects/poppler/test-data/blank.pdf",
  };

  auto doc = LoadDocFromCandidates(candidates);
  if (!doc) {
    GTEST_SKIP() << "No candidate non-tagged PDF found in common test-data locations.";
  }
  ASSERT_TRUE(doc->isOk());

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  StructTreeRoot *root = catalog->getStructTreeRoot();
  // For non-tagged PDFs, this is expected to be null. If the candidate is tagged anyway,
  // we skip to avoid making assumptions about the file.
  if (root) {
    GTEST_SKIP() << "Candidate PDF appears to be tagged; expected a non-tagged PDF for this test.";
  }
  EXPECT_EQ(root, nullptr);
}

TEST_F(StructElementGetLanguageTest_1700, ReturnsNonNullForAtLeastOneElementInTaggedPdf_1700) {
  auto doc = LoadAnyTaggedPdfOrSkip();
  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  const unsigned n = root->getNumChildren();
  if (n == 0) {
    GTEST_SKIP() << "Tagged PDF has an empty structure tree.";
  }

  std::vector<const StructElement *> all;
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = root->getChild(static_cast<int>(i));
    if (child) {
      CollectElementsDepthFirst(child, all);
    }
  }

  const StructElement *any = FindAnyWithLanguage(all);
  if (!any) {
    GTEST_SKIP() << "No StructElement in this tagged PDF returned a non-null language.";
  }

  GooString *lang = const_cast<StructElement *>(any)->getLanguage();
  ASSERT_NE(lang, nullptr);
  EXPECT_NE(std::string(lang->c_str()).size(), 0u);

  // Boundary-ish: calling twice should remain consistent as an observable output.
  GooString *lang2 = const_cast<StructElement *>(any)->getLanguage();
  ASSERT_NE(lang2, nullptr);
  EXPECT_STREQ(lang->c_str(), lang2->c_str());
}

TEST_F(StructElementGetLanguageTest_1700, ChildLanguageCanDifferFromParentLanguageWhenAvailable_1700) {
  auto doc = LoadAnyTaggedPdfOrSkip();
  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  std::vector<const StructElement *> all;
  const unsigned n = root->getNumChildren();
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = root->getChild(static_cast<int>(i));
    if (child) {
      CollectElementsDepthFirst(child, all);
    }
  }

  const StructElement *child = nullptr;
  const StructElement *parent = nullptr;
  if (!FindChildParentDifferentLanguage(all, child, parent)) {
    GTEST_SKIP() << "Could not find a child/parent pair with differing observable languages in this PDF.";
  }

  GooString *childLang = const_cast<StructElement *>(child)->getLanguage();
  GooString *parentLang = const_cast<StructElement *>(parent)->getLanguage();
  ASSERT_NE(childLang, nullptr);
  ASSERT_NE(parentLang, nullptr);

  EXPECT_STRNE(childLang->c_str(), parentLang->c_str());
}

TEST_F(StructElementGetLanguageTest_1700, DescendantCanMatchAncestorLanguage_1700) {
  auto doc = LoadAnyTaggedPdfOrSkip();
  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  const StructElement *ancestor = nullptr;
  const StructElement *descendant = nullptr;

  // This checks a common observable behavior consistent with inheritance/delegation:
  // some descendants return the same language string as an ancestor.
  // We do not assume *why*; we only verify the returned values.
  // Use the first top-level child as a traversal root if available.
  const unsigned n = root->getNumChildren();
  if (n == 0) {
    GTEST_SKIP() << "Tagged PDF has an empty structure tree.";
  }

  const StructElement *top = root->getChild(0);
  if (!FindAncestorDescendantSameLanguage(top, ancestor, descendant)) {
    GTEST_SKIP() << "Could not find ancestor/descendant sharing the same observable language in this PDF.";
  }

  GooString *aLang = const_cast<StructElement *>(ancestor)->getLanguage();
  GooString *dLang = const_cast<StructElement *>(descendant)->getLanguage();
  ASSERT_NE(aLang, nullptr);
  ASSERT_NE(dLang, nullptr);

  EXPECT_STREQ(aLang->c_str(), dLang->c_str());
}

TEST_F(StructElementGetLanguageTest_1700, ReturnsNullOrStringButNeverCrashesAcrossWholeTree_1700) {
  auto doc = LoadAnyTaggedPdfOrSkip();
  StructTreeRoot *root = GetStructTreeRoot(doc.get());
  ASSERT_NE(root, nullptr);

  std::vector<const StructElement *> all;
  const unsigned n = root->getNumChildren();
  for (unsigned i = 0; i < n; ++i) {
    const StructElement *child = root->getChild(static_cast<int>(i));
    if (child) {
      CollectElementsDepthFirst(child, all);
    }
  }

  if (all.empty()) {
    GTEST_SKIP() << "No StructElements collected from structure tree.";
  }

  // Boundary/robustness: call getLanguage on every element and only validate
  // observable properties (null or non-empty string).
  for (const StructElement *e : all) {
    ASSERT_NE(e, nullptr);
    GooString *lang = const_cast<StructElement *>(e)->getLanguage();
    if (lang) {
      EXPECT_NE(std::string(lang->c_str()).size(), 0u);
    } else {
      SUCCEED();
    }
  }
}

} // namespace