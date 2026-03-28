// poppler_document_get_pdf_version_string_test_2170.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <string>
#include <vector>

#include <poppler.h>

// Build a small, valid PDF in-memory with a chosen header version (e.g. "1.7", "1.0").
// This is test data generation, not re-implementing any Poppler logic.
static std::string MakeMinimalPdfWithVersion(const std::string& version) {
  // Header must be exactly "%PDF-x.y\n" for typical parsers.
  const std::string header = "%PDF-" + version + "\n";

  const std::vector<std::string> objects = {
      // 1 0 obj: Catalog
      "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n",
      // 2 0 obj: Pages
      "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n",
      // 3 0 obj: Page
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
      "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
      "endobj\n",
      // 4 0 obj: Contents stream
      "4 0 obj\n<< /Length 44 >>\nstream\n"
      "BT /F1 24 Tf 72 120 Td (Hi) Tj ET\n"
      "endstream\nendobj\n",
      // 5 0 obj: Font
      "5 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n",
  };

  // Assemble body and record offsets for xref.
  std::string pdf = header;
  std::vector<size_t> offsets;
  offsets.reserve(objects.size() + 1);

  // Object 0 is the free entry at offset 0.
  offsets.push_back(0);

  for (const auto& obj : objects) {
    offsets.push_back(pdf.size());
    pdf += obj;
  }

  // xref starts here
  const size_t xref_offset = pdf.size();

  pdf += "xref\n";
  pdf += "0 6\n";
  // Entry 0: free
  pdf += "0000000000 65535 f \n";

  // Entries 1..5: in-use.
  for (int i = 1; i <= 5; ++i) {
    // Format: 10-digit offset, space, 5-digit generation, space, n/f, space, newline.
    char line[32];
    g_snprintf(line, sizeof(line), "%010u 00000 n \n",
               static_cast<unsigned>(offsets[static_cast<size_t>(i)]));
    pdf += line;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";

  return pdf;
}

class PopplerDocumentGetPdfVersionStringTest_2170 : public ::testing::Test {
 protected:
  static PopplerDocument* LoadDocFromDataOrFail(const std::string& pdf_data) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf_data.c_str(),
                                       static_cast<int>(pdf_data.size()),
                                       /*password=*/nullptr,
                                       &error);
    if (!doc) {
      std::string msg = "Failed to create PopplerDocument from in-memory PDF.";
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

  static void ExpectLooksLikePdfVersionString(const char* s) {
    ASSERT_NE(s, nullptr);
    ASSERT_TRUE(g_str_has_prefix(s, "PDF-")) << "Returned string: " << s;
    // Must have at least one digit after "PDF-".
    ASSERT_NE(s[4], '\0') << "Returned string too short: " << s;
    ASSERT_TRUE(g_ascii_isdigit(s[4])) << "Expected digit after 'PDF-': " << s;
  }
};

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, NullDocumentReturnsNull_2170) {
  // g_return_val_if_fail should return NULL for invalid input.
  // We don't assume logging behavior here—only the return value.
  gchar* s = poppler_document_get_pdf_version_string(nullptr);
  EXPECT_EQ(s, nullptr);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, NonDocumentTriggersCriticalAndReturnsNull_2170) {
  // When passing a non-PopplerDocument pointer, g_return_val_if_fail typically emits a CRITICAL.
  // We verify observable external interaction (GLib log) and return value.
  GObject* not_a_doc = static_cast<GObject*>(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL,
                        "*POPPLER_IS_DOCUMENT*failed*");

  gchar* s = poppler_document_get_pdf_version_string(reinterpret_cast<PopplerDocument*>(not_a_doc));
  EXPECT_EQ(s, nullptr);

  g_test_assert_expected_messages();
  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, ValidDocumentReturnsNonNullWithPdfPrefix_2170) {
  const std::string pdf = MakeMinimalPdfWithVersion("1.7");
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* s = poppler_document_get_pdf_version_string(doc);
  ExpectLooksLikePdfVersionString(s);

  g_free(s);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, TypicalPdf17ReturnsExpectedString_2170) {
  const std::string pdf = MakeMinimalPdfWithVersion("1.7");
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* s = poppler_document_get_pdf_version_string(doc);
  ASSERT_NE(s, nullptr);

  // For common PDFs, the API is expected to return a "PDF-x.y" style string.
  // We assert the exact value for this controlled input.
  EXPECT_STREQ(s, "PDF-1.7");

  g_free(s);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, MinorZeroBoundaryIsHandled_2170) {
  const std::string pdf = MakeMinimalPdfWithVersion("1.0");
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* s = poppler_document_get_pdf_version_string(doc);
  ExpectLooksLikePdfVersionString(s);

  // Formatting for 1.0 may reasonably be "PDF-1" or "PDF-1.0" depending on implementation.
  // We accept either, without inferring internal formatting logic.
  ASSERT_TRUE(g_str_has_prefix(s, "PDF-1")) << "Returned string: " << s;

  const char after_major = s[5];  // character after "PDF-1"
  if (after_major == '\0') {
    SUCCEED();
  } else {
    // If there is more, it should be ".0" (common for 1.0).
    EXPECT_EQ(after_major, '.');
    EXPECT_EQ(s[6], '0');
    EXPECT_EQ(s[7], '\0');
  }

  g_free(s);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, RepeatedCallsReturnIndependentAllocatedStrings_2170) {
  const std::string pdf = MakeMinimalPdfWithVersion("1.7");
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* s1 = poppler_document_get_pdf_version_string(doc);
  gchar* s2 = poppler_document_get_pdf_version_string(doc);

  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);
  EXPECT_STREQ(s1, s2);

  // The function returns newly allocated strings; pointers should not alias.
  EXPECT_NE(s1, s2);

  g_free(s1);
  g_free(s2);
  g_object_unref(doc);
}