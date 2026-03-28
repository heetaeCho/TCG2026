// File: poppler-structure-element-get-table-scope-test_2594.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

namespace {

static std::string ToFileUri(const std::string &path) {
  gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
  if (!uri)
    return std::string();
  std::string out(uri);
  g_free(uri);
  return out;
}

static std::string FindFirstExistingFile(const std::vector<std::string> &candidates) {
  for (const auto &p : candidates) {
    if (g_file_test(p.c_str(), G_FILE_TEST_EXISTS) && g_file_test(p.c_str(), G_FILE_TEST_IS_REGULAR)) {
      return p;
    }
  }
  return std::string();
}

static bool IsValidTableScope(PopplerStructureTableScope scope) {
  return scope == POPPLER_STRUCTURE_TABLE_SCOPE_ROW ||
         scope == POPPLER_STRUCTURE_TABLE_SCOPE_COLUMN ||
         scope == POPPLER_STRUCTURE_TABLE_SCOPE_BOTH;
}

static PopplerDocument *OpenDocOrSkip(const std::string &file_path) {
  std::string uri = ToFileUri(file_path);
  if (uri.empty()) {
    GTEST_SKIP() << "Failed to create file:// URI for: " << file_path;
  }

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error)
      g_error_free(error);
    GTEST_SKIP() << "Failed to open test PDF: " << file_path << " (" << msg << ")";
  }
  return doc;
}

static PopplerStructureElement *FindFirstElementByKind(PopplerStructureElementIter *iter,
                                                       PopplerStructureElementKind wanted) {
  if (!iter)
    return nullptr;

  // Depth-first walk: look at current element, then recurse to children, then advance siblings.
  do {
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    if (elem && poppler_structure_element_get_kind(elem) == wanted) {
      return elem; // borrowed; valid as long as iter/tree lives
    }

    PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
    if (child) {
      PopplerStructureElement *found = FindFirstElementByKind(child, wanted);
      poppler_structure_element_iter_free(child);
      if (found)
        return found;
    }
  } while (poppler_structure_element_iter_next(iter));

  return nullptr;
}

static PopplerStructureElement *FindFirstElementNotKind(PopplerStructureElementIter *iter,
                                                        PopplerStructureElementKind not_kind) {
  if (!iter)
    return nullptr;

  do {
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    if (elem && poppler_structure_element_get_kind(elem) != not_kind) {
      return elem; // borrowed
    }

    PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
    if (child) {
      PopplerStructureElement *found = FindFirstElementNotKind(child, not_kind);
      poppler_structure_element_iter_free(child);
      if (found)
        return found;
    }
  } while (poppler_structure_element_iter_next(iter));

  return nullptr;
}

class PopplerStructureElementGetTableScopeTest_2594 : public ::testing::Test {
protected:
  void TearDown() override {
    if (doc_)
      g_object_unref(doc_);
    doc_ = nullptr;
  }

  // Tries to locate a tagged PDF with a table in a few common Poppler test-data locations.
  // If none found, tests that require a real table element will be skipped.
  void LoadTaggedPdfOrSkip() {
    if (doc_)
      return;

    const std::vector<std::string> candidates = {
        // Common-ish names/paths used in various Poppler trees
        "test/unittest-data/tagged-table.pdf",
        "test/unittest-data/structure-table.pdf",
        "test/unittest-data/structure-tables.pdf",
        "test/unittest-data/tagged.pdf",
        "test/data/tagged-table.pdf",
        "test/data/structure-table.pdf",
        "test/data/tagged.pdf",
        "glib/tests/data/tagged-table.pdf",
        "glib/tests/data/tagged.pdf",
        "testfiles/tagged-table.pdf",
        "testfiles/tagged.pdf",
    };

    const std::string path = FindFirstExistingFile(candidates);
    if (path.empty()) {
      GTEST_SKIP() << "No suitable tagged PDF test-data file found (tried common candidates).";
    }

    doc_ = OpenDocOrSkip(path);
  }

  PopplerDocument *doc_ = nullptr;
};

} // namespace

TEST_F(PopplerStructureElementGetTableScopeTest_2594, NullElementReturnsDefault_2594) {
  // Observable behavior: should not crash; g_return_val_if_fail should return the default enum value.
  // From PopplerStructureTableScope enum ordering in docs, the first value is ROW.
  PopplerStructureTableScope scope = poppler_structure_element_get_table_scope(nullptr);
  EXPECT_EQ(scope, POPPLER_STRUCTURE_TABLE_SCOPE_ROW);
}

TEST_F(PopplerStructureElementGetTableScopeTest_2594, NonTableElementReturnsDefault_2594) {
  LoadTaggedPdfOrSkip();

  PopplerStructureElementIter *root = poppler_structure_element_iter_new(doc_);
  if (!root) {
    GTEST_SKIP() << "Document has no structure tree (poppler_structure_element_iter_new returned NULL).";
  }

  // Pick any element that is not a TABLE.
  PopplerStructureElement *non_table =
      FindFirstElementNotKind(root, POPPLER_STRUCTURE_ELEMENT_TABLE);

  if (!non_table) {
    poppler_structure_element_iter_free(root);
    GTEST_SKIP() << "Could not find a non-table structure element in the structure tree.";
  }

  PopplerStructureTableScope scope = poppler_structure_element_get_table_scope(non_table);

  // On kind mismatch, the function uses g_return_val_if_fail(..., default)
  EXPECT_EQ(scope, POPPLER_STRUCTURE_TABLE_SCOPE_ROW);

  poppler_structure_element_iter_free(root);
}

TEST_F(PopplerStructureElementGetTableScopeTest_2594, TableElementReturnsAValidScope_2594) {
  LoadTaggedPdfOrSkip();

  PopplerStructureElementIter *root = poppler_structure_element_iter_new(doc_);
  if (!root) {
    GTEST_SKIP() << "Document has no structure tree (poppler_structure_element_iter_new returned NULL).";
  }

  PopplerStructureElement *table =
      FindFirstElementByKind(root, POPPLER_STRUCTURE_ELEMENT_TABLE);

  if (!table) {
    poppler_structure_element_iter_free(root);
    GTEST_SKIP() << "No TABLE structure element found in the structure tree.";
  }

  PopplerStructureTableScope scope = poppler_structure_element_get_table_scope(table);
  EXPECT_TRUE(IsValidTableScope(scope));

  poppler_structure_element_iter_free(root);
}

TEST_F(PopplerStructureElementGetTableScopeTest_2594, TableElementScopeIsStableAcrossCalls_2594) {
  LoadTaggedPdfOrSkip();

  PopplerStructureElementIter *root = poppler_structure_element_iter_new(doc_);
  if (!root) {
    GTEST_SKIP() << "Document has no structure tree (poppler_structure_element_iter_new returned NULL).";
  }

  PopplerStructureElement *table =
      FindFirstElementByKind(root, POPPLER_STRUCTURE_ELEMENT_TABLE);

  if (!table) {
    poppler_structure_element_iter_free(root);
    GTEST_SKIP() << "No TABLE structure element found in the structure tree.";
  }

  PopplerStructureTableScope s1 = poppler_structure_element_get_table_scope(table);
  PopplerStructureTableScope s2 = poppler_structure_element_get_table_scope(table);

  EXPECT_TRUE(IsValidTableScope(s1));
  EXPECT_EQ(s1, s2);

  poppler_structure_element_iter_free(root);
}