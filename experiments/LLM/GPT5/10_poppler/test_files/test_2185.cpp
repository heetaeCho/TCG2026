// poppler-document-set-creation-date-ut-2185.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cerrno>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <vector>

namespace {

// Builds a valid minimal PDF (1 page, empty content) with a correct xref table.
// This avoids relying on any internal Poppler state while still letting us create
// a real PopplerDocument through the public poppler-glib API.
static std::string BuildMinimalPdf()
{
  // Objects (1..4). We'll compute offsets and generate the xref accordingly.
  const char *header = "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<std::string> objs;
  objs.emplace_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");
  objs.emplace_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");
  objs.emplace_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\n"
      "endobj\n");
  // Empty stream content.
  objs.emplace_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n");

  std::string pdf;
  pdf.reserve(2048);
  pdf.append(header);

  // Track offsets for xref entries. Object 0 is the free entry.
  std::vector<size_t> offsets;
  offsets.resize(5); // 0..4
  offsets[0] = 0;

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = pdf.size();
    pdf.append(objs[i]);
  }

  const size_t xref_offset = pdf.size();
  pdf.append("xref\n");
  pdf.append("0 5\n");

  // Free entry.
  pdf.append("0000000000 65535 f \n");

  // Each object entry: 10-digit byte offset, 5-digit generation, in-use "n".
  for (size_t obj = 1; obj <= 4; ++obj) {
    char line[32];
    // Offsets must fit 10 digits for xref format here; our file is tiny.
    g_snprintf(line, sizeof(line), "%010lu 00000 n \n",
               static_cast<unsigned long>(offsets[obj]));
    pdf.append(line);
  }

  pdf.append("trailer\n");
  pdf.append("<< /Size 5 /Root 1 0 R >>\n");
  pdf.append("startxref\n");
  {
    char buf[64];
    g_snprintf(buf, sizeof(buf), "%lu\n", static_cast<unsigned long>(xref_offset));
    pdf.append(buf);
  }
  pdf.append("%%EOF\n");

  return pdf;
}

static std::string WriteTempPdfAndGetUri()
{
  std::string pdf = BuildMinimalPdf();

  gchar *tmp_path = nullptr;
  int fd = g_file_open_tmp("poppler_creation_date_XXXXXX.pdf", &tmp_path, nullptr);
  if (fd >= 0) {
#ifdef G_OS_WIN32
    _close(fd);
#else
    close(fd);
#endif
  }
  EXPECT_NE(tmp_path, nullptr);

  GError *error = nullptr;
  gboolean ok = g_file_set_contents(tmp_path, pdf.c_str(), static_cast<gssize>(pdf.size()), &error);
  if (!ok) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    g_free(tmp_path);
    ADD_FAILURE() << "Failed to write temp PDF: " << msg;
    return {};
  }

  gchar *uri = g_filename_to_uri(tmp_path, /*hostname=*/nullptr, &error);
  if (!uri) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    g_free(tmp_path);
    ADD_FAILURE() << "Failed to convert path to URI: " << msg;
    return {};
  }

  std::string out(uri);
  g_free(uri);
  g_free(tmp_path);
  return out;
}

class PopplerDocumentSetCreationDateTest_2185 : public ::testing::Test {
protected:
  void SetUp() override
  {
    uri_ = WriteTempPdfAndGetUri();
    ASSERT_FALSE(uri_.empty());

    GError *error = nullptr;
    // password is optional; passing nullptr.
    doc_ = poppler_document_new_from_file(uri_.c_str(), nullptr, &error);
    if (!doc_) {
      std::string msg = error ? error->message : "unknown error";
      if (error) g_error_free(error);
      FAIL() << "poppler_document_new_from_file failed: " << msg;
    }
    if (error) g_error_free(error);
  }

  void TearDown() override
  {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  PopplerDocument *doc_ = nullptr;
  std::string uri_;
};

} // namespace

// Normal operation: setting a valid creation date should be observable via the public getter.
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetValidCreationDateUpdatesGetter_2185)
{
  // 2021-01-01 00:00:00 UTC
  const time_t t = static_cast<time_t>(1609459200);

  poppler_document_set_creation_date(doc_, t);

  const time_t got = poppler_document_get_creation_date(doc_);
  EXPECT_EQ(got, t);
}

// Boundary: epoch time (0) should be settable and observable (not treated as "unset").
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetEpochCreationDateIsObservable_2185)
{
  const time_t t = static_cast<time_t>(0);

  poppler_document_set_creation_date(doc_, t);

  const time_t got = poppler_document_get_creation_date(doc_);
  EXPECT_EQ(got, t);
}

// Boundary: near-2038 value when representable by time_t.
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetNear2038CreationDateWhenRepresentable_2185)
{
  const time_t t = static_cast<time_t>(2147483647); // 2038-01-19T03:14:07Z
  if (t < 0) {
    GTEST_SKIP() << "time_t cannot represent 2147483647 on this platform";
  }

  poppler_document_set_creation_date(doc_, t);

  const time_t got = poppler_document_get_creation_date(doc_);
  EXPECT_EQ(got, t);
}

// Error/exceptional (observable): passing (time_t)-1 should clear/unset the creation date.
// We verify this by setting a date first, then clearing, and observing via the public getter.
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetMinusOneClearsCreationDate_2185)
{
  const time_t t = static_cast<time_t>(1609459200);

  poppler_document_set_creation_date(doc_, t);
  EXPECT_EQ(poppler_document_get_creation_date(doc_), t);

  poppler_document_set_creation_date(doc_, static_cast<time_t>(-1));

  const time_t got = poppler_document_get_creation_date(doc_);
  EXPECT_EQ(got, static_cast<time_t>(-1));
}

// Error/exceptional: g_return_if_fail should guard against nullptr document without crashing.
TEST(PopplerDocumentSetCreationDateStandaloneTest_2185, NullDocumentDoesNotCrash_2185)
{
  // Should simply return due to g_return_if_fail() in the implementation.
  poppler_document_set_creation_date(nullptr, static_cast<time_t>(0));
  SUCCEED();
}