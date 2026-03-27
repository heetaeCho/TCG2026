// poppler-document-is-linearized-test_2192.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <poppler.h>

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

namespace {

class ScopedGlibDefaultLogCatcher {
public:
  ScopedGlibDefaultLogCatcher()
      : old_handler_(g_log_set_default_handler(&ScopedGlibDefaultLogCatcher::Handler, this)) {
    Reset();
  }

  ~ScopedGlibDefaultLogCatcher()
  {
    g_log_set_default_handler(old_handler_, nullptr);
  }

  void Reset()
  {
    saw_critical_ = false;
    last_domain_.clear();
    last_message_.clear();
    last_level_ = static_cast<GLogLevelFlags>(0);
  }

  bool saw_critical() const { return saw_critical_; }
  const std::string &last_domain() const { return last_domain_; }
  const std::string &last_message() const { return last_message_; }
  GLogLevelFlags last_level() const { return last_level_; }

private:
  static void Handler(const gchar *log_domain,
                      GLogLevelFlags log_level,
                      const gchar *message,
                      gpointer user_data)
  {
    auto *self = static_cast<ScopedGlibDefaultLogCatcher *>(user_data);
    self->last_domain_ = log_domain ? log_domain : "";
    self->last_message_ = message ? message : "";
    self->last_level_ = log_level;

    // g_return_* typically logs CRITICAL.
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->saw_critical_ = true;
    }
    // Swallow the log to keep test output clean.
  }

  GLogFunc old_handler_;
  bool saw_critical_{false};
  std::string last_domain_;
  std::string last_message_;
  GLogLevelFlags last_level_{static_cast<GLogLevelFlags>(0)};
};

static std::string BuildMinimalPdfNonLinearized()
{
  // Build a small, valid, *non-linearized* PDF with correct xref offsets.
  // This is just test data generation; it does not infer the function-under-test logic.
  std::vector<std::string> objs;

  objs.emplace_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  objs.emplace_back(
      "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
  objs.emplace_back(
      "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources << /Font << /F1 5 0 R >> >>\n"
      "   /Contents 4 0 R >>\nendobj\n");

  const char kStream[] = "BT /F1 18 Tf 50 100 Td (Hello) Tj ET\n";
  {
    std::ostringstream o;
    o << "4 0 obj\n<< /Length " << (sizeof(kStream) - 1) << " >>\nstream\n";
    o << kStream;
    o << "endstream\nendobj\n";
    objs.emplace_back(o.str());
  }

  objs.emplace_back(
      "5 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n");

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n"; // binary comment as commonly used

  std::vector<uint32_t> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 is the free entry

  for (const auto &obj : objs) {
    offsets.push_back(static_cast<uint32_t>(pdf.tellp()));
    pdf << obj;
  }

  const uint32_t xref_pos = static_cast<uint32_t>(pdf.tellp());
  const int count = static_cast<int>(objs.size()) + 1;

  pdf << "xref\n";
  pdf << "0 " << count << "\n";
  pdf << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    // 10-digit, zero-padded offsets, generation 00000, in-use 'n'
    pdf << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
  }

  pdf << "trailer\n<< /Size " << count << " /Root 1 0 R >>\n";
  pdf << "startxref\n" << xref_pos << "\n%%EOF\n";

  return pdf.str();
}

struct PopplerDocDeleter {
  void operator()(PopplerDocument *doc) const
  {
    if (doc) {
      g_object_unref(doc);
    }
  }
};

class PopplerDocumentIsLinearizedTest_2192 : public ::testing::Test {
protected:
  void SetUp() override { /* nothing */ }
  void TearDown() override { /* nothing */ }
};

} // namespace

TEST_F(PopplerDocumentIsLinearizedTest_2192, NullDocumentReturnsFalseAndLogsCritical_2192)
{
  ScopedGlibDefaultLogCatcher catcher;
  catcher.Reset();

  const gboolean linearized = poppler_document_is_linearized(nullptr);

  EXPECT_FALSE(linearized);
  EXPECT_TRUE(catcher.saw_critical());
  // Message/domain are implementation details; we only assert that a critical was emitted.
}

TEST_F(PopplerDocumentIsLinearizedTest_2192, WrongGObjectTypeReturnsFalseAndLogsCritical_2192)
{
  ScopedGlibDefaultLogCatcher catcher;
  catcher.Reset();

  GObject *not_a_doc = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(not_a_doc, nullptr);

  const gboolean linearized =
      poppler_document_is_linearized(reinterpret_cast<PopplerDocument *>(not_a_doc));

  EXPECT_FALSE(linearized);
  EXPECT_TRUE(catcher.saw_critical());

  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentIsLinearizedTest_2192, ValidDocumentFromDataReturnsDeterministicBoolean_2192)
{
  const std::string pdf = BuildMinimalPdfNonLinearized();

  GError *error = nullptr;
  PopplerDocument *doc_raw =
      poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), nullptr, &error);

  ASSERT_EQ(error, nullptr);
  ASSERT_NE(doc_raw, nullptr);

  std::unique_ptr<PopplerDocument, PopplerDocDeleter> doc(doc_raw);

  const gboolean v1 = poppler_document_is_linearized(doc.get());
  const gboolean v2 = poppler_document_is_linearized(doc.get());

  // Observable behavior: function should return a gboolean and be stable for same object.
  EXPECT_TRUE(v1 == FALSE || v1 == TRUE);
  EXPECT_EQ(v1, v2);
}

TEST_F(PopplerDocumentIsLinearizedTest_2192, MinimalNonLinearizedPdfExpectedFalse_2192)
{
  // Boundary/normal: a small valid PDF that is not created as linearized should report FALSE.
  const std::string pdf = BuildMinimalPdfNonLinearized();

  GError *error = nullptr;
  PopplerDocument *doc_raw =
      poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), nullptr, &error);

  ASSERT_EQ(error, nullptr);
  ASSERT_NE(doc_raw, nullptr);

  std::unique_ptr<PopplerDocument, PopplerDocDeleter> doc(doc_raw);

  const gboolean linearized = poppler_document_is_linearized(doc.get());
  EXPECT_FALSE(linearized);
}