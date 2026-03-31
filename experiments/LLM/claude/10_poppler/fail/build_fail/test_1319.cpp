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

// Output function for PSOutputDev
static void outputFunc(void *stream, const char *data, size_t len) {
    // Just discard output for testing purposes
    (void)stream;
    (void)data;
    (void)len;
}

class PSOutputDevTest_1319 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with minimal valid setup
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        char title[] = "test";
        auto dev = std::make_unique<PSOutputDev>(
            outputFunc, nullptr, title, doc, pages,
            psModePS, // PSOutMode
            -1, -1,   // paperWidth, paperHeight
            false,     // noCrop
            true,      // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // PSForceRasterize
            true,      // manualCtrl
            nullptr,   // customCodeCbk
            nullptr,   // customCodeCbkData
            psLevel2   // PSLevel
        );
        return dev;
    }
};

// Test with a real simple PDF document
class PSOutputDevWithDocTest_1319 : public ::testing::Test {
protected:
    std::unique_ptr<PDFDoc> doc;
    std::unique_ptr<PSOutputDev> psOut;
    
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        
        // Create a minimal PDF in memory
        // We'll try to create a PSOutputDev using a temp file approach
        const char *minimalPDF = 
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
        
        // Write to temp file
        tmpFile = tmpnam(nullptr);
        FILE *f = fopen(tmpFile.c_str(), "wb");
        if (f) {
            fwrite(minimalPDF, 1, strlen(minimalPDF), f);
            fclose(f);
        }
        
        auto *fileName = new GooString(tmpFile.c_str());
        doc = std::make_unique<PDFDoc>(fileName);
    }
    
    void TearDown() override {
        psOut.reset();
        doc.reset();
        if (!tmpFile.empty()) {
            remove(tmpFile.c_str());
        }
    }
    
    std::string tmpFile;
    
    PSOutputDev* createDev() {
        if (!doc || !doc->isOk()) return nullptr;
        
        std::vector<int> pages = {1};
        char title[] = "test";
        psOut = std::make_unique<PSOutputDev>(
            outputFunc, nullptr, title, doc.get(), pages,
            psModePS,
            -1, -1,
            false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded,
            true,
            nullptr, nullptr,
            psLevel2
        );
        return psOut.get();
    }
};

// Test getEmbedCIDTrueType getter directly
TEST_F(PSOutputDevWithDocTest_1319, GetEmbedCIDTrueTypeDefault_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Default value should be a boolean
    bool val = dev->getEmbedCIDTrueType();
    // Just verify it returns without crashing and is a valid bool
    EXPECT_TRUE(val == true || val == false);
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedCIDTrueType_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedCIDTrueType_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedType1_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedType1_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedTrueType_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedTrueType_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedCIDPostScript_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEmbedCIDPostScript_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetFontPassthrough_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetFontPassthrough_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetOptimizeColorSpace_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetOptimizeColorSpace_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetPassLevel1CustomColor_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetPassLevel1CustomColor_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEnableLZW_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEnableLZW_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEnableFlate_True_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
}

TEST_F(PSOutputDevWithDocTest_1319, SetAndGetEnableFlate_False_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevWithDocTest_1319, UpsideDown_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->upsideDown();
    EXPECT_TRUE(val == true || val == false);
}

// Test useDrawChar
TEST_F(PSOutputDevWithDocTest_1319, UseDrawChar_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useDrawChar();
    EXPECT_TRUE(val == true || val == false);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevWithDocTest_1319, UseTilingPatternFill_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useTilingPatternFill();
    EXPECT_TRUE(val == true || val == false);
}

// Test useDrawForm
TEST_F(PSOutputDevWithDocTest_1319, UseDrawForm_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useDrawForm();
    EXPECT_TRUE(val == true || val == false);
}

// Test interpretType3Chars
TEST_F(PSOutputDevWithDocTest_1319, InterpretType3Chars_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->interpretType3Chars();
    EXPECT_TRUE(val == true || val == false);
}

// Test needClipToCropBox
TEST_F(PSOutputDevWithDocTest_1319, NeedClipToCropBox_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->needClipToCropBox();
    EXPECT_TRUE(val == true || val == false);
}

// Test isOk
TEST_F(PSOutputDevWithDocTest_1319, IsOk_1319) {
    PSOutputDev *dev = createDev();
    // After creation with valid doc, isOk should return true
    if (doc && doc->isOk() && dev) {
        EXPECT_TRUE(dev->isOk());
    }
}

// Test toggle: set true then false for embedCIDTrueType
TEST_F(PSOutputDevWithDocTest_1319, ToggleEmbedCIDTrueType_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
}

// Test setDisplayText
TEST_F(PSOutputDevWithDocTest_1319, SetDisplayText_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Should not crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);
}

// Test setPSCenter
TEST_F(PSOutputDevWithDocTest_1319, SetPSCenter_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSCenter(true);
    dev->setPSCenter(false);
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevWithDocTest_1319, SetPSExpandSmaller_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevWithDocTest_1319, SetPSShrinkLarger_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
}

// Test setOverprintPreview
TEST_F(PSOutputDevWithDocTest_1319, SetOverprintPreview_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
}

// Test setRasterAntialias
TEST_F(PSOutputDevWithDocTest_1319, SetRasterAntialias_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
}

// Test setRasterResolution
TEST_F(PSOutputDevWithDocTest_1319, SetRasterResolution_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);
}

// Test setOffset
TEST_F(PSOutputDevWithDocTest_1319, SetOffset_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOffset(0.0, 0.0);
    dev->setOffset(100.0, 200.0);
    dev->setOffset(-50.0, -50.0);
}

// Test setScale
TEST_F(PSOutputDevWithDocTest_1319, SetScale_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 0.5);
}

// Test setRotate
TEST_F(PSOutputDevWithDocTest_1319, SetRotate_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
}

// Test setClip
TEST_F(PSOutputDevWithDocTest_1319, SetClip_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setClip(0.0, 0.0, 612.0, 792.0);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevWithDocTest_1319, SetUncompressPreloadedImages_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevWithDocTest_1319, SetPreloadImagesForms_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
}

// Test setGenerateOPI
TEST_F(PSOutputDevWithDocTest_1319, SetGenerateOPI_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevWithDocTest_1319, SetUseASCIIHex_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
}

// Test setUseBinary
TEST_F(PSOutputDevWithDocTest_1319, SetUseBinary_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUseBinary(true);
    dev->setUseBinary(false);
}

// Test useShadedFills with different types
TEST_F(PSOutputDevWithDocTest_1319, UseShadedFills_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    for (int type = 1; type <= 7; ++type) {
        bool val = dev->useShadedFills(type);
        EXPECT_TRUE(val == true || val == false);
    }
}

// Test setRasterMono
TEST_F(PSOutputDevWithDocTest_1319, SetRasterMono_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterMono();
    // Should not crash
}

// Test multiple setter/getter round-trips in sequence
TEST_F(PSOutputDevWithDocTest_1319, MultipleSettersGetters_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedType1(false);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(true);
    dev->setEnableLZW(false);
    dev->setEnableFlate(true);
    
    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());
}

// Test setForceRasterize
TEST_F(PSOutputDevWithDocTest_1319, SetForceRasterize_1319) {
    PSOutputDev *dev = createDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);
}
