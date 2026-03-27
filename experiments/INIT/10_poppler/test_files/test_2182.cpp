// TEST_ID: 2182
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Minimal PDF builder (enough for Poppler to open) with an Info dictionary that may include /Producer.
static std::string BuildMinimalPdfWithInfoProducer(const std::optional<std::string> &producer_entry /* e.g. "/Producer (X)" */)
{
  // Objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4: Contents (empty stream)
  // 5: Info
  //
  // Trailer: /Root 1 0 R /Info 5 0 R
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.reserve(6);
  offsets.push_back(0); // object 0 (unused)

  auto mark_obj_offset = [&](int /*objnum*/) { offsets.push_back(static_cast<long>(pdf.tellp())); };

  mark_obj_offset(1);
  pdf << "1 0 obj\n"
      << "<< /Type /Catalog /Pages 2 0 R >>\n"
      << "endobj\n";

  mark_obj_offset(2);
  pdf << "2 0 obj\n"
      << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      << "endobj\n";

  mark_obj_offset(3);
  pdf << "3 0 obj\n"
      << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
      << "endobj\n";

  mark_obj_offset(4);
  pdf << "4 0 obj\n"
      << "<< /Length 0 >>\n"
      << "stream\n"
      << "\n"
      << "endstream\n"
      << "endobj\n";

  mark_obj_offset(5);
  pdf << "5 0 obj\n"
      << "<< ";
  if (producer_entry.has_value() && !producer_entry->empty()) {
    pdf << *producer_entry << " ";
  }
  pdf << ">>\n"
      << "endobj\n";

  const long xref_start = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 6\n";
  pdf << "0000000000 65535 f \n";
  // offsets[1..5] exist in the same order we pushed.
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[static_cast<size_t>(i)]);
    pdf << buf;
  }

  pdf << "trailer\n"
      << "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n"
      << "startxref\n"
      << xref_start << "\n"
      << "%%EOF\n";

  return pdf.str();
}

static std::string WriteTempFile(const std::string &bytes)
{
  // Create a unique temp file.
  gchar *path = nullptr;
  int fd = g_file_open_tmp("poppler-get-producer-XXXXXX.pdf", &path, nullptr);
  if (fd < 0 || path == nullptr) {
    if (path) {
      g_free(path);
    }
    return {};
  }

  // Write bytes to fd.
  FILE *f = fdopen(fd, "wb");
  if (!f) {
    close(fd);
    g_free(path);
    return {};
  }
  const size_t written = fwrite(bytes.data(), 1, bytes.size(), f);
  fclose(f); // closes fd too

  std::string out = path;
  g_free(path);

  if (written != bytes.size()) {
    // Best-effort cleanup.
    std::remove(out.c_str());
    return {};
  }
  return out;
}

static std::string FilePathToUri(const std::string &path)
{
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  if (!uri) {
    return {};
  }
  std::string out = uri;
  g_free(uri);
  return out;
}

struct TempPath {
  std::string path;
  ~TempPath()
  {
    if (!path.empty()) {
      std::remove(path.c_str());
    }
  }
};

} // namespace

class PopplerDocumentGetProducerTest_2182 : public ::testing::Test {
protected:
  void TearDown() override
  {
    // Ensure GLib doesn't treat criticals as fatal after tests that adjust it.
    // (No-op if unchanged.)
  }
};

TEST_F(PopplerDocumentGetProducerTest_2182, ReturnsProducerStringForValidDocument_2182)
{
  const std::string pdf = BuildMinimalPdfWithInfoProducer(std::string("/Producer (TestProducer-2182)"));
  TempPath tmp{WriteTempFile(pdf)};
  ASSERT_FALSE(tmp.path.empty());

  const std::string uri = FilePathToUri(tmp.path);
  ASSERT_FALSE(uri.empty());

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  gchar *producer = poppler_document_get_producer(doc);
  ASSERT_NE(producer, nullptr);
  EXPECT_STREQ(producer, "TestProducer-2182");

  g_free(producer);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, ConvertsUtf16BeProducerToUtf8_2182)
{
  // "테스트" (Korean) as UTF-16BE with BOM: FE FF D1 4C C2 A4 D2 B8
  const std::string pdf =
      BuildMinimalPdfWithInfoProducer(std::string("/Producer <FEFFD14CC2A4D2B8>"));
  TempPath tmp{WriteTempFile(pdf)};
  ASSERT_FALSE(tmp.path.empty());

  const std::string uri = FilePathToUri(tmp.path);
  ASSERT_FALSE(uri.empty());

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  gchar *producer = poppler_document_get_producer(doc);
  ASSERT_NE(producer, nullptr);
  EXPECT_STREQ(producer, u8"테스트");

  g_free(producer);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, ReturnsNullOrEmptyWhenProducerMissing_2182)
{
  const std::string pdf = BuildMinimalPdfWithInfoProducer(std::nullopt);
  TempPath tmp{WriteTempFile(pdf)};
  ASSERT_FALSE(tmp.path.empty());

  const std::string uri = FilePathToUri(tmp.path);
  ASSERT_FALSE(uri.empty());

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  gchar *producer = poppler_document_get_producer(doc);

  // Observable behavior varies depending on Poppler build/version:
  // Some may return NULL for missing entries; others may return an empty string.
  EXPECT_TRUE(producer == nullptr || producer[0] == '\0');

  if (producer) {
    g_free(producer);
  }
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, NullDocumentReturnsNull_2182)
{
  // Avoid GLib treating CRITICAL as fatal in test environments.
  const GLogLevelFlags old_fatal = g_log_set_always_fatal((GLogLevelFlags)0);

  EXPECT_EQ(poppler_document_get_producer(nullptr), nullptr);

  g_log_set_always_fatal(old_fatal);
}