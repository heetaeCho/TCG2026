// File: poppler-annot-ink-set-ink-list-test-2131.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string BuildPdfWithInkAnnot_2131(double border_width)
{
  // Builds a minimal 1-page PDF containing a single /Subtype /Ink annotation.
  // The annotation's /Rect is arbitrary; poppler_annot_ink_set_ink_list should update it.
  //
  // Page MediaBox: [0 0 200 200]
  // Annotation object 5: /Subtype /Ink, /InkList has one path with two points.
  //
  // NOTE: We compute xref offsets to keep the PDF valid without external files.

  std::vector<std::string> objs;

  // 1 0 obj: Catalog
  objs.emplace_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");

  // 2 0 obj: Pages
  objs.emplace_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  // 3 0 obj: Page (includes Annots [5 0 R])
  objs.emplace_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << >>\n"
      "   /Annots [5 0 R]\n"
      ">>\n"
      "endobj\n");

  // 4 0 obj: Empty content stream
  objs.emplace_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n");

  // 5 0 obj: Ink annotation.
  // Include /BS /W so poppler_annot_get_border_width can observe it.
  // Include an initial /Rect; the function under test should override it.
  {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(2);

    // /InkList format: [ [ x y x y ... ] [ ... ] ]
    // Here: one stroke with two points.
    oss << "5 0 obj\n"
           "<< /Type /Annot\n"
           "   /Subtype /Ink\n"
           "   /Rect [10 10 20 20]\n"
           "   /BS << /W "
        << border_width
        << " >>\n"
           "   /InkList [ [ 30 40  50 60 ] ]\n"
           ">>\n"
           "endobj\n";
    objs.emplace_back(oss.str());
  }

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  std::vector<long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 is the free object for xref.

  for (const auto &obj : objs) {
    offsets.push_back(static_cast<long>(pdf.tellp()));
    pdf << obj;
  }

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (objs.size() + 1) << "\n";
  pdf << "0000000000 65535 f \n";

  for (size_t i = 1; i < offsets.size(); i++) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf << buf;
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xref_pos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static std::string WriteTempPdf_2131(const std::string &pdf_bytes)
{
  gchar *tmpl = g_strdup("/tmp/poppler_ink_2131_XXXXXX.pdf");
  int fd = g_mkstemp(tmpl);
  EXPECT_NE(fd, -1);
  if (fd == -1) {
    std::string bad;
    g_free(tmpl);
    return bad;
  }

  const ssize_t want = static_cast<ssize_t>(pdf_bytes.size());
  const ssize_t wrote = write(fd, pdf_bytes.data(), want);
  close(fd);

  EXPECT_EQ(wrote, want);

  std::string path(tmpl);
  g_free(tmpl);
  return path;
}

static std::string ToFileUri_2131(const std::string &path)
{
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  EXPECT_NE(uri, nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
}

static PopplerPath *MakePath_2131(const std::vector<std::pair<double, double>> &pts)
{
  // PopplerPath is an opaque-ish struct in poppler-glib; creation helpers exist in API.
  // However, poppler_annot_ink_set_ink_list only needs poppler_path_get_points() to work.
  // Use the public constructor API if available; otherwise fall back to allocating
  // via poppler_path_new() + poppler_path_add_point() which exist in poppler-glib.

  PopplerPath *path = poppler_path_new();
  EXPECT_NE(path, nullptr);
  for (const auto &p : pts) {
    poppler_path_add_point(path, p.first, p.second);
  }
  return path;
}

static void AssertRectNear_2131(const PopplerRectangle &r,
                               double x1, double y1, double x2, double y2,
                               double eps = 1e-6)
{
  EXPECT_NEAR(r.x1, x1, eps);
  EXPECT_NEAR(r.y1, y1, eps);
  EXPECT_NEAR(r.x2, x2, eps);
  EXPECT_NEAR(r.y2, y2, eps);
}

class PopplerAnnotInkSetInkListTest_2131 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Default border width used in the embedded annotation.
    border_width_ = 2.0;

    const std::string pdf = BuildPdfWithInkAnnot_2131(border_width_);
    pdf_path_ = WriteTempPdf_2131(pdf);
    ASSERT_FALSE(pdf_path_.empty());

    const std::string uri = ToFileUri_2131(pdf_path_);
    ASSERT_FALSE(uri.empty());

    GError *error = nullptr;
    doc_ = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    ASSERT_NE(doc_, nullptr);
    if (error) {
      const std::string msg = error->message ? error->message : "";
      g_error_free(error);
      FAIL() << "Failed to open PDF: " << msg;
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    // Get the first annotation and ensure it's Ink.
    GList *mappings = poppler_page_get_annot_mapping(page_);
    ASSERT_NE(mappings, nullptr);

    PopplerAnnotMapping *first = static_cast<PopplerAnnotMapping *>(mappings->data);
    ASSERT_NE(first, nullptr);
    ASSERT_NE(first->annot, nullptr);

    ASSERT_EQ(poppler_annot_get_annot_type(first->annot), POPPLER_ANNOT_INK);

    annot_ = POPPLER_ANNOT_INK(first->annot);
    ASSERT_NE(annot_, nullptr);

    poppler_page_free_annot_mapping(mappings);
  }

  void TearDown() override
  {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!pdf_path_.empty()) {
      g_remove(pdf_path_.c_str());
    }
  }

  std::string pdf_path_;
  double border_width_ = 0.0;
  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
  PopplerAnnotInk *annot_ = nullptr;
};

TEST_F(PopplerAnnotInkSetInkListTest_2131, UpdatesRectangleFromSinglePathTwoPoints_2131)
{
  // Provide one path with two points.
  // Expected rectangle: min/max of points expanded by border width.
  std::unique_ptr<PopplerPath, void (*)(PopplerPath *)> path(
      MakePath_2131({{10.0, 20.0}, {30.0, 5.0}}),
      poppler_path_free);

  PopplerPath *ink_list[1] = {path.get()};

  // Sanity: get current rectangle (should be the one from PDF).
  PopplerRectangle before{};
  ASSERT_TRUE(poppler_annot_get_rectangle(POPPLER_ANNOT(annot_), &before));

  poppler_annot_ink_set_ink_list(annot_, ink_list, 1);

  PopplerRectangle after{};
  ASSERT_TRUE(poppler_annot_get_rectangle(POPPLER_ANNOT(annot_), &after));

  // min x = 10, max x = 30, min y = 5, max y = 20; expanded by border_width_.
  AssertRectNear_2131(after,
                      10.0 - border_width_,
                      5.0 - border_width_,
                      30.0 + border_width_,
                      20.0 + border_width_);
}

TEST_F(PopplerAnnotInkSetInkListTest_2131, UpdatesRectangleFromMultiplePaths_2131)
{
  std::unique_ptr<PopplerPath, void (*)(PopplerPath *)> p1(
      MakePath_2131({{1.0, 2.0}, {3.0, 4.0}}),
      poppler_path_free);
  std::unique_ptr<PopplerPath, void (*)(PopplerPath *)> p2(
      MakePath_2131({{100.0, 50.0}, {80.0, 70.0}, {90.0, 10.0}}),
      poppler_path_free);

  PopplerPath *ink_list[2] = {p1.get(), p2.get()};

  poppler_annot_ink_set_ink_list(annot_, ink_list, 2);

  PopplerRectangle r{};
  ASSERT_TRUE(poppler_annot_get_rectangle(POPPLER_ANNOT(annot_), &r));

  // Overall min/max across all points:
  // xs: min 1, max 100; ys: min 2? actually 2 and 4 and 50,70,10 => min 2, max 70.
  AssertRectNear_2131(r,
                      1.0 - border_width_,
                      2.0 - border_width_,
                      100.0 + border_width_,
                      70.0 + border_width_);
}

TEST_F(PopplerAnnotInkSetInkListTest_2131, PersistsInkListObservableViaGetter_2131)
{
  // Set two separate strokes and verify the getter returns the same geometry.
  std::unique_ptr<PopplerPath, void (*)(PopplerPath *)> p1(
      MakePath_2131({{11.0, 12.0}, {13.0, 14.0}}),
      poppler_path_free);
  std::unique_ptr<PopplerPath, void (*)(PopplerPath *)> p2(
      MakePath_2131({{21.0, 22.0}, {23.0, 24.0}, {25.0, 26.0}}),
      poppler_path_free);

  PopplerPath *ink_list_in[2] = {p1.get(), p2.get()};
  poppler_annot_ink_set_ink_list(annot_, ink_list_in, 2);

  gsize n_paths_out = 0;
  PopplerPath **ink_list_out = poppler_annot_ink_get_ink_list(annot_, &n_paths_out);
  ASSERT_NE(ink_list_out, nullptr);
  ASSERT_EQ(n_paths_out, 2u);

  // Stroke 1
  gsize n_points1 = 0;
  PopplerPoint *pts1 = poppler_path_get_points(ink_list_out[0], &n_points1);
  ASSERT_NE(pts1, nullptr);
  ASSERT_EQ(n_points1, 2u);
  EXPECT_DOUBLE_EQ(pts1[0].x, 11.0);
  EXPECT_DOUBLE_EQ(pts1[0].y, 12.0);
  EXPECT_DOUBLE_EQ(pts1[1].x, 13.0);
  EXPECT_DOUBLE_EQ(pts1[1].y, 14.0);

  // Stroke 2
  gsize n_points2 = 0;
  PopplerPoint *pts2 = poppler_path_get_points(ink_list_out[1], &n_points2);
  ASSERT_NE(pts2, nullptr);
  ASSERT_EQ(n_points2, 3u);
  EXPECT_DOUBLE_EQ(pts2[0].x, 21.0);
  EXPECT_DOUBLE_EQ(pts2[0].y, 22.0);
  EXPECT_DOUBLE_EQ(pts2[1].x, 23.0);
  EXPECT_DOUBLE_EQ(pts2[1].y, 24.0);
  EXPECT_DOUBLE_EQ(pts2[2].x, 25.0);
  EXPECT_DOUBLE_EQ(pts2[2].y, 26.0);

  // Free list returned by getter.
  // poppler-glib returns a NULL-terminated list in some APIs, but here we rely on count.
  for (gsize i = 0; i < n_paths_out; i++) {
    poppler_path_free(ink_list_out[i]);
  }
  g_free(ink_list_out);
}

TEST_F(PopplerAnnotInkSetInkListTest_2131, HandlesZeroPathsWithoutCrash_2131)
{
  // Boundary: n_paths == 0. We only assert that it does not crash and that
  // poppler_annot_get_rectangle remains callable.
  poppler_annot_ink_set_ink_list(annot_, nullptr, 0);

  PopplerRectangle r{};
  // Some implementations may keep previous rect or set something else; just observe it.
  EXPECT_TRUE(poppler_annot_get_rectangle(POPPLER_ANNOT(annot_), &r));
}

TEST_F(PopplerAnnotInkSetInkListTest_2131, RectangleReflectsSinglePointPath_2131)
{
  // Boundary: one path with one point => min==max; expansion by border width still applies.
  std::unique_ptr<PopplerPath, void (*)(PopplerPath *)> p(
      MakePath_2131({{42.0, 99.0}}),
      poppler_path_free);
  PopplerPath *ink_list[1] = {p.get()};

  poppler_annot_ink_set_ink_list(annot_, ink_list, 1);

  PopplerRectangle r{};
  ASSERT_TRUE(poppler_annot_get_rectangle(POPPLER_ANNOT(annot_), &r));

  AssertRectNear_2131(r,
                      42.0 - border_width_,
                      99.0 - border_width_,
                      42.0 + border_width_,
                      99.0 + border_width_);
}

} // namespace