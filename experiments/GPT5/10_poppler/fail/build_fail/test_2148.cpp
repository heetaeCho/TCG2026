// File: poppler-document-save-to-fd-test_2148.cc
#include <gtest/gtest.h>

#include <fcntl.h>
#include <unistd.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

// Minimal, valid one-page PDF (very small; enough for Poppler to parse).
static const char kMinimalPdf_2148[] =
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
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 5\n"
    "0000000000 65535 f \n"
    "0000000010 00000 n \n"
    "0000000061 00000 n \n"
    "0000000116 00000 n \n"
    "0000000202 00000 n \n"
    "trailer\n"
    "<< /Size 5 /Root 1 0 R >>\n"
    "startxref\n"
    "266\n"
    "%%EOF\n";

static PopplerDocument* CreateDocFromMinimalPdf_2148() {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_data(
      kMinimalPdf_2148, static_cast<int>(strlen(kMinimalPdf_2148)),
      /*password=*/nullptr, &error);
  EXPECT_EQ(error, nullptr) << (error ? error->message : "");
  EXPECT_NE(doc, nullptr);
  if (error) g_error_free(error);
  return doc;
}

static goffset GetFileSize_2148(const char* path) {
  GStatBuf st;
  if (g_stat(path, &st) != 0) return -1;
  return static_cast<goffset>(st.st_size);
}

class PopplerDocumentSaveToFdTest_2148 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  PopplerDocument* doc_ = nullptr;
};

TEST_F(PopplerDocumentSaveToFdTest_2148, SaveWithoutChangesWritesNonEmpty_2148) {
  doc_ = CreateDocFromMinimalPdf_2148();
  ASSERT_NE(doc_, nullptr);

  GError* error = nullptr;
  gchar* tmp_path = nullptr;

  int fd = g_file_open_tmp("poppler-savefd-2148-XXXXXX", &tmp_path, &error);
  ASSERT_NE(fd, -1);
  ASSERT_NE(tmp_path, nullptr);
  ASSERT_EQ(error, nullptr) << (error ? error->message : "");

  const gboolean ok = poppler_document_save_to_fd(
      doc_, fd, /*include_changes=*/FALSE, &error);

  // Close regardless of ownership semantics; ignore EBADF if already closed.
  (void)close(fd);

  EXPECT_TRUE(ok);
  EXPECT_EQ(error, nullptr) << (error ? error->message : "");

  const goffset sz = GetFileSize_2148(tmp_path);
  EXPECT_GT(sz, 0) << "Expected output file to be non-empty";

  g_remove(tmp_path);
  g_free(tmp_path);
  if (error) g_error_free(error);
}

TEST_F(PopplerDocumentSaveToFdTest_2148, SaveWithChangesWritesNonEmpty_2148) {
  doc_ = CreateDocFromMinimalPdf_2148();
  ASSERT_NE(doc_, nullptr);

  GError* error = nullptr;
  gchar* tmp_path = nullptr;

  int fd = g_file_open_tmp("poppler-savefd-2148-XXXXXX", &tmp_path, &error);
  ASSERT_NE(fd, -1);
  ASSERT_NE(tmp_path, nullptr);
  ASSERT_EQ(error, nullptr) << (error ? error->message : "");

  const gboolean ok = poppler_document_save_to_fd(
      doc_, fd, /*include_changes=*/TRUE, &error);

  (void)close(fd);

  EXPECT_TRUE(ok);
  EXPECT_EQ(error, nullptr) << (error ? error->message : "");

  const goffset sz = GetFileSize_2148(tmp_path);
  EXPECT_GT(sz, 0) << "Expected output file to be non-empty";

  g_remove(tmp_path);
  g_free(tmp_path);
  if (error) g_error_free(error);
}

TEST_F(PopplerDocumentSaveToFdTest_2148, NullDocumentReturnsFalse_2148) {
  // g_return_val_if_fail emits a critical log; expect it to avoid noisy output.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");

  const gboolean ok =
      poppler_document_save_to_fd(/*document=*/nullptr, /*fd=*/1,
                                  /*include_changes=*/FALSE, /*error=*/nullptr);

  g_test_assert_expected_messages();
  EXPECT_FALSE(ok);
}

TEST_F(PopplerDocumentSaveToFdTest_2148, FdMinusOneReturnsFalse_2148) {
  doc_ = CreateDocFromMinimalPdf_2148();
  ASSERT_NE(doc_, nullptr);

  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*fd != -1*");

  const gboolean ok =
      poppler_document_save_to_fd(doc_, /*fd=*/-1, /*include_changes=*/FALSE,
                                  /*error=*/nullptr);

  g_test_assert_expected_messages();
  EXPECT_FALSE(ok);
}

TEST_F(PopplerDocumentSaveToFdTest_2148, ClosedFdReturnsFalseAndSetsError_2148) {
  doc_ = CreateDocFromMinimalPdf_2148();
  ASSERT_NE(doc_, nullptr);

  // Create a temp file and immediately close it, then pass the (now invalid) fd.
  GError* error = nullptr;
  gchar* tmp_path = nullptr;
  int fd = g_file_open_tmp("poppler-savefd-2148-XXXXXX", &tmp_path, &error);
  ASSERT_NE(fd, -1);
  ASSERT_NE(tmp_path, nullptr);
  ASSERT_EQ(error, nullptr) << (error ? error->message : "");

  ASSERT_EQ(close(fd), 0);

  error = nullptr;
  const gboolean ok = poppler_document_save_to_fd(
      doc_, fd, /*include_changes=*/FALSE, &error);

  EXPECT_FALSE(ok);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, G_FILE_ERROR);
  // Message should mention failing to open FD for writing.
  EXPECT_NE(g_strstr_len(error->message, -1, "Failed to open FD"), nullptr);

  g_error_free(error);
  g_remove(tmp_path);
  g_free(tmp_path);
}