// File: poppler-page-render-to-ps-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>

namespace {

class PopplerPageRenderToPsTest_2451 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Nothing required, but keep for symmetry / future expansion.
  }

  static void TearDownTestSuite() {
    // Nothing required.
  }

  static std::string WriteMinimalPdfToTempFileOrDie() {
    // A tiny one-page PDF (valid enough for Poppler to open).
    // Keep it stable and simple: 1 page, empty content stream.
    static const char kPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300] /Contents 4 0 R >>\n"
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
        "256\n"
        "%%EOF\n";

    gchar *tmp_path = nullptr;
    GError *error = nullptr;

    // Create a temp file.
    int fd = g_file_open_tmp("poppler_render_to_ps_2451_XXXXXX.pdf", &tmp_path, &error);
    if (fd == -1) {
      std::string msg = "g_file_open_tmp failed: ";
      msg += (error && error->message) ? error->message : "unknown";
      if (error) g_error_free(error);
      FAIL() << msg;
    }

    // Write PDF content.
    gssize want = static_cast<gssize>(sizeof(kPdf) - 1);
    gssize written = write(fd, kPdf, static_cast<size_t>(want));
    close(fd);

    if (written != want) {
      std::string p = tmp_path ? tmp_path : "";
      if (tmp_path) g_free(tmp_path);
      FAIL() << "Failed to write minimal PDF to temp file (path=" << p << ")";
    }

    std::string path = tmp_path;
    g_free(tmp_path);
    return path;
  }

  static std::string MakeTempPsPathOrDie() {
    gchar *tmp_path = nullptr;
    GError *error = nullptr;

    int fd = g_file_open_tmp("poppler_render_to_ps_2451_XXXXXX.ps", &tmp_path, &error);
    if (fd == -1) {
      std::string msg = "g_file_open_tmp for PS failed: ";
      msg += (error && error->message) ? error->message : "unknown";
      if (error) g_error_free(error);
      FAIL() << msg;
    }
    close(fd);

    std::string path = tmp_path;
    g_free(tmp_path);

    // Ensure empty starting file (best-effort).
    (void)g_remove(path.c_str());
    return path;
  }

  static goffset FileSizeOrMinus1(const std::string &path) {
    GStatBuf st;
    if (g_stat(path.c_str(), &st) != 0)
      return -1;
    return static_cast<goffset>(st.st_size);
  }
};

TEST_F(PopplerPageRenderToPsTest_2451, NullPageTriggersCritical_2451) {
  // g_return_if_fail(POPPLER_IS_PAGE(page))
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
  poppler_page_render_to_ps(nullptr, reinterpret_cast<PopplerPSFile *>(0x1));
  g_test_assert_expected_messages();
}

TEST_F(PopplerPageRenderToPsTest_2451, NullPsFileTriggersCritical_2451) {
  // Need a valid PopplerPage* to reach g_return_if_fail(ps_file != nullptr).
  const std::string pdf_path = WriteMinimalPdfToTempFileOrDie();
  g_autofree gchar *pdf_uri = g_filename_to_uri(pdf_path.c_str(), nullptr, nullptr);
  ASSERT_NE(pdf_uri, nullptr);

  GError *error = nullptr;
  g_autoptr(PopplerDocument) doc = poppler_document_new_from_file(pdf_uri, nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "");
  if (error) g_error_free(error);

  g_autoptr(PopplerPage) page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*ps_file != NULL*");
  poppler_page_render_to_ps(page, nullptr);
  g_test_assert_expected_messages();

  (void)g_remove(pdf_path.c_str());
}

TEST_F(PopplerPageRenderToPsTest_2451, RendersToPsFileByFilenameProducesNonEmptyOutput_2451) {
  const std::string pdf_path = WriteMinimalPdfToTempFileOrDie();
  g_autofree gchar *pdf_uri = g_filename_to_uri(pdf_path.c_str(), nullptr, nullptr);
  ASSERT_NE(pdf_uri, nullptr);

  GError *error = nullptr;
  g_autoptr(PopplerDocument) doc = poppler_document_new_from_file(pdf_uri, nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "");
  if (error) g_error_free(error);

  g_autoptr(PopplerPage) page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  const std::string ps_path = MakeTempPsPathOrDie();

  // first_page is 1-based in the PS file API (as used by the implementation),
  // n_pages=1 means render a single page range.
  g_autoptr(PopplerPSFile) ps =
      poppler_ps_file_new(doc, ps_path.c_str(), /*first_page=*/1, /*n_pages=*/1);
  ASSERT_NE(ps, nullptr);

  // No crash is the primary observable behavior; also verify output exists and is non-empty.
  poppler_page_render_to_ps(page, ps);

  const goffset size = FileSizeOrMinus1(ps_path);
  ASSERT_GT(size, 0) << "Expected PS output file to be created and non-empty";

  poppler_ps_file_free(ps);
  (void)g_remove(ps_path.c_str());
  (void)g_remove(pdf_path.c_str());
}

TEST_F(PopplerPageRenderToPsTest_2451, RendersToPsFileByFdProducesNonEmptyOutput_2451) {
  const std::string pdf_path = WriteMinimalPdfToTempFileOrDie();
  g_autofree gchar *pdf_uri = g_filename_to_uri(pdf_path.c_str(), nullptr, nullptr);
  ASSERT_NE(pdf_uri, nullptr);

  GError *error = nullptr;
  g_autoptr(PopplerDocument) doc = poppler_document_new_from_file(pdf_uri, nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "");
  if (error) g_error_free(error);

  g_autoptr(PopplerPage) page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  // Create a temp PS file and open an FD for it.
  const std::string ps_path = MakeTempPsPathOrDie();
  int fd = g_open(ps_path.c_str(), O_CREAT | O_TRUNC | O_RDWR, 0600);
  ASSERT_NE(fd, -1);

  g_autoptr(PopplerPSFile) ps =
      poppler_ps_file_new_fd(doc, fd, /*first_page=*/1, /*n_pages=*/1);
  ASSERT_NE(ps, nullptr);

  poppler_page_render_to_ps(page, ps);

  // Close fd after rendering (PSOutputDev may keep it open internally, but closing
  // our handle should still be fine for checking file size on disk).
  close(fd);

  const goffset size = FileSizeOrMinus1(ps_path);
  ASSERT_GT(size, 0) << "Expected PS output to be created and non-empty when using FD";

  poppler_ps_file_free(ps);
  (void)g_remove(ps_path.c_str());
  (void)g_remove(pdf_path.c_str());
}

TEST_F(PopplerPageRenderToPsTest_2451, CallingTwiceDoesNotCrashAndKeepsOutputNonEmpty_2451) {
  const std::string pdf_path = WriteMinimalPdfToTempFileOrDie();
  g_autofree gchar *pdf_uri = g_filename_to_uri(pdf_path.c_str(), nullptr, nullptr);
  ASSERT_NE(pdf_uri, nullptr);

  GError *error = nullptr;
  g_autoptr(PopplerDocument) doc = poppler_document_new_from_file(pdf_uri, nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "");
  if (error) g_error_free(error);

  g_autoptr(PopplerPage) page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  const std::string ps_path = MakeTempPsPathOrDie();
  g_autoptr(PopplerPSFile) ps =
      poppler_ps_file_new(doc, ps_path.c_str(), /*first_page=*/1, /*n_pages=*/1);
  ASSERT_NE(ps, nullptr);

  poppler_page_render_to_ps(page, ps);
  const goffset size1 = FileSizeOrMinus1(ps_path);
  ASSERT_GT(size1, 0);

  // Second render to same PopplerPSFile.
  poppler_page_render_to_ps(page, ps);
  const goffset size2 = FileSizeOrMinus1(ps_path);
  ASSERT_GT(size2, 0);

  poppler_ps_file_free(ps);
  (void)g_remove(ps_path.c_str());
  (void)g_remove(pdf_path.c_str());
}

}  // namespace

int main(int argc, char **argv) {
  // Initialize both frameworks so GLib log expectations work alongside gtest.
  g_test_init(&argc, &argv, nullptr);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}