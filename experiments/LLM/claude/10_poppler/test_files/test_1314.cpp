#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "poppler/PSOutputDev.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include "splash/SplashTypes.h"

// Helper function to capture PS output
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1314 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a PSOutputDev with output function - returns nullptr on failure
    // We use a minimal approach: create from output function with manual control
    PSOutputDev* createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        return new PSOutputDev(outputFunc, &outputBuffer, nullptr, doc, pages,
                               psModePS, -1, -1, false, true,
                               0, 0, 0, 0,
                               psRasterizeWhenNeeded, true,
                               nullptr, nullptr, psLevel2);
    }

    std::string outputBuffer;
};

// Test setRasterMono method
TEST_F(PSOutputDevTest_1314, SetRasterMono_1314) {
    // We can't easily create a full PSOutputDev without a valid PDFDoc,
    // but we can test the setRasterMono behavior by verifying
    // that it's callable and doesn't crash. Since PSOutputDev requires
    // complex initialization, we test the setter/getter methods
    // that don't require full initialization through a file-based approach.

    // Create a minimal PDF file for testing
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to a temp file
    FILE *f = tmpfile();
    if (!f) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    fwrite(pdfContent, 1, strlen(pdfContent), f);
    fflush(f);
    rewind(f);

    // Try to create PDFDoc from file descriptor
    // This may fail with invalid PDF, which is okay for setter tests
    int fd = fileno(f);

    // Use a temp filename approach instead
    fclose(f);

    char tmpName[] = "/tmp/psoutput_test_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Test setRasterMono
        psOut->setRasterMono();
        // No crash means success - the method sets internal state

        // Test various setters and getters
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());

        psOut->setEmbedTrueType(true);
        EXPECT_TRUE(psOut->getEmbedTrueType());
        psOut->setEmbedTrueType(false);
        EXPECT_FALSE(psOut->getEmbedTrueType());

        psOut->setEmbedCIDPostScript(true);
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());
        psOut->setEmbedCIDPostScript(false);
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());

        psOut->setEmbedCIDTrueType(true);
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());
        psOut->setEmbedCIDTrueType(false);
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());

        psOut->setFontPassthrough(true);
        EXPECT_TRUE(psOut->getFontPassthrough());
        psOut->setFontPassthrough(false);
        EXPECT_FALSE(psOut->getFontPassthrough());

        psOut->setOptimizeColorSpace(true);
        EXPECT_TRUE(psOut->getOptimizeColorSpace());
        psOut->setOptimizeColorSpace(false);
        EXPECT_FALSE(psOut->getOptimizeColorSpace());

        psOut->setPassLevel1CustomColor(true);
        EXPECT_TRUE(psOut->getPassLevel1CustomColor());
        psOut->setPassLevel1CustomColor(false);
        EXPECT_FALSE(psOut->getPassLevel1CustomColor());

        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());

        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());
        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
    }

    delete psOut;
    unlink(tmpName);
}

// Test boolean setters/getters toggle correctly
TEST_F(PSOutputDevTest_1314, SettersAndGettersToggle_1314) {
    char tmpName[] = "/tmp/psoutput_test2_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Test upsideDown
        EXPECT_FALSE(psOut->upsideDown());

        // Test useDrawChar
        EXPECT_FALSE(psOut->useDrawChar());

        // Test useTilingPatternFill
        EXPECT_TRUE(psOut->useTilingPatternFill());

        // Test useDrawForm
        EXPECT_TRUE(psOut->useDrawForm());

        // Test interpretType3Chars
        EXPECT_FALSE(psOut->interpretType3Chars());

        // Test needClipToCropBox
        EXPECT_TRUE(psOut->needClipToCropBox());

        // Test setDisplayText
        psOut->setDisplayText(true);
        psOut->setDisplayText(false);

        // Test setPSCenter
        psOut->setPSCenter(true);
        psOut->setPSCenter(false);

        // Test setPSExpandSmaller
        psOut->setPSExpandSmaller(true);
        psOut->setPSExpandSmaller(false);

        // Test setPSShrinkLarger
        psOut->setPSShrinkLarger(true);
        psOut->setPSShrinkLarger(false);

        // Test setOverprintPreview
        psOut->setOverprintPreview(true);
        psOut->setOverprintPreview(false);

        // Test setRasterAntialias
        psOut->setRasterAntialias(true);
        psOut->setRasterAntialias(false);

        // Test setRasterResolution
        psOut->setRasterResolution(300.0);
        psOut->setRasterResolution(72.0);

        // Test setUncompressPreloadedImages
        psOut->setUncompressPreloadedImages(true);
        psOut->setUncompressPreloadedImages(false);

        // Test setForceRasterize
        psOut->setForceRasterize(psRasterizeWhenNeeded);
        psOut->setForceRasterize(psAlwaysRasterize);
        psOut->setForceRasterize(psNeverRasterize);

        // Test setProcessColorFormat
        psOut->setProcessColorFormat(splashModeMono8);
        psOut->setProcessColorFormat(splashModeRGB8);
        psOut->setProcessColorFormat(splashModeCMYK8);

        // Test setOffset
        psOut->setOffset(0.0, 0.0);
        psOut->setOffset(100.0, 200.0);

        // Test setScale
        psOut->setScale(1.0, 1.0);
        psOut->setScale(2.0, 0.5);

        // Test setRotate
        psOut->setRotate(0);
        psOut->setRotate(90);
        psOut->setRotate(180);
        psOut->setRotate(270);

        // Test setClip
        psOut->setClip(0.0, 0.0, 612.0, 792.0);

        // Test setPreloadImagesForms
        psOut->setPreloadImagesForms(true);
        psOut->setPreloadImagesForms(false);

        // Test setGenerateOPI
        psOut->setGenerateOPI(true);
        psOut->setGenerateOPI(false);

        // Test setUseASCIIHex
        psOut->setUseASCIIHex(true);
        psOut->setUseASCIIHex(false);

        // Test setUseBinary
        psOut->setUseBinary(true);
        psOut->setUseBinary(false);
    }

    delete psOut;
    unlink(tmpName);
}

// Test setUnderlayCbk and setOverlayCbk
TEST_F(PSOutputDevTest_1314, SetCallbacks_1314) {
    char tmpName[] = "/tmp/psoutput_test3_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Test setting underlay callback
        static bool underlayCalled = false;
        auto underlayCbk = [](PSOutputDev *psOut, void *data) {
            underlayCalled = true;
        };
        int dummyData = 42;
        psOut->setUnderlayCbk(underlayCbk, &dummyData);

        // Test setting overlay callback
        static bool overlayCalled = false;
        auto overlayCbk = [](PSOutputDev *psOut, void *data) {
            overlayCalled = true;
        };
        psOut->setOverlayCbk(overlayCbk, &dummyData);

        // Test setting nullptr callbacks
        psOut->setUnderlayCbk(nullptr, nullptr);
        psOut->setOverlayCbk(nullptr, nullptr);
    }

    delete psOut;
    unlink(tmpName);
}

// Test useShadedFills with different types
TEST_F(PSOutputDevTest_1314, UseShadedFills_1314) {
    char tmpName[] = "/tmp/psoutput_test4_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Test useShadedFills with various type values
        // Types 1-7 correspond to PDF shading types
        for (int type = 1; type <= 7; type++) {
            // Just verify it returns a boolean without crashing
            bool result = psOut->useShadedFills(type);
            (void)result; // suppress unused warning
        }

        // Test boundary types
        psOut->useShadedFills(0);
        psOut->useShadedFills(8);
    }

    delete psOut;
    unlink(tmpName);
}

// Test that isOk returns correct state
TEST_F(PSOutputDevTest_1314, IsOk_1314) {
    char tmpName[] = "/tmp/psoutput_test5_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    // A properly initialized PSOutputDev should be ok
    EXPECT_TRUE(psOut->isOk());

    delete psOut;
    unlink(tmpName);
}

// Test EmbedType1 getter/setter roundtrip
TEST_F(PSOutputDevTest_1314, EmbedType1RoundTrip_1314) {
    char tmpName[] = "/tmp/psoutput_test6_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Test multiple set/get cycles
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());

        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());

        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
    }

    delete psOut;
    unlink(tmpName);
}

// Test EmbedTrueType getter/setter roundtrip
TEST_F(PSOutputDevTest_1314, EmbedTrueTypeRoundTrip_1314) {
    char tmpName[] = "/tmp/psoutput_test7_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEmbedTrueType(true);
        EXPECT_TRUE(psOut->getEmbedTrueType());

        psOut->setEmbedTrueType(false);
        EXPECT_FALSE(psOut->getEmbedTrueType());
    }

    delete psOut;
    unlink(tmpName);
}

// Test EnableLZW and EnableFlate getter/setter
TEST_F(PSOutputDevTest_1314, EnableLZWFlateRoundTrip_1314) {
    char tmpName[] = "/tmp/psoutput_test8_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());

        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());
        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
    }

    delete psOut;
    unlink(tmpName);
}

// Test CID font embedding getters/setters
TEST_F(PSOutputDevTest_1314, CIDFontEmbeddingRoundTrip_1314) {
    char tmpName[] = "/tmp/psoutput_test9_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEmbedCIDPostScript(true);
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());
        psOut->setEmbedCIDPostScript(false);
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());

        psOut->setEmbedCIDTrueType(true);
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());
        psOut->setEmbedCIDTrueType(false);
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());
    }

    delete psOut;
    unlink(tmpName);
}

// Test FontPassthrough and OptimizeColorSpace
TEST_F(PSOutputDevTest_1314, FontPassthroughOptimizeColorSpace_1314) {
    char tmpName[] = "/tmp/psoutput_test10_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setFontPassthrough(true);
        EXPECT_TRUE(psOut->getFontPassthrough());
        psOut->setFontPassthrough(false);
        EXPECT_FALSE(psOut->getFontPassthrough());

        psOut->setOptimizeColorSpace(true);
        EXPECT_TRUE(psOut->getOptimizeColorSpace());
        psOut->setOptimizeColorSpace(false);
        EXPECT_FALSE(psOut->getOptimizeColorSpace());
    }

    delete psOut;
    unlink(tmpName);
}

// Test setProcessColorFormat with various modes
TEST_F(PSOutputDevTest_1314, SetProcessColorFormat_1314) {
    char tmpName[] = "/tmp/psoutput_test11_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Test all SplashColorMode values
        psOut->setProcessColorFormat(splashModeMono1);
        psOut->setProcessColorFormat(splashModeMono8);
        psOut->setProcessColorFormat(splashModeRGB8);
        psOut->setProcessColorFormat(splashModeBGR8);
        psOut->setProcessColorFormat(splashModeXBGR8);
        psOut->setProcessColorFormat(splashModeCMYK8);
        psOut->setProcessColorFormat(splashModeDeviceN8);
        
        // No crashes = pass
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setScale with boundary values
TEST_F(PSOutputDevTest_1314, SetScaleBoundary_1314) {
    char tmpName[] = "/tmp/psoutput_test12_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Test with zero scale
        psOut->setScale(0.0, 0.0);

        // Test with negative scale
        psOut->setScale(-1.0, -1.0);

        // Test with very large scale
        psOut->setScale(1e10, 1e10);

        // Test with very small positive scale
        psOut->setScale(1e-10, 1e-10);

        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setOffset with boundary values
TEST_F(PSOutputDevTest_1314, SetOffsetBoundary_1314) {
    char tmpName[] = "/tmp/psoutput_test13_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setOffset(0.0, 0.0);
        psOut->setOffset(-1000.0, -1000.0);
        psOut->setOffset(1e10, 1e10);

        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setClip with various rectangle values
TEST_F(PSOutputDevTest_1314, SetClipBoundary_1314) {
    char tmpName[] = "/tmp/psoutput_test14_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Normal clip
        psOut->setClip(0.0, 0.0, 612.0, 792.0);

        // Zero-sized clip
        psOut->setClip(0.0, 0.0, 0.0, 0.0);

        // Inverted clip
        psOut->setClip(612.0, 792.0, 0.0, 0.0);

        // Negative coordinates
        psOut->setClip(-100.0, -100.0, 100.0, 100.0);

        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setRasterResolution with boundary values
TEST_F(PSOutputDevTest_1314, SetRasterResolutionBoundary_1314) {
    char tmpName[] = "/tmp/psoutput_test15_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }

    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(tmpFd, pdfContent, strlen(pdfContent));
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;

    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output, nullptr, doc.get(), pages,
                                          psModePS, -1, -1, false, true,
                                          0, 0, 0, 0,
                                          psRasterizeWhenNeeded, true,
                                          nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setRasterResolution(72.0);
        psOut->setRasterResolution(150.0);
        psOut->setRasterResolution(300.0);
        psOut->setRasterResolution(600.0);
        psOut->setRasterResolution(1200.0);
        psOut->setRasterResolution(0.0);  // boundary

        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}
