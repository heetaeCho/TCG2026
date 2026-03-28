// File: poppler-document-get-layers-test_2244.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

extern "C" {
// Internal function under test (implemented in poppler-document.cc)
GList *_poppler_document_get_layers(PopplerDocument *document);
}

namespace {

class PopplerDocumentGetLayersTest_2244 : public ::testing::Test {
protected:
  static gchar *WriteTempPdfOrFail_2244(const gchar *contents, gsize len) {
    GError *error = nullptr;
    gchar *tmp_path = nullptr;

    // Create a temp file path (not opened), then write contents into it.
    gint fd = g_file_open_tmp("poppler_get_layers_2244_XXXXXX.pdf", &tmp_path, &error);
    if (fd >= 0) {
      close(fd);
    }
    if (!tmp_path) {
      gchar *msg = g_strdup_printf("g_file_open_tmp failed: %s", error ? error->message : "unknown");
      if (error) g_error_free(error);
      FAIL() << msg;
      g_free(msg);
      return nullptr;
    }

    if (!g_file_set_contents(tmp_path, contents, static_cast<gssize>(len), &error)) {
      gchar *msg = g_strdup_printf("g_file_set_contents failed: %s", error ? error->message : "unknown");
      if (error) g_error_free(error);
      g_remove(tmp_path);
      g_free(tmp_path);
      FAIL() << msg;
      g_free(msg);
      return nullptr;
    }

    return tmp_path;
  }

  static PopplerDocument *LoadDocumentFromPathOrFail_2244(const gchar *path) {
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(path, /*hostname=*/nullptr, &error);
    if (!uri) {
      gchar *msg = g_strdup_printf("g_filename_to_uri failed: %s", error ? error->message : "unknown");
      if (error) g_error_free(error);
      FAIL() << msg;
      g_free(msg);
      return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    if (!doc) {
      gchar *msg = g_strdup_printf("poppler_document_new_from_file failed: %s", error ? error->message : "unknown");
      if (error) g_error_free(error);
      FAIL() << msg;
      g_free(msg);
      return nullptr;
    }
    return doc;
  }

  static void RemoveTempFile_2244(gchar *path) {
    if (!path) return;
    g_remove(path);
    g_free(path);
  }
};

// Minimal PDF without optional content (/OCProperties). Should yield no layers.
static const char kPdfNoLayers_2244[] =
  "%PDF-1.4\n"
  "1 0 obj\n"
  "<< /Type /Catalog /Pages 2 0 R >>\n"
  "endobj\n"
  "2 0 obj\n"
  "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
  "endobj\n"
  "3 0 obj\n"
  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>\n"
  "endobj\n"
  "4 0 obj\n"
  "<< /Length 0 >>\n"
  "stream\n"
  "\n"
  "endstream\n"
  "endobj\n"
  "xref\n"
  "0 5\n"
  "0000000000 65535 f \n"
  "0000000010 00000 n \n"
  "0000000062 00000 n \n"
  "0000000117 00000 n \n"
  "0000000223 00000 n \n"
  "trailer\n"
  "<< /Size 5 /Root 1 0 R >>\n"
  "startxref\n"
  "290\n"
  "%%EOF\n";

// Minimal PDF with /OCProperties and one OCG. Should yield a non-null layers list.
static const char kPdfWithLayers_2244[] =
  "%PDF-1.5\n"
  "1 0 obj\n"
  "<< /Type /Catalog\n"
  "   /Pages 2 0 R\n"
  "   /OCProperties <<\n"
  "     /OCGs [5 0 R]\n"
  "     /D << /Order [5 0 R] >>\n"
  "   >>\n"
  ">>\n"
  "endobj\n"
  "2 0 obj\n"
  "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
  "endobj\n"
  "3 0 obj\n"
  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>\n"
  "endobj\n"
  "4 0 obj\n"
  "<< /Length 0 >>\n"
  "stream\n"
  "\n"
  "endstream\n"
  "endobj\n"
  "5 0 obj\n"
  "<< /Type /OCG /Name (Layer 1) >>\n"
  "endobj\n"
  "xref\n"
  "0 6\n"
  "0000000000 65535 f \n"
  "0000000010 00000 n \n"
  "0000000141 00000 n \n"
  "0000000196 00000 n \n"
  "0000000302 00000 n \n"
  "0000000379 00000 n \n"
  "trailer\n"
  "<< /Size 6 /Root 1 0 R >>\n"
  "startxref\n"
  "428\n"
  "%%EOF\n";

TEST_F(PopplerDocumentGetLayersTest_2244, ReturnsNullWhenNoOptionalContentConfig_2244) {
  gchar *path = WriteTempPdfOrFail_2244(kPdfNoLayers_2244, sizeof(kPdfNoLayers_2244) - 1);
  ASSERT_NE(path, nullptr);

  PopplerDocument *doc = LoadDocumentFromPathOrFail_2244(path);
  ASSERT_NE(doc, nullptr);

  GList *layers = _poppler_document_get_layers(doc);
  EXPECT_EQ(layers, nullptr);

  g_object_unref(doc);
  RemoveTempFile_2244(path);
}

TEST_F(PopplerDocumentGetLayersTest_2244, ReturnsNonNullListWhenOcPropertiesPresent_2244) {
  gchar *path = WriteTempPdfOrFail_2244(kPdfWithLayers_2244, sizeof(kPdfWithLayers_2244) - 1);
  ASSERT_NE(path, nullptr);

  PopplerDocument *doc = LoadDocumentFromPathOrFail_2244(path);
  ASSERT_NE(doc, nullptr);

  GList *layers = _poppler_document_get_layers(doc);
  ASSERT_NE(layers, nullptr);

  // Observable behavior: list contains at least one item and items are non-null.
  EXPECT_GE(g_list_length(layers), 1);
  EXPECT_NE(layers->data, nullptr);

  g_object_unref(doc);
  RemoveTempFile_2244(path);
}

TEST_F(PopplerDocumentGetLayersTest_2244, SubsequentCallsReturnSamePointer_2244) {
  gchar *path = WriteTempPdfOrFail_2244(kPdfWithLayers_2244, sizeof(kPdfWithLayers_2244) - 1);
  ASSERT_NE(path, nullptr);

  PopplerDocument *doc = LoadDocumentFromPathOrFail_2244(path);
  ASSERT_NE(doc, nullptr);

  GList *layers_first = _poppler_document_get_layers(doc);
  ASSERT_NE(layers_first, nullptr);

  GList *layers_second = _poppler_document_get_layers(doc);
  ASSERT_NE(layers_second, nullptr);

  // The function contract (as observed) implies caching: repeated calls should return the same list handle.
  EXPECT_EQ(layers_second, layers_first);

  g_object_unref(doc);
  RemoveTempFile_2244(path);
}

TEST_F(PopplerDocumentGetLayersTest_2244, RepeatedCallsOnNoLayersStayNull_2244) {
  gchar *path = WriteTempPdfOrFail_2244(kPdfNoLayers_2244, sizeof(kPdfNoLayers_2244) - 1);
  ASSERT_NE(path, nullptr);

  PopplerDocument *doc = LoadDocumentFromPathOrFail_2244(path);
  ASSERT_NE(doc, nullptr);

  GList *layers_first = _poppler_document_get_layers(doc);
  GList *layers_second = _poppler_document_get_layers(doc);

  EXPECT_EQ(layers_first, nullptr);
  EXPECT_EQ(layers_second, nullptr);

  g_object_unref(doc);
  RemoveTempFile_2244(path);
}

}  // namespace