#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

// Helper to create a minimal valid PDF in memory
std::string createMinimalPDF() {
    return "%PDF-1.0\n"
           "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
           "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
           "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
           "xref\n0 4\n"
           "0000000000 65535 f \n"
           "0000000009 00000 n \n"
           "0000000058 00000 n \n"
           "0000000115 00000 n \n"
           "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n206\n%%EOF\n";
}

class PSOutputDevTest_1324 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Write a minimal PDF to a temp file
        pdfFileName = "test_minimal_1324.pdf";
        std::string pdfContent = createMinimalPDF();
        std::ofstream ofs(pdfFileName, std::ios::binary);
        ofs.write(pdfContent.c_str(), pdfContent.size());
        ofs.close();

        doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(pdfFileName.c_str()));

        psFileName = "test_output_1324.ps";
    }

    void TearDown() override {
        psOut.reset();
        doc.reset();
        std::remove(pdfFileName.c_str());
        std::remove(psFileName.c_str());
    }

    PSOutputDev* createPSOutputDev() {
        std::vector<int> pages = {1};
        return new PSOutputDev(psFileName.c_str(), doc.get(), nullptr, pages,
                               psModePS, 612, 792, false, false,
                               0, 0, 0, 0, psRasterizeWhenNeeded, true,
                               nullptr, nullptr, psLevel2);
    }

    std::string pdfFileName;
    std::string psFileName;
    std::unique_ptr<PDFDoc> doc;
    std::unique_ptr<PSOutputDev> psOut;
};

// Test getEnableFlate returns a boolean value (default)
TEST_F(PSOutputDevTest_1324, GetEnableFlateDefault_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        // getEnableFlate should return a bool
        bool val = psOut->getEnableFlate();
        // Default value - just verify it returns without crashing
        (void)val;
        SUCCEED();
    }
}

// Test setEnableFlate/getEnableFlate roundtrip true
TEST_F(PSOutputDevTest_1324, SetEnableFlateTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());
    }
}

// Test setEnableFlate/getEnableFlate roundtrip false
TEST_F(PSOutputDevTest_1324, SetEnableFlateFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
    }
}

// Test setEnableLZW/getEnableLZW roundtrip
TEST_F(PSOutputDevTest_1324, SetEnableLZWTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
    }
}

TEST_F(PSOutputDevTest_1324, SetEnableLZWFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());
    }
}

// Test getEmbedType1/setEmbedType1
TEST_F(PSOutputDevTest_1324, SetEmbedType1True_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
    }
}

TEST_F(PSOutputDevTest_1324, SetEmbedType1False_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());
    }
}

// Test getEmbedTrueType/setEmbedTrueType
TEST_F(PSOutputDevTest_1324, SetEmbedTrueTypeTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedTrueType(true);
        EXPECT_TRUE(psOut->getEmbedTrueType());
    }
}

TEST_F(PSOutputDevTest_1324, SetEmbedTrueTypeFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedTrueType(false);
        EXPECT_FALSE(psOut->getEmbedTrueType());
    }
}

// Test getEmbedCIDPostScript/setEmbedCIDPostScript
TEST_F(PSOutputDevTest_1324, SetEmbedCIDPostScriptTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDPostScript(true);
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());
    }
}

TEST_F(PSOutputDevTest_1324, SetEmbedCIDPostScriptFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDPostScript(false);
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());
    }
}

// Test getEmbedCIDTrueType/setEmbedCIDTrueType
TEST_F(PSOutputDevTest_1324, SetEmbedCIDTrueTypeTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDTrueType(true);
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());
    }
}

TEST_F(PSOutputDevTest_1324, SetEmbedCIDTrueTypeFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDTrueType(false);
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());
    }
}

// Test getFontPassthrough/setFontPassthrough
TEST_F(PSOutputDevTest_1324, SetFontPassthroughTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setFontPassthrough(true);
        EXPECT_TRUE(psOut->getFontPassthrough());
    }
}

TEST_F(PSOutputDevTest_1324, SetFontPassthroughFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setFontPassthrough(false);
        EXPECT_FALSE(psOut->getFontPassthrough());
    }
}

// Test getOptimizeColorSpace/setOptimizeColorSpace
TEST_F(PSOutputDevTest_1324, SetOptimizeColorSpaceTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setOptimizeColorSpace(true);
        EXPECT_TRUE(psOut->getOptimizeColorSpace());
    }
}

TEST_F(PSOutputDevTest_1324, SetOptimizeColorSpaceFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setOptimizeColorSpace(false);
        EXPECT_FALSE(psOut->getOptimizeColorSpace());
    }
}

// Test getPassLevel1CustomColor/setPassLevel1CustomColor
TEST_F(PSOutputDevTest_1324, SetPassLevel1CustomColorTrue_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setPassLevel1CustomColor(true);
        EXPECT_TRUE(psOut->getPassLevel1CustomColor());
    }
}

TEST_F(PSOutputDevTest_1324, SetPassLevel1CustomColorFalse_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setPassLevel1CustomColor(false);
        EXPECT_FALSE(psOut->getPassLevel1CustomColor());
    }
}

// Test upsideDown
TEST_F(PSOutputDevTest_1324, UpsideDown_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        bool val = psOut->upsideDown();
        (void)val;
        SUCCEED();
    }
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1324, UseDrawChar_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        bool val = psOut->useDrawChar();
        (void)val;
        SUCCEED();
    }
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1324, UseTilingPatternFill_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        bool val = psOut->useTilingPatternFill();
        (void)val;
        SUCCEED();
    }
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1324, UseDrawForm_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        bool val = psOut->useDrawForm();
        (void)val;
        SUCCEED();
    }
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1324, InterpretType3Chars_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        bool val = psOut->interpretType3Chars();
        (void)val;
        SUCCEED();
    }
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1324, NeedClipToCropBox_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        bool val = psOut->needClipToCropBox();
        (void)val;
        SUCCEED();
    }
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1324, SetDisplayText_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        // Just verify no crash
        psOut->setDisplayText(true);
        psOut->setDisplayText(false);
        SUCCEED();
    }
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1324, SetPSCenter_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setPSCenter(true);
        psOut->setPSCenter(false);
        SUCCEED();
    }
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevTest_1324, SetPSExpandSmaller_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setPSExpandSmaller(true);
        psOut->setPSExpandSmaller(false);
        SUCCEED();
    }
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevTest_1324, SetPSShrinkLarger_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setPSShrinkLarger(true);
        psOut->setPSShrinkLarger(false);
        SUCCEED();
    }
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1324, SetOverprintPreview_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setOverprintPreview(true);
        psOut->setOverprintPreview(false);
        SUCCEED();
    }
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1324, SetRasterAntialias_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setRasterAntialias(true);
        psOut->setRasterAntialias(false);
        SUCCEED();
    }
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1324, SetRasterResolution_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setRasterResolution(300.0);
        psOut->setRasterResolution(72.0);
        psOut->setRasterResolution(1200.0);
        SUCCEED();
    }
}

// Test setOffset
TEST_F(PSOutputDevTest_1324, SetOffset_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setOffset(10.0, 20.0);
        psOut->setOffset(0.0, 0.0);
        psOut->setOffset(-5.0, -10.0);
        SUCCEED();
    }
}

// Test setScale
TEST_F(PSOutputDevTest_1324, SetScale_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setScale(1.0, 1.0);
        psOut->setScale(2.0, 0.5);
        SUCCEED();
    }
}

// Test setRotate
TEST_F(PSOutputDevTest_1324, SetRotate_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setRotate(0);
        psOut->setRotate(90);
        psOut->setRotate(180);
        psOut->setRotate(270);
        SUCCEED();
    }
}

// Test setClip
TEST_F(PSOutputDevTest_1324, SetClip_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setClip(0.0, 0.0, 612.0, 792.0);
        SUCCEED();
    }
}

// Test toggle setEnableFlate multiple times
TEST_F(PSOutputDevTest_1324, ToggleEnableFlateMultipleTimes_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());
        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());
    }
}

// Test toggle setEnableLZW multiple times
TEST_F(PSOutputDevTest_1324, ToggleEnableLZWMultipleTimes_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
    }
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1324, SetUncompressPreloadedImages_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setUncompressPreloadedImages(true);
        psOut->setUncompressPreloadedImages(false);
        SUCCEED();
    }
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1324, SetPreloadImagesForms_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setPreloadImagesForms(true);
        psOut->setPreloadImagesForms(false);
        SUCCEED();
    }
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1324, SetGenerateOPI_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setGenerateOPI(true);
        psOut->setGenerateOPI(false);
        SUCCEED();
    }
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1324, SetUseASCIIHex_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setUseASCIIHex(true);
        psOut->setUseASCIIHex(false);
        SUCCEED();
    }
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1324, SetUseBinary_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setUseBinary(true);
        psOut->setUseBinary(false);
        SUCCEED();
    }
}

// Test useShadedFills with various types
TEST_F(PSOutputDevTest_1324, UseShadedFills_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        for (int type = 1; type <= 7; ++type) {
            bool val = psOut->useShadedFills(type);
            (void)val;
        }
        SUCCEED();
    }
}

// Test setUnderlayCbk with nullptr
TEST_F(PSOutputDevTest_1324, SetUnderlayCbkNull_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setUnderlayCbk(nullptr, nullptr);
        SUCCEED();
    }
}

// Test setOverlayCbk with nullptr
TEST_F(PSOutputDevTest_1324, SetOverlayCbkNull_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setOverlayCbk(nullptr, nullptr);
        SUCCEED();
    }
}

// Test setForceRasterize
TEST_F(PSOutputDevTest_1324, SetForceRasterize_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setForceRasterize(psRasterizeWhenNeeded);
        psOut->setForceRasterize(psAlwaysRasterize);
        psOut->setForceRasterize(psNeverRasterize);
        SUCCEED();
    }
}

// Test isOk on valid construction
TEST_F(PSOutputDevTest_1324, IsOkValid_1324) {
    psOut.reset(createPSOutputDev());
    // With a valid minimal PDF and valid output file, isOk should be true
    // (depends on whether minimal PDF is accepted)
    if (psOut) {
        bool ok = psOut->isOk();
        (void)ok;
        SUCCEED();
    }
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1324, SetRasterMono_1324) {
    psOut.reset(createPSOutputDev());
    if (psOut && psOut->isOk()) {
        psOut->setRasterMono();
        SUCCEED();
    }
}

} // namespace
