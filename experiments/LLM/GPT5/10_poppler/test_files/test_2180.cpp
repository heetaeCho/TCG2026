// File: poppler-document-get-creator-test-2180.cc
#include <gtest/gtest.h>

#include <string>
#include <vector>

extern "C" {
#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
}

// Helper: build a minimal, valid PDF with an /Info dictionary (optionally with /Creator).
static std::string MakeMinimalPdfWithInfo2180(const char* creator_or_null) {
  const std::string header = "%PDF-1.4\n";

  std::vector<std::string> objs;
  objs.reserve(5);

  // 1: Catalog
  objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  // 2: Pages
  objs.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
  // 3: Page
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R /Resources << >> >>\n"
      "endobj\n");
  // 4: Empty content stream
  objs.push_back("4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n");
  // 5: Info dictionary
  {
    std::string info = "5 0 obj\n<< /Producer (UnitTestProducer2180)";
    if (creator_or_null) {
      info += " /Creator (";
      info += creator_or_null;
      info += ")";
    }
    info += " >>\nendobj\n";
    objs.push_back(std::move(info));
  }

  std::string pdf = header;

  // Compute offsets for xref.
  // Offsets are from the beginning of the file.
  std::vector<size_t> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0);  // object 0 (free) entry

  for (const auto& obj : objs) {
    offsets.push_back(pdf.size());
    pdf += obj;
  }

  const size_t xref_offset = pdf.size();

  // xref table
  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char line[32];
    // 10-digit, zero-padded offset; generation 00000; in-use 'n'
    std::snprintf(line, sizeof(line), "%010lu 00000 n \n",
                  static_cast<unsigned long>(offsets[i]));
    pdf += line;
  }

  // trailer
  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";

  return pdf;
}

class PopplerDocumentGetCreatorTest_2180 : public ::testing::Test {
protected:
  static PopplerDocument* NewDocFromPdfDataOrFail_2180(const std::string& pdf) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), nullptr, &error);
    if (!doc) {
      std::string msg = "poppler_document_new_from_data failed";
      if (error && error->message) {
        msg += ": ";
        msg += error->message;
      }
      if (error) g_error_free(error);
      ADD_FAILURE() << msg;
    }
    if (error) g_error_free(error);
    return doc;
  }
};

TEST_F(PopplerDocumentGetCreatorTest_2180, ReturnsCreatorStringWhenPresent_2180) {
  const char* kCreator = "UnitTestCreator2180";
  const std::string pdf = MakeMinimalPdfWithInfo2180(kCreator);

  PopplerDocument* doc = NewDocFromPdfDataOrFail_2180(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* creator = poppler_document_get_creator(doc);
  ASSERT_NE(creator, nullptr);
  EXPECT_STREQ(creator, kCreator);

  g_free(creator);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetCreatorTest_2180, MultipleCallsReturnIndependentAllocatedStrings_2180) {
  const char* kCreator = "UnitTestCreator2180";
  const std::string pdf = MakeMinimalPdfWithInfo2180(kCreator);

  PopplerDocument* doc = NewDocFromPdfDataOrFail_2180(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* c1 = poppler_document_get_creator(doc);
  gchar* c2 = poppler_document_get_creator(doc);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  EXPECT_STREQ(c1, kCreator);
  EXPECT_STREQ(c2, kCreator);

  // They should be separate allocations (not a strict API guarantee, but typical for gchar* getters).
  // If an implementation returns the same pointer, freeing twice would be unsafe; so only compare.
  EXPECT_NE(c1, c2);

  g_free(c1);
  g_free(c2);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetCreatorTest_2180, MissingCreatorDoesNotCrashAndReturnsNullOrEmpty_2180) {
  const std::string pdf = MakeMinimalPdfWithInfo2180(nullptr);

  PopplerDocument* doc = NewDocFromPdfDataOrFail_2180(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* creator = poppler_document_get_creator(doc);

  // Behavior when absent may be NULL or an empty string depending on implementation.
  EXPECT_TRUE(creator == nullptr || creator[0] == '\0');

  if (creator) g_free(creator);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetCreatorTest_2180, NullDocumentTriggersCriticalAndReturnsNull_2180) {
  // g_return_val_if_fail should emit a critical warning.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
  gchar* creator = poppler_document_get_creator(nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(creator, nullptr);
}

TEST_F(PopplerDocumentGetCreatorTest_2180, NonDocumentInstanceTriggersCriticalAndReturnsNull_2180) {
  // Pass a GObject that is not a PopplerDocument.
  GObject* not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
  gchar* creator = poppler_document_get_creator(reinterpret_cast<PopplerDocument*>(not_a_doc));
  g_test_assert_expected_messages();

  EXPECT_EQ(creator, nullptr);

  g_object_unref(not_a_doc);
}