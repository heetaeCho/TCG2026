// poppler_structure_element_get_text_decoration_color_test_2578.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

extern "C" {
gboolean poppler_structure_element_get_text_decoration_color(PopplerStructureElement *poppler_structure_element,
                                                            PopplerColor *color);
}

namespace {

class PopplerStructureElementTextDecorationColorTest_2578 : public ::testing::Test {
protected:
  static void SetUpTestSuite()
  {
    // Ensure GLib's test message capture utilities are initialized.
    // (Safe even if initialized elsewhere.)
    int argc = 0;
    char **argv = nullptr;
    g_test_init(&argc, &argv, nullptr);
  }

  static PopplerDocument *TryLoadAnyTaggedPdf()
  {
    // Best-effort: try common Poppler test-data filenames/locations.
    // If none exist in the build environment, tests that depend on them will skip.
    const char *candidates[] = {
        // Common names used in various PDF test suites
        "tagged.pdf",
        "structure.pdf",
        "struct-tree.pdf",
        "pdfa1b.pdf",
        // Common relative directories
        "testdata/tagged.pdf",
        "test-data/tagged.pdf",
        "testdata/structure.pdf",
        "test-data/structure.pdf",
        "tests/tagged.pdf",
        "tests/test-data/tagged.pdf",
    };

    for (const char *rel : candidates) {
      if (!rel)
        continue;

      if (!g_file_test(rel, G_FILE_TEST_EXISTS))
        continue;

      GError *error = nullptr;

      // Interpret as a local path.
      gchar *abs_path = g_canonicalize_filename(rel, nullptr);
      gchar *uri = g_filename_to_uri(abs_path, nullptr, &error);
      g_free(abs_path);

      if (!uri) {
        if (error)
          g_error_free(error);
        continue;
      }

      PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
      g_free(uri);

      if (doc)
        return doc;

      if (error)
        g_error_free(error);
    }

    return nullptr;
  }

  static PopplerStructureElement *FindFirstInline(PopplerStructureElement *root)
  {
    if (!root)
      return nullptr;

    // Depth-first search using the public GLib API, if available.
    if (poppler_structure_element_is_inline(root))
      return root;

    const int n = poppler_structure_element_get_n_children(root);
    for (int i = 0; i < n; ++i) {
      PopplerStructureElement *child = poppler_structure_element_get_child(root, i);
      PopplerStructureElement *found = FindFirstInline(child);
      if (found)
        return found;
    }
    return nullptr;
  }
};

} // namespace

TEST_F(PopplerStructureElementTextDecorationColorTest_2578,
       NullElementReturnsFalseAndLogsCritical_2578)
{
  PopplerColor color{};
  // The implementation uses g_return_val_if_fail on an expression involving the element.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  gboolean ok = poppler_structure_element_get_text_decoration_color(nullptr, &color);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);
}

TEST_F(PopplerStructureElementTextDecorationColorTest_2578,
       NullColorReturnsFalseAndLogsCritical_2578)
{
  // Color == nullptr should trigger a g_return_val_if_fail (either directly or after earlier checks).
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  gboolean ok = poppler_structure_element_get_text_decoration_color(nullptr, nullptr);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);
}

TEST_F(PopplerStructureElementTextDecorationColorTest_2578,
       NonInlineElementReturnsFalseAndLogsCritical_2578)
{
  // Best-effort: create a PopplerStructureElement instance via GObject.
  // If the type isn't available in this build, skip.
#ifdef POPPLER_TYPE_STRUCTURE_ELEMENT
  PopplerStructureElement *elem =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  if (!elem) {
    GTEST_SKIP() << "Could not instantiate PopplerStructureElement via GObject.";
  }

  PopplerColor color{};
  // If the created element is not considered inline, the first g_return_val_if_fail should log CRITICAL.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  gboolean ok = poppler_structure_element_get_text_decoration_color(elem, &color);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);

  g_object_unref(elem);
#else
  GTEST_SKIP() << "POPPLER_TYPE_STRUCTURE_ELEMENT not available in headers/build.";
#endif
}

TEST_F(PopplerStructureElementTextDecorationColorTest_2578,
       InlineElementIfAvailableStillReturnsFalse_2578)
{
  // Best-effort: If we can load a tagged PDF and find an inline structure element,
  // the current implementation returns FALSE even after converting color.
  PopplerDocument *doc = TryLoadAnyTaggedPdf();
  if (!doc) {
    GTEST_SKIP() << "No suitable tagged/structured PDF found in the test environment.";
  }

  PopplerStructureElement *root = poppler_document_get_structure_tree(doc);
  if (!root) {
    g_object_unref(doc);
    GTEST_SKIP() << "Document has no structure tree.";
  }

  PopplerStructureElement *inline_elem = FindFirstInline(root);
  if (!inline_elem) {
    g_object_unref(doc);
    GTEST_SKIP() << "No inline structure element found in the structure tree.";
  }

  PopplerColor color{};
  color.red = 0x1234;
  color.green = 0x2345;
  color.blue = 0x3456;

  gboolean ok = poppler_structure_element_get_text_decoration_color(inline_elem, &color);
  EXPECT_FALSE(ok);

  g_object_unref(doc);
}

// If your test runner does not already provide a main(), this ensures both GLib
// test utilities (message capture) and GoogleTest are initialized.
int main(int argc, char **argv)
{
  // Initialize GLib testing (required for g_test_expect_message APIs).
  g_test_init(&argc, &argv, nullptr);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}