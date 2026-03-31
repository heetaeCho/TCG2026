#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper: output function that writes to a std::string buffer
static void stringOutputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1332 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // Returns nullptr if creation fails. Caller owns the pointer.
    PSOutputDev *createPSOutputDev(std::string &outputBuffer, PDFDoc *doc,
                                    const std::vector<int> &pages,
                                    PSOutMode mode = psModePS,
                                    PSLevel level = psLevel2) {
        PSOutputDev *dev = new PSOutputDev(
            stringOutputFunc, &outputBuffer, nullptr, doc, pages,
            mode, -1, -1, false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, level);
        return dev;
    }
};

// Test that setPreloadImagesForms works (the inline method from the header)
TEST_F(PSOutputDevTest_1332, SetPreloadImagesForms_True_1332) {
    // We need a valid PDFDoc to create PSOutputDev.
    // Create a minimal PDF in a temp file
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    // Create PDFDoc from the FILE*
    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create a valid PDFDoc for testing";
    }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev could not be initialized";
    }

    // Test setPreloadImagesForms with true
    dev->setPreloadImagesForms(true);
    // No crash, method completes successfully
    // We can't directly read private member, but we verify it doesn't crash

    // Test setPreloadImagesForms with false
    dev->setPreloadImagesForms(false);

    delete dev;
}

// Test setter/getter pairs for embed flags
TEST_F(PSOutputDevTest_1332, SetGetEmbedType1_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create a valid PDFDoc";
    }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetEmbedTrueType_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) {
        GTEST_SKIP();
    }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetEmbedCIDPostScript_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetEmbedCIDTrueType_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetFontPassthrough_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetOptimizeColorSpace_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetPassLevel1CustomColor_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetEnableLZW_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());

    delete dev;
}

TEST_F(PSOutputDevTest_1332, SetGetEnableFlate_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());

    delete dev;
}

// Test OutputDev interface methods
TEST_F(PSOutputDevTest_1332, UpsideDown_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    // upsideDown should return a bool value
    bool result = dev->upsideDown();
    // Just verify it returns without crash; the actual value depends on implementation
    (void)result;

    delete dev;
}

TEST_F(PSOutputDevTest_1332, UseDrawChar_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    bool result = dev->useDrawChar();
    (void)result;

    delete dev;
}

TEST_F(PSOutputDevTest_1332, UseTilingPatternFill_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    bool result = dev->useTilingPatternFill();
    (void)result;

    delete dev;
}

TEST_F(PSOutputDevTest_1332, UseDrawForm_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    bool result = dev->useDrawForm();
    (void)result;

    delete dev;
}

TEST_F(PSOutputDevTest_1332, InterpretType3Chars_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    bool result = dev->interpretType3Chars();
    (void)result;

    delete dev;
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1332, SetDisplayText_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    // Should not crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);

    delete dev;
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1332, SetPSCenter_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setPSCenter(true);
    dev->setPSCenter(false);

    delete dev;
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1332, SetPSExpandShrink_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);

    delete dev;
}

// Test setOffset and setScale
TEST_F(PSOutputDevTest_1332, SetOffsetAndScale_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setOffset(10.0, 20.0);
    dev->setScale(1.5, 2.0);
    dev->setRotate(90);
    dev->setClip(0.0, 0.0, 612.0, 792.0);

    // Boundary: zero offset and scale
    dev->setOffset(0.0, 0.0);
    dev->setScale(0.0, 0.0);

    // Negative values
    dev->setOffset(-10.0, -20.0);
    dev->setScale(-1.0, -1.0);

    delete dev;
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1332, SetOverprintPreview_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);

    delete dev;
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1332, SetRasterResolution_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);

    delete dev;
}

// Test setGenerateOPI, setUseASCIIHex, setUseBinary
TEST_F(PSOutputDevTest_1332, SetMiscBooleans_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);

    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);

    dev->setUseBinary(true);
    dev->setUseBinary(false);

    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);

    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);

    delete dev;
}

// Test setForceRasterize
TEST_F(PSOutputDevTest_1332, SetForceRasterize_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);

    delete dev;
}

// Test setUnderlayCbk and setOverlayCbk
static bool underlayCalled = false;
static bool overlayCalled = false;

static void testUnderlayCbk(PSOutputDev *psOut, void *data) {
    underlayCalled = true;
}

static void testOverlayCbk(PSOutputDev *psOut, void *data) {
    overlayCalled = true;
}

TEST_F(PSOutputDevTest_1332, SetUnderlayCbk_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    int dummyData = 42;
    dev->setUnderlayCbk(testUnderlayCbk, &dummyData);
    dev->setOverlayCbk(testOverlayCbk, &dummyData);

    // Setting to nullptr should also work
    dev->setUnderlayCbk(nullptr, nullptr);
    dev->setOverlayCbk(nullptr, nullptr);

    delete dev;
}

// Test isOk on a valid device
TEST_F(PSOutputDevTest_1332, IsOk_ValidDevice_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // For a properly constructed device, isOk should return true
    // (depending on the implementation with the minimal PDF)
    bool ok = dev->isOk();
    // We just verify the method is callable
    (void)ok;

    delete dev;
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1332, NeedClipToCropBox_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    bool result = dev->needClipToCropBox();
    (void)result;

    delete dev;
}

// Test toggling all boolean setters back and forth
TEST_F(PSOutputDevTest_1332, ToggleAllBooleanSetters_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    // Toggle each setter twice to verify stability
    for (int i = 0; i < 2; i++) {
        bool val = (i == 0);
        dev->setEmbedType1(val);
        EXPECT_EQ(dev->getEmbedType1(), val);

        dev->setEmbedTrueType(val);
        EXPECT_EQ(dev->getEmbedTrueType(), val);

        dev->setEmbedCIDPostScript(val);
        EXPECT_EQ(dev->getEmbedCIDPostScript(), val);

        dev->setEmbedCIDTrueType(val);
        EXPECT_EQ(dev->getEmbedCIDTrueType(), val);

        dev->setFontPassthrough(val);
        EXPECT_EQ(dev->getFontPassthrough(), val);

        dev->setOptimizeColorSpace(val);
        EXPECT_EQ(dev->getOptimizeColorSpace(), val);

        dev->setPassLevel1CustomColor(val);
        EXPECT_EQ(dev->getPassLevel1CustomColor(), val);

        dev->setEnableLZW(val);
        EXPECT_EQ(dev->getEnableLZW(), val);

        dev->setEnableFlate(val);
        EXPECT_EQ(dev->getEnableFlate(), val);
    }

    delete dev;
}

// Test setRasterMono doesn't crash
TEST_F(PSOutputDevTest_1332, SetRasterMono_1332) {
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
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent, 1, strlen(pdfContent), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    if (!doc->isOk()) { GTEST_SKIP(); }

    std::string outputBuffer;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(outputBuffer, doc.get(), pages);
    ASSERT_NE(dev, nullptr);
    if (!dev->isOk()) { delete dev; GTEST_SKIP(); }

    dev->setRasterMono();

    delete dev;
}
