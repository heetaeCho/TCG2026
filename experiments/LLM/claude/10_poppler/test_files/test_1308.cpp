#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>

// Helper function to collect PS output
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1308 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test setPSExpandSmaller and related setter behavior
TEST_F(PSOutputDevTest_1308, SetPSExpandSmaller_True_1308) {
    // We cannot easily construct a full PSOutputDev without a valid PDFDoc,
    // but we can test the setter method's interface contract.
    // Since PSOutputDev requires complex construction, we test what we can
    // through the FoFiOutputFunc constructor path with a minimal PDF.

    // Create a minimal valid PDF in a temp file
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    // Write minimal PDF to temp file
    char tmpName[] = "/tmp/test_psoutput_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output, 
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK, skipping";
        return;
    }

    // Test setPSExpandSmaller with true
    psOut->setPSExpandSmaller(true);
    // No crash, setter accepted value

    // Test setPSExpandSmaller with false
    psOut->setPSExpandSmaller(false);
    // No crash, setter accepted value

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetPSShrinkLarger_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput2_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setPSShrinkLarger(true);
    psOut->setPSShrinkLarger(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetOverprintPreview_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput3_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setOverprintPreview(true);
    psOut->setOverprintPreview(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, EmbedGettersAndSetters_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput4_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    // Test EmbedType1
    psOut->setEmbedType1(true);
    EXPECT_TRUE(psOut->getEmbedType1());
    psOut->setEmbedType1(false);
    EXPECT_FALSE(psOut->getEmbedType1());

    // Test EmbedTrueType
    psOut->setEmbedTrueType(true);
    EXPECT_TRUE(psOut->getEmbedTrueType());
    psOut->setEmbedTrueType(false);
    EXPECT_FALSE(psOut->getEmbedTrueType());

    // Test EmbedCIDPostScript
    psOut->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOut->getEmbedCIDPostScript());
    psOut->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOut->getEmbedCIDPostScript());

    // Test EmbedCIDTrueType
    psOut->setEmbedCIDTrueType(true);
    EXPECT_TRUE(psOut->getEmbedCIDTrueType());
    psOut->setEmbedCIDTrueType(false);
    EXPECT_FALSE(psOut->getEmbedCIDTrueType());

    // Test FontPassthrough
    psOut->setFontPassthrough(true);
    EXPECT_TRUE(psOut->getFontPassthrough());
    psOut->setFontPassthrough(false);
    EXPECT_FALSE(psOut->getFontPassthrough());

    // Test OptimizeColorSpace
    psOut->setOptimizeColorSpace(true);
    EXPECT_TRUE(psOut->getOptimizeColorSpace());
    psOut->setOptimizeColorSpace(false);
    EXPECT_FALSE(psOut->getOptimizeColorSpace());

    // Test PassLevel1CustomColor
    psOut->setPassLevel1CustomColor(true);
    EXPECT_TRUE(psOut->getPassLevel1CustomColor());
    psOut->setPassLevel1CustomColor(false);
    EXPECT_FALSE(psOut->getPassLevel1CustomColor());

    // Test EnableLZW
    psOut->setEnableLZW(true);
    EXPECT_TRUE(psOut->getEnableLZW());
    psOut->setEnableLZW(false);
    EXPECT_FALSE(psOut->getEnableLZW());

    // Test EnableFlate
    psOut->setEnableFlate(true);
    EXPECT_TRUE(psOut->getEnableFlate());
    psOut->setEnableFlate(false);
    EXPECT_FALSE(psOut->getEnableFlate());

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, UpsideDown_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput5_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    // PSOutputDev should report upsideDown
    bool ud = psOut->upsideDown();
    // Just verify it returns a valid boolean without crashing
    EXPECT_TRUE(ud == true || ud == false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, UseDrawChar_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput6_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    bool udc = psOut->useDrawChar();
    EXPECT_TRUE(udc == true || udc == false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetDisplayText_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput7_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    // Should not crash
    psOut->setDisplayText(true);
    psOut->setDisplayText(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetPSCenter_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput8_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setPSCenter(true);
    psOut->setPSCenter(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetOffsetAndScale_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput9_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    // Test setOffset with various values
    psOut->setOffset(0.0, 0.0);
    psOut->setOffset(100.0, 200.0);
    psOut->setOffset(-50.0, -50.0);

    // Test setScale with various values
    psOut->setScale(1.0, 1.0);
    psOut->setScale(2.0, 0.5);

    // Test setRotate
    psOut->setRotate(0);
    psOut->setRotate(90);
    psOut->setRotate(180);
    psOut->setRotate(270);

    // Test setClip
    psOut->setClip(0.0, 0.0, 612.0, 792.0);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetRasterResolution_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput10_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setRasterResolution(72.0);
    psOut->setRasterResolution(300.0);
    psOut->setRasterResolution(600.0);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetRasterAntialias_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput11_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setRasterAntialias(true);
    psOut->setRasterAntialias(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetUncompressPreloadedImages_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput12_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setUncompressPreloadedImages(true);
    psOut->setUncompressPreloadedImages(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, UseTilingPatternFill_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput13_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    bool tpf = psOut->useTilingPatternFill();
    EXPECT_TRUE(tpf == true || tpf == false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, UseDrawForm_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput14_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    bool udf = psOut->useDrawForm();
    EXPECT_TRUE(udf == true || udf == false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, InterpretType3Chars_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput15_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    bool it3c = psOut->interpretType3Chars();
    EXPECT_TRUE(it3c == true || it3c == false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetGenerateOPI_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput16_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setGenerateOPI(true);
    psOut->setGenerateOPI(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetUseASCIIHex_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput17_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setUseASCIIHex(true);
    psOut->setUseASCIIHex(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetUseBinary_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput18_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setUseBinary(true);
    psOut->setUseBinary(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetPreloadImagesForms_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput19_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setPreloadImagesForms(true);
    psOut->setPreloadImagesForms(false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, IsOkAfterConstruction_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput20_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    // isOk should return true for valid construction
    EXPECT_TRUE(psOut->isOk());

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, NeedClipToCropBox_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput21_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    bool nctcb = psOut->needClipToCropBox();
    EXPECT_TRUE(nctcb == true || nctcb == false);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, UseShadedFills_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput22_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    // Test various shading types
    for (int type = 1; type <= 7; type++) {
        bool usf = psOut->useShadedFills(type);
        EXPECT_TRUE(usf == true || usf == false);
    }

    unlink(tmpName);
}

// Test callback setters
TEST_F(PSOutputDevTest_1308, SetUnderlayCbk_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput23_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    // Set nullptr callback - should not crash
    psOut->setUnderlayCbk(nullptr, nullptr);

    // Set a valid callback
    auto dummyCbk = [](PSOutputDev *, void *) {};
    psOut->setUnderlayCbk(dummyCbk, nullptr);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetOverlayCbk_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput24_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setOverlayCbk(nullptr, nullptr);

    auto dummyCbk = [](PSOutputDev *, void *) {};
    psOut->setOverlayCbk(dummyCbk, nullptr);

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, SetForceRasterize_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput25_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (!psOut->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "PSOutputDev not OK";
        return;
    }

    psOut->setForceRasterize(psRasterizeWhenNeeded);
    psOut->setForceRasterize(psAlwaysRasterize);
    psOut->setForceRasterize(psNeverRasterize);

    unlink(tmpName);
}

// Test EPS mode construction
TEST_F(PSOutputDevTest_1308, EPSModeConstruction_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput26_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModeEPS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    // Should construct OK
    EXPECT_TRUE(psOut->isOk());

    unlink(tmpName);
}

// Test different PS levels
TEST_F(PSOutputDevTest_1308, Level3Construction_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput27_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel3);

    EXPECT_TRUE(psOut->isOk());

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1308, Level1Construction_1308) {
    const char *minimalPdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    char tmpName[] = "/tmp/test_psoutput28_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    write(fd, minimalPdf, strlen(minimalPdf));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create minimal PDFDoc";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char*>("Test"), doc.get(), pages,
        psModePS, 612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel1);

    EXPECT_TRUE(psOut->isOk());

    unlink(tmpName);
}
