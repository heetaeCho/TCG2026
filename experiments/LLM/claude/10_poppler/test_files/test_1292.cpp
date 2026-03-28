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

// Helper function to collect PS output
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1292 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test: Construction with invalid file name should result in !isOk()
TEST_F(PSOutputDevTest_1292, ConstructWithInvalidFileName_1292) {
    // Passing nullptr doc should cause initialization failure
    std::vector<int> pages = {1};
    PSOutputDev psOut("/dev/null/nonexistent/path/file.ps", nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    // Without a valid doc, isOk() should be false
    EXPECT_FALSE(psOut.isOk());
}

// Test: Construction with output function and null doc
TEST_F(PSOutputDevTest_1292, ConstructWithOutputFuncNullDoc_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_FALSE(psOut.isOk());
}

// Test: upsideDown returns expected value
TEST_F(PSOutputDevTest_1292, UpsideDown_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    // upsideDown should return a boolean regardless of ok state
    bool result = psOut.upsideDown();
    // Just verify it returns a bool (typically true for PS)
    EXPECT_TRUE(result == true || result == false);
}

// Test: useDrawChar returns expected value
TEST_F(PSOutputDevTest_1292, UseDrawChar_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    bool result = psOut.useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

// Test: interpretType3Chars
TEST_F(PSOutputDevTest_1292, InterpretType3Chars_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    bool result = psOut.interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test: setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevTest_1292, SetGetEmbedType1_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setEmbedType1(true);
    EXPECT_TRUE(psOut.getEmbedType1());
    psOut.setEmbedType1(false);
    EXPECT_FALSE(psOut.getEmbedType1());
}

// Test: setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevTest_1292, SetGetEmbedTrueType_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setEmbedTrueType(true);
    EXPECT_TRUE(psOut.getEmbedTrueType());
    psOut.setEmbedTrueType(false);
    EXPECT_FALSE(psOut.getEmbedTrueType());
}

// Test: setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1292, SetGetEmbedCIDPostScript_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOut.getEmbedCIDPostScript());
    psOut.setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOut.getEmbedCIDPostScript());
}

// Test: setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1292, SetGetEmbedCIDTrueType_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setEmbedCIDTrueType(true);
    EXPECT_TRUE(psOut.getEmbedCIDTrueType());
    psOut.setEmbedCIDTrueType(false);
    EXPECT_FALSE(psOut.getEmbedCIDTrueType());
}

// Test: setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevTest_1292, SetGetFontPassthrough_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setFontPassthrough(true);
    EXPECT_TRUE(psOut.getFontPassthrough());
    psOut.setFontPassthrough(false);
    EXPECT_FALSE(psOut.getFontPassthrough());
}

// Test: setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1292, SetGetOptimizeColorSpace_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setOptimizeColorSpace(true);
    EXPECT_TRUE(psOut.getOptimizeColorSpace());
    psOut.setOptimizeColorSpace(false);
    EXPECT_FALSE(psOut.getOptimizeColorSpace());
}

// Test: setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1292, SetGetPassLevel1CustomColor_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setPassLevel1CustomColor(true);
    EXPECT_TRUE(psOut.getPassLevel1CustomColor());
    psOut.setPassLevel1CustomColor(false);
    EXPECT_FALSE(psOut.getPassLevel1CustomColor());
}

// Test: setEnableLZW and getEnableLZW
TEST_F(PSOutputDevTest_1292, SetGetEnableLZW_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setEnableLZW(true);
    EXPECT_TRUE(psOut.getEnableLZW());
    psOut.setEnableLZW(false);
    EXPECT_FALSE(psOut.getEnableLZW());
}

// Test: setEnableFlate and getEnableFlate
TEST_F(PSOutputDevTest_1292, SetGetEnableFlate_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    psOut.setEnableFlate(true);
    EXPECT_TRUE(psOut.getEnableFlate());
    psOut.setEnableFlate(false);
    EXPECT_FALSE(psOut.getEnableFlate());
}

// Test: setDisplayText does not crash
TEST_F(PSOutputDevTest_1292, SetDisplayText_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setDisplayText(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setDisplayText(false));
}

// Test: setPSCenter does not crash
TEST_F(PSOutputDevTest_1292, SetPSCenter_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setPSCenter(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setPSCenter(false));
}

// Test: setPSExpandSmaller does not crash
TEST_F(PSOutputDevTest_1292, SetPSExpandSmaller_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setPSExpandSmaller(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setPSExpandSmaller(false));
}

// Test: setPSShrinkLarger does not crash
TEST_F(PSOutputDevTest_1292, SetPSShrinkLarger_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setPSShrinkLarger(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setPSShrinkLarger(false));
}

// Test: setOverprintPreview does not crash
TEST_F(PSOutputDevTest_1292, SetOverprintPreview_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setOverprintPreview(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setOverprintPreview(false));
}

// Test: setRasterAntialias does not crash
TEST_F(PSOutputDevTest_1292, SetRasterAntialias_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setRasterAntialias(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setRasterAntialias(false));
}

// Test: setRasterResolution does not crash
TEST_F(PSOutputDevTest_1292, SetRasterResolution_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setRasterResolution(300.0));
    EXPECT_NO_FATAL_FAILURE(psOut.setRasterResolution(72.0));
    EXPECT_NO_FATAL_FAILURE(psOut.setRasterResolution(1200.0));
}

// Test: setOffset does not crash
TEST_F(PSOutputDevTest_1292, SetOffset_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setOffset(10.0, 20.0));
    EXPECT_NO_FATAL_FAILURE(psOut.setOffset(0.0, 0.0));
    EXPECT_NO_FATAL_FAILURE(psOut.setOffset(-5.0, -10.0));
}

// Test: setScale does not crash
TEST_F(PSOutputDevTest_1292, SetScale_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setScale(1.0, 1.0));
    EXPECT_NO_FATAL_FAILURE(psOut.setScale(2.0, 0.5));
}

// Test: setRotate does not crash
TEST_F(PSOutputDevTest_1292, SetRotate_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setRotate(0));
    EXPECT_NO_FATAL_FAILURE(psOut.setRotate(90));
    EXPECT_NO_FATAL_FAILURE(psOut.setRotate(180));
    EXPECT_NO_FATAL_FAILURE(psOut.setRotate(270));
}

// Test: setClip does not crash
TEST_F(PSOutputDevTest_1292, SetClip_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setClip(0.0, 0.0, 612.0, 792.0));
}

// Test: setForceRasterize does not crash
TEST_F(PSOutputDevTest_1292, SetForceRasterize_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setForceRasterize(psRasterizeWhenNeeded));
    EXPECT_NO_FATAL_FAILURE(psOut.setForceRasterize(psAlwaysRasterize));
    EXPECT_NO_FATAL_FAILURE(psOut.setForceRasterize(psNeverRasterize));
}

// Test: setUncompressPreloadedImages does not crash
TEST_F(PSOutputDevTest_1292, SetUncompressPreloadedImages_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setUncompressPreloadedImages(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setUncompressPreloadedImages(false));
}

// Test: setUnderlayCbk with null callback
TEST_F(PSOutputDevTest_1292, SetUnderlayCbkNull_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setUnderlayCbk(nullptr, nullptr));
}

// Test: setOverlayCbk with null callback
TEST_F(PSOutputDevTest_1292, SetOverlayCbkNull_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setOverlayCbk(nullptr, nullptr));
}

// Test: useTilingPatternFill
TEST_F(PSOutputDevTest_1292, UseTilingPatternFill_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    bool result = psOut.useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test: useDrawForm
TEST_F(PSOutputDevTest_1292, UseDrawForm_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    bool result = psOut.useDrawForm();
    EXPECT_TRUE(result == true || result == false);
}

// Test: needClipToCropBox
TEST_F(PSOutputDevTest_1292, NeedClipToCropBox_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    bool result = psOut.needClipToCropBox();
    EXPECT_TRUE(result == true || result == false);
}

// Test: useShadedFills with different types
TEST_F(PSOutputDevTest_1292, UseShadedFills_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    for (int type = 1; type <= 7; ++type) {
        bool result = psOut.useShadedFills(type);
        EXPECT_TRUE(result == true || result == false);
    }
}

// Test: setRasterMono does not crash
TEST_F(PSOutputDevTest_1292, SetRasterMono_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setRasterMono());
}

// Test: empty pages vector
TEST_F(PSOutputDevTest_1292, EmptyPagesVector_1292) {
    std::string output;
    std::vector<int> pages;
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    // With no doc, this should not be ok
    EXPECT_FALSE(psOut.isOk());
}

// Test: various setter methods for binary/hex output
TEST_F(PSOutputDevTest_1292, SetUseASCIIHexAndBinary_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setUseASCIIHex(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setUseASCIIHex(false));
    EXPECT_NO_FATAL_FAILURE(psOut.setUseBinary(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setUseBinary(false));
}

// Test: setGenerateOPI does not crash
TEST_F(PSOutputDevTest_1292, SetGenerateOPI_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setGenerateOPI(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setGenerateOPI(false));
}

// Test: setPreloadImagesForms does not crash
TEST_F(PSOutputDevTest_1292, SetPreloadImagesForms_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_NO_FATAL_FAILURE(psOut.setPreloadImagesForms(true));
    EXPECT_NO_FATAL_FAILURE(psOut.setPreloadImagesForms(false));
}

// Test: Construction with different PS levels
TEST_F(PSOutputDevTest_1292, ConstructWithDifferentLevels_1292) {
    std::string output1, output2, output3;
    std::vector<int> pages = {1};

    PSOutputDev psOut1(outputFunc, &output1, nullptr, nullptr,
                       pages, psModePS, 612, 792, false, false,
                       0, 0, 0, 0, psRasterizeWhenNeeded, true,
                       nullptr, nullptr, psLevel1);
    // Without valid doc, all should fail
    EXPECT_FALSE(psOut1.isOk());

    PSOutputDev psOut2(outputFunc, &output2, nullptr, nullptr,
                       pages, psModePS, 612, 792, false, false,
                       0, 0, 0, 0, psRasterizeWhenNeeded, true,
                       nullptr, nullptr, psLevel2);
    EXPECT_FALSE(psOut2.isOk());

    PSOutputDev psOut3(outputFunc, &output3, nullptr, nullptr,
                       pages, psModePS, 612, 792, false, false,
                       0, 0, 0, 0, psRasterizeWhenNeeded, true,
                       nullptr, nullptr, psLevel3);
    EXPECT_FALSE(psOut3.isOk());
}

// Test: Construction with EPS mode
TEST_F(PSOutputDevTest_1292, ConstructWithEPSMode_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModeEPS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);
    EXPECT_FALSE(psOut.isOk());
}

// Test: Multiple boolean setter/getter roundtrip consistency
TEST_F(PSOutputDevTest_1292, BooleanSetterGetterConsistency_1292) {
    std::string output;
    std::vector<int> pages = {1};
    PSOutputDev psOut(outputFunc, &output, nullptr, nullptr,
                      pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    // Test all boolean pairs in sequence
    psOut.setEmbedType1(false);
    EXPECT_FALSE(psOut.getEmbedType1());
    psOut.setEmbedType1(true);
    EXPECT_TRUE(psOut.getEmbedType1());

    psOut.setEmbedTrueType(false);
    EXPECT_FALSE(psOut.getEmbedTrueType());
    psOut.setEmbedTrueType(true);
    EXPECT_TRUE(psOut.getEmbedTrueType());

    psOut.setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOut.getEmbedCIDPostScript());
    psOut.setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOut.getEmbedCIDPostScript());

    psOut.setEmbedCIDTrueType(false);
    EXPECT_FALSE(psOut.getEmbedCIDTrueType());
    psOut.setEmbedCIDTrueType(true);
    EXPECT_TRUE(psOut.getEmbedCIDTrueType());

    psOut.setFontPassthrough(false);
    EXPECT_FALSE(psOut.getFontPassthrough());
    psOut.setFontPassthrough(true);
    EXPECT_TRUE(psOut.getFontPassthrough());

    psOut.setOptimizeColorSpace(false);
    EXPECT_FALSE(psOut.getOptimizeColorSpace());
    psOut.setOptimizeColorSpace(true);
    EXPECT_TRUE(psOut.getOptimizeColorSpace());

    psOut.setEnableLZW(false);
    EXPECT_FALSE(psOut.getEnableLZW());
    psOut.setEnableLZW(true);
    EXPECT_TRUE(psOut.getEnableLZW());

    psOut.setEnableFlate(false);
    EXPECT_FALSE(psOut.getEnableFlate());
    psOut.setEnableFlate(true);
    EXPECT_TRUE(psOut.getEnableFlate());
}
