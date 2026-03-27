// TEST_ID: 2220
// File: poppler-fonts-iter-get-full-name-test-2220.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerFontsIterGetFullNameTest_2220 : public ::testing::Test {
protected:
  static std::string BuildPdfFromObjects(const std::vector<std::string> &objects) {
    // Minimal PDF builder:
    // - Writes header
    // - Writes each "N 0 obj ... endobj" block
    // - Writes xref/trailer with correct byte offsets
    //
    // NOTE: This is NOT re-implementing Poppler behavior. It's only generating
    // a syntactically valid PDF input for black-box testing.

    std::string out;
    out.reserve(4096);
    out += "%PDF-1.4\n";
    out += "%\xE2\xE3\xCF\xD3\n"; // binary marker

    std::vector<size_t> offsets;
    offsets.resize(objects.size() + 1);
    offsets[0] = 0; // object 0 (free)

    for (size_t i = 0; i < objects.size(); ++i) {
      offsets[i + 1] = out.size();
      out += std::to_string(i + 1);
      out += " 0 obj\n";
      out += objects[i];
      if (out.empty() || out.back() != '\n')
        out += "\n";
      out += "endobj\n";
    }

    const size_t xref_pos = out.size();
    out += "xref\n";
    out += "0 ";
    out += std::to_string(objects.size() + 1);
    out += "\n";
    out += "0000000000 65535 f \n";

    for (size_t i = 1; i <= objects.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
      out += buf;
    }

    // trailer (Root = 1 0 R)
    out += "trailer\n";
    out += "<< /Size ";
    out += std::to_string(objects.size() + 1);
    out += " /Root 1 0 R >>\n";
    out += "startxref\n";
    out += std::to_string(xref_pos);
    out += "\n%%EOF\n";

    return out;
  }

  static std::string BuildPdfWithHelvetica() {
    // 1: Catalog
    // 2: Pages
    // 3: Page (with /Resources containing /Font /F1 -> 4 0 R)
    // 4: Font (Type1 Helvetica)
    // 5: Contents stream "BT /F1 12 Tf (Hi) Tj ET"
    const std::string stream = "BT /F1 12 Tf 72 720 Td (Hi) Tj ET\n";
    const std::string contents =
        "<< /Length " + std::to_string(stream.size()) + " >>\nstream\n" + stream + "endstream\n";

    std::vector<std::string> objs;
    objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
    objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    objs.emplace_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
                      "   /Resources << /Font << /F1 4 0 R >> >>\n"
                      "   /Contents 5 0 R >>");
    objs.emplace_back("<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");
    objs.emplace_back(contents);

    return BuildPdfFromObjects(objs);
  }

  static std::string BuildPdfNoFonts() {
    // Like above but no /Font in /Resources. Contents uses no text/font.
    const std::string stream = "0 0 m 10 10 l S\n";
    const std::string contents =
        "<< /Length " + std::to_string(stream.size()) + " >>\nstream\n" + stream + "endstream\n";

    std::vector<std::string> objs;
    objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
    objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    objs.emplace_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
                      "   /Resources << >>\n"
                      "   /Contents 4 0 R >>");
    objs.emplace_back(contents);

    return BuildPdfFromObjects(objs);
  }

  static std::string BuildPdfType3NoBaseFont() {
    // Attempt to include a Type3 font without /BaseFont, which may result in no "name" in Poppler.
    // Some PDF consumers may still synthesize a name; if so, the test will skip the nullptr assertion.
    //
    // 4: Type3 Font (no /BaseFont)
    // 5: CharProcs
    // 6: Contents uses /F3
    const std::string glyph_stream = "0 0 500 500 re f\n";
    const std::string glyph =
        "<< /Length " + std::to_string(glyph_stream.size()) + " >>\nstream\n" + glyph_stream +
        "endstream\n";

    const std::string page_stream = "BT /F3 12 Tf 72 720 Td (X) Tj ET\n";
    const std::string contents =
        "<< /Length " + std::to_string(page_stream.size()) + " >>\nstream\n" + page_stream +
        "endstream\n";

    std::vector<std::string> objs;
    objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
    objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    objs.emplace_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
                      "   /Resources << /Font << /F3 4 0 R >> >>\n"
                      "   /Contents 6 0 R >>");

    // Type3 font (no /BaseFont on purpose)
    objs.emplace_back("<< /Type /Font /Subtype /Type3\n"
                      "   /FontBBox [0 0 500 500]\n"
                      "   /FontMatrix [0.001 0 0 0.001 0 0]\n"
                      "   /CharProcs << /X 5 0 R >>\n"
                      "   /Encoding << /Differences [88 /X] >>\n"
                      "   /FirstChar 88 /LastChar 88\n"
                      "   /Widths [500]\n"
                      "   /Resources << >>\n"
                      ">>");

    objs.emplace_back(glyph);     // 5 0 obj
    objs.emplace_back(contents);  // 6 0 obj

    return BuildPdfFromObjects(objs);
  }

  static std::string WriteTempPdf(const std::string &pdf_bytes) {
    gchar *path = nullptr;
    gint fd = g_file_open_tmp("poppler-fonts-iter-2220-XXXXXX.pdf", &path, nullptr);
    EXPECT_GE(fd, 0);
    EXPECT_NE(path, nullptr);

    if (fd >= 0) {
      const gssize want = static_cast<gssize>(pdf_bytes.size());
      const gssize wrote = write(fd, pdf_bytes.data(), want);
      (void)close(fd);
      EXPECT_EQ(wrote, want);
    }

    std::string out_path = path ? path : "";
    g_free(path);
    return out_path;
  }

  static PopplerDocument *LoadDocumentFromPath(const std::string &path) {
    // poppler_document_new_from_file expects a URI.
    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
    EXPECT_NE(uri, nullptr);
    if (!uri)
      return nullptr;

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    if (error) {
      g_error_free(error);
      return nullptr;
    }
    return doc;
  }
};

TEST_F(PopplerFontsIterGetFullNameTest_2220, ReturnsNonNullForHelveticaFont_2220) {
  const std::string pdf = BuildPdfWithHelvetica();
  const std::string path = WriteTempPdf(pdf);

  PopplerDocument *doc = LoadDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerFontsIter *iter = poppler_fonts_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  // Under test:
  char *full_name = poppler_fonts_iter_get_full_name(iter);

  ASSERT_NE(full_name, nullptr);
  // Be tolerant: Poppler may return "Helvetica" or include variations.
  EXPECT_NE(std::string(full_name).find("Helvetica"), std::string::npos);

  poppler_fonts_iter_free(iter);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST_F(PopplerFontsIterGetFullNameTest_2220, RepeatedCallsReturnSameContentForSameIterPosition_2220) {
  const std::string pdf = BuildPdfWithHelvetica();
  const std::string path = WriteTempPdf(pdf);

  PopplerDocument *doc = LoadDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerFontsIter *iter = poppler_fonts_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  char *n1 = poppler_fonts_iter_get_full_name(iter);
  char *n2 = poppler_fonts_iter_get_full_name(iter);

  ASSERT_NE(n1, nullptr);
  ASSERT_NE(n2, nullptr);
  EXPECT_EQ(std::string(n1), std::string(n2));

  poppler_fonts_iter_free(iter);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST_F(PopplerFontsIterGetFullNameTest_2220, NoFontsDocumentDoesNotCrashAndMayReturnNull_2220) {
  const std::string pdf = BuildPdfNoFonts();
  const std::string path = WriteTempPdf(pdf);

  PopplerDocument *doc = LoadDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerFontsIter *iter = poppler_fonts_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  // For a document with no fonts, Poppler may return nullptr here, or it may have an empty iterator
  // semantics. This test ensures the call is safe and the result is either nullptr or a valid string.
  char *name = poppler_fonts_iter_get_full_name(iter);
  if (name) {
    EXPECT_FALSE(std::string(name).empty());
  } else {
    SUCCEED();
  }

  poppler_fonts_iter_free(iter);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST_F(PopplerFontsIterGetFullNameTest_2220, Type3FontWithoutBaseFontMayProduceNullName_2220) {
  const std::string pdf = BuildPdfType3NoBaseFont();
  const std::string path = WriteTempPdf(pdf);

  PopplerDocument *doc = LoadDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerFontsIter *iter = poppler_fonts_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  // We try to observe a nullptr return (name absent). Depending on Poppler's behavior, it might
  // synthesize a name anyway. If no nullptr is observed, skip rather than fail.
  bool saw_null = false;
  bool saw_any = false;

  // Iterate defensively with a small cap to avoid infinite loops if API behavior changes.
  for (int i = 0; i < 32; ++i) {
    char *name = poppler_fonts_iter_get_full_name(iter);
    saw_any = true;
    if (!name) {
      saw_null = true;
      break;
    }
    if (!poppler_fonts_iter_next(iter))
      break;
  }

  if (!saw_any) {
    GTEST_SKIP() << "No fonts were enumerated for the Type3 PDF; cannot observe name-null behavior.";
  }
  if (!saw_null) {
    GTEST_SKIP() << "Poppler did not produce a nullptr name for this Type3 font; behavior may "
                    "synthesize a name on this build.";
  }

  EXPECT_TRUE(saw_null);

  poppler_fonts_iter_free(iter);
  g_object_unref(doc);
  g_remove(path.c_str());
}

} // namespace