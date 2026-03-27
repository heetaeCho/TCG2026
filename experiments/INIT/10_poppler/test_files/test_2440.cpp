// Test file: poppler-page-get-thumbnail-size-test_2440.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

class ScopedGLibLogCapture {
public:
  ScopedGLibLogCapture(const char *domain, GLogLevelFlags levels)
      : domain_(domain ? domain : ""), levels_(levels)
  {
    handler_id_ = g_log_set_handler(domain_, levels_, &ScopedGLibLogCapture::Handler, this);
  }

  ~ScopedGLibLogCapture()
  {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_, handler_id_);
    }
  }

  int count() const { return count_; }

  void reset() { count_ = 0; }

private:
  static void Handler(const gchar * /*log_domain*/, GLogLevelFlags /*log_level*/,
                      const gchar * /*message*/, gpointer user_data)
  {
    auto *self = static_cast<ScopedGLibLogCapture *>(user_data);
    self->count_++;
    // Swallow the message to keep test output clean.
  }

  std::string domain_;
  GLogLevelFlags levels_;
  guint handler_id_ = 0;
  int count_ = 0;
};

static std::string BuildPdfFromObjects(const std::vector<std::string> &objects)
{
  // objects[i] corresponds to object number (i+1) with generation 0.
  std::string pdf;
  pdf += "%PDF-1.4\n";

  std::vector<long> offsets;
  offsets.reserve(objects.size() + 1);
  offsets.push_back(0); // object 0 special.

  for (size_t i = 0; i < objects.size(); ++i) {
    offsets.push_back(static_cast<long>(pdf.size()));
    pdf += std::to_string(i + 1);
    pdf += " 0 obj\n";
    pdf += objects[i];
    if (pdf.empty() || pdf.back() != '\n') {
      pdf += "\n";
    }
    pdf += "endobj\n";
  }

  const long xref_offset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 ";
  pdf += std::to_string(objects.size() + 1);
  pdf += "\n";

  // Object 0 entry.
  pdf += "0000000000 65535 f \n";

  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size ";
  pdf += std::to_string(objects.size() + 1);
  pdf += " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";
  return pdf;
}

static std::string WriteTempPdfAndGetUri(const std::string &pdf_bytes)
{
  // Create a unique file in /tmp
  std::string tmpl = "/tmp/poppler_gtest_2440_XXXXXX.pdf";
  std::vector<char> path(tmpl.begin(), tmpl.end());
  path.push_back('\0');

  int fd = g_mkstemp_full(path.data(), O_CREAT | O_EXCL | O_RDWR, 0600);
  if (fd < 0) {
    // Fallback to mkstemp if mkstemp_full isn't available on some builds.
    path.assign(tmpl.begin(), tmpl.end());
    path.push_back('\0');
    fd = g_mkstemp(path.data());
  }
  if (fd < 0) {
    ADD_FAILURE() << "Failed to create temp file: " << std::strerror(errno);
    return {};
  }

  // Write all bytes.
  ssize_t total = 0;
  const char *buf = pdf_bytes.data();
  ssize_t len = static_cast<ssize_t>(pdf_bytes.size());
  while (total < len) {
    ssize_t w = ::write(fd, buf + total, static_cast<size_t>(len - total));
    if (w < 0) {
      ::close(fd);
      ADD_FAILURE() << "Failed to write temp PDF: " << std::strerror(errno);
      return {};
    }
    total += w;
  }
  ::close(fd);

  gchar *uri = g_filename_to_uri(path.data(), nullptr, nullptr);
  if (!uri) {
    ADD_FAILURE() << "g_filename_to_uri failed for path: " << path.data();
    return {};
  }
  std::string uri_str(uri);
  g_free(uri);
  return uri_str;
}

static PopplerDocument *OpenDocFromUriOrFail(const std::string &uri)
{
  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error) {
      g_error_free(error);
    }
    ADD_FAILURE() << "poppler_document_new_from_file failed: " << msg;
  }
  return doc;
}

static std::string MakePdf_WithThumbStream_WidthHeight(int w, int h)
{
  // Objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page (with /Thumb 4 0 R)
  // 4: Thumb stream (with /Width /Height)
  // 5: Content stream
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  objs.emplace_back(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 100 100] "
      "/Resources << >> "
      "/Contents 5 0 R "
      "/Thumb 4 0 R >>");

  std::string thumb =
      "<< /Length 0 /Width " + std::to_string(w) + " /Height " + std::to_string(h) + " >>\n"
      "stream\n"
      "\n"
      "endstream";
  objs.emplace_back(std::move(thumb));

  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");

  return BuildPdfFromObjects(objs);
}

static std::string MakePdf_WithThumbStream_ShortKeys(int w, int h)
{
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  objs.emplace_back(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 100 100] "
      "/Resources << >> "
      "/Contents 5 0 R "
      "/Thumb 4 0 R >>");

  std::string thumb =
      "<< /Length 0 /W " + std::to_string(w) + " /H " + std::to_string(h) + " >>\n"
      "stream\n"
      "\n"
      "endstream";
  objs.emplace_back(std::move(thumb));

  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");

  return BuildPdfFromObjects(objs);
}

static std::string MakePdf_WithThumbNotStream()
{
  // Make /Thumb reference a plain dictionary (not a stream).
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  objs.emplace_back(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 100 100] "
      "/Resources << >> "
      "/Contents 5 0 R "
      "/Thumb 4 0 R >>");

  // Not a stream:
  objs.emplace_back("<< /Width 10 /Height 20 >>");

  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");

  return BuildPdfFromObjects(objs);
}

static std::string MakePdf_WithThumbStream_MissingHeight(int w)
{
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  objs.emplace_back(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 100 100] "
      "/Resources << >> "
      "/Contents 5 0 R "
      "/Thumb 4 0 R >>");

  std::string thumb =
      "<< /Length 0 /Width " + std::to_string(w) + " >>\n"
      "stream\n"
      "\n"
      "endstream";
  objs.emplace_back(std::move(thumb));

  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");

  return BuildPdfFromObjects(objs);
}

static std::string MakePdf_WithoutThumb()
{
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // No /Thumb entry.
  objs.emplace_back(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 100 100] "
      "/Resources << >> "
      "/Contents 4 0 R >>");

  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");

  return BuildPdfFromObjects(objs);
}

class PopplerPageGetThumbnailSizeTest_2440 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Capture g_return_val_if_fail criticals (domain is typically "GLib").
    glib_criticals_ = std::make_unique<ScopedGLibLogCapture>("GLib", G_LOG_LEVEL_CRITICAL);

    uri_with_wh_ = WriteTempPdfAndGetUri(MakePdf_WithThumbStream_WidthHeight(16, 8));
    uri_with_short_ = WriteTempPdfAndGetUri(MakePdf_WithThumbStream_ShortKeys(21, 34));
    uri_thumb_not_stream_ = WriteTempPdfAndGetUri(MakePdf_WithThumbNotStream());
    uri_missing_height_ = WriteTempPdfAndGetUri(MakePdf_WithThumbStream_MissingHeight(12));
    uri_without_thumb_ = WriteTempPdfAndGetUri(MakePdf_WithoutThumb());

    ASSERT_FALSE(uri_with_wh_.empty());
    ASSERT_FALSE(uri_with_short_.empty());
    ASSERT_FALSE(uri_thumb_not_stream_.empty());
    ASSERT_FALSE(uri_missing_height_.empty());
    ASSERT_FALSE(uri_without_thumb_.empty());
  }

  std::unique_ptr<ScopedGLibLogCapture> glib_criticals_;

  std::string uri_with_wh_;
  std::string uri_with_short_;
  std::string uri_thumb_not_stream_;
  std::string uri_missing_height_;
  std::string uri_without_thumb_;
};

TEST_F(PopplerPageGetThumbnailSizeTest_2440, ThumbStreamWithWidthHeight_ReturnsTrueAndSetsSize_2440)
{
  PopplerDocument *doc = OpenDocFromUriOrFail(uri_with_wh_);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  int w = -1;
  int h = -1;
  gboolean ok = poppler_page_get_thumbnail_size(page, &w, &h);

  EXPECT_TRUE(ok);
  EXPECT_EQ(w, 16);
  EXPECT_EQ(h, 8);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetThumbnailSizeTest_2440, ThumbStreamWithShortKeys_ReturnsTrueAndSetsSize_2440)
{
  PopplerDocument *doc = OpenDocFromUriOrFail(uri_with_short_);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  int w = -1;
  int h = -1;
  gboolean ok = poppler_page_get_thumbnail_size(page, &w, &h);

  EXPECT_TRUE(ok);
  EXPECT_EQ(w, 21);
  EXPECT_EQ(h, 34);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetThumbnailSizeTest_2440, ThumbObjectNotAStream_ReturnsFalseAndLeavesOutputsUnchanged_2440)
{
  PopplerDocument *doc = OpenDocFromUriOrFail(uri_thumb_not_stream_);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  int w = 1234;
  int h = 5678;
  gboolean ok = poppler_page_get_thumbnail_size(page, &w, &h);

  EXPECT_FALSE(ok);
  // Observable behavior: function returns FALSE. It returns early when thumb isn't a stream,
  // so outputs should remain as passed (best-effort expectation).
  EXPECT_EQ(w, 1234);
  EXPECT_EQ(h, 5678);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetThumbnailSizeTest_2440, ThumbStreamMissingHeight_ReturnsFalse_2440)
{
  PopplerDocument *doc = OpenDocFromUriOrFail(uri_missing_height_);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  int w = -1;
  int h = -1;
  gboolean ok = poppler_page_get_thumbnail_size(page, &w, &h);

  EXPECT_FALSE(ok);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetThumbnailSizeTest_2440, PageWithoutThumb_ReturnsFalse_2440)
{
  PopplerDocument *doc = OpenDocFromUriOrFail(uri_without_thumb_);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  int w = -1;
  int h = -1;
  gboolean ok = poppler_page_get_thumbnail_size(page, &w, &h);

  EXPECT_FALSE(ok);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetThumbnailSizeTest_2440, NullPage_ReturnsFalseAndEmitsCritical_2440)
{
  glib_criticals_->reset();

  int w = -1;
  int h = -1;
  gboolean ok = poppler_page_get_thumbnail_size(nullptr, &w, &h);

  EXPECT_FALSE(ok);
  EXPECT_GE(glib_criticals_->count(), 1);
}

TEST_F(PopplerPageGetThumbnailSizeTest_2440, NullWidth_ReturnsFalseAndEmitsCritical_2440)
{
  PopplerDocument *doc = OpenDocFromUriOrFail(uri_with_wh_);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  glib_criticals_->reset();

  int h = -1;
  gboolean ok = poppler_page_get_thumbnail_size(page, nullptr, &h);

  EXPECT_FALSE(ok);
  EXPECT_GE(glib_criticals_->count(), 1);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetThumbnailSizeTest_2440, NullHeight_ReturnsFalseAndEmitsCritical_2440)
{
  PopplerDocument *doc = OpenDocFromUriOrFail(uri_with_wh_);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  glib_criticals_->reset();

  int w = -1;
  gboolean ok = poppler_page_get_thumbnail_size(page, &w, nullptr);

  EXPECT_FALSE(ok);
  EXPECT_GE(glib_criticals_->count(), 1);

  g_object_unref(page);
  g_object_unref(doc);
}

} // namespace