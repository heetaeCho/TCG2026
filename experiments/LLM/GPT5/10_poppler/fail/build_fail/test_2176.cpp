// poppler_document_get_subject_test_2176.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string EscapePdfLiteralString(const std::string& s) {
  // Escape for PDF literal strings: backslash and parentheses.
  std::string out;
  out.reserve(s.size());
  for (char c : s) {
    if (c == '\\' || c == '(' || c == ')') out.push_back('\\');
    out.push_back(c);
  }
  return out;
}

static std::string BuildMinimalPdfWithInfoSubject(const std::string* subject_or_nullptr) {
  // Builds a minimal valid PDF. If subject_or_nullptr is nullptr, omits /Info entirely.
  // If non-null, includes an /Info dict with /Subject ( ... ) (can be empty).
  std::string pdf;
  pdf.reserve(1024);

  auto append = [&](const std::string& s) { pdf += s; };
  auto obj_offsets = std::vector<size_t>(6, 0);

  append("%PDF-1.4\n%\xE2\xE3\xCF\xD3\n");  // header + binary comment

  // 1 0 obj - Catalog
  obj_offsets[1] = pdf.size();
  append("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

  // 2 0 obj - Pages
  obj_offsets[2] = pdf.size();
  append("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

  // 3 0 obj - Page
  obj_offsets[3] = pdf.size();
  append("3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10] /Contents 4 0 R >>\nendobj\n");

  // 4 0 obj - Empty contents stream
  obj_offsets[4] = pdf.size();
  append("4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n");

  // 5 0 obj - Info (optional)
  bool has_info = (subject_or_nullptr != nullptr);
  if (has_info) {
    obj_offsets[5] = pdf.size();
    append("5 0 obj\n<< ");
    append("/Subject (");
    append(EscapePdfLiteralString(*subject_or_nullptr));
    append(") ");
    append(">>\nendobj\n");
  } else {
    // Keep a placeholder offset for xref consistency; object 5 will be "free" if not emitted.
    obj_offsets[5] = 0;
  }

  const size_t xref_offset = pdf.size();
  append("xref\n0 6\n");
  append("0000000000 65535 f \n");

  auto xref_entry = [&](size_t off, bool in_use) {
    std::ostringstream oss;
    oss << std::setw(10) << std::setfill('0') << off << " " << std::setw(5) << std::setfill('0') << 0
        << (in_use ? " n \n" : " f \n");
    append(oss.str());
  };

  xref_entry(obj_offsets[1], true);
  xref_entry(obj_offsets[2], true);
  xref_entry(obj_offsets[3], true);
  xref_entry(obj_offsets[4], true);
  if (has_info) {
    xref_entry(obj_offsets[5], true);
  } else {
    // Object 5 is not present; mark it free.
    xref_entry(0, false);
  }

  append("trailer\n<< /Size 6 /Root 1 0 R ");
  if (has_info) append("/Info 5 0 R ");
  append(">>\n");
  append("startxref\n");
  append(std::to_string(xref_offset));
  append("\n%%EOF\n");

  return pdf;
}

static PopplerDocument* LoadDocFromPdfBytesOrFail(const std::string& pdf_bytes) {
  GError* error = nullptr;
  PopplerDocument* doc =
      poppler_document_new_from_data(pdf_bytes.data(), static_cast<int>(pdf_bytes.size()), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = "poppler_document_new_from_data failed";
    if (error && error->message) msg += std::string(": ") + error->message;
    if (error) g_error_free(error);
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

struct PopplerDocumentGetSubjectTest_2176 : public ::testing::Test {};

}  // namespace

TEST_F(PopplerDocumentGetSubjectTest_2176, NullDocumentReturnsNull_2176) {
  gchar* subject = poppler_document_get_subject(nullptr);
  EXPECT_EQ(subject, nullptr);
}

TEST_F(PopplerDocumentGetSubjectTest_2176, InvalidTypeReturnsNull_2176) {
  // Pass a non-PopplerDocument GObject instance; the type check should fail and return NULL.
  GObject* not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  gchar* subject = poppler_document_get_subject(reinterpret_cast<PopplerDocument*>(not_a_doc));
  EXPECT_EQ(subject, nullptr);

  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetSubjectTest_2176, ReturnsExpectedSubject_2176) {
  const std::string expected = "Test Subject";
  const std::string pdf = BuildMinimalPdfWithInfoSubject(&expected);

  PopplerDocument* doc = LoadDocFromPdfBytesOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* subject = poppler_document_get_subject(doc);
  ASSERT_NE(subject, nullptr);
  EXPECT_STREQ(subject, expected.c_str());

  g_free(subject);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetSubjectTest_2176, EmptySubjectReturnsEmptyString_2176) {
  const std::string empty = "";
  const std::string pdf = BuildMinimalPdfWithInfoSubject(&empty);

  PopplerDocument* doc = LoadDocFromPdfBytesOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* subject = poppler_document_get_subject(doc);
  ASSERT_NE(subject, nullptr);
  EXPECT_STREQ(subject, "");

  g_free(subject);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetSubjectTest_2176, NoInfoReturnsNull_2176) {
  const std::string pdf = BuildMinimalPdfWithInfoSubject(/*subject_or_nullptr=*/nullptr);

  PopplerDocument* doc = LoadDocFromPdfBytesOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* subject = poppler_document_get_subject(doc);
  EXPECT_EQ(subject, nullptr);

  // Only free if non-null (defensive; expectation is NULL).
  if (subject) g_free(subject);
  g_object_unref(doc);
}