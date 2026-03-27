// File: poppler-page-unrotate-rect-for-annot-and-page-test_2460.cc
//
// Unit tests for:
//   void _unrotate_rect_for_annot_and_page(Page *page, Annot *annot,
//                                         double *x1, double *y1,
//                                         double *x2, double *y2);
//
// Constraints honored:
// - Treat implementation as a black box.
// - Assert only observable effects via public interface and mutated out-params.
// - No access to private/internal state.
// - No re-implementation of Poppler internals.
//
// NOTE: These tests create small, valid PDFs on-the-fly with various /Rotate values
// so we can obtain real poppler::Page objects.

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "poppler/GlobalParams.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "poppler/Annot.h"
#include "poppler/PDFDocFactory.h"
#include "goo/GooString.h"
#include "poppler/PDFRectangle.h"

// Function under test (defined in glib/poppler-page.cc)
extern void _unrotate_rect_for_annot_and_page(Page *page, Annot *annot,
                                             double *x1, double *y1,
                                             double *x2, double *y2);

namespace {

static std::unique_ptr<GlobalParams> g_globalParamsOnce;

static void EnsureGlobalParamsInitialized() {
  if (!g_globalParamsOnce) {
    g_globalParamsOnce = std::make_unique<GlobalParams>();
  }
}

// Build a minimal one-page PDF with configurable /Rotate value.
// Returns full PDF bytes.
static std::string BuildMinimalPdfWithRotate(int rotate_degrees) {
  // A very small PDF:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page (with /Rotate)
  // 4 0 obj: Contents (empty stream)
  //
  // We'll compute xref offsets programmatically.

  struct Obj {
    int num;
    std::string body;  // includes "obj ... endobj"
    size_t offset = 0;
  };

  std::vector<Obj> objs;

  objs.push_back({1, ""});
  objs.push_back({2, ""});
  objs.push_back({3, ""});
  objs.push_back({4, ""});

  // Use a standard US Letter-ish MediaBox; exact size not critical for these tests.
  // Contents is empty but valid.
  {
    std::ostringstream o;
    o << "1 0 obj\n"
      << "<< /Type /Catalog /Pages 2 0 R >>\n"
      << "endobj\n";
    objs[0].body = o.str();
  }
  {
    std::ostringstream o;
    o << "2 0 obj\n"
      << "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
      << "endobj\n";
    objs[1].body = o.str();
  }
  {
    std::ostringstream o;
    o << "3 0 obj\n"
      << "<< /Type /Page /Parent 2 0 R\n"
      << "   /MediaBox [0 0 612 792]\n"
      << "   /Rotate " << rotate_degrees << "\n"
      << "   /Contents 4 0 R >>\n"
      << "endobj\n";
    objs[2].body = o.str();
  }
  {
    const char *stream_data = ""; // empty
    std::ostringstream o;
    o << "4 0 obj\n"
      << "<< /Length " << std::strlen(stream_data) << " >>\n"
      << "stream\n"
      << stream_data << "\n"
      << "endstream\n"
      << "endobj\n";
    objs[3].body = o.str();
  }

  std::string out;
  out += "%PDF-1.4\n";

  // Record offsets.
  for (auto &obj : objs) {
    obj.offset = out.size();
    out += obj.body;
  }

  const size_t xref_offset = out.size();

  // xref table: 0..4
  // Object 0 is the free head.
  std::ostringstream xref;
  xref << "xref\n"
       << "0 5\n"
       << "0000000000 65535 f \n";
  for (const auto &obj : objs) {
    // 10-digit offset, generation 00000, in-use 'n'
    xref << std::setw(10) << std::setfill('0') << obj.offset
         << " 00000 n \n";
  }

  out += xref.str();

  std::ostringstream trailer;
  trailer << "trailer\n"
          << "<< /Size 5 /Root 1 0 R >>\n"
          << "startxref\n"
          << xref_offset << "\n"
          << "%%EOF\n";
  out += trailer.str();

  return out;
}

static std::string WriteTempPdf(const std::string &bytes, const std::string &name_hint) {
  // Use /tmp (common in test environments).
  std::string path = "/tmp/" + name_hint;
  std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
  ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  ofs.close();
  return path;
}

static std::unique_ptr<PDFDoc> OpenPdfDoc(const std::string &path) {
  EnsureGlobalParamsInitialized();
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  return doc;
}

static bool NearlyEqual(double a, double b, double eps = 1e-9) {
  return std::fabs(a - b) <= eps;
}

static void ExpectRectEqual(double ax1, double ay1, double ax2, double ay2,
                            double bx1, double by1, double bx2, double by2,
                            double eps = 1e-9) {
  EXPECT_TRUE(NearlyEqual(ax1, bx1, eps));
  EXPECT_TRUE(NearlyEqual(ay1, by1, eps));
  EXPECT_TRUE(NearlyEqual(ax2, bx2, eps));
  EXPECT_TRUE(NearlyEqual(ay2, by2, eps));
}

} // namespace

class UnrotateRectForAnnotAndPageTest_2460 : public ::testing::Test {
protected:
  void SetUp() override { EnsureGlobalParamsInitialized(); }
};

TEST_F(UnrotateRectForAnnotAndPageTest_2460, UnsupportedRotationReturnsWithoutModifyingInputs_2460) {
  // Use /Rotate 45 (not a multiple of 90). If rotation is unsupported,
  // function is expected to return early (observable: no normalization or changes).
  const std::string pdf = BuildMinimalPdfWithRotate(45);
  const std::string path = WriteTempPdf(pdf, "unrotate_unsupported_2460.pdf");
  auto doc = OpenPdfDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);
  EXPECT_EQ(page->getRotate(), 45);

  PDFRectangle r(0, 0, 10, 10);
  Annot annot(doc.get(), &r);

  double x1 = 200.0;
  double y1 = 100.0;
  double x2 = 100.0;
  double y2 = 200.0;

  const double ox1 = x1, oy1 = y1, ox2 = x2, oy2 = y2;

  _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

  // Observable behavior: unchanged, because it returned early.
  ExpectRectEqual(x1, y1, x2, y2, ox1, oy1, ox2, oy2);
}

TEST_F(UnrotateRectForAnnotAndPageTest_2460, FlagNoRotatePreservesWidthAndHeightAfterNormalization_2460) {
  // Supported rotation (90) and annot has flagNoRotate.
  const std::string pdf = BuildMinimalPdfWithRotate(90);
  const std::string path = WriteTempPdf(pdf, "unrotate_norotate_flag_2460.pdf");
  auto doc = OpenPdfDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);
  EXPECT_EQ(page->getRotate(), 90);

  PDFRectangle r(0, 0, 10, 10);
  Annot annot(doc.get(), &r);
  annot.setFlags(Annot::flagNoRotate);

  // Provide diagonal not in (upper-left -> bottom-right) order to exercise normalization:
  // y2 > y1 and x1 > x2
  double x1 = 200.0;
  double y1 = 100.0;
  double x2 = 100.0;
  double y2 = 200.0;

  // Expected normalized dimensions before unrotation:
  // After normalization: (x1,x2) -> (100,200), (y1,y2) -> (200,100)
  const double expected_width = 200.0 - 100.0;
  const double expected_height = 200.0 - 100.0; // y1 - y2

  _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

  // Observable invariant of the flagNoRotate path:
  // width/height should match normalized original width/height.
  const double width = x2 - x1;
  const double height = y1 - y2;

  EXPECT_TRUE(width >= 0.0);
  EXPECT_TRUE(height >= 0.0);
  EXPECT_TRUE(NearlyEqual(width, expected_width, 1e-6));
  EXPECT_TRUE(NearlyEqual(height, expected_height, 1e-6));

  // Also, because it reconstructs x2/y2 from x1/y1 + width/height,
  // ordering should remain consistent.
  EXPECT_LE(x1, x2);
  EXPECT_GE(y1, y2);
}

TEST_F(UnrotateRectForAnnotAndPageTest_2460, FlagNoRotateAndDefaultPathProduceDifferentOutputsForSameInputs_2460) {
  // For supported rotation (90), compare outputs with and without flagNoRotate
  // starting from identical coordinates. Observable: results should differ
  // because one path unrotates one corner and reconstructs, while the other
  // unrotates both corners.
  const std::string pdf = BuildMinimalPdfWithRotate(90);
  const std::string path = WriteTempPdf(pdf, "unrotate_compare_paths_2460.pdf");
  auto doc = OpenPdfDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);
  EXPECT_EQ(page->getRotate(), 90);

  PDFRectangle r(0, 0, 10, 10);

  Annot annot_no_rotate(doc.get(), &r);
  annot_no_rotate.setFlags(Annot::flagNoRotate);

  Annot annot_default(doc.get(), &r);
  annot_default.setFlags(0);

  // Already normalized diagonal.
  double ax1 = 100.0, ay1 = 200.0, ax2 = 200.0, ay2 = 100.0;
  double bx1 = 100.0, by1 = 200.0, bx2 = 200.0, by2 = 100.0;

  _unrotate_rect_for_annot_and_page(page, &annot_no_rotate, &ax1, &ay1, &ax2, &ay2);
  _unrotate_rect_for_annot_and_page(page, &annot_default, &bx1, &by1, &bx2, &by2);

  const bool all_equal =
      NearlyEqual(ax1, bx1, 1e-9) &&
      NearlyEqual(ay1, by1, 1e-9) &&
      NearlyEqual(ax2, bx2, 1e-9) &&
      NearlyEqual(ay2, by2, 1e-9);

  EXPECT_FALSE(all_equal);
}

TEST_F(UnrotateRectForAnnotAndPageTest_2460, ZeroRotationKeepsRectangleWhenAlreadyNormalized_2460) {
  // With /Rotate 0, unrotation should be a no-op (observable: for an already-normalized
  // rectangle, outputs should remain the same within tolerance).
  const std::string pdf = BuildMinimalPdfWithRotate(0);
  const std::string path = WriteTempPdf(pdf, "unrotate_zero_rotation_2460.pdf");
  auto doc = OpenPdfDoc(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);
  EXPECT_EQ(page->getRotate(), 0);

  PDFRectangle r(0, 0, 10, 10);
  Annot annot(doc.get(), &r);

  // Already normalized (x1 <= x2, y1 >= y2)
  double x1 = 10.0;
  double y1 = 20.0;
  double x2 = 30.0;
  double y2 = 5.0;

  const double ox1 = x1, oy1 = y1, ox2 = x2, oy2 = y2;

  _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

  // For rotate=0, we expect no observable change.
  ExpectRectEqual(x1, y1, x2, y2, ox1, oy1, ox2, oy2, 1e-6);
}