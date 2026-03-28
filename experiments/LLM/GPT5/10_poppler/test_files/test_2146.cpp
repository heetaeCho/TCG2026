// File: poppler-document-save-test_2146.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

namespace {

class PopplerDocumentSaveTest_2146 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a temporary directory for the test artifacts.
    GError* error = nullptr;
    gchar* tmpdir_template = g_strdup("/tmp/poppler-save-XXXXXX");
    tmp_dir_ = g_mkdtemp(tmpdir_template);
    ASSERT_NE(tmp_dir_, nullptr);
    // tmp_dir_ now points inside tmpdir_template; keep the allocated buffer.
    tmpdir_buf_.reset(tmpdir_template);

    // Write a minimal, valid PDF to a temp file, then open it with Poppler.
    src_path_ = g_build_filename(tmp_dir_, "source.pdf", nullptr);
    ASSERT_NE(src_path_, nullptr);

    const char kMinimalPdf[] =
        "%PDF-1.1\n"
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
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "0000000183\n"
        "%%EOF\n";

    ASSERT_TRUE(g_file_set_contents(src_path_, kMinimalPdf, -1, &error))
        << (error ? error->message : "unknown error");
    if (error) {
      g_clear_error(&error);
    }

    src_uri_ = g_filename_to_uri(src_path_, /*hostname=*/nullptr, &error);
    ASSERT_NE(src_uri_, nullptr) << (error ? error->message : "g_filename_to_uri failed");
    if (error) {
      g_clear_error(&error);
    }

    doc_ = poppler_document_new_from_file(src_uri_, /*password=*/nullptr, &error);
    ASSERT_NE(doc_, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
    if (error) {
      g_clear_error(&error);
    }
  }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (src_uri_) {
      g_free(src_uri_);
      src_uri_ = nullptr;
    }
    if (src_path_) {
      // Best-effort cleanup; file may be overwritten in some tests.
      g_remove(src_path_);
      g_free(src_path_);
      src_path_ = nullptr;
    }
    if (tmp_dir_) {
      // Remove any remaining files created by tests (best effort).
      // We only created within tmp_dir_ and our test filenames are known.
      gchar* p1 = g_build_filename(tmp_dir_, "saved.pdf", nullptr);
      if (p1) {
        g_remove(p1);
        g_free(p1);
      }
      gchar* p2 = g_build_filename(tmp_dir_, "dest_dir", nullptr);
      if (p2) {
        g_rmdir(p2);
        g_free(p2);
      }
      g_rmdir(tmp_dir_);
      tmp_dir_ = nullptr;
    }
    tmpdir_buf_.reset();
  }

  struct GFreeDeleter {
    void operator()(gchar* p) const { g_free(p); }
  };

  std::unique_ptr<gchar, GFreeDeleter> tmpdir_buf_;
  gchar* tmp_dir_ = nullptr;

  gchar* src_path_ = nullptr;
  gchar* src_uri_ = nullptr;
  PopplerDocument* doc_ = nullptr;
};

TEST_F(PopplerDocumentSaveTest_2146, NullDocumentReturnsFalseAndEmitsCritical_2146) {
  // poppler_document_save uses g_return_val_if_fail(POPPLER_IS_DOCUMENT(document), FALSE)
  // which emits a critical log and returns FALSE.
  GError* error = nullptr;

  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
  gboolean ok = poppler_document_save(nullptr, "file:///tmp/does-not-matter.pdf", &error);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);
  // The function may or may not touch 'error' in this early-return path.
  if (error) {
    g_clear_error(&error);
  }
}

TEST_F(PopplerDocumentSaveTest_2146, InvalidUriReturnsFalseAndSetsError_2146) {
  GError* error = nullptr;

  // Not a valid URI for g_filename_from_uri().
  gboolean ok = poppler_document_save(doc_, "not a uri", &error);

  EXPECT_FALSE(ok);
  EXPECT_NE(error, nullptr);
  if (error) {
    g_clear_error(&error);
  }
}

TEST_F(PopplerDocumentSaveTest_2146, NonFileSchemeUriReturnsFalseAndSetsError_2146) {
  GError* error = nullptr;

  // g_filename_from_uri() should fail for a non-file URI.
  gboolean ok = poppler_document_save(doc_, "http://example.com/test.pdf", &error);

  EXPECT_FALSE(ok);
  EXPECT_NE(error, nullptr);
  if (error) {
    g_clear_error(&error);
  }
}

TEST_F(PopplerDocumentSaveTest_2146, SaveToWritableFileUriSucceedsAndCreatesFile_2146) {
  GError* error = nullptr;

  gchar* dest_path = g_build_filename(tmp_dir_, "saved.pdf", nullptr);
  ASSERT_NE(dest_path, nullptr);

  gchar* dest_uri = g_filename_to_uri(dest_path, /*hostname=*/nullptr, &error);
  ASSERT_NE(dest_uri, nullptr) << (error ? error->message : "g_filename_to_uri failed");
  if (error) g_clear_error(&error);

  gboolean ok = poppler_document_save(doc_, dest_uri, &error);

  EXPECT_TRUE(ok);
  EXPECT_EQ(error, nullptr);

  // Verify observable effect: the destination exists and is a regular file.
  GStatBuf st;
  ASSERT_EQ(g_stat(dest_path, &st), 0);
  EXPECT_TRUE(S_ISREG(st.st_mode));
  EXPECT_GT(st.st_size, 0);

  g_free(dest_uri);
  g_free(dest_path);
}

TEST_F(PopplerDocumentSaveTest_2146, SaveToDirectoryUriFailsAndSetsError_2146) {
  // Boundary / error case: destination is a directory, not a file.
  // This should cause the underlying save operation to fail; we only assert observable outcomes.
  GError* error = nullptr;

  gchar* dest_dir = g_build_filename(tmp_dir_, "dest_dir", nullptr);
  ASSERT_NE(dest_dir, nullptr);
  ASSERT_EQ(g_mkdir(dest_dir, 0700), 0);

  gchar* dest_uri = g_filename_to_uri(dest_dir, /*hostname=*/nullptr, &error);
  ASSERT_NE(dest_uri, nullptr) << (error ? error->message : "g_filename_to_uri failed");
  if (error) g_clear_error(&error);

  gboolean ok = poppler_document_save(doc_, dest_uri, &error);

  EXPECT_FALSE(ok);
  EXPECT_NE(error, nullptr);

  if (error) g_clear_error(&error);
  g_free(dest_uri);
  g_free(dest_dir);
}

}  // namespace