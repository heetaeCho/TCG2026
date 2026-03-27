// File: poppler-document-save-a-copy-test_2147.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

#include <string>
#include <vector>

namespace {

class PopplerDocumentSaveACopyTest_2147 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a temp directory for this test.
    gchar *tmpl = g_strdup("/tmp/poppler-savecopy-XXXXXX");
    tmp_dir_ = g_mkdtemp(tmpl);
    ASSERT_NE(tmp_dir_, nullptr);
    // tmp_dir_ now points into tmpl buffer; keep ownership.
    tmp_dir_buf_.reset(tmpl);
  }

  void TearDown() override {
    // Best-effort cleanup.
    for (const auto &p : paths_to_delete_) {
      if (!p.empty()) {
        g_remove(p.c_str());
      }
    }
    if (tmp_dir_ && *tmp_dir_) {
      // Remove directory (may fail if not empty).
      g_rmdir(tmp_dir_);
    }
  }

  std::string MakePath(const char *name) {
    gchar *p = g_build_filename(tmp_dir_, name, nullptr);
    std::string out = p ? p : "";
    g_free(p);
    return out;
  }

  std::string WriteFile(const char *name, const std::string &contents) {
    std::string path = MakePath(name);
    GError *error = nullptr;
    gboolean ok = g_file_set_contents(path.c_str(), contents.data(),
                                     static_cast<gssize>(contents.size()), &error);
    EXPECT_TRUE(ok);
    EXPECT_EQ(error, nullptr);
    if (error) g_error_free(error);
    if (ok) paths_to_delete_.push_back(path);
    return path;
  }

  std::string ToFileUri(const std::string &path) {
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
    EXPECT_NE(uri, nullptr);
    EXPECT_EQ(error, nullptr);
    if (error) g_error_free(error);
    std::string out = uri ? uri : "";
    g_free(uri);
    return out;
  }

  PopplerDocument *LoadDocFromPdfPath(const std::string &pdf_path) {
    std::string uri = ToFileUri(pdf_path);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    EXPECT_NE(doc, nullptr);
    EXPECT_EQ(error, nullptr);
    if (error) g_error_free(error);
    return doc;
  }

  // A tiny, valid-ish single-page PDF for loading (no need to render).
  static std::string MinimalPdfBytes() {
    // Keep it small and self-contained; Poppler accepts many minimal PDFs.
    return "%PDF-1.1\n"
           "1 0 obj\n"
           "<< /Type /Catalog /Pages 2 0 R >>\n"
           "endobj\n"
           "2 0 obj\n"
           "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
           "endobj\n"
           "3 0 obj\n"
           "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] >>\n"
           "endobj\n"
           "xref\n"
           "0 4\n"
           "0000000000 65535 f \n"
           "0000000010 00000 n \n"
           "0000000060 00000 n \n"
           "0000000123 00000 n \n"
           "trailer\n"
           "<< /Size 4 /Root 1 0 R >>\n"
           "startxref\n"
           "190\n"
           "%%EOF\n";
  }

  struct LogCapture {
    int critical_count = 0;
    std::string last_message;
    static void Handler(const gchar *log_domain,
                        GLogLevelFlags log_level,
                        const gchar *message,
                        gpointer user_data) {
      (void)log_domain;
      if ((log_level & G_LOG_LEVEL_CRITICAL) == 0) return;
      auto *self = static_cast<LogCapture *>(user_data);
      self->critical_count++;
      if (message) self->last_message = message;
    }
  };

  const gchar *tmp_dir_ = nullptr;
  struct GFreeDeleter {
    void operator()(gchar *p) const { g_free(p); }
  };
  std::unique_ptr<gchar, GFreeDeleter> tmp_dir_buf_{nullptr};
  std::vector<std::string> paths_to_delete_;
};

TEST_F(PopplerDocumentSaveACopyTest_2147, SaveCopySucceeds_CreatesFile_2147) {
  const std::string pdf_path = WriteFile("in.pdf", MinimalPdfBytes());
  PopplerDocument *doc = LoadDocFromPdfPath(pdf_path);
  ASSERT_NE(doc, nullptr);

  const std::string out_path = MakePath("out.pdf");
  const std::string out_uri = ToFileUri(out_path);

  GError *error = nullptr;
  gboolean ok = poppler_document_save_a_copy(doc, out_uri.c_str(), &error);

  EXPECT_TRUE(ok);
  EXPECT_EQ(error, nullptr);

  // Observable side effect: output file exists and is non-empty.
  GStatBuf st;
  ASSERT_EQ(g_stat(out_path.c_str(), &st), 0);
  EXPECT_GT(st.st_size, 0);

  paths_to_delete_.push_back(out_path);

  if (error) g_error_free(error);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentSaveACopyTest_2147, SaveCopyInvalidUri_FailsAndSetsError_2147) {
  const std::string pdf_path = WriteFile("in.pdf", MinimalPdfBytes());
  PopplerDocument *doc = LoadDocFromPdfPath(pdf_path);
  ASSERT_NE(doc, nullptr);

  // Invalid URI for g_filename_from_uri() (not a file:// URI).
  const char *bad_uri = "not-a-uri";

  GError *error = nullptr;
  gboolean ok = poppler_document_save_a_copy(doc, bad_uri, &error);

  EXPECT_FALSE(ok);
  EXPECT_NE(error, nullptr);

  if (error) g_error_free(error);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentSaveACopyTest_2147, SaveCopyUnwritableDestination_FailsAndSetsError_2147) {
  const std::string pdf_path = WriteFile("in.pdf", MinimalPdfBytes());
  PopplerDocument *doc = LoadDocFromPdfPath(pdf_path);
  ASSERT_NE(doc, nullptr);

  // Create a directory and make it non-writable, then attempt to save inside it.
  const std::string ro_dir = MakePath("readonly");
  ASSERT_EQ(g_mkdir(ro_dir.c_str(), 0700), 0);
  ASSERT_EQ(g_chmod(ro_dir.c_str(), 0500), 0); // no write bit

  const std::string out_path = ro_dir + G_DIR_SEPARATOR_S + "out.pdf";
  const std::string out_uri = ToFileUri(out_path);

  GError *error = nullptr;
  gboolean ok = poppler_document_save_a_copy(doc, out_uri.c_str(), &error);

  EXPECT_FALSE(ok);
  EXPECT_NE(error, nullptr);

  // Restore permissions so cleanup can remove directory if possible.
  (void)g_chmod(ro_dir.c_str(), 0700);
  (void)g_remove(out_path.c_str());
  (void)g_rmdir(ro_dir.c_str());

  if (error) g_error_free(error);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentSaveACopyTest_2147, SaveCopyNullDocument_ReturnsFalseAndLogsCritical_2147) {
  LogCapture cap;

  // Capture critical logs emitted by g_return_val_if_fail.
  const guint handler_id =
      g_log_set_handler(nullptr, G_LOG_LEVEL_CRITICAL, &LogCapture::Handler, &cap);

  GError *error = nullptr;
  gboolean ok = poppler_document_save_a_copy(nullptr, "file:///tmp/out.pdf", &error);

  EXPECT_FALSE(ok);
  EXPECT_EQ(error, nullptr); // early return; should not set error
  EXPECT_GE(cap.critical_count, 1);

  g_log_remove_handler(nullptr, handler_id);
  if (error) g_error_free(error);
}

TEST_F(PopplerDocumentSaveACopyTest_2147, SaveCopyWithNullErrorPtr_NoCrash_ReturnsBool_2147) {
  const std::string pdf_path = WriteFile("in.pdf", MinimalPdfBytes());
  PopplerDocument *doc = LoadDocFromPdfPath(pdf_path);
  ASSERT_NE(doc, nullptr);

  const std::string out_path = MakePath("out-noerr.pdf");
  const std::string out_uri = ToFileUri(out_path);

  // error == nullptr is allowed by the interface.
  gboolean ok = poppler_document_save_a_copy(doc, out_uri.c_str(), nullptr);

  // Observable behavior: should either succeed and create a file, or fail cleanly.
  // We assert the non-crash + consistency with file existence.
  GStatBuf st;
  const int stat_rc = g_stat(out_path.c_str(), &st);
  if (ok) {
    EXPECT_EQ(stat_rc, 0);
    if (stat_rc == 0) EXPECT_GT(st.st_size, 0);
    paths_to_delete_.push_back(out_path);
  } else {
    // If it failed, file may or may not exist; just ensure no crash and return is boolean.
    SUCCEED();
  }

  g_object_unref(doc);
}

} // namespace