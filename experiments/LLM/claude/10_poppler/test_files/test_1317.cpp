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

class PSOutputDevTest_1317 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal PSOutputDev via FoFiOutputFunc
    // Returns nullptr if creation fails
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        outputBuffer.clear();
        PSOutputDev *dev = new PSOutputDev(
            outputFunc, &outputBuffer,
            nullptr, // psTitleA
            doc,
            pages,
            psModePS, // modeA
            0, 0,     // paperWidth, paperHeight
            false,    // noCrop
            false,    // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterize
            true,     // manualCtrl
            nullptr,  // customCodeCbk
            nullptr,  // customCodeCbkData
            psLevel2  // level
        );
        return dev;
    }

    std::string outputBuffer;
};

// Test getEmbedTrueType default and setter
TEST_F(PSOutputDevTest_1317, GetEmbedTrueTypeDefault_1317) {
    // We need a valid PDFDoc to create PSOutputDev.
    // Create a minimal PDF in a temp file.
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

    // Create PDFDoc from the file descriptor
    int fd = fileno(tmpFile);
    // We need to use a file-based approach
    // Let's write to a named temp file instead
    fclose(tmpFile);

    char tmpName[] = "/tmp/psoutdev_test_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Test getEmbedTrueType - check the default value
    bool defaultVal = dev->getEmbedTrueType();
    // The default is expected to be true based on the field declaration
    EXPECT_TRUE(defaultVal);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevTest_1317, SetAndGetEmbedTrueType_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test2_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevTest_1317, SetAndGetEmbedType1_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test3_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1317, SetAndGetEmbedCIDPostScript_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test4_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1317, SetAndGetEmbedCIDTrueType_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test5_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevTest_1317, SetAndGetFontPassthrough_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test6_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1317, SetAndGetOptimizeColorSpace_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test7_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1317, SetAndGetPassLevel1CustomColor_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test8_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setEnableLZW and getEnableLZW
TEST_F(PSOutputDevTest_1317, SetAndGetEnableLZW_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test9_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevTest_1317, SetAndGetEnableFlate_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test10_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test isOk after valid construction
TEST_F(PSOutputDevTest_1317, IsOkAfterValidConstruction_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test11_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    EXPECT_TRUE(dev->isOk());

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1317, UpsideDown_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test12_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // PSOutputDev typically returns false for upsideDown
    bool result = dev->upsideDown();
    // Just verify it returns a bool without crashing
    (void)result;

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test useDrawChar returns expected value
TEST_F(PSOutputDevTest_1317, UseDrawChar_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test13_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // PSOutputDev typically returns false for useDrawChar (uses drawString)
    bool result = dev->useDrawChar();
    EXPECT_FALSE(result);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1317, SetDisplayText_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test14_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1317, SetPSCenter_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test15_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setPSCenter(true);
    dev->setPSCenter(false);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1317, SetPSExpandSmallerAndShrinkLarger_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test16_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setOffset and setScale and setRotate and setClip don't crash
TEST_F(PSOutputDevTest_1317, SetOffsetScaleRotateClip_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test17_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    dev->setOffset(10.0, 20.0);
    dev->setScale(1.5, 2.0);
    dev->setRotate(90);
    dev->setClip(0.0, 0.0, 612.0, 792.0);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1317, SetRasterResolution_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test18_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test toggle of multiple boolean setters and getters in sequence
TEST_F(PSOutputDevTest_1317, MultipleBooleanToggle_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test19_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

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

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1317, UseTilingPatternFill_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test20_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // PSOutputDev typically supports tiling pattern fill
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1317, InterpretType3Chars_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test21_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    bool result = dev->interpretType3Chars();
    // Just verify it doesn't crash and returns a boolean
    (void)result;

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setOverprintPreview and setRasterAntialias
TEST_F(PSOutputDevTest_1317, SetOverprintPreviewAndRasterAntialias_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test22_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setUseASCIIHex and setUseBinary
TEST_F(PSOutputDevTest_1317, SetUseASCIIHexAndUseBinary_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test23_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    dev->setUseBinary(true);
    dev->setUseBinary(false);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setGenerateOPI and setPreloadImagesForms
TEST_F(PSOutputDevTest_1317, SetGenerateOPIAndPreloadImagesForms_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test24_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1317, SetUncompressPreloadedImages_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test25_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    // Should not crash
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1317, UseDrawForm_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test26_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    bool result = dev->useDrawForm();
    EXPECT_TRUE(result);

    delete dev;
    delete doc;
    unlink(tmpName);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1317, NeedClipToCropBox_1317) {
    const char *pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdev_test27_XXXXXX";
    int tfd = mkstemp(tmpName);
    ASSERT_NE(tfd, -1);
    write(tfd, pdfContent, strlen(pdfContent));
    close(tfd);

    auto *doc = new PDFDoc(std::make_unique<GooString>(tmpName));
    ASSERT_TRUE(doc->isOk());

    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc, pages);
    ASSERT_NE(dev, nullptr);

    bool result = dev->needClipToCropBox();
    // Just verify it returns without crashing
    (void)result;

    delete dev;
    delete doc;
    unlink(tmpName);
}
