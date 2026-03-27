// save_page_slice_test_2654.cc
//
// Unit tests for static savePageSlice() in utils/pdftoppm.cc
// TEST_ID: 2654
//
// Notes:
// - We treat the implementation as a black box.
// - We include pdftoppm.cc into this test TU (with main renamed) so we can call the
//   file-local static function without modifying production code.
// - We focus on observable behavior: file/stdout output, stderr progress output, and exit-on-error.

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/SplashOutputDev.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashErrorCodes.h"

// --- Bring the static function into this translation unit ---
#define main pdftoppm_main_ignored_for_tests_2654
#include "utils/pdftoppm.cc"
#undef main

namespace {

namespace fs = std::filesystem;

struct GlobalFlagsGuard_2654 {
  int lastPage_old;
  double xres_old;
  double yres_old;
  bool useCropBox_old;
  bool png_old;
  bool jpeg_old;
  bool jpegcmyk_old;
  bool tiff_old;
  int jpegQuality_old;
  bool jpegProgressive_old;
  bool jpegOptimize_old;
  char tiffCompression_old[16];
  bool progress_old;

  GlobalFlagsGuard_2654() {
    lastPage_old = ::lastPage;
    xres_old = ::x_resolution;
    yres_old = ::y_resolution;
    useCropBox_old = ::useCropBox;
    png_old = ::png;
    jpeg_old = ::jpeg;
    jpegcmyk_old = ::jpegcmyk;
    tiff_old = ::tiff;
    jpegQuality_old = ::jpegQuality;
    jpegProgressive_old = ::jpegProgressive;
    jpegOptimize_old = ::jpegOptimize;
    std::memset(tiffCompression_old, 0, sizeof(tiffCompression_old));
    std::memcpy(tiffCompression_old, ::TiffCompressionStr,
                std::min<size_t>(sizeof(tiffCompression_old), sizeof(::TiffCompressionStr)));
    progress_old = ::progress;
  }

  ~GlobalFlagsGuard_2654() {
    ::lastPage = lastPage_old;
    ::x_resolution = xres_old;
    ::y_resolution = yres_old;
    ::useCropBox = useCropBox_old;
    ::png = png_old;
    ::jpeg = jpeg_old;
    ::jpegcmyk = jpegcmyk_old;
    ::tiff = tiff_old;
    ::jpegQuality = jpegQuality_old;
    ::jpegProgressive = jpegProgressive_old;
    ::jpegOptimize = jpegOptimize_old;
    std::memset(::TiffCompressionStr, 0, sizeof(::TiffCompressionStr));
    std::memcpy(::TiffCompressionStr, tiffCompression_old,
                std::min<size_t>(sizeof(tiffCompression_old), sizeof(::TiffCompressionStr)));
    ::progress = progress_old;
  }
};

static std::string BuildMinimalSinglePagePdf_2654() {
  // Build a tiny, valid PDF with one page of size 10x10 user units and empty content stream.
  // We compute xref offsets precisely to avoid relying on any external PDF fixtures.
  struct Obj {
    int num;
    std::string body;
  };
  std::vector<Obj> objs;
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10] "
                  "/Contents 4 0 R /Resources << >> >>"});
  // Empty stream
  objs.push_back({4, "<< /Length 0 >>\nstream\n\nendstream"});

  std::string out;
  out += "%PDF-1.4\n";
  std::vector<long long> offsets(5, 0);  // index by obj number, 0 unused except xref entry 0
  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long long>(out.size());
    out += std::to_string(o.num) + " 0 obj\n";
    out += o.body + "\n";
    out += "endobj\n";
  }

  const long long xref_pos = static_cast<long long>(out.size());
  out += "xref\n";
  out += "0 5\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 4; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", offsets[i]);
    out += buf;
  }
  out += "trailer\n";
  out += "<< /Size 5 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

static fs::path WriteTempFile_2654(const fs::path &dir, const std::string &name,
                                  const std::string &bytes) {
  fs::create_directories(dir);
  fs::path p = dir / name;
  std::ofstream ofs(p, std::ios::binary);
  ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  ofs.close();
  return p;
}

static std::unique_ptr<PDFDoc> OpenPdfDoc_2654(const fs::path &pdfPath) {
  auto gs = std::make_unique<GooString>(pdfPath.string().c_str());
  return std::make_unique<PDFDoc>(std::move(gs), std::nullopt, std::nullopt, []() {});
}

static std::unique_ptr<SplashOutputDev> MakeSplashOut_2654() {
  SplashColor paper;
  paper[0] = 0xff;
  paper[1] = 0xff;
  paper[2] = 0xff;

  // The exact thin line mode / overprint preview choice is not observable from the interface here.
  // We just need a usable SplashOutputDev instance.
  return std::make_unique<SplashOutputDev>(splashModeRGB8, /*bitmapRowPadA=*/1, paper,
                                           /*bitmapTopDownA=*/true, splashThinLineDefault,
                                           /*overprintPreviewA=*/false);
}

static long long FileSize_2654(const fs::path &p) {
  std::error_code ec;
  auto sz = fs::file_size(p, ec);
  if (ec) return -1;
  return static_cast<long long>(sz);
}

class SavePageSliceTest_2654 : public ::testing::Test {
protected:
  fs::path tmpDir;

  void SetUp() override {
    tmpDir = fs::temp_directory_path() / "poppler_savePageSlice_tests_2654";
    std::error_code ec;
    fs::remove_all(tmpDir, ec);
    fs::create_directories(tmpDir);
  }

  void TearDown() override {
    std::error_code ec;
    fs::remove_all(tmpDir, ec);
  }
};

TEST_F(SavePageSliceTest_2654, WritesPNMFileWhenNoFormatFlagsAndFileProvided_2654) {
  GlobalFlagsGuard_2654 guard;

  // Arrange: minimal PDF and objects
  const auto pdfBytes = BuildMinimalSinglePagePdf_2654();
  const auto pdfPath = WriteTempFile_2654(tmpDir, "onepage_2654.pdf", pdfBytes);

  auto doc = OpenPdfDoc_2654(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  auto splashOut = MakeSplashOut_2654();
  ASSERT_TRUE(splashOut);
  splashOut->startDoc(doc.get());

  ::png = false;
  ::jpeg = false;
  ::jpegcmyk = false;
  ::tiff = false;
  ::useCropBox = false;

  const int page = 1;
  const double pg_w = doc->getPageMediaWidth(page);
  const double pg_h = doc->getPageMediaHeight(page);
  ASSERT_GT(pg_w, 0);
  ASSERT_GT(pg_h, 0);

  ::lastPage = page;
  ::progress = false;

  const fs::path outPnm = tmpDir / "out_2654.pnm";
  std::string outPnmStr = outPnm.string(); // stable buffer for char*
  char *outFile = outPnmStr.data();

  // Act: w=0,h=0 means "full page" per the observable interface contract of this function.
  ASSERT_NO_FATAL_FAILURE(savePageSlice(doc.get(), splashOut.get(), page,
                                       /*x=*/0, /*y=*/0, /*w=*/0, /*h=*/0,
                                       pg_w, pg_h, outFile));

  // Assert: output file exists and is non-empty
  EXPECT_TRUE(fs::exists(outPnm));
  EXPECT_GT(FileSize_2654(outPnm), 0);
}

TEST_F(SavePageSliceTest_2654, ClipsSliceToPageBoundsAndStillWritesOutput_2654) {
  GlobalFlagsGuard_2654 guard;

  const auto pdfBytes = BuildMinimalSinglePagePdf_2654();
  const auto pdfPath = WriteTempFile_2654(tmpDir, "onepage_clip_2654.pdf", pdfBytes);

  auto doc = OpenPdfDoc_2654(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  auto splashOut = MakeSplashOut_2654();
  ASSERT_TRUE(splashOut);
  splashOut->startDoc(doc.get());

  ::png = false;
  ::jpeg = false;
  ::jpegcmyk = false;
  ::tiff = false;
  ::useCropBox = false;
  ::progress = false;

  const int page = 1;
  const double pg_w = doc->getPageMediaWidth(page);
  const double pg_h = doc->getPageMediaHeight(page);
  ASSERT_GT(pg_w, 0);
  ASSERT_GT(pg_h, 0);

  // Deliberately request a slice that extends beyond the page.
  const int x = static_cast<int>(std::max(0.0, pg_w - 2.0));
  const int y = static_cast<int>(std::max(0.0, pg_h - 2.0));
  const int w = 100000; // huge on purpose
  const int h = 100000;

  const fs::path outPnm = tmpDir / "out_clip_2654.pnm";
  std::string outPnmStr = outPnm.string();
  char *outFile = outPnmStr.data();

  ASSERT_NO_FATAL_FAILURE(savePageSlice(doc.get(), splashOut.get(), page,
                                       x, y, w, h, pg_w, pg_h, outFile));

  EXPECT_TRUE(fs::exists(outPnm));
  EXPECT_GT(FileSize_2654(outPnm), 0);
}

TEST_F(SavePageSliceTest_2654, PrintsProgressLineToStderrWhenEnabled_2654) {
  GlobalFlagsGuard_2654 guard;

  const auto pdfBytes = BuildMinimalSinglePagePdf_2654();
  const auto pdfPath = WriteTempFile_2654(tmpDir, "onepage_progress_2654.pdf", pdfBytes);

  auto doc = OpenPdfDoc_2654(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  auto splashOut = MakeSplashOut_2654();
  ASSERT_TRUE(splashOut);
  splashOut->startDoc(doc.get());

  ::png = false;
  ::jpeg = false;
  ::jpegcmyk = false;
  ::tiff = false;
  ::useCropBox = false;

  const int page = 1;
  const double pg_w = doc->getPageMediaWidth(page);
  const double pg_h = doc->getPageMediaHeight(page);

  ::lastPage = 7;     // observable in progress output
  ::progress = true;  // enable progress line

  const fs::path outPnm = tmpDir / "out_progress_2654.pnm";
  std::string outPnmStr = outPnm.string();
  char *outFile = outPnmStr.data();

  testing::internal::CaptureStderr();
  savePageSlice(doc.get(), splashOut.get(), page,
                /*x=*/0, /*y=*/0, /*w=*/0, /*h=*/0, pg_w, pg_h, outFile);
  const std::string err = testing::internal::GetCapturedStderr();

  // Expected format: "<pg> <lastPage> <filename>\n"
  EXPECT_NE(err.find("1 7 "), std::string::npos);
  EXPECT_NE(err.find(outPnm.string()), std::string::npos);
}

TEST_F(SavePageSliceTest_2654, ExitsWithFailureWhenImageWriteReturnsError_2654) {
  GlobalFlagsGuard_2654 guard;

  const auto pdfBytes = BuildMinimalSinglePagePdf_2654();
  const auto pdfPath = WriteTempFile_2654(tmpDir, "onepage_exit_2654.pdf", pdfBytes);

  auto doc = OpenPdfDoc_2654(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  auto splashOut = MakeSplashOut_2654();
  ASSERT_TRUE(splashOut);
  splashOut->startDoc(doc.get());

  // Force the code path that uses writePNMFile(char*), which reports errors via SplashError.
  ::png = false;
  ::jpeg = false;
  ::jpegcmyk = false;
  ::tiff = false;
  ::useCropBox = false;
  ::progress = false;

  const int page = 1;
  const double pg_w = doc->getPageMediaWidth(page);
  const double pg_h = doc->getPageMediaHeight(page);

  // Use a path in a non-existent directory so file open should fail.
  const fs::path badPath = tmpDir / "does_not_exist_2654" / "out.pnm";
  std::string badPathStr = badPath.string();
  char *badFile = badPathStr.data();

  EXPECT_EXIT(
      savePageSlice(doc.get(), splashOut.get(), page,
                    /*x=*/0, /*y=*/0, /*w=*/0, /*h=*/0, pg_w, pg_h, badFile),
      ::testing::ExitedWithCode(EXIT_FAILURE),
      "Could not write image to");
}

TEST_F(SavePageSliceTest_2654, WritesToStdoutWhenNoFilenameProvided_2654) {
  GlobalFlagsGuard_2654 guard;

  const auto pdfBytes = BuildMinimalSinglePagePdf_2654();
  const auto pdfPath = WriteTempFile_2654(tmpDir, "onepage_stdout_2654.pdf", pdfBytes);

  auto doc = OpenPdfDoc_2654(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  auto splashOut = MakeSplashOut_2654();
  ASSERT_TRUE(splashOut);
  splashOut->startDoc(doc.get());

  ::png = false;
  ::jpeg = false;
  ::jpegcmyk = false;
  ::tiff = false;
  ::useCropBox = false;
  ::progress = false;

  const int page = 1;
  const double pg_w = doc->getPageMediaWidth(page);
  const double pg_h = doc->getPageMediaHeight(page);

  // Redirect stdout to a file so we can observe bytes were produced.
  const fs::path outStd = tmpDir / "stdout_capture_2654.bin";
  std::FILE *origStdout = stdout;

  std::FILE *f = std::fopen(outStd.string().c_str(), "wb");
  ASSERT_NE(f, nullptr);

#if defined(_WIN32) || defined(__CYGWIN__)
  // pdftoppm.cc will setmode(stdout) in this code path; we just need a valid FILE*.
#endif

  stdout = f;
  savePageSlice(doc.get(), splashOut.get(), page,
                /*x=*/0, /*y=*/0, /*w=*/0, /*h=*/0, pg_w, pg_h,
                /*ppmFile=*/nullptr);
  std::fflush(stdout);

  // Restore stdout and close file.
  stdout = origStdout;
  std::fclose(f);

  EXPECT_TRUE(fs::exists(outStd));
  EXPECT_GT(FileSize_2654(outStd), 0);
}

}  // namespace