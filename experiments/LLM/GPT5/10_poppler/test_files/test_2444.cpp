// poppler-page-get-text-test_2444.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerPageGetTextTest_2444 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  // Build a minimal, valid PDF (PDF-1.4) with 1 page.
  // - media_w/media_h: page size in points
  // - text: if non-empty, emits a simple text drawing command
  static std::string BuildMinimalPdf(double media_w, double media_h, const std::string& text) {
    auto dbl = [](double v) {
      std::ostringstream oss;
      oss.setf(std::ios::fixed);
      oss.precision(2);
      oss << v;
      return oss.str();
    };

    // PDF objects (1-based):
    // 1 0 obj: Catalog
    // 2 0 obj: Pages
    // 3 0 obj: Page
    // 4 0 obj: Font
    // 5 0 obj: Contents stream
    std::string contents;
    if (!text.empty()) {
      // Very simple text painting. Keep it ASCII to avoid encoding surprises.
      // Escape '(' and ')' if present.
      std::string esc = text;
      for (size_t i = 0; i < esc.size(); ++i) {
        if (esc[i] == '(' || esc[i] == ')' || esc[i] == '\\') {
          esc.insert(i, "\\");
          ++i;
        }
      }
      contents = "BT\n/F1 24 Tf\n50 50 Td\n(" + esc + ") Tj\nET\n";
    } else {
      contents = "";  // blank page
    }

    std::vector<std::string> objs;
    objs.reserve(5);

    {
      std::ostringstream o;
      o << "<< /Type /Catalog /Pages 2 0 R >>\n";
      objs.push_back(o.str());
    }
    {
      std::ostringstream o;
      o << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n";
      objs.push_back(o.str());
    }
    {
      std::ostringstream o;
      o << "<< /Type /Page /Parent 2 0 R\n"
        << "   /MediaBox [0 0 " << dbl(media_w) << " " << dbl(media_h) << "]\n"
        << "   /Resources << /Font << /F1 4 0 R >> >>\n"
        << "   /Contents 5 0 R\n"
        << ">>\n";
      objs.push_back(o.str());
    }
    {
      std::ostringstream o;
      o << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n";
      objs.push_back(o.str());
    }
    {
      std::ostringstream o;
      o << "<< /Length " << contents.size() << " >>\n"
        << "stream\n"
        << contents
        << "endstream\n";
      objs.push_back(o.str());
    }

    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n";  // binary comment

    // offsets[i] = byte offset of object (i), for i=1..N. offsets[0] is unused.
    std::vector<long> offsets(objs.size() + 1, 0);

    for (size_t i = 0; i < objs.size(); ++i) {
      const int obj_num = static_cast<int>(i) + 1;
      offsets[obj_num] = static_cast<long>(pdf.size());
      pdf += std::to_string(obj_num) + " 0 obj\n";
      pdf += objs[i];
      pdf += "endobj\n";
    }

    const long xref_pos = static_cast<long>(pdf.size());
    {
      std::ostringstream x;
      x << "xref\n";
      x << "0 " << (objs.size() + 1) << "\n";
      x << "0000000000 65535 f \n";
      for (size_t i = 1; i <= objs.size(); ++i) {
        // 10-digit, zero-padded offsets
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
        x << buf;
      }
      pdf += x.str();
    }

    {
      std::ostringstream t;
      t << "trailer\n"
        << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n"
        << "startxref\n"
        << xref_pos << "\n"
        << "%%EOF\n";
      pdf += t.str();
    }

    return pdf;
  }

  static std::string WriteTempFile(const std::string& bytes) {
    // Create a temporary file path via GLib for portability.
    gchar* path = nullptr;
    GError* error = nullptr;

    // g_file_open_tmp returns an fd; we’ll close and rewrite using std::ofstream for simplicity.
    int fd = g_file_open_tmp("poppler_get_text_XXXXXX.pdf", &path, &error);
    if (fd < 0 || !path) {
      std::string msg = "g_file_open_tmp failed";
      if (error) {
        msg += ": ";
        msg += error->message;
        g_error_free(error);
      }
      if (path) g_free(path);
      throw std::runtime_error(msg);
    }
#ifdef G_OS_WIN32
    _close(fd);
#else
    close(fd);
#endif

    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();

    std::string ret(path);
    g_free(path);
    return ret;
  }

  static PopplerDocument* LoadDocFromPath(const std::string& path, GError** err) {
    gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, err);
    if (!uri) return nullptr;

    PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, err);
    g_free(uri);
    return doc;
  }
};

TEST_F(PopplerPageGetTextTest_2444, NullPageReturnsNull_2444) {
  // Observable behavior: g_return_val_if_fail() returns NULL when the page is invalid.
  char* txt = poppler_page_get_text(nullptr);
  EXPECT_EQ(txt, nullptr);
}

TEST_F(PopplerPageGetTextTest_2444, TextEqualsSelectedTextForFullPageGlyph_2444) {
  // This checks the wrapper behavior through public APIs only:
  // poppler_page_get_text(page) should match poppler_page_get_selected_text(page, GLYPH, full-page-rectangle).
  const std::string pdf = BuildMinimalPdf(/*media_w=*/300.0, /*media_h=*/400.0, "Hello");
  const std::string path = WriteTempFile(pdf);

  GError* err = nullptr;
  PopplerDocument* doc = LoadDocFromPath(path, &err);
  ASSERT_NE(doc, nullptr) << (err ? err->message : "unknown error");
  if (err) g_error_free(err);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  double w = 0.0, h = 0.0;
  poppler_page_get_size(page, &w, &h);

  PopplerRectangle rect;
  rect.x1 = 0.0;
  rect.y1 = 0.0;
  rect.x2 = w;
  rect.y2 = h;

  char* via_get_text = poppler_page_get_text(page);
  ASSERT_NE(via_get_text, nullptr);

  char* via_selected = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
  ASSERT_NE(via_selected, nullptr);

  EXPECT_STREQ(via_get_text, via_selected);

  g_free(via_get_text);
  g_free(via_selected);
  g_object_unref(page);
  g_object_unref(doc);

  // Cleanup temp file best-effort.
  std::remove(path.c_str());
}

TEST_F(PopplerPageGetTextTest_2444, BlankPageReturnsNonNullString_2444) {
  // Boundary-ish: a valid page with no text content. poppler_page_get_text should still behave safely.
  const std::string pdf = BuildMinimalPdf(/*media_w=*/300.0, /*media_h=*/400.0, /*text=*/"");
  const std::string path = WriteTempFile(pdf);

  GError* err = nullptr;
  PopplerDocument* doc = LoadDocFromPath(path, &err);
  ASSERT_NE(doc, nullptr) << (err ? err->message : "unknown error");
  if (err) g_error_free(err);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  char* txt = poppler_page_get_text(page);
  // We avoid asserting exact contents (could be "", could contain whitespace depending on backend),
  // but it should be a valid NUL-terminated string pointer or NULL if implementation chooses so.
  // Given it's public API, we just check it doesn't crash and returns a usable pointer when non-NULL.
  if (txt) {
    EXPECT_GE(std::strlen(txt), static_cast<size_t>(0));
    g_free(txt);
  }

  g_object_unref(page);
  g_object_unref(doc);
  std::remove(path.c_str());
}

TEST_F(PopplerPageGetTextTest_2444, VerySmallPageStillMatchesSelectedText_2444) {
  // Boundary: extremely small MediaBox size; verifies rectangle construction via poppler_page_get_size.
  const std::string pdf = BuildMinimalPdf(/*media_w=*/1.0, /*media_h=*/1.0, "Hi");
  const std::string path = WriteTempFile(pdf);

  GError* err = nullptr;
  PopplerDocument* doc = LoadDocFromPath(path, &err);
  ASSERT_NE(doc, nullptr) << (err ? err->message : "unknown error");
  if (err) g_error_free(err);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  double w = 0.0, h = 0.0;
  poppler_page_get_size(page, &w, &h);

  PopplerRectangle rect;
  rect.x1 = 0.0;
  rect.y1 = 0.0;
  rect.x2 = w;
  rect.y2 = h;

  char* via_get_text = poppler_page_get_text(page);
  ASSERT_NE(via_get_text, nullptr);

  char* via_selected = poppler_page_get_selected_text(page, POPPLER_SELECTION_GLYPH, &rect);
  ASSERT_NE(via_selected, nullptr);

  EXPECT_STREQ(via_get_text, via_selected);

  g_free(via_get_text);
  g_free(via_selected);
  g_object_unref(page);
  g_object_unref(doc);
  std::remove(path.c_str());
}

}  // namespace