// poppler-document-set-modification-date-time-test_2191.cc
//
// Unit tests for:
//   void poppler_document_set_modification_date_time(PopplerDocument *document,
//                                                    GDateTime *modification_datetime);
//
// Constraints respected:
// - Treat implementation as black box.
// - No private/internal state access.
// - Observable behavior via GLib critical logging (g_return_if_fail) and "no critical" for valid usage.

#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib-object.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// -----------------------------
// Test helpers
// -----------------------------

namespace {

class ScopedCriticalLogCatcher {
public:
  ScopedCriticalLogCatcher()
      : handler_id_(0)
  {
    // Catch critical logs from any domain. We use the default domain (nullptr),
    // which acts as "match all domains" for g_log_set_handler.
    handler_id_ = g_log_set_handler(
        nullptr,
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
        &ScopedCriticalLogCatcher::LogHandlerThunk,
        this);
  }

  ~ScopedCriticalLogCatcher()
  {
    if (handler_id_ != 0) {
      g_log_remove_handler(nullptr, handler_id_);
    }
  }

  int critical_count() const { return critical_count_; }
  const std::vector<std::string> &messages() const { return messages_; }

private:
  static void LogHandlerThunk(const gchar *log_domain,
                              GLogLevelFlags log_level,
                              const gchar *message,
                              gpointer user_data)
  {
    static_cast<ScopedCriticalLogCatcher *>(user_data)
        ->LogHandler(log_domain, log_level, message);
  }

  void LogHandler(const gchar * /*log_domain*/,
                  GLogLevelFlags /*log_level*/,
                  const gchar *message)
  {
    ++critical_count_;
    messages_.push_back(message ? message : "");
  }

  guint handler_id_;
  int critical_count_ = 0;
  std::vector<std::string> messages_;
};

// Build a minimal valid PDF with correct xref offsets.
// This is only test input generation (not re-implementing Poppler logic).
static std::string BuildMinimalPdfBytes()
{
  std::string pdf;
  pdf.reserve(1024);

  auto append = [&](const char *s) { pdf.append(s); };

  append("%PDF-1.1\n");

  // Record offsets for objects 1..4.
  std::vector<long> obj_offset(5, 0);

  auto append_obj = [&](int obj_num, const std::string &body) {
    obj_offset[obj_num] = static_cast<long>(pdf.size());
    pdf += std::to_string(obj_num) + " 0 obj\n";
    pdf += body;
    if (body.empty() || body.back() != '\n') pdf += "\n";
    append("endobj\n");
  };

  append_obj(1, "<< /Type /Catalog /Pages 2 0 R >>\n");
  append_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n");
  append_obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n");

  // Simple content stream.
  const char *stream_data = "BT /F1 24 Tf 72 120 Td (Hi) Tj ET\n";
  std::string obj4;
  obj4 += "<< /Length ";
  obj4 += std::to_string(std::strlen(stream_data));
  obj4 += " >>\nstream\n";
  obj4 += stream_data;
  obj4 += "endstream\n";
  append_obj(4, obj4);

  // xref table
  const long xref_pos = static_cast<long>(pdf.size());
  append("xref\n");
  append("0 5\n");
  append("0000000000 65535 f \n");

  char line[32];
  for (int i = 1; i <= 4; ++i) {
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", obj_offset[i]);
    append(line);
  }

  // trailer
  append("trailer\n");
  append("<< /Root 1 0 R /Size 5 >>\n");
  append("startxref\n");
  pdf += std::to_string(xref_pos);
  append("\n%%EOF\n");

  return pdf;
}

static PopplerDocument *CreateDocumentFromMinimalPdfOrDie()
{
  std::string pdf = BuildMinimalPdfBytes();

  GError *error = nullptr;
  // poppler_document_new_from_data is part of poppler-glib and is widely available.
  PopplerDocument *doc =
      poppler_document_new_from_data(pdf.c_str(), static_cast<int>(pdf.size()), /*password=*/nullptr, &error);

  if (!doc) {
    std::string msg = "Failed to create PopplerDocument from minimal PDF.";
    if (error && error->message) {
      msg += " GError: ";
      msg += error->message;
    }
    if (error) g_error_free(error);
    // Hard fail: without a valid document we can't test the "valid document" paths.
    ADD_FAILURE() << msg;
    return nullptr;
  }

  if (error) g_error_free(error);
  return doc;
}

} // namespace

// -----------------------------
// Tests
// -----------------------------

class PopplerDocumentSetModificationDateTimeTest_2191 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Ensure GLib type system is initialized in older environments (harmless if already done).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, NullDocumentEmitsCritical_2191)
{
  ScopedCriticalLogCatcher logs;

  // Should trigger g_return_if_fail(POPPLER_IS_DOCUMENT(document)) and return.
  poppler_document_set_modification_date_time(nullptr, nullptr);

  EXPECT_GE(logs.critical_count(), 1);

  // Best-effort check: message typically mentions the failed check.
  bool mentions_failed_check = false;
  for (const auto &m : logs.messages()) {
    if (m.find("POPPLER_IS_DOCUMENT") != std::string::npos) {
      mentions_failed_check = true;
      break;
    }
  }
  EXPECT_TRUE(mentions_failed_check);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, ValidDocumentWithNullDateDoesNotEmitCritical_2191)
{
  PopplerDocument *doc = CreateDocumentFromMinimalPdfOrDie();
  ASSERT_NE(doc, nullptr);

  ScopedCriticalLogCatcher logs;

  // Boundary: modification_datetime == nullptr.
  poppler_document_set_modification_date_time(doc, nullptr);

  EXPECT_EQ(logs.critical_count(), 0);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, ValidDocumentWithDateDoesNotEmitCritical_2191)
{
  PopplerDocument *doc = CreateDocumentFromMinimalPdfOrDie();
  ASSERT_NE(doc, nullptr);

  // Create a deterministic datetime.
  GDateTime *dt = g_date_time_new_utc(2020, 1, 2, 3, 4, 5);
  ASSERT_NE(dt, nullptr);

  ScopedCriticalLogCatcher logs;

  // Normal operation: non-null datetime.
  poppler_document_set_modification_date_time(doc, dt);

  EXPECT_EQ(logs.critical_count(), 0);

  g_date_time_unref(dt);
  g_object_unref(doc);
}