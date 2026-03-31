#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <fstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Output function that captures PS output to a string
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1294 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        outputStr.clear();
    }

    // Helper to create a PSOutputDev with FoFiOutputFunc for a given PDF file
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages,
                                                     PSOutMode mode = psModePS,
                                                     PSLevel level = psLevel2) {
        char title[] = "Test";
        auto dev = std::make_unique<PSOutputDev>(
            outputToString, &outputStr, title, doc, pages,
            mode, -1, -1, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, level);
        if (dev->isOk()) {
            return dev;
        }
        return nullptr;
    }

    std::string outputStr;
};

// Test useDrawChar returns false
TEST_F(PSOutputDevTest_1294, UseDrawCharReturnsFalse_1294) {
    // Create a minimal valid PDF in memory or from file
    // Since we need a PDFDoc, let's try to create a simple one
    // We'll test with a nullptr doc scenario - but that may crash
    // Instead, let's create a minimal PDF file
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) {
        GTEST_SKIP() << "Cannot create PSOutputDev";
    }

    EXPECT_FALSE(dev->useDrawChar());
}

// Test upsideDown
TEST_F(PSOutputDevTest_1294, UpsideDownReturnsExpected_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    // upsideDown typically returns true for PS output
    EXPECT_TRUE(dev->upsideDown());
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1294, UseTilingPatternFill_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1294, UseDrawForm_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_TRUE(dev->useDrawForm());
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1294, InterpretType3Chars_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    // interpretType3Chars should return false for PS output
    EXPECT_FALSE(dev->interpretType3Chars());
}

// Test setter/getter for EmbedType1
TEST_F(PSOutputDevTest_1294, SetGetEmbedType1_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setter/getter for EmbedTrueType
TEST_F(PSOutputDevTest_1294, SetGetEmbedTrueType_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setter/getter for EmbedCIDPostScript
TEST_F(PSOutputDevTest_1294, SetGetEmbedCIDPostScript_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setter/getter for EmbedCIDTrueType
TEST_F(PSOutputDevTest_1294, SetGetEmbedCIDTrueType_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test setter/getter for FontPassthrough
TEST_F(PSOutputDevTest_1294, SetGetFontPassthrough_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setter/getter for OptimizeColorSpace
TEST_F(PSOutputDevTest_1294, SetGetOptimizeColorSpace_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setter/getter for PassLevel1CustomColor
TEST_F(PSOutputDevTest_1294, SetGetPassLevel1CustomColor_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test setter/getter for EnableLZW
TEST_F(PSOutputDevTest_1294, SetGetEnableLZW_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setter/getter for EnableFlate
TEST_F(PSOutputDevTest_1294, SetGetEnableFlate_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test setDisplayText doesn't crash
TEST_F(PSOutputDevTest_1294, SetDisplayTextNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setDisplayText(true));
    EXPECT_NO_THROW(dev->setDisplayText(false));
}

// Test setPSCenter doesn't crash
TEST_F(PSOutputDevTest_1294, SetPSCenterNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setPSCenter(true));
    EXPECT_NO_THROW(dev->setPSCenter(false));
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1294, SetPSExpandShrinkNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setPSExpandSmaller(true));
    EXPECT_NO_THROW(dev->setPSExpandSmaller(false));
    EXPECT_NO_THROW(dev->setPSShrinkLarger(true));
    EXPECT_NO_THROW(dev->setPSShrinkLarger(false));
}

// Test setOffset and setScale and setRotate and setClip don't crash
TEST_F(PSOutputDevTest_1294, SetTransformParametersNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setOffset(10.0, 20.0));
    EXPECT_NO_THROW(dev->setScale(1.5, 2.0));
    EXPECT_NO_THROW(dev->setRotate(90));
    EXPECT_NO_THROW(dev->setClip(0.0, 0.0, 612.0, 792.0));
}

// Test setOffset with zero values
TEST_F(PSOutputDevTest_1294, SetOffsetZeroValues_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setOffset(0.0, 0.0));
}

// Test setScale with negative values (boundary)
TEST_F(PSOutputDevTest_1294, SetScaleNegativeValues_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setScale(-1.0, -1.0));
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1294, SetOverprintPreviewNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setOverprintPreview(true));
    EXPECT_NO_THROW(dev->setOverprintPreview(false));
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1294, SetRasterResolutionNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setRasterResolution(300.0));
    EXPECT_NO_THROW(dev->setRasterResolution(72.0));
    EXPECT_NO_THROW(dev->setRasterResolution(1200.0));
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1294, SetRasterAntialiasNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setRasterAntialias(true));
    EXPECT_NO_THROW(dev->setRasterAntialias(false));
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1294, SetRasterMonoNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setRasterMono());
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1294, SetUncompressPreloadedImagesNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setUncompressPreloadedImages(true));
    EXPECT_NO_THROW(dev->setUncompressPreloadedImages(false));
}

// Test setUseASCIIHex and setUseBinary
TEST_F(PSOutputDevTest_1294, SetUseASCIIHexAndBinaryNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setUseASCIIHex(true));
    EXPECT_NO_THROW(dev->setUseASCIIHex(false));
    EXPECT_NO_THROW(dev->setUseBinary(true));
    EXPECT_NO_THROW(dev->setUseBinary(false));
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1294, SetGenerateOPINoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setGenerateOPI(true));
    EXPECT_NO_THROW(dev->setGenerateOPI(false));
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1294, SetPreloadImagesFormsNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setPreloadImagesForms(true));
    EXPECT_NO_THROW(dev->setPreloadImagesForms(false));
}

// Test setUnderlayCbk and setOverlayCbk with nullptr
TEST_F(PSOutputDevTest_1294, SetCallbacksNullNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setUnderlayCbk(nullptr, nullptr));
    EXPECT_NO_THROW(dev->setOverlayCbk(nullptr, nullptr));
}

// Test setForceRasterize
TEST_F(PSOutputDevTest_1294, SetForceRasterizeNoThrow_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    EXPECT_NO_THROW(dev->setForceRasterize(psRasterizeWhenNeeded));
    EXPECT_NO_THROW(dev->setForceRasterize(psAlwaysRasterize));
    EXPECT_NO_THROW(dev->setForceRasterize(psNeverRasterize));
}

// Test isOk returns true for valid construction
TEST_F(PSOutputDevTest_1294, IsOkReturnsTrueForValidConstruction_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    char title[] = "Test";
    PSOutputDev dev(outputToString, &outputStr, title, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    EXPECT_TRUE(dev.isOk());
}

// Test useShadedFills for different types
TEST_F(PSOutputDevTest_1294, UseShadedFillsForVariousTypes_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    // Test different shading types (1-7 are valid PDF shading types)
    for (int type = 1; type <= 7; ++type) {
        // Just verify it doesn't crash and returns a bool
        bool result = dev->useShadedFills(type);
        (void)result; // We just check it doesn't crash
    }
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1294, NeedClipToCropBox_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    // Just verify it returns without crashing
    bool result = dev->needClipToCropBox();
    (void)result;
}

// Test with EPS mode
TEST_F(PSOutputDevTest_1294, EPSModeConstruction_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    char title[] = "Test EPS";
    PSOutputDev dev(outputToString, &outputStr, title, doc.get(), pages,
                    psModeEPS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    // isOk should still be true for EPS mode
    EXPECT_TRUE(dev.isOk());
}

// Test with psLevel1
TEST_F(PSOutputDevTest_1294, Level1Construction_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    char title[] = "Test L1";
    PSOutputDev dev(outputToString, &outputStr, title, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel1);

    EXPECT_TRUE(dev.isOk());
}

// Test with psLevel3
TEST_F(PSOutputDevTest_1294, Level3Construction_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    char title[] = "Test L3";
    PSOutputDev dev(outputToString, &outputStr, title, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel3);

    EXPECT_TRUE(dev.isOk());
}

// Test multiple setter calls in sequence
TEST_F(PSOutputDevTest_1294, MultipleSettersInSequence_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();

    // Set everything to true
    dev->setEmbedType1(true);
    dev->setEmbedTrueType(true);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(true);
    dev->setFontPassthrough(true);
    dev->setOptimizeColorSpace(true);
    dev->setPassLevel1CustomColor(true);
    dev->setEnableLZW(true);
    dev->setEnableFlate(true);

    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_TRUE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());

    // Set everything to false
    dev->setEmbedType1(false);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(false);
    dev->setOptimizeColorSpace(false);
    dev->setPassLevel1CustomColor(false);
    dev->setEnableLZW(false);
    dev->setEnableFlate(false);

    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_FALSE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test with custom paper size
TEST_F(PSOutputDevTest_1294, CustomPaperSizeConstruction_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    char title[] = "Test Custom";
    // Use custom paper size 595x842 (A4 in points)
    PSOutputDev dev(outputToString, &outputStr, title, doc.get(), pages,
                    psModePS, 595, 842, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    EXPECT_TRUE(dev.isOk());
}

// Test with duplex enabled
TEST_F(PSOutputDevTest_1294, DuplexConstruction_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    char title[] = "Test Duplex";
    PSOutputDev dev(outputToString, &outputStr, title, doc.get(), pages,
                    psModePS, -1, -1, false, true,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    EXPECT_TRUE(dev.isOk());
}

// Test with noCrop enabled
TEST_F(PSOutputDevTest_1294, NoCropConstruction_1294) {
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

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) GTEST_SKIP();

    std::vector<int> pages = {1};
    char title[] = "Test NoCrop";
    PSOutputDev dev(outputToString, &outputStr, title, doc.get(), pages,
                    psModePS, -1, -1, true, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);

    EXPECT_TRUE(dev.isOk());
}
