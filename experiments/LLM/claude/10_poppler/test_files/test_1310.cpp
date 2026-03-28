#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Output function for PSOutputDev that writes to a string buffer
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1310 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        outputBuffer.clear();
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // This may fail if no valid PDFDoc is provided, so we check isOk()
    PSOutputDev* createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        return new PSOutputDev(
            (FoFiOutputFunc)outputToString, &outputBuffer,
            nullptr, // psTitle
            doc,
            pages,
            psModePS, // mode
            0, 0,     // paperWidth, paperHeight
            false,    // noCrop
            true,     // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterize
            true,     // manualCtrl
            nullptr,  // customCodeCbk
            nullptr,  // customCodeCbkData
            psLevel2  // level
        );
    }

    std::string outputBuffer;
};

// Test creating a PSOutputDev with a null doc - should not crash, isOk should be false
TEST_F(PSOutputDevTest_1310, NullDocCreation_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    // With null doc, the device should not be ok
    EXPECT_FALSE(dev->isOk());
    delete dev;
}

// Test setOverprintPreview and verify it doesn't crash
TEST_F(PSOutputDevTest_1310, SetOverprintPreviewTrue_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    // Even if not ok, setter should not crash
    dev->setOverprintPreview(true);
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetOverprintPreviewFalse_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setOverprintPreview(false);
    delete dev;
}

// Test setter/getter pairs for embed flags
TEST_F(PSOutputDevTest_1310, SetGetEmbedType1_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetEmbedTrueType_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetEmbedCIDPostScript_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetEmbedCIDTrueType_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetFontPassthrough_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetOptimizeColorSpace_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetPassLevel1CustomColor_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetEnableLZW_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetGetEnableFlate_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
    delete dev;
}

// Test OutputDev interface methods
TEST_F(PSOutputDevTest_1310, UpsideDown_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    // upsideDown() should return a consistent boolean value
    bool result = dev->upsideDown();
    (void)result; // Just verify it doesn't crash
    delete dev;
}

TEST_F(PSOutputDevTest_1310, UseDrawChar_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    bool result = dev->useDrawChar();
    (void)result;
    delete dev;
}

TEST_F(PSOutputDevTest_1310, UseTilingPatternFill_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    bool result = dev->useTilingPatternFill();
    (void)result;
    delete dev;
}

TEST_F(PSOutputDevTest_1310, UseDrawForm_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    bool result = dev->useDrawForm();
    (void)result;
    delete dev;
}

// Test setDisplayText doesn't crash
TEST_F(PSOutputDevTest_1310, SetDisplayText_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setDisplayText(true);
    dev->setDisplayText(false);
    delete dev;
}

// Test setPSCenter doesn't crash
TEST_F(PSOutputDevTest_1310, SetPSCenter_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setPSCenter(true);
    dev->setPSCenter(false);
    delete dev;
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1310, SetPSExpandSmaller_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetPSShrinkLarger_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
    delete dev;
}

// Test setOffset, setScale, setRotate, setClip
TEST_F(PSOutputDevTest_1310, SetOffset_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setOffset(10.0, 20.0);
    dev->setOffset(0.0, 0.0);
    dev->setOffset(-5.0, -10.0);
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetScale_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 0.5);
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetRotate_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
    delete dev;
}

TEST_F(PSOutputDevTest_1310, SetClip_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setClip(0.0, 0.0, 612.0, 792.0);
    delete dev;
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1310, SetRasterResolution_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);
    delete dev;
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1310, SetRasterAntialias_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
    delete dev;
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1310, SetUncompressPreloadedImages_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
    delete dev;
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1310, SetPreloadImagesForms_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
    delete dev;
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1310, SetGenerateOPI_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
    delete dev;
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1310, SetUseASCIIHex_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    delete dev;
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1310, SetUseBinary_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setUseBinary(true);
    dev->setUseBinary(false);
    delete dev;
}

// Test with empty pages vector
TEST_F(PSOutputDevTest_1310, EmptyPagesVector_1310) {
    std::vector<int> pages;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    // With null doc and empty pages, should not be ok
    EXPECT_FALSE(dev->isOk());
    delete dev;
}

// Test setting underlay callback
TEST_F(PSOutputDevTest_1310, SetUnderlayCbk_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setUnderlayCbk(nullptr, nullptr);
    delete dev;
}

// Test setting overlay callback
TEST_F(PSOutputDevTest_1310, SetOverlayCbk_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setOverlayCbk(nullptr, nullptr);
    delete dev;
}

// Test multiple setter toggles in sequence
TEST_F(PSOutputDevTest_1310, MultipleSetterToggles_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );

    // Toggle multiple settings
    dev->setEmbedType1(true);
    dev->setEmbedTrueType(true);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_TRUE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedType1(false);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());

    delete dev;
}

// Test setForceRasterize with different values
TEST_F(PSOutputDevTest_1310, SetForceRasterize_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);
    delete dev;
}

// Test with different PS levels
TEST_F(PSOutputDevTest_1310, DifferentPSLevels_1310) {
    std::vector<int> pages = {1};
    
    // Level 1
    PSOutputDev *dev1 = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel1
    );
    EXPECT_FALSE(dev1->isOk());
    delete dev1;

    outputBuffer.clear();

    // Level 3
    PSOutputDev *dev3 = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel3
    );
    EXPECT_FALSE(dev3->isOk());
    delete dev3;
}

// Test with different PS modes
TEST_F(PSOutputDevTest_1310, EPSMode_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModeEPS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    // With null doc should not be ok
    EXPECT_FALSE(dev->isOk());
    delete dev;
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1310, SetRasterMono_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    dev->setRasterMono();
    delete dev;
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1310, NeedClipToCropBox_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    bool result = dev->needClipToCropBox();
    (void)result;
    delete dev;
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1310, InterpretType3Chars_1310) {
    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &outputBuffer,
        nullptr, nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2
    );
    bool result = dev->interpretType3Chars();
    (void)result;
    delete dev;
}
