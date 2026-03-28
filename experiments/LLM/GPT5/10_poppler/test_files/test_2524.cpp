// poppler_structure_element_is_content_test_2524.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

namespace {

class PopplerStructureElementIsContentTest_2524 : public ::testing::Test {
protected:
  static gchar *FindTaggedPdfPathOrNull_2524() {
    // Allow overriding the test PDF via env var.
    const char *override_path = g_getenv("POPPLER_TEST_TAGGED_PDF");
    if (override_path && *override_path) {
      if (g_file_test(override_path, G_FILE_TEST_IS_REGULAR)) {
        return g_strdup(override_path);
      }
    }

    const char *testdatadir = g_getenv("TESTDATADIR");
    const char *srcdir = g_getenv("SRCDIR");

    const char *bases[] = {
        testdatadir,
        srcdir,
        ".",
    };

    const char *names[] = {
        "tagged.pdf",
        "tagged-structure.pdf",
        "structure.pdf",
        "struct-tree.pdf",
        "test-tagged.pdf",
    };

    for (const char *base : bases) {
      if (!base || !*base)
        continue;
      for (const char *name : names) {
        gchar *candidate = g_build_filename(base, name, nullptr);
        if (g_file_test(candidate, G_FILE_TEST_IS_REGULAR)) {
          return candidate; // transfer
        }
        g_free(candidate);
      }
    }

    return nullptr;
  }

  static PopplerDocument *LoadDocumentOrSkip_2524() {
    g_autofree gchar *path = FindTaggedPdfPathOrNull_2524();
    if (!path) {
      GTEST_SKIP() << "No tagged/structure test PDF found. Set POPPLER_TEST_TAGGED_PDF or TESTDATADIR/SRCDIR.";
      return nullptr;
    }

    g_autoptr(GError) error = nullptr;
    g_autofree gchar *uri = g_filename_to_uri(path, nullptr, &error);
    if (!uri) {
      GTEST_SKIP() << "Failed to create URI for test PDF: " << (error ? error->message : "unknown error");
      return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    if (!doc) {
      GTEST_SKIP() << "Failed to load test PDF with Poppler: " << (error ? error->message : "unknown error");
      return nullptr;
    }

    return doc; // transfer
  }

  struct FoundKinds_2524 {
    PopplerStructureElement *content_elem = nullptr;     // borrowed
    PopplerStructureElement *objectref_elem = nullptr;   // borrowed
    bool saw_any = false;
  };

  static FoundKinds_2524 FindInterestingElements_2524(PopplerDocument *doc) {
    FoundKinds_2524 out;

    PopplerStructureElementIter *root = poppler_structure_element_iter_new(doc);
    if (!root) {
      return out;
    }

    // Depth-first walk using the API example from Poppler docs.
    struct Walker {
      static void Walk(PopplerStructureElementIter *iter, FoundKinds_2524 *out) {
        if (!iter || !out)
          return;

        do {
          out->saw_any = true;

          PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
          if (elem) {
            PopplerStructureElementKind kind = poppler_structure_element_get_kind(elem);
            if (!out->content_elem && kind == POPPLER_STRUCTURE_ELEMENT_CONTENT) {
              out->content_elem = elem;
            }
            if (!out->objectref_elem && kind == POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE) {
              out->objectref_elem = elem;
            }
          }

          PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
          if (child) {
            Walk(child, out);
            poppler_structure_element_iter_free(child);
          }
        } while (poppler_structure_element_iter_next(iter) &&
                 !(out->content_elem && out->objectref_elem));
      }
    };

    Walker::Walk(root, &out);
    poppler_structure_element_iter_free(root);
    return out;
  }
};

TEST_F(PopplerStructureElementIsContentTest_2524, NullPointerReturnsFalse_2524) {
  // g_return_val_if_fail should return FALSE for NULL input.
  EXPECT_FALSE(poppler_structure_element_is_content(nullptr));
}

TEST_F(PopplerStructureElementIsContentTest_2524, WrongGTypeReturnsFalse_2524) {
  // Passing a non-PopplerStructureElement instance should fail the type check and return FALSE.
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  EXPECT_FALSE(poppler_structure_element_is_content(reinterpret_cast<PopplerStructureElement *>(obj)));

  g_object_unref(obj);
}

TEST_F(PopplerStructureElementIsContentTest_2524, WorksOnRealStructureElementsFromTaggedPdf_2524) {
  g_autoptr(PopplerDocument) doc = LoadDocumentOrSkip_2524();
  if (!doc)
    return;

  const FoundKinds_2524 found = FindInterestingElements_2524(doc);
  if (!found.saw_any) {
    GTEST_SKIP() << "Document has no structure elements or structure iterator returned no nodes.";
    return;
  }

  // If the document exposes at least one CONTENT kind element, is_content should report TRUE for it.
  if (found.content_elem) {
    EXPECT_TRUE(poppler_structure_element_is_content(found.content_elem));
  } else {
    GTEST_SKIP() << "No POPPLER_STRUCTURE_ELEMENT_CONTENT node found in this document's structure tree.";
  }

  // If the document exposes at least one OBJECT_REFERENCE kind element, is_content should report FALSE for it.
  if (found.objectref_elem) {
    EXPECT_FALSE(poppler_structure_element_is_content(found.objectref_elem));
  } else {
    GTEST_SKIP() << "No POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE node found in this document's structure tree.";
  }
}

TEST_F(PopplerStructureElementIsContentTest_2524, StableAcrossMultipleCalls_2524) {
  g_autoptr(PopplerDocument) doc = LoadDocumentOrSkip_2524();
  if (!doc)
    return;

  const FoundKinds_2524 found = FindInterestingElements_2524(doc);
  if (!found.saw_any) {
    GTEST_SKIP() << "Document has no structure elements or structure iterator returned no nodes.";
    return;
  }
  if (!found.content_elem && !found.objectref_elem) {
    GTEST_SKIP() << "No suitable structure elements (CONTENT/OBJECT_REFERENCE) found to test stability.";
    return;
  }

  if (found.content_elem) {
    const gboolean first = poppler_structure_element_is_content(found.content_elem);
    const gboolean second = poppler_structure_element_is_content(found.content_elem);
    EXPECT_EQ(first, second);
  }

  if (found.objectref_elem) {
    const gboolean first = poppler_structure_element_is_content(found.objectref_elem);
    const gboolean second = poppler_structure_element_is_content(found.objectref_elem);
    EXPECT_EQ(first, second);
  }
}

} // namespace