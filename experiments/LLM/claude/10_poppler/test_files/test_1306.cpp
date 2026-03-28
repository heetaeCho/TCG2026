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

namespace {

class PSOutputDevTest_1306 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev writing to a temp file with a minimal valid PDF
    // Returns nullptr if creation fails
    struct PSOutputDevContext {
        PSOutputDev* dev = nullptr;
        PDFDoc* doc = nullptr;
        FILE* tmpFile = nullptr;
        std::string tmpFileName;

        ~PSOutputDevContext() {
            delete dev;
            delete doc;
            if (tmpFile) {
                fclose(tmpFile);
            }
            if (!tmpFileName.empty()) {
                remove(tmpFileName.c_str());
            }
        }
    };

    // Create a minimal PDF in a temp file and open it
    std::unique_ptr<PSOutputDevContext> createPSOutputDev() {
        auto ctx = std::make_unique<PSOutputDevContext>();

        // Create a minimal PDF file
        ctx->tmpFileName = "test_psoutputdev_1306.pdf";
        FILE* f = fopen(ctx->tmpFileName.c_str(), "wb");
        if (!f) return nullptr;

        const char* minimalPDF =
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

        fwrite(minimalPDF, 1, strlen(minimalPDF), f);
        fclose(f);

        auto* fileName = new GooString(ctx->tmpFileName.c_str());
        ctx->doc = new PDFDoc(fileName);
        if (!ctx->doc->isOk()) {
            return nullptr;
        }

        std::string psFileName = "test_output_1306.ps";
        std::vector<int> pages = {1};

        ctx->dev = new PSOutputDev(
            psFileName.c_str(), ctx->doc, nullptr,
            pages, psModePS, 612, 792,
            false, false, 0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);

        if (!ctx->dev->isOk()) {
            return nullptr;
        }

        return ctx;
    }
};

// Test setDisplayText with true
TEST_F(PSOutputDevTest_1306, SetDisplayTextTrue_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Should not throw or crash
    ctx->dev->setDisplayText(true);
}

// Test setDisplayText with false
TEST_F(PSOutputDevTest_1306, SetDisplayTextFalse_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setDisplayText(false);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1306, SetPSCenter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setPSCenter(true);
    ctx->dev->setPSCenter(false);
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevTest_1306, SetPSExpandSmaller_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setPSExpandSmaller(true);
    ctx->dev->setPSExpandSmaller(false);
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevTest_1306, SetPSShrinkLarger_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setPSShrinkLarger(true);
    ctx->dev->setPSShrinkLarger(false);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1306, SetOverprintPreview_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setOverprintPreview(true);
    ctx->dev->setOverprintPreview(false);
}

// Test embed type1 getter/setter pair
TEST_F(PSOutputDevTest_1306, EmbedType1GetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setEmbedType1(true);
    EXPECT_TRUE(ctx->dev->getEmbedType1());
    ctx->dev->setEmbedType1(false);
    EXPECT_FALSE(ctx->dev->getEmbedType1());
}

// Test embed TrueType getter/setter pair
TEST_F(PSOutputDevTest_1306, EmbedTrueTypeGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setEmbedTrueType(true);
    EXPECT_TRUE(ctx->dev->getEmbedTrueType());
    ctx->dev->setEmbedTrueType(false);
    EXPECT_FALSE(ctx->dev->getEmbedTrueType());
}

// Test embed CID PostScript getter/setter pair
TEST_F(PSOutputDevTest_1306, EmbedCIDPostScriptGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(ctx->dev->getEmbedCIDPostScript());
    ctx->dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(ctx->dev->getEmbedCIDPostScript());
}

// Test embed CID TrueType getter/setter pair
TEST_F(PSOutputDevTest_1306, EmbedCIDTrueTypeGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(ctx->dev->getEmbedCIDTrueType());
    ctx->dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(ctx->dev->getEmbedCIDTrueType());
}

// Test font passthrough getter/setter pair
TEST_F(PSOutputDevTest_1306, FontPassthroughGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setFontPassthrough(true);
    EXPECT_TRUE(ctx->dev->getFontPassthrough());
    ctx->dev->setFontPassthrough(false);
    EXPECT_FALSE(ctx->dev->getFontPassthrough());
}

// Test optimize color space getter/setter pair
TEST_F(PSOutputDevTest_1306, OptimizeColorSpaceGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(ctx->dev->getOptimizeColorSpace());
    ctx->dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(ctx->dev->getOptimizeColorSpace());
}

// Test pass level1 custom color getter/setter pair
TEST_F(PSOutputDevTest_1306, PassLevel1CustomColorGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(ctx->dev->getPassLevel1CustomColor());
    ctx->dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(ctx->dev->getPassLevel1CustomColor());
}

// Test enable LZW getter/setter pair
TEST_F(PSOutputDevTest_1306, EnableLZWGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setEnableLZW(true);
    EXPECT_TRUE(ctx->dev->getEnableLZW());
    ctx->dev->setEnableLZW(false);
    EXPECT_FALSE(ctx->dev->getEnableLZW());
}

// Test enable Flate getter/setter pair
TEST_F(PSOutputDevTest_1306, EnableFlateGetterSetter_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setEnableFlate(true);
    EXPECT_TRUE(ctx->dev->getEnableFlate());
    ctx->dev->setEnableFlate(false);
    EXPECT_FALSE(ctx->dev->getEnableFlate());
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1306, UpsideDown_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // upsideDown should return a bool without crashing
    bool result = ctx->dev->upsideDown();
    (void)result; // Just verify it doesn't crash
}

// Test useDrawChar returns expected value
TEST_F(PSOutputDevTest_1306, UseDrawChar_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool result = ctx->dev->useDrawChar();
    (void)result;
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1306, UseTilingPatternFill_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool result = ctx->dev->useTilingPatternFill();
    (void)result;
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1306, UseDrawForm_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool result = ctx->dev->useDrawForm();
    (void)result;
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1306, InterpretType3Chars_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool result = ctx->dev->interpretType3Chars();
    (void)result;
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1306, NeedClipToCropBox_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool result = ctx->dev->needClipToCropBox();
    (void)result;
}

// Test setOffset does not crash
TEST_F(PSOutputDevTest_1306, SetOffset_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setOffset(10.0, 20.0);
    ctx->dev->setOffset(0.0, 0.0);
    ctx->dev->setOffset(-5.0, -10.0);
}

// Test setScale does not crash
TEST_F(PSOutputDevTest_1306, SetScale_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setScale(1.0, 1.0);
    ctx->dev->setScale(2.0, 0.5);
}

// Test setRotate does not crash
TEST_F(PSOutputDevTest_1306, SetRotate_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setRotate(0);
    ctx->dev->setRotate(90);
    ctx->dev->setRotate(180);
    ctx->dev->setRotate(270);
}

// Test setClip does not crash
TEST_F(PSOutputDevTest_1306, SetClip_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setClip(0.0, 0.0, 612.0, 792.0);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1306, SetRasterResolution_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setRasterResolution(300.0);
    ctx->dev->setRasterResolution(72.0);
    ctx->dev->setRasterResolution(600.0);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1306, SetRasterAntialias_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setRasterAntialias(true);
    ctx->dev->setRasterAntialias(false);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1306, SetUncompressPreloadedImages_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setUncompressPreloadedImages(true);
    ctx->dev->setUncompressPreloadedImages(false);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1306, SetPreloadImagesForms_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setPreloadImagesForms(true);
    ctx->dev->setPreloadImagesForms(false);
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1306, SetGenerateOPI_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setGenerateOPI(true);
    ctx->dev->setGenerateOPI(false);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1306, SetUseASCIIHex_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setUseASCIIHex(true);
    ctx->dev->setUseASCIIHex(false);
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1306, SetUseBinary_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setUseBinary(true);
    ctx->dev->setUseBinary(false);
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1306, SetRasterMono_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setRasterMono();
}

// Test setUnderlayCbk with null
TEST_F(PSOutputDevTest_1306, SetUnderlayCbkNull_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setUnderlayCbk(nullptr, nullptr);
}

// Test setOverlayCbk with null
TEST_F(PSOutputDevTest_1306, SetOverlayCbkNull_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setOverlayCbk(nullptr, nullptr);
}

// Test isOk after construction
TEST_F(PSOutputDevTest_1306, IsOkAfterConstruction_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_TRUE(ctx->dev->isOk());
}

// Test useShadedFills for various types
TEST_F(PSOutputDevTest_1306, UseShadedFills_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    for (int type = 1; type <= 7; ++type) {
        bool result = ctx->dev->useShadedFills(type);
        (void)result;
    }
}

// Test toggling embedType1 multiple times
TEST_F(PSOutputDevTest_1306, EmbedType1Toggle_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setEmbedType1(false);
    EXPECT_FALSE(ctx->dev->getEmbedType1());
    ctx->dev->setEmbedType1(true);
    EXPECT_TRUE(ctx->dev->getEmbedType1());
    ctx->dev->setEmbedType1(true);
    EXPECT_TRUE(ctx->dev->getEmbedType1());
}

// Test setForceRasterize
TEST_F(PSOutputDevTest_1306, SetForceRasterize_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setForceRasterize(psRasterizeWhenNeeded);
    ctx->dev->setForceRasterize(psAlwaysRasterize);
    ctx->dev->setForceRasterize(psNeverRasterize);
}

// Test boundary: setOffset with very large values
TEST_F(PSOutputDevTest_1306, SetOffsetLargeValues_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setOffset(1e10, 1e10);
    ctx->dev->setOffset(-1e10, -1e10);
}

// Test boundary: setScale with zero
TEST_F(PSOutputDevTest_1306, SetScaleZero_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setScale(0.0, 0.0);
}

// Test boundary: setRasterResolution with zero
TEST_F(PSOutputDevTest_1306, SetRasterResolutionZero_1306) {
    auto ctx = createPSOutputDev();
    if (!ctx || !ctx->dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    ctx->dev->setRasterResolution(0.0);
}

} // namespace
