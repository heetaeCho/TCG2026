// File: poppler-page-rotate-xy-test_2457.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Page.h"

// Function under test (defined in glib/poppler-page.cc)
void _page_rotate_xy(Page *page, double *x, double *y);

namespace {

class GlobalParamsGuard_2457 {
public:
  GlobalParamsGuard_2457() {
    // Poppler uses a global GlobalParams* named globalParams in many builds.
    // Ensure it exists for PDFDoc parsing.
    if (!globalParams) {
      globalParams = new GlobalParams();
      created_ = true;
    }
  }

  ~GlobalParamsGuard_2457() {
    if (created_) {
      delete globalParams;
      globalParams = nullptr;
    }
  }

private:
  bool created_ = false;
};

static std::string BuildSinglePagePdf_2457(int rotate_degrees,
                                           double crop_w,
                                           double crop_h) {
  // Minimal, valid PDF with one page.
  // We generate xref offsets programmatically to avoid hardcoding.
  auto fmt = [](const char *s) { return std::string(s); };

  std::vector<std::string> objs;
  objs.reserve(6);

  // 1: Catalog
  objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  // 2: Pages
  objs.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

  // 3: Page (MediaBox and CropBox are same for simplicity; rotate configurable)
  {
    char buf[512];
    // Use a simple empty contents stream
    // MediaBox [0 0 crop_w crop_h]
    // CropBox  [0 0 crop_w crop_h]
    std::snprintf(buf,
                  sizeof(buf),
                  "3 0 obj\n"
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 %.0f %.0f]\n"
                  "   /CropBox [0 0 %.0f %.0f]\n"
                  "   /Rotate %d\n"
                  "   /Resources << >>\n"
                  "   /Contents 4 0 R\n"
                  ">>\n"
                  "endobj\n",
                  crop_w,
                  crop_h,
                  crop_w,
                  crop_h,
                  rotate_degrees);
    objs.push_back(std::string(buf));
  }

  // 4: Contents (empty stream)
  objs.push_back("4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n");

  // Build final PDF with xref
  std::string pdf;
  pdf += "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.resize(5, 0); // objects 0..4

  // object 0 is free entry
  for (int i = 1; i <= 4; ++i) {
    offsets[i] = static_cast<long>(pdf.size());
    pdf += objs[i - 1];
  }

  const long xref_pos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 5\n";
  pdf += "0000000000 65535 f \n";

  for (int i = 1; i <= 4; ++i) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", offsets[i]);
    pdf += line;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 5 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos);
  pdf += "\n%%EOF\n";

  return pdf;
}

static std::string WriteTempPdf_2457(const std::string &bytes) {
  gchar *tmp_path = nullptr;
  gint fd = g_file_open_tmp("poppler_rotate_xy_XXXXXX.pdf", &tmp_path, nullptr);
  if (fd < 0 || !tmp_path) {
    if (tmp_path) {
      g_free(tmp_path);
    }
    return std::string();
  }

  const char *data = bytes.data();
  size_t remaining = bytes.size();
  while (remaining > 0) {
    const ssize_t written = write(fd, data, remaining);
    if (written <= 0) {
      close(fd);
      g_remove(tmp_path);
      std::string out;
      g_free(tmp_path);
      return out;
    }
    data += written;
    remaining -= static_cast<size_t>(written);
  }

  close(fd);
  std::string path(tmp_path);
  g_free(tmp_path);
  return path;
}

static std::unique_ptr<PDFDoc> LoadPdfDoc_2457(const std::string &path) {
  // Use the common Poppler ctor that takes std::unique_ptr<GooString>.
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  if (!doc || !doc->isOk()) {
    return nullptr;
  }
  return doc;
}

class PageRotateXyTest_2457 : public ::testing::Test {
protected:
  GlobalParamsGuard_2457 gp_;
};

} // namespace

TEST_F(PageRotateXyTest_2457, Rotation0DoesNotChangeCoordinates_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/0, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 10.0, y = 20.0;
  _page_rotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 10.0);
  EXPECT_DOUBLE_EQ(y, 20.0);

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, Rotation90RotatesUsingCropDimensions_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/90, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  // For 90° in the implementation:
  // page_height = cropWidth (200), page_width = cropHeight (100)
  // temp = x; x = y; y = page_height - temp
  double x = 10.0, y = 20.0;
  _page_rotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 20.0);
  EXPECT_DOUBLE_EQ(y, 200.0 - 10.0);

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, Rotation180RotatesUsingCropDimensions_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/180, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  // For 180°:
  // page_width = cropWidth (200), page_height = cropHeight (100)
  // x = page_width - x; y = page_height - y
  double x = 10.0, y = 20.0;
  _page_rotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 200.0 - 10.0);
  EXPECT_DOUBLE_EQ(y, 100.0 - 20.0);

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, Rotation270RotatesUsingCropDimensions_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/270, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  // For 270°:
  // page_height = cropWidth (200), page_width = cropHeight (100)
  // temp = x; x = page_width - y; y = temp
  double x = 10.0, y = 20.0;
  _page_rotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 100.0 - 20.0);
  EXPECT_DOUBLE_EQ(y, 10.0);

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, NonRightAngleRotationLeavesCoordinatesUnchanged_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/45, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 10.0, y = 20.0;
  _page_rotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 10.0);
  EXPECT_DOUBLE_EQ(y, 20.0);

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, BoundaryCoordinatesAtEdges_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/180, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  // x=0,y=0 -> becomes (200,100) for 180°
  {
    double x = 0.0, y = 0.0;
    _page_rotate_xy(page, &x, &y);
    EXPECT_DOUBLE_EQ(x, 200.0);
    EXPECT_DOUBLE_EQ(y, 100.0);
  }

  // x=200,y=100 -> becomes (0,0) for 180°
  {
    double x = 200.0, y = 100.0;
    _page_rotate_xy(page, &x, &y);
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
  }

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, NegativeCoordinatesAreTransformedConsistently_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/90, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  // For 90°: x'=y, y'=cropWidth - x
  double x = -5.0, y = 12.0;
  _page_rotate_xy(page, &x, &y);

  EXPECT_DOUBLE_EQ(x, 12.0);
  EXPECT_DOUBLE_EQ(y, 200.0 - (-5.0));

  g_remove(path.c_str());
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PageRotateXyTest_2457, DiesOnNullXPointer_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/0, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  double y = 1.0;
  EXPECT_DEATH(_page_rotate_xy(page, nullptr, &y), "");

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, DiesOnNullYPointer_2457) {
  const std::string pdf = BuildSinglePagePdf_2457(/*rotate=*/0, /*crop_w=*/200, /*crop_h=*/100);
  const std::string path = WriteTempPdf_2457(pdf);
  ASSERT_FALSE(path.empty());

  auto doc = LoadPdfDoc_2457(path);
  ASSERT_TRUE(doc);
  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);

  double x = 1.0;
  EXPECT_DEATH(_page_rotate_xy(page, &x, nullptr), "");

  g_remove(path.c_str());
}

TEST_F(PageRotateXyTest_2457, DiesOnNullPagePointer_2457) {
  double x = 1.0, y = 2.0;
  EXPECT_DEATH(_page_rotate_xy(nullptr, &x, &y), "");
}
#endif