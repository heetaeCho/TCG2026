// poppler_structure_element_get_text_spans_test_2550.cc
//
// Unit tests for poppler_structure_element_get_text_spans()
// File under test: ./TestProjects/poppler/glib/poppler-structure-element.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// ----------------------------------------------------------------------------
// Test helpers
// ----------------------------------------------------------------------------

namespace {

class PopplerStructureElementGetTextSpansTest_2550 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib criticals are not treated as fatal for these tests, because
    // the API uses g_return_val_if_fail() for argument validation.
    old_fatal_mask_ = g_log_set_fatal_mask(nullptr, G_LOG_LEVEL_ERROR);
  }

  void TearDown() override {
    g_log_set_fatal_mask(nullptr, old_fatal_mask_);
  }

  // Try to locate a tagged/structured PDF in common testdata locations.
  // If none are found, callers should GTEST_SKIP().
  static gchar *FindAnyStructuredPdf_2550() {
    // A small list of common filenames/locations used across Poppler test suites.
    const char *candidates[] = {
        "tagged.pdf",
        "structured.pdf",
        "structure.pdf",
        "testcases/tagged.pdf",
        "testcases/structured.pdf",
        "testcases/structure.pdf",
        "tests/tagged.pdf",
        "tests/structured.pdf",
        "tests/structure.pdf",
        "test-data/tagged.pdf",
        "test-data/structured.pdf",
        "test-data/structure.pdf",
        "data/tagged.pdf",
        "data/structured.pdf",
        "data/structure.pdf",
    };

    for (const char *rel : candidates) {
      if (g_file_test(rel, G_FILE_TEST_IS_REGULAR)) {
        return g_strdup(rel);
      }
    }
    return nullptr;
  }

  static PopplerDocument *LoadDocumentFromPath_2550(const gchar *path) {
    if (!path) {
      return nullptr;
    }
    // poppler_document_new_from_file expects a URI.
    // Convert local path -> file:// URI.
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(path, nullptr, &error);
    if (!uri) {
      if (error) {
        g_error_free(error);
      }
      return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);
    if (!doc) {
      if (error) {
        g_error_free(error);
      }
      return nullptr;
    }
    return doc;
  }

  struct FoundElementResult_2550 {
    PopplerStructureElement *element = nullptr; // borrowed (from iter_get_element)
    bool has_text_spans = false;
    guint n_spans = 0;
  };

  // Depth-first search: find either
  //  - a non-content element, or
  //  - a content element with non-null spans and n_spans > 0 (preferred).
  //
  // NOTE: This calls poppler_structure_element_get_text_spans() as part of the
  // search; tests that need a "content-with-spans" element should use this.
  static bool FindElementInTree_2550(PopplerStructureElementIter *iter,
                                    bool want_content_with_spans,
                                    FoundElementResult_2550 *out) {
    if (!iter || !out) {
      return false;
    }

    do {
      PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
      if (elem) {
        const gboolean is_content = poppler_structure_element_is_content(elem);

        if (!want_content_with_spans) {
          if (!is_content) {
            out->element = elem;
            out->has_text_spans = false;
            out->n_spans = 0;
            return true;
          }
        } else {
          if (is_content) {
            guint n = 0;
            PopplerTextSpan **spans = poppler_structure_element_get_text_spans(elem, &n);
            if (spans != nullptr && n > 0) {
              // Free what we allocated during search; caller will call again.
              for (guint i = 0; i < n; i++) {
                if (spans[i]) {
                  poppler_text_span_free(spans[i]);
                }
              }
              g_free(spans);

              out->element = elem;
              out->has_text_spans = true;
              out->n_spans = n;
              return true;
            }

            // Free if returned something with n==0 (or unexpected non-null).
            if (spans) {
              for (guint i = 0; i < n; i++) {
                if (spans[i]) {
                  poppler_text_span_free(spans[i]);
                }
              }
              g_free(spans);
            }
          }
        }
      }

      PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
      if (child) {
        const bool found = FindElementInTree_2550(child, want_content_with_spans, out);
        poppler_structure_element_iter_free(child);
        if (found) {
          return true;
        }
      }
    } while (poppler_structure_element_iter_next(iter));

    return false;
  }

private:
  GLogLevelFlags old_fatal_mask_{0};
};

} // namespace

// ----------------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------------

TEST_F(PopplerStructureElementGetTextSpansTest_2550, NullElementReturnsNull_2550) {
  guint n_spans = 123;
  EXPECT_EQ(poppler_structure_element_get_text_spans(nullptr, &n_spans), nullptr);
}

TEST_F(PopplerStructureElementGetTextSpansTest_2550, NullOutParamReturnsNull_2550) {
  // We need a valid PopplerStructureElement object to specifically exercise the
  // n_text_spans == nullptr precondition.
  gchar *pdf_path = FindAnyStructuredPdf_2550();
  if (!pdf_path) {
    GTEST_SKIP() << "No structured/tagged PDF found in common testdata locations.";
  }

  PopplerDocument *doc = LoadDocumentFromPath_2550(pdf_path);
  g_free(pdf_path);
  if (!doc) {
    GTEST_SKIP() << "Failed to load structured/tagged PDF (poppler_document_new_from_file failed).";
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    g_object_unref(doc);
    GTEST_SKIP() << "Document has no structure tree (poppler_structure_element_iter_new returned NULL).";
  }

  // Grab any element from the iterator (root-level current element).
  PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
  ASSERT_NE(elem, nullptr);

  EXPECT_EQ(poppler_structure_element_get_text_spans(elem, nullptr), nullptr);

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementGetTextSpansTest_2550, NonContentElementReturnsNullAndDoesNotChangeCount_2550) {
  gchar *pdf_path = FindAnyStructuredPdf_2550();
  if (!pdf_path) {
    GTEST_SKIP() << "No structured/tagged PDF found in common testdata locations.";
  }

  PopplerDocument *doc = LoadDocumentFromPath_2550(pdf_path);
  g_free(pdf_path);
  if (!doc) {
    GTEST_SKIP() << "Failed to load structured/tagged PDF (poppler_document_new_from_file failed).";
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    g_object_unref(doc);
    GTEST_SKIP() << "Document has no structure tree (poppler_structure_element_iter_new returned NULL).";
  }

  FoundElementResult_2550 found;
  if (!FindElementInTree_2550(iter, /*want_content_with_spans=*/false, &found) || !found.element) {
    poppler_structure_element_iter_free(iter);
    g_object_unref(doc);
    GTEST_SKIP() << "Could not find a non-content structure element in the tree.";
  }

  ASSERT_FALSE(poppler_structure_element_is_content(found.element));

  guint n_spans = 77; // sentinel
  PopplerTextSpan **spans = poppler_structure_element_get_text_spans(found.element, &n_spans);
  EXPECT_EQ(spans, nullptr);
  EXPECT_EQ(n_spans, 77u) << "n_text_spans should not be modified when returning NULL for non-content.";

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementGetTextSpansTest_2550, ContentElementReturnsArrayAndCountAndSpansHaveText_2550) {
  gchar *pdf_path = FindAnyStructuredPdf_2550();
  if (!pdf_path) {
    GTEST_SKIP() << "No structured/tagged PDF found in common testdata locations.";
  }

  PopplerDocument *doc = LoadDocumentFromPath_2550(pdf_path);
  g_free(pdf_path);
  if (!doc) {
    GTEST_SKIP() << "Failed to load structured/tagged PDF (poppler_document_new_from_file failed).";
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    g_object_unref(doc);
    GTEST_SKIP() << "Document has no structure tree (poppler_structure_element_iter_new returned NULL).";
  }

  FoundElementResult_2550 found;
  if (!FindElementInTree_2550(iter, /*want_content_with_spans=*/true, &found) || !found.element) {
    poppler_structure_element_iter_free(iter);
    g_object_unref(doc);
    GTEST_SKIP() << "Could not find a content structure element with text spans (n_spans > 0).";
  }

  ASSERT_TRUE(poppler_structure_element_is_content(found.element));

  guint n_spans = 0;
  PopplerTextSpan **spans = poppler_structure_element_get_text_spans(found.element, &n_spans);
  ASSERT_NE(spans, nullptr);
  ASSERT_GT(n_spans, 0u);

  for (guint i = 0; i < n_spans; i++) {
    ASSERT_NE(spans[i], nullptr) << "Span pointer at index " << i << " must not be NULL";
    const gchar *text = poppler_text_span_get_text(spans[i]);
    ASSERT_NE(text, nullptr) << "Span text must not be NULL";
    // Allow empty strings depending on PDF content; but must be a valid C string.
  }

  for (guint i = 0; i < n_spans; i++) {
    poppler_text_span_free(spans[i]);
  }
  g_free(spans);

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementGetTextSpansTest_2550, RepeatedCallsReturnIndependentArrays_2550) {
  gchar *pdf_path = FindAnyStructuredPdf_2550();
  if (!pdf_path) {
    GTEST_SKIP() << "No structured/tagged PDF found in common testdata locations.";
  }

  PopplerDocument *doc = LoadDocumentFromPath_2550(pdf_path);
  g_free(pdf_path);
  if (!doc) {
    GTEST_SKIP() << "Failed to load structured/tagged PDF (poppler_document_new_from_file failed).";
  }

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    g_object_unref(doc);
    GTEST_SKIP() << "Document has no structure tree (poppler_structure_element_iter_new returned NULL).";
  }

  FoundElementResult_2550 found;
  if (!FindElementInTree_2550(iter, /*want_content_with_spans=*/true, &found) || !found.element) {
    poppler_structure_element_iter_free(iter);
    g_object_unref(doc);
    GTEST_SKIP() << "Could not find a content structure element with text spans (n_spans > 0).";
  }

  guint n1 = 0, n2 = 0;
  PopplerTextSpan **a1 = poppler_structure_element_get_text_spans(found.element, &n1);
  PopplerTextSpan **a2 = poppler_structure_element_get_text_spans(found.element, &n2);

  ASSERT_NE(a1, nullptr);
  ASSERT_NE(a2, nullptr);
  EXPECT_EQ(n1, n2);
  EXPECT_NE(a1, a2) << "Each call should return a newly-allocated array (transfer full).";

  for (guint i = 0; i < n1; i++) {
    if (a1[i]) poppler_text_span_free(a1[i]);
  }
  g_free(a1);

  for (guint i = 0; i < n2; i++) {
    if (a2[i]) poppler_text_span_free(a2[i]);
  }
  g_free(a2);

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}