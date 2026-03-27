// poppler-document-set-author-test_2175.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace {

// Build a minimal, valid PDF (with /Info) in-memory so we can create a PopplerDocument
// without relying on external fixture files.
static std::string BuildMinimalPdfWithInfo(const std::string& author_utf8) {
  // NOTE: We keep the PDF extremely small: 1 page, empty content stream.
  // /Info contains /Author ( ... ) and /Producer ( ... ) for completeness.
  // We must generate a correct xref table with accurate byte offsets.
  auto pdf_escape = [](const std::string& s) -> std::string {
    // Escape parentheses and backslashes for PDF literal strings.
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s) {
      if (c == '(' || c == ')' || c == '\\') out.push_back('\\');
      out.push_back(static_cast<char>(c));
    }
    return out;
  };

  const std::string author_escaped = pdf_escape(author_utf8);

  std::vector<std::string> objs;
  objs.reserve(6);
  objs.push_back("");  // index 0 unused (xref entry 0 is the free object)

  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");

  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
      "endobj\n");

  objs.push_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n");

  objs.push_back(
      "5 0 obj\n"
      "<< /Producer (PopplerTest) /Author (" +
      author_escaped +
      ") >>\n"
      "endobj\n");

  std::string pdf;
  pdf.reserve(2048 + author_utf8.size());

  pdf += "%PDF-1.4\n";
  // Track offsets for xref (object number -> byte offset).
  std::vector<size_t> offsets(6, 0);

  for (int i = 1; i <= 5; ++i) {
    offsets[i] = pdf.size();
    pdf += objs[i];
  }

  const size_t xref_offset = pdf.size();
  pdf += "xref\n";
  pdf += "0 6\n";
  // Object 0: free entry
  pdf += "0000000000 65535 f \n";

  auto fmt_offset = [](size_t off) -> std::string {
    char buf[32];
    // 10-digit, zero-padded offset.
    std::snprintf(buf, sizeof(buf), "%010zu", off);
    return std::string(buf);
  };

  for (int i = 1; i <= 5; ++i) {
    pdf += fmt_offset(offsets[i]);
    pdf += " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";

  return pdf;
}

static PopplerDocument* NewDocFromPdfDataOrFail(const std::string& pdf_data) {
  GError* error = nullptr;
  PopplerDocument* doc =
      poppler_document_new_from_data(pdf_data.data(),
                                     static_cast<int>(pdf_data.size()),
                                     /*password=*/nullptr,
                                     &error);
  if (!doc) {
    std::string msg = "Failed to create PopplerDocument from minimal PDF.";
    if (error && error->message) {
      msg += " GError: ";
      msg += error->message;
    }
    if (error) g_error_free(error);
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

static std::string GetAuthorOrEmpty(PopplerDocument* doc) {
  gchar* author = poppler_document_get_author(doc);
  std::string out = author ? author : "";
  if (author) g_free(author);
  return out;
}

// GLib log capture for g_return_if_fail criticals.
struct LogCapture {
  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar* /*message*/,
                      gpointer user_data) {
    auto* self = static_cast<LogCapture*>(user_data);
    self->count++;
  }

  void Install() {
    // Install on default domain and the common "Poppler" domain (depending on build).
    handler_id_default =
        g_log_set_handler(nullptr, (GLogLevelFlags)G_LOG_LEVEL_CRITICAL, &Handler, this);
    handler_id_poppler =
        g_log_set_handler("Poppler", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL, &Handler, this);
  }

  void Uninstall() {
    if (handler_id_default) g_log_remove_handler(nullptr, handler_id_default);
    if (handler_id_poppler) g_log_remove_handler("Poppler", handler_id_poppler);
    handler_id_default = 0;
    handler_id_poppler = 0;
  }

  int count = 0;
  guint handler_id_default = 0;
  guint handler_id_poppler = 0;
};

class PopplerDocumentSetAuthorTest_2175 : public ::testing::Test {
 protected:
  void SetUp() override {
    const std::string pdf = BuildMinimalPdfWithInfo("Initial Author");
    doc_ = NewDocFromPdfDataOrFail(pdf);
    ASSERT_NE(doc_, nullptr);
  }

  void TearDown() override {
    if (doc_) g_object_unref(doc_);
    doc_ = nullptr;
  }

  PopplerDocument* doc_ = nullptr;
};

}  // namespace

// Normal operation: setting a new valid UTF-8 author updates the observable author string.
TEST_F(PopplerDocumentSetAuthorTest_2175, SetValidUtf8AuthorUpdatesAuthor_2175) {
  const std::string before = GetAuthorOrEmpty(doc_);
  EXPECT_FALSE(before.empty());

  poppler_document_set_author(doc_, "New Author");
  const std::string after = GetAuthorOrEmpty(doc_);

  EXPECT_EQ(after, "New Author");
}

// Boundary condition: passing NULL author should be handled (clears or becomes empty/null).
TEST_F(PopplerDocumentSetAuthorTest_2175, SetNullAuthorClearsOrEmptiesAuthor_2175) {
  poppler_document_set_author(doc_, "Some Author");
  EXPECT_EQ(GetAuthorOrEmpty(doc_), "Some Author");

  poppler_document_set_author(doc_, nullptr);
  const std::string after = GetAuthorOrEmpty(doc_);

  // Different implementations may return NULL or empty after clearing; treat both as acceptable.
  EXPECT_TRUE(after.empty());
}

// Boundary condition: very long author string should be accepted and round-trip through getter.
TEST_F(PopplerDocumentSetAuthorTest_2175, SetVeryLongAuthorRoundTrips_2175) {
  std::string long_author(10000, 'A');

  poppler_document_set_author(doc_, long_author.c_str());
  const std::string after = GetAuthorOrEmpty(doc_);

  EXPECT_EQ(after.size(), long_author.size());
  EXPECT_EQ(after, long_author);
}

// Error/exceptional (observable): invalid UTF-8 input should not update author (function returns early).
TEST_F(PopplerDocumentSetAuthorTest_2175, InvalidUtf8DoesNotChangeAuthor_2175) {
  poppler_document_set_author(doc_, "Stable Author");
  const std::string stable = GetAuthorOrEmpty(doc_);
  EXPECT_EQ(stable, "Stable Author");

  // Invalid UTF-8 sequence: 0xC3 0x28 is not valid UTF-8.
  const char invalid_utf8[] = "\xC3\x28";
  poppler_document_set_author(doc_, invalid_utf8);

  const std::string after = GetAuthorOrEmpty(doc_);
  EXPECT_EQ(after, stable);
}

// Error/exceptional: g_return_if_fail should log a critical and return when document is NULL.
TEST(PopplerDocumentSetAuthorStandaloneTest_2175, NullDocumentTriggersCriticalAndDoesNotCrash_2175) {
  LogCapture cap;
  cap.Install();

  poppler_document_set_author(nullptr, "Ignored");

  cap.Uninstall();
  EXPECT_GE(cap.count, 1) << "Expected at least one CRITICAL log from g_return_if_fail.";
}

// Error/exceptional: non-document GObject should trigger g_return_if_fail critical and return.
// (We only verify it doesn't crash and emits a critical log.)
TEST(PopplerDocumentSetAuthorStandaloneTest_2175, WrongGObjectTypeTriggersCriticalAndDoesNotCrash_2175) {
  GObject* not_a_doc = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(not_a_doc, nullptr);

  LogCapture cap;
  cap.Install();

  poppler_document_set_author(reinterpret_cast<PopplerDocument*>(not_a_doc), "Ignored");

  cap.Uninstall();
  g_object_unref(not_a_doc);

  EXPECT_GE(cap.count, 1) << "Expected at least one CRITICAL log from g_return_if_fail.";
}