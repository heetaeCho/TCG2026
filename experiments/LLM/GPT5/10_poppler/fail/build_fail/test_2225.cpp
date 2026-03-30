// File: poppler_fonts_iter_get_encoding_test_2225.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Builds a minimal, valid single-page PDF that uses a single Type1 font (/Helvetica).
// If include_encoding is true, the font dictionary contains `/Encoding /WinAnsiEncoding`.
static std::string BuildSimplePdfWithType1Font(bool include_encoding) {
  const std::string stream_data = "BT /F1 12 Tf 72 72 Td (Hi) Tj ET\n";
  const int stream_len = static_cast<int>(stream_data.size());

  std::vector<std::string> objs;
  objs.reserve(6);

  // 1 0 obj: Catalog
  objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

  // 2 0 obj: Pages
  objs.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

  // 3 0 obj: Page
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources << /Font << /F1 4 0 R >> >>\n"
      "   /Contents 5 0 R >>\n"
      "endobj\n");

  // 4 0 obj: Font
  std::ostringstream font_obj;
  font_obj << "4 0 obj\n"
           << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica";
  if (include_encoding) {
    font_obj << " /Encoding /WinAnsiEncoding";
  }
  font_obj << " >>\nendobj\n";
  objs.push_back(font_obj.str());

  // 5 0 obj: Contents stream
  std::ostringstream contents_obj;
  contents_obj << "5 0 obj\n"
               << "<< /Length " << stream_len << " >>\n"
               << "stream\n"
               << stream_data
               << "endstream\n"
               << "endobj\n";
  objs.push_back(contents_obj.str());

  // Assemble header + objects while tracking offsets.
  std::string pdf;
  pdf.reserve(2048);
  pdf += "%PDF-1.4\n";

  // Offsets for xref: object 0 is special.
  std::vector<long> offsets(6, 0);
  offsets[0] = 0;

  for (int i = 1; i <= 5; ++i) {
    offsets[i] = static_cast<long>(pdf.size());
    pdf += objs[static_cast<size_t>(i - 1)];
  }

  const long xref_pos = static_cast<long>(pdf.size());

  // xref table
  std::ostringstream xref;
  xref << "xref\n";
  xref << "0 6\n";
  xref << "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    xref << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
  }
  pdf += xref.str();

  // trailer
  std::ostringstream trailer;
  trailer << "trailer\n"
          << "<< /Size 6 /Root 1 0 R >>\n"
          << "startxref\n"
          << xref_pos << "\n"
          << "%%EOF\n";
  pdf += trailer.str();

  return pdf;
}

class PopplerFontsIterGetEncodingTest_2225 : public ::testing::Test {
 protected:
  static PopplerDocument* NewDocumentFromPdfDataOrFail(const std::string& pdf) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), /*password=*/nullptr, &error);
    if (!doc) {
      std::string msg = "poppler_document_new_from_data failed";
      if (error && error->message) {
        msg += ": ";
        msg += error->message;
      }
      if (error) g_error_free(error);
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (error) {
      // If Poppler returned a document, error should typically be null; keep it strict.
      std::string msg = error->message ? error->message : "(unknown)";
      g_error_free(error);
      ADD_FAILURE() << "Unexpected GError set: " << msg;
      g_object_unref(doc);
      return nullptr;
    }
    return doc;
  }

  static PopplerFontsIter* ScanFontsOrFail(PopplerDocument* doc, int n_pages) {
    PopplerFontInfo* font_info = poppler_font_info_new(doc);
    if (!font_info) {
      ADD_FAILURE() << "poppler_font_info_new returned nullptr";
      return nullptr;
    }

    PopplerFontsIter* iter = nullptr;
    const gboolean ok = poppler_font_info_scan(font_info, n_pages, &iter);
    poppler_font_info_free(font_info);

    if (!ok || !iter) {
      ADD_FAILURE() << "poppler_font_info_scan did not produce an iterator";
      if (iter) poppler_fonts_iter_free(iter);
      return nullptr;
    }
    return iter;
  }
};

}  // namespace

TEST_F(PopplerFontsIterGetEncodingTest_2225, ReturnsExpectedEncodingWhenExplicitInPdf_2225) {
  const std::string pdf = BuildSimplePdfWithType1Font(/*include_encoding=*/true);
  PopplerDocument* doc = NewDocumentFromPdfDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFontsIter* iter = ScanFontsOrFail(doc, /*n_pages=*/1);
  ASSERT_NE(iter, nullptr);

  const char* enc = poppler_fonts_iter_get_encoding(iter);
  ASSERT_NE(enc, nullptr);
  EXPECT_STRNE(enc, "");

  // Because the PDF explicitly specifies /WinAnsiEncoding, we expect Poppler to report it.
  EXPECT_STREQ(enc, "WinAnsiEncoding");

  poppler_fonts_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerFontsIterGetEncodingTest_2225, PointerIsStableAcrossRepeatedCallsWithoutAdvancing_2225) {
  const std::string pdf = BuildSimplePdfWithType1Font(/*include_encoding=*/true);
  PopplerDocument* doc = NewDocumentFromPdfDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFontsIter* iter = ScanFontsOrFail(doc, /*n_pages=*/1);
  ASSERT_NE(iter, nullptr);

  const char* enc1 = poppler_fonts_iter_get_encoding(iter);
  const char* enc2 = poppler_fonts_iter_get_encoding(iter);

  // Observable contract from the implementation: a non-empty encoding returns encoding.c_str().
  // So repeated calls without changing the iterator should yield the same pointer.
  ASSERT_NE(enc1, nullptr);
  ASSERT_NE(enc2, nullptr);
  EXPECT_EQ(enc1, enc2);
  EXPECT_STREQ(enc1, "WinAnsiEncoding");

  poppler_fonts_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerFontsIterGetEncodingTest_2225, IterationProducesNullOrNonEmptyEncodingNeverEmptyString_2225) {
  const std::string pdf = BuildSimplePdfWithType1Font(/*include_encoding=*/true);
  PopplerDocument* doc = NewDocumentFromPdfDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFontsIter* iter = ScanFontsOrFail(doc, /*n_pages=*/1);
  ASSERT_NE(iter, nullptr);

  // Walk all discovered fonts; for each one, encoding is either nullptr or a non-empty C string.
  int visited = 0;
  do {
    const char* enc = poppler_fonts_iter_get_encoding(iter);
    if (enc) {
      EXPECT_STRNE(enc, "");
    }
    ++visited;
  } while (poppler_fonts_iter_next(iter));

  EXPECT_GE(visited, 1);

  poppler_fonts_iter_free(iter);
  g_object_unref(doc);
}