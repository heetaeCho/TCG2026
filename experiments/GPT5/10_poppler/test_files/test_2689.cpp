// writePageImage_test_2689.cc
//
// Unit tests for static writePageImage(GooString *filename) in utils/pdftocairo.cc
// Constraints honored: treat implementation as black-box; verify only observable effects.

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/stat.h>

#if defined(_WIN32)
#  include <io.h>
#  include <fcntl.h>
#  define STAT _stat
#  define stat _stat
#else
#  include <unistd.h>
#  define STAT stat
#endif

#include <cairo/cairo.h>

// If pdftocairo.cc defines a main(), avoid collision when including it into the test TU.
#define main pdftocairo_main_2689
#include "./TestProjects/poppler/utils/pdftocairo.cc"
#undef main

namespace {

static bool FileExists(const std::string &path) {
  struct STAT st;
  return stat(path.c_str(), &st) == 0;
}

static long FileSize(const std::string &path) {
  struct STAT st;
  if (stat(path.c_str(), &st) != 0) return -1;
#if defined(_WIN32)
  return static_cast<long>(st.st_size);
#else
  return static_cast<long>(st.st_size);
#endif
}

static std::string MakeTempPath(const char *suffix) {
#if defined(_WIN32)
  // On Windows, fall back to tmpnam + suffix (best-effort for tests).
  char buf[L_tmpnam];
  std::tmpnam(buf);
  return std::string(buf) + suffix;
#else
  std::string tmpl = std::string("/tmp/pdftocairo_writePageImage_2689_XXXXXX");
  std::vector<char> writable(tmpl.begin(), tmpl.end());
  writable.push_back('\0');
  int fd = ::mkstemp(writable.data());
  if (fd >= 0) ::close(fd);
  std::string base(writable.data());
  // Remove the file created by mkstemp; writePageImage will create it.
  ::unlink(base.c_str());
  return base + suffix;
#endif
}

class WritePageImageTest_2689 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset the global flags used by writePageImage.
    png = false;
    jpeg = false;
    tiff = false;
    gray = false;
    mono = false;
    transp = false;

    jpegQuality = -1;
    jpegProgressive = false;
    jpegOptimize = false;

    x_resolution = 150.0;
    y_resolution = 150.0;

    tiffCompressionStr[0] = '\0';
    icc_data = nullptr;
    icc_data_size = 0;

    // Create a small ARGB32 surface and paint something non-transparent.
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 2, 2);
    ASSERT_NE(surface, nullptr);

    cairo_t *cr = cairo_create(surface);
    ASSERT_NE(cr, nullptr);

    cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0); // opaque red
    cairo_paint(cr);

    cairo_destroy(cr);
    cairo_surface_flush(surface);
  }

  void TearDown() override {
    if (surface) {
      cairo_surface_destroy(surface);
      surface = nullptr;
    }
  }
};

TEST_F(WritePageImageTest_2689, NoWriterSelected_DoesNotCreateOutputFile_2689) {
  // No format flags set => writer stays null => function returns early.
  const std::string out = MakeTempPath(".img");

  EXPECT_FALSE(FileExists(out));
  GooString fname(out.c_str());
  writePageImage(&fname);

  EXPECT_FALSE(FileExists(out));
}

#if ENABLE_LIBPNG
TEST_F(WritePageImageTest_2689, PngSelected_WritesNonEmptyFile_2689) {
  png = true;

  const std::string out = MakeTempPath(".png");
  EXPECT_FALSE(FileExists(out));

  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}

TEST_F(WritePageImageTest_2689, PngGrayMode_WritesNonEmptyFile_2689) {
  png = true;
  gray = true;

  const std::string out = MakeTempPath(".png");
  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}

TEST_F(WritePageImageTest_2689, PngMonoMode_WritesNonEmptyFile_2689) {
  png = true;
  mono = true;

  // Use a 1x1 surface to cover a boundary size.
  cairo_surface_destroy(surface);
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
  ASSERT_NE(surface, nullptr);
  cairo_t *cr = cairo_create(surface);
  cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
  cairo_paint(cr);
  cairo_destroy(cr);
  cairo_surface_flush(surface);

  const std::string out = MakeTempPath(".png");
  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}

TEST_F(WritePageImageTest_2689, FilenameFd0_WritesToStdout_2689) {
  png = true;

  // Capture stdout bytes; content is binary, but CaptureStdout supports it.
  testing::internal::CaptureStdout();
  GooString fname("fd://0");
  writePageImage(&fname);
  std::string captured = testing::internal::GetCapturedStdout();

  EXPECT_FALSE(captured.empty());
}
#endif  // ENABLE_LIBPNG

#if ENABLE_LIBJPEG
TEST_F(WritePageImageTest_2689, JpegSelected_WritesNonEmptyFile_2689) {
  jpeg = true;

  const std::string out = MakeTempPath(".jpg");
  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}

TEST_F(WritePageImageTest_2689, JpegGrayMode_WritesNonEmptyFile_2689) {
  jpeg = true;
  gray = true;

  const std::string out = MakeTempPath(".jpg");
  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}

TEST_F(WritePageImageTest_2689, JpegQualityAndFlags_WritesNonEmptyFile_2689) {
  jpeg = true;
  jpegQuality = 85;
  jpegOptimize = true;
  jpegProgressive = true;

  const std::string out = MakeTempPath(".jpg");
  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}
#endif  // ENABLE_LIBJPEG

#if ENABLE_LIBTIFF
TEST_F(WritePageImageTest_2689, TiffSelected_WritesNonEmptyFile_2689) {
  tiff = true;

  const std::string out = MakeTempPath(".tif");
  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}

TEST_F(WritePageImageTest_2689, TiffWithTransparency_WritesNonEmptyFile_2689) {
  tiff = true;
  transp = true;

  // Paint semi-transparent pixels to exercise alpha path.
  cairo_t *cr = cairo_create(surface);
  cairo_set_source_rgba(cr, 0.0, 1.0, 0.0, 0.5);
  cairo_paint(cr);
  cairo_destroy(cr);
  cairo_surface_flush(surface);

  const std::string out = MakeTempPath(".tif");
  GooString fname(out.c_str());
  writePageImage(&fname);

  ASSERT_TRUE(FileExists(out));
  EXPECT_GT(FileSize(out), 0);

  std::remove(out.c_str());
}
#endif  // ENABLE_LIBTIFF

TEST_F(WritePageImageTest_2689, OpenFileFailure_ExitsWithCode2_2689) {
  // Choose any enabled writer; otherwise function returns early and won't hit fopen/exit.
#if ENABLE_LIBPNG
  png = true;
#elif ENABLE_LIBJPEG
  jpeg = true;
#elif ENABLE_LIBTIFF
  tiff = true;
#else
  GTEST_SKIP() << "No image backend enabled (LIBPNG/LIBJPEG/LIBTIFF); cannot observe error exit.";
#endif

  // Path that should fail to open for writing.
  // (Non-existent directory is the usual portable approach.)
  const std::string badPath = "/this_directory_should_not_exist_2689/out.png";
  ASSERT_FALSE(FileExists("/this_directory_should_not_exist_2689/out.png"));

  ASSERT_EXIT(
      {
        // Ensure a surface exists in the child process.
        if (!surface) {
          surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
        }
        GooString fname(badPath.c_str());
        writePageImage(&fname);
        std::exit(0);  // Should not reach
      },
      ::testing::ExitedWithCode(2),
      "Error opening output file");
}

}  // namespace