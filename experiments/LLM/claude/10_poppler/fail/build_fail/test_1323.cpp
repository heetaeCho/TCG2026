#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <memory>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper output function that writes to a string buffer
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1323 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using a FoFiOutputFunc
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        outputBuffer.clear();
        char title[] = "Test";
        auto dev = std::make_unique<PSOutputDev>(
            outputToString, &outputBuffer,
            title, doc, pages,
            psModePS,    // PSOutMode
            -1, -1,      // paperWidth, paperHeight
            false,        // noCrop
            true,         // duplex
            0, 0, 0, 0,  // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // PSForceRasterize
            true,         // manualCtrl
            nullptr,      // customCodeCbk
            nullptr,      // customCodeCbkData
            psLevel2      // PSLevel
        );
        return dev;
    }

    std::string outputBuffer;
};

// Test that we can create a PSOutputDev with a simple PDF and it reports isOk
TEST_F(PSOutputDevTest_1323, CreateWithOutputFunc_1323) {
    // Create a minimal PDF in memory for testing
    // We'll use a file-based approach with a known test PDF if available
    // For now, test with nullptr doc - expect it to fail gracefully
    // This tests that the constructor doesn't crash
    std::string buf;
    char title[] = "Test";
    std::vector<int> pages;

    // Without a valid doc, we can't fully construct, but we test the interface
    // through setter/getter pairs on a successfully constructed object.
    // We'll create a minimal PDF file for testing.
    
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (doc->isOk()) {
        pages.push_back(1);
        auto dev = createPSOutputDev(doc.get(), pages);
        // If the device was created, test isOk
        if (dev) {
            // The device may or may not be ok depending on the PDF
            // We just ensure no crash
            dev->isOk();
        }
    }
}

// Test getEnableLZW / setEnableLZW
TEST_F(PSOutputDevTest_1323, EnableLZWGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // Test setting to true
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    // Test setting to false
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());

    // Test toggling back
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
}

// Test getEnableFlate / setEnableFlate
TEST_F(PSOutputDevTest_1323, EnableFlateGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test getEmbedType1 / setEmbedType1
TEST_F(PSOutputDevTest_1323, EmbedType1GetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test getEmbedTrueType / setEmbedTrueType
TEST_F(PSOutputDevTest_1323, EmbedTrueTypeGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test getEmbedCIDPostScript / setEmbedCIDPostScript
TEST_F(PSOutputDevTest_1323, EmbedCIDPostScriptGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test getEmbedCIDTrueType / setEmbedCIDTrueType
TEST_F(PSOutputDevTest_1323, EmbedCIDTrueTypeGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test getFontPassthrough / setFontPassthrough
TEST_F(PSOutputDevTest_1323, FontPassthroughGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test getOptimizeColorSpace / setOptimizeColorSpace
TEST_F(PSOutputDevTest_1323, OptimizeColorSpaceGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test getPassLevel1CustomColor / setPassLevel1CustomColor
TEST_F(PSOutputDevTest_1323, PassLevel1CustomColorGetterSetter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test upsideDown
TEST_F(PSOutputDevTest_1323, UpsideDown_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // upsideDown should return a consistent boolean value
    bool result = dev->upsideDown();
    // PS coordinate system typically has origin at bottom-left, so upsideDown should be false
    EXPECT_FALSE(result);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1323, UseDrawChar_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // PSOutputDev typically returns false for useDrawChar (uses drawString instead)
    bool result = dev->useDrawChar();
    EXPECT_FALSE(result);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1323, UseTilingPatternFill_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1323, UseDrawForm_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    bool result = dev->useDrawForm();
    EXPECT_TRUE(result);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1323, SetDisplayText_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash - no getter to verify, but test that it doesn't throw
    dev->setDisplayText(true);
    dev->setDisplayText(false);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1323, SetPSCenter_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setPSCenter(true);
    dev->setPSCenter(false);
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevTest_1323, SetPSExpandSmaller_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevTest_1323, SetPSShrinkLarger_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1323, SetOverprintPreview_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
}

// Test setOffset
TEST_F(PSOutputDevTest_1323, SetOffset_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setOffset(10.0, 20.0);
    dev->setOffset(0.0, 0.0);
    dev->setOffset(-5.0, -10.0);
}

// Test setScale
TEST_F(PSOutputDevTest_1323, SetScale_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 2.0);
    dev->setScale(0.5, 0.5);
}

// Test setRotate
TEST_F(PSOutputDevTest_1323, SetRotate_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
}

// Test setClip
TEST_F(PSOutputDevTest_1323, SetClip_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setClip(0.0, 0.0, 612.0, 792.0);
    dev->setClip(100.0, 100.0, 500.0, 700.0);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1323, SetRasterResolution_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(600.0);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1323, SetRasterAntialias_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1323, SetUncompressPreloadedImages_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1323, SetGenerateOPI_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1323, SetUseASCIIHex_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1323, SetUseBinary_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setUseBinary(true);
    dev->setUseBinary(false);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1323, SetPreloadImagesForms_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
}

// Test multiple setter/getter toggling in sequence
TEST_F(PSOutputDevTest_1323, MultipleSetterGetterSequence_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // Set all to true
    dev->setEnableLZW(true);
    dev->setEnableFlate(true);
    dev->setEmbedType1(true);
    dev->setEmbedTrueType(true);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(true);
    dev->setFontPassthrough(true);
    dev->setOptimizeColorSpace(true);
    dev->setPassLevel1CustomColor(true);

    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());
    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_TRUE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    // Set all to false
    dev->setEnableLZW(false);
    dev->setEnableFlate(false);
    dev->setEmbedType1(false);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(false);
    dev->setOptimizeColorSpace(false);
    dev->setPassLevel1CustomColor(false);

    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());
    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_FALSE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test underlay callback setter
TEST_F(PSOutputDevTest_1323, SetUnderlayCbk_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // Set underlay callback to nullptr - should not crash
    dev->setUnderlayCbk(nullptr, nullptr);

    // Set to a lambda-like function
    int callbackData = 42;
    dev->setUnderlayCbk([](PSOutputDev *, void *) {}, &callbackData);
}

// Test overlay callback setter
TEST_F(PSOutputDevTest_1323, SetOverlayCbk_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    dev->setOverlayCbk(nullptr, nullptr);

    int callbackData = 42;
    dev->setOverlayCbk([](PSOutputDev *, void *) {}, &callbackData);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1323, InterpretType3Chars_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // PSOutputDev should interpret Type 3 chars
    bool result = dev->interpretType3Chars();
    EXPECT_FALSE(result);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1323, NeedClipToCropBox_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // Just verify it returns a boolean value without crashing
    bool result = dev->needClipToCropBox();
    // The result is implementation-dependent but should be consistent
    (void)result;
}

// Test useShadedFills with various types
TEST_F(PSOutputDevTest_1323, UseShadedFills_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // Test with different shading types (1-7 are common PDF shading types)
    for (int type = 1; type <= 7; type++) {
        bool result = dev->useShadedFills(type);
        // Just verify no crash; result depends on PS level and type
        (void)result;
    }
}

// Test creating PSOutputDev with file name constructor
TEST_F(PSOutputDevTest_1323, CreateWithFileName_1323) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    char title[] = "TestTitle";

    // Create with output to /dev/null or a temp file
    const char *outputFile = "/dev/null";
    auto dev = std::make_unique<PSOutputDev>(
        outputFile, doc.get(), title, pages,
        psModePS, -1, -1, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );

    if (dev && dev->isOk()) {
        // Verify basic getters work
        dev->setEnableLZW(true);
        EXPECT_TRUE(dev->getEnableLZW());
    }
}
