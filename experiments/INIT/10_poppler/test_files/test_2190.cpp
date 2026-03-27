// poppler-document-get-modification-date-time-test.cc
//
// Unit tests for:
//   GDateTime *poppler_document_get_modification_date_time(PopplerDocument *document)
//
// Constraints respected:
// - Treat implementation as a black box
// - Only use public/observable behavior (return values, GLib type checks)
// - No access to private/internal state
// - Cover normal, boundary, and observable error cases

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h> // Poppler GLib API (PopplerDocument, poppler_document_new_from_data, etc.)

#include <string>
#include <utility>

namespace {

class ScopedGLogCriticalSilencer_2190 {
public:
  ScopedGLogCriticalSilencer_2190() {
    prev_handler_ = g_log_set_handler(nullptr,
                                      static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                      &ScopedGLogCriticalSilencer_2190::Handler,
                                      nullptr);
  }

  ~ScopedGLogCriticalSilencer_2190() { g_log_remove_handler(nullptr, prev_handler_); }

  ScopedGLogCriticalSilencer_2190(const ScopedGLogCriticalSilencer_2190 &) = delete;
  ScopedGLogCriticalSilencer_2190 &operator=(const ScopedGLogCriticalSilencer_2190 &) = delete;

private:
  static void Handler(const gchar *, GLogLevelFlags, const gchar *, gpointer) {
    // Intentionally ignore CRITICAL logs (e.g., from g_return_val_if_fail).
  }

  guint prev_handler_ = 0;
};

static std::string MakeMinimalPdfWithInfoObject_2190(const std::string &info_object_body) {
  // A tiny, valid PDF with an /Info entry (object 5 0 obj).
  //
  // We keep offsets and xref coherent by generating a fixed-layout string with
  // deterministic object ordering. Poppler should accept this minimal structure.
  //
  // Objects:
  // 1 0: Catalog
  // 2 0: Pages
  // 3 0: Page
  // 4 0: Contents (empty stream)
  // 5 0: Info (caller-supplied body)
  //
  // Trailer includes /Info 5 0 R so document->doc->getDocInfoModDate() can see it.

  // We'll build incrementally while recording byte offsets.
  std::string pdf;
  pdf.reserve(2048);

  auto append = [&](const std::string &s) { pdf += s; };

  append("%PDF-1.4\n");
  const auto off1 = pdf.size();
  append("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  const auto off2 = pdf.size();
  append("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
  const auto off3 = pdf.size();
  append("3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] /Contents 4 0 R >>\nendobj\n");
  const auto off4 = pdf.size();
  append("4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n");
  const auto off5 = pdf.size();
  append("5 0 obj\n");
  append(info_object_body);
  append("\nendobj\n");

  const auto xref_off = pdf.size();
  append("xref\n");
  append("0 6\n");
  append("0000000000 65535 f \n");

  auto xref_line = [&](size_t off) {
    char buf[32];
    // PDF xref offsets are 10 digits, zero-padded.
    g_snprintf(buf, sizeof(buf), "%010u 00000 n \n", static_cast<unsigned>(off));
    return std::string(buf);
  };

  append(xref_line(off1));
  append(xref_line(off2));
  append(xref_line(off3));
  append(xref_line(off4));
  append(xref_line(off5));

  append("trailer\n");
  append("<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xref_off));
  append("\n%%EOF\n");

  return pdf;
}

static PopplerDocument *LoadDocumentFromPdfData_2190(const std::string &pdf_data) {
  GError *error = nullptr;
  // poppler_document_new_from_data expects length as int.
  PopplerDocument *doc = poppler_document_new_from_data(pdf_data.c_str(),
                                                        static_cast<int>(pdf_data.size()),
                                                        /*password=*/nullptr,
                                                        &error);
  if (!doc) {
    std::string msg = "Failed to create PopplerDocument from data";
    if (error && error->message) {
      msg += ": ";
      msg += error->message;
    }
    if (error) {
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) {
    g_error_free(error);
  }
  return doc;
}

class PopplerDocumentGetModificationDateTimeTest_2190 : public ::testing::Test {
protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  void LoadWithInfoBody(const std::string &info_body) {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    const std::string pdf = MakeMinimalPdfWithInfoObject_2190(info_body);
    doc_ = LoadDocumentFromPdfData_2190(pdf);
    ASSERT_NE(doc_, nullptr);
  }

  PopplerDocument *doc_ = nullptr;
};

TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, ReturnsNullForNullDocument_2190) {
  // g_return_val_if_fail(POPPLER_IS_DOCUMENT(document), nullptr)
  ScopedGLogCriticalSilencer_2190 silence;
  GDateTime *dt = poppler_document_get_modification_date_time(nullptr);
  EXPECT_EQ(dt, nullptr);
}

TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, ReturnsNullForNonDocumentGObject_2190) {
  // Pass a non-PopplerDocument instance; POPPLER_IS_DOCUMENT should fail.
  ScopedGLogCriticalSilencer_2190 silence;

  GObject *obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(obj, nullptr);

  GDateTime *dt =
      poppler_document_get_modification_date_time(reinterpret_cast<PopplerDocument *>(obj));
  EXPECT_EQ(dt, nullptr);

  g_object_unref(obj);
}

TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, ReturnsNullWhenNoInfoModDatePresent_2190) {
  // If getDocInfoModDate() yields null (no /ModDate), function should return nullptr.
  // Observable expectation: return value is nullptr.
  LoadWithInfoBody("<< /Producer (UnitTest) >>");

  GDateTime *dt = poppler_document_get_modification_date_time(doc_);
  EXPECT_EQ(dt, nullptr);
}

TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, ReturnsDateTimeWhenModDatePresent_2190) {
  // Normal operation: provide an /Info dictionary with a well-formed /ModDate.
  // Use UTC ("Z") to make expectations stable across environments.
  LoadWithInfoBody("<< /Producer (UnitTest) /ModDate (D:20240220123456Z) >>");

  GDateTime *dt = poppler_document_get_modification_date_time(doc_);
  ASSERT_NE(dt, nullptr);

  EXPECT_EQ(g_date_time_get_year(dt), 2024);
  EXPECT_EQ(g_date_time_get_month(dt), 2);
  EXPECT_EQ(g_date_time_get_day_of_month(dt), 20);
  EXPECT_EQ(g_date_time_get_hour(dt), 12);
  EXPECT_EQ(g_date_time_get_minute(dt), 34);
  EXPECT_EQ(g_date_time_get_second(dt), 56);

  // UTC offset is in microseconds.
  EXPECT_EQ(g_date_time_get_utc_offset(dt), static_cast<gint64>(0));

  g_date_time_unref(dt);
}

TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, DoesNotCrashOnClearlyMalformedModDate_2190) {
  // Boundary / error-ish input: malformed /ModDate string.
  // We do NOT assume conversion semantics; only require it to be safe and return either
  // nullptr or a valid GDateTime* (which we then unref).
  LoadWithInfoBody("<< /Producer (UnitTest) /ModDate (NOT_A_PDF_DATE) >>");

  GDateTime *dt = poppler_document_get_modification_date_time(doc_);
  if (dt) {
    g_date_time_unref(dt);
  }
  SUCCEED();
}

} // namespace