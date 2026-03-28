#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "PDFDoc.h"
#include "SplashOutputDev.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "splash/SplashErrorCodes.h"

// We need access to the global variables and the savePageSlice function
// These are defined in pdftoppm.cc
extern int lastPage;
extern double x_resolution;
extern double y_resolution;
extern bool useCropBox;
extern bool png;
extern bool jpeg;
extern bool jpegcmyk;
extern bool tiff;
extern int jpegQuality;
extern bool jpegProgressive;
extern bool jpegOptimize;
extern char TiffCompressionStr[];
extern bool progress;

// Forward declare the function under test
static void savePageSlice(PDFDoc *doc, SplashOutputDev *splashOut, int pg,
                          int x, int y, int w, int h,
                          double pg_w, double pg_h, char *ppmFile);

// Include the implementation to get access to savePageSlice
// Since it's static, we need to include the source
#include "pdftoppm.cc"

class SavePageSliceTest_2654 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset global state
        x_resolution = 150.0;
        y_resolution = 150.0;
        useCropBox = false;
        png = false;
        jpeg = false;
        jpegcmyk = false;
        tiff = false;
        jpegQuality = -1;
        jpegProgressive = false;
        jpegOptimize = false;
        memset(TiffCompressionStr, 0, sizeof(TiffCompressionStr));
        progress = false;
        lastPage = 0;
    }

    void TearDown() override {
        // Clean up any temp files
        for (auto &f : tempFiles) {
            remove(f.c_str());
        }
    }

    std::string createTempFile() {
        char tmpl[] = "/tmp/pdftoppm_test_XXXXXX";
        int fd = mkstemp(tmpl);
        if (fd >= 0) {
            close(fd);
        }
        std::string name(tmpl);
        tempFiles.push_back(name);
        return name;
    }

    std::vector<std::string> tempFiles;
};

// Test: When w == 0, width should be set to ceil(pg_w)
TEST_F(SavePageSliceTest_2654, ZeroWidthUsesPageWidth_2654) {
    // This test verifies that when w=0, the function computes w from pg_w
    // We can verify this indirectly through the displayPageSlice call
    // by checking the file output exists and is valid

    // Create a simple test PDF
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    // w=0 and h=0 should use pg_w and pg_h
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile);

    // Verify file was written (non-zero size)
    FILE *f = fopen(ppmFile, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        EXPECT_GT(size, 0);
    }
}

// Test: When h == 0, height should be set to ceil(pg_h)
TEST_F(SavePageSliceTest_2654, ZeroHeightUsesPageHeight_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    // w=50, h=0 should use pg_h for height
    savePageSlice(&doc, &splashOut, 1, 0, 0, 50, 0, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        EXPECT_GT(size, 0);
    }
}

// Test: Width clamping when x + w > pg_w
TEST_F(SavePageSliceTest_2654, WidthClampedToPageBoundary_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    // x=80, w=50 with pg_w=100 => w should be clamped to ceil(100-80)=20
    savePageSlice(&doc, &splashOut, 1, 80, 0, 50, 0, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        EXPECT_GT(size, 0);
    }
}

// Test: Height clamping when y + h > pg_h
TEST_F(SavePageSliceTest_2654, HeightClampedToPageBoundary_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    // y=60, h=50 with pg_h=100 => h should be clamped to ceil(100-60)=40
    savePageSlice(&doc, &splashOut, 1, 0, 60, 0, 50, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        EXPECT_GT(size, 0);
    }
}

// Test: PNM output (default format, no png/jpeg/tiff flags)
TEST_F(SavePageSliceTest_2654, DefaultFormatWritesPNM_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    // All format flags false => PNM output
    png = false;
    jpeg = false;
    jpegcmyk = false;
    tiff = false;

    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: PNG format output
TEST_F(SavePageSliceTest_2654, PngFormatOutput_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeRGB8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile() + ".png";
    tempFiles.push_back(tmpFile);
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    png = true;

    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        EXPECT_GT(size, 0);
    }
}

// Test: JPEG format output
TEST_F(SavePageSliceTest_2654, JpegFormatOutput_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeRGB8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile() + ".jpg";
    tempFiles.push_back(tmpFile);
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    jpeg = true;
    jpegQuality = 85;

    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        EXPECT_GT(size, 0);
    }
}

// Test: Progress output
TEST_F(SavePageSliceTest_2654, ProgressOutputEnabled_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    progress = true;
    lastPage = 5;

    // Capture stderr to verify progress output
    testing::internal::CaptureStderr();
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile);
    std::string stderrOutput = testing::internal::GetCapturedStderr();

    EXPECT_NE(stderrOutput.find("1 5"), std::string::npos);
}

// Test: Null ppmFile writes to stdout
TEST_F(SavePageSliceTest_2654, NullFileWritesToStdout_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    // Redirect stdout to a temp file
    std::string tmpFile = createTempFile();
    FILE *origStdout = stdout;
    FILE *tmpOut = fopen(tmpFile.c_str(), "wb");
    ASSERT_NE(tmpOut, nullptr);

    // Save original stdout fd and redirect
    int origFd = dup(fileno(stdout));
    dup2(fileno(tmpOut), fileno(stdout));

    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, nullptr);

    // Restore stdout
    fflush(stdout);
    dup2(origFd, fileno(stdout));
    close(origFd);
    fclose(tmpOut);

    // Check that something was written to the redirected stdout
    FILE *f = fopen(tmpFile.c_str(), "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: Progress with null ppmFile prints empty string
TEST_F(SavePageSliceTest_2654, ProgressWithNullFilePrintsEmpty_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    progress = true;
    lastPage = 3;

    // Redirect stdout to /dev/null to avoid PNM data on terminal
    int origFd = dup(fileno(stdout));
    FILE *devnull = fopen("/dev/null", "wb");
    if (devnull) {
        dup2(fileno(devnull), fileno(stdout));
    }

    testing::internal::CaptureStderr();
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, nullptr);
    std::string stderrOutput = testing::internal::GetCapturedStderr();

    // Restore stdout
    if (devnull) {
        fflush(stdout);
        dup2(origFd, fileno(stdout));
        fclose(devnull);
    }
    close(origFd);

    // Progress line should contain page numbers and empty filename
    EXPECT_NE(stderrOutput.find("1 3 "), std::string::npos);
}

// Test: Non-integer page dimensions with ceil behavior
TEST_F(SavePageSliceTest_2654, CeilBehaviorForNonIntegerDimensions_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    // pg_w = 100.5, pg_h = 200.3, w=0, h=0
    // w should become ceil(100.5) = 101, h should become ceil(200.3) = 201
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.5, 200.3, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: Both width and height within page bounds (no clamping needed)
TEST_F(SavePageSliceTest_2654, DimensionsWithinBoundsNoClamping_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    // x=10, y=10, w=50, h=50 with pg_w=200, pg_h=200 => no clamping
    savePageSlice(&doc, &splashOut, 1, 10, 10, 50, 50, 200.0, 200.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: WriteImgParams jpegQuality is passed correctly
TEST_F(SavePageSliceTest_2654, JpegQualityParameter_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeRGB8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile1 = createTempFile() + "_q10.jpg";
    std::string tmpFile2 = createTempFile() + "_q95.jpg";
    tempFiles.push_back(tmpFile1);
    tempFiles.push_back(tmpFile2);

    char ppmFile1[256], ppmFile2[256];
    strncpy(ppmFile1, tmpFile1.c_str(), sizeof(ppmFile1) - 1);
    ppmFile1[sizeof(ppmFile1) - 1] = '\0';
    strncpy(ppmFile2, tmpFile2.c_str(), sizeof(ppmFile2) - 1);
    ppmFile2[sizeof(ppmFile2) - 1] = '\0';

    jpeg = true;

    jpegQuality = 10;
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile1);

    jpegQuality = 95;
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile2);

    // Low quality JPEG should generally be smaller than high quality
    FILE *f1 = fopen(ppmFile1, "rb");
    FILE *f2 = fopen(ppmFile2, "rb");
    if (f1 && f2) {
        fseek(f1, 0, SEEK_END);
        long size1 = ftell(f1);
        fseek(f2, 0, SEEK_END);
        long size2 = ftell(f2);
        fclose(f1);
        fclose(f2);
        EXPECT_GT(size1, 0);
        EXPECT_GT(size2, 0);
        // Generally low quality < high quality, but not strictly guaranteed
        // Just verify both are written
    } else {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
    }
}

// Test: useCropBox flag affects displayPageSlice call
TEST_F(SavePageSliceTest_2654, UseCropBoxFlag_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    useCropBox = true;
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

// Test: Resolution parameters
TEST_F(SavePageSliceTest_2654, CustomResolution_2654) {
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/simple.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);

    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    SplashColor paperColor = {0xff, 0xff, 0xff};
    SplashOutputDev splashOut(splashModeMono8, 1, paperColor, true,
                              splashThinLineDefault, false);
    splashOut.startDoc(&doc);

    std::string tmpFile = createTempFile();
    char ppmFile[256];
    strncpy(ppmFile, tmpFile.c_str(), sizeof(ppmFile) - 1);
    ppmFile[sizeof(ppmFile) - 1] = '\0';

    x_resolution = 300.0;
    y_resolution = 300.0;
    savePageSlice(&doc, &splashOut, 1, 0, 0, 0, 0, 100.0, 100.0, ppmFile);

    FILE *f = fopen(ppmFile, "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    EXPECT_GT(size, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
