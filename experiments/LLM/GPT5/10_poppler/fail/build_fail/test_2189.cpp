// poppler_document_set_modification_date_test_2189.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

// Builds a tiny valid single-page PDF entirely in-memory, with a correct xref table.
// This is test scaffolding (not related to Poppler internals).
std::string BuildMinimalPdfOnePage()
{
  // PDF header + 4 indirect objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4: Contents (empty stream)
  const std::string header = "%PDF-1.4\n";

  std::vector<std::string> objs;
  objs.emplace_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  objs.emplace_back(
      "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
  objs.emplace_back(
      "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] "
      "/Contents 4 0 R >>\nendobj\n");
  objs.emplace_back(
      "4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n");

  // Compute byte offsets for xref (object numbers start at 1).
  std::vector<size_t> offsets(objs.size() + 1, 0); // offsets[0] unused for obj0
  std::string body;
  body.reserve(1024);

  size_t cursor = header.size();
  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = cursor;
    body += objs[i];
    cursor += objs[i].size();
  }

  // Build xref.
  std::string xref;
  xref += "xref\n";
  xref += "0 5\n";
  xref += "0000000000 65535 f \n";
  for (int obj = 1; obj <= 4; ++obj) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010zu 00000 n \n", offsets[obj]);
    xref += line;
  }

  // Trailer + startxref.
  std::string trailer;
  trailer += "trailer\n";
  trailer += "<< /Size 5 /Root 1 0 R >>\n";

  const size_t startxref = header.size() + body.size();
  char sx[64];
  std::snprintf(sx, sizeof(sx), "startxref\n%zu\n%%%%EOF\n", startxref);

  std::string pdf;
  pdf.reserve(header.size() + body.size() + xref.size() + trailer.size() + 64);
  pdf += header;
  pdf += body;
  pdf += xref;
  pdf += trailer;
  pdf += sx;

  return pdf;
}

struct GErrorDeleter
{
  void operator()(GError *e) const
  {
    if (e)
      g_error_free(e);
  }
};

class PopplerSetModificationDateTest_2189 : public ::testing::Test
{
protected:
  static PopplerDocument *NewDocFromMinimalPdf()
  {
    const std::string pdf = BuildMinimalPdfOnePage();
    std::unique_ptr<GError, GErrorDeleter> error;

    GError *raw_err = nullptr;
    PopplerDocument *doc =
        poppler_document_new_from_data(pdf.data(),
                                       static_cast<int>(pdf.size()),
                                       /*password=*/nullptr,
                                       &raw_err);
    error.reset(raw_err);

    EXPECT_NE(doc, nullptr);
    EXPECT_EQ(error.get(), nullptr);
    return doc;
  }
};

TEST_F(PopplerSetModificationDateTest_2189, SetThenGetMatchesInput_2189)
{
  PopplerDocument *doc = NewDocFromMinimalPdf();
  ASSERT_NE(doc, nullptr);

  const time_t t = static_cast<time_t>(1609459200); // 2021-01-01 00:00:00 UTC
  poppler_document_set_modification_date(doc, t);

  const time_t got = poppler_document_get_modification_date(doc);
  EXPECT_EQ(got, t);

  g_object_unref(doc);
}

TEST_F(PopplerSetModificationDateTest_2189, SettingMinusOneClearsToMinusOne_2189)
{
  PopplerDocument *doc = NewDocFromMinimalPdf();
  ASSERT_NE(doc, nullptr);

  const time_t t = static_cast<time_t>(1609459200);
  poppler_document_set_modification_date(doc, t);
  ASSERT_EQ(poppler_document_get_modification_date(doc), t);

  poppler_document_set_modification_date(doc, static_cast<time_t>(-1));
  const time_t got = poppler_document_get_modification_date(doc);
  EXPECT_EQ(got, static_cast<time_t>(-1));

  g_object_unref(doc);
}

TEST_F(PopplerSetModificationDateTest_2189, BoundaryEpochZeroIsAccepted_2189)
{
  PopplerDocument *doc = NewDocFromMinimalPdf();
  ASSERT_NE(doc, nullptr);

  const time_t t = static_cast<time_t>(0);
  poppler_document_set_modification_date(doc, t);

  const time_t got = poppler_document_get_modification_date(doc);
  EXPECT_EQ(got, t);

  g_object_unref(doc);
}

TEST_F(PopplerSetModificationDateTest_2189, LastCallWinsWhenSetMultipleTimes_2189)
{
  PopplerDocument *doc = NewDocFromMinimalPdf();
  ASSERT_NE(doc, nullptr);

  const time_t t1 = static_cast<time_t>(1609459200);
  const time_t t2 = static_cast<time_t>(1640995200); // 2022-01-01 00:00:00 UTC

  poppler_document_set_modification_date(doc, t1);
  ASSERT_EQ(poppler_document_get_modification_date(doc), t1);

  poppler_document_set_modification_date(doc, t2);
  EXPECT_EQ(poppler_document_get_modification_date(doc), t2);

  g_object_unref(doc);
}

TEST_F(PopplerSetModificationDateTest_2189, NullDocumentDoesNotCrash_2189)
{
  // g_return_if_fail() should return early; this verifies the function is robust
  // against invalid input without relying on internal state.
  EXPECT_NO_FATAL_FAILURE(
      poppler_document_set_modification_date(nullptr, static_cast<time_t>(0)));
}

} // namespace