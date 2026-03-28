// File: poppler-document-get-creation-date-time-test_2186.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace {

class PopplerDocumentGetCreationDateTimeTest_2186 : public ::testing::Test {
protected:
  static std::string WriteTempPdf(const std::string &pdf_bytes) {
    // Create a unique temp file path.
    // Using g_mkstemp to avoid races.
    std::string templ = std::string(g_get_tmp_dir()) + G_DIR_SEPARATOR_S + "poppler_ut_XXXXXX.pdf";
    std::vector<char> pathbuf(templ.begin(), templ.end());
    pathbuf.push_back('\0');

    int fd = g_mkstemp(pathbuf.data());
    EXPECT_NE(fd, -1);

    // Write bytes.
    ssize_t total = 0;
    const char *data = pdf_bytes.data();
    ssize_t len = static_cast<ssize_t>(pdf_bytes.size());
    while (total < len) {
      ssize_t w = write(fd, data + total, len - total);
      EXPECT_GT(w, 0);
      total += w;
    }
    close(fd);

    return std::string(pathbuf.data());
  }

  static std::string FileUriFromPath(const std::string &path) {
    GError *error = nullptr;
    char *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
    EXPECT_EQ(error, nullptr);
    EXPECT_NE(uri, nullptr);
    std::string out(uri);
    g_free(uri);
    return out;
  }

  static PopplerDocument *LoadDocumentFromFileUri(const std::string &file_uri) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(file_uri.c_str(), /*password=*/nullptr, &error);
    EXPECT_EQ(error, nullptr);
    EXPECT_NE(doc, nullptr);
    return doc;
  }

  static std::string BuildMinimalPdfWithOptionalCreationDate(const char *creation_date_pdf_literal_or_null) {
    // Build a minimal, valid PDF with an Info dictionary.
    // If creation_date_pdf_literal_or_null == nullptr, omit /CreationDate entry.
    //
    // The PDF is constructed with correct xref offsets.
    auto append_obj = [](std::string &out, std::vector<size_t> &offsets, int obj_num,
                         const std::string &body) {
      offsets[obj_num] = out.size();
      out += std::to_string(obj_num) + " 0 obj\n";
      out += body;
      out += "\nendobj\n";
    };

    std::string pdf;
    pdf.reserve(1024);

    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment

    // We'll create 4 objects:
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Info
    const int kNumObjects = 4;
    std::vector<size_t> offsets(kNumObjects + 1, 0); // 1-based

    append_obj(pdf, offsets, 1, "<< /Type /Catalog /Pages 2 0 R >>");
    append_obj(pdf, offsets, 2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    append_obj(pdf, offsets, 3,
               "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>");

    std::string info_dict = "<< ";
    if (creation_date_pdf_literal_or_null) {
      info_dict += "/CreationDate (";
      info_dict += creation_date_pdf_literal_or_null;
      info_dict += ") ";
    }
    info_dict += ">>";
    append_obj(pdf, offsets, 4, info_dict);

    // xref
    const size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 " + std::to_string(kNumObjects + 1) + "\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= kNumObjects; ++i) {
      char line[32];
      std::snprintf(line, sizeof(line), "%010lu 00000 n \n", static_cast<unsigned long>(offsets[i]));
      pdf += line;
    }

    // trailer
    pdf += "trailer\n";
    pdf += "<< /Size " + std::to_string(kNumObjects + 1) + " /Root 1 0 R /Info 4 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset) + "\n";
    pdf += "%%EOF\n";

    return pdf;
  }
};

static void FreeGDateTime(GDateTime *dt) {
  if (dt) {
    g_date_time_unref(dt);
  }
}

TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, NullDocumentReturnsNull_2186) {
  // Observable behavior: returns nullptr when the instance check fails.
  GDateTime *dt = poppler_document_get_creation_date_time(nullptr);
  EXPECT_EQ(dt, nullptr);
}

TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, MissingCreationDateReturnsNull_2186) {
  // Create a PDF whose Info dictionary has no /CreationDate entry.
  const std::string pdf = BuildMinimalPdfWithOptionalCreationDate(nullptr);
  const std::string path = WriteTempPdf(pdf);
  const std::string uri = FileUriFromPath(path);

  PopplerDocument *doc = LoadDocumentFromFileUri(uri);

  GDateTime *dt = poppler_document_get_creation_date_time(doc);
  EXPECT_EQ(dt, nullptr);

  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, ValidCreationDateZuluParsesToExpectedUnix_2186) {
  // PDF date: D:YYYYMMDDHHmmSSZ
  const char *creation = "D:20200102123456Z";
  const std::string pdf = BuildMinimalPdfWithOptionalCreationDate(creation);
  const std::string path = WriteTempPdf(pdf);
  const std::string uri = FileUriFromPath(path);

  PopplerDocument *doc = LoadDocumentFromFileUri(uri);

  std::unique_ptr<GDateTime, decltype(&FreeGDateTime)> dt(
      poppler_document_get_creation_date_time(doc), &FreeGDateTime);
  ASSERT_NE(dt.get(), nullptr);

  // Build the expected time in UTC and compare unix seconds.
  GTimeZone *utc = g_time_zone_new_utc();
  GDateTime *expected = g_date_time_new(utc, 2020, 1, 2, 12, 34, 56.0);
  g_time_zone_unref(utc);
  ASSERT_NE(expected, nullptr);

  gint64 got_unix = g_date_time_to_unix(dt.get());
  gint64 exp_unix = g_date_time_to_unix(expected);

  EXPECT_EQ(got_unix, exp_unix);

  // Also check it is effectively UTC (offset 0) for a Zulu timestamp.
  EXPECT_EQ(g_date_time_get_utc_offset(dt.get()), 0);

  g_date_time_unref(expected);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, ValidCreationDateWithOffsetHasExpectedUtcOffset_2186) {
  // Boundary-ish: explicit timezone offset (+09'00').
  // PDF date format commonly supports: D:YYYYMMDDHHmmSS+HH'mm'
  const char *creation = "D:20200102123456+09'00'";
  const std::string pdf = BuildMinimalPdfWithOptionalCreationDate(creation);
  const std::string path = WriteTempPdf(pdf);
  const std::string uri = FileUriFromPath(path);

  PopplerDocument *doc = LoadDocumentFromFileUri(uri);

  std::unique_ptr<GDateTime, decltype(&FreeGDateTime)> dt(
      poppler_document_get_creation_date_time(doc), &FreeGDateTime);
  ASSERT_NE(dt.get(), nullptr);

  // Expected UTC offset is +9 hours in seconds.
  const gint32 expected_offset = 9 * 60 * 60;
  EXPECT_EQ(g_date_time_get_utc_offset(dt.get()), expected_offset);

  // Sanity-check unix timestamp against a known equivalent:
  // 2020-01-02 12:34:56 +0900 == 2020-01-02 03:34:56Z
  GTimeZone *utc = g_time_zone_new_utc();
  GDateTime *expected_utc = g_date_time_new(utc, 2020, 1, 2, 3, 34, 56.0);
  g_time_zone_unref(utc);
  ASSERT_NE(expected_utc, nullptr);

  EXPECT_EQ(g_date_time_to_unix(dt.get()), g_date_time_to_unix(expected_utc));

  g_date_time_unref(expected_utc);
  g_object_unref(doc);
  g_remove(path.c_str());
}

} // namespace