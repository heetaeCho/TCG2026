// File: poppler_document_get_creation_date_test_2184.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <optional>
#include <string>
#include <vector>

namespace {

class PopplerDocumentCreationDateTest_2184 : public ::testing::Test {
protected:
  void TearDown() override
  {
    if (document_) {
      g_object_unref(document_);
      document_ = nullptr;
    }
    if (!tmp_path_.empty()) {
      std::remove(tmp_path_.c_str());
      tmp_path_.clear();
    }
  }

  static std::string BuildMinimalPdfWithOptionalCreationDate(const std::optional<std::string> &creation_date_value)
  {
    // Build a minimal, valid PDF with 1 page.
    // If creation_date_value has a value, embed it into the Info dictionary as /CreationDate (<value>).
    // If creation_date_value is nullopt, omit the /Info entry entirely.
    //
    // NOTE: This helper only constructs a syntactically valid PDF file, without relying on Poppler internals.

    std::vector<std::string> objs;

    // 1: Catalog
    objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
    // 2: Pages
    objs.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
    // 3: Page
    objs.push_back(
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>\n"
        "endobj\n");
    // 4: Empty contents stream
    objs.push_back(
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n");

    bool include_info = creation_date_value.has_value();
    if (include_info) {
      // 5: Info dictionary
      // Put the raw value inside parentheses as requested by PDF syntax.
      std::string info =
          "5 0 obj\n"
          "<< /Producer (PopplerCreationDateTest) /CreationDate (" +
          *creation_date_value +
          ") >>\n"
          "endobj\n";
      objs.push_back(info);
    }

    std::string pdf;
    pdf.reserve(2048);
    pdf += "%PDF-1.4\n";

    // Track xref offsets for objects 1..N (object 0 is special/free).
    std::vector<long> offsets;
    offsets.reserve(objs.size() + 1);
    offsets.push_back(0); // obj 0 placeholder

    for (const auto &obj : objs) {
      offsets.push_back(static_cast<long>(pdf.size()));
      pdf += obj;
    }

    long xref_pos = static_cast<long>(pdf.size());

    // XRef table
    // Size is highest object number + 1 (including object 0).
    int size = static_cast<int>(objs.size()) + 1;
    pdf += "xref\n";
    pdf += "0 " + std::to_string(size) + "\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i < size; ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      pdf += buf;
    }

    // Trailer
    pdf += "trailer\n<< /Size " + std::to_string(size) + " /Root 1 0 R";
    if (include_info) {
      // Info object is #5 when included.
      pdf += " /Info 5 0 R";
    }
    pdf += " >>\n";

    pdf += "startxref\n";
    pdf += std::to_string(xref_pos) + "\n";
    pdf += "%%EOF\n";

    return pdf;
  }

  void WriteTempPdfOrFail(const std::string &pdf_bytes)
  {
    // Create a temp file path
    gchar *path = nullptr;
    gint fd = g_file_open_tmp("poppler_creation_date_2184_XXXXXX.pdf", &path, nullptr);
    ASSERT_NE(fd, -1);
    ASSERT_NE(path, nullptr);

    // Close the fd; we'll write via g_file_set_contents for simplicity.
#ifdef G_OS_WIN32
    _close(fd);
#else
    close(fd);
#endif

    tmp_path_ = path;
    g_free(path);

    GError *error = nullptr;
    gboolean ok = g_file_set_contents(tmp_path_.c_str(), pdf_bytes.data(),
                                      static_cast<gssize>(pdf_bytes.size()), &error);
    ASSERT_TRUE(ok);
    ASSERT_EQ(error, nullptr);
  }

  void OpenDocumentOrFail()
  {
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmp_path_.c_str(), nullptr, &error);
    ASSERT_NE(uri, nullptr);
    ASSERT_EQ(error, nullptr);

    document_ = poppler_document_new_from_file(uri, /*password*/ nullptr, &error);
    g_free(uri);

    ASSERT_NE(document_, nullptr);
    ASSERT_EQ(error, nullptr);
  }

  static time_t UnixUtc(int year, int month, int day, int hour, int minute, int second)
  {
    GDateTime *dt = g_date_time_new_utc(year, month, day, hour, minute, second);
    EXPECT_NE(dt, nullptr);
    gint64 unix_seconds = g_date_time_to_unix(dt);
    g_date_time_unref(dt);
    return static_cast<time_t>(unix_seconds);
  }

  PopplerDocument *document_ = nullptr;
  std::string tmp_path_;
};

TEST_F(PopplerDocumentCreationDateTest_2184, ReturnsMinusOneWhenDocumentIsNull_2184)
{
  time_t result = poppler_document_get_creation_date(nullptr);
  EXPECT_EQ(result, static_cast<time_t>(-1));
}

TEST_F(PopplerDocumentCreationDateTest_2184, ReturnsMinusOneWhenCreationDateMissing_2184)
{
  const std::string pdf = BuildMinimalPdfWithOptionalCreationDate(std::nullopt);
  WriteTempPdfOrFail(pdf);
  OpenDocumentOrFail();

  time_t result = poppler_document_get_creation_date(document_);
  EXPECT_EQ(result, static_cast<time_t>(-1));
}

TEST_F(PopplerDocumentCreationDateTest_2184, ReturnsParsedTimeWhenCreationDatePresentUtcZ_2184)
{
  // Use a UTC "Z" PDF date to avoid local-time ambiguities.
  // PDF date string format example: D:YYYYMMDDHHmmSSZ
  const std::string pdf = BuildMinimalPdfWithOptionalCreationDate(std::string("D:20240220123456Z"));
  WriteTempPdfOrFail(pdf);
  OpenDocumentOrFail();

  time_t result = poppler_document_get_creation_date(document_);
  time_t expected = UnixUtc(2024, 2, 20, 12, 34, 56);

  EXPECT_EQ(result, expected);
}

TEST_F(PopplerDocumentCreationDateTest_2184, ReturnsMinusOneWhenCreationDateIsInvalid_2184)
{
  // If conversion fails, the API is expected to return (time_t)-1.
  const std::string pdf = BuildMinimalPdfWithOptionalCreationDate(std::string("D:NOT_A_DATE"));
  WriteTempPdfOrFail(pdf);
  OpenDocumentOrFail();

  time_t result = poppler_document_get_creation_date(document_);
  EXPECT_EQ(result, static_cast<time_t>(-1));
}

TEST_F(PopplerDocumentCreationDateTest_2184, BoundaryAcceptsEpochStartUtcZ_2184)
{
  // Boundary-style check: epoch start.
  const std::string pdf = BuildMinimalPdfWithOptionalCreationDate(std::string("D:19700101000000Z"));
  WriteTempPdfOrFail(pdf);
  OpenDocumentOrFail();

  time_t result = poppler_document_get_creation_date(document_);
  time_t expected = UnixUtc(1970, 1, 1, 0, 0, 0);

  EXPECT_EQ(result, expected);
}

} // namespace