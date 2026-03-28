// poppler-document-get-page-mode-ut-2196.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerDocumentGetPageModeTest_2196 : public ::testing::Test {
protected:
  static std::string BuildMinimalPdfWithOptionalPageMode(const std::optional<std::string> &pageModeName)
  {
    // Minimal, valid PDF with 1 empty page.
    // If pageModeName is provided, adds: /PageMode /<pageModeName> to the catalog.
    //
    // Objects:
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Contents (empty)
    std::vector<std::string> objs;
    objs.reserve(4);

    {
      std::string catalog = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R";
      if (pageModeName.has_value()) {
        catalog += " /PageMode /" + *pageModeName;
      }
      catalog += " >>\nendobj\n";
      objs.push_back(std::move(catalog));
    }

    objs.push_back(
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n");

    objs.push_back(
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 1 1]\n"
        "   /Contents 4 0 R /Resources << >> >>\n"
        "endobj\n");

    objs.push_back(
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "\n"
        "endstream\n"
        "endobj\n");

    std::string out;
    out.reserve(1024);
    out += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

    std::vector<long> offsets;
    offsets.reserve(objs.size() + 1);
    offsets.push_back(0); // object 0 (free)

    for (const auto &o : objs) {
      offsets.push_back(static_cast<long>(out.size()));
      out += o;
    }

    const long xref_pos = static_cast<long>(out.size());
    out += "xref\n";
    out += "0 5\n";
    out += "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      out += buf;
    }

    out += "trailer\n";
    out += "<< /Size 5 /Root 1 0 R >>\n";
    out += "startxref\n";
    out += std::to_string(xref_pos);
    out += "\n%%EOF\n";

    return out;
  }

  static std::pair<std::string, std::string> WriteTempPdf(const std::string &pdfBytes)
  {
    // Returns {filepath, uri}
    gchar *tmpl = g_strdup("/tmp/poppler_page_mode_XXXXXX.pdf");
    int fd = g_mkstemp(tmpl);
    EXPECT_NE(fd, -1) << "Failed to create temp file";

    const char *data = pdfBytes.data();
    gsize remaining = static_cast<gsize>(pdfBytes.size());
    while (remaining > 0) {
      const ssize_t wrote = write(fd, data, remaining);
      EXPECT_GT(wrote, 0) << "Failed to write temp PDF";
      data += wrote;
      remaining -= static_cast<gsize>(wrote);
    }
    close(fd);

    gchar *uri = g_filename_to_uri(tmpl, nullptr, nullptr);
    EXPECT_NE(uri, nullptr) << "Failed to create file URI";

    std::string path(tmpl);
    std::string uriStr(uri);

    g_free(uri);
    g_free(tmpl);

    return {path, uriStr};
  }

  static PopplerDocument *OpenDocumentFromUri(const std::string &uri)
  {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    if (!doc) {
      std::string msg = error ? error->message : "unknown error";
      if (error) {
        g_error_free(error);
      }
      ADD_FAILURE() << "Failed to open PopplerDocument: " << msg;
      return nullptr;
    }
    if (error) {
      // Some builds may set non-fatal warnings; be strict and free if present.
      g_error_free(error);
    }
    return doc;
  }

  static void SilentLogHandler(const gchar *, GLogLevelFlags, const gchar *, gpointer) {}
};

TEST_F(PopplerDocumentGetPageModeTest_2196, NullDocumentReturnsUnset_2196)
{
  // g_return_val_if_fail() will log a critical message; silence it for this test.
  const guint handler =
      g_log_set_handler(nullptr, static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL), &SilentLogHandler, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(nullptr), POPPLER_PAGE_MODE_UNSET);

  g_log_remove_handler(nullptr, handler);
}

TEST_F(PopplerDocumentGetPageModeTest_2196, MissingPageModeReturnsUnset_2196)
{
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::nullopt);
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_UNSET);

  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerDocumentGetPageModeTest_2196, UseNoneMapsToNone_2196)
{
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::make_optional<std::string>("UseNone"));
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_NONE);

  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerDocumentGetPageModeTest_2196, UseOutlinesMapsToUseOutlines_2196)
{
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::make_optional<std::string>("UseOutlines"));
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_USE_OUTLINES);

  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerDocumentGetPageModeTest_2196, UseThumbsMapsToUseThumbs_2196)
{
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::make_optional<std::string>("UseThumbs"));
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_USE_THUMBS);

  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerDocumentGetPageModeTest_2196, FullScreenMapsToFullScreen_2196)
{
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::make_optional<std::string>("FullScreen"));
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_FULL_SCREEN);

  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerDocumentGetPageModeTest_2196, UseOCMapsToUseOC_2196)
{
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::make_optional<std::string>("UseOC"));
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_USE_OC);

  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerDocumentGetPageModeTest_2196, UseAttachmentsMapsToUseAttachments_2196)
{
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::make_optional<std::string>("UseAttachments"));
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_USE_ATTACHMENTS);

  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerDocumentGetPageModeTest_2196, UnknownPageModeFallsBackToUnset_2196)
{
  // Boundary/error-ish case: a non-standard name. Observable behavior should be a safe fallback.
  const std::string pdf = BuildMinimalPdfWithOptionalPageMode(std::make_optional<std::string>("NotARealMode"));
  const auto [path, uri] = WriteTempPdf(pdf);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_mode(doc), POPPLER_PAGE_MODE_UNSET);

  g_object_unref(doc);
  std::remove(path.c_str());
}

} // namespace