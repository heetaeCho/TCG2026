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

// Helper function to capture PS output
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1313 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // Returns nullptr if creation fails. Caller must delete.
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages,
                                   std::string *outputStr,
                                   PSOutMode mode = psModePS,
                                   PSLevel level = psLevel2) {
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, outputStr,
            nullptr, // psTitle
            doc,
            pages,
            mode,
            -1, -1, // paperWidth, paperHeight (default)
            false,   // noCrop
            true,    // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterize
            true,    // manualCtrl
            nullptr, // customCodeCbk
            nullptr, // customCodeCbkData
            level);
        return dev;
    }
};

// Test setRasterResolution with a normal value
TEST_F(PSOutputDevTest_1313, SetRasterResolution_NormalValue_1313) {
    // We test the method from the partial code snippet directly.
    // Since constructing a full PSOutputDev requires a PDFDoc, and we mainly
    // want to test the setter behavior, we need a valid object.
    // However, if we can't construct one, we at least verify the interface compiles.
    // For this test, we'll try with a simple PDF.

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to a temp file
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        // Test setting raster resolution to a normal value
        psOut->setRasterResolution(300.0);
        // No crash, method is callable
        SUCCEED();

        // Test setting raster resolution to a different value
        psOut->setRasterResolution(150.0);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setRasterResolution with zero
TEST_F(PSOutputDevTest_1313, SetRasterResolution_ZeroValue_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest2_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setRasterResolution(0.0);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setRasterResolution with negative value
TEST_F(PSOutputDevTest_1313, SetRasterResolution_NegativeValue_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest3_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setRasterResolution(-100.0);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setRasterResolution with very large value
TEST_F(PSOutputDevTest_1313, SetRasterResolution_VeryLargeValue_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest4_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setRasterResolution(1e10);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test boolean setters and getters
TEST_F(PSOutputDevTest_1313, SetAndGetEmbedType1_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest5_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());

        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetEmbedTrueType_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest6_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setEmbedTrueType(true);
        EXPECT_TRUE(psOut->getEmbedTrueType());

        psOut->setEmbedTrueType(false);
        EXPECT_FALSE(psOut->getEmbedTrueType());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetEmbedCIDPostScript_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest7_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setEmbedCIDPostScript(true);
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());

        psOut->setEmbedCIDPostScript(false);
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetEmbedCIDTrueType_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest8_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setEmbedCIDTrueType(true);
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());

        psOut->setEmbedCIDTrueType(false);
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetFontPassthrough_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest9_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setFontPassthrough(true);
        EXPECT_TRUE(psOut->getFontPassthrough());

        psOut->setFontPassthrough(false);
        EXPECT_FALSE(psOut->getFontPassthrough());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetOptimizeColorSpace_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest10_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setOptimizeColorSpace(true);
        EXPECT_TRUE(psOut->getOptimizeColorSpace());

        psOut->setOptimizeColorSpace(false);
        EXPECT_FALSE(psOut->getOptimizeColorSpace());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetEnableLZW_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest11_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());

        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetEnableFlate_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest12_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());

        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, SetAndGetPassLevel1CustomColor_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest13_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setPassLevel1CustomColor(true);
        EXPECT_TRUE(psOut->getPassLevel1CustomColor());

        psOut->setPassLevel1CustomColor(false);
        EXPECT_FALSE(psOut->getPassLevel1CustomColor());
    }

    delete psOut;
    unlink(tmpName);
}

// Test OutputDev interface methods
TEST_F(PSOutputDevTest_1313, UpsideDownReturnsFalse_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest14_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        // PSOutputDev typically reports upsideDown as false
        bool result = psOut->upsideDown();
        // We just check it returns a boolean without crashing
        EXPECT_FALSE(result);
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, UseDrawCharReturnsExpected_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest15_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        // PSOutputDev uses drawString, so useDrawChar should return false
        EXPECT_FALSE(psOut->useDrawChar());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, UseTilingPatternFillReturnsTrue_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest16_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->useTilingPatternFill());
    }

    delete psOut;
    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1313, UseDrawFormReturnsTrue_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest17_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->useDrawForm());
    }

    delete psOut;
    unlink(tmpName);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1313, SetDisplayText_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest18_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        // Should not crash
        psOut->setDisplayText(true);
        psOut->setDisplayText(false);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1313, SetPSCenter_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest19_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setPSCenter(true);
        psOut->setPSCenter(false);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1313, SetPSExpandAndShrink_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest20_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setPSExpandSmaller(true);
        psOut->setPSExpandSmaller(false);
        psOut->setPSShrinkLarger(true);
        psOut->setPSShrinkLarger(false);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setOffset and setScale and setRotate and setClip
TEST_F(PSOutputDevTest_1313, SetOffsetScaleRotateClip_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest21_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setOffset(10.0, 20.0);
        psOut->setScale(1.5, 2.0);
        psOut->setRotate(90);
        psOut->setClip(0.0, 0.0, 612.0, 792.0);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1313, SetOverprintPreview_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest22_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setOverprintPreview(true);
        psOut->setOverprintPreview(false);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1313, SetRasterAntialias_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest23_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setRasterAntialias(true);
        psOut->setRasterAntialias(false);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1313, SetUncompressPreloadedImages_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest24_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setUncompressPreloadedImages(true);
        psOut->setUncompressPreloadedImages(false);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test isOk with valid construction via FoFiOutputFunc
TEST_F(PSOutputDevTest_1313, IsOkWithValidDoc_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest25_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    // With a valid doc and valid output function, isOk should return true
    EXPECT_TRUE(psOut->isOk());

    delete psOut;
    unlink(tmpName);
}

// Test setting underlay and overlay callbacks
TEST_F(PSOutputDevTest_1313, SetUnderlayCbk_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest26_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        // Setting nullptr callback should not crash
        psOut->setUnderlayCbk(nullptr, nullptr);
        psOut->setOverlayCbk(nullptr, nullptr);

        // Setting a real callback
        int data = 42;
        psOut->setUnderlayCbk([](PSOutputDev *, void *) {}, &data);
        psOut->setOverlayCbk([](PSOutputDev *, void *) {}, &data);
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test multiple setters called in sequence don't crash
TEST_F(PSOutputDevTest_1313, MultipleSettersCombined_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest27_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        psOut->setEmbedType1(true);
        psOut->setEmbedTrueType(false);
        psOut->setEmbedCIDPostScript(true);
        psOut->setEmbedCIDTrueType(false);
        psOut->setFontPassthrough(true);
        psOut->setOptimizeColorSpace(false);
        psOut->setEnableLZW(true);
        psOut->setEnableFlate(false);
        psOut->setRasterResolution(600.0);
        psOut->setDisplayText(true);
        psOut->setPSCenter(true);
        psOut->setPSExpandSmaller(true);
        psOut->setPSShrinkLarger(false);
        psOut->setOverprintPreview(true);
        psOut->setRasterAntialias(true);
        psOut->setUncompressPreloadedImages(true);
        psOut->setGenerateOPI(false);
        psOut->setUseASCIIHex(true);
        psOut->setUseBinary(false);
        psOut->setPreloadImagesForms(true);
        psOut->setPassLevel1CustomColor(true);
        psOut->setOffset(5.0, 10.0);
        psOut->setScale(2.0, 2.0);
        psOut->setRotate(180);
        psOut->setClip(0, 0, 100, 100);

        // Verify getters
        EXPECT_TRUE(psOut->getEmbedType1());
        EXPECT_FALSE(psOut->getEmbedTrueType());
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());
        EXPECT_TRUE(psOut->getFontPassthrough());
        EXPECT_FALSE(psOut->getOptimizeColorSpace());
        EXPECT_TRUE(psOut->getEnableLZW());
        EXPECT_FALSE(psOut->getEnableFlate());
        EXPECT_TRUE(psOut->getPassLevel1CustomColor());
    }

    delete psOut;
    unlink(tmpName);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1313, NeedClipToCropBox_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest28_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        // Just verify it returns a bool without crashing
        bool result = psOut->needClipToCropBox();
        (void)result;
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1313, InterpretType3Chars_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest29_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        bool result = psOut->interpretType3Chars();
        // PSOutputDev should return false for interpretType3Chars
        EXPECT_FALSE(result);
    }

    delete psOut;
    unlink(tmpName);
}

// Test useShadedFills for different types
TEST_F(PSOutputDevTest_1313, UseShadedFills_1313) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpName[] = "/tmp/psoutdevtest30_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temp file";
    }
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create PDFDoc";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *psOut = createPSOutputDev(doc.get(), pages, &output);
    ASSERT_NE(psOut, nullptr);

    if (psOut->isOk()) {
        // Test with different shading types
        for (int type = 1; type <= 7; ++type) {
            bool result = psOut->useShadedFills(type);
            // Just verify it doesn't crash and returns a valid boolean
            (void)result;
        }
        SUCCEED();
    }

    delete psOut;
    unlink(tmpName);
}
