// PDFDoc_getPageMediaHeight_test_955.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "PDFDoc.h"
#include "goo/GooString.h"

namespace {

// Build a minimal, valid single-page PDF with a known MediaBox.
// Page height = mediaHeight (points), width fixed at 612 (Letter width).
std::string buildSinglePagePdf(double mediaHeight) {
  // Keep numbers stable and simple (avoid scientific notation).
  auto fmtNum = [](double v) {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss << std::setprecision(0) << v; // integer points expected here
    return oss.str();
  };

  const std::string w = "612";
  const std::string h = fmtNum(mediaHeight);

  // Objects 1..4
  const std::vector<std::string> objs = {
      "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n",
      "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n",
      ("3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 " + w + " " + h +
       "] /Contents 4 0 R >>\nendobj\n"),
      // Empty content stream.
      "4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n",
  };

  std::string pdf;
  pdf += "%PDF-1.4\n";

  std::vector<long long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 (free) placeholder for xref formatting

  // Record byte offsets for each object start.
  for (const auto &obj : objs) {
    offsets.push_back(static_cast<long long>(pdf.size()));
    pdf += obj;
  }

  const long long xrefPos = static_cast<long long>(pdf.size());

  std::ostringstream xref;
  xref << "xref\n";
  xref << "0 " << (objs.size() + 1) << "\n";
  xref << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    xref << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
  }

  std::ostringstream trailer;
  trailer << "trailer\n"
          << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n"
          << "startxref\n"
          << xrefPos << "\n"
          << "%%EOF\n";

  pdf += xref.str();
  pdf += trailer.str();
  return pdf;
}

std::filesystem::path writeTempFile(const std::string &contents,
                                   const std::string &suffix) {
  const auto dir = std::filesystem::temp_directory_path();
  // Simple unique-ish name (good enough for unit tests).
  const auto path =
      dir / (std::string("poppler_test_955_") + std::to_string(::getpid()) +
             "_" + std::to_string(reinterpret_cast<uintptr_t>(&contents)) +
             suffix);

  std::ofstream ofs(path, std::ios::binary);
  ofs.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  ofs.close();
  return path;
}

} // namespace

class PDFDocTest_955 : public ::testing::Test {
protected:
  void TearDown() override {
    for (const auto &p : toRemove_) {
      std::error_code ec;
      std::filesystem::remove(p, ec);
    }
    toRemove_.clear();
  }

  std::filesystem::path makeSinglePagePdfFile(double mediaHeight) {
    const std::string pdf = buildSinglePagePdf(mediaHeight);
    auto path = writeTempFile(pdf, ".pdf");
    toRemove_.push_back(path);
    return path;
  }

private:
  std::vector<std::filesystem::path> toRemove_;
};

TEST_F(PDFDocTest_955, ValidPdf_Page1ReturnsMediaHeight_955) {
  constexpr double kExpectedHeight = 792.0;

  const auto pdfPath = makeSinglePagePdfFile(kExpectedHeight);

  auto fileName = std::make_unique<GooString>(pdfPath.string().c_str());
  PDFDoc doc(std::move(fileName), std::nullopt, std::nullopt, []() {});

  ASSERT_TRUE(doc.isOk());

  // Observable behavior: should return Page::getMediaHeight() for an existing page.
  EXPECT_DOUBLE_EQ(doc.getPageMediaHeight(1), kExpectedHeight);
}

TEST_F(PDFDocTest_955, OutOfRangePageNumberReturnsZero_955) {
  constexpr double kHeight = 792.0;
  const auto pdfPath = makeSinglePagePdfFile(kHeight);

  auto fileName = std::make_unique<GooString>(pdfPath.string().c_str());
  PDFDoc doc(std::move(fileName), std::nullopt, std::nullopt, []() {});

  ASSERT_TRUE(doc.isOk());
  ASSERT_EQ(doc.getNumPages(), 1);

  // Boundary/invalid indices (observable via return value).
  EXPECT_DOUBLE_EQ(doc.getPageMediaHeight(0), 0.0);
  EXPECT_DOUBLE_EQ(doc.getPageMediaHeight(-1), 0.0);
  EXPECT_DOUBLE_EQ(doc.getPageMediaHeight(2), 0.0);
  EXPECT_DOUBLE_EQ(doc.getPageMediaHeight(9999), 0.0);
}

TEST_F(PDFDocTest_955, ErrorPdfDocReturnsZero_955) {
  // Exceptional/error case: an error PDFDoc should not have pages; getPageMediaHeight should be 0.0.
  auto fileName = std::make_unique<GooString>("nonexistent_or_error.pdf");
  std::unique_ptr<PDFDoc> err = PDFDoc::ErrorPDFDoc(/*errorCode=*/1, std::move(fileName));
  ASSERT_NE(err, nullptr);

  EXPECT_DOUBLE_EQ(err->getPageMediaHeight(1), 0.0);
  EXPECT_DOUBLE_EQ(err->getPageMediaHeight(0), 0.0);
}

TEST_F(PDFDocTest_955, ValidPdf_MediaHeightMatchesDifferentValue_955) {
  // Normal operation with a different MediaBox height to ensure we don't hardcode expectations.
  constexpr double kExpectedHeight = 1000.0;

  const auto pdfPath = makeSinglePagePdfFile(kExpectedHeight);

  auto fileName = std::make_unique<GooString>(pdfPath.string().c_str());
  PDFDoc doc(std::move(fileName), std::nullopt, std::nullopt, []() {});

  ASSERT_TRUE(doc.isOk());

  EXPECT_DOUBLE_EQ(doc.getPageMediaHeight(1), kExpectedHeight);
}