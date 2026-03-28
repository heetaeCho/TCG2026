// File: page_getCropHeight_709_test.cpp
// Unit tests for Page::getCropHeight()
// TEST_ID = 709

#include <gtest/gtest.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "poppler/GlobalParams.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "goo/GooString.h"

namespace {

// Poppler commonly uses a global GlobalParams instance.
class PopplerGlobalParamsGuard {
public:
  PopplerGlobalParamsGuard() {
    if (!globalParams) {
      globalParams = new GlobalParams();
      owned_ = true;
    }
  }
  ~PopplerGlobalParamsGuard() {
    // Avoid deleting if someone else owns/uses it across tests in the suite.
    // Many poppler test setups intentionally leak globalParams.
    if (owned_) {
      delete globalParams;
      globalParams = nullptr;
    }
  }

private:
  bool owned_ = false;
};

struct Box {
  double x1;
  double y1;
  double x2;
  double y2;
};

static std::string FormatDouble(double v) {
  // Keep PDF numeric output stable and readable.
  std::ostringstream oss;
  oss << std::setprecision(17) << v;
  return oss.str();
}

static std::string MakePdfWithSinglePage(const Box& mediaBox, const Box* cropBoxOrNull) {
  // Objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page (with MediaBox, optional CropBox)
  // 4: Contents (empty stream)
  std::vector<std::string> objs;
  objs.reserve(4);

  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");

  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  std::ostringstream pageDict;
  pageDict << "3 0 obj\n"
              "<< /Type /Page /Parent 2 0 R\n"
              "   /MediaBox ["
           << FormatDouble(mediaBox.x1) << " " << FormatDouble(mediaBox.y1) << " "
           << FormatDouble(mediaBox.x2) << " " << FormatDouble(mediaBox.y2) << "]\n";
  if (cropBoxOrNull) {
    pageDict << "   /CropBox ["
             << FormatDouble(cropBoxOrNull->x1) << " " << FormatDouble(cropBoxOrNull->y1) << " "
             << FormatDouble(cropBoxOrNull->x2) << " " << FormatDouble(cropBoxOrNull->y2) << "]\n";
  }
  pageDict << "   /Contents 4 0 R\n"
              ">>\n"
              "endobj\n";
  objs.push_back(pageDict.str());

  objs.push_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n");

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  // Record offsets (byte offsets from beginning of file).
  std::vector<long long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0);  // xref entry 0 (free object)

  for (const auto& o : objs) {
    offsets.push_back(static_cast<long long>(pdf.tellp()));
    pdf << o;
  }

  const long long xrefPos = static_cast<long long>(pdf.tellp());
  const int size = static_cast<int>(objs.size()) + 1;

  pdf << "xref\n";
  pdf << "0 " << size << "\n";
  // Object 0: free
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i < size; ++i) {
    pdf << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
  }

  pdf << "trailer\n"
         "<< /Size "
      << size
      << " /Root 1 0 R >>\n"
         "startxref\n"
      << xrefPos
      << "\n"
         "%%EOF\n";

  return pdf.str();
}

static std::filesystem::path WriteTempPdf(const std::string& bytes, const std::string& stem) {
  const auto dir = std::filesystem::temp_directory_path();
  const auto path = dir / (stem + ".pdf");

  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();

  return path;
}

static std::unique_ptr<PDFDoc> OpenPdfDoc(const std::filesystem::path& path) {
  auto gooPath = std::make_unique<GooString>(path.string().c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gooPath));
  return doc;
}

}  // namespace

class PageGetCropHeightTest_709 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Ensure globalParams exists for poppler operations.
    guard_ = std::make_unique<PopplerGlobalParamsGuard>();
  }

  static void TearDownTestSuite() { guard_.reset(); }

  static std::unique_ptr<PopplerGlobalParamsGuard> guard_;
};

std::unique_ptr<PopplerGlobalParamsGuard> PageGetCropHeightTest_709::guard_;

// Normal operation: CropBox present, getCropHeight matches (getCropBox()->y2 - y1).
TEST_F(PageGetCropHeightTest_709, CropBoxPresent_HeightMatchesCropBoxDelta_709) {
  const Box media{0.0, 0.0, 200.0, 400.0};
  const Box crop{0.0, 50.0, 200.0, 350.0};  // height = 300

  const auto pdfBytes = MakePdfWithSinglePage(media, &crop);
  const auto pdfPath = WriteTempPdf(pdfBytes, "poppler_getCropHeight_crop_present_709");

  auto doc = OpenPdfDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page* page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const PDFRectangle* cropBox = page->getCropBox();
  ASSERT_NE(cropBox, nullptr);

  const double expected = cropBox->y2 - cropBox->y1;
  EXPECT_DOUBLE_EQ(page->getCropHeight(), expected);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

// Boundary-ish: Fractional coordinates.
TEST_F(PageGetCropHeightTest_709, FractionalCropBox_UsesExactDeltaFromGetCropBox_709) {
  const Box media{0.0, 0.0, 612.0, 792.0};
  const Box crop{10.25, 20.5, 600.75, 770.125};

  const auto pdfBytes = MakePdfWithSinglePage(media, &crop);
  const auto pdfPath = WriteTempPdf(pdfBytes, "poppler_getCropHeight_fractional_709");

  auto doc = OpenPdfDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page* page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const PDFRectangle* cropBox = page->getCropBox();
  ASSERT_NE(cropBox, nullptr);

  const double expected = cropBox->y2 - cropBox->y1;
  EXPECT_DOUBLE_EQ(page->getCropHeight(), expected);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

// Boundary case: "Inverted" crop coordinates as authored in the PDF.
// We do NOT assume poppler normalizes or clips; we only assert getCropHeight
// is consistent with the observable getCropBox() values.
TEST_F(PageGetCropHeightTest_709, InvertedCropY_HeightConsistentWithGetCropBox_709) {
  const Box media{0.0, 0.0, 200.0, 400.0};
  const Box crop{0.0, 300.0, 200.0, 100.0};  // authored y2 < y1

  const auto pdfBytes = MakePdfWithSinglePage(media, &crop);
  const auto pdfPath = WriteTempPdf(pdfBytes, "poppler_getCropHeight_inverted_y_709");

  auto doc = OpenPdfDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page* page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const PDFRectangle* cropBox = page->getCropBox();
  ASSERT_NE(cropBox, nullptr);

  const double expected = cropBox->y2 - cropBox->y1;
  EXPECT_DOUBLE_EQ(page->getCropHeight(), expected);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

// Observable behavior when CropBox is not authored: still ensure getCropHeight
// matches getCropBox() delta (whatever poppler chooses to return).
TEST_F(PageGetCropHeightTest_709, NoCropBoxAuthored_HeightMatchesGetCropBoxDelta_709) {
  const Box media{0.0, 0.0, 200.0, 400.0};

  const auto pdfBytes = MakePdfWithSinglePage(media, nullptr);
  const auto pdfPath = WriteTempPdf(pdfBytes, "poppler_getCropHeight_no_cropbox_709");

  auto doc = OpenPdfDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page* page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const PDFRectangle* cropBox = page->getCropBox();
  ASSERT_NE(cropBox, nullptr);

  const double expected = cropBox->y2 - cropBox->y1;
  EXPECT_DOUBLE_EQ(page->getCropHeight(), expected);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

// Exceptional/error case (observable): opening a non-existent file should fail isOk(),
// so we should not attempt to access pages. This verifies the test harness behavior
// around the interface usage.
TEST_F(PageGetCropHeightTest_709, NonExistentPdf_DocNotOk_709) {
  const auto missingPath = std::filesystem::temp_directory_path() / "poppler_missing_709.pdf";

  auto doc = OpenPdfDoc(missingPath);
  ASSERT_TRUE(doc);
  EXPECT_FALSE(doc->isOk());
}