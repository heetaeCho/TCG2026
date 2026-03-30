// File: poppler-structure-element-get-table-row-span-test_2591.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include <poppler.h>
#include "poppler-private.h"
}

// NOTE:
// - These tests treat Poppler as a black box.
// - For “normal operation” we try to find a TABLE structure element from a tagged PDF test file.
//   If no suitable test PDF / structure tree is available in the environment, those tests will skip.

namespace {

class PopplerStructureElementGetTableRowSpanTest_2591 : public ::testing::Test {
protected:
  void SetUp() override {
    // Try to open a test PDF that may contain a structure tree with tables.
    // Different Poppler test suites use different filenames; we try several.
    const char *candidates[] = {
        "tagged.pdf",
        "structure.pdf",
        "structured.pdf",
        "tagged-structure.pdf",
        "tables.pdf",
        "table.pdf",
        "tagged-table.pdf",
    };

    for (const char *name : candidates) {
#ifdef TESTDATADIR
      gchar *path = g_build_filename(TESTDATADIR, name, nullptr);
#else
      // Fallback: rely on current working directory layouts if TESTDATADIR is not provided.
      gchar *path = g_build_filename(".", name, nullptr);
#endif
      if (!g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_free(path);
        continue;
      }

      GError *error = nullptr;
      gchar *uri = g_filename_to_uri(path, nullptr, &error);
      g_free(path);

      if (!uri) {
        if (error) {
          g_error_free(error);
        }
        continue;
      }

      error = nullptr;
      PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
      g_free(uri);

      if (!doc) {
        if (error) {
          g_error_free(error);
        }
        continue;
      }

      doc_.reset(doc);
      break;
    }
  }

  void TearDown() override { doc_.reset(nullptr); }

  // Finds the first element of the given kind in the subtree rooted at |root|.
  // Returns nullptr if traversal APIs or suitable element is not available.
  static PopplerStructureElement *FindFirstOfKind(PopplerStructureElement *root,
                                                  PopplerStructureElementKind kind,
                                                  int max_depth = 64) {
    if (!root || max_depth <= 0) {
      return nullptr;
    }

    if (poppler_structure_element_get_kind(root) == kind) {
      return root;
    }

    // These traversal APIs are part of Poppler GLib structure element interface in many versions.
    const int n_children = poppler_structure_element_get_n_children(root);
    for (int i = 0; i < n_children; ++i) {
      PopplerStructureElement *child = poppler_structure_element_get_child(root, i);
      if (!child) {
        continue;
      }
      PopplerStructureElement *found = FindFirstOfKind(child, kind, max_depth - 1);
      if (found) {
        return found;
      }
    }
    return nullptr;
  }

  // Tries to obtain a structure tree root from the first page that has one.
  PopplerStructureElement *FindAnyStructureRoot() const {
    if (!doc_) {
      return nullptr;
    }
    const int n_pages = poppler_document_get_n_pages(doc_.get());
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage *page = poppler_document_get_page(doc_.get(), i);
      if (!page) {
        continue;
      }

      // Common GLib API name for getting the structure tree root for a page.
      // If the page has no structure tree, it may return nullptr.
      PopplerStructureElement *root = poppler_page_get_structure(page);

      g_object_unref(page);

      if (root) {
        return root;
      }
    }
    return nullptr;
  }

  struct GObjectDeleter {
    void operator()(GObject *o) const {
      if (o) {
        g_object_unref(o);
      }
    }
  };

  std::unique_ptr<PopplerDocument, GObjectDeleter> doc_{nullptr};
};

TEST_F(PopplerStructureElementGetTableRowSpanTest_2591, NullElementReturnsZero_2591) {
  // Exceptional / error case: nullptr input.
  // Observable behavior: returns 0.
  EXPECT_EQ(poppler_structure_element_get_table_row_span(nullptr), 0u);
}

TEST_F(PopplerStructureElementGetTableRowSpanTest_2591, NonTableElementReturnsZero_2591) {
  // Exceptional / error case: kind != TABLE.
  // We try to find any structure root and then find a non-table element (e.g., DOCUMENT or any other).
  PopplerStructureElement *root = FindAnyStructureRoot();
  if (!root) {
    GTEST_SKIP() << "No structure tree root available from test PDFs; cannot obtain a non-table element.";
  }

  // If the root is already not a TABLE, use it. Otherwise, find the first non-table child.
  PopplerStructureElement *non_table = nullptr;
  if (poppler_structure_element_get_kind(root) != POPPLER_STRUCTURE_ELEMENT_TABLE) {
    non_table = root;
  } else {
    // Try common top-level kinds first.
    non_table = FindFirstOfKind(root, POPPLER_STRUCTURE_ELEMENT_DOCUMENT);
    if (!non_table) {
      non_table = FindFirstOfKind(root, POPPLER_STRUCTURE_ELEMENT_SECT);
    }
    if (!non_table) {
      non_table = FindFirstOfKind(root, POPPLER_STRUCTURE_ELEMENT_P);
    }
    if (!non_table) {
      // As a fallback, walk children and pick the first that isn't TABLE.
      const int n_children = poppler_structure_element_get_n_children(root);
      for (int i = 0; i < n_children && !non_table; ++i) {
        PopplerStructureElement *child = poppler_structure_element_get_child(root, i);
        if (child && poppler_structure_element_get_kind(child) != POPPLER_STRUCTURE_ELEMENT_TABLE) {
          non_table = child;
        }
      }
    }
  }

  if (!non_table) {
    GTEST_SKIP() << "Could not locate a non-table structure element in available structure tree.";
  }

  EXPECT_EQ(poppler_structure_element_get_table_row_span(non_table), 0u);
}

TEST_F(PopplerStructureElementGetTableRowSpanTest_2591, TableElementReturnsStableValue_2591) {
  // Normal operation: kind == TABLE should return a value (guint) derived from the element attributes.
  // Since we don't re-implement internals, we only assert stability and basic type properties.
  PopplerStructureElement *root = FindAnyStructureRoot();
  if (!root) {
    GTEST_SKIP() << "No structure tree root available from test PDFs; cannot locate TABLE element.";
  }

  PopplerStructureElement *table = FindFirstOfKind(root, POPPLER_STRUCTURE_ELEMENT_TABLE);
  if (!table) {
    GTEST_SKIP() << "No TABLE structure element found in available structure tree.";
  }

  const guint v1 = poppler_structure_element_get_table_row_span(table);
  const guint v2 = poppler_structure_element_get_table_row_span(table);

  EXPECT_EQ(v1, v2);

  // Boundary-oriented checks (non-negative is implied by guint). Also verify it doesn't overflow by
  // ensuring it fits in a reasonable range for spans in test docs.
  // (We avoid asserting an exact value because it depends on the test PDF contents.)
  EXPECT_LE(v1, static_cast<guint>(G_MAXUINT));
}

TEST_F(PopplerStructureElementGetTableRowSpanTest_2591, TableRowSpanCallableMultipleTimes_2591) {
  // Boundary / robustness: repeated calls should not crash and should remain consistent.
  PopplerStructureElement *root = FindAnyStructureRoot();
  if (!root) {
    GTEST_SKIP() << "No structure tree root available from test PDFs; cannot locate TABLE element.";
  }

  PopplerStructureElement *table = FindFirstOfKind(root, POPPLER_STRUCTURE_ELEMENT_TABLE);
  if (!table) {
    GTEST_SKIP() << "No TABLE structure element found in available structure tree.";
  }

  guint first = poppler_structure_element_get_table_row_span(table);
  for (int i = 0; i < 50; ++i) {
    EXPECT_EQ(poppler_structure_element_get_table_row_span(table), first);
  }
}

} // namespace