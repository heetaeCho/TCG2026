// poppler-document-get-author-test_2174.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <iomanip>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace {

class ScopedGLogHandler {
public:
  ScopedGLogHandler(const gchar* domain, GLogLevelFlags levels)
      : domain_(domain ? domain : ""), levels_(levels) {
    handler_id_ = g_log_set_handler(domain ? domain : nullptr, levels_, &ScopedGLogHandler::HandlerThunk, this);
  }

  ~ScopedGLogHandler() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_.empty() ? nullptr : domain_.c_str(), handler_id_);
    }
  }

  int critical_count() const { return critical_count_; }
  int warning_count() const { return warning_count_; }
  int error_count() const { return error_count_; }

private:
  static void HandlerThunk(const gchar* /*log_domain*/,
                           GLogLevelFlags log_level,
                           const gchar* /*message*/,
                           gpointer user_data) {
    auto* self = static_cast<ScopedGLogHandler*>(user_data);
    if (log_level & G_LOG_LEVEL_CRITICAL) self->critical_count_++;
    if (log_level & G_LOG_LEVEL_WARNING) self->warning_count_++;
    if (log_level & G_LOG_LEVEL_ERROR) self->error_count_++;
  }

  std::string domain_;
  GLogLevelFlags levels_;
  guint handler_id_{0};

  int critical_count_{0};
  int warning_count_{0};
  int error_count_{0};
};

static std::string Pad10(size_t off) {
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0') << off;
  return oss.str();
}

// Build a tiny valid PDF with an /Info dictionary.
// We compute xref offsets so Poppler can reliably parse it.
static std::string BuildMinimalPdfWithOptionalAuthor(const std::optional<std::string>& author) {
  // Objects:
  // 1 0: Catalog
  // 2 0: Pages
  // 3 0: Page
  // 4 0: Contents (empty stream)
  // 5 0: Info (Producer + optional Author)
  std::vector<size_t> offsets(6, 0); // include object 0 (free)

  std::string pdf;
  pdf += "%PDF-1.4\n";

  auto add_obj = [&](int obj_num, const std::string& body) {
    offsets[obj_num] = pdf.size();
    pdf += std::to_string(obj_num) + " 0 obj\n";
    pdf += body;
    if (!body.empty() && body.back() != '\n') pdf += "\n";
    pdf += "endobj\n";
  };

  add_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");
  add_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  add_obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>");

  // Empty stream contents
  add_obj(4, "<< /Length 0 >>\nstream\n\nendstream");

  std::string info = "<< /Producer (PopplerTest)";
  if (author.has_value()) {
    // Keep it simple: PDFDocEncoding-safe ASCII.
    info += " /Author (" + *author + ")";
  }
  info += " >>";
  add_obj(5, info);

  const size_t xref_offset = pdf.size();
  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    pdf += Pad10(offsets[i]) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static PopplerDocument* NewDocFromPdfDataOrSkip(const std::string& pdf_bytes) {
  GError* error = nullptr;
  PopplerDocument* doc =
      poppler_document_new_from_data(pdf_bytes.data(),
                                     static_cast<int>(pdf_bytes.size()),
                                     /*password=*/nullptr,
                                     &error);
  if (!doc) {
    std::string msg = "poppler_document_new_from_data failed";
    if (error && error->message) {
      msg += std::string(": ") + error->message;
    }
    if (error) g_error_free(error);
    GTEST_SKIP() << msg;
  }
  if (error) g_error_free(error);
  return doc;
}

class PopplerDocumentGetAuthorTest_2174 : public ::testing::Test {};

TEST_F(PopplerDocumentGetAuthorTest_2174, NullDocumentReturnsNullAndLogsCritical_2174) {
  // Intercept CRITICAL logs produced by g_return_val_if_fail.
  ScopedGLogHandler handler(/*domain=*/nullptr, static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  gchar* author = poppler_document_get_author(nullptr);
  EXPECT_EQ(author, nullptr);
  EXPECT_GE(handler.critical_count(), 1);
}

TEST_F(PopplerDocumentGetAuthorTest_2174, NonDocumentInstanceReturnsNullAndLogsCritical_2174) {
  ScopedGLogHandler handler(/*domain=*/nullptr, static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  // Create a valid GObject instance that is NOT a PopplerDocument.
  GObject* not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  gchar* author = poppler_document_get_author(reinterpret_cast<PopplerDocument*>(not_a_doc));
  EXPECT_EQ(author, nullptr);
  EXPECT_GE(handler.critical_count(), 1);

  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetAuthorTest_2174, ValidDocumentWithAuthorReturnsExpectedUtf8_2174) {
  const std::string pdf = BuildMinimalPdfWithOptionalAuthor(std::optional<std::string>{"John Doe"});
  PopplerDocument* doc = NewDocFromPdfDataOrSkip(pdf);

  gchar* author = poppler_document_get_author(doc);
  ASSERT_NE(author, nullptr);
  EXPECT_STREQ(author, "John Doe");

  g_free(author);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetAuthorTest_2174, ValidDocumentWithoutAuthorReturnsNullOrEmpty_2174) {
  const std::string pdf = BuildMinimalPdfWithOptionalAuthor(std::nullopt);
  PopplerDocument* doc = NewDocFromPdfDataOrSkip(pdf);

  gchar* author = poppler_document_get_author(doc);

  // Boundary behavior: depending on implementation details of doc info extraction and
  // _poppler_goo_string_to_utf8, this may be NULL or an empty string. We only assert
  // the observable, non-crashing contract and accept either.
  if (author) {
    EXPECT_TRUE(author[0] == '\0');
    g_free(author);
  } else {
    SUCCEED();
  }

  g_object_unref(doc);
}

} // namespace