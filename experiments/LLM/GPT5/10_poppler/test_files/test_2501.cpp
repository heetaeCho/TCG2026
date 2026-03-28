// poppler-page-get-text-layout-for-area-test_2501.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string BuildSimpleOnePagePdfWithText(const std::string &text) {
  // Minimal, valid PDF with one page and a single text drawing operation.
  // We generate correct xref offsets programmatically.
  //
  // Page size: US Letter (612x792). Text at (72, 720).
  std::vector<std::string> obj;
  obj.reserve(6);

  obj.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

  obj.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  obj.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R\n"
      "   /MediaBox [0 0 612 792]\n"
      "   /Resources << /Font << /F1 4 0 R >> >>\n"
      "   /Contents 5 0 R\n"
      ">>\n"
      "endobj\n");

  obj.push_back(
      "4 0 obj\n"
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
      "endobj\n");

  // Escape parentheses and backslashes for a literal string in PDF.
  auto escape_pdf_literal = [](const std::string &in) {
    std::string out;
    out.reserve(in.size());
    for (char c : in) {
      if (c == '\\' || c == '(' || c == ')') out.push_back('\\');
      out.push_back(c);
    }
    return out;
  };

  const std::string escaped = escape_pdf_literal(text);
  std::ostringstream content;
  content << "BT\n"
          << "/F1 24 Tf\n"
          << "72 720 Td\n"
          << "(" << escaped << ") Tj\n"
          << "ET\n";

  const std::string content_str = content.str();
  std::ostringstream contents_obj;
  contents_obj << "5 0 obj\n"
               << "<< /Length " << content_str.size() << " >>\n"
               << "stream\n"
               << content_str
               << "endstream\n"
               << "endobj\n";
  obj.push_back(contents_obj.str());

  // Assemble file with xref.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.resize(6, 0);

  // Object 0 is the free object.
  offsets[0] = 0;

  for (int i = 1; i <= 5; ++i) {
    offsets[i] = static_cast<long>(pdf.tellp());
    pdf << obj[i - 1];
  }

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n"
      << "0 6\n"
      << "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n"
      << "<< /Size 6 /Root 1 0 R >>\n"
      << "startxref\n"
      << xref_pos << "\n"
      << "%%EOF\n";

  return pdf.str();
}

static std::string WriteTempPdfFile_2501(const std::string &pdf_bytes) {
  // Create a temporary file in the system temp dir.
  gchar *tmp_name = nullptr;
  int fd = g_file_open_tmp("poppler_gtest_2501_XXXXXX.pdf", &tmp_name, nullptr);
  if (fd < 0 || tmp_name == nullptr) {
    if (tmp_name) g_free(tmp_name);
    return {};
  }

  // Write bytes and close.
  FILE *f = fdopen(fd, "wb");
  if (!f) {
    close(fd);
    g_free(tmp_name);
    return {};
  }
  fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
  fclose(f); // closes fd

  std::string path(tmp_name);
  g_free(tmp_name);
  return path;
}

class PopplerPageGetTextLayoutForAreaTest_2501 : public ::testing::Test {
protected:
  void SetUp() override {
    const std::string pdf = BuildSimpleOnePagePdfWithText("Hello World");
    pdf_path_ = WriteTempPdfFile_2501(pdf);
    ASSERT_FALSE(pdf_path_.empty());

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(pdf_path_.c_str(), nullptr, &error);
    ASSERT_NE(uri, nullptr);
    ASSERT_EQ(error, nullptr);

    doc_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    ASSERT_NE(doc_, nullptr);
    ASSERT_EQ(error, nullptr);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) g_object_unref(page_);
    if (doc_) g_object_unref(doc_);
    if (!pdf_path_.empty()) {
      g_remove(pdf_path_.c_str());
    }
  }

  std::string pdf_path_;
  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
};

TEST_F(PopplerPageGetTextLayoutForAreaTest_2501, NullPageReturnsFalse_2501) {
  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 100;
  area.y2 = 100;

  PopplerRectangle *rects = nullptr;
  guint n_rects = 1234;

  gboolean ok = poppler_page_get_text_layout_for_area(nullptr, &area, &rects, &n_rects);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n_rects, 0u);
  EXPECT_EQ(rects, nullptr);
}

TEST_F(PopplerPageGetTextLayoutForAreaTest_2501, NullAreaReturnsFalse_2501) {
  PopplerRectangle *rects = nullptr;
  guint n_rects = 777;

  gboolean ok = poppler_page_get_text_layout_for_area(page_, nullptr, &rects, &n_rects);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n_rects, 0u);
  EXPECT_EQ(rects, nullptr);
}

TEST_F(PopplerPageGetTextLayoutForAreaTest_2501, AreaWithNoTextReturnsFalseAndZeroRects_2501) {
  // Text is drawn near (72, 720). Use a tiny area near the origin to avoid it.
  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 10;
  area.y2 = 10;

  PopplerRectangle *rects = nullptr;
  guint n_rects = 999;

  gboolean ok = poppler_page_get_text_layout_for_area(page_, &area, &rects, &n_rects);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n_rects, 0u);
  EXPECT_EQ(rects, nullptr);
}

TEST_F(PopplerPageGetTextLayoutForAreaTest_2501, WholePageAreaReturnsSomeRectangles_2501) {
  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 612;
  area.y2 = 792;

  PopplerRectangle *rects = nullptr;
  guint n_rects = 0;

  gboolean ok = poppler_page_get_text_layout_for_area(page_, &area, &rects, &n_rects);

  ASSERT_TRUE(ok);
  ASSERT_NE(rects, nullptr);
  ASSERT_GT(n_rects, 0u);

  bool saw_non_zero = false;
  for (guint i = 0; i < n_rects; ++i) {
    const PopplerRectangle &r = rects[i];

    // Basic sanity checks on returned geometry.
    EXPECT_TRUE(std::isfinite(r.x1));
    EXPECT_TRUE(std::isfinite(r.y1));
    EXPECT_TRUE(std::isfinite(r.x2));
    EXPECT_TRUE(std::isfinite(r.y2));

    // Poppler rectangles are typically normalized, but we avoid assuming too much:
    // just detect at least one with non-zero area.
    if (r.x1 != r.x2 || r.y1 != r.y2) {
      saw_non_zero = true;
    }
  }
  EXPECT_TRUE(saw_non_zero);

  g_free(rects);
}

TEST_F(PopplerPageGetTextLayoutForAreaTest_2501, TightAreaAroundExpectedTextPositionReturnsTrue_2501) {
  // The text baseline is at (72, 720) with 24pt font; pick a box that should cover it.
  PopplerRectangle area;
  area.x1 = 60;
  area.y1 = 700;
  area.x2 = 300;
  area.y2 = 760;

  PopplerRectangle *rects = nullptr;
  guint n_rects = 0;

  gboolean ok = poppler_page_get_text_layout_for_area(page_, &area, &rects, &n_rects);

  ASSERT_TRUE(ok);
  ASSERT_NE(rects, nullptr);
  ASSERT_GT(n_rects, 0u);

  // Boundary-ish check: all rectangles should at least be finite.
  for (guint i = 0; i < n_rects; ++i) {
    EXPECT_TRUE(std::isfinite(rects[i].x1));
    EXPECT_TRUE(std::isfinite(rects[i].y1));
    EXPECT_TRUE(std::isfinite(rects[i].x2));
    EXPECT_TRUE(std::isfinite(rects[i].y2));
  }

  g_free(rects);
}

} // namespace