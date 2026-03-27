// poppler-structure-element-get-alt-text-test_2532.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

// This header is part of Poppler’s GLib bindings private surface in the codebase.
#include "poppler-private.h"

namespace {

class PopplerStructureElementGetAltTextTest_2532 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib type system is ready (harmless if already initialized).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  static std::string WriteTempPdfOrDie(const std::string &pdf_bytes) {
    gchar *tmp_name = nullptr;
    GError *error = nullptr;

    // Use a unique temp filename.
    int fd = g_file_open_tmp("poppler-structure-alt-text-XXXXXX.pdf", &tmp_name, &error);
    ASSERT_NE(fd, -1) << (error ? error->message : "g_file_open_tmp failed");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    FILE *f = fdopen(fd, "wb");
    ASSERT_NE(f, nullptr);

    size_t written = fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
    ASSERT_EQ(written, pdf_bytes.size());

    int rc = fclose(f);
    ASSERT_EQ(rc, 0);

    std::string path(tmp_name);
    g_free(tmp_name);
    return path;
  }

  static PopplerDocument *LoadDocOrDie(const std::string &path) {
    GError *error = nullptr;

    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
    EXPECT_EQ(error, nullptr) << (error ? error->message : "");
    EXPECT_NE(uri, nullptr);

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    EXPECT_EQ(error, nullptr) << (error ? error->message : "");
    EXPECT_NE(doc, nullptr);

    if (error) {
      g_error_free(error);
    }
    return doc;
  }

  static void RemoveFileNoFail(const std::string &path) { (void)g_remove(path.c_str()); }
};

// A minimal tagged PDF with a structure element that has /Alt (AltHello).
// The structure tree is:
// StructTreeRoot -> Figure (AltHello) -> MCR (MCID 0 on page)
static const char kPdfWithAlt_2532[] =
    "%PDF-1.5\n"
    "%\xE2\xE3\xCF\xD3\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 6 0 R /StructTreeRoot 2 0 R /MarkInfo << /Marked true >> >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /StructTreeRoot /K [3 0 R] >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /StructElem /S /Figure /P 2 0 R /Alt (AltHello) /K 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Type /MCR /Pg 5 0 R /MCID 0 >>\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Type /Page /Parent 6 0 R\n"
    "   /Resources << >>\n"
    "   /MediaBox [0 0 200 200]\n"
    "   /Contents 7 0 R\n"
    ">>\n"
    "endobj\n"
    "6 0 obj\n"
    "<< /Type /Pages /Kids [5 0 R] /Count 1 >>\n"
    "endobj\n"
    "7 0 obj\n"
    "<< /Length 28 >>\n"
    "stream\n"
    "/P <</MCID 0>> BDC\n"
    "EMC\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 8\n"
    "0000000000 65535 f \n"
    "0000000015 00000 n \n"
    "0000000112 00000 n \n"
    "0000000173 00000 n \n"
    "0000000250 00000 n \n"
    "0000000311 00000 n \n"
    "0000000424 00000 n \n"
    "0000000487 00000 n \n"
    "trailer\n"
    "<< /Size 8 /Root 1 0 R >>\n"
    "startxref\n"
    "586\n"
    "%%EOF\n";

// Same but without /Alt, so get_alt_text should yield nullptr.
static const char kPdfWithoutAlt_2532[] =
    "%PDF-1.5\n"
    "%\xE2\xE3\xCF\xD3\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 6 0 R /StructTreeRoot 2 0 R /MarkInfo << /Marked true >> >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /StructTreeRoot /K [3 0 R] >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /StructElem /S /Figure /P 2 0 R /K 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Type /MCR /Pg 5 0 R /MCID 0 >>\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Type /Page /Parent 6 0 R\n"
    "   /Resources << >>\n"
    "   /MediaBox [0 0 200 200]\n"
    "   /Contents 7 0 R\n"
    ">>\n"
    "endobj\n"
    "6 0 obj\n"
    "<< /Type /Pages /Kids [5 0 R] /Count 1 >>\n"
    "endobj\n"
    "7 0 obj\n"
    "<< /Length 28 >>\n"
    "stream\n"
    "/P <</MCID 0>> BDC\n"
    "EMC\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 8\n"
    "0000000000 65535 f \n"
    "0000000015 00000 n \n"
    "0000000112 00000 n \n"
    "0000000173 00000 n \n"
    "0000000242 00000 n \n"
    "0000000303 00000 n \n"
    "0000000416 00000 n \n"
    "0000000479 00000 n \n"
    "trailer\n"
    "<< /Size 8 /Root 1 0 R >>\n"
    "startxref\n"
    "578\n"
    "%%EOF\n";

TEST_F(PopplerStructureElementGetAltTextTest_2532, NullObjectReturnsNull_2532) {
  // Should return NULL for invalid instance.
  gchar *alt = poppler_structure_element_get_alt_text(nullptr);
  EXPECT_EQ(alt, nullptr);
}

TEST_F(PopplerStructureElementGetAltTextTest_2532, NonStructureElementTriggersCriticalAndReturnsNull_2532) {
  // g_return_val_if_fail should emit a critical log and return NULL.
  GObject *not_a_structure = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_structure, nullptr);

  // Domain for g_return_* is typically G_LOG_DOMAIN of the compilation unit.
  // In Poppler GLib sources this is commonly "Poppler".
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
  gchar *alt = poppler_structure_element_get_alt_text(reinterpret_cast<PopplerStructureElement *>(not_a_structure));
  g_test_assert_expected_messages();

  EXPECT_EQ(alt, nullptr);
  g_object_unref(not_a_structure);
}

TEST_F(PopplerStructureElementGetAltTextTest_2532, ElementWithNullElemReturnsNull_2532) {
  // Create an instance (if constructible) and ensure that when elem is unset/null,
  // the function returns NULL (second g_return_val_if_fail).
  PopplerStructureElement *se =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));

  if (!se) {
    GTEST_SKIP() << "PopplerStructureElement is not constructible via g_object_new() in this build.";
  }

  // No poking at internal state: we rely on default-constructed instance having elem == nullptr.
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*poppler_structure_element->elem != nullptr*");
  gchar *alt = poppler_structure_element_get_alt_text(se);
  g_test_assert_expected_messages();

  EXPECT_EQ(alt, nullptr);
  g_object_unref(se);
}

TEST_F(PopplerStructureElementGetAltTextTest_2532, ReturnsUtf8AltTextWhenPresent_2532) {
  const std::string path = WriteTempPdfOrDie(std::string(kPdfWithAlt_2532, sizeof(kPdfWithAlt_2532) - 1));
  PopplerDocument *doc = LoadDocOrDie(path);
  ASSERT_NE(doc, nullptr);

  // Poppler GLib provides access to the structure tree root in tagged PDFs.
  // If not available in this build/config, skip rather than guessing internals.
  PopplerStructureElement *root = poppler_document_get_structure_tree_root(doc);
  if (!root) {
    g_object_unref(doc);
    RemoveFileNoFail(path);
    GTEST_SKIP() << "Structure tree root not available (PDF not parsed as tagged or API not supported).";
  }

  // Typical expectation: root has at least one child (the Figure element).
  int n = poppler_structure_element_get_n_children(root);
  ASSERT_GE(n, 1);

  PopplerStructureElement *child = poppler_structure_element_get_child(root, 0);
  ASSERT_NE(child, nullptr);

  gchar *alt = poppler_structure_element_get_alt_text(child);
  ASSERT_NE(alt, nullptr);
  EXPECT_STREQ(alt, "AltHello");
  g_free(alt);

  g_object_unref(child);
  g_object_unref(root);
  g_object_unref(doc);
  RemoveFileNoFail(path);
}

TEST_F(PopplerStructureElementGetAltTextTest_2532, ReturnsNullWhenAltTextAbsent_2532) {
  const std::string path =
      WriteTempPdfOrDie(std::string(kPdfWithoutAlt_2532, sizeof(kPdfWithoutAlt_2532) - 1));
  PopplerDocument *doc = LoadDocOrDie(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement *root = poppler_document_get_structure_tree_root(doc);
  if (!root) {
    g_object_unref(doc);
    RemoveFileNoFail(path);
    GTEST_SKIP() << "Structure tree root not available (PDF not parsed as tagged or API not supported).";
  }

  int n = poppler_structure_element_get_n_children(root);
  ASSERT_GE(n, 1);

  PopplerStructureElement *child = poppler_structure_element_get_child(root, 0);
  ASSERT_NE(child, nullptr);

  gchar *alt = poppler_structure_element_get_alt_text(child);
  EXPECT_EQ(alt, nullptr);

  g_object_unref(child);
  g_object_unref(root);
  g_object_unref(doc);
  RemoveFileNoFail(path);
}

} // namespace