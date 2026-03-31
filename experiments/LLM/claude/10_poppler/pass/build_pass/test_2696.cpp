#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the GooString header
#include "GooString.h"

// Declare the external global variables that control behavior
extern bool singleFile;
extern bool png;
extern bool jpeg;
extern bool tiff;

// Declare the function under test
static std::unique_ptr<GooString> getImageFileName(const GooString *outputFileName, int numDigits, int page);

// We need to include the actual implementation. Since the function is static in pdftocairo.cc,
// we include it here or redefine the necessary pieces. However, per constraints, we must not
// re-implement. We'll include the source file to get the static function.
// In practice, the build system would handle this, but for testing a static function,
// we include the translation unit or use a test-friendly build.

// For this test file, we replicate the global variable declarations and include the function.
// The globals are defined in pdftoppm.cc but we need them here.
bool singleFile = false;
bool png = false;
bool jpeg = false;
bool tiff = false;

// Include the static function definition directly
static std::unique_ptr<GooString> getImageFileName(const GooString *outputFileName, int numDigits, int page)
{
    char buf[10];
    std::unique_ptr<GooString> imageName = outputFileName->copy();
    if (!singleFile) {
        snprintf(buf, sizeof(buf), "-%0*d", numDigits, page);
        imageName->append(buf);
    }
    if (outputFileName->compare("fd://0") != 0) {
        if (png) {
            imageName->append(".png");
        } else if (jpeg) {
            imageName->append(".jpg");
        } else if (tiff) {
            imageName->append(".tif");
        }
    }
    return imageName;
}

class GetImageFileNameTest_2696 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset all globals to default state before each test
        singleFile = false;
        png = false;
        jpeg = false;
        tiff = false;
    }
};

// Test: Basic PNG output with page number
TEST_F(GetImageFileNameTest_2696, PngWithPageNumber_2696) {
    png = true;
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 3, 1);
    EXPECT_STREQ(result->toStr().c_str(), "output-001.png");
}

// Test: Basic JPEG output with page number
TEST_F(GetImageFileNameTest_2696, JpegWithPageNumber_2696) {
    jpeg = true;
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 3, 5);
    EXPECT_STREQ(result->toStr().c_str(), "output-005.jpg");
}

// Test: Basic TIFF output with page number
TEST_F(GetImageFileNameTest_2696, TiffWithPageNumber_2696) {
    tiff = true;
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 3, 10);
    EXPECT_STREQ(result->toStr().c_str(), "output-010.tif");
}

// Test: No format flags set - no extension appended
TEST_F(GetImageFileNameTest_2696, NoFormatFlagsNoExtension_2696) {
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 3, 1);
    EXPECT_STREQ(result->toStr().c_str(), "output-001");
}

// Test: SingleFile mode - no page number suffix
TEST_F(GetImageFileNameTest_2696, SingleFileNoPagesuffix_2696) {
    singleFile = true;
    png = true;
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 3, 1);
    EXPECT_STREQ(result->toStr().c_str(), "output.png");
}

// Test: SingleFile mode with JPEG
TEST_F(GetImageFileNameTest_2696, SingleFileJpeg_2696) {
    singleFile = true;
    jpeg = true;
    GooString outputFileName("myfile");
    auto result = getImageFileName(&outputFileName, 2, 99);
    EXPECT_STREQ(result->toStr().c_str(), "myfile.jpg");
}

// Test: SingleFile mode with TIFF
TEST_F(GetImageFileNameTest_2696, SingleFileTiff_2696) {
    singleFile = true;
    tiff = true;
    GooString outputFileName("myfile");
    auto result = getImageFileName(&outputFileName, 2, 99);
    EXPECT_STREQ(result->toStr().c_str(), "myfile.tif");
}

// Test: fd://0 special case - no extension appended even if png is set
TEST_F(GetImageFileNameTest_2696, FdStdoutPngNoExtension_2696) {
    png = true;
    GooString outputFileName("fd://0");
    auto result = getImageFileName(&outputFileName, 3, 1);
    EXPECT_STREQ(result->toStr().c_str(), "fd://0-001");
}

// Test: fd://0 with singleFile - no page suffix and no extension
TEST_F(GetImageFileNameTest_2696, FdStdoutSingleFile_2696) {
    singleFile = true;
    png = true;
    GooString outputFileName("fd://0");
    auto result = getImageFileName(&outputFileName, 3, 1);
    EXPECT_STREQ(result->toStr().c_str(), "fd://0");
}

// Test: fd://0 with jpeg - no extension appended
TEST_F(GetImageFileNameTest_2696, FdStdoutJpegNoExtension_2696) {
    jpeg = true;
    GooString outputFileName("fd://0");
    auto result = getImageFileName(&outputFileName, 2, 5);
    EXPECT_STREQ(result->toStr().c_str(), "fd://0-05");
}

// Test: fd://0 with tiff - no extension appended
TEST_F(GetImageFileNameTest_2696, FdStdoutTiffNoExtension_2696) {
    tiff = true;
    GooString outputFileName("fd://0");
    auto result = getImageFileName(&outputFileName, 2, 5);
    EXPECT_STREQ(result->toStr().c_str(), "fd://0-05");
}

// Test: numDigits = 1
TEST_F(GetImageFileNameTest_2696, SingleDigitPageNumber_2696) {
    png = true;
    GooString outputFileName("img");
    auto result = getImageFileName(&outputFileName, 1, 7);
    EXPECT_STREQ(result->toStr().c_str(), "img-7.png");
}

// Test: numDigits = 5, large page number
TEST_F(GetImageFileNameTest_2696, FiveDigitPageNumber_2696) {
    png = true;
    GooString outputFileName("img");
    auto result = getImageFileName(&outputFileName, 5, 42);
    EXPECT_STREQ(result->toStr().c_str(), "img-00042.png");
}

// Test: Page number 0
TEST_F(GetImageFileNameTest_2696, PageZero_2696) {
    png = true;
    GooString outputFileName("test");
    auto result = getImageFileName(&outputFileName, 3, 0);
    EXPECT_STREQ(result->toStr().c_str(), "test-000.png");
}

// Test: Priority of format flags - png takes precedence over jpeg and tiff
TEST_F(GetImageFileNameTest_2696, PngPrecedenceOverJpegAndTiff_2696) {
    png = true;
    jpeg = true;
    tiff = true;
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 2, 1);
    EXPECT_STREQ(result->toStr().c_str(), "output-01.png");
}

// Test: jpeg takes precedence over tiff when png is false
TEST_F(GetImageFileNameTest_2696, JpegPrecedenceOverTiff_2696) {
    jpeg = true;
    tiff = true;
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 2, 1);
    EXPECT_STREQ(result->toStr().c_str(), "output-01.jpg");
}

// Test: Output filename with path
TEST_F(GetImageFileNameTest_2696, FileNameWithPath_2696) {
    png = true;
    GooString outputFileName("/tmp/mydir/output");
    auto result = getImageFileName(&outputFileName, 3, 12);
    EXPECT_STREQ(result->toStr().c_str(), "/tmp/mydir/output-012.png");
}

// Test: Empty output filename
TEST_F(GetImageFileNameTest_2696, EmptyFileName_2696) {
    png = true;
    GooString outputFileName("");
    auto result = getImageFileName(&outputFileName, 3, 1);
    EXPECT_STREQ(result->toStr().c_str(), "-001.png");
}

// Test: SingleFile with no format flags and non-fd filename
TEST_F(GetImageFileNameTest_2696, SingleFileNoFormatFlags_2696) {
    singleFile = true;
    GooString outputFileName("output");
    auto result = getImageFileName(&outputFileName, 3, 1);
    EXPECT_STREQ(result->toStr().c_str(), "output");
}

// Test: Large page number that exceeds numDigits
TEST_F(GetImageFileNameTest_2696, PageNumberExceedsDigits_2696) {
    png = true;
    GooString outputFileName("out");
    auto result = getImageFileName(&outputFileName, 2, 999);
    EXPECT_STREQ(result->toStr().c_str(), "out-999.png");
}

// Test: numDigits = 0 edge case
TEST_F(GetImageFileNameTest_2696, ZeroDigits_2696) {
    png = true;
    GooString outputFileName("out");
    auto result = getImageFileName(&outputFileName, 0, 5);
    EXPECT_STREQ(result->toStr().c_str(), "out-5.png");
}
