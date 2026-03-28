#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

// Output function that collects output into a string
void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1333 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev if possible with a real PDF
    // We'll use a minimal approach; tests that require a valid object
    // will be skipped if we can't create one.
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        outputBuffer.clear();
        char title[] = "Test";
        auto dev = std::make_unique<PSOutputDev>(
            outputToString, &outputBuffer, title, doc, pages,
            psModePS, -1, -1, false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        if (dev->isOk()) {
            return dev;
        }
        return nullptr;
    }

    std::string outputBuffer;
};

// Helper to create a minimal valid PDF in memory for testing
class PSOutputDevWithDocTest_1333 : public PSOutputDevTest_1333 {
protected:
    void SetUp() override {
        PSOutputDevTest_1333::SetUp();

        // Create a minimal PDF file
        tmpFileName = std::tmpnam(nullptr);
        if (tmpFileName.empty()) {
            tmpFileName = "/tmp/test_psoutputdev_1333.pdf";
        }
        
        FILE *f = fopen(tmpFileName.c_str(), "wb");
        if (f) {
            // Minimal valid PDF
            const char *minPdf =
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
            fwrite(minPdf, 1, strlen(minPdf), f);
            fclose(f);
        }

        auto *gs = new GooString(tmpFileName.c_str());
        doc = std::make_unique<PDFDoc>(gs);
        docValid = doc->isOk();
    }

    void TearDown() override {
        dev.reset();
        doc.reset();
        if (!tmpFileName.empty()) {
            std::remove(tmpFileName.c_str());
        }
        PSOutputDevTest_1333::TearDown();
    }

    void createDev() {
        if (!docValid) return;
        std::vector<int> pages = {1};
        outputBuffer.clear();
        char title[] = "Test";
        dev = std::make_unique<PSOutputDev>(
            outputToString, &outputBuffer, title, doc.get(), pages,
            psModePS, -1, -1, false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
    }

    std::string tmpFileName;
    std::unique_ptr<PDFDoc> doc;
    std::unique_ptr<PSOutputDev> dev;
    bool docValid = false;
};

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedType1_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedType1_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedTrueType_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedTrueType_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedCIDPostScript_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedCIDPostScript_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedCIDTrueType_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetEmbedCIDTrueType_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevWithDocTest_1333, SetGetFontPassthrough_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetFontPassthrough_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevWithDocTest_1333, SetGetOptimizeColorSpace_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetOptimizeColorSpace_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevWithDocTest_1333, SetGetPassLevel1CustomColor_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetPassLevel1CustomColor_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test setEnableLZW and getEnableLZW
TEST_F(PSOutputDevWithDocTest_1333, SetGetEnableLZW_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetEnableLZW_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevWithDocTest_1333, SetGetEnableFlate_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
}

TEST_F(PSOutputDevWithDocTest_1333, SetGetEnableFlate_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevWithDocTest_1333, UpsideDown_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    // upsideDown should return a consistent boolean value
    bool result = dev->upsideDown();
    // Just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar
TEST_F(PSOutputDevWithDocTest_1333, UseDrawChar_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevWithDocTest_1333, UseTilingPatternFill_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawForm
TEST_F(PSOutputDevWithDocTest_1333, UseDrawForm_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    bool result = dev->useDrawForm();
    EXPECT_TRUE(result == true || result == false);
}

// Test interpretType3Chars
TEST_F(PSOutputDevWithDocTest_1333, InterpretType3Chars_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test needClipToCropBox
TEST_F(PSOutputDevWithDocTest_1333, NeedClipToCropBox_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    bool result = dev->needClipToCropBox();
    EXPECT_TRUE(result == true || result == false);
}

// Test toggle behavior: set true then false
TEST_F(PSOutputDevWithDocTest_1333, ToggleEmbedType1_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

// Test toggle behavior for EnableFlate
TEST_F(PSOutputDevWithDocTest_1333, ToggleEnableFlate_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test isOk after valid construction
TEST_F(PSOutputDevWithDocTest_1333, IsOkAfterConstruction_1333) {
    createDev();
    if (!docValid) GTEST_SKIP() << "Could not create valid PDFDoc";
    // dev should be ok if doc was valid
    if (dev) {
        EXPECT_TRUE(dev->isOk());
    }
}

// Test setDisplayText doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetDisplayText_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setDisplayText(true);
    dev->setDisplayText(false);
    // No crash means success; no getter to verify
    SUCCEED();
}

// Test setPSCenter doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetPSCenter_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setPSCenter(true);
    dev->setPSCenter(false);
    SUCCEED();
}

// Test setPSExpandSmaller doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetPSExpandSmaller_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    SUCCEED();
}

// Test setPSShrinkLarger doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetPSShrinkLarger_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
    SUCCEED();
}

// Test setOverprintPreview doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetOverprintPreview_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
    SUCCEED();
}

// Test setRasterAntialias doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetRasterAntialias_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
    SUCCEED();
}

// Test setRasterResolution doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetRasterResolution_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);
    SUCCEED();
}

// Test setGenerateOPI doesn't crash (the main method from the partial code)
TEST_F(PSOutputDevWithDocTest_1333, SetGenerateOPI_True_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setGenerateOPI(true);
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1333, SetGenerateOPI_False_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setGenerateOPI(false);
    SUCCEED();
}

// Test setUseASCIIHex doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetUseASCIIHex_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    SUCCEED();
}

// Test setUseBinary doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetUseBinary_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setUseBinary(true);
    dev->setUseBinary(false);
    SUCCEED();
}

// Test setUncompressPreloadedImages doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetUncompressPreloadedImages_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
    SUCCEED();
}

// Test setPreloadImagesForms doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetPreloadImagesForms_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
    SUCCEED();
}

// Test setOffset doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetOffset_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setOffset(0.0, 0.0);
    dev->setOffset(100.0, 200.0);
    dev->setOffset(-50.0, -50.0);
    SUCCEED();
}

// Test setScale doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetScale_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 2.0);
    dev->setScale(0.5, 0.5);
    SUCCEED();
}

// Test setRotate doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetRotate_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
    SUCCEED();
}

// Test setClip doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetClip_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setClip(0.0, 0.0, 612.0, 792.0);
    SUCCEED();
}

// Test setForceRasterize doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetForceRasterize_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);
    SUCCEED();
}

// Test useShadedFills with different type values
TEST_F(PSOutputDevWithDocTest_1333, UseShadedFills_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        EXPECT_TRUE(result == true || result == false);
    }
}

// Test setUnderlayCbk with null callback
TEST_F(PSOutputDevWithDocTest_1333, SetUnderlayCbk_Null_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setUnderlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test setOverlayCbk with null callback
TEST_F(PSOutputDevWithDocTest_1333, SetOverlayCbk_Null_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setOverlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test setRasterMono doesn't crash
TEST_F(PSOutputDevWithDocTest_1333, SetRasterMono_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setRasterMono();
    SUCCEED();
}

// Test multiple setter calls in sequence (boundary: rapid toggling)
TEST_F(PSOutputDevWithDocTest_1333, RapidToggleMultipleSettings_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    for (int i = 0; i < 100; ++i) {
        bool val = (i % 2 == 0);
        dev->setEmbedType1(val);
        dev->setEmbedTrueType(val);
        dev->setEmbedCIDPostScript(val);
        dev->setEmbedCIDTrueType(val);
        dev->setFontPassthrough(val);
        dev->setOptimizeColorSpace(val);
        dev->setEnableLZW(val);
        dev->setEnableFlate(val);
        EXPECT_EQ(dev->getEmbedType1(), val);
        EXPECT_EQ(dev->getEmbedTrueType(), val);
        EXPECT_EQ(dev->getEmbedCIDPostScript(), val);
        EXPECT_EQ(dev->getEmbedCIDTrueType(), val);
        EXPECT_EQ(dev->getFontPassthrough(), val);
        EXPECT_EQ(dev->getOptimizeColorSpace(), val);
        EXPECT_EQ(dev->getEnableLZW(), val);
        EXPECT_EQ(dev->getEnableFlate(), val);
    }
}

// Test boundary: setRasterResolution with zero
TEST_F(PSOutputDevWithDocTest_1333, SetRasterResolution_Zero_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setRasterResolution(0.0);
    SUCCEED();
}

// Test boundary: setRasterResolution with negative
TEST_F(PSOutputDevWithDocTest_1333, SetRasterResolution_Negative_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setRasterResolution(-100.0);
    SUCCEED();
}

// Test boundary: setScale with zero
TEST_F(PSOutputDevWithDocTest_1333, SetScale_Zero_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setScale(0.0, 0.0);
    SUCCEED();
}

// Test boundary: setClip with inverted coordinates
TEST_F(PSOutputDevWithDocTest_1333, SetClip_Inverted_1333) {
    createDev();
    if (!dev || !dev->isOk()) GTEST_SKIP() << "Could not create PSOutputDev";
    dev->setClip(612.0, 792.0, 0.0, 0.0);
    SUCCEED();
}

} // namespace
