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
#include "splash/SplashTypes.h"

namespace {

// Helper function to collect PS output
void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1338 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with an output function
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        outputBuffer.clear();
        auto dev = std::make_unique<PSOutputDev>(
            (FoFiOutputFunc)outputFunc, &outputBuffer,
            const_cast<char *>("Test Title"), doc,
            pages, psModePS,
            -1, -1, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        if (dev && dev->isOk()) {
            return dev;
        }
        return nullptr;
    }

    std::string outputBuffer;
};

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevTest_1338, SetGetEmbedType1_True_1338) {
    // We need a valid PDF to construct PSOutputDev
    // Create a minimal PDF in a temp file
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    // Create a GooString for the file name approach - use fd approach
    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());

            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
        }
    }
    fclose(tmpFile);
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevTest_1338, SetGetEmbedTrueType_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setEmbedTrueType(true);
            EXPECT_TRUE(dev->getEmbedTrueType());

            dev->setEmbedTrueType(false);
            EXPECT_FALSE(dev->getEmbedTrueType());
        }
    }
    fclose(tmpFile);
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1338, SetGetEmbedCIDPostScript_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setEmbedCIDPostScript(true);
            EXPECT_TRUE(dev->getEmbedCIDPostScript());

            dev->setEmbedCIDPostScript(false);
            EXPECT_FALSE(dev->getEmbedCIDPostScript());
        }
    }
    fclose(tmpFile);
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1338, SetGetEmbedCIDTrueType_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setEmbedCIDTrueType(true);
            EXPECT_TRUE(dev->getEmbedCIDTrueType());

            dev->setEmbedCIDTrueType(false);
            EXPECT_FALSE(dev->getEmbedCIDTrueType());
        }
    }
    fclose(tmpFile);
}

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevTest_1338, SetGetFontPassthrough_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setFontPassthrough(true);
            EXPECT_TRUE(dev->getFontPassthrough());

            dev->setFontPassthrough(false);
            EXPECT_FALSE(dev->getFontPassthrough());
        }
    }
    fclose(tmpFile);
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1338, SetGetOptimizeColorSpace_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setOptimizeColorSpace(true);
            EXPECT_TRUE(dev->getOptimizeColorSpace());

            dev->setOptimizeColorSpace(false);
            EXPECT_FALSE(dev->getOptimizeColorSpace());
        }
    }
    fclose(tmpFile);
}

// Test setEnableLZW and getEnableLZW
TEST_F(PSOutputDevTest_1338, SetGetEnableLZW_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setEnableLZW(true);
            EXPECT_TRUE(dev->getEnableLZW());

            dev->setEnableLZW(false);
            EXPECT_FALSE(dev->getEnableLZW());
        }
    }
    fclose(tmpFile);
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevTest_1338, SetGetEnableFlate_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setEnableFlate(true);
            EXPECT_TRUE(dev->getEnableFlate());

            dev->setEnableFlate(false);
            EXPECT_FALSE(dev->getEnableFlate());
        }
    }
    fclose(tmpFile);
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1338, SetGetPassLevel1CustomColor_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            dev->setPassLevel1CustomColor(true);
            EXPECT_TRUE(dev->getPassLevel1CustomColor());

            dev->setPassLevel1CustomColor(false);
            EXPECT_FALSE(dev->getPassLevel1CustomColor());
        }
    }
    fclose(tmpFile);
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1338, UpsideDown_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            // PS coordinate system has origin at bottom-left, so upsideDown should return false
            EXPECT_FALSE(dev->upsideDown());
        }
    }
    fclose(tmpFile);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1338, UseDrawChar_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            // PSOutputDev uses drawString, not drawChar
            EXPECT_FALSE(dev->useDrawChar());
        }
    }
    fclose(tmpFile);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1338, UseTilingPatternFill_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_TRUE(dev->useTilingPatternFill());
        }
    }
    fclose(tmpFile);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1338, UseDrawForm_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_TRUE(dev->useDrawForm());
        }
    }
    fclose(tmpFile);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1338, InterpretType3Chars_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            // PSOutputDev should interpret Type 3 chars
            EXPECT_TRUE(dev->interpretType3Chars());
        }
    }
    fclose(tmpFile);
}

// Test multiple setter calls in sequence
TEST_F(PSOutputDevTest_1338, MultipleSetterCallsSequence_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            // Set all to true
            dev->setEmbedType1(true);
            dev->setEmbedTrueType(true);
            dev->setEmbedCIDPostScript(true);
            dev->setEmbedCIDTrueType(true);
            dev->setFontPassthrough(true);
            dev->setOptimizeColorSpace(true);
            dev->setEnableLZW(true);
            dev->setEnableFlate(true);

            EXPECT_TRUE(dev->getEmbedType1());
            EXPECT_TRUE(dev->getEmbedTrueType());
            EXPECT_TRUE(dev->getEmbedCIDPostScript());
            EXPECT_TRUE(dev->getEmbedCIDTrueType());
            EXPECT_TRUE(dev->getFontPassthrough());
            EXPECT_TRUE(dev->getOptimizeColorSpace());
            EXPECT_TRUE(dev->getEnableLZW());
            EXPECT_TRUE(dev->getEnableFlate());

            // Set all to false
            dev->setEmbedType1(false);
            dev->setEmbedTrueType(false);
            dev->setEmbedCIDPostScript(false);
            dev->setEmbedCIDTrueType(false);
            dev->setFontPassthrough(false);
            dev->setOptimizeColorSpace(false);
            dev->setEnableLZW(false);
            dev->setEnableFlate(false);

            EXPECT_FALSE(dev->getEmbedType1());
            EXPECT_FALSE(dev->getEmbedTrueType());
            EXPECT_FALSE(dev->getEmbedCIDPostScript());
            EXPECT_FALSE(dev->getEmbedCIDTrueType());
            EXPECT_FALSE(dev->getFontPassthrough());
            EXPECT_FALSE(dev->getOptimizeColorSpace());
            EXPECT_FALSE(dev->getEnableLZW());
            EXPECT_FALSE(dev->getEnableFlate());
        }
    }
    fclose(tmpFile);
}

// Test setDisplayText does not crash
TEST_F(PSOutputDevTest_1338, SetDisplayText_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setDisplayText(true));
            EXPECT_NO_FATAL_FAILURE(dev->setDisplayText(false));
        }
    }
    fclose(tmpFile);
}

// Test setPSCenter does not crash
TEST_F(PSOutputDevTest_1338, SetPSCenter_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setPSCenter(true));
            EXPECT_NO_FATAL_FAILURE(dev->setPSCenter(false));
        }
    }
    fclose(tmpFile);
}

// Test setPSExpandSmaller does not crash
TEST_F(PSOutputDevTest_1338, SetPSExpandSmaller_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setPSExpandSmaller(true));
            EXPECT_NO_FATAL_FAILURE(dev->setPSExpandSmaller(false));
        }
    }
    fclose(tmpFile);
}

// Test setPSShrinkLarger does not crash
TEST_F(PSOutputDevTest_1338, SetPSShrinkLarger_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setPSShrinkLarger(true));
            EXPECT_NO_FATAL_FAILURE(dev->setPSShrinkLarger(false));
        }
    }
    fclose(tmpFile);
}

// Test setOverprintPreview does not crash
TEST_F(PSOutputDevTest_1338, SetOverprintPreview_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setOverprintPreview(true));
            EXPECT_NO_FATAL_FAILURE(dev->setOverprintPreview(false));
        }
    }
    fclose(tmpFile);
}

// Test setOffset does not crash
TEST_F(PSOutputDevTest_1338, SetOffset_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setOffset(10.0, 20.0));
            EXPECT_NO_FATAL_FAILURE(dev->setOffset(0.0, 0.0));
            EXPECT_NO_FATAL_FAILURE(dev->setOffset(-5.0, -10.0));
        }
    }
    fclose(tmpFile);
}

// Test setScale does not crash
TEST_F(PSOutputDevTest_1338, SetScale_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setScale(1.0, 1.0));
            EXPECT_NO_FATAL_FAILURE(dev->setScale(2.0, 0.5));
        }
    }
    fclose(tmpFile);
}

// Test setRotate does not crash
TEST_F(PSOutputDevTest_1338, SetRotate_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setRotate(0));
            EXPECT_NO_FATAL_FAILURE(dev->setRotate(90));
            EXPECT_NO_FATAL_FAILURE(dev->setRotate(180));
            EXPECT_NO_FATAL_FAILURE(dev->setRotate(270));
        }
    }
    fclose(tmpFile);
}

// Test setClip does not crash
TEST_F(PSOutputDevTest_1338, SetClip_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setClip(0.0, 0.0, 612.0, 792.0));
        }
    }
    fclose(tmpFile);
}

// Test setRasterResolution does not crash
TEST_F(PSOutputDevTest_1338, SetRasterResolution_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setRasterResolution(300.0));
            EXPECT_NO_FATAL_FAILURE(dev->setRasterResolution(72.0));
            EXPECT_NO_FATAL_FAILURE(dev->setRasterResolution(600.0));
        }
    }
    fclose(tmpFile);
}

// Test setRasterAntialias does not crash
TEST_F(PSOutputDevTest_1338, SetRasterAntialias_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setRasterAntialias(true));
            EXPECT_NO_FATAL_FAILURE(dev->setRasterAntialias(false));
        }
    }
    fclose(tmpFile);
}

// Test setUncompressPreloadedImages does not crash
TEST_F(PSOutputDevTest_1338, SetUncompressPreloadedImages_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setUncompressPreloadedImages(true));
            EXPECT_NO_FATAL_FAILURE(dev->setUncompressPreloadedImages(false));
        }
    }
    fclose(tmpFile);
}

// Test setProcessColorFormat does not crash with various SplashColorMode values
TEST_F(PSOutputDevTest_1338, SetProcessColorFormat_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setProcessColorFormat(splashModeMono8));
            EXPECT_NO_FATAL_FAILURE(dev->setProcessColorFormat(splashModeRGB8));
            EXPECT_NO_FATAL_FAILURE(dev->setProcessColorFormat(splashModeCMYK8));
        }
    }
    fclose(tmpFile);
}

// Test setRasterMono does not crash
TEST_F(PSOutputDevTest_1338, SetRasterMono_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setRasterMono());
        }
    }
    fclose(tmpFile);
}

// Test setUseASCIIHex does not crash
TEST_F(PSOutputDevTest_1338, SetUseASCIIHex_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setUseASCIIHex(true));
            EXPECT_NO_FATAL_FAILURE(dev->setUseASCIIHex(false));
        }
    }
    fclose(tmpFile);
}

// Test setUseBinary does not crash
TEST_F(PSOutputDevTest_1338, SetUseBinary_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setUseBinary(true));
            EXPECT_NO_FATAL_FAILURE(dev->setUseBinary(false));
        }
    }
    fclose(tmpFile);
}

// Test setGenerateOPI does not crash
TEST_F(PSOutputDevTest_1338, SetGenerateOPI_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setGenerateOPI(true));
            EXPECT_NO_FATAL_FAILURE(dev->setGenerateOPI(false));
        }
    }
    fclose(tmpFile);
}

// Test setPreloadImagesForms does not crash
TEST_F(PSOutputDevTest_1338, SetPreloadImagesForms_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setPreloadImagesForms(true));
            EXPECT_NO_FATAL_FAILURE(dev->setPreloadImagesForms(false));
        }
    }
    fclose(tmpFile);
}

// Test setForceRasterize does not crash
TEST_F(PSOutputDevTest_1338, SetForceRasterize_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            EXPECT_NO_FATAL_FAILURE(dev->setForceRasterize(psRasterizeWhenNeeded));
            EXPECT_NO_FATAL_FAILURE(dev->setForceRasterize(psAlwaysRasterize));
            EXPECT_NO_FATAL_FAILURE(dev->setForceRasterize(psNeverRasterize));
        }
    }
    fclose(tmpFile);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1338, NeedClipToCropBox_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            // Just verify it returns a bool value without crashing
            bool result = dev->needClipToCropBox();
            (void)result; // suppress unused variable warning
            SUCCEED();
        }
    }
    fclose(tmpFile);
}

// Test isOk on a valid PSOutputDev
TEST_F(PSOutputDevTest_1338, IsOkValidDevice_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        outputBuffer.clear();
        auto dev = std::make_unique<PSOutputDev>(
            (FoFiOutputFunc)outputFunc, &outputBuffer,
            const_cast<char *>("Test"), doc.get(),
            pages, psModePS,
            -1, -1, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        if (dev) {
            EXPECT_TRUE(dev->isOk());
        }
    }
    fclose(tmpFile);
}

// Test useShadedFills with different types
TEST_F(PSOutputDevTest_1338, UseShadedFills_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            // Test different shaded fill types (1-7 typically)
            for (int type = 1; type <= 7; ++type) {
                bool result = dev->useShadedFills(type);
                (void)result;
            }
            SUCCEED();
        }
    }
    fclose(tmpFile);
}

// Test underlay and overlay callbacks
TEST_F(PSOutputDevTest_1338, SetUnderlayCbk_1338) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);

    if (doc->isOk()) {
        std::vector<int> pages = {1};
        auto dev = createPSOutputDev(doc.get(), pages);
        if (dev) {
            int data = 42;
            EXPECT_NO_FATAL_FAILURE(dev->setUnderlayCbk(nullptr, nullptr));
            EXPECT_NO_FATAL_FAILURE(dev->setOverlayCbk(nullptr, nullptr));
        }
    }
    fclose(tmpFile);
}

} // namespace
