// poppler-form-field-signature-validate-async-test-2323.cc
//
// Unit tests for:
//   poppler_form_field_signature_validate_async()
//
// Constraints honored:
// - Treat implementation as a black box (no internal logic assumptions).
// - Test only observable behavior via the public async callback mechanism.
// - Use GMainLoop to observe callback invocation.
// - Include normal, boundary, and cancellation/error-path coverage where observable.

#include <gtest/gtest.h>

#include <poppler.h>
#include <glib.h>
#include <gio/gio.h>

#include <string>
#include <vector>

namespace {

struct AsyncCbData {
  GMainLoop* loop = nullptr;
  int called = 0;
  GAsyncResult* result = nullptr;   // reffed
  GObject* source = nullptr;        // reffed via g_async_result_get_source_object()
  gboolean timed_out = FALSE;
};

gboolean QuitLoopOnTimeout(gpointer user_data) {
  auto* data = static_cast<AsyncCbData*>(user_data);
  data->timed_out = TRUE;
  if (data->loop)
    g_main_loop_quit(data->loop);
  return G_SOURCE_REMOVE;
}

void ValidateAsyncCallback(GObject* source_object, GAsyncResult* res, gpointer user_data) {
  auto* data = static_cast<AsyncCbData*>(user_data);
  data->called++;

  if (res) {
    data->result = static_cast<GAsyncResult*>(g_object_ref(res));
    // g_async_result_get_source_object returns a new ref (may be NULL depending on task).
    data->source = g_async_result_get_source_object(res);
  }

  if (data->loop)
    g_main_loop_quit(data->loop);

  (void)source_object; // source_object may be NULL; we validate via g_async_result_get_source_object().
}

class PopplerFormFieldSignatureValidateAsyncTest_2323 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temp directory for PDFs.
    GError* error = nullptr;
    tmp_dir_ = g_dir_make_tmp("poppler_gtest_2323_XXXXXX", &error);
    ASSERT_NE(tmp_dir_, nullptr) << (error ? error->message : "g_dir_make_tmp failed");
    if (error) g_error_free(error);
  }

  void TearDown() override {
    // Best-effort cleanup.
    if (!created_files_.empty()) {
      for (const auto& path : created_files_) {
        g_unlink(path.c_str());
      }
    }
    if (tmp_dir_) {
      g_rmdir(tmp_dir_);
      g_free(tmp_dir_);
      tmp_dir_ = nullptr;
    }
  }

  // Minimal 1-page PDF with an AcroForm signature field.
  // (Not signed; just a /FT /Sig field with a widget.)
  std::string WriteMinimalSignaturePdfAndGetUri() {
    const char* pdf =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
        "   /Resources << >>\n"
        "   /Annots [4 0 R]\n"
        ">>\n"
        "endobj\n"
        // Widget annotation + signature field dictionary (combined for minimalism).
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Widget\n"
        "   /FT /Sig\n"
        "   /T (Sig1)\n"
        "   /Rect [10 10 190 60]\n"
        "   /F 4\n"
        "   /P 3 0 R\n"
        ">>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /SigFlags 3 /Fields [4 0 R] /NeedAppearances true >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000079 00000 n \n"
        "0000000136 00000 n \n"
        "0000000254 00000 n \n"
        "0000000406 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "0500\n"
        "%%EOF\n";

    // Note: The xref offsets above are not accurate. Some PDF parsers are lenient; Poppler
    // generally is not. To avoid relying on leniency, we generate a correct-xref PDF.
    // We'll build a tiny PDF with computed offsets here instead of the static string.
    std::string dynamic_pdf = BuildPdfWithCorrectXref_();
    ASSERT_FALSE(dynamic_pdf.empty());

    const std::string file_path = std::string(tmp_dir_) + G_DIR_SEPARATOR_S + "sig_2323.pdf";
    created_files_.push_back(file_path);

    GError* error = nullptr;
    gboolean ok = g_file_set_contents(file_path.c_str(),
                                     dynamic_pdf.data(),
                                     static_cast<gssize>(dynamic_pdf.size()),
                                     &error);
    ASSERT_TRUE(ok) << (error ? error->message : "g_file_set_contents failed");
    if (error) g_error_free(error);

    // Convert to file:// URI.
    error = nullptr;
    gchar* uri = g_filename_to_uri(file_path.c_str(), nullptr, &error);
    ASSERT_NE(uri, nullptr) << (error ? error->message : "g_filename_to_uri failed");
    if (error) g_error_free(error);

    std::string uri_str(uri);
    g_free(uri);
    return uri_str;
  }

  PopplerDocument* LoadDocFromUriOrFail(const std::string& uri) {
    GError* error = nullptr;
    PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    ASSERT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
    if (error) g_error_free(error);
    return doc;
  }

  PopplerFormField* FindFirstSignatureFieldOrFail(PopplerDocument* doc) {
    ASSERT_NE(doc, nullptr);
    PopplerPage* page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList* mappings = poppler_page_get_form_field_mapping(page);
    ASSERT_NE(mappings, nullptr);

    PopplerFormField* sig = nullptr;
    for (GList* l = mappings; l != nullptr; l = l->next) {
      auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
      if (!m || !m->field)
        continue;
      if (poppler_form_field_get_field_type(m->field) == POPPLER_FORM_FIELD_SIGNATURE) {
        sig = m->field;
        break;
      }
    }

    poppler_page_free_form_field_mapping(mappings);
    g_object_unref(page);

    ASSERT_NE(sig, nullptr) << "Failed to locate a signature form field in the generated PDF";
    return sig; // owned by Poppler internals; do not unref here.
  }

 private:
  // Builds a minimal PDF with correct xref offsets to ensure Poppler can parse it reliably.
  std::string BuildPdfWithCorrectXref_() {
    // Objects:
    // 1: Catalog (Pages 2, AcroForm 5)
    // 2: Pages
    // 3: Page (Annots [4])
    // 4: Widget annotation signature field
    // 5: AcroForm dict with Fields [4]
    std::vector<std::string> objs;
    objs.push_back("<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>");
    objs.push_back("<< /Type /Pages /Count 1 /Kids [3 0 R] >>");
    objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                   "   /Resources << >>\n"
                   "   /Annots [4 0 R]\n"
                   ">>");
    objs.push_back("<< /Type /Annot /Subtype /Widget\n"
                   "   /FT /Sig\n"
                   "   /T (Sig1)\n"
                   "   /Rect [10 10 190 60]\n"
                   "   /F 4\n"
                   "   /P 3 0 R\n"
                   ">>");
    objs.push_back("<< /SigFlags 3 /Fields [4 0 R] /NeedAppearances true >>");

    std::string out;
    out += "%PDF-1.4\n";

    std::vector<size_t> offsets;
    offsets.resize(objs.size() + 1);
    offsets[0] = 0; // xref entry for object 0

    for (size_t i = 0; i < objs.size(); ++i) {
      offsets[i + 1] = out.size();
      out += std::to_string(i + 1);
      out += " 0 obj\n";
      out += objs[i];
      out += "\nendobj\n";
    }

    const size_t xref_pos = out.size();
    out += "xref\n";
    out += "0 ";
    out += std::to_string(objs.size() + 1);
    out += "\n";
    // Object 0 free entry
    out += "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      // 10-digit offset, 5-digit generation, 'n'
      g_snprintf(buf, sizeof(buf), "%010u 00000 n \n", static_cast<unsigned>(offsets[i]));
      out += buf;
    }

    out += "trailer\n";
    out += "<< /Size ";
    out += std::to_string(objs.size() + 1);
    out += " /Root 1 0 R >>\n";
    out += "startxref\n";
    out += std::to_string(xref_pos);
    out += "\n%%EOF\n";

    return out;
  }

 protected:
  gchar* tmp_dir_ = nullptr;
  std::vector<std::string> created_files_;
};

TEST_F(PopplerFormFieldSignatureValidateAsyncTest_2323, CallsCallbackAndProvidesSourceObject_2323) {
  const std::string uri = WriteMinimalSignaturePdfAndGetUri();
  PopplerDocument* doc = LoadDocFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* sig = FindFirstSignatureFieldOrFail(doc);
  ASSERT_NE(sig, nullptr);

  AsyncCbData data;
  data.loop = g_main_loop_new(nullptr, FALSE);
  ASSERT_NE(data.loop, nullptr);

  // Timeout safety.
  guint timeout_id = g_timeout_add_seconds(5, QuitLoopOnTimeout, &data);

  // Normal operation: no cancellable.
  poppler_form_field_signature_validate_async(
      sig,
      static_cast<PopplerSignatureValidationFlags>(0),
      nullptr,
      ValidateAsyncCallback,
      &data);

  g_main_loop_run(data.loop);

  g_source_remove(timeout_id);
  g_main_loop_unref(data.loop);
  data.loop = nullptr;

  EXPECT_FALSE(data.timed_out);
  EXPECT_EQ(data.called, 1);
  ASSERT_NE(data.result, nullptr);

  // Observable: GTask uses the provided source object. Validate it via GAsyncResult API.
  ASSERT_NE(data.source, nullptr);
  EXPECT_EQ(data.source, G_OBJECT(sig));

  g_object_unref(data.result);
  g_object_unref(data.source);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldSignatureValidateAsyncTest_2323, CancelImmediatelyStillInvokesCallback_2323) {
  const std::string uri = WriteMinimalSignaturePdfAndGetUri();
  PopplerDocument* doc = LoadDocFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* sig = FindFirstSignatureFieldOrFail(doc);
  ASSERT_NE(sig, nullptr);

  GCancellable* cancellable = g_cancellable_new();
  ASSERT_NE(cancellable, nullptr);

  AsyncCbData data;
  data.loop = g_main_loop_new(nullptr, FALSE);
  ASSERT_NE(data.loop, nullptr);

  guint timeout_id = g_timeout_add_seconds(5, QuitLoopOnTimeout, &data);

  poppler_form_field_signature_validate_async(
      sig,
      static_cast<PopplerSignatureValidationFlags>(0),
      cancellable,
      ValidateAsyncCallback,
      &data);

  // Cancel right away (error/cancel path observable via callback occurrence).
  g_cancellable_cancel(cancellable);

  g_main_loop_run(data.loop);

  g_source_remove(timeout_id);
  g_main_loop_unref(data.loop);
  data.loop = nullptr;

  EXPECT_FALSE(data.timed_out);
  EXPECT_EQ(data.called, 1);
  ASSERT_NE(data.result, nullptr);

  // Source object should still be the field (GTask source object).
  ASSERT_NE(data.source, nullptr);
  EXPECT_EQ(data.source, G_OBJECT(sig));

  g_object_unref(data.result);
  g_object_unref(data.source);
  g_object_unref(cancellable);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldSignatureValidateAsyncTest_2323, AcceptsNonZeroFlagsAndStillInvokesCallback_2323) {
  const std::string uri = WriteMinimalSignaturePdfAndGetUri();
  PopplerDocument* doc = LoadDocFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* sig = FindFirstSignatureFieldOrFail(doc);
  ASSERT_NE(sig, nullptr);

  AsyncCbData data;
  data.loop = g_main_loop_new(nullptr, FALSE);
  ASSERT_NE(data.loop, nullptr);

  guint timeout_id = g_timeout_add_seconds(5, QuitLoopOnTimeout, &data);

  // Boundary-ish: pass a non-zero bit pattern without assuming semantics.
  // (We intentionally do not assume which bits are valid; the test only verifies
  // that the async API remains well-behaved from the caller’s perspective.)
  const auto flags = static_cast<PopplerSignatureValidationFlags>(~0u);

  poppler_form_field_signature_validate_async(
      sig,
      flags,
      nullptr,
      ValidateAsyncCallback,
      &data);

  g_main_loop_run(data.loop);

  g_source_remove(timeout_id);
  g_main_loop_unref(data.loop);
  data.loop = nullptr;

  EXPECT_FALSE(data.timed_out);
  EXPECT_EQ(data.called, 1);
  ASSERT_NE(data.result, nullptr);

  ASSERT_NE(data.source, nullptr);
  EXPECT_EQ(data.source, G_OBJECT(sig));

  g_object_unref(data.result);
  g_object_unref(data.source);
  g_object_unref(doc);
}

}  // namespace