#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

// Include necessary headers
#include "GooString.h"
#include "ImgWriter.h"

// We need access to the global variables and the function under test
// These are declared in the source files

// Forward declare globals from pdftocairo.cc / pdftoppm.cc
extern double x_resolution;
extern double y_resolution;
extern bool mono;
extern bool gray;
extern bool png;
extern bool jpeg;
extern bool tiff;
extern int jpegQuality;
extern bool jpegProgressive;
extern bool jpegOptimize;
extern bool transp;
extern char tiffCompressionStr[16];
extern unsigned char *icc_data;
extern int icc_data_size;

// Forward declare the function under test
// Note: since it's static, we may need to include the .cc or use a test wrapper
// For testing purposes, we assume a linkable version is available
extern void writePageImage(GooString *filename);

// We also need cairo surface - declared externally
#include <cairo.h>
extern cairo_surface_t *surface;

class WritePageImageTest_2689 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset all globals to default
        x_resolution = 150.0;
        y_resolution = 150.0;
        mono = false;
        gray = false;
        png = false;
        jpeg = false;
        tiff = false;
        jpegQuality = -1;
        jpegProgressive = false;
        jpegOptimize = false;
        transp = false;
        memset(tiffCompressionStr, 0, sizeof(tiffCompressionStr));
        icc_data = nullptr;
        icc_data_size = 0;
    }

    void TearDown() override {
        if (surface) {
            cairo_surface_destroy(surface);
            surface = nullptr;
        }
        // Clean up any temp files
        for (const auto &f : tempFiles) {
            std::remove(f.c_str());
        }
    }

    std::string createTempFilename(const std::string &ext) {
        char tmpl[] = "/tmp/pdftocairo_test_XXXXXX";
        int fd = mkstemp(tmpl);
        if (fd >= 0) close(fd);
        std::string name = std::string(tmpl) + ext;
        std::rename(tmpl, name.c_str());
        tempFiles.push_back(name);
        return name;
    }

    void createSurface(int width, int height) {
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
        // Fill with a known color
        cairo_t *cr = cairo_create(surface);
        cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0); // Red
        cairo_paint(cr);
        cairo_destroy(cr);
    }

    std::vector<std::string> tempFiles;
};

// Test: No writer format selected - function should return early without crash
TEST_F(WritePageImageTest_2689, NoFormatSelectedReturnsEarly_2689) {
    png = false;
    jpeg = false;
    tiff = false;

    createSurface(10, 10);
    std::string fname = createTempFilename(".out");
    GooString filename(fname.c_str());

    // Should return without creating/writing file (no writer)
    writePageImage(&filename);

    // File should not have meaningful content or may not exist
    FILE *f = fopen(fname.c_str(), "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        // File may exist but should be empty or not written to
        EXPECT_EQ(size, 0);
    }
}

#if ENABLE_LIBPNG
// Test: PNG RGB output creates a valid file
TEST_F(WritePageImageTest_2689, PngRgbWritesFile_2689) {
    png = true;
    createSurface(4, 4);
    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: PNG RGBA (transparent) output
TEST_F(WritePageImageTest_2689, PngRgbaTranspWritesFile_2689) {
    png = true;
    transp = true;
    createSurface(4, 4);
    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: PNG gray output
TEST_F(WritePageImageTest_2689, PngGrayWritesFile_2689) {
    png = true;
    gray = true;
    createSurface(4, 4);
    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: PNG monochrome output
TEST_F(WritePageImageTest_2689, PngMonoWritesFile_2689) {
    png = true;
    mono = true;
    createSurface(8, 4);
    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: PNG with 1x1 surface (boundary)
TEST_F(WritePageImageTest_2689, PngSinglePixel_2689) {
    png = true;
    createSurface(1, 1);
    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}
#endif

#if ENABLE_LIBJPEG
// Test: JPEG RGB output
TEST_F(WritePageImageTest_2689, JpegRgbWritesFile_2689) {
    jpeg = true;
    createSurface(8, 8);
    std::string fname = createTempFilename(".jpg");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: JPEG gray output
TEST_F(WritePageImageTest_2689, JpegGrayWritesFile_2689) {
    jpeg = true;
    gray = true;
    createSurface(8, 8);
    std::string fname = createTempFilename(".jpg");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: JPEG with quality setting
TEST_F(WritePageImageTest_2689, JpegWithQualityWritesFile_2689) {
    jpeg = true;
    jpegQuality = 50;
    createSurface(8, 8);
    std::string fname = createTempFilename(".jpg");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: JPEG with progressive and optimize
TEST_F(WritePageImageTest_2689, JpegProgressiveOptimize_2689) {
    jpeg = true;
    jpegProgressive = true;
    jpegOptimize = true;
    createSurface(8, 8);
    std::string fname = createTempFilename(".jpg");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}
#endif

#if ENABLE_LIBTIFF
// Test: TIFF RGB output
TEST_F(WritePageImageTest_2689, TiffRgbWritesFile_2689) {
    tiff = true;
    createSurface(8, 8);
    std::string fname = createTempFilename(".tiff");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: TIFF RGBA (transparent) output
TEST_F(WritePageImageTest_2689, TiffRgbaTranspWritesFile_2689) {
    tiff = true;
    transp = true;
    createSurface(8, 8);
    std::string fname = createTempFilename(".tiff");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: TIFF gray output
TEST_F(WritePageImageTest_2689, TiffGrayWritesFile_2689) {
    tiff = true;
    gray = true;
    createSurface(8, 8);
    std::string fname = createTempFilename(".tiff");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: TIFF monochrome output
TEST_F(WritePageImageTest_2689, TiffMonoWritesFile_2689) {
    tiff = true;
    mono = true;
    createSurface(16, 4);
    std::string fname = createTempFilename(".tiff");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}
#endif

// Test: Writing to stdout via "fd://0"
#if ENABLE_LIBPNG
TEST_F(WritePageImageTest_2689, WriteToStdout_2689) {
    png = true;
    createSurface(2, 2);
    GooString filename("fd://0");

    // Redirect stdout to a temp file to capture output
    std::string tmpname = createTempFilename(".stdout");
    FILE *tmpf = freopen(tmpname.c_str(), "wb", stdout);
    ASSERT_NE(tmpf, nullptr);

    writePageImage(&filename);
    fflush(stdout);

    // Reopen stdout (best effort)
    freopen("/dev/tty", "w", stdout);

    FILE *f = fopen(tmpname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}
#endif

// Test: Large image (boundary test)
#if ENABLE_LIBPNG
TEST_F(WritePageImageTest_2689, PngLargeImage_2689) {
    png = true;
    createSurface(256, 256);
    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}
#endif

// Test: Monochrome with non-multiple-of-8 width (boundary for bit packing)
#if ENABLE_LIBPNG
TEST_F(WritePageImageTest_2689, PngMonoNonMultipleOf8Width_2689) {
    png = true;
    mono = true;
    createSurface(13, 3); // 13 is not a multiple of 8
    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}
#endif

// Test: Transparent PNG with fully transparent pixels (alpha=0 boundary)
#if ENABLE_LIBPNG
TEST_F(WritePageImageTest_2689, PngTransparentAlphaZero_2689) {
    png = true;
    transp = true;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 4, 4);
    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0); // Fully transparent
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint(cr);
    cairo_destroy(cr);

    std::string fname = createTempFilename(".png");
    GooString filename(fname.c_str());

    writePageImage(&filename);

    FILE *f = fopen(fname.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}
#endif
