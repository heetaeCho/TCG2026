// File: poppler-document-get-print-page-ranges-ut-2200.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

// -----------------------
// Test helpers
// -----------------------

namespace {

class ScopedGLogSilencer {
public:
  ScopedGLogSilencer()
  {
    // g_return_val_if_fail() logs CRITICAL on the default (nullptr) domain.
    default_handler_id_ = g_log_set_handler(nullptr,
                                           static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING),
                                           &ScopedGLogSilencer::Handler, nullptr);
    // Also silence Poppler domain just in case a build uses it.
    poppler_handler_id_ = g_log_set_handler("Poppler",
                                           static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING),
                                           &ScopedGLogSilencer::Handler, nullptr);
  }

  ~ScopedGLogSilencer()
  {
    if (default_handler_id_ != 0) {
      g_log_remove_handler(nullptr, default_handler_id_);
    }
    if (poppler_handler_id_ != 0) {
      g_log_remove_handler("Poppler", poppler_handler_id_);
    }
  }

  ScopedGLogSilencer(const ScopedGLogSilencer &) = delete;
  ScopedGLogSilencer &operator=(const ScopedGLogSilencer &) = delete;

private:
  static void Handler(const gchar *, GLogLevelFlags, const gchar *, gpointer) { /* swallow */ }

  guint default_handler_id_{0};
  guint poppler_handler_id_{0};
};

static std::string BuildPdfWithPrintPageRange(const std::vector<std::pair<int, int>> &ranges)
{
  // Build a minimal, valid PDF with a Catalog ViewerPreferences dictionary containing /PrintPageRange.
  // This is test data construction (not re-implementing Poppler logic).
  std::string pdf;
  pdf.reserve(2048);

  auto append = [&](const std::string &s) { pdf += s; };

  append("%PDF-1.5\n");
  append("%\xE2\xE3\xCF\xD3\n"); // binary marker

  // Track object offsets for xref.
  std::vector<size_t> obj_offs; // index 1..N, obj_offs[0] unused
  obj_offs.resize(6, 0);        // we will create objects 1..5

  auto begin_obj = [&](int obj_num) {
    obj_offs[obj_num] = pdf.size();
    append(std::to_string(obj_num));
    append(" 0 obj\n");
  };
  auto end_obj = [&]() { append("endobj\n"); };

  // 1 0 obj: Catalog
  begin_obj(1);
  append("<< /Type /Catalog /Pages 2 0 R /ViewerPreferences 5 0 R >>\n");
  end_obj();

  // 2 0 obj: Pages
  begin_obj(2);
  append("<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n");
  end_obj();

  // 3 0 obj: Page
  begin_obj(3);
  append("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Resources << >> /Contents 4 0 R >>\n");
  end_obj();

  // 4 0 obj: Contents stream (empty content is fine for parsing)
  begin_obj(4);
  const std::string stream_data = " ";
  append("<< /Length " + std::to_string(stream_data.size()) + " >>\n");
  append("stream\n");
  append(stream_data);
  append("\nendstream\n");
  end_obj();

  // 5 0 obj: ViewerPreferences with PrintPageRange
  begin_obj(5);
  append("<< /PrintPageRange [ ");
  for (const auto &r : ranges) {
    append("[ ");
    append(std::to_string(r.first));
    append(" ");
    append(std::to_string(r.second));
    append(" ] ");
  }
  append("] >>\n");
  end_obj();

  // xref
  const size_t xref_off = pdf.size();
  append("xref\n");
  append("0 6\n");
  append("0000000000 65535 f \n");
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    // 10-digit, zero-padded byte offset
    std::snprintf(buf, sizeof(buf), "%010u 00000 n \n", static_cast<unsigned>(obj_offs[i]));
    append(buf);
  }

  // trailer
  append("trailer\n");
  append("<< /Size 6 /Root 1 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xref_off));
  append("\n%%EOF\n");

  return pdf;
}

static PopplerDocument *LoadDocFromPdfDataOrFail(const std::string &pdf)
{
  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = "poppler_document_new_from_data failed";
    if (error && error->message) {
      msg += std::string(": ") + error->message;
    }
    if (error) {
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) {
    // Some builds may set a non-fatal warning error; free it to avoid leaks.
    g_error_free(error);
  }
  return doc;
}

} // namespace

// -----------------------
// Tests (TEST_ID 2200)
// -----------------------

class PopplerDocumentPrintPageRangesTest_2200 : public ::testing::Test {
protected:
  void TearDown() override
  {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  PopplerDocument *doc_{nullptr};
};

TEST_F(PopplerDocumentPrintPageRangesTest_2200, ReturnsNullWhenNRangesIsNull_2200)
{
  ScopedGLogSilencer silence;

  // Using a valid document pointer is not required to test the n_ranges precondition,
  // but we pass nullptr to keep the call simple.
  PopplerPageRange *ranges = poppler_document_get_print_page_ranges(nullptr, nullptr);
  EXPECT_EQ(ranges, nullptr);
}

TEST_F(PopplerDocumentPrintPageRangesTest_2200, ReturnsNullAndZeroRangesWhenDocumentIsNull_2200)
{
  ScopedGLogSilencer silence;

  int n_ranges = 123;
  PopplerPageRange *ranges = poppler_document_get_print_page_ranges(nullptr, &n_ranges);

  EXPECT_EQ(ranges, nullptr);
  EXPECT_EQ(n_ranges, 0);
}

TEST_F(PopplerDocumentPrintPageRangesTest_2200, ReturnsRangesFromViewerPreferences_2200)
{
  const std::vector<std::pair<int, int>> expected = {{1, 2}, {4, 6}, {9, 9}};
  const std::string pdf = BuildPdfWithPrintPageRange(expected);

  doc_ = LoadDocFromPdfDataOrFail(pdf);
  ASSERT_NE(doc_, nullptr);

  int n_ranges = -1;
  PopplerPageRange *ranges = poppler_document_get_print_page_ranges(doc_, &n_ranges);

  ASSERT_NE(ranges, nullptr);
  ASSERT_EQ(n_ranges, static_cast<int>(expected.size()));

  for (int i = 0; i < n_ranges; ++i) {
    EXPECT_EQ(ranges[i].start_page, expected[static_cast<size_t>(i)].first) << "index=" << i;
    EXPECT_EQ(ranges[i].end_page, expected[static_cast<size_t>(i)].second) << "index=" << i;
  }

  g_free(ranges);
}

TEST_F(PopplerDocumentPrintPageRangesTest_2200, HandlesSingleRangeBoundary_2200)
{
  const std::vector<std::pair<int, int>> expected = {{0, 0}};
  const std::string pdf = BuildPdfWithPrintPageRange(expected);

  doc_ = LoadDocFromPdfDataOrFail(pdf);
  ASSERT_NE(doc_, nullptr);

  int n_ranges = 0;
  PopplerPageRange *ranges = poppler_document_get_print_page_ranges(doc_, &n_ranges);

  ASSERT_NE(ranges, nullptr);
  ASSERT_EQ(n_ranges, 1);
  EXPECT_EQ(ranges[0].start_page, 0);
  EXPECT_EQ(ranges[0].end_page, 0);

  g_free(ranges);
}

TEST_F(PopplerDocumentPrintPageRangesTest_2200, StableOutputAcrossMultipleCalls_2200)
{
  const std::vector<std::pair<int, int>> expected = {{2, 3}, {7, 8}};
  const std::string pdf = BuildPdfWithPrintPageRange(expected);

  doc_ = LoadDocFromPdfDataOrFail(pdf);
  ASSERT_NE(doc_, nullptr);

  int n1 = -1;
  PopplerPageRange *r1 = poppler_document_get_print_page_ranges(doc_, &n1);
  ASSERT_NE(r1, nullptr);
  ASSERT_EQ(n1, static_cast<int>(expected.size()));

  int n2 = -1;
  PopplerPageRange *r2 = poppler_document_get_print_page_ranges(doc_, &n2);
  ASSERT_NE(r2, nullptr);
  ASSERT_EQ(n2, static_cast<int>(expected.size()));

  for (int i = 0; i < n1; ++i) {
    EXPECT_EQ(r1[i].start_page, r2[i].start_page) << "index=" << i;
    EXPECT_EQ(r1[i].end_page, r2[i].end_page) << "index=" << i;
  }

  g_free(r1);
  g_free(r2);
}