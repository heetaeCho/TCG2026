// poppler_structure_element_iter_get_element_test_2539.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

namespace {

class PopplerStructureElementIterGetElementTest_2539 : public ::testing::Test {
protected:
  static gchar *FindStructurePdfPathOrNull()
  {
    // Allow override via env var (useful for different build layouts).
    const char *env = g_getenv("POPPLER_TEST_STRUCTURE_PDF");
    if (env && *env) {
      if (g_file_test(env, G_FILE_TEST_EXISTS)) {
        return g_strdup(env);
      }
    }

    // Try common locations used in Poppler / downstream test suites.
    const char *candidates[] = {
        "tagged.pdf",
        "tests/tagged.pdf",
        "testdata/tagged.pdf",
        "test-data/tagged.pdf",
        "glib/tests/tagged.pdf",
        "glib/test/tagged.pdf",
        "glib/testdata/tagged.pdf",
        "TestProjects/poppler/testdata/tagged.pdf",
        "TestProjects/poppler/test-data/tagged.pdf",
        nullptr,
    };

    for (int i = 0; candidates[i] != nullptr; ++i) {
      if (g_file_test(candidates[i], G_FILE_TEST_EXISTS)) {
        return g_strdup(candidates[i]);
      }
    }
    return nullptr;
  }

  static PopplerDocument *LoadDocWithStructureOrSkip()
  {
    g_autofree gchar *path = FindStructurePdfPathOrNull();
    if (!path) {
      GTEST_SKIP() << "No tagged/structured PDF found. Set POPPLER_TEST_STRUCTURE_PDF to a file path.";
      return nullptr;
    }

    g_autoptr(GError) error = nullptr;
    g_autofree gchar *uri = g_filename_to_uri(path, /*hostname=*/nullptr, &error);
    if (!uri) {
      GTEST_SKIP() << "Failed to create file URI for test PDF: " << (error ? error->message : "unknown error");
      return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    if (!doc) {
      GTEST_SKIP() << "Failed to open test PDF: " << (error ? error->message : "unknown error");
      return nullptr;
    }
    return doc;
  }
};

TEST_F(PopplerStructureElementIterGetElementTest_2539, NullIterReturnsNull_2539)
{
  // Observable behavior from g_return_val_if_fail(): returns NULL when iter is nullptr.
  EXPECT_EQ(poppler_structure_element_iter_get_element(nullptr), nullptr);
}

TEST_F(PopplerStructureElementIterGetElementTest_2539, RootIterGetElementReturnsElementOrSkips_2539)
{
  g_autoptr(PopplerDocument) doc = LoadDocWithStructureOrSkip();
  if (!doc) {
    return;
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    GTEST_SKIP() << "Document appears to have no structure tree (iter_new returned NULL).";
    return;
  }

  PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
  ASSERT_NE(elem, nullptr);

  // Minimal observable: element is a GObject of the expected type.
  EXPECT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(elem));

  g_object_unref(elem);
  poppler_structure_element_iter_free(iter);
}

TEST_F(PopplerStructureElementIterGetElementTest_2539, TraversalGetElementNonNullUntilEnd_2539)
{
  g_autoptr(PopplerDocument) doc = LoadDocWithStructureOrSkip();
  if (!doc) {
    return;
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    GTEST_SKIP() << "Document appears to have no structure tree (iter_new returned NULL).";
    return;
  }

  int visited = 0;
  // Hard cap to avoid hanging in case of unexpected iterator behavior.
  for (int steps = 0; steps < 200; ++steps) {
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    ASSERT_NE(elem, nullptr) << "get_element returned NULL while iter is expected to be valid at step " << steps;
    EXPECT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(elem));
    g_object_unref(elem);

    ++visited;
    if (!poppler_structure_element_iter_next(iter)) {
      break; // boundary: end reached
    }

    if (steps == 199) {
      ADD_FAILURE() << "Iterator did not terminate within 200 steps; possible non-terminating traversal.";
    }
  }

  EXPECT_GE(visited, 1);
  poppler_structure_element_iter_free(iter);
}

TEST_F(PopplerStructureElementIterGetElementTest_2539, ChildIteratorGetElementWhenChildExists_2539)
{
  g_autoptr(PopplerDocument) doc = LoadDocWithStructureOrSkip();
  if (!doc) {
    return;
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    GTEST_SKIP() << "Document appears to have no structure tree (iter_new returned NULL).";
    return;
  }

  PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
  if (!child) {
    // Valid boundary condition: element may have no children.
    poppler_structure_element_iter_free(iter);
    GTEST_SKIP() << "Root-level iterator has no children in this document.";
    return;
  }

  PopplerStructureElement *child_elem = poppler_structure_element_iter_get_element(child);
  ASSERT_NE(child_elem, nullptr);
  EXPECT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(child_elem));

  g_object_unref(child_elem);
  poppler_structure_element_iter_free(child);
  poppler_structure_element_iter_free(iter);
}

TEST_F(PopplerStructureElementIterGetElementTest_2539, GetElementCanBeCalledMultipleTimes_2539)
{
  g_autoptr(PopplerDocument) doc = LoadDocWithStructureOrSkip();
  if (!doc) {
    return;
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    GTEST_SKIP() << "Document appears to have no structure tree (iter_new returned NULL).";
    return;
  }

  // The API says [transfer full]; we only assert both are valid and independently unref-able.
  PopplerStructureElement *e1 = poppler_structure_element_iter_get_element(iter);
  PopplerStructureElement *e2 = poppler_structure_element_iter_get_element(iter);

  ASSERT_NE(e1, nullptr);
  ASSERT_NE(e2, nullptr);
  EXPECT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(e1));
  EXPECT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(e2));

  g_object_unref(e1);
  g_object_unref(e2);
  poppler_structure_element_iter_free(iter);
}

} // namespace