// poppler_document_get_title_test_2172.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

class ScopedGLogCatcher {
public:
  ScopedGLogCatcher(const char* domain, GLogLevelFlags levels)
      : domain_(domain), levels_(levels) {
    handler_id_ = g_log_set_handler(domain_, levels_, &ScopedGLogCatcher::Handler, this);
  }

  ~ScopedGLogCatcher() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_, handler_id_);
      handler_id_ = 0;
    }
  }

  int count() const { return count_; }
  const std::string& last_message() const { return last_message_; }

private:
  static void Handler(const gchar* /*log_domain*/, GLogLevelFlags /*log_level*/,
                      const gchar* message, gpointer user_data) {
    auto* self = static_cast<ScopedGLogCatcher*>(user_data);
    self->count_++;
    self->last_message_ = message ? message : "";
  }

  const char* domain_;
  GLogLevelFlags levels_;
  guint handler_id_ = 0;
  int count_ = 0;
  std::string last_message_;
};

static std::string EscapePdfLiteralString(const std::string& s) {
  std::string out;
  out.reserve(s.size() + 8);
  for (char c : s) {
    if (c == '\\' || c == '(' || c == ')') out.push_back('\\');
    out.push_back(c);
  }
  return out;
}

static std::string XrefEntryForOffset(size_t off, bool in_use) {
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0') << off << " "
      << "00000" << " " << (in_use ? "n" : "f") << " \n";
  return oss.str();
}

static std::string BuildMinimalPdfWithInfoTitleLiteral(const std::string& title_literal) {
  // Build a minimal, valid PDF with an /Info dictionary containing /Title (...).
  // Offsets are computed dynamically for correctness.
  const std::string header = "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<std::string> objs(6); // 0 unused; 1..5 used
  objs[1] =
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n";
  objs[2] =
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n";
  objs[3] =
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>\n"
      "endobj\n";
  // Empty content stream (Length 0)
  objs[4] =
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n";
  objs[5] =
      "5 0 obj\n"
      "<< /Title (" + EscapePdfLiteralString(title_literal) + ") >>\n"
      "endobj\n";

  std::string pdf = header;
  std::vector<size_t> offsets(6, 0);

  for (int i = 1; i <= 5; ++i) {
    offsets[i] = pdf.size();
    pdf += objs[i];
  }

  const size_t xref_off = pdf.size();
  std::ostringstream xref;
  xref << "xref\n";
  xref << "0 6\n";
  xref << "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) xref << XrefEntryForOffset(offsets[i], true);

  pdf += xref.str();

  std::ostringstream trailer;
  trailer << "trailer\n"
          << "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n"
          << "startxref\n"
          << xref_off << "\n"
          << "%%EOF\n";
  pdf += trailer.str();

  return pdf;
}

static std::string BuildMinimalPdfWithInfoTitleHex(const std::string& hex_string_no_brackets) {
  const std::string header = "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<std::string> objs(6);
  objs[1] =
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n";
  objs[2] =
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n";
  objs[3] =
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>\n"
      "endobj\n";
  objs[4] =
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n";
  objs[5] =
      "5 0 obj\n"
      "<< /Title <" + hex_string_no_brackets + "> >>\n"
      "endobj\n";

  std::string pdf = header;
  std::vector<size_t> offsets(6, 0);
  for (int i = 1; i <= 5; ++i) {
    offsets[i] = pdf.size();
    pdf += objs[i];
  }

  const size_t xref_off = pdf.size();
  std::ostringstream xref;
  xref << "xref\n";
  xref << "0 6\n";
  xref << "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) xref << XrefEntryForOffset(offsets[i], true);
  pdf += xref.str();

  std::ostringstream trailer;
  trailer << "trailer\n"
          << "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n"
          << "startxref\n"
          << xref_off << "\n"
          << "%%EOF\n";
  pdf += trailer.str();

  return pdf;
}

static PopplerDocument* NewDocumentFromDataOrFail(const std::string& pdf) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_data(pdf.data(),
                                                        static_cast<int>(pdf.size()),
                                                        /*password*/ nullptr,
                                                        &error);
  if (!doc) {
    std::string msg = "poppler_document_new_from_data failed";
    if (error && error->message) msg += std::string(": ") + error->message;
    if (error) g_error_free(error);
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) {
    g_error_free(error);
    ADD_FAILURE() << "Expected no error from poppler_document_new_from_data";
  }
  return doc;
}

class PopplerDocumentGetTitleTest_2172 : public ::testing::Test {
protected:
  void TearDown() override {
    // Nothing global to clean up.
  }
};

TEST_F(PopplerDocumentGetTitleTest_2172, NullDocumentReturnsNullAndLogsCritical_2172) {
  ScopedGLogCatcher catcher("GLib-GObject", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL);

  gchar* title = poppler_document_get_title(nullptr);

  EXPECT_EQ(title, nullptr);
  EXPECT_GE(catcher.count(), 1) << "Expected a GLib-GObject critical log for g_return_val_if_fail";
}

TEST_F(PopplerDocumentGetTitleTest_2172, NonDocumentGObjectReturnsNullAndLogsCritical_2172) {
  ScopedGLogCatcher catcher("GLib-GObject", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL);

  GObject* not_a_doc = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(not_a_doc, nullptr);

  gchar* title = poppler_document_get_title(reinterpret_cast<PopplerDocument*>(not_a_doc));

  EXPECT_EQ(title, nullptr);
  EXPECT_GE(catcher.count(), 1) << "Expected a GLib-GObject critical log for invalid instance";

  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetTitleTest_2172, ReturnsAsciiTitleFromInfoDictionary_2172) {
  const std::string pdf = BuildMinimalPdfWithInfoTitleLiteral("Unit Test Title");
  PopplerDocument* doc = NewDocumentFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* title = poppler_document_get_title(doc);

  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Unit Test Title");

  g_free(title);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetTitleTest_2172, ReturnsUtf8ForUtf16BeHexTitle_2172) {
  // "테스트" in UTF-16BE with BOM: FE FF D1 4C C2 A4 D2 B8
  const std::string pdf = BuildMinimalPdfWithInfoTitleHex("FEFFD14CC2A4D2B8");
  PopplerDocument* doc = NewDocumentFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* title = poppler_document_get_title(doc);

  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, u8"테스트");

  g_free(title);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetTitleTest_2172, EmptyTitleDoesNotCrashAndIsNullOrEmpty_2172) {
  const std::string pdf = BuildMinimalPdfWithInfoTitleLiteral("");
  PopplerDocument* doc = NewDocumentFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* title = poppler_document_get_title(doc);

  // Observable boundary behavior: accept either NULL or an empty string, but must not crash.
  if (title) {
    EXPECT_STREQ(title, "");
    g_free(title);
  }

  g_object_unref(doc);
}

} // namespace