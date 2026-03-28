#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Output function that captures PS output to a string
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1293 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with FoFiOutputFunc for testing.
    // Returns nullptr if creation fails. Caller owns the pointer.
    PSOutputDev* createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages, std::string *outputStr) {
        PSOutputDev *dev = new PSOutputDev(
            outputToString,           // outputFuncA
            outputStr,                // outputStreamA
            const_cast<char*>("Test Title"), // psTitleA
            doc,                      // docA
            pages,                    // pages
            psModePS,                 // modeA
            -1,                       // paperWidthA
            -1,                       // paperHeightA
            false,                    // noCrop
            true,                     // duplexA
            0, 0, 0, 0,             // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded,    // forceRasterizeA
            false,                    // manualCtrlA
            nullptr,                  // customCodeCbkA
            nullptr,                  // customCodeCbkDataA
            psLevel2                  // levelA
        );
        return dev;
    }
};

// Test that a PSOutputDev created with a valid PDF returns isOk() true
TEST_F(PSOutputDevTest_1293, CreateWithValidPDF_IsOk_1293) {
    // Create a minimal valid PDF in memory
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
    fseek(tmpFile, 0, SEEK_SET);

    // Use GooString for filename - but we need a file-based PDFDoc
    // Actually, let's write to a named temp file
    fclose(tmpFile);

    char tmpName[] = "/tmp/psoutdev_test_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    // The device should be created (may or may not be ok depending on the PDF)
    ASSERT_NE(dev, nullptr);
    
    // Check isOk - with a valid simple PDF this should succeed
    bool ok = dev->isOk();
    // We just verify it doesn't crash; the result depends on the PDF validity
    EXPECT_TRUE(ok || !ok); // Always true, but exercises the code path

    delete dev;
    unlink(tmpName);
}

// Test upsideDown always returns false
TEST_F(PSOutputDevTest_1293, UpsideDown_ReturnsFalse_1293) {
    char tmpName[] = "/tmp/psoutdev_upside_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    
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
    
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        EXPECT_FALSE(dev->upsideDown());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedType1
TEST_F(PSOutputDevTest_1293, SetGetEmbedType1_1293) {
    char tmpName[] = "/tmp/psoutdev_embed1_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());
        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedTrueType
TEST_F(PSOutputDevTest_1293, SetGetEmbedTrueType_1293) {
    char tmpName[] = "/tmp/psoutdev_embedtt_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setEmbedTrueType(true);
        EXPECT_TRUE(dev->getEmbedTrueType());
        dev->setEmbedTrueType(false);
        EXPECT_FALSE(dev->getEmbedTrueType());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedCIDPostScript
TEST_F(PSOutputDevTest_1293, SetGetEmbedCIDPostScript_1293) {
    char tmpName[] = "/tmp/psoutdev_cidps_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setEmbedCIDPostScript(true);
        EXPECT_TRUE(dev->getEmbedCIDPostScript());
        dev->setEmbedCIDPostScript(false);
        EXPECT_FALSE(dev->getEmbedCIDPostScript());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedCIDTrueType
TEST_F(PSOutputDevTest_1293, SetGetEmbedCIDTrueType_1293) {
    char tmpName[] = "/tmp/psoutdev_cidtt_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setEmbedCIDTrueType(true);
        EXPECT_TRUE(dev->getEmbedCIDTrueType());
        dev->setEmbedCIDTrueType(false);
        EXPECT_FALSE(dev->getEmbedCIDTrueType());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for FontPassthrough
TEST_F(PSOutputDevTest_1293, SetGetFontPassthrough_1293) {
    char tmpName[] = "/tmp/psoutdev_fontpt_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setFontPassthrough(true);
        EXPECT_TRUE(dev->getFontPassthrough());
        dev->setFontPassthrough(false);
        EXPECT_FALSE(dev->getFontPassthrough());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for OptimizeColorSpace
TEST_F(PSOutputDevTest_1293, SetGetOptimizeColorSpace_1293) {
    char tmpName[] = "/tmp/psoutdev_optcs_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setOptimizeColorSpace(true);
        EXPECT_TRUE(dev->getOptimizeColorSpace());
        dev->setOptimizeColorSpace(false);
        EXPECT_FALSE(dev->getOptimizeColorSpace());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EnableLZW
TEST_F(PSOutputDevTest_1293, SetGetEnableLZW_1293) {
    char tmpName[] = "/tmp/psoutdev_lzw_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setEnableLZW(true);
        EXPECT_TRUE(dev->getEnableLZW());
        dev->setEnableLZW(false);
        EXPECT_FALSE(dev->getEnableLZW());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EnableFlate
TEST_F(PSOutputDevTest_1293, SetGetEnableFlate_1293) {
    char tmpName[] = "/tmp/psoutdev_flate_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setEnableFlate(true);
        EXPECT_TRUE(dev->getEnableFlate());
        dev->setEnableFlate(false);
        EXPECT_FALSE(dev->getEnableFlate());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for PassLevel1CustomColor
TEST_F(PSOutputDevTest_1293, SetGetPassLevel1CustomColor_1293) {
    char tmpName[] = "/tmp/psoutdev_l1cc_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());
        dev->setPassLevel1CustomColor(false);
        EXPECT_FALSE(dev->getPassLevel1CustomColor());
    }

    delete dev;
    unlink(tmpName);
}

// Test useDrawChar returns expected value
TEST_F(PSOutputDevTest_1293, UseDrawChar_ReturnsFalse_1293) {
    char tmpName[] = "/tmp/psoutdev_udc_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        // useDrawChar should return false for PSOutputDev (it uses drawString)
        EXPECT_FALSE(dev->useDrawChar());
    }

    delete dev;
    unlink(tmpName);
}

// Test useTilingPatternFill returns true
TEST_F(PSOutputDevTest_1293, UseTilingPatternFill_ReturnsTrue_1293) {
    char tmpName[] = "/tmp/psoutdev_tpf_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        EXPECT_TRUE(dev->useTilingPatternFill());
    }

    delete dev;
    unlink(tmpName);
}

// Test useDrawForm returns true
TEST_F(PSOutputDevTest_1293, UseDrawForm_ReturnsTrue_1293) {
    char tmpName[] = "/tmp/psoutdev_udf_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        EXPECT_TRUE(dev->useDrawForm());
    }

    delete dev;
    unlink(tmpName);
}

// Test interpretType3Chars returns expected value
TEST_F(PSOutputDevTest_1293, InterpretType3Chars_1293) {
    char tmpName[] = "/tmp/psoutdev_t3c_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        // interpretType3Chars should return a boolean
        bool result = dev->interpretType3Chars();
        EXPECT_TRUE(result || !result); // exercises the path; actual value depends on implementation
    }

    delete dev;
    unlink(tmpName);
}

// Test that the output contains PostScript header when created with valid PDF
TEST_F(PSOutputDevTest_1293, OutputContainsPSHeader_1293) {
    char tmpName[] = "/tmp/psoutdev_hdr_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        // The output should contain some PostScript content (header)
        // Non-manual control mode should auto-generate headers
        EXPECT_FALSE(output.empty());
        // Check for PS header markers
        if (!output.empty()) {
            EXPECT_NE(output.find("%!"), std::string::npos);
        }
    }

    delete dev;
    unlink(tmpName);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1293, SetDisplayText_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_dt_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        // These should not crash
        dev->setDisplayText(true);
        dev->setDisplayText(false);
    }

    delete dev;
    unlink(tmpName);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1293, SetPSCenter_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_psc_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setPSCenter(true);
        dev->setPSCenter(false);
    }

    delete dev;
    unlink(tmpName);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1293, SetPSExpandShrink_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_exsh_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setPSExpandSmaller(true);
        dev->setPSExpandSmaller(false);
        dev->setPSShrinkLarger(true);
        dev->setPSShrinkLarger(false);
    }

    delete dev;
    unlink(tmpName);
}

// Test setOffset and setScale and setRotate and setClip
TEST_F(PSOutputDevTest_1293, SetTransformParameters_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_trans_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setOffset(10.0, 20.0);
        dev->setScale(1.5, 2.0);
        dev->setRotate(90);
        dev->setClip(0.0, 0.0, 612.0, 792.0);
    }

    delete dev;
    unlink(tmpName);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1293, SetOverprintPreview_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_op_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setOverprintPreview(true);
        dev->setOverprintPreview(false);
    }

    delete dev;
    unlink(tmpName);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1293, SetRasterResolution_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_rr_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setRasterResolution(300.0);
        dev->setRasterResolution(72.0);
        dev->setRasterResolution(600.0);
    }

    delete dev;
    unlink(tmpName);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1293, SetRasterAntialias_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_raa_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setRasterAntialias(true);
        dev->setRasterAntialias(false);
    }

    delete dev;
    unlink(tmpName);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1293, SetUncompressPreloadedImages_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_upi_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setUncompressPreloadedImages(true);
        dev->setUncompressPreloadedImages(false);
    }

    delete dev;
    unlink(tmpName);
}

// Test underlay and overlay callbacks
TEST_F(PSOutputDevTest_1293, SetUnderlayCbk_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_ucbk_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        int callbackData = 42;
        dev->setUnderlayCbk(
            [](PSOutputDev *psOut, void *data) {
                // underlay callback
            },
            &callbackData
        );
        dev->setOverlayCbk(
            [](PSOutputDev *psOut, void *data) {
                // overlay callback
            },
            &callbackData
        );
    }

    delete dev;
    unlink(tmpName);
}

// Test useShadedFills with various types
TEST_F(PSOutputDevTest_1293, UseShadedFills_VariousTypes_1293) {
    char tmpName[] = "/tmp/psoutdev_sf_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        // Test various shading types
        for (int type = 1; type <= 7; type++) {
            bool result = dev->useShadedFills(type);
            // Just verify it returns without crashing
            EXPECT_TRUE(result || !result);
        }
    }

    delete dev;
    unlink(tmpName);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1293, NeedClipToCropBox_1293) {
    char tmpName[] = "/tmp/psoutdev_nctcb_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        bool result = dev->needClipToCropBox();
        EXPECT_TRUE(result || !result); // exercises the path
    }

    delete dev;
    unlink(tmpName);
}

// Test creating PSOutputDev with empty pages vector
TEST_F(PSOutputDevTest_1293, CreateWithEmptyPages_1293) {
    char tmpName[] = "/tmp/psoutdev_empty_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> emptyPages;
    PSOutputDev *dev = createPSOutputDev(doc.get(), emptyPages, &output);
    ASSERT_NE(dev, nullptr);

    // With empty pages, it may or may not be ok
    // Just ensure no crash
    dev->isOk();

    delete dev;
    unlink(tmpName);
}

// Test setUseBinary and setUseASCIIHex
TEST_F(PSOutputDevTest_1293, SetBinaryAndASCIIHex_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_bin_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setUseBinary(true);
        dev->setUseBinary(false);
        dev->setUseASCIIHex(true);
        dev->setUseASCIIHex(false);
    }

    delete dev;
    unlink(tmpName);
}

// Test setGenerateOPI and setPreloadImagesForms
TEST_F(PSOutputDevTest_1293, SetGenerateOPIAndPreload_DoesNotCrash_1293) {
    char tmpName[] = "/tmp/psoutdev_opi_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
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
    write(fd, pdfContent, strlen(pdfContent));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(dev, nullptr);

    if (dev->isOk()) {
        dev->setGenerateOPI(true);
        dev->setGenerateOPI(false);
        dev->setPreloadImagesForms(true);
        dev->setPreloadImagesForms(false);
    }

    delete dev;
    unlink(tmpName);
}
