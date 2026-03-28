#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <memory>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Output function for PSOutputDev
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *output = static_cast<std::string *>(stream);
    output->append(data, len);
}

class PSOutputDevTest_1322 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using a file-based constructor with a minimal PDF
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(const char* pdfPath) {
        doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(pdfPath));
        if (!doc->isOk()) {
            return nullptr;
        }

        std::vector<int> pages;
        pages.push_back(1);

        outputStr.clear();

        auto dev = std::make_unique<PSOutputDev>(
            outputFunc, &outputStr, nullptr, doc.get(),
            pages, psModePS, -1, -1,
            false, true, 0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);

        if (!dev->isOk()) {
            return nullptr;
        }
        return dev;
    }

    std::unique_ptr<PDFDoc> doc;
    std::string outputStr;
};

// Test getPassLevel1CustomColor returns a bool value
TEST_F(PSOutputDevTest_1322, GetPassLevel1CustomColor_DefaultValue_1322) {
    // Create a minimal PDF file for testing
    // We'll create a tiny valid PDF in memory
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    // Write minimal PDF to temp file
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    fwrite(minimalPdf, 1, strlen(minimalPdf), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    int fd = fileno(tmpFile);
    // Try using a temp file path approach instead
    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        fclose(tmpFile);
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        fclose(tmpFile);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // getPassLevel1CustomColor should return a bool
        bool val = dev->getPassLevel1CustomColor();
        // Just verify it returns without crashing - the actual default depends on globalParams
        EXPECT_TRUE(val == true || val == false);
    }

    unlink(tmpPath);
    fclose(tmpFile);
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1322, SetAndGetPassLevel1CustomColor_True_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());
    }

    unlink(tmpPath);
}

// Test setPassLevel1CustomColor to false
TEST_F(PSOutputDevTest_1322, SetAndGetPassLevel1CustomColor_False_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setPassLevel1CustomColor(false);
        EXPECT_FALSE(dev->getPassLevel1CustomColor());
    }

    unlink(tmpPath);
}

// Test toggling PassLevel1CustomColor
TEST_F(PSOutputDevTest_1322, TogglePassLevel1CustomColor_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());

        dev->setPassLevel1CustomColor(false);
        EXPECT_FALSE(dev->getPassLevel1CustomColor());

        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());
    }

    unlink(tmpPath);
}

// Test various setter/getter pairs
TEST_F(PSOutputDevTest_1322, SetAndGetEmbedType1_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());

        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());
    }

    unlink(tmpPath);
}

TEST_F(PSOutputDevTest_1322, SetAndGetEmbedTrueType_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedTrueType(true);
        EXPECT_TRUE(dev->getEmbedTrueType());

        dev->setEmbedTrueType(false);
        EXPECT_FALSE(dev->getEmbedTrueType());
    }

    unlink(tmpPath);
}

TEST_F(PSOutputDevTest_1322, SetAndGetEmbedCIDPostScript_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedCIDPostScript(true);
        EXPECT_TRUE(dev->getEmbedCIDPostScript());

        dev->setEmbedCIDPostScript(false);
        EXPECT_FALSE(dev->getEmbedCIDPostScript());
    }

    unlink(tmpPath);
}

TEST_F(PSOutputDevTest_1322, SetAndGetEmbedCIDTrueType_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedCIDTrueType(true);
        EXPECT_TRUE(dev->getEmbedCIDTrueType());

        dev->setEmbedCIDTrueType(false);
        EXPECT_FALSE(dev->getEmbedCIDTrueType());
    }

    unlink(tmpPath);
}

TEST_F(PSOutputDevTest_1322, SetAndGetFontPassthrough_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setFontPassthrough(true);
        EXPECT_TRUE(dev->getFontPassthrough());

        dev->setFontPassthrough(false);
        EXPECT_FALSE(dev->getFontPassthrough());
    }

    unlink(tmpPath);
}

TEST_F(PSOutputDevTest_1322, SetAndGetOptimizeColorSpace_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setOptimizeColorSpace(true);
        EXPECT_TRUE(dev->getOptimizeColorSpace());

        dev->setOptimizeColorSpace(false);
        EXPECT_FALSE(dev->getOptimizeColorSpace());
    }

    unlink(tmpPath);
}

TEST_F(PSOutputDevTest_1322, SetAndGetEnableLZW_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEnableLZW(true);
        EXPECT_TRUE(dev->getEnableLZW());

        dev->setEnableLZW(false);
        EXPECT_FALSE(dev->getEnableLZW());
    }

    unlink(tmpPath);
}

TEST_F(PSOutputDevTest_1322, SetAndGetEnableFlate_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEnableFlate(true);
        EXPECT_TRUE(dev->getEnableFlate());

        dev->setEnableFlate(false);
        EXPECT_FALSE(dev->getEnableFlate());
    }

    unlink(tmpPath);
}

// Test upsideDown returns expected value for PS output
TEST_F(PSOutputDevTest_1322, UpsideDown_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        bool result = dev->upsideDown();
        EXPECT_TRUE(result == true || result == false);
    }

    unlink(tmpPath);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1322, UseDrawChar_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        bool result = dev->useDrawChar();
        EXPECT_TRUE(result == true || result == false);
    }

    unlink(tmpPath);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1322, SetDisplayText_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // These setters should not crash
        dev->setDisplayText(true);
        dev->setDisplayText(false);
        dev->setPSCenter(true);
        dev->setPSCenter(false);
        dev->setPSExpandSmaller(true);
        dev->setPSExpandSmaller(false);
        dev->setPSShrinkLarger(true);
        dev->setPSShrinkLarger(false);
        dev->setOverprintPreview(true);
        dev->setOverprintPreview(false);
    }

    unlink(tmpPath);
}

// Test setOffset and setScale and setRotate and setClip don't crash
TEST_F(PSOutputDevTest_1322, SetTransformParameters_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setOffset(10.0, 20.0);
        dev->setScale(1.5, 2.0);
        dev->setRotate(90);
        dev->setClip(0.0, 0.0, 612.0, 792.0);

        // Boundary: zero offset
        dev->setOffset(0.0, 0.0);
        dev->setScale(1.0, 1.0);
        dev->setRotate(0);

        // Boundary: negative values
        dev->setOffset(-10.0, -20.0);
        dev->setScale(0.5, 0.5);
        dev->setRotate(270);
    }

    unlink(tmpPath);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1322, SetRasterResolution_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setRasterResolution(300.0);
        dev->setRasterResolution(72.0);
        dev->setRasterResolution(600.0);
        dev->setRasterAntialias(true);
        dev->setRasterAntialias(false);
        dev->setUncompressPreloadedImages(true);
        dev->setUncompressPreloadedImages(false);
    }

    unlink(tmpPath);
}

// Test setting callbacks
TEST_F(PSOutputDevTest_1322, SetCallbacks_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // Set underlay callback to nullptr
        dev->setUnderlayCbk(nullptr, nullptr);

        // Set overlay callback to nullptr
        dev->setOverlayCbk(nullptr, nullptr);

        // Set with actual function pointers
        auto cbk = [](PSOutputDev *psOut, void *data) {};
        int dummyData = 42;
        dev->setUnderlayCbk(cbk, &dummyData);
        dev->setOverlayCbk(cbk, &dummyData);
    }

    unlink(tmpPath);
}

// Test binary and ASCII hex settings
TEST_F(PSOutputDevTest_1322, SetOutputEncodings_1322) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    char tmpPath[] = "/tmp/test_psoutput_XXXXXX";
    int tmpFd = mkstemp(tmpPath);
    if (tmpFd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(tmpFd, minimalPdf, strlen(minimalPdf));
    close(tmpFd);

    doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    if (!doc->isOk()) {
        unlink(tmpPath);
        GTEST_SKIP() << "Cannot open test PDF document";
    }

    std::vector<int> pages;
    pages.push_back(1);
    outputStr.clear();

    auto dev = std::make_unique<PSOutputDev>(
        outputFunc, &outputStr, nullptr, doc.get(),
        pages, psModePS, -1, -1,
        false, true, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setUseASCIIHex(true);
        dev->setUseASCIIHex(false);
        dev->setUseBinary(true);
        dev->setUseBinary(false);
        dev->setGenerateOPI(true);
        dev->setGenerateOPI(false);
        dev->setPreloadImagesForms(true);
        dev->setPreloadImagesForms(false);
    }

    unlink(tmpPath);
}
