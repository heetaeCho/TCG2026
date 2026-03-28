// File: test_pdfdoc_getpagecropwidth_956.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <optional>
#include <string>

#include "poppler/PDFDoc.h"
#include "goo/GooString.h"

namespace {

class PDFDocGetPageCropWidthTest_956 : public ::testing::Test {
protected:
  static std::filesystem::path WriteTempPdf(const std::string &pdfBytes, const std::string &stem) {
    const auto dir = std::filesystem::temp_directory_path();
    const auto path = dir / (stem + "_956.pdf");

    std::ofstream os(path, std::ios::binary | std::ios::trunc);
    os.write(pdfBytes.data(), static_cast<std::streamsize>(pdfBytes.size()));
    os.close();

    return path;
  }

  static std::unique_ptr<PDFDoc> OpenPdf(const std::filesystem::path &path) {
    auto fileName = std::make_unique<GooString>(path.string().c_str());
    return std::make_unique<PDFDoc>(std::move(fileName),
                                    std::optional<GooString>{},
                                    std::optional<GooString>{},
                                    []() {});
  }

  static std::string OnePagePdfWithMediaAndCropBoxes() {
    // MediaBox width: 300 (0..300), CropBox width: 200 (0..200)
    // Minimal valid 1-page PDF.
    return std::string(
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R\n"
        "   /MediaBox [0 0 300 500]\n"
        "   /CropBox  [0 0 200 400]\n"
        "   /Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000117 00000 n \n"
        "0000000244 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "300\n"
        "%%EOF\n");
  }

  static std::string OnePagePdfWithMediaBoxOnly() {
    // MediaBox width: 300 (0..300); no CropBox.
    return std::string(
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R\n"
        "   /MediaBox [0 0 300 500]\n"
        "   /Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000117 00000 n \n"
        "0000000226 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "282\n"
        "%%EOF\n");
  }

  static void ExpectNearDouble(double actual, double expected, double eps = 1e-9) {
    ASSERT_TRUE(std::isfinite(actual));
    ASSERT_TRUE(std::isfinite(expected));
    EXPECT_NEAR(actual, expected, eps);
  }
};

TEST_F(PDFDocGetPageCropWidthTest_956, ReturnsZeroWhenPageDoesNotExist_ErrorDoc_956) {
  // ErrorPDFDoc is a public factory; observable behavior here is that getPageCropWidth()
  // should return 0.0 when getPage(page) yields nullptr.
  auto fileName = std::make_unique<GooString>("nonexistent_956.pdf");
  std::unique_ptr<PDFDoc> doc = PDFDoc::ErrorPDFDoc(/*errorCode*/ 1, std::move(fileName));
  ASSERT_TRUE(doc != nullptr);

  ExpectNearDouble(doc->getPageCropWidth(1), 0.0);
  ExpectNearDouble(doc->getPageCropWidth(0), 0.0);
  ExpectNearDouble(doc->getPageCropWidth(-1), 0.0);
  ExpectNearDouble(doc->getPageCropWidth(999999), 0.0);
}

TEST_F(PDFDocGetPageCropWidthTest_956, ReturnsCropBoxWidthWhenCropBoxPresent_956) {
  const auto path = WriteTempPdf(OnePagePdfWithMediaAndCropBoxes(), "with_cropbox");
  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc != nullptr);
  ASSERT_TRUE(doc->isOk());

  // Page numbers in Poppler are 1-based.
  const double cropW = doc->getPageCropWidth(1);
  // CropBox [0 0 200 400] => expected width 200.
  ExpectNearDouble(cropW, 200.0);

  // Also verify it differs from media width for this PDF (observable via public API).
  const double mediaW = doc->getPageMediaWidth(1);
  ExpectNearDouble(mediaW, 300.0);
  EXPECT_NE(cropW, mediaW);
}

TEST_F(PDFDocGetPageCropWidthTest_956, CropWidthMatchesMediaWidthWhenNoCropBox_956) {
  const auto path = WriteTempPdf(OnePagePdfWithMediaBoxOnly(), "media_only");
  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc != nullptr);
  ASSERT_TRUE(doc->isOk());

  const double cropW = doc->getPageCropWidth(1);
  const double mediaW = doc->getPageMediaWidth(1);

  // This test checks a relationship observable through the public interface,
  // without asserting internal details of Page::getCropWidth().
  ExpectNearDouble(mediaW, 300.0);
  ExpectNearDouble(cropW, mediaW);
}

TEST_F(PDFDocGetPageCropWidthTest_956, ReturnsZeroForOutOfRangePagesOnValidDoc_956) {
  const auto path = WriteTempPdf(OnePagePdfWithMediaAndCropBoxes(), "range_checks");
  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc != nullptr);
  ASSERT_TRUE(doc->isOk());

  ASSERT_EQ(doc->getNumPages(), 1);

  // Out-of-range page indices should behave like "no page" for getPageCropWidth().
  ExpectNearDouble(doc->getPageCropWidth(0), 0.0);
  ExpectNearDouble(doc->getPageCropWidth(-123), 0.0);
  ExpectNearDouble(doc->getPageCropWidth(2), 0.0);
  ExpectNearDouble(doc->getPageCropWidth(1000), 0.0);
}

} // namespace