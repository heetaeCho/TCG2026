// File: poppler-page-unrotate-xy-test_2458.cc
//
// Unit tests for: void _page_unrotate_xy(Page *page, double *x, double *y)
//
// These tests treat the implementation as a black box and validate only
// observable behavior through the public Page interface used by the function.
//
// NOTE: This test builds a tiny PDF on the fly, opens it with Poppler core
// (PDFDoc), obtains Page* objects, and then calls _page_unrotate_xy().

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "poppler/Page.h"
#include "poppler/PDFDoc.h"
#include "poppler/goo/GooString.h"

// Under test (implemented in ./TestProjects/poppler/glib/poppler-page.cc)
extern "C" void _page_unrotate_xy(Page *page, double *x, double *y);

namespace {

class PageUnrotateXYTest_2458 : public ::testing::Test {
protected:
  static std::string MakeTempPath_2458(const std::string &suffix) {
    // Keep it simple and deterministic enough for CI environments.
    // If your test harness provides a temp-dir helper, feel free to swap this.
    std::ostringstream oss;
    oss << "poppler_page_unrotate_xy_2458_" << ::testing::UnitTest::GetInstance()->random_seed()
        << "_" << reinterpret_cast<uintptr_t>(&oss) << suffix;
    return oss.str();
  }

  static void WriteFileBytes_2458(const std::string &path, const std::string &bytes) {
    std::ofstream out(path, std::ios::binary);
    ASSERT_TRUE(out.good()) << "Failed to open temp file for writing: " << path;
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    ASSERT_TRUE(out.good()) << "Failed to write PDF bytes to: " << path;
  }

  // Builds a minimal PDF with one page per rotation value.
  // Each page has:
  //   /MediaBox [0 0 200 100]
  //   /Rotate <rotation>
  //
  // This is sufficient for Page::getCropWidth/Height and Page::getRotate()
  // used by _page_unrotate_xy().
  static std::string BuildMinimalPdfWithRotations_2458(const std::vector<int> &rotations) {
    // Object layout:
    //  1: Catalog
    //  2: Pages
    //  3..(3+n-1): Page objects
    //  (3+n)..(3+2n-1): Contents streams (one per page)
    //
    // We'll generate a correct xref by tracking offsets.
    std::vector<std::string> objs;

    auto addObj = [&](std::string s) { objs.emplace_back(std::move(s)); };

    // Placeholder; will fill Kids later once we know page object numbers.
    // Object numbers are 1-based in the PDF.
    // 1 0 obj: Catalog
    addObj("<< /Type /Catalog /Pages 2 0 R >>");

    // 2 0 obj: Pages (Kids will be inserted later)
    // We'll construct this after knowing page/contents object numbers.
    addObj(""); // index 1 (object #2)

    const int n = static_cast<int>(rotations.size());
    const int firstPageObj = 3;
    const int firstContentsObj = firstPageObj + n;

    // Page objects
    for (int i = 0; i < n; ++i) {
      const int pageObjNum = firstPageObj + i;
      const int contentsObjNum = firstContentsObj + i;

      std::ostringstream page;
      page << "<< /Type /Page"
           << " /Parent 2 0 R"
           << " /MediaBox [0 0 200 100]"
           << " /Rotate " << rotations[i]
           << " /Contents " << contentsObjNum << " 0 R"
           << " >>";
      addObj(page.str());
      (void)pageObjNum;
    }

    // Contents stream objects (empty content is fine)
    for (int i = 0; i < n; ++i) {
      std::ostringstream contents;
      contents << "<< /Length 0 >>\n"
               << "stream\n"
               << "\n"
               << "endstream";
      addObj(contents.str());
    }

    // Now fill Pages object (#2).
    {
      std::ostringstream kids;
      kids << "[ ";
      for (int i = 0; i < n; ++i) {
        kids << (firstPageObj + i) << " 0 R ";
      }
      kids << "]";

      std::ostringstream pages;
      pages << "<< /Type /Pages"
            << " /Count " << n
            << " /Kids " << kids.str()
            << " >>";
      objs[1] = pages.str();
    }

    // Assemble PDF with xref
    std::ostringstream pdf;
    pdf << "%PDF-1.4\n";

    // Offsets: object 0 is the free object.
    std::vector<long> offsets;
    offsets.reserve(objs.size() + 1);
    offsets.push_back(0);

    for (size_t i = 0; i < objs.size(); ++i) {
      offsets.push_back(static_cast<long>(pdf.tellp()));
      const int objNum = static_cast<int>(i) + 1;
      pdf << objNum << " 0 obj\n" << objs[i] << "\nendobj\n";
    }

    const long xrefPos = static_cast<long>(pdf.tellp());
    pdf << "xref\n";
    pdf << "0 " << (objs.size() + 1) << "\n";
    // Object 0 entry
    pdf << "0000000000 65535 f \n";
    // Other entries: 10-digit offset, 5-digit gen, 'n'
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      pdf << buf;
    }

    pdf << "trailer\n";
    pdf << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
    pdf << "startxref\n" << xrefPos << "\n%%EOF\n";

    return pdf.str();
  }

  static std::unique_ptr<PDFDoc> OpenPdfDocFromPath_2458(const std::string &path) {
    auto fname = std::make_unique<GooString>(path.c_str());
    auto doc = std::make_unique<PDFDoc>(std::move(fname));
    if (!doc || !doc->isOk()) {
      return nullptr;
    }
    return doc;
  }
};

TEST_F(PageUnrotateXYTest_2458, Rotation0DoesNotChangeCoordinates_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({0});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 10.0;
  double y = 20.0;
  _page_unrotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 10.0);
  EXPECT_DOUBLE_EQ(y, 20.0);

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, Rotation90TransformsCoordinates_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({90});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  // With MediaBox [0 0 200 100], cropWidth=200, cropHeight=100.
  // For rotate=90, the function's observable behavior should map (x,y) accordingly.
  double x = 10.0;
  double y = 20.0;

  _page_unrotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 180.0);
  EXPECT_DOUBLE_EQ(y, 10.0);

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, Rotation180TransformsCoordinates_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({180});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 10.0;
  double y = 20.0;

  _page_unrotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 190.0);
  EXPECT_DOUBLE_EQ(y, 80.0);

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, Rotation270TransformsCoordinates_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({270});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 10.0;
  double y = 20.0;

  _page_unrotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 20.0);
  EXPECT_DOUBLE_EQ(y, 90.0);

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, BoundaryAtOriginRotation180_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({180});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 0.0;
  double y = 0.0;

  _page_unrotate_xy(page, &x, &y);

  // With cropWidth=200, cropHeight=100
  EXPECT_DOUBLE_EQ(x, 200.0);
  EXPECT_DOUBLE_EQ(y, 100.0);

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, BoundaryOnSwappedHeightRotation90_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({90});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  // For rotate=90, the function uses a "page_height" derived from cropWidth (=200).
  double x = 0.0;
  double y = 200.0;

  _page_unrotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 0.0);
  EXPECT_DOUBLE_EQ(y, 0.0);

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, NonRightAngleRotationLeavesCoordinatesUnchanged_2458) {
  // Poppler typically normalizes /Rotate to multiples of 90; if an unusual value
  // is retained through Page::getRotate(), this verifies the function does not
  // transform unless it matches the handled cases.
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({45});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 10.0;
  double y = 20.0;

  _page_unrotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 10.0);
  EXPECT_DOUBLE_EQ(y, 20.0);

  std::remove(path.c_str());
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PageUnrotateXYTest_2458, DeathOnNullXPointer_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({0});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  double y = 1.0;

  ASSERT_DEATH({ _page_unrotate_xy(page, nullptr, &y); }, "");

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, DeathOnNullYPointer_2458) {
  const std::string path = MakeTempPath_2458(".pdf");
  const std::string pdfBytes = BuildMinimalPdfWithRotations_2458({0});
  WriteFileBytes_2458(path, pdfBytes);

  auto doc = OpenPdfDocFromPath_2458(path);
  ASSERT_NE(doc, nullptr);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 1.0;

  ASSERT_DEATH({ _page_unrotate_xy(page, &x, nullptr); }, "");

  std::remove(path.c_str());
}

TEST_F(PageUnrotateXYTest_2458, DeathOnNullPagePointer_2458) {
  double x = 1.0;
  double y = 2.0;
  ASSERT_DEATH({ _page_unrotate_xy(nullptr, &x, &y); }, "");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace