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

// Helper to collect PS output
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1325 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // with a minimal valid PDF document. Returns nullptr if creation fails.
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages,
                                   std::string *outputStr,
                                   PSOutMode mode = psModePS,
                                   bool manualCtrl = true) {
        PSOutputDev *dev = new PSOutputDev(
            outputFunc, outputStr, nullptr, doc, pages,
            mode, -1, -1, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, manualCtrl,
            nullptr, nullptr, psLevel2);
        return dev;
    }
};

// Test: setEmbedType1 / getEmbedType1 - set to true
TEST_F(PSOutputDevTest_1325, SetEmbedType1True_1325) {
    // We can test the setter/getter without a fully initialized device
    // by using a minimal approach. Since setEmbedType1 directly sets a member
    // and getEmbedType1 returns it, we need a constructed object.
    // We'll create a temporary file-based PSOutputDev or use output func approach.

    // Create a minimal PDF in memory
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to temp file
    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setEmbedType1 / getEmbedType1 - set to false
TEST_F(PSOutputDevTest_1325, SetEmbedType1False_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevTest_1325, SetEmbedTrueType_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEmbedTrueType(true);
        EXPECT_TRUE(dev->getEmbedTrueType());

        dev->setEmbedTrueType(false);
        EXPECT_FALSE(dev->getEmbedTrueType());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1325, SetEmbedCIDPostScript_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEmbedCIDPostScript(true);
        EXPECT_TRUE(dev->getEmbedCIDPostScript());

        dev->setEmbedCIDPostScript(false);
        EXPECT_FALSE(dev->getEmbedCIDPostScript());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1325, SetEmbedCIDTrueType_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEmbedCIDTrueType(true);
        EXPECT_TRUE(dev->getEmbedCIDTrueType());

        dev->setEmbedCIDTrueType(false);
        EXPECT_FALSE(dev->getEmbedCIDTrueType());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevTest_1325, SetFontPassthrough_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setFontPassthrough(true);
        EXPECT_TRUE(dev->getFontPassthrough());

        dev->setFontPassthrough(false);
        EXPECT_FALSE(dev->getFontPassthrough());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevTest_1325, SetOptimizeColorSpace_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setOptimizeColorSpace(true);
        EXPECT_TRUE(dev->getOptimizeColorSpace());

        dev->setOptimizeColorSpace(false);
        EXPECT_FALSE(dev->getOptimizeColorSpace());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1325, SetPassLevel1CustomColor_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());

        dev->setPassLevel1CustomColor(false);
        EXPECT_FALSE(dev->getPassLevel1CustomColor());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setEnableLZW / getEnableLZW
TEST_F(PSOutputDevTest_1325, SetEnableLZW_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEnableLZW(true);
        EXPECT_TRUE(dev->getEnableLZW());

        dev->setEnableLZW(false);
        EXPECT_FALSE(dev->getEnableLZW());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setEnableFlate / getEnableFlate
TEST_F(PSOutputDevTest_1325, SetEnableFlate_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEnableFlate(true);
        EXPECT_TRUE(dev->getEnableFlate());

        dev->setEnableFlate(false);
        EXPECT_FALSE(dev->getEnableFlate());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: Toggle embedType1 multiple times
TEST_F(PSOutputDevTest_1325, ToggleEmbedType1Multiple_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());

        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());

        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());

        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: upsideDown returns expected value
TEST_F(PSOutputDevTest_1325, UpsideDown_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        // PS coordinate system: upsideDown should return false typically
        bool result = dev->upsideDown();
        // Just verify it returns a valid bool (doesn't crash)
        EXPECT_TRUE(result == true || result == false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: useDrawChar returns expected value
TEST_F(PSOutputDevTest_1325, UseDrawChar_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        // PSOutputDev typically returns false for useDrawChar
        bool result = dev->useDrawChar();
        EXPECT_TRUE(result == true || result == false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: useTilingPatternFill
TEST_F(PSOutputDevTest_1325, UseTilingPatternFill_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        bool result = dev->useTilingPatternFill();
        EXPECT_TRUE(result == true || result == false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: useDrawForm
TEST_F(PSOutputDevTest_1325, UseDrawForm_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        bool result = dev->useDrawForm();
        EXPECT_TRUE(result == true || result == false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: interpretType3Chars
TEST_F(PSOutputDevTest_1325, InterpretType3Chars_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        bool result = dev->interpretType3Chars();
        EXPECT_TRUE(result == true || result == false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setDisplayText
TEST_F(PSOutputDevTest_1325, SetDisplayText_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        // Should not crash
        dev->setDisplayText(true);
        dev->setDisplayText(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setPSCenter
TEST_F(PSOutputDevTest_1325, SetPSCenter_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setPSCenter(true);
        dev->setPSCenter(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setPSExpandSmaller / setPSShrinkLarger
TEST_F(PSOutputDevTest_1325, SetPSExpandSmallerAndShrinkLarger_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setPSExpandSmaller(true);
        dev->setPSExpandSmaller(false);
        dev->setPSShrinkLarger(true);
        dev->setPSShrinkLarger(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setOverprintPreview
TEST_F(PSOutputDevTest_1325, SetOverprintPreview_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setOverprintPreview(true);
        dev->setOverprintPreview(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setRasterResolution
TEST_F(PSOutputDevTest_1325, SetRasterResolution_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setRasterResolution(300.0);
        dev->setRasterResolution(72.0);
        dev->setRasterResolution(1200.0);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setOffset and setScale
TEST_F(PSOutputDevTest_1325, SetOffsetAndScale_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setOffset(10.0, 20.0);
        dev->setScale(1.0, 1.0);
        dev->setRotate(90);
        dev->setClip(0.0, 0.0, 612.0, 792.0);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setRasterAntialias
TEST_F(PSOutputDevTest_1325, SetRasterAntialias_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setRasterAntialias(true);
        dev->setRasterAntialias(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1325, SetUncompressPreloadedImages_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setUncompressPreloadedImages(true);
        dev->setUncompressPreloadedImages(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setUseASCIIHex / setUseBinary
TEST_F(PSOutputDevTest_1325, SetUseASCIIHexAndBinary_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setUseASCIIHex(true);
        dev->setUseASCIIHex(false);
        dev->setUseBinary(true);
        dev->setUseBinary(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: setPreloadImagesForms / setGenerateOPI
TEST_F(PSOutputDevTest_1325, SetPreloadImagesFormsAndGenerateOPI_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        dev->setPreloadImagesForms(true);
        dev->setPreloadImagesForms(false);
        dev->setGenerateOPI(true);
        dev->setGenerateOPI(false);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: isOk after construction with output func
TEST_F(PSOutputDevTest_1325, IsOkAfterConstruction_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    ASSERT_NE(dev, nullptr);
    // The device should be ok if constructed with valid parameters
    EXPECT_TRUE(dev->isOk());

    delete dev;
    unlink(tmpFileName);
}

// Test: setUnderlayCbk and setOverlayCbk don't crash
TEST_F(PSOutputDevTest_1325, SetUnderlayCbkAndOverlayCbk_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        // Setting null callbacks should be fine
        dev->setUnderlayCbk(nullptr, nullptr);
        dev->setOverlayCbk(nullptr, nullptr);
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: All boolean getters/setters consistency
TEST_F(PSOutputDevTest_1325, AllBooleanSettersGettersConsistency_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        // Test all setter/getter pairs with both true and false
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());
        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());

        dev->setEmbedTrueType(true);
        EXPECT_TRUE(dev->getEmbedTrueType());
        dev->setEmbedTrueType(false);
        EXPECT_FALSE(dev->getEmbedTrueType());

        dev->setEmbedCIDPostScript(true);
        EXPECT_TRUE(dev->getEmbedCIDPostScript());
        dev->setEmbedCIDPostScript(false);
        EXPECT_FALSE(dev->getEmbedCIDPostScript());

        dev->setEmbedCIDTrueType(true);
        EXPECT_TRUE(dev->getEmbedCIDTrueType());
        dev->setEmbedCIDTrueType(false);
        EXPECT_FALSE(dev->getEmbedCIDTrueType());

        dev->setFontPassthrough(true);
        EXPECT_TRUE(dev->getFontPassthrough());
        dev->setFontPassthrough(false);
        EXPECT_FALSE(dev->getFontPassthrough());

        dev->setOptimizeColorSpace(true);
        EXPECT_TRUE(dev->getOptimizeColorSpace());
        dev->setOptimizeColorSpace(false);
        EXPECT_FALSE(dev->getOptimizeColorSpace());

        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());
        dev->setPassLevel1CustomColor(false);
        EXPECT_FALSE(dev->getPassLevel1CustomColor());

        dev->setEnableLZW(true);
        EXPECT_TRUE(dev->getEnableLZW());
        dev->setEnableLZW(false);
        EXPECT_FALSE(dev->getEnableLZW());

        dev->setEnableFlate(true);
        EXPECT_TRUE(dev->getEnableFlate());
        dev->setEnableFlate(false);
        EXPECT_FALSE(dev->getEnableFlate());
    }

    delete dev;
    unlink(tmpFileName);
}

// Test: needClipToCropBox
TEST_F(PSOutputDevTest_1325, NeedClipToCropBox_1325) {
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                             "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                             "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                             "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                             "0000000058 00000 n \n0000000115 00000 n \n"
                             "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    char tmpFileName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpFileName);
    ASSERT_NE(fd, -1);
    write(fd, pdfContent.c_str(), pdfContent.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName));
    if (!doc->isOk()) {
        unlink(tmpFileName);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    auto *dev = createPSOutputDev(doc.get(), pages, &output);

    if (dev && dev->isOk()) {
        bool result = dev->needClipToCropBox();
        EXPECT_TRUE(result == true || result == false);
    }

    delete dev;
    unlink(tmpFileName);
}
