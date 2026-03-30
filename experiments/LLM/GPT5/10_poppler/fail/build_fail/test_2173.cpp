// poppler_document_set_title_test_2173.cc
//
// Unit tests for:
//   void poppler_document_set_title(PopplerDocument *document, const gchar *title);
//
// Constraints respected:
// - Treat implementation as black box.
// - Verify only observable behavior through public API (e.g., poppler_document_get_title).
// - No access to private/internal state.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

// Build a minimal, valid PDF in-memory so we can create a real PopplerDocument.
// This is test data generation (not re-implementing Poppler logic).
static std::string BuildMinimalPdf_2173() {
  std::string pdf;
  pdf.reserve(1024);

  auto append = [&](const std::string& s) { pdf.append(s); };

  append("%PDF-1.4\n");

  // Record offsets for xref (object 0 is special/free).
  std::vector<long> offsets(5, 0);

  auto add_obj = [&](int obj_num, const std::string& body) {
    offsets[obj_num] = static_cast<long>(pdf.size());
    append(std::to_string(obj_num));
    append(" 0 obj\n");
    append(body);
    append("\nendobj\n");
  };

  // 1: Catalog
  add_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");

  // 2: Pages
  add_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // 3: Page (empty resources; contents points to 4)
  add_obj(3,
          "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
          "   /Resources << >>\n"
          "   /Contents 4 0 R >>");

  // 4: Contents stream (empty stream)
  const char kStream[] = "stream\n\nendstream";
  std::string obj4;
  obj4 += "<< /Length ";
  obj4 += std::to_string(static_cast<int>(std::strlen(kStream)));
  obj4 += " >>\n";
  obj4 += kStream;
  add_obj(4, obj4);

  // xref
  const long xref_offset = static_cast<long>(pdf.size());
  append("xref\n");
  append("0 5\n");
  append("0000000000 65535 f \n");

  char buf[64];
  for (int i = 1; i <= 4; ++i) {
    // 10-digit, zero-padded byte offset, generation 00000, in-use 'n'
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    append(buf);
  }

  // trailer
  append("trailer\n");
  append("<< /Size 5 /Root 1 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xref_offset));
  append("\n%%EOF\n");

  return pdf;
}

static PopplerDocument* CreateTestDocument_2173(GError** error_out) {
  std::string pdf = BuildMinimalPdf_2173();
  // poppler_document_new_from_data copies/parses the bytes; keep pdf alive until return.
  return poppler_document_new_from_data(pdf.data(),
                                       static_cast<int>(pdf.size()),
                                       /*password*/ nullptr,
                                       error_out);
}

static gchar* GetTitleDup_2173(PopplerDocument* doc) {
  // Poppler GLib typically returns newly allocated strings for getters like get_title().
  // If in your build it returns const gchar*, this is still safe to treat as gchar*
  // for comparison; but only free if it's documented as allocated.
  return poppler_document_get_title(doc);
}

class PopplerDocumentSetTitleTest_2173 : public ::testing::Test {
protected:
  void SetUp() override {
    GError* error = nullptr;
    doc_ = CreateTestDocument_2173(&error);
    ASSERT_NE(doc_, nullptr) << (error ? error->message : "Failed to create PopplerDocument");
    if (error) g_error_free(error);
  }

  void TearDown() override {
    if (doc_) g_object_unref(doc_);
    doc_ = nullptr;
  }

  PopplerDocument* doc_ = nullptr;
};

TEST_F(PopplerDocumentSetTitleTest_2173, SetsAsciiTitleAndIsObservableViaGetTitle_2173) {
  poppler_document_set_title(doc_, "My Title");

  g_autofree gchar* title = GetTitleDup_2173(doc_);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "My Title");
}

TEST_F(PopplerDocumentSetTitleTest_2173, SetsUtf8TitleIncludingNonAscii_2173) {
  const gchar* utf8_title = "제목 – Poppler ✓";

  poppler_document_set_title(doc_, utf8_title);

  g_autofree gchar* title = GetTitleDup_2173(doc_);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, utf8_title);
}

TEST_F(PopplerDocumentSetTitleTest_2173, EmptyStringTitleIsAcceptedAndObservable_2173) {
  poppler_document_set_title(doc_, "");

  g_autofree gchar* title = GetTitleDup_2173(doc_);
  // Depending on Poppler behavior, empty title may be stored as "" or treated as unset (NULL).
  // Accept either, but if non-null it must be empty.
  if (title) {
    EXPECT_STREQ(title, "");
  } else {
    SUCCEED();
  }
}

TEST_F(PopplerDocumentSetTitleTest_2173, NullTitleClearsOrUnsetsTitle_2173) {
  poppler_document_set_title(doc_, "Initial");
  {
    g_autofree gchar* title = GetTitleDup_2173(doc_);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Initial");
  }

  poppler_document_set_title(doc_, nullptr);

  g_autofree gchar* cleared = GetTitleDup_2173(doc_);
  // Clearing may yield NULL or empty string depending on underlying document info handling.
  if (cleared) {
    EXPECT_TRUE(cleared[0] == '\0');
  } else {
    SUCCEED();
  }
}

TEST_F(PopplerDocumentSetTitleTest_2173, InvalidUtf8DoesNotChangeExistingTitle_2173) {
  poppler_document_set_title(doc_, "Before");

  // Invalid UTF-8 byte sequence (C3 28).
  const gchar invalid_utf8[] = {static_cast<gchar>(0xC3), static_cast<gchar>(0x28), 0};

  poppler_document_set_title(doc_, invalid_utf8);

  g_autofree gchar* title = GetTitleDup_2173(doc_);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Before");
}

TEST_F(PopplerDocumentSetTitleTest_2173, VeryLongTitleIsHandled_2173) {
  std::string long_title(16 * 1024, 'A');  // 16 KiB of 'A'
  poppler_document_set_title(doc_, long_title.c_str());

  g_autofree gchar* title = GetTitleDup_2173(doc_);
  ASSERT_NE(title, nullptr);
  EXPECT_EQ(std::strlen(title), long_title.size());
  EXPECT_EQ(std::memcmp(title, long_title.data(), long_title.size()), 0);
}

TEST_F(PopplerDocumentSetTitleTest_2173, NullDocumentPointerDoesNotCrash_2173) {
  // g_return_if_fail should early-return; behavior is observable as "no crash".
  EXPECT_NO_FATAL_FAILURE(poppler_document_set_title(nullptr, "X"));
}

}  // namespace