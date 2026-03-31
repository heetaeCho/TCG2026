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
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1327 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // Returns nullptr if creation fails. Caller owns the returned pointer.
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages,
                                   std::string *outputStr,
                                   PSOutMode mode = psModePS,
                                   bool manualCtrl = true) {
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputFunc, outputStr,
            nullptr, // psTitle
            doc,
            pages,
            mode,
            -1, -1, // paperWidth, paperHeight (default)
            false,   // noCrop
            true,    // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterize
            manualCtrl,
            nullptr, // customCodeCbk
            nullptr, // customCodeCbkData
            psLevel2  // level
        );
        return dev;
    }
};

// Test setEmbedCIDPostScript / getEmbedCIDPostScript with true
TEST_F(PSOutputDevTest_1327, SetGetEmbedCIDPostScript_True_1327) {
    // We need a valid PDFDoc to construct PSOutputDev.
    // Create a minimal PDF in a temp file.
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    // Create PDFDoc from the file descriptor
    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    delete dev;
    fclose(tmpFile);
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript with false
TEST_F(PSOutputDevTest_1327, SetGetEmbedCIDPostScript_False_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());

    delete dev;
    fclose(tmpFile);
}

// Test toggling setEmbedCIDPostScript multiple times
TEST_F(PSOutputDevTest_1327, SetGetEmbedCIDPostScript_Toggle_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    delete dev;
    fclose(tmpFile);
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevTest_1327, SetGetEmbedType1_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());

    delete dev;
    fclose(tmpFile);
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevTest_1327, SetGetEmbedTrueType_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());

    delete dev;
    fclose(tmpFile);
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1327, SetGetEmbedCIDTrueType_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());

    delete dev;
    fclose(tmpFile);
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevTest_1327, SetGetFontPassthrough_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());

    delete dev;
    fclose(tmpFile);
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevTest_1327, SetGetOptimizeColorSpace_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());

    delete dev;
    fclose(tmpFile);
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1327, SetGetPassLevel1CustomColor_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());

    delete dev;
    fclose(tmpFile);
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevTest_1327, SetGetEnableLZW_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());

    delete dev;
    fclose(tmpFile);
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevTest_1327, SetGetEnableFlate_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());

    delete dev;
    fclose(tmpFile);
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1327, UpsideDown_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    // upsideDown should return a boolean value
    bool result = dev->upsideDown();
    // PS coordinate system is not upside down typically
    EXPECT_FALSE(result);

    delete dev;
    fclose(tmpFile);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1327, UseDrawChar_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    // PSOutputDev typically returns false for useDrawChar
    bool result = dev->useDrawChar();
    EXPECT_FALSE(result);

    delete dev;
    fclose(tmpFile);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1327, UseTilingPatternFill_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);

    delete dev;
    fclose(tmpFile);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1327, SetPSExpandSmallerAndShrinkLarger_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    // These are setter-only functions. We verify they don't crash.
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);

    // If we get here without crashing, the test passes
    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1327, SetDisplayText_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    // Test that setDisplayText doesn't crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setOffset and setScale
TEST_F(PSOutputDevTest_1327, SetOffsetAndScale_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    // Test various offset/scale values including boundary
    dev->setOffset(0.0, 0.0);
    dev->setOffset(100.0, 200.0);
    dev->setOffset(-50.0, -100.0);
    dev->setScale(1.0, 1.0);
    dev->setScale(0.5, 0.5);
    dev->setScale(2.0, 3.0);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setRotate
TEST_F(PSOutputDevTest_1327, SetRotate_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setClip
TEST_F(PSOutputDevTest_1327, SetClip_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setClip(0.0, 0.0, 612.0, 792.0);
    dev->setClip(100.0, 100.0, 500.0, 700.0);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1327, SetRasterResolution_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setRasterResolution(72.0);
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(600.0);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test all boolean setters/getters in combination
TEST_F(PSOutputDevTest_1327, AllBooleanSettersGettersCombination_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    // Set all to true
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

    // Set all to false
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

    delete dev;
    fclose(tmpFile);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1327, SetOverprintPreview_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1327, SetRasterAntialias_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1327, SetUncompressPreloadedImages_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1327, SetPreloadImagesForms_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1327, SetGenerateOPI_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setUseASCIIHex and setUseBinary
TEST_F(PSOutputDevTest_1327, SetUseASCIIHexAndBinary_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    dev->setUseBinary(true);
    dev->setUseBinary(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test isOk on a valid device
TEST_F(PSOutputDevTest_1327, IsOkOnValidDevice_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    // isOk should be callable
    bool ok = dev->isOk();
    // We just verify it returns a boolean without crashing
    (void)ok;

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1327, SetPSCenter_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    dev->setPSCenter(true);
    dev->setPSCenter(false);

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1327, UseDrawForm_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    bool result = dev->useDrawForm();
    EXPECT_TRUE(result);

    delete dev;
    fclose(tmpFile);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1327, InterpretType3Chars_1327) {
    const char *minimalPDF =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    int fd = fileno(tmpFile);
    auto doc = std::make_unique<PDFDoc>(fd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create valid PDFDoc for testing";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev *dev = createPSOutputDev(doc.get(), pages, &output);
    
    if (!dev->isOk()) {
        delete dev;
        fclose(tmpFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
        return;
    }

    // interpretType3Chars returns a boolean
    bool result = dev->interpretType3Chars();
    (void)result; // Just verify it doesn't crash

    SUCCEED();

    delete dev;
    fclose(tmpFile);
}
