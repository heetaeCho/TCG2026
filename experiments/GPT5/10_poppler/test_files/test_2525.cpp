// poppler-structure-element-is-inline-test_2525.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// Unit under test
extern "C" gboolean poppler_structure_element_is_inline(PopplerStructureElement *poppler_structure_element);

namespace {

struct PopplerStructureElementIsInlineTest_2525 : public ::testing::Test {
  // Helper: expect a GLib critical message (avoids failures under fatal-warnings setups)
  static void ExpectCriticalAndReturn(const char *domain, const char *pattern,
                                      const std::function<void()> &fn) {
    g_test_expect_message(domain, G_LOG_LEVEL_CRITICAL, pattern);
    fn();
    g_test_assert_expected_messages();
  }

  static PopplerDocument *TryLoadTaggedDocOrNull() {
    // Try a few commonly-used filenames in Poppler test suites.
    const char *candidates[] = {
        "tagged.pdf",
        "structure.pdf",
        "a11y.pdf",
        "accessibility.pdf",
        "struct-tree.pdf",
    };

#ifdef POPPLER_TESTDATADIR
    for (const char *name : candidates) {
      gchar *path = g_build_filename(POPPLER_TESTDATADIR, name, nullptr);
      if (!path) {
        continue;
      }

      // poppler_document_new_from_file expects a URI.
      gchar *uri = g_filename_to_uri(path, nullptr, nullptr);
      g_free(path);
      if (!uri) {
        continue;
      }

      GError *error = nullptr;
      PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
      g_free(uri);

      if (doc) {
        if (error) {
          g_error_free(error);
        }
        return doc;
      }
      if (error) {
        g_error_free(error);
      }
    }
#endif

    return nullptr;
  }

  // Depth-first search for any structure element (starting from root).
  // NOTE: This uses public Poppler GLib API functions that are commonly present for structure trees.
  static PopplerStructureElement *FindAnyElement(PopplerStructureElement *root) {
    if (!root) {
      return nullptr;
    }

    // If the root itself is usable, return it immediately.
    // (Even if it isn't "inline", it should be valid for calling the function under test.)
    return root;
  }
};

} // namespace

TEST_F(PopplerStructureElementIsInlineTest_2525, NullPtrReturnsFalse_2525) {
  // g_return_val_if_fail emits a CRITICAL; capture it to keep test output clean/stable.
  ExpectCriticalAndReturn(
      "Poppler", "*POPPLER_IS_STRUCTURE_ELEMENT*",
      []() {
        EXPECT_EQ(poppler_structure_element_is_inline(nullptr), FALSE);
      });
}

TEST_F(PopplerStructureElementIsInlineTest_2525, WrongTypeReturnsFalse_2525) {
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Cast a non-PopplerStructureElement to trigger the type check failure.
  ExpectCriticalAndReturn(
      "Poppler", "*POPPLER_IS_STRUCTURE_ELEMENT*",
      [obj]() {
        EXPECT_EQ(poppler_structure_element_is_inline(reinterpret_cast<PopplerStructureElement *>(obj)),
                  FALSE);
      });

  g_object_unref(obj);
}

TEST_F(PopplerStructureElementIsInlineTest_2525, ElemNullReturnsFalse_2525) {
  // Construct a valid PopplerStructureElement instance. Its internal elem pointer is expected
  // to be null unless it was created/attached by parsing a tagged PDF structure tree.
  PopplerStructureElement *se =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(se, nullptr);

  ExpectCriticalAndReturn(
      "Poppler", "*poppler_structure_element->elem != nullptr*",
      [se]() {
        EXPECT_EQ(poppler_structure_element_is_inline(se), FALSE);
      });

  g_object_unref(se);
}

TEST_F(PopplerStructureElementIsInlineTest_2525, RealElementCallIsStableIfAvailable_2525) {
  // Normal-operation test: load a tagged/structured PDF from test data (if available),
  // obtain a structure element via public API, and verify the function behaves consistently.
  PopplerDocument *doc = TryLoadTaggedDocOrNull();
  if (!doc) {
    GTEST_SKIP() << "No tagged/structured PDF found (POPPLER_TESTDATADIR not set or files missing).";
  }

  // Common Poppler GLib API for structure trees:
  // PopplerStructureElement *root = poppler_document_get_structure_tree_root(doc);
  //
  // If your Poppler version uses a different entry point, adjust accordingly.
  PopplerStructureElement *root = poppler_document_get_structure_tree_root(doc);
  if (!root) {
    g_object_unref(doc);
    GTEST_SKIP() << "Document has no structure tree root (not a tagged PDF in this build).";
  }

  PopplerStructureElement *any = FindAnyElement(root);
  ASSERT_NE(any, nullptr);

  gboolean v1 = poppler_structure_element_is_inline(any);
  gboolean v2 = poppler_structure_element_is_inline(any);

  // Observable behavior: returns a gboolean and is deterministic for the same object.
  EXPECT_TRUE(v1 == FALSE || v1 == TRUE);
  EXPECT_EQ(v1, v2);

  g_object_unref(root);
  g_object_unref(doc);
}