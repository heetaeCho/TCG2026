#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Output function for PSOutputDev
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *output = static_cast<std::string *>(stream);
    output->append(data, len);
}

class PSOutputDevTest_1330 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using a FoFiOutputFunc
    // Returns nullptr if creation fails
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        return new PSOutputDev(outputFunc, &outputBuffer, nullptr, doc,
                               pages, psModePS, -1, -1, false, false,
                               0, 0, 0, 0, psRasterizeWhenNeeded, true,
                               nullptr, nullptr, psLevel2);
    }

    std::string outputBuffer;
};

// Test with a simple PDF file to exercise setter/getter pairs
class PSOutputDevSetterGetterTest_1330 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal PDF in a temp file
        tmpFile = tmpfile();
        if (tmpFile) {
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
                "trailer<</Root 1 0 R/Size 4>>\n"
                "startxref\n190\n%%EOF\n";
            fwrite(minimalPDF, 1, strlen(minimalPDF), tmpFile);
            fflush(tmpFile);
            rewind(tmpFile);

            doc = new PDFDoc(tmpFile);
        } else {
            doc = nullptr;
        }

        if (doc && doc->isOk()) {
            std::vector<int> pages = {1};
            psDev = new PSOutputDev(outputFunc, &outputBuffer, nullptr, doc,
                                    pages, psModePS, -1, -1, false, false,
                                    0, 0, 0, 0, psRasterizeWhenNeeded, true,
                                    nullptr, nullptr, psLevel2);
        } else {
            psDev = nullptr;
        }
    }

    void TearDown() override {
        delete psDev;
        delete doc;
        // tmpFile is owned by PDFDoc after construction, or closed
    }

    static void outputFunc(void *stream, const char *data, size_t len) {
        std::string *output = static_cast<std::string *>(stream);
        output->append(data, len);
    }

    std::string outputBuffer;
    FILE *tmpFile = nullptr;
    PDFDoc *doc = nullptr;
    PSOutputDev *psDev = nullptr;
};

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevSetterGetterTest_1330, SetOptimizeColorSpaceTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setOptimizeColorSpace(true);
    EXPECT_TRUE(psDev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetOptimizeColorSpaceFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setOptimizeColorSpace(false);
    EXPECT_FALSE(psDev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetOptimizeColorSpaceToggle_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setOptimizeColorSpace(true);
    EXPECT_TRUE(psDev->getOptimizeColorSpace());
    psDev->setOptimizeColorSpace(false);
    EXPECT_FALSE(psDev->getOptimizeColorSpace());
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedType1True_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedType1(true);
    EXPECT_TRUE(psDev->getEmbedType1());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedType1False_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedType1(false);
    EXPECT_FALSE(psDev->getEmbedType1());
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedTrueTypeTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedTrueType(true);
    EXPECT_TRUE(psDev->getEmbedTrueType());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedTrueTypeFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedTrueType(false);
    EXPECT_FALSE(psDev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedCIDPostScriptTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psDev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedCIDPostScriptFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psDev->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedCIDTrueTypeTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(psDev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetEmbedCIDTrueTypeFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(psDev->getEmbedCIDTrueType());
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevSetterGetterTest_1330, SetFontPassthroughTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setFontPassthrough(true);
    EXPECT_TRUE(psDev->getFontPassthrough());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetFontPassthroughFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setFontPassthrough(false);
    EXPECT_FALSE(psDev->getFontPassthrough());
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevSetterGetterTest_1330, SetPassLevel1CustomColorTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(psDev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetPassLevel1CustomColorFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(psDev->getPassLevel1CustomColor());
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevSetterGetterTest_1330, SetEnableLZWTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEnableLZW(true);
    EXPECT_TRUE(psDev->getEnableLZW());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetEnableLZWFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEnableLZW(false);
    EXPECT_FALSE(psDev->getEnableLZW());
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevSetterGetterTest_1330, SetEnableFlateTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEnableFlate(true);
    EXPECT_TRUE(psDev->getEnableFlate());
}

TEST_F(PSOutputDevSetterGetterTest_1330, SetEnableFlateFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setEnableFlate(false);
    EXPECT_FALSE(psDev->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevSetterGetterTest_1330, UpsideDownReturnsFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    // PS output is typically not upside down
    EXPECT_FALSE(psDev->upsideDown());
}

// Test useDrawChar
TEST_F(PSOutputDevSetterGetterTest_1330, UseDrawCharReturnsFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    // PSOutputDev uses drawString, not drawChar
    EXPECT_FALSE(psDev->useDrawChar());
}

// Test useTilingPatternFill
TEST_F(PSOutputDevSetterGetterTest_1330, UseTilingPatternFillReturnsTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    EXPECT_TRUE(psDev->useTilingPatternFill());
}

// Test useDrawForm
TEST_F(PSOutputDevSetterGetterTest_1330, UseDrawFormReturnsTrue_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    EXPECT_TRUE(psDev->useDrawForm());
}

// Test interpretType3Chars
TEST_F(PSOutputDevSetterGetterTest_1330, InterpretType3CharsReturnsFalse_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    EXPECT_FALSE(psDev->interpretType3Chars());
}

// Test setDisplayText
TEST_F(PSOutputDevSetterGetterTest_1330, SetDisplayText_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    // Just verify it doesn't crash; no getter available
    psDev->setDisplayText(true);
    psDev->setDisplayText(false);
}

// Test setPSCenter
TEST_F(PSOutputDevSetterGetterTest_1330, SetPSCenter_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setPSCenter(true);
    psDev->setPSCenter(false);
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevSetterGetterTest_1330, SetPSExpandSmaller_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setPSExpandSmaller(true);
    psDev->setPSExpandSmaller(false);
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevSetterGetterTest_1330, SetPSShrinkLarger_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setPSShrinkLarger(true);
    psDev->setPSShrinkLarger(false);
}

// Test setOverprintPreview
TEST_F(PSOutputDevSetterGetterTest_1330, SetOverprintPreview_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setOverprintPreview(true);
    psDev->setOverprintPreview(false);
}

// Test setRasterAntialias
TEST_F(PSOutputDevSetterGetterTest_1330, SetRasterAntialias_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setRasterAntialias(true);
    psDev->setRasterAntialias(false);
}

// Test setRasterResolution
TEST_F(PSOutputDevSetterGetterTest_1330, SetRasterResolution_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setRasterResolution(300.0);
    psDev->setRasterResolution(72.0);
    psDev->setRasterResolution(600.0);
}

// Test setOffset
TEST_F(PSOutputDevSetterGetterTest_1330, SetOffset_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setOffset(0.0, 0.0);
    psDev->setOffset(100.0, 200.0);
    psDev->setOffset(-50.0, -50.0);
}

// Test setScale
TEST_F(PSOutputDevSetterGetterTest_1330, SetScale_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setScale(1.0, 1.0);
    psDev->setScale(2.0, 2.0);
    psDev->setScale(0.5, 0.5);
}

// Test setRotate
TEST_F(PSOutputDevSetterGetterTest_1330, SetRotate_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setRotate(0);
    psDev->setRotate(90);
    psDev->setRotate(180);
    psDev->setRotate(270);
}

// Test setClip
TEST_F(PSOutputDevSetterGetterTest_1330, SetClip_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setClip(0.0, 0.0, 612.0, 792.0);
}

// Test setUnderlayCbk
TEST_F(PSOutputDevSetterGetterTest_1330, SetUnderlayCbk_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setUnderlayCbk(nullptr, nullptr);
}

// Test setOverlayCbk
TEST_F(PSOutputDevSetterGetterTest_1330, SetOverlayCbk_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setOverlayCbk(nullptr, nullptr);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevSetterGetterTest_1330, SetUncompressPreloadedImages_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setUncompressPreloadedImages(true);
    psDev->setUncompressPreloadedImages(false);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevSetterGetterTest_1330, SetPreloadImagesForms_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setPreloadImagesForms(true);
    psDev->setPreloadImagesForms(false);
}

// Test setGenerateOPI
TEST_F(PSOutputDevSetterGetterTest_1330, SetGenerateOPI_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setGenerateOPI(true);
    psDev->setGenerateOPI(false);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevSetterGetterTest_1330, SetUseASCIIHex_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setUseASCIIHex(true);
    psDev->setUseASCIIHex(false);
}

// Test setUseBinary
TEST_F(PSOutputDevSetterGetterTest_1330, SetUseBinary_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setUseBinary(true);
    psDev->setUseBinary(false);
}

// Test isOk
TEST_F(PSOutputDevSetterGetterTest_1330, IsOk_1330) {
    if (!psDev) GTEST_SKIP() << "PSOutputDev not available";
    // Should be ok if constructed successfully
    EXPECT_TRUE(psDev->isOk());
}

// Test multiple setters in sequence to verify no interference
TEST_F(PSOutputDevSetterGetterTest_1330, MultipleSettersNoInterference_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";

    psDev->setEmbedType1(true);
    psDev->setEmbedTrueType(false);
    psDev->setEmbedCIDPostScript(true);
    psDev->setEmbedCIDTrueType(false);
    psDev->setFontPassthrough(true);
    psDev->setOptimizeColorSpace(false);
    psDev->setEnableLZW(true);
    psDev->setEnableFlate(false);

    EXPECT_TRUE(psDev->getEmbedType1());
    EXPECT_FALSE(psDev->getEmbedTrueType());
    EXPECT_TRUE(psDev->getEmbedCIDPostScript());
    EXPECT_FALSE(psDev->getEmbedCIDTrueType());
    EXPECT_TRUE(psDev->getFontPassthrough());
    EXPECT_FALSE(psDev->getOptimizeColorSpace());
    EXPECT_TRUE(psDev->getEnableLZW());
    EXPECT_FALSE(psDev->getEnableFlate());
}

// Test setter/getter boundary: rapidly toggle
TEST_F(PSOutputDevSetterGetterTest_1330, RapidToggleOptimizeColorSpace_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";

    for (int i = 0; i < 100; ++i) {
        bool val = (i % 2 == 0);
        psDev->setOptimizeColorSpace(val);
        EXPECT_EQ(val, psDev->getOptimizeColorSpace());
    }
}

// Test useShadedFills for various types
TEST_F(PSOutputDevSetterGetterTest_1330, UseShadedFillsVariousTypes_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";

    // Types 1-7 are the shading types in PDF
    for (int type = 1; type <= 7; ++type) {
        // Just verify it returns a bool without crashing
        bool result = psDev->useShadedFills(type);
        (void)result; // We can't predict the value without knowing internals
    }
}

// Test needClipToCropBox
TEST_F(PSOutputDevSetterGetterTest_1330, NeedClipToCropBox_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    // Just verify it returns a bool without crashing
    bool result = psDev->needClipToCropBox();
    (void)result;
}

// Test setForceRasterize
TEST_F(PSOutputDevSetterGetterTest_1330, SetForceRasterize_1330) {
    if (!psDev || !psDev->isOk()) GTEST_SKIP() << "PSOutputDev not available";
    psDev->setForceRasterize(psRasterizeWhenNeeded);
    psDev->setForceRasterize(psAlwaysRasterize);
    psDev->setForceRasterize(psNeverRasterize);
}
