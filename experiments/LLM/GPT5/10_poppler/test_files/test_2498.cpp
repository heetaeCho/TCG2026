// poppler-page-get-crop-box-test_2498.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

#include <cstring>
#include <string>
#include <vector>

extern "C" {
// Function under test (implemented in poppler-page.cc)
void poppler_page_get_crop_box(PopplerPage *page, PopplerRectangle *rect);
}

namespace {

static std::string BuildPdfWithSinglePageAndCropBox(double x1, double y1, double x2, double y2) {
  // Minimal valid PDF with:
  // - 1 page
  // - MediaBox [0 0 612 792]
  // - CropBox [x1 y1 x2 y2]
  //
  // We compute xref offsets to keep the file parsable by Poppler.
  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"});

  // 2: Pages
  objs.push_back({2, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"});

  // 3: Page with explicit CropBox
  {
    gchar *crop = g_strdup_printf(
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R\n"
        "   /MediaBox [0 0 612 792]\n"
        "   /CropBox [%.6f %.6f %.6f %.6f]\n"
        "   /Contents 4 0 R\n"
        ">>\n"
        "endobj\n",
        x1, y1, x2, y2);
    objs.push_back({3, std::string(crop)});
    g_free(crop);
  }

  // 4: Empty content stream
  objs.push_back({4,
                 "4 0 obj\n"
                 "<< /Length 0 >>\n"
                 "stream\n"
                 "\n"
                 "endstream\n"
                 "endobj\n"});

  std::string pdf;
  pdf.reserve(2048);

  pdf += "%PDF-1.4\n";
  // Binary comment line (common practice)
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // Track offsets: index by object number (0..N)
  const int max_obj_num = 4;
  std::vector<long> offsets(max_obj_num + 1, 0);

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    pdf += o.body;
  }

  const long xref_offset = static_cast<long>(pdf.size());

  // xref table
  pdf += "xref\n";
  pdf += "0 5\n";
  pdf += "0000000000 65535 f \n";

  // Each entry is 10-digit offset, 5-digit gen, n/f
  for (int i = 1; i <= max_obj_num; ++i) {
    gchar *line = g_strdup_printf("%010ld 00000 n \n", offsets[i]);
    pdf += line;
    g_free(line);
  }

  // trailer + startxref
  pdf += "trailer\n";
  pdf += "<< /Size 5 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  {
    gchar *sx = g_strdup_printf("%ld\n", xref_offset);
    pdf += sx;
    g_free(sx);
  }
  pdf += "%%EOF\n";

  return pdf;
}

struct TempPdf {
  std::string path;
  std::string uri;
};

static TempPdf WriteTempPdfToDisk(const std::string &pdf_bytes) {
  TempPdf out;

  gchar *tmpdir = g_dir_make_tmp("poppler-ut-2498-XXXXXX", nullptr);
  EXPECT_NE(tmpdir, nullptr);

  gchar *filepath = g_build_filename(tmpdir, "cropbox_2498.pdf", nullptr);

  gboolean ok = g_file_set_contents(filepath, pdf_bytes.data(),
                                    static_cast<gssize>(pdf_bytes.size()), nullptr);
  EXPECT_TRUE(ok);

  gchar *file_uri = g_filename_to_uri(filepath, nullptr, nullptr);
  EXPECT_NE(file_uri, nullptr);

  out.path = filepath;
  out.uri = file_uri;

  g_free(file_uri);
  g_free(filepath);
  g_rmdir(tmpdir); // directory will fail to remove if not empty; ignore here
  g_free(tmpdir);

  return out;
}

class PopplerPageGetCropBoxTest_2498 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (!temp_path_.empty()) {
      g_remove(temp_path_.c_str());
    }
  }

  PopplerDocument *LoadDocFromUriOrFail(const std::string &uri) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    if (!doc && error) {
      ADD_FAILURE() << "Failed to open PDF: " << error->message;
      g_error_free(error);
    }
    EXPECT_NE(doc, nullptr);
    return doc;
  }

  std::string temp_path_;
};

TEST_F(PopplerPageGetCropBoxTest_2498, CopiesCropBoxIntoRect_2498) {
  const double x1 = 10.0, y1 = 20.0, x2 = 210.0, y2 = 320.0;
  const std::string pdf = BuildPdfWithSinglePageAndCropBox(x1, y1, x2, y2);
  TempPdf tmp = WriteTempPdfToDisk(pdf);
  temp_path_ = tmp.path;

  PopplerDocument *doc = LoadDocFromUriOrFail(tmp.uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerRectangle rect;
  // Pre-fill with sentinel values to ensure the function overwrites all fields.
  rect.x1 = -1;
  rect.y1 = -2;
  rect.x2 = -3;
  rect.y2 = -4;

  poppler_page_get_crop_box(page, &rect);

  EXPECT_DOUBLE_EQ(rect.x1, x1);
  EXPECT_DOUBLE_EQ(rect.y1, y1);
  EXPECT_DOUBLE_EQ(rect.x2, x2);
  EXPECT_DOUBLE_EQ(rect.y2, y2);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetCropBoxTest_2498, HandlesNegativeAndFractionalValues_2498) {
  const double x1 = -5.5, y1 = 0.25, x2 = 100.125, y2 = 200.75;
  const std::string pdf = BuildPdfWithSinglePageAndCropBox(x1, y1, x2, y2);
  TempPdf tmp = WriteTempPdfToDisk(pdf);
  temp_path_ = tmp.path;

  PopplerDocument *doc = LoadDocFromUriOrFail(tmp.uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerRectangle rect;
  rect.x1 = 999;
  rect.y1 = 999;
  rect.x2 = 999;
  rect.y2 = 999;

  poppler_page_get_crop_box(page, &rect);

  EXPECT_DOUBLE_EQ(rect.x1, x1);
  EXPECT_DOUBLE_EQ(rect.y1, y1);
  EXPECT_DOUBLE_EQ(rect.x2, x2);
  EXPECT_DOUBLE_EQ(rect.y2, y2);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetCropBoxTest_2498, ZeroSizedCropBoxIsCopied_2498) {
  // Boundary-ish: x1==x2 and y1==y2 (degenerate rectangle). We only verify copying.
  const double x1 = 42.0, y1 = 42.0, x2 = 42.0, y2 = 42.0;
  const std::string pdf = BuildPdfWithSinglePageAndCropBox(x1, y1, x2, y2);
  TempPdf tmp = WriteTempPdfToDisk(pdf);
  temp_path_ = tmp.path;

  PopplerDocument *doc = LoadDocFromUriOrFail(tmp.uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerRectangle rect;
  poppler_page_get_crop_box(page, &rect);

  EXPECT_DOUBLE_EQ(rect.x1, x1);
  EXPECT_DOUBLE_EQ(rect.y1, y1);
  EXPECT_DOUBLE_EQ(rect.x2, x2);
  EXPECT_DOUBLE_EQ(rect.y2, y2);

  g_object_unref(page);
  g_object_unref(doc);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerPageGetCropBoxTest_2498, DeathOnNullRect_2498) {
  const std::string pdf = BuildPdfWithSinglePageAndCropBox(1, 2, 3, 4);
  TempPdf tmp = WriteTempPdfToDisk(pdf);
  temp_path_ = tmp.path;

  PopplerDocument *doc = LoadDocFromUriOrFail(tmp.uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  // The implementation dereferences rect unconditionally; verify it fails fast.
  ASSERT_DEATH({ poppler_page_get_crop_box(page, nullptr); }, "");

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetCropBoxTest_2498, DeathOnNullPage_2498) {
  PopplerRectangle rect;
  std::memset(&rect, 0, sizeof(rect));

  // The implementation dereferences page->page unconditionally; verify it fails fast.
  ASSERT_DEATH({ poppler_page_get_crop_box(nullptr, &rect); }, "");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace