// File: poppler-document-has-javascript-test-2208.cc
#include <gtest/gtest.h>

#include <poppler.h>
#include <glib.h>

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

// Build a minimal, valid PDF with 1 blank page.
// If with_js == true, adds a Catalog /OpenAction JavaScript action.
static std::string BuildMinimalPdf(bool with_js) {
  // Objects (as plain strings). We'll compute xref offsets precisely.
  // PDF structure:
  // 1 0 obj: Catalog (optionally /OpenAction 5 0 R)
  // 2 0 obj: Pages
  // 3 0 obj: Page
  // 4 0 obj: Contents (empty stream)
  // 5 0 obj: JavaScript action (only if with_js)
  std::vector<std::string> objs;

  if (with_js) {
    objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R /OpenAction 5 0 R >>\nendobj\n");
  } else {
    objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  }

  objs.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources << >>\n"
      "   /Contents 4 0 R >>\n"
      "endobj\n");

  // Empty content stream.
  objs.push_back("4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n");

  if (with_js) {
    // Keep JS payload simple ASCII for robust parsing.
    objs.push_back(
        "5 0 obj\n"
        "<< /S /JavaScript /JS (app.alert\\(Hi\\)) >>\n"
        "endobj\n");
  }

  std::string pdf;
  pdf.reserve(1024);

  // Header
  pdf += "%PDF-1.4\n";
  // Binary comment line (recommended by spec/readers; harmless).
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // Track byte offsets of each object.
  // xref requires entry 0 + all objects up to max obj number.
  std::vector<size_t> offsets;
  offsets.resize(objs.size() + 1, 0);  // offsets[0] unused for obj 0

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = pdf.size();
    pdf += objs[i];
  }

  const size_t xref_offset = pdf.size();

  // Build xref
  // We generated object numbers 1..N sequentially.
  const int num_objs = static_cast<int>(objs.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(num_objs + 1) + "\n";
  // Object 0: free
  pdf += "0000000000 65535 f \n";
  for (int objno = 1; objno <= num_objs; ++objno) {
    char line[32];
    // 10-digit, zero-padded offset
    std::snprintf(line, sizeof(line), "%010lu 00000 n \n",
                  static_cast<unsigned long>(offsets[objno]));
    pdf += line;
  }

  // Trailer
  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(num_objs + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static PopplerDocument* NewDocFromDataOrFail(const std::string& pdf_bytes) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_data(
      pdf_bytes.data(), static_cast<int>(pdf_bytes.size()), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = "poppler_document_new_from_data failed";
    if (error && error->message) {
      msg += ": ";
      msg += error->message;
    }
    if (error) {
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) {
    std::string msg = "Unexpected GError from poppler_document_new_from_data: ";
    msg += (error->message ? error->message : "(null)");
    g_error_free(error);
    ADD_FAILURE() << msg;
    g_object_unref(doc);
    return nullptr;
  }
  return doc;
}

class PopplerDocumentHasJavascriptTest_2208 : public ::testing::Test {
 protected:
  void TearDown() override {
    // No global teardown required.
  }
};

TEST_F(PopplerDocumentHasJavascriptTest_2208, ReturnsFalseForValidDocumentWithoutJavascript_2208) {
  const std::string pdf = BuildMinimalPdf(/*with_js=*/false);
  PopplerDocument* doc = NewDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  const gboolean has_js = poppler_document_has_javascript(doc);
  EXPECT_FALSE(has_js);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentHasJavascriptTest_2208, ReturnsTrueForValidDocumentWithJavascriptOpenAction_2208) {
  const std::string pdf = BuildMinimalPdf(/*with_js=*/true);
  PopplerDocument* doc = NewDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  const gboolean has_js = poppler_document_has_javascript(doc);
  EXPECT_TRUE(has_js);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentHasJavascriptTest_2208, ReturnsFalseForNullDocumentPointer_2208) {
  // Observable behavior for invalid input: returns FALSE (and may log a critical).
  const gboolean has_js = poppler_document_has_javascript(nullptr);
  EXPECT_FALSE(has_js);
}

}  // namespace