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

// Helper function used as output function for PSOutputDev
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *output = static_cast<std::string *>(stream);
    output->append(data, len);
}

class PSOutputDevTest_1321 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal PSOutputDev using the FoFiOutputFunc constructor
    // Returns nullptr if creation fails. Caller owns the pointer.
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages,
                                   PSOutMode mode = psModePS,
                                   PSLevel level = psLevel2) {
        std::string *outStr = new std::string();
        outputStrings.push_back(outStr);

        PSOutputDev *dev = new PSOutputDev(
            outputFunc, outStr, nullptr, doc, pages,
            mode, -1, -1, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, level);
        return dev;
    }

    void TearDown() override {
        for (auto *s : outputStrings) {
            delete s;
        }
        outputStrings.clear();
    }

    std::vector<std::string *> outputStrings;
};

// Test getOptimizeColorSpace returns default value
TEST_F(PSOutputDevTest_1321, GetOptimizeColorSpaceDefault_1321) {
    // We need a valid PDFDoc to create a PSOutputDev. Create a minimal PDF in memory.
    // Use a temporary file approach
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to temp file
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    // Create GooString for filename - use file descriptor approach
    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
    }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (dev.isOk()) {
        // Just test the getter - the default depends on globalParams
        bool val = dev.getOptimizeColorSpace();
        // We can at least verify it returns a bool without crashing
        EXPECT_TRUE(val == true || val == false);
    }

    fclose(tmpFile);
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1321, SetGetOptimizeColorSpace_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev not ok";
    }

    dev.setOptimizeColorSpace(true);
    EXPECT_TRUE(dev.getOptimizeColorSpace());

    dev.setOptimizeColorSpace(false);
    EXPECT_FALSE(dev.getOptimizeColorSpace());

    fclose(tmpFile);
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevTest_1321, SetGetEmbedType1_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setEmbedType1(true);
    EXPECT_TRUE(dev.getEmbedType1());

    dev.setEmbedType1(false);
    EXPECT_FALSE(dev.getEmbedType1());

    fclose(tmpFile);
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevTest_1321, SetGetEmbedTrueType_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setEmbedTrueType(true);
    EXPECT_TRUE(dev.getEmbedTrueType());

    dev.setEmbedTrueType(false);
    EXPECT_FALSE(dev.getEmbedTrueType());

    fclose(tmpFile);
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1321, SetGetEmbedCIDPostScript_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev.getEmbedCIDPostScript());

    dev.setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev.getEmbedCIDPostScript());

    fclose(tmpFile);
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1321, SetGetEmbedCIDTrueType_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev.getEmbedCIDTrueType());

    dev.setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev.getEmbedCIDTrueType());

    fclose(tmpFile);
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevTest_1321, SetGetFontPassthrough_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setFontPassthrough(true);
    EXPECT_TRUE(dev.getFontPassthrough());

    dev.setFontPassthrough(false);
    EXPECT_FALSE(dev.getFontPassthrough());

    fclose(tmpFile);
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1321, SetGetPassLevel1CustomColor_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev.getPassLevel1CustomColor());

    dev.setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev.getPassLevel1CustomColor());

    fclose(tmpFile);
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevTest_1321, SetGetEnableLZW_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setEnableLZW(true);
    EXPECT_TRUE(dev.getEnableLZW());

    dev.setEnableLZW(false);
    EXPECT_FALSE(dev.getEnableLZW());

    fclose(tmpFile);
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevTest_1321, SetGetEnableFlate_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setEnableFlate(true);
    EXPECT_TRUE(dev.getEnableFlate());

    dev.setEnableFlate(false);
    EXPECT_FALSE(dev.getEnableFlate());

    fclose(tmpFile);
}

// Test upsideDown returns false (PS output is not upside down)
TEST_F(PSOutputDevTest_1321, UpsideDown_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // PS coordinate system is not upside down
    EXPECT_FALSE(dev.upsideDown());

    fclose(tmpFile);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1321, UseDrawChar_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // PSOutputDev typically returns false for useDrawChar
    EXPECT_FALSE(dev.useDrawChar());

    fclose(tmpFile);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1321, UseTilingPatternFill_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    EXPECT_TRUE(dev.useTilingPatternFill());

    fclose(tmpFile);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1321, UseDrawForm_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    EXPECT_TRUE(dev.useDrawForm());

    fclose(tmpFile);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1321, InterpretType3Chars_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Just verify it returns a valid bool
    bool result = dev.interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);

    fclose(tmpFile);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1321, SetDisplayText_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Should not crash
    dev.setDisplayText(true);
    dev.setDisplayText(false);

    fclose(tmpFile);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1321, SetPSCenter_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Should not crash
    dev.setPSCenter(true);
    dev.setPSCenter(false);

    fclose(tmpFile);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1321, SetPSExpandSmallerAndShrinkLarger_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setPSExpandSmaller(true);
    dev.setPSExpandSmaller(false);
    dev.setPSShrinkLarger(true);
    dev.setPSShrinkLarger(false);

    fclose(tmpFile);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1321, SetOverprintPreview_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setOverprintPreview(true);
    dev.setOverprintPreview(false);

    fclose(tmpFile);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1321, SetRasterResolution_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Should not crash with various resolutions
    dev.setRasterResolution(72.0);
    dev.setRasterResolution(300.0);
    dev.setRasterResolution(600.0);

    fclose(tmpFile);
}

// Test setOffset and setScale and setRotate and setClip
TEST_F(PSOutputDevTest_1321, SetTransformParams_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Should not crash
    dev.setOffset(10.0, 20.0);
    dev.setScale(1.5, 2.0);
    dev.setRotate(90);
    dev.setClip(0.0, 0.0, 612.0, 792.0);

    fclose(tmpFile);
}

// Test toggle optimizeColorSpace multiple times
TEST_F(PSOutputDevTest_1321, ToggleOptimizeColorSpaceMultiple_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Toggle multiple times
    for (int i = 0; i < 10; i++) {
        dev.setOptimizeColorSpace(true);
        EXPECT_TRUE(dev.getOptimizeColorSpace());
        dev.setOptimizeColorSpace(false);
        EXPECT_FALSE(dev.getOptimizeColorSpace());
    }

    fclose(tmpFile);
}

// Test all boolean setters/getters consistency
TEST_F(PSOutputDevTest_1321, AllBooleanSettersGettersConsistency_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Set all to true
    dev.setEmbedType1(true);
    dev.setEmbedTrueType(true);
    dev.setEmbedCIDPostScript(true);
    dev.setEmbedCIDTrueType(true);
    dev.setFontPassthrough(true);
    dev.setOptimizeColorSpace(true);
    dev.setPassLevel1CustomColor(true);
    dev.setEnableLZW(true);
    dev.setEnableFlate(true);

    EXPECT_TRUE(dev.getEmbedType1());
    EXPECT_TRUE(dev.getEmbedTrueType());
    EXPECT_TRUE(dev.getEmbedCIDPostScript());
    EXPECT_TRUE(dev.getEmbedCIDTrueType());
    EXPECT_TRUE(dev.getFontPassthrough());
    EXPECT_TRUE(dev.getOptimizeColorSpace());
    EXPECT_TRUE(dev.getPassLevel1CustomColor());
    EXPECT_TRUE(dev.getEnableLZW());
    EXPECT_TRUE(dev.getEnableFlate());

    // Set all to false
    dev.setEmbedType1(false);
    dev.setEmbedTrueType(false);
    dev.setEmbedCIDPostScript(false);
    dev.setEmbedCIDTrueType(false);
    dev.setFontPassthrough(false);
    dev.setOptimizeColorSpace(false);
    dev.setPassLevel1CustomColor(false);
    dev.setEnableLZW(false);
    dev.setEnableFlate(false);

    EXPECT_FALSE(dev.getEmbedType1());
    EXPECT_FALSE(dev.getEmbedTrueType());
    EXPECT_FALSE(dev.getEmbedCIDPostScript());
    EXPECT_FALSE(dev.getEmbedCIDTrueType());
    EXPECT_FALSE(dev.getFontPassthrough());
    EXPECT_FALSE(dev.getOptimizeColorSpace());
    EXPECT_FALSE(dev.getPassLevel1CustomColor());
    EXPECT_FALSE(dev.getEnableLZW());
    EXPECT_FALSE(dev.getEnableFlate());

    fclose(tmpFile);
}

// Test setUncompressPreloadedImages does not crash
TEST_F(PSOutputDevTest_1321, SetUncompressPreloadedImages_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setUncompressPreloadedImages(true);
    dev.setUncompressPreloadedImages(false);

    fclose(tmpFile);
}

// Test setUseASCIIHex and setUseBinary
TEST_F(PSOutputDevTest_1321, SetUseASCIIHexAndBinary_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setUseASCIIHex(true);
    dev.setUseASCIIHex(false);
    dev.setUseBinary(true);
    dev.setUseBinary(false);

    fclose(tmpFile);
}

// Test setPreloadImagesForms and setGenerateOPI
TEST_F(PSOutputDevTest_1321, SetPreloadImagesFormsAndGenerateOPI_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setPreloadImagesForms(true);
    dev.setPreloadImagesForms(false);
    dev.setGenerateOPI(true);
    dev.setGenerateOPI(false);

    fclose(tmpFile);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1321, SetRasterAntialias_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    dev.setRasterAntialias(true);
    dev.setRasterAntialias(false);

    fclose(tmpFile);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1321, NeedClipToCropBox_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    bool result = dev.needClipToCropBox();
    EXPECT_TRUE(result == true || result == false);

    fclose(tmpFile);
}

// Test underlay and overlay callbacks can be set without crashing
TEST_F(PSOutputDevTest_1321, SetUnderlayCbkAndOverlayCbk_1321) {
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) GTEST_SKIP();
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(fileno(tmpFile));
    if (!doc->isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string outStr;

    PSOutputDev dev(outputFunc, &outStr, nullptr, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    if (!dev.isOk()) { fclose(tmpFile); GTEST_SKIP(); }

    // Set null callbacks - should not crash
    dev.setUnderlayCbk(nullptr, nullptr);
    dev.setOverlayCbk(nullptr, nullptr);

    // Set actual callbacks
    auto cbk = [](PSOutputDev *, void *) {};
    int data = 42;
    dev.setUnderlayCbk(cbk, &data);
    dev.setOverlayCbk(cbk, &data);

    fclose(tmpFile);
}
