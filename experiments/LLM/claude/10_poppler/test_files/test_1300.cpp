#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

// Output function for capturing PS output
void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1300 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with FoFiOutputFunc if possible
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        outputBuffer.clear();
        char title[] = "test";
        auto dev = std::make_unique<PSOutputDev>(
            (FoFiOutputFunc)outputToString, &outputBuffer, title, doc,
            pages, psModePS, 612, 792, false, false,
            0, 0, 612, 792, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        if (dev && dev->isOk()) {
            return dev;
        }
        return nullptr;
    }

    std::string outputBuffer;
};

// Test with a minimal valid PDF if possible. Since we need a PDFDoc,
// we create a minimal PDF file for testing.
class PSOutputDevWithDocTest_1300 : public PSOutputDevTest_1300 {
protected:
    void SetUp() override {
        PSOutputDevTest_1300::SetUp();

        // Create a minimal PDF in a temp file
        tmpFileName = "/tmp/test_psoutputdev_1300.pdf";
        std::ofstream ofs(tmpFileName, std::ios::binary);
        // Minimal valid PDF
        std::string minPdf =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\nstartxref\n215\n%%EOF\n";
        ofs.write(minPdf.c_str(), minPdf.size());
        ofs.close();

        auto *gooStr = new GooString(tmpFileName);
        doc = std::make_unique<PDFDoc>(gooStr);
    }

    void TearDown() override {
        psDev.reset();
        doc.reset();
        std::remove(tmpFileName.c_str());
        PSOutputDevTest_1300::TearDown();
    }

    bool createDevice() {
        if (!doc || !doc->isOk()) return false;
        std::vector<int> pages = {1};
        outputBuffer.clear();
        char title[] = "test";
        psDev = std::make_unique<PSOutputDev>(
            (FoFiOutputFunc)outputToString, &outputBuffer, title, doc.get(),
            pages, psModePS, 612, 792, false, false,
            0, 0, 612, 792, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        return psDev && psDev->isOk();
    }

    const char *tmpFileName;
    std::unique_ptr<PDFDoc> doc;
    std::unique_ptr<PSOutputDev> psDev;
};

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedType1_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedType1(true);
    EXPECT_TRUE(psDev->getEmbedType1());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedType1_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedType1(false);
    EXPECT_FALSE(psDev->getEmbedType1());
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedTrueType_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedTrueType(true);
    EXPECT_TRUE(psDev->getEmbedTrueType());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedTrueType_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedTrueType(false);
    EXPECT_FALSE(psDev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedCIDPostScript_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psDev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedCIDPostScript_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psDev->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedCIDTrueType_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(psDev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetEmbedCIDTrueType_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(psDev->getEmbedCIDTrueType());
}

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevWithDocTest_1300, SetGetFontPassthrough_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setFontPassthrough(true);
    EXPECT_TRUE(psDev->getFontPassthrough());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetFontPassthrough_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setFontPassthrough(false);
    EXPECT_FALSE(psDev->getFontPassthrough());
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevWithDocTest_1300, SetGetOptimizeColorSpace_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOptimizeColorSpace(true);
    EXPECT_TRUE(psDev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetOptimizeColorSpace_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOptimizeColorSpace(false);
    EXPECT_FALSE(psDev->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevWithDocTest_1300, SetGetPassLevel1CustomColor_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(psDev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetPassLevel1CustomColor_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(psDev->getPassLevel1CustomColor());
}

// Test setEnableLZW and getEnableLZW
TEST_F(PSOutputDevWithDocTest_1300, SetGetEnableLZW_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEnableLZW(true);
    EXPECT_TRUE(psDev->getEnableLZW());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetEnableLZW_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEnableLZW(false);
    EXPECT_FALSE(psDev->getEnableLZW());
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevWithDocTest_1300, SetGetEnableFlate_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEnableFlate(true);
    EXPECT_TRUE(psDev->getEnableFlate());
}

TEST_F(PSOutputDevWithDocTest_1300, SetGetEnableFlate_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEnableFlate(false);
    EXPECT_FALSE(psDev->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevWithDocTest_1300, UpsideDown_1300) {
    if (!createDevice()) GTEST_SKIP();
    // OutputDev method - just verify it returns a bool without crashing
    bool result = psDev->upsideDown();
    (void)result; // Just ensure it doesn't crash
    SUCCEED();
}

// Test useDrawChar
TEST_F(PSOutputDevWithDocTest_1300, UseDrawChar_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->useDrawChar();
    (void)result;
    SUCCEED();
}

// Test useTilingPatternFill
TEST_F(PSOutputDevWithDocTest_1300, UseTilingPatternFill_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->useTilingPatternFill();
    (void)result;
    SUCCEED();
}

// Test useDrawForm
TEST_F(PSOutputDevWithDocTest_1300, UseDrawForm_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->useDrawForm();
    (void)result;
    SUCCEED();
}

// Test interpretType3Chars
TEST_F(PSOutputDevWithDocTest_1300, InterpretType3Chars_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->interpretType3Chars();
    (void)result;
    SUCCEED();
}

// Test needClipToCropBox
TEST_F(PSOutputDevWithDocTest_1300, NeedClipToCropBox_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->needClipToCropBox();
    (void)result;
    SUCCEED();
}

// Test isOk
TEST_F(PSOutputDevWithDocTest_1300, IsOk_1300) {
    if (!createDevice()) GTEST_SKIP();
    EXPECT_TRUE(psDev->isOk());
}

// Test setOffset - as specified in the partial code, it sets tx0 and ty0
// We can't directly observe the effect on private members, but we verify no crash
TEST_F(PSOutputDevWithDocTest_1300, SetOffset_Normal_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOffset(10.0, 20.0);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetOffset_Zero_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOffset(0.0, 0.0);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetOffset_Negative_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOffset(-100.5, -200.3);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetOffset_LargeValues_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOffset(1e10, 1e10);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetOffset_VerySmallValues_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOffset(1e-15, 1e-15);
    SUCCEED();
}

// Test setScale
TEST_F(PSOutputDevWithDocTest_1300, SetScale_Normal_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setScale(1.0, 1.0);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetScale_Zoom_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setScale(2.0, 2.0);
    SUCCEED();
}

// Test setRotate
TEST_F(PSOutputDevWithDocTest_1300, SetRotate_Zero_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRotate(0);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetRotate_90_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRotate(90);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetRotate_180_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRotate(180);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetRotate_270_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRotate(270);
    SUCCEED();
}

// Test setClip
TEST_F(PSOutputDevWithDocTest_1300, SetClip_Normal_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setClip(0.0, 0.0, 612.0, 792.0);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetClip_SmallArea_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setClip(100.0, 100.0, 200.0, 200.0);
    SUCCEED();
}

// Test setDisplayText
TEST_F(PSOutputDevWithDocTest_1300, SetDisplayText_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setDisplayText(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetDisplayText_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setDisplayText(false);
    SUCCEED();
}

// Test setPSCenter
TEST_F(PSOutputDevWithDocTest_1300, SetPSCenter_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPSCenter(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetPSCenter_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPSCenter(false);
    SUCCEED();
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevWithDocTest_1300, SetPSExpandSmaller_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPSExpandSmaller(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetPSExpandSmaller_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPSExpandSmaller(false);
    SUCCEED();
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevWithDocTest_1300, SetPSShrinkLarger_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPSShrinkLarger(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetPSShrinkLarger_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPSShrinkLarger(false);
    SUCCEED();
}

// Test setOverprintPreview
TEST_F(PSOutputDevWithDocTest_1300, SetOverprintPreview_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOverprintPreview(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetOverprintPreview_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOverprintPreview(false);
    SUCCEED();
}

// Test setRasterAntialias
TEST_F(PSOutputDevWithDocTest_1300, SetRasterAntialias_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRasterAntialias(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetRasterAntialias_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRasterAntialias(false);
    SUCCEED();
}

// Test setRasterResolution
TEST_F(PSOutputDevWithDocTest_1300, SetRasterResolution_Normal_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRasterResolution(300.0);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetRasterResolution_High_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRasterResolution(1200.0);
    SUCCEED();
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevWithDocTest_1300, SetUncompressPreloadedImages_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setUncompressPreloadedImages(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetUncompressPreloadedImages_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setUncompressPreloadedImages(false);
    SUCCEED();
}

// Test toggle - set true then false
TEST_F(PSOutputDevWithDocTest_1300, ToggleEmbedType1_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedType1(true);
    EXPECT_TRUE(psDev->getEmbedType1());
    psDev->setEmbedType1(false);
    EXPECT_FALSE(psDev->getEmbedType1());
    psDev->setEmbedType1(true);
    EXPECT_TRUE(psDev->getEmbedType1());
}

// Test multiple setters don't interfere
TEST_F(PSOutputDevWithDocTest_1300, MultipleSettersIndependent_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setEmbedType1(true);
    psDev->setEmbedTrueType(false);
    psDev->setEmbedCIDPostScript(true);
    psDev->setEmbedCIDTrueType(false);
    psDev->setFontPassthrough(true);
    psDev->setEnableLZW(false);
    psDev->setEnableFlate(true);

    EXPECT_TRUE(psDev->getEmbedType1());
    EXPECT_FALSE(psDev->getEmbedTrueType());
    EXPECT_TRUE(psDev->getEmbedCIDPostScript());
    EXPECT_FALSE(psDev->getEmbedCIDTrueType());
    EXPECT_TRUE(psDev->getFontPassthrough());
    EXPECT_FALSE(psDev->getEnableLZW());
    EXPECT_TRUE(psDev->getEnableFlate());
}

// Test setOverlayCbk
TEST_F(PSOutputDevWithDocTest_1300, SetOverlayCbk_Null_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setOverlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test setUnderlayCbk
TEST_F(PSOutputDevWithDocTest_1300, SetUnderlayCbk_Null_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setUnderlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test setRasterMono
TEST_F(PSOutputDevWithDocTest_1300, SetRasterMono_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setRasterMono();
    SUCCEED();
}

// Test useShadedFills with different types
TEST_F(PSOutputDevWithDocTest_1300, UseShadedFills_Type1_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->useShadedFills(1);
    (void)result;
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, UseShadedFills_Type2_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->useShadedFills(2);
    (void)result;
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, UseShadedFills_Type3_1300) {
    if (!createDevice()) GTEST_SKIP();
    bool result = psDev->useShadedFills(3);
    (void)result;
    SUCCEED();
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevWithDocTest_1300, SetPreloadImagesForms_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPreloadImagesForms(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1300, SetPreloadImagesForms_False_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setPreloadImagesForms(false);
    SUCCEED();
}

// Test setGenerateOPI
TEST_F(PSOutputDevWithDocTest_1300, SetGenerateOPI_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setGenerateOPI(true);
    SUCCEED();
}

// Test setUseASCIIHex
TEST_F(PSOutputDevWithDocTest_1300, SetUseASCIIHex_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setUseASCIIHex(true);
    SUCCEED();
}

// Test setUseBinary
TEST_F(PSOutputDevWithDocTest_1300, SetUseBinary_True_1300) {
    if (!createDevice()) GTEST_SKIP();
    psDev->setUseBinary(true);
    SUCCEED();
}

} // namespace
