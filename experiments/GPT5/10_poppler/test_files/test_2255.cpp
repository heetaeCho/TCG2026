// File: poppler-ps-file-finalize-test_2255.cc
//
// Unit tests for poppler_ps_file_finalize() behavior through the public/observable
// GObject lifecycle (finalize happens on last unref).
//
// Constraints respected:
// - Black-box: no re-implementation of internal logic.
// - Only observable effects: object lifetime / weak refs / “does not crash”.
// - No private state inspection (we only use the provided struct fields from poppler-private.h).

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// Provided/inferred dependency (contains struct _PopplerPSFile fields)
#include "poppler-private.h"

namespace {

class PopplerPSFileFinalizeTest_2255 : public ::testing::Test {
protected:
  static std::string WriteMinimalPdfToTemp_2255() {
    // Minimal single-page PDF (enough for poppler_document_new_from_file()).
    // Keep it tiny and deterministic.
    static const char kPdf[] =
        "%PDF-1.1\n"
        "1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj\n"
        "2 0 obj << /Type /Pages /Kids [3 0 R] /Count 1 >> endobj\n"
        "3 0 obj << /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10] "
        "/Contents 4 0 R >> endobj\n"
        "4 0 obj << /Length 0 >> stream\n"
        "endstream endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000117 00000 n \n"
        "0000000203 00000 n \n"
        "trailer << /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "258\n"
        "%%EOF\n";

    gchar *tmp_name = nullptr;
    GError *err = nullptr;

    int fd = g_file_open_tmp("poppler_ps_file_finalize_2255_XXXXXX.pdf", &tmp_name, &err);
    EXPECT_NE(fd, -1) << (err ? err->message : "g_file_open_tmp failed");
    if (err) g_error_free(err);

    // Write file.
    gsize len = sizeof(kPdf) - 1;
    gssize written = write(fd, kPdf, len);
    EXPECT_EQ(static_cast<gsize>(written), len);
    close(fd);

    std::string path(tmp_name ? tmp_name : "");
    g_free(tmp_name);
    return path;
  }

  static PopplerDocument *OpenDocFromPath_2255(const std::string &path) {
    GError *error = nullptr;

    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
    EXPECT_NE(uri, nullptr) << (error ? error->message : "g_filename_to_uri failed");
    if (!uri) {
      if (error) g_error_free(error);
      return nullptr;
    }
    if (error) g_error_free(error);

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    EXPECT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
    if (error) g_error_free(error);
    return doc;
  }
};

TEST_F(PopplerPSFileFinalizeTest_2255, FinalizeUnrefsOwnedDocument_2255) {
  // Create a real PopplerDocument so we can observe its lifetime via weak refs.
  const std::string pdf_path = WriteMinimalPdfToTemp_2255();
  ASSERT_FALSE(pdf_path.empty());

  PopplerDocument *doc = OpenDocFromPath_2255(pdf_path);
  ASSERT_NE(doc, nullptr);

  // Create PopplerPSFile object (finalize happens at last unref).
  PopplerPSFile *ps_file = POPPLER_PS_FILE(g_object_new(POPPLER_TYPE_PS_FILE, nullptr));
  ASSERT_NE(ps_file, nullptr);

  // Observable: when ps_file is finalized, it should unref its owned document.
  // We arrange ownership so that ps_file holds the *only* reference.
  gboolean doc_finalized = FALSE;
  g_object_weak_ref(G_OBJECT(doc),
                    [](gpointer data, GObject *) {
                      *static_cast<gboolean *>(data) = TRUE;
                    },
                    &doc_finalized);

  // Transfer ownership to ps_file: keep exactly one ref held by ps_file.
  ps_file->document = POPPLER_DOCUMENT(g_object_ref(doc));
  g_object_unref(doc); // now only ps_file holds a ref

  // Also set safe values for other fields; deleting nullptr is fine.
  ps_file->out = nullptr;
  ps_file->filename = g_strdup("out_2255.ps");

  // Trigger finalize.
  g_object_unref(ps_file);

  // Document should have been finalized (weak ref callback fired).
  EXPECT_TRUE(doc_finalized);

  // Cleanup temp file.
  g_remove(pdf_path.c_str());
}

TEST_F(PopplerPSFileFinalizeTest_2255, FinalizeDoesNotDestroyDocumentWhenOtherRefsExist_2255) {
  const std::string pdf_path = WriteMinimalPdfToTemp_2255();
  ASSERT_FALSE(pdf_path.empty());

  PopplerDocument *doc = OpenDocFromPath_2255(pdf_path);
  ASSERT_NE(doc, nullptr);

  PopplerPSFile *ps_file = POPPLER_PS_FILE(g_object_new(POPPLER_TYPE_PS_FILE, nullptr));
  ASSERT_NE(ps_file, nullptr);

  gboolean doc_finalized = FALSE;
  g_object_weak_ref(G_OBJECT(doc),
                    [](gpointer data, GObject *) {
                      *static_cast<gboolean *>(data) = TRUE;
                    },
                    &doc_finalized);

  // Keep our own ref in addition to ps_file's ref.
  ps_file->document = POPPLER_DOCUMENT(g_object_ref(doc));
  // doc still has at least one ref held by this test.

  ps_file->out = nullptr;
  ps_file->filename = g_strdup("out_2255.ps");

  // Finalize ps_file; doc should still be alive (not finalized yet).
  g_object_unref(ps_file);
  EXPECT_FALSE(doc_finalized);

  // Once we drop our ref, doc should finalize.
  g_object_unref(doc);
  EXPECT_TRUE(doc_finalized);

  g_remove(pdf_path.c_str());
}

TEST_F(PopplerPSFileFinalizeTest_2255, FinalizeHandlesNullFieldsWithoutCrash_2255) {
  // Boundary/error-like case: fields left null. Observable requirement is “no crash”.
  PopplerPSFile *ps_file = POPPLER_PS_FILE(g_object_new(POPPLER_TYPE_PS_FILE, nullptr));
  ASSERT_NE(ps_file, nullptr);

  // Intentionally set fields to null to ensure finalize tolerates them.
  ps_file->document = nullptr;
  ps_file->out = nullptr;
  ps_file->filename = nullptr;

  // Should not crash.
  g_object_unref(ps_file);
}

} // namespace