// poppler_fonts_iter_get_file_name_test_2223.cc
//
// Unit tests for:
//   const char *poppler_fonts_iter_get_file_name(PopplerFontsIter *iter);
//
// Constraints note:
// - Treat implementation as a black box.
// - Use only observable behavior via the public Poppler GLib API.
// - Do not access private/internal state of PopplerFontsIter/FontInfo.
//
// Build assumptions:
// - poppler-glib headers are available (e.g., <poppler.h>).
// - gtest is available.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace {

class PopplerFontsIterGetFileNameTest_2223 : public ::testing::Test {
protected:
  static std::optional<std::string> WriteTempFile(const std::string& bytes,
                                                 const char* suffix) {
    // Create a temp file path pattern.
    std::string tmpl = std::string(g_get_tmp_dir()) + G_DIR_SEPARATOR_S + "poppler_ut_XXXXXX";
    std::vector<char> pattern(tmpl.begin(), tmpl.end());
    pattern.push_back('\0');

    int fd = g_mkstemp(pattern.data());
    if (fd < 0) return std::nullopt;

    // Close FD and write via std::ofstream for simplicity.
    close(fd);

    std::string path(pattern.data());
    if (suffix && *suffix) path += suffix;

    // If suffix requested, rename the file.
    if (path != std::string(pattern.data())) {
      if (g_rename(pattern.data(), path.c_str()) != 0) {
        g_remove(pattern.data());
        return std::nullopt;
      }
    }

    std::ofstream out(path, std::ios::binary);
    if (!out) {
      g_remove(path.c_str());
      return std::nullopt;
    }
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();
    if (!out) {
      g_remove(path.c_str());
      return std::nullopt;
    }

    return path;
  }

  static std::optional<std::vector<unsigned char>> ReadFileBytes(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return std::nullopt;
    in.seekg(0, std::ios::end);
    std::streamsize sz = in.tellg();
    if (sz <= 0) return std::nullopt;
    in.seekg(0, std::ios::beg);
    std::vector<unsigned char> buf(static_cast<size_t>(sz));
    in.read(reinterpret_cast<char*>(buf.data()), sz);
    if (!in) return std::nullopt;
    return buf;
  }

  struct PdfObj {
    int num;
    std::string body;  // must include trailing newline if desired
  };

  static std::string BuildPdf(const std::vector<PdfObj>& objs, int rootObjNum) {
    // Minimal PDF builder that calculates xref offsets.
    std::string pdf;
    pdf += "%PDF-1.4\n";
    // Binary comment (recommended).
    pdf += "%\xE2\xE3\xCF\xD3\n";

    // Offsets are byte offsets from beginning of file.
    std::vector<long> offsets;
    offsets.resize(static_cast<size_t>(rootObjNum) + 50, -1); // oversized; we only use present ids

    auto append_obj = [&](int num, const std::string& body) {
      // Record offset at start of "n 0 obj"
      long off = static_cast<long>(pdf.size());
      if (num >= 0 && static_cast<size_t>(num) < offsets.size()) offsets[static_cast<size_t>(num)] = off;
      pdf += std::to_string(num) + " 0 obj\n";
      pdf += body;
      if (!body.empty() && body.back() != '\n') pdf += "\n";
      pdf += "endobj\n";
    };

    int maxObj = 0;
    for (const auto& o : objs) {
      maxObj = std::max(maxObj, o.num);
      append_obj(o.num, o.body);
    }

    long xrefPos = static_cast<long>(pdf.size());
    pdf += "xref\n";
    pdf += "0 " + std::to_string(maxObj + 1) + "\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= maxObj; ++i) {
      long off = (i >= 0 && static_cast<size_t>(i) < offsets.size()) ? offsets[static_cast<size_t>(i)] : -1;
      if (off < 0) {
        // Unused object slot.
        pdf += "0000000000 65535 f \n";
      } else {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off);
        pdf += buf;
      }
    }
    pdf += "trailer\n";
    pdf += "<< /Size " + std::to_string(maxObj + 1) + " /Root " + std::to_string(rootObjNum) + " 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xrefPos) + "\n";
    pdf += "%%EOF\n";
    return pdf;
  }

  static std::string MakePdfWithStandard14FontHelvetica() {
    // A single-page PDF using /Helvetica (not embedded).
    const std::string contents = "BT /F1 18 Tf 20 100 Td (Hello) Tj ET\n";
    const int contentsLen = static_cast<int>(contents.size());

    std::vector<PdfObj> objs;
    objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
    objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});
    objs.push_back({3,
                    "<< /Type /Page /Parent 2 0 R "
                    "/MediaBox [0 0 200 200] "
                    "/Resources << /Font << /F1 4 0 R >> >> "
                    "/Contents 5 0 R >>"});
    objs.push_back({4, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"});
    objs.push_back({5, "<< /Length " + std::to_string(contentsLen) + " >>\nstream\n" + contents + "endstream"});
    return BuildPdf(objs, /*rootObjNum=*/1);
  }

  static std::optional<std::string> MakePdfWithEmbeddedTrueTypeFontFromPath(const std::string& ttfPath) {
    auto bytesOpt = ReadFileBytes(ttfPath);
    if (!bytesOpt) return std::nullopt;
    const auto& bytes = *bytesOpt;

    // Put the font file bytes directly in a stream.
    // Provide a basic TrueType font dictionary with a FontDescriptor and widths.
    //
    // NOTE: We intentionally keep this minimal; if Poppler rejects it, the test will
    // skip when no non-null file name is discoverable.
    const int fontFileLen = static_cast<int>(bytes.size());

    std::string fontFileStream;
    fontFileStream.reserve(bytes.size() + 256);
    fontFileStream += "<< /Length " + std::to_string(fontFileLen) + " >>\nstream\n";
    fontFileStream.append(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    fontFileStream += "\nendstream";

    // Page contents uses F1.
    const std::string contents = "BT /F1 18 Tf 20 100 Td (Hello) Tj ET\n";
    const int contentsLen = static_cast<int>(contents.size());

    // A simple widths array for ASCII range 32..32 (space only) to keep it short.
    // Many readers tolerate simplistic widths; Poppler may still parse enough for font listing.
    const std::string widths = "[250]";

    std::vector<PdfObj> objs;
    // 1 Catalog, 2 Pages, 3 Page, 4 Font, 5 Contents, 6 FontFile2 stream, 7 FontDescriptor
    objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
    objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});
    objs.push_back({3,
                    "<< /Type /Page /Parent 2 0 R "
                    "/MediaBox [0 0 200 200] "
                    "/Resources << /Font << /F1 4 0 R >> >> "
                    "/Contents 5 0 R >>"});

    // Font dictionary
    // BaseFont name is arbitrary; use a safe name.
    objs.push_back({4,
                    "<< /Type /Font /Subtype /TrueType "
                    "/BaseFont /DejaVuSans "
                    "/FirstChar 32 /LastChar 32 "
                    "/Widths " + widths + " "
                    "/FontDescriptor 7 0 R "
                    "/Encoding /WinAnsiEncoding >>"});

    // Contents stream
    objs.push_back({5, "<< /Length " + std::to_string(contentsLen) + " >>\nstream\n" + contents + "endstream"});

    // FontFile2 stream
    objs.push_back({6, fontFileStream});

    // FontDescriptor
    // Provide minimal required-ish entries.
    objs.push_back({7,
                    "<< /Type /FontDescriptor "
                    "/FontName /DejaVuSans "
                    "/Flags 4 "
                    "/FontBBox [0 -200 1000 900] "
                    "/ItalicAngle 0 "
                    "/Ascent 800 "
                    "/Descent -200 "
                    "/CapHeight 700 "
                    "/StemV 80 "
                    "/FontFile2 6 0 R >>"});

    return BuildPdf(objs, /*rootObjNum=*/1);
  }

  static PopplerDocument* LoadDocumentFromPdfBytes(const std::string& pdfBytes, GError** error) {
    auto pathOpt = WriteTempFile(pdfBytes, ".pdf");
    if (!pathOpt) return nullptr;

    gchar* uri = g_filename_to_uri(pathOpt->c_str(), /*hostname=*/nullptr, error);
    if (!uri) {
      g_remove(pathOpt->c_str());
      return nullptr;
    }

    PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, error);

    g_free(uri);
    // Keep the file on disk until after Poppler loads; safe to remove after.
    g_remove(pathOpt->c_str());
    return doc;
  }

  static PopplerFontsIter* NewFontsIterOrSkip(PopplerDocument* doc) {
    // Public constructor in poppler-glib.
    PopplerFontsIter* it = poppler_fonts_iter_new(doc);
    return it;
  }

  static bool IterAdvance(PopplerFontsIter* it) {
    // Public API: returns TRUE if moved to next, FALSE if no more.
    return poppler_fonts_iter_next(it);
  }
};

TEST_F(PopplerFontsIterGetFileNameTest_2223, Standard14FontReturnsNull_2223) {
  GError* error = nullptr;
  const std::string pdf = MakePdfWithStandard14FontHelvetica();
  PopplerDocument* doc = LoadDocumentFromPdfBytes(pdf, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "Failed to load PDF");
  if (error) g_error_free(error), error = nullptr;

  PopplerFontsIter* it = NewFontsIterOrSkip(doc);
  ASSERT_NE(it, nullptr);

  // For a standard 14 font like Helvetica, Poppler commonly reports no backing font file.
  const char* file = poppler_fonts_iter_get_file_name(it);
  EXPECT_EQ(file, nullptr);

  poppler_fonts_iter_free(it);
  g_object_unref(doc);
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, EmbeddedTrueTypeMayReturnNonNullAndIsStableAcrossCalls_2223) {
  // Try a common system font; skip if not present.
  const char* kCandidates[] = {
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "/usr/share/fonts/TTF/DejaVuSans.ttf",
      "/usr/share/fonts/dejavu/DejaVuSans.ttf",
  };

  std::string fontPath;
  for (const char* p : kCandidates) {
    if (g_file_test(p, G_FILE_TEST_EXISTS) && g_file_test(p, G_FILE_TEST_IS_REGULAR)) {
      fontPath = p;
      break;
    }
  }
  if (fontPath.empty()) {
    GTEST_SKIP() << "No suitable TTF found on this system to embed into a test PDF.";
  }

  auto pdfOpt = MakePdfWithEmbeddedTrueTypeFontFromPath(fontPath);
  if (!pdfOpt) {
    GTEST_SKIP() << "Could not build embedded-font PDF from system TTF.";
  }

  GError* error = nullptr;
  PopplerDocument* doc = LoadDocumentFromPdfBytes(*pdfOpt, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "Failed to load embedded-font PDF");
  if (error) g_error_free(error), error = nullptr;

  PopplerFontsIter* it = NewFontsIterOrSkip(doc);
  ASSERT_NE(it, nullptr);

  // Iterate a few fonts and look for one that exposes a non-null file name.
  // (Different platforms/configurations may list additional fonts.)
  const char* found = nullptr;
  for (int i = 0; i < 32; ++i) {
    const char* file = poppler_fonts_iter_get_file_name(it);
    if (file && *file) {
      found = file;
      break;
    }
    if (!IterAdvance(it)) break;
  }

  if (!found) {
    poppler_fonts_iter_free(it);
    g_object_unref(doc);
    GTEST_SKIP() << "No font in this document exposed a non-null file name on this build/config.";
  }

  // Observable behavior: repeated calls should return a consistent string while the iterator lives.
  const char* again = poppler_fonts_iter_get_file_name(it);
  ASSERT_NE(again, nullptr);
  EXPECT_STREQ(again, found);
  EXPECT_NE(std::strlen(found), 0u);

  poppler_fonts_iter_free(it);
  g_object_unref(doc);
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, MultipleCallsWithoutAdvancingAreConsistentForNullCase_2223) {
  GError* error = nullptr;
  const std::string pdf = MakePdfWithStandard14FontHelvetica();
  PopplerDocument* doc = LoadDocumentFromPdfBytes(pdf, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "Failed to load PDF");
  if (error) g_error_free(error), error = nullptr;

  PopplerFontsIter* it = NewFontsIterOrSkip(doc);
  ASSERT_NE(it, nullptr);

  const char* f1 = poppler_fonts_iter_get_file_name(it);
  const char* f2 = poppler_fonts_iter_get_file_name(it);
  const char* f3 = poppler_fonts_iter_get_file_name(it);

  EXPECT_EQ(f1, nullptr);
  EXPECT_EQ(f2, nullptr);
  EXPECT_EQ(f3, nullptr);

  poppler_fonts_iter_free(it);
  g_object_unref(doc);
}

} // namespace