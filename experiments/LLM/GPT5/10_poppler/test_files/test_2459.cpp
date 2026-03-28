// File: poppler-page-new-quads-unrotated-test_2459.cc
//
// Unit tests for _page_new_quads_unrotated(Page*, AnnotQuadrilaterals*)
// Black-box tests using Poppler core objects (PDFDoc/Page) and AnnotQuadrilaterals.

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "poppler/Annot.h"
#include "poppler/Page.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include "goo/GooString.h"

// Function under test (defined in glib/poppler-page.cc)
extern AnnotQuadrilaterals *_page_new_quads_unrotated(Page *page, AnnotQuadrilaterals *quads);

// Poppler has a global singleton for parameters.
extern std::unique_ptr<GlobalParams> globalParams;

namespace {

class PageNewQuadsUnrotatedTest_2459 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Ensure Poppler global params are initialized for PDFDoc parsing.
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }

  static std::string WriteMinimalPdfOnePage(const std::string &path, int rotateDeg /*0/90/180/270*/) {
    // Minimal valid PDF with 4 indirect objects:
    // 1: Catalog
    // 2: Pages
    // 3: Page (with /Rotate)
    // 4: Contents (empty stream)
    //
    // We compute xref offsets programmatically to avoid hand-maintained offsets.

    std::ostringstream out;
    out << "%PDF-1.4\n";

    std::vector<long> offsets;
    offsets.reserve(5);
    offsets.push_back(0); // object 0 (free)

    auto append_obj = [&](int objNum, const std::string &body) {
      offsets.push_back(static_cast<long>(out.tellp()));
      out << objNum << " 0 obj\n" << body << "\nendobj\n";
    };

    append_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");
    append_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

    {
      std::ostringstream pageDict;
      pageDict << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R";
      if (rotateDeg != 0) {
        pageDict << " /Rotate " << rotateDeg;
      }
      pageDict << " >>";
      append_obj(3, pageDict.str());
    }

    // Empty content stream
    offsets.push_back(static_cast<long>(out.tellp()));
    out << "4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n";

    const long xref_pos = static_cast<long>(out.tellp());
    out << "xref\n0 5\n";
    out << "0000000000 65535 f \n";
    for (int i = 1; i <= 4; ++i) {
      // Each offset is 10 digits, zero-padded.
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      out << buf;
    }

    out << "trailer\n<< /Size 5 /Root 1 0 R >>\n";
    out << "startxref\n" << xref_pos << "\n%%EOF\n";

    std::ofstream file(path, std::ios::binary);
    file << out.str();
    file.close();

    return path;
  }

  static std::unique_ptr<PDFDoc> OpenPdf(const std::string &path) {
    auto fname = std::make_unique<GooString>(path.c_str());

    // Common Poppler constructor signature:
    // PDFDoc(std::unique_ptr<GooString>&& fileName, GooString *ownerPassword,
    //        GooString *userPassword, void *guiDataA)
    //
    // If your Poppler version differs, adapt the constructor accordingly.
    auto doc = std::make_unique<PDFDoc>(std::move(fname), nullptr, nullptr, nullptr);
    return doc;
  }

  static std::unique_ptr<AnnotQuadrilaterals> MakeQuads(
      const std::vector<AnnotQuadrilaterals::AnnotQuadrilateral> &quadsVec) {
    const int len = static_cast<int>(quadsVec.size());
    auto arr = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral[]>(len);
    for (int i = 0; i < len; ++i) {
      arr[i] = quadsVec[i];
    }
    return std::make_unique<AnnotQuadrilaterals>(std::move(arr), len);
  }

  static void ExpectQuadEq(const AnnotQuadrilaterals *q, int i,
                           double x1, double y1, double x2, double y2,
                           double x3, double y3, double x4, double y4) {
    ASSERT_NE(q, nullptr);
    EXPECT_DOUBLE_EQ(q->getX1(i), x1);
    EXPECT_DOUBLE_EQ(q->getY1(i), y1);
    EXPECT_DOUBLE_EQ(q->getX2(i), x2);
    EXPECT_DOUBLE_EQ(q->getY2(i), y2);
    EXPECT_DOUBLE_EQ(q->getX3(i), x3);
    EXPECT_DOUBLE_EQ(q->getY3(i), y3);
    EXPECT_DOUBLE_EQ(q->getX4(i), x4);
    EXPECT_DOUBLE_EQ(q->getY4(i), y4);
  }
};

TEST_F(PageNewQuadsUnrotatedTest_2459, ReturnsSameLengthOnUnrotatedPage_2459) {
  const std::string pdfPath = "/tmp/page_new_quads_unrotated_2459_rotate0.pdf";
  WriteMinimalPdfOnePage(pdfPath, /*rotateDeg=*/0);

  auto doc = OpenPdf(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  auto in = MakeQuads({
      AnnotQuadrilaterals::AnnotQuadrilateral(10, 20, 30, 40, 50, 60, 70, 80),
      AnnotQuadrilaterals::AnnotQuadrilateral(1.25, 2.5, 3.75, 4.125, 5.5, 6.625, 7.75, 8.875),
  });
  ASSERT_NE(in, nullptr);
  ASSERT_EQ(in->getQuadrilateralsLength(), 2);

  std::unique_ptr<AnnotQuadrilaterals> out(_page_new_quads_unrotated(page, in.get()));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->getQuadrilateralsLength(), in->getQuadrilateralsLength());
}

TEST_F(PageNewQuadsUnrotatedTest_2459, CopiesCoordinatesWhenNoRotation_2459) {
  const std::string pdfPath = "/tmp/page_new_quads_unrotated_2459_copy_rotate0.pdf";
  WriteMinimalPdfOnePage(pdfPath, /*rotateDeg=*/0);

  auto doc = OpenPdf(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const auto q0 = AnnotQuadrilaterals::AnnotQuadrilateral(10, 20, 30, 40, 50, 60, 70, 80);
  const auto q1 = AnnotQuadrilaterals::AnnotQuadrilateral(-10, -20, 0, 5, 199.5, 0.25, 12.75, 199.125);

  auto in = MakeQuads({q0, q1});
  ASSERT_NE(in, nullptr);

  std::unique_ptr<AnnotQuadrilaterals> out(_page_new_quads_unrotated(page, in.get()));
  ASSERT_NE(out, nullptr);
  ASSERT_EQ(out->getQuadrilateralsLength(), 2);

  // For a non-rotated page, "unrotating" should be observable as a no-op on coordinates.
  ExpectQuadEq(out.get(), 0, 10, 20, 30, 40, 50, 60, 70, 80);
  ExpectQuadEq(out.get(), 1, -10, -20, 0, 5, 199.5, 0.25, 12.75, 199.125);
}

TEST_F(PageNewQuadsUnrotatedTest_2459, DoesNotModifyInputQuadrilaterals_2459) {
  const std::string pdfPath = "/tmp/page_new_quads_unrotated_2459_input_unchanged.pdf";
  WriteMinimalPdfOnePage(pdfPath, /*rotateDeg=*/0);

  auto doc = OpenPdf(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  auto in = MakeQuads({
      AnnotQuadrilaterals::AnnotQuadrilateral(11, 22, 33, 44, 55, 66, 77, 88),
  });
  ASSERT_NE(in, nullptr);
  ASSERT_EQ(in->getQuadrilateralsLength(), 1);

  // Snapshot input values through public getters (black-box safe).
  const double bx1 = in->getX1(0), by1 = in->getY1(0);
  const double bx2 = in->getX2(0), by2 = in->getY2(0);
  const double bx3 = in->getX3(0), by3 = in->getY3(0);
  const double bx4 = in->getX4(0), by4 = in->getY4(0);

  std::unique_ptr<AnnotQuadrilaterals> out(_page_new_quads_unrotated(page, in.get()));
  ASSERT_NE(out, nullptr);

  // Verify input remains unchanged after the call.
  EXPECT_DOUBLE_EQ(in->getX1(0), bx1);
  EXPECT_DOUBLE_EQ(in->getY1(0), by1);
  EXPECT_DOUBLE_EQ(in->getX2(0), bx2);
  EXPECT_DOUBLE_EQ(in->getY2(0), by2);
  EXPECT_DOUBLE_EQ(in->getX3(0), bx3);
  EXPECT_DOUBLE_EQ(in->getY3(0), by3);
  EXPECT_DOUBLE_EQ(in->getX4(0), bx4);
  EXPECT_DOUBLE_EQ(in->getY4(0), by4);
}

TEST_F(PageNewQuadsUnrotatedTest_2459, ZeroLengthQuadrilateralsReturnsZeroLength_2459) {
  const std::string pdfPath = "/tmp/page_new_quads_unrotated_2459_zero_len.pdf";
  WriteMinimalPdfOnePage(pdfPath, /*rotateDeg=*/0);

  auto doc = OpenPdf(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  auto empty = MakeQuads({});
  ASSERT_NE(empty, nullptr);
  ASSERT_EQ(empty->getQuadrilateralsLength(), 0);

  std::unique_ptr<AnnotQuadrilaterals> out(_page_new_quads_unrotated(page, empty.get()));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->getQuadrilateralsLength(), 0);
}

TEST_F(PageNewQuadsUnrotatedTest_2459, ReturnsDistinctObjectPointer_2459) {
  const std::string pdfPath = "/tmp/page_new_quads_unrotated_2459_distinct_ptr.pdf";
  WriteMinimalPdfOnePage(pdfPath, /*rotateDeg=*/0);

  auto doc = OpenPdf(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  auto in = MakeQuads({
      AnnotQuadrilaterals::AnnotQuadrilateral(0, 0, 1, 0, 1, 1, 0, 1),
  });
  ASSERT_NE(in, nullptr);

  AnnotQuadrilaterals *rawIn = in.get();
  std::unique_ptr<AnnotQuadrilaterals> out(_page_new_quads_unrotated(page, in.get()));
  ASSERT_NE(out, nullptr);

  // Observable behavior: returns a new heap object (per signature/ownership expectation).
  EXPECT_NE(out.get(), rawIn);
}

} // namespace