// File: poppler-document-get-keywords-test-2178.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerDocumentGetKeywordsTest_2178 : public ::testing::Test {
protected:
  static std::string BuildMinimalPdfWithInfoDict(const std::string& info_dict_body) {
    // Objects:
    // 1 0: Catalog
    // 2 0: Pages
    // 3 0: Page
    // 4 0: Contents (empty)
    // 5 0: Info (caller-provided)
    std::vector<std::string> objs;
    objs.emplace_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
    objs.emplace_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
    objs.emplace_back(
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 1 1] /Contents 4 0 R /Resources << >> "
        ">>\nendobj\n");
    objs.emplace_back("4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n");

    std::string info_obj = "5 0 obj\n<< " + info_dict_body + " >>\nendobj\n";
    objs.emplace_back(info_obj);

    std::string header = "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

    // Assemble and compute xref offsets.
    std::vector<long> offsets;
    offsets.reserve(objs.size() + 1);
    offsets.push_back(0); // object 0

    std::string body;
    body.reserve(2048);
    long cur = static_cast<long>(header.size());
    for (const auto& obj : objs) {
      offsets.push_back(cur);
      body += obj;
      cur += static_cast<long>(obj.size());
    }

    std::ostringstream xref;
    xref << "xref\n";
    xref << "0 " << (objs.size() + 1) << "\n";
    // Free entry
    xref << "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      xref << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
    }

    std::ostringstream trailer;
    trailer << "trailer\n"
            << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R /Info 5 0 R >>\n";

    const std::string xref_str = xref.str();
    const std::string trailer_str = trailer.str();

    const long startxref = static_cast<long>(header.size() + body.size());
    std::ostringstream out;
    out << header << body << xref_str << trailer_str << "startxref\n" << startxref << "\n%%EOF\n";
    return out.str();
  }

  static PopplerDocument* NewDocFromPdfData(const std::string& pdf) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), /*password=*/nullptr, &error);
    if (!doc) {
      // Keep the failure observable in the test output, but don't assume error domain/code.
      if (error) {
        ADD_FAILURE() << "poppler_document_new_from_data failed: " << error->message;
        g_error_free(error);
      } else {
        ADD_FAILURE() << "poppler_document_new_from_data failed with no GError.";
      }
    } else if (error) {
      // Some APIs may return both doc and warning error; avoid leaking.
      g_error_free(error);
    }
    return doc;
  }
};

TEST_F(PopplerDocumentGetKeywordsTest_2178, NullDocumentReturnsNull_2178) {
  gchar* keywords = poppler_document_get_keywords(nullptr);
  EXPECT_EQ(keywords, nullptr);
}

TEST_F(PopplerDocumentGetKeywordsTest_2178, NonDocumentInstanceReturnsNull_2178) {
  GObject* not_a_doc = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(not_a_doc, nullptr);

  gchar* keywords = poppler_document_get_keywords(reinterpret_cast<PopplerDocument*>(not_a_doc));
  EXPECT_EQ(keywords, nullptr);

  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetKeywordsTest_2178, ReturnsKeywordsWhenPresent_2178) {
  const std::string pdf = BuildMinimalPdfWithInfoDict("/Producer (unit-test) /Keywords (hello world)");
  PopplerDocument* doc = NewDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* keywords = poppler_document_get_keywords(doc);
  ASSERT_NE(keywords, nullptr);
  EXPECT_STREQ(keywords, "hello world");

  g_free(keywords);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetKeywordsTest_2178, EmptyKeywordsDoesNotCrashAndIsConsistent_2178) {
  const std::string pdf = BuildMinimalPdfWithInfoDict("/Producer (unit-test) /Keywords ()");
  PopplerDocument* doc = NewDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* keywords = poppler_document_get_keywords(doc);

  // Black-box friendly: accept either NULL or empty string, but it must not crash.
  if (keywords) {
    EXPECT_STREQ(keywords, "");
    g_free(keywords);
  } else {
    SUCCEED();
  }

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetKeywordsTest_2178, PdfDocEncodingOctalEscapeIsConvertedToUtf8_2178) {
  // PDF literal string with octal escape for é: \351.
  const std::string pdf = BuildMinimalPdfWithInfoDict("/Producer (unit-test) /Keywords (caf\\351)");
  PopplerDocument* doc = NewDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  gchar* keywords = poppler_document_get_keywords(doc);
  ASSERT_NE(keywords, nullptr);

  // Must be valid UTF-8, and should match the expected conversion if supported.
  EXPECT_TRUE(g_utf8_validate(keywords, -1, nullptr));

  // Prefer exact match when conversion is performed as expected.
  // If an implementation returns a different but still valid UTF-8 representation, this assertion will
  // expose the observable behavior difference (intentional for a black-box test).
  EXPECT_STREQ(keywords, u8"café");

  g_free(keywords);
  g_object_unref(doc);
}

} // namespace