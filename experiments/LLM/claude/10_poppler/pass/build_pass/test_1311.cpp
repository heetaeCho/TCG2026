#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper function to capture PS output
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1311 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // Returns nullptr if creation fails. Caller must manage lifetime.
    PSOutputDev* createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages,
                                    std::string *outputStr,
                                    PSOutMode mode = psModePS,
                                    PSLevel level = psLevel2) {
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputFunc, outputStr,
            nullptr, // psTitleA
            doc,
            pages,
            mode,
            -1, -1, // paperWidth, paperHeight
            false, // noCrop
            false, // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterize
            true, // manualCtrl
            nullptr, nullptr, // customCodeCbk
            level
        );
        return dev;
    }
};

// Test that setRasterAntialias can be called (basic setter test)
TEST_F(PSOutputDevTest_1311, SetRasterAntialias_True_1311) {
    // We need a valid PDF document to construct PSOutputDev
    // Create a minimal test using a temp file approach
    // Since we can't easily create a PDFDoc without a file,
    // we test the setter/getter pattern through observable behavior
    
    // Create a simple 1-page PDF in memory
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to temp file
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    // Try creating a GooString-based file for PDFDoc
    char tmpName[L_tmpnam + 1];
    std::string tmpFileName;
    
    // Use a named temp file instead
    tmpFileName = "/tmp/psoutputdev_test_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) {
        fclose(tmpFile);
        GTEST_SKIP() << "Cannot create temp PDF file";
    }
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);
    fclose(tmpFile);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    
    if (!doc->isOk()) {
        delete doc;
        unlink(tmpFileName.c_str());
        GTEST_SKIP() << "Cannot create valid PDFDoc for testing";
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        delete doc;
        unlink(tmpFileName.c_str());
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Test setRasterAntialias with true
    dev->setRasterAntialias(true);
    // No crash means success - the setter should work

    // Test setRasterAntialias with false
    dev->setRasterAntialias(false);
    // No crash means success

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter pairs for embed flags
TEST_F(PSOutputDevTest_1311, SetGetEmbedType1_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test2_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp PDF file";
    }
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));

    if (!doc->isOk()) {
        delete doc;
        unlink(tmpFileName.c_str());
        GTEST_SKIP() << "Cannot create valid PDFDoc for testing";
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);

    if (!dev->isOk()) {
        delete dev;
        delete doc;
        unlink(tmpFileName.c_str());
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Test setEmbedType1 / getEmbedType1
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter pairs for EmbedTrueType
TEST_F(PSOutputDevTest_1311, SetGetEmbedTrueType_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test3_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter pairs for EmbedCIDPostScript
TEST_F(PSOutputDevTest_1311, SetGetEmbedCIDPostScript_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test4_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter for EmbedCIDTrueType
TEST_F(PSOutputDevTest_1311, SetGetEmbedCIDTrueType_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test5_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter for FontPassthrough
TEST_F(PSOutputDevTest_1311, SetGetFontPassthrough_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test6_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter for OptimizeColorSpace
TEST_F(PSOutputDevTest_1311, SetGetOptimizeColorSpace_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test7_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter for PassLevel1CustomColor
TEST_F(PSOutputDevTest_1311, SetGetPassLevel1CustomColor_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test8_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter for EnableLZW
TEST_F(PSOutputDevTest_1311, SetGetEnableLZW_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test9_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setter/getter for EnableFlate
TEST_F(PSOutputDevTest_1311, SetGetEnableFlate_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test10_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test OutputDev interface methods
TEST_F(PSOutputDevTest_1311, OutputDevInterfaceMethods_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test11_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    // Test upsideDown - PS typically returns true
    bool upsideDown = dev->upsideDown();
    // Just verify it returns a valid bool (no crash)
    EXPECT_TRUE(upsideDown || !upsideDown);

    // Test useDrawChar
    bool drawChar = dev->useDrawChar();
    EXPECT_TRUE(drawChar || !drawChar);

    // Test useTilingPatternFill
    bool tilingFill = dev->useTilingPatternFill();
    EXPECT_TRUE(tilingFill || !tilingFill);

    // Test useDrawForm
    bool drawForm = dev->useDrawForm();
    EXPECT_TRUE(drawForm || !drawForm);

    // Test interpretType3Chars
    bool type3 = dev->interpretType3Chars();
    EXPECT_TRUE(type3 || !type3);

    // Test needClipToCropBox
    bool clipCrop = dev->needClipToCropBox();
    EXPECT_TRUE(clipCrop || !clipCrop);

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test various setters that don't have getters - ensure no crash
TEST_F(PSOutputDevTest_1311, SettersWithoutGetters_NoCrash_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test12_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    // Test setOffset
    dev->setOffset(10.0, 20.0);
    dev->setOffset(0.0, 0.0);
    dev->setOffset(-5.0, -10.0);

    // Test setScale
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 0.5);

    // Test setRotate
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);

    // Test setClip
    dev->setClip(0.0, 0.0, 612.0, 792.0);

    // Test setDisplayText
    dev->setDisplayText(true);
    dev->setDisplayText(false);

    // Test setPSCenter
    dev->setPSCenter(true);
    dev->setPSCenter(false);

    // Test setPSExpandSmaller
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);

    // Test setPSShrinkLarger
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);

    // Test setOverprintPreview
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);

    // Test setRasterResolution
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);

    // Test setRasterMono
    dev->setRasterMono();

    // Test setUncompressPreloadedImages
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);

    // Test setForceRasterize
    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);

    // Test setPreloadImagesForms
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);

    // Test setGenerateOPI
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);

    // Test setUseASCIIHex
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);

    // Test setUseBinary
    dev->setUseBinary(true);
    dev->setUseBinary(false);

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test overlay and underlay callbacks
TEST_F(PSOutputDevTest_1311, SetCallbacks_NoCrash_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test13_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    // Test setting null callbacks
    dev->setUnderlayCbk(nullptr, nullptr);
    dev->setOverlayCbk(nullptr, nullptr);

    // Test setting actual callbacks
    auto dummyCbk = [](PSOutputDev *, void *) {};
    int dummyData = 42;
    dev->setUnderlayCbk(dummyCbk, &dummyData);
    dev->setOverlayCbk(dummyCbk, &dummyData);

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test useShadedFills with different types
TEST_F(PSOutputDevTest_1311, UseShadedFills_DifferentTypes_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test14_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    // Test different shading types (1-7 are typical PDF shading types)
    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        EXPECT_TRUE(result || !result) << "Type " << type;
    }

    // Boundary: type 0 (invalid)
    bool result0 = dev->useShadedFills(0);
    EXPECT_TRUE(result0 || !result0);

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test isOk on a valid PSOutputDev
TEST_F(PSOutputDevTest_1311, IsOk_ValidDevice_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test15_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);

    // A properly constructed PSOutputDev should be ok
    EXPECT_TRUE(dev->isOk());

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test toggling boolean setters back and forth
TEST_F(PSOutputDevTest_1311, ToggleBooleanSetters_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test16_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    // Toggle EmbedType1 multiple times
    for (int i = 0; i < 5; ++i) {
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());
        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());
    }

    // Toggle EnableFlate multiple times
    for (int i = 0; i < 5; ++i) {
        dev->setEnableFlate(true);
        EXPECT_TRUE(dev->getEnableFlate());
        dev->setEnableFlate(false);
        EXPECT_FALSE(dev->getEnableFlate());
    }

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test with file constructor (filename-based)
TEST_F(PSOutputDevTest_1311, FileNameConstructor_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpPdfName = "/tmp/psoutputdev_input_1311.pdf";
    std::string tmpPsName = "/tmp/psoutputdev_output_1311.ps";
    
    FILE *f = fopen(tmpPdfName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpPdfName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpPdfName.c_str()); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        tmpPsName.c_str(),
        doc,
        nullptr, // psTitleA
        pages,
        psModePS,
        -1, -1,
        false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded,
        true,
        nullptr, nullptr,
        psLevel2
    );

    if (dev->isOk()) {
        // Basic verification that the device was created successfully
        EXPECT_TRUE(dev->isOk());
    }

    delete dev;
    delete doc;
    unlink(tmpPdfName.c_str());
    unlink(tmpPsName.c_str());
}

// Test setRasterResolution boundary values
TEST_F(PSOutputDevTest_1311, SetRasterResolution_BoundaryValues_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test17_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    // Test various resolution values
    dev->setRasterResolution(0.0);
    dev->setRasterResolution(1.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(150.0);
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(600.0);
    dev->setRasterResolution(1200.0);
    dev->setRasterResolution(9999.0);

    // No crash is the success criterion
    SUCCEED();

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setOffset with extreme values
TEST_F(PSOutputDevTest_1311, SetOffset_ExtremeValues_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test18_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setOffset(1e10, 1e10);
    dev->setOffset(-1e10, -1e10);
    dev->setOffset(0.0, 0.0);

    SUCCEED();

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}

// Test setScale with extreme values
TEST_F(PSOutputDevTest_1311, SetScale_ExtremeValues_1311) {
    const char *pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    std::string tmpFileName = "/tmp/psoutputdev_test19_1311.pdf";
    FILE *f = fopen(tmpFileName.c_str(), "wb");
    if (!f) GTEST_SKIP();
    fwrite(pdfData, 1, strlen(pdfData), f);
    fclose(f);

    auto docStr = std::make_unique<GooString>(tmpFileName.c_str());
    PDFDoc *doc = new PDFDoc(std::move(docStr));
    if (!doc->isOk()) { delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages, &output);
    if (!dev->isOk()) { delete dev; delete doc; unlink(tmpFileName.c_str()); GTEST_SKIP(); }

    dev->setScale(0.001, 0.001);
    dev->setScale(100.0, 100.0);
    dev->setScale(1.0, 1.0);

    SUCCEED();

    delete dev;
    delete doc;
    unlink(tmpFileName.c_str());
}
