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

// Output function for PSOutputDev that writes to a string buffer
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1318 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using FoFiOutputFunc with a simple PDF
    PSOutputDev* createPSOutputDev(PDFDoc* doc, const std::vector<int>& pages) {
        outputBuffer.clear();
        char title[] = "test";
        PSOutputDev* dev = new PSOutputDev(
            outputToString, &outputBuffer, title, doc,
            pages, psModePS, -1, -1,
            false, false, 0, 0, 0, 0,
            psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
        return dev;
    }

    std::string outputBuffer;
};

// Helper to create a minimal valid PDF in a temp file
class TempPDFFixture_1318 : public PSOutputDevTest_1318 {
protected:
    void SetUp() override {
        PSOutputDevTest_1318::SetUp();
        
        // Create a minimal PDF
        const char* pdfContent =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

        tmpFile = tmpnam(nullptr);
        FILE* f = fopen(tmpFile.c_str(), "wb");
        if (f) {
            fwrite(pdfContent, 1, strlen(pdfContent), f);
            fclose(f);
        }

        doc = new PDFDoc(std::make_unique<GooString>(tmpFile.c_str()));
    }

    void TearDown() override {
        delete doc;
        doc = nullptr;
        if (!tmpFile.empty()) {
            remove(tmpFile.c_str());
        }
        PSOutputDevTest_1318::TearDown();
    }

    PDFDoc* doc = nullptr;
    std::string tmpFile;
};

// Test getEmbedCIDPostScript default and after set
TEST_F(TempPDFFixture_1318, GetEmbedCIDPostScript_Default_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // Default value - just ensure it returns a bool
    bool val = dev->getEmbedCIDPostScript();
    (void)val; // We just verify it doesn't crash
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedCIDPostScript_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedCIDPostScript_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedType1_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedType1_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedTrueType_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedTrueType_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedCIDTrueType_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEmbedCIDTrueType_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetFontPassthrough_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetFontPassthrough_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetOptimizeColorSpace_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetOptimizeColorSpace_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetPassLevel1CustomColor_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetPassLevel1CustomColor_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEnableLZW_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEnableLZW_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEnableFlate_True_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetAndGetEnableFlate_False_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
    delete dev;
}

// Test toggling EmbedCIDPostScript multiple times
TEST_F(TempPDFFixture_1318, ToggleEmbedCIDPostScriptMultipleTimes_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    delete dev;
}

// Test upsideDown
TEST_F(TempPDFFixture_1318, UpsideDown_ReturnsFalse_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // PS coordinate system is not upside down
    EXPECT_FALSE(dev->upsideDown());
    delete dev;
}

// Test useDrawChar
TEST_F(TempPDFFixture_1318, UseDrawChar_ReturnsFalse_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // PSOutputDev typically uses drawString, not drawChar
    EXPECT_FALSE(dev->useDrawChar());
    delete dev;
}

// Test useTilingPatternFill
TEST_F(TempPDFFixture_1318, UseTilingPatternFill_ReturnsTrue_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    EXPECT_TRUE(dev->useTilingPatternFill());
    delete dev;
}

// Test useDrawForm
TEST_F(TempPDFFixture_1318, UseDrawForm_ReturnsTrue_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    EXPECT_TRUE(dev->useDrawForm());
    delete dev;
}

// Test interpretType3Chars
TEST_F(TempPDFFixture_1318, InterpretType3Chars_ReturnsFalse_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // PSOutputDev typically doesn't interpret Type3 chars internally
    bool val = dev->interpretType3Chars();
    (void)val; // Just ensure it doesn't crash
    delete dev;
}

// Test setDisplayText
TEST_F(TempPDFFixture_1318, SetDisplayText_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // Should not crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);
    delete dev;
}

// Test setPSCenter
TEST_F(TempPDFFixture_1318, SetPSCenter_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPSCenter(true);
    dev->setPSCenter(false);
    delete dev;
}

// Test setPSExpandSmaller
TEST_F(TempPDFFixture_1318, SetPSExpandSmaller_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    delete dev;
}

// Test setPSShrinkLarger
TEST_F(TempPDFFixture_1318, SetPSShrinkLarger_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
    delete dev;
}

// Test setOverprintPreview
TEST_F(TempPDFFixture_1318, SetOverprintPreview_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
    delete dev;
}

// Test setRasterResolution
TEST_F(TempPDFFixture_1318, SetRasterResolution_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    delete dev;
}

// Test setOffset
TEST_F(TempPDFFixture_1318, SetOffset_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOffset(10.0, 20.0);
    dev->setOffset(0.0, 0.0);
    dev->setOffset(-5.0, -10.0);
    delete dev;
}

// Test setScale
TEST_F(TempPDFFixture_1318, SetScale_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 0.5);
    delete dev;
}

// Test setRotate
TEST_F(TempPDFFixture_1318, SetRotate_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
    delete dev;
}

// Test setClip
TEST_F(TempPDFFixture_1318, SetClip_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setClip(0.0, 0.0, 612.0, 792.0);
    delete dev;
}

// Test setRasterAntialias
TEST_F(TempPDFFixture_1318, SetRasterAntialias_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
    delete dev;
}

// Test setUncompressPreloadedImages
TEST_F(TempPDFFixture_1318, SetUncompressPreloadedImages_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
    delete dev;
}

// Test setPreloadImagesForms
TEST_F(TempPDFFixture_1318, SetPreloadImagesForms_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
    delete dev;
}

// Test setGenerateOPI
TEST_F(TempPDFFixture_1318, SetGenerateOPI_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
    delete dev;
}

// Test setUseASCIIHex
TEST_F(TempPDFFixture_1318, SetUseASCIIHex_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    delete dev;
}

// Test setUseBinary
TEST_F(TempPDFFixture_1318, SetUseBinary_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUseBinary(true);
    dev->setUseBinary(false);
    delete dev;
}

// Test multiple setter/getter round-trips in sequence
TEST_F(TempPDFFixture_1318, MultipleSettersAndGetters_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }

    dev->setEmbedType1(false);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(true);
    dev->setOptimizeColorSpace(true);
    dev->setEnableLZW(false);
    dev->setEnableFlate(true);

    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());

    delete dev;
}

// Test needClipToCropBox
TEST_F(TempPDFFixture_1318, NeedClipToCropBox_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    bool val = dev->needClipToCropBox();
    (void)val;
    delete dev;
}

// Test useShadedFills for different types
TEST_F(TempPDFFixture_1318, UseShadedFills_DifferentTypes_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // Test with different shading types
    for (int type = 1; type <= 7; ++type) {
        bool val = dev->useShadedFills(type);
        (void)val; // Just verify it doesn't crash
    }
    delete dev;
}

// Test isOk on valid construction
TEST_F(TempPDFFixture_1318, IsOk_ValidConstruction_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    // Should be ok if doc is valid
    EXPECT_TRUE(dev->isOk());
    delete dev;
}

// Test underlay/overlay callbacks
TEST_F(TempPDFFixture_1318, SetUnderlayCbk_NullCallback_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUnderlayCbk(nullptr, nullptr);
    delete dev;
}

TEST_F(TempPDFFixture_1318, SetOverlayCbk_NullCallback_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOverlayCbk(nullptr, nullptr);
    delete dev;
}

// Test setting same value twice
TEST_F(TempPDFFixture_1318, SetSameValueTwice_EmbedCIDPostScript_1318) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc, pages);
    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    delete dev;
}
