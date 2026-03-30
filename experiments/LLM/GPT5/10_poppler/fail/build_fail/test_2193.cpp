// File: poppler-document-get-n-signatures-test_2193.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>
#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class ScopedGLogHandler {
public:
  ScopedGLogHandler(const gchar *domain, GLogLevelFlags levels)
      : domain_(domain ? domain : ""), levels_(levels) {
    handler_id_ = g_log_set_handler(domain, levels, &ScopedGLogHandler::Handler, this);
  }

  ~ScopedGLogHandler() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_.empty() ? nullptr : domain_.c_str(), handler_id_);
    }
  }

  int count() const { return count_; }

private:
  static void Handler(const gchar * /*log_domain*/, GLogLevelFlags /*log_level*/, const gchar * /*message*/,
                      gpointer user_data) {
    auto *self = static_cast<ScopedGLogHandler *>(user_data);
    self->count_++;
  }

  std::string domain_;
  GLogLevelFlags levels_{};
  guint handler_id_{0};
  int count_{0};
};

static std::string ToFileUri(const std::string &path) {
#ifdef G_OS_WIN32
  // file:///C:/...
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
#else
  // file:///tmp/...
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
#endif
}

// Minimal PDF builder that creates a valid xref/trailer and embeds N signature fields (/FT /Sig).
// This is test data generation, not an implementation of Poppler internals.
static std::string BuildPdfWithNSignatureFields(int n_fields) {
  if (n_fields < 0) n_fields = 0;

  // Objects:
  // 1: Catalog (references Pages 2 and AcroForm 5)
  // 2: Pages
  // 3: Page (references Contents 4 and Annots array)
  // 4: Contents stream (empty)
  // 5: AcroForm (Fields array references widget objects)
  // 6..(5+n_fields): Widget annotations with /FT /Sig
  // last: (optional) Sig dictionaries referenced by /V, but we can omit /V to keep it simple.
  const int first_widget_obj = 6;
  const int last_obj = 5 + n_fields;

  auto obj = [](int num, const std::string &body) {
    std::ostringstream oss;
    oss << num << " 0 obj\n" << body << "\nendobj\n";
    return oss.str();
  };

  std::ostringstream annots;
  annots << "[";
  for (int i = 0; i < n_fields; ++i) {
    annots << (first_widget_obj + i) << " 0 R ";
  }
  annots << "]";

  std::ostringstream fields;
  fields << "[";
  for (int i = 0; i < n_fields; ++i) {
    fields << (first_widget_obj + i) << " 0 R ";
  }
  fields << "]";

  std::vector<std::string> objects;
  objects.reserve(static_cast<size_t>(last_obj + 1));

  // Placeholder for object 0 (free object entry in xref).
  objects.push_back("");

  objects.push_back(obj(1,
                        "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>"));
  objects.push_back(obj(2,
                        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"));
  objects.push_back(obj(3,
                        "<< /Type /Page /Parent 2 0 R "
                        "/MediaBox [0 0 200 200] "
                        "/Resources << >> "
                        "/Contents 4 0 R "
                        "/Annots " +
                            annots.str() + " >>"));
  objects.push_back(obj(4,
                        "<< /Length 0 >>\nstream\n\nendstream"));
  objects.push_back(obj(5,
                        "<< /Fields " + fields.str() + " /SigFlags 3 >>"));

  for (int i = 0; i < n_fields; ++i) {
    const int objnum = first_widget_obj + i;
    std::ostringstream w;
    w << "<< /Type /Annot /Subtype /Widget /FT /Sig "
      << "/Rect [10 10 60 30] "
      << "/T (Signature" << (i + 1) << ") "
      << "/P 3 0 R >>";
    objects.push_back(obj(objnum, w.str()));
  }

  // Build full PDF with xref.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<long> offsets;
  offsets.resize(static_cast<size_t>(last_obj + 1), 0);

  // Object 0 offset is 0 by spec in xref (free entry).
  for (int i = 1; i <= last_obj; ++i) {
    offsets[static_cast<size_t>(i)] = static_cast<long>(pdf.tellp());
    pdf << objects[static_cast<size_t>(i)];
  }

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (last_obj + 1) << "\n";
  // free entry
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i <= last_obj; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[static_cast<size_t>(i)]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (last_obj + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xref_pos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static std::string WriteTempPdf(const std::string &contents, const char *basename) {
  gchar *dir_template = g_build_filename(g_get_tmp_dir(), "poppler-gtest-XXXXXX", nullptr);
  gchar *tmpdir = g_mkdtemp(dir_template);
  // If mkdtemp fails, tmpdir == nullptr and dir_template is unchanged.
  std::string out_path;
  if (tmpdir) {
    gchar *path = g_build_filename(tmpdir, basename, nullptr);
    out_path = path;
    g_free(path);
  } else {
    // Fallback: write into tmp dir directly with a unique-ish name
    gchar *path = g_build_filename(g_get_tmp_dir(), basename, nullptr);
    out_path = path;
    g_free(path);
  }
  // dir_template points to created directory path (or template). Either way, free it.
  g_free(dir_template);

  std::ofstream ofs(out_path, std::ios::binary);
  ofs.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  ofs.close();

  return out_path;
}

class PopplerDocumentGetNSignaturesTest_2193 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GType system is ready; safe to call multiple times in modern GLib.
    // (No-op on newer versions, but harmless.)
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerDocumentGetNSignaturesTest_2193, NullDocumentReturns0AndEmitsCritical_2193) {
  ScopedGLogHandler handler("Poppler", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  gint n = poppler_document_get_n_signatures(nullptr);
  EXPECT_EQ(n, 0);

  // g_return_val_if_fail typically logs a critical message in the library's log domain.
  // We only assert that at least one critical was emitted, without depending on exact text.
  EXPECT_GE(handler.count(), 1);
}

TEST_F(PopplerDocumentGetNSignaturesTest_2193, NonDocumentInstanceReturns0AndEmitsCritical_2193) {
  ScopedGLogHandler handler("Poppler", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  GObject *not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  gint n = poppler_document_get_n_signatures(reinterpret_cast<PopplerDocument *>(not_a_doc));
  EXPECT_EQ(n, 0);

  EXPECT_GE(handler.count(), 1);

  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetNSignaturesTest_2193, PdfWithoutSignaturesReturns0_2193) {
  const std::string pdf = BuildPdfWithNSignatureFields(0);
  const std::string path = WriteTempPdf(pdf, "no-sigs.pdf");
  const std::string uri = ToFileUri(path);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  gint n = poppler_document_get_n_signatures(doc);
  EXPECT_EQ(n, 0);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetNSignaturesTest_2193, PdfWithOneSignatureFieldReturns1_2193) {
  const std::string pdf = BuildPdfWithNSignatureFields(1);
  const std::string path = WriteTempPdf(pdf, "one-sig-field.pdf");
  const std::string uri = ToFileUri(path);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  gint n = poppler_document_get_n_signatures(doc);
  EXPECT_EQ(n, 1);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetNSignaturesTest_2193, PdfWithMultipleSignatureFieldsCountsAll_2193) {
  const std::string pdf = BuildPdfWithNSignatureFields(2);
  const std::string path = WriteTempPdf(pdf, "two-sig-fields.pdf");
  const std::string uri = ToFileUri(path);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  gint n = poppler_document_get_n_signatures(doc);
  EXPECT_EQ(n, 2);

  g_object_unref(doc);
}

} // namespace