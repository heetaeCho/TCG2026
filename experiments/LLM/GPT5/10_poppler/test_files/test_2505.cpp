// File: poppler-layer-finalize-test_2505.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <poppler.h>

namespace {

class PopplerLayerTest_2505 : public ::testing::Test {
protected:
  static PopplerLayer* NewLayer() {
    // If PopplerLayer type is not registered/available in this build, this will return nullptr.
    auto* obj = g_object_new(POPPLER_TYPE_LAYER, nullptr);
    return obj ? POPPLER_LAYER(obj) : nullptr;
  }

  static bool HasWritableProperty(GObject* obj, const char* name) {
    if (!obj || !name) return false;
    GParamSpec* pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(obj), name);
    if (!pspec) return false;
    return (pspec->flags & G_PARAM_WRITABLE) != 0;
  }

  static GParamSpec* FindProperty(GObject* obj, const char* name) {
    if (!obj || !name) return nullptr;
    return g_object_class_find_property(G_OBJECT_GET_CLASS(obj), name);
  }

  static PopplerDocument* NewMinimalDocument(GError** error) {
    // A tiny, valid, single-page PDF with correct xref offsets.
    static const char kPdf[] =
        "%PDF-1.1\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
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
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000202 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "251\n"
        "%%EOF\n";

    return poppler_document_new_from_data(kPdf, static_cast<int>(sizeof(kPdf) - 1), nullptr, error);
  }

  static void WeakNotify(GObject* /*where_the_object_was*/, gpointer user_data) {
    auto* flag = static_cast<bool*>(user_data);
    if (flag) *flag = true;
  }
};

TEST_F(PopplerLayerTest_2505, UnrefNewLayerDoesNotCrash_2505) {
  PopplerLayer* layer = NewLayer();
  if (!layer) {
    GTEST_SKIP() << "POPPLER_TYPE_LAYER is not available in this build.";
  }

  // Observable behavior: finalization via unref should not crash.
  g_object_unref(layer);
}

TEST_F(PopplerLayerTest_2505, UnrefLayerAfterSettingTitleEmptyStringDoesNotCrash_2505) {
  PopplerLayer* layer = NewLayer();
  if (!layer) {
    GTEST_SKIP() << "POPPLER_TYPE_LAYER is not available in this build.";
  }

  // Boundary case: empty string. Only attempt if a writable "title" property exists.
  if (HasWritableProperty(G_OBJECT(layer), "title")) {
    g_object_set(G_OBJECT(layer), "title", "", nullptr);
  }

  g_object_unref(layer);
}

TEST_F(PopplerLayerTest_2505, UnrefLayerAfterSettingTitleLongStringDoesNotCrash_2505) {
  PopplerLayer* layer = NewLayer();
  if (!layer) {
    GTEST_SKIP() << "POPPLER_TYPE_LAYER is not available in this build.";
  }

  // Boundary case: long string. Only attempt if a writable "title" property exists.
  if (HasWritableProperty(G_OBJECT(layer), "title")) {
    std::string long_title(4096, 'A');
    g_object_set(G_OBJECT(layer), "title", long_title.c_str(), nullptr);
  }

  g_object_unref(layer);
}

TEST_F(PopplerLayerTest_2505, FinalizeUnrefsDocumentPropertyIfPresent_2505) {
  PopplerLayer* layer = NewLayer();
  if (!layer) {
    GTEST_SKIP() << "POPPLER_TYPE_LAYER is not available in this build.";
  }

  // This test verifies the externally observable interaction:
  // if a writable object property named "document" exists and accepts PopplerDocument,
  // then destroying the layer should release its reference to the document.
  GParamSpec* pspec = FindProperty(G_OBJECT(layer), "document");
  if (!pspec || (pspec->flags & G_PARAM_WRITABLE) == 0) {
    g_object_unref(layer);
    GTEST_SKIP() << "No writable 'document' property found on PopplerLayer.";
  }

  if (!G_IS_PARAM_SPEC_OBJECT(pspec)) {
    g_object_unref(layer);
    GTEST_SKIP() << "'document' exists but is not an object property.";
  }

  const GType expected = poppler_document_get_type();
  const GType actual = G_PARAM_SPEC_VALUE_TYPE(pspec);
  if (actual != expected && !g_type_is_a(expected, actual)) {
    g_object_unref(layer);
    GTEST_SKIP() << "'document' property type is not compatible with PopplerDocument.";
  }

  GError* error = nullptr;
  PopplerDocument* doc = NewMinimalDocument(&error);
  if (!doc) {
    std::string msg = "Failed to create PopplerDocument from minimal PDF.";
    if (error && error->message) msg += std::string(" GError: ") + error->message;
    if (error) g_error_free(error);
    g_object_unref(layer);
    GTEST_SKIP() << msg;
  }

  bool doc_finalized = false;
  g_object_weak_ref(G_OBJECT(doc), WeakNotify, &doc_finalized);

  // Give the layer a reference (through the public property API).
  g_object_set(G_OBJECT(layer), "document", doc, nullptr);

  // Drop our reference. If the layer retained one, the document must remain alive here.
  g_object_unref(doc);
  EXPECT_FALSE(doc_finalized);

  // Destroying the layer should release its reference, allowing the doc to finalize.
  g_object_unref(layer);
  EXPECT_TRUE(doc_finalized);
}

}  // namespace