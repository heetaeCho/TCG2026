#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Output function for capturing PS output
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1337 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with an output function
    // Returns nullptr if creation fails (e.g., no valid doc)
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        std::string *output = new std::string();
        outputs.push_back(std::unique_ptr<std::string>(output));
        
        auto dev = std::make_unique<PSOutputDev>(
            outputToString, output, nullptr, doc, pages,
            psModePS, -1, -1, false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev && dev->isOk()) {
            return dev;
        }
        return nullptr;
    }

    std::vector<std::unique_ptr<std::string>> outputs;
};

// Helper to create a minimal valid PDF in memory for testing
class PSOutputDevWithDocTest_1337 : public PSOutputDevTest_1337 {
protected:
    void SetUp() override {
        PSOutputDevTest_1337::SetUp();
        
        // Create a minimal PDF file for testing
        tmpFile = tmpnam(nullptr);
        FILE *f = fopen(tmpFile.c_str(), "wb");
        if (f) {
            const char *minimalPDF =
                "%PDF-1.0\n"
                "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
                "xref\n0 4\n"
                "0000000000 65535 f \n"
                "0000000009 00000 n \n"
                "0000000058 00000 n \n"
                "0000000115 00000 n \n"
                "trailer<</Size 4/Root 1 0 R>>\n"
                "startxref\n210\n%%EOF\n";
            fwrite(minimalPDF, 1, strlen(minimalPDF), f);
            fclose(f);
        }
        
        doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    }

    void TearDown() override {
        doc.reset();
        if (!tmpFile.empty()) {
            remove(tmpFile.c_str());
        }
        PSOutputDevTest_1337::TearDown();
    }

    std::string tmpFile;
    std::unique_ptr<PDFDoc> doc;
};

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevWithDocTest_1337, SetEnableFlateTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
}

TEST_F(PSOutputDevWithDocTest_1337, SetEnableFlateFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevWithDocTest_1337, SetEnableLZWTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
}

TEST_F(PSOutputDevWithDocTest_1337, SetEnableLZWFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevWithDocTest_1337, SetEmbedType1True_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

TEST_F(PSOutputDevWithDocTest_1337, SetEmbedType1False_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevWithDocTest_1337, SetEmbedTrueTypeTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
}

TEST_F(PSOutputDevWithDocTest_1337, SetEmbedTrueTypeFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevWithDocTest_1337, SetEmbedCIDPostScriptTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevWithDocTest_1337, SetEmbedCIDPostScriptFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevWithDocTest_1337, SetEmbedCIDTrueTypeTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevWithDocTest_1337, SetEmbedCIDTrueTypeFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevWithDocTest_1337, SetFontPassthroughTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
}

TEST_F(PSOutputDevWithDocTest_1337, SetFontPassthroughFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevWithDocTest_1337, SetOptimizeColorSpaceTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevWithDocTest_1337, SetOptimizeColorSpaceFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevWithDocTest_1337, SetPassLevel1CustomColorTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevWithDocTest_1337, SetPassLevel1CustomColorFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test upsideDown
TEST_F(PSOutputDevWithDocTest_1337, UpsideDown_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    // Just verify it returns a boolean without crashing
    bool result = dev->upsideDown();
    (void)result;
}

// Test useDrawChar
TEST_F(PSOutputDevWithDocTest_1337, UseDrawChar_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    bool result = dev->useDrawChar();
    (void)result;
}

// Test useTilingPatternFill
TEST_F(PSOutputDevWithDocTest_1337, UseTilingPatternFill_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    bool result = dev->useTilingPatternFill();
    (void)result;
}

// Test useDrawForm
TEST_F(PSOutputDevWithDocTest_1337, UseDrawForm_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    bool result = dev->useDrawForm();
    (void)result;
}

// Test interpretType3Chars
TEST_F(PSOutputDevWithDocTest_1337, InterpretType3Chars_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    bool result = dev->interpretType3Chars();
    (void)result;
}

// Test needClipToCropBox
TEST_F(PSOutputDevWithDocTest_1337, NeedClipToCropBox_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    bool result = dev->needClipToCropBox();
    (void)result;
}

// Test isOk
TEST_F(PSOutputDevWithDocTest_1337, IsOk_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    EXPECT_TRUE(dev->isOk());
}

// Test setDisplayText
TEST_F(PSOutputDevWithDocTest_1337, SetDisplayTextTrue_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    // Should not crash
    dev->setDisplayText(true);
}

TEST_F(PSOutputDevWithDocTest_1337, SetDisplayTextFalse_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setDisplayText(false);
}

// Test setPSCenter
TEST_F(PSOutputDevWithDocTest_1337, SetPSCenter_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setPSCenter(true);
    dev->setPSCenter(false);
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevWithDocTest_1337, SetPSExpandSmaller_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevWithDocTest_1337, SetPSShrinkLarger_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
}

// Test setOverprintPreview
TEST_F(PSOutputDevWithDocTest_1337, SetOverprintPreview_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
}

// Test setRasterAntialias
TEST_F(PSOutputDevWithDocTest_1337, SetRasterAntialias_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
}

// Test setRasterResolution
TEST_F(PSOutputDevWithDocTest_1337, SetRasterResolution_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(600.0);
}

// Test setOffset
TEST_F(PSOutputDevWithDocTest_1337, SetOffset_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setOffset(0.0, 0.0);
    dev->setOffset(100.0, 200.0);
    dev->setOffset(-50.0, -50.0);
}

// Test setScale
TEST_F(PSOutputDevWithDocTest_1337, SetScale_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 2.0);
    dev->setScale(0.5, 0.5);
}

// Test setRotate
TEST_F(PSOutputDevWithDocTest_1337, SetRotate_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
}

// Test setClip
TEST_F(PSOutputDevWithDocTest_1337, SetClip_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setClip(0.0, 0.0, 612.0, 792.0);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevWithDocTest_1337, SetUncompressPreloadedImages_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevWithDocTest_1337, SetUseASCIIHex_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
}

// Test setUseBinary
TEST_F(PSOutputDevWithDocTest_1337, SetUseBinary_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setUseBinary(true);
    dev->setUseBinary(false);
}

// Test setGenerateOPI
TEST_F(PSOutputDevWithDocTest_1337, SetGenerateOPI_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevWithDocTest_1337, SetPreloadImagesForms_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
}

// Test toggle behavior: set true then false for enableFlate
TEST_F(PSOutputDevWithDocTest_1337, ToggleEnableFlate_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
}

// Test toggle behavior: set true then false for enableLZW
TEST_F(PSOutputDevWithDocTest_1337, ToggleEnableLZW_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test multiple setter/getter combinations on same instance
TEST_F(PSOutputDevWithDocTest_1337, MultipleSettersGetters_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setEmbedType1(true);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(true);
    dev->setOptimizeColorSpace(false);
    dev->setEnableLZW(true);
    dev->setEnableFlate(false);
    dev->setPassLevel1CustomColor(true);
    
    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
}

// Test useShadedFills with different type values
TEST_F(PSOutputDevWithDocTest_1337, UseShadedFills_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    // Test various shading types
    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        (void)result; // Just verify it doesn't crash
    }
}

// Test setForceRasterize
TEST_F(PSOutputDevWithDocTest_1337, SetForceRasterize_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);
}

// Test setUnderlayCbk
TEST_F(PSOutputDevWithDocTest_1337, SetUnderlayCbk_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    // Set to nullptr
    dev->setUnderlayCbk(nullptr, nullptr);
    
    // Set to a lambda-compatible function
    auto cbk = [](PSOutputDev *, void *) {};
    dev->setUnderlayCbk(cbk, nullptr);
}

// Test setOverlayCbk
TEST_F(PSOutputDevWithDocTest_1337, SetOverlayCbk_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setOverlayCbk(nullptr, nullptr);
    
    auto cbk = [](PSOutputDev *, void *) {};
    dev->setOverlayCbk(cbk, nullptr);
}

// Test setRasterMono
TEST_F(PSOutputDevWithDocTest_1337, SetRasterMono_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    // Should not crash
    dev->setRasterMono();
}

// Test boundary: setRasterResolution with zero
TEST_F(PSOutputDevWithDocTest_1337, SetRasterResolutionZero_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setRasterResolution(0.0);
}

// Test boundary: setRasterResolution with negative
TEST_F(PSOutputDevWithDocTest_1337, SetRasterResolutionNegative_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setRasterResolution(-100.0);
}

// Test boundary: setScale with zero
TEST_F(PSOutputDevWithDocTest_1337, SetScaleZero_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    dev->setScale(0.0, 0.0);
}

// Test setClip with inverted coordinates
TEST_F(PSOutputDevWithDocTest_1337, SetClipInverted_1337) {
    if (!doc || !doc->isOk()) GTEST_SKIP();
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    if (!dev) GTEST_SKIP();
    
    // URX < LLX, URY < LLY - boundary condition
    dev->setClip(612.0, 792.0, 0.0, 0.0);
}
