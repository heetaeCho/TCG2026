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

// Helper: output function that writes to a std::string
static void stringOutputFunc(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1328 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// ===========================================================================
// Tests for setter/getter pairs on embed and configuration flags
// These do not require a fully initialized PSOutputDev with a document,
// but PSOutputDev constructors need a PDFDoc. We'll create a minimal PDF
// in memory to get a valid PSOutputDev, or test the setters that are
// accessible after construction with a file-based constructor.
// 
// Since constructing PSOutputDev properly requires a valid PDFDoc and pages,
// we create a minimal valid PDF file for testing.
// ===========================================================================

class PSOutputDevFlagTest_1328 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF in a temp file
        tmpFileName = std::tmpnam(nullptr);
        if (tmpFileName.empty()) {
            tmpFileName = "/tmp/psoutputdev_test_1328.pdf";
        }
        
        // Minimal PDF content
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

        FILE *f = fopen(tmpFileName.c_str(), "wb");
        if (f) {
            fwrite(minimalPDF, 1, strlen(minimalPDF), f);
            fclose(f);
        }

        doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName.c_str()));
    }

    void TearDown() override {
        psDev.reset();
        doc.reset();
        std::remove(tmpFileName.c_str());
        if (!psOutFileName.empty()) {
            std::remove(psOutFileName.c_str());
        }
    }

    // Helper to create a PSOutputDev with output to a string
    PSOutputDev* createPSOutputDev() {
        if (!doc || !doc->isOk()) {
            return nullptr;
        }
        
        std::vector<int> pages = {1};
        outputBuffer.clear();

        psDev.reset(new PSOutputDev(stringOutputFunc, &outputBuffer,
                                     nullptr, doc.get(), pages,
                                     psModePS, 612, 792,
                                     false, false,
                                     0, 0, 0, 0,
                                     psRasterizeWhenNeeded,
                                     true, nullptr, nullptr,
                                     psLevel2));
        return psDev.get();
    }

    std::string tmpFileName;
    std::string psOutFileName;
    std::unique_ptr<PDFDoc> doc;
    std::unique_ptr<PSOutputDev> psDev;
    std::string outputBuffer;
};

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedType1_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedType1_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedTrueType_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedTrueType_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedCIDPostScript_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedCIDPostScript_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType (the primary focus from the prompt)
TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedCIDTrueType_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetEmbedCIDTrueType_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevFlagTest_1328, SetEmbedCIDTrueType_Toggle_1328) {
    PSOutputDev *dev = createPSOutputDev();
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

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevFlagTest_1328, SetGetFontPassthrough_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetFontPassthrough_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevFlagTest_1328, SetGetOptimizeColorSpace_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetOptimizeColorSpace_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevFlagTest_1328, SetGetPassLevel1CustomColor_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetPassLevel1CustomColor_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevFlagTest_1328, SetGetEnableLZW_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetEnableLZW_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevFlagTest_1328, SetGetEnableFlate_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
}

TEST_F(PSOutputDevFlagTest_1328, SetGetEnableFlate_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test OutputDev interface methods
TEST_F(PSOutputDevFlagTest_1328, UpsideDown_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Just verify it returns a bool without crashing
    bool val = dev->upsideDown();
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, UseDrawChar_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useDrawChar();
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, UseTilingPatternFill_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useTilingPatternFill();
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, UseDrawForm_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useDrawForm();
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, InterpretType3Chars_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->interpretType3Chars();
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, NeedClipToCropBox_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->needClipToCropBox();
    (void)val;
    SUCCEED();
}

// Test useShadedFills with various type values
TEST_F(PSOutputDevFlagTest_1328, UseShadedFills_Type1_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useShadedFills(1);
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, UseShadedFills_Type2_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useShadedFills(2);
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, UseShadedFills_Type3_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = dev->useShadedFills(3);
    (void)val;
    SUCCEED();
}

// Test setDisplayText
TEST_F(PSOutputDevFlagTest_1328, SetDisplayText_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setDisplayText(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetDisplayText_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setDisplayText(false);
    SUCCEED();
}

// Test setPSCenter
TEST_F(PSOutputDevFlagTest_1328, SetPSCenter_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSCenter(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetPSCenter_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSCenter(false);
    SUCCEED();
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevFlagTest_1328, SetPSExpandSmaller_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSExpandSmaller(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetPSExpandSmaller_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSExpandSmaller(false);
    SUCCEED();
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevFlagTest_1328, SetPSShrinkLarger_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSShrinkLarger(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetPSShrinkLarger_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPSShrinkLarger(false);
    SUCCEED();
}

// Test setOverprintPreview
TEST_F(PSOutputDevFlagTest_1328, SetOverprintPreview_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOverprintPreview(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetOverprintPreview_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOverprintPreview(false);
    SUCCEED();
}

// Test setRasterAntialias
TEST_F(PSOutputDevFlagTest_1328, SetRasterAntialias_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterAntialias(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetRasterAntialias_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterAntialias(false);
    SUCCEED();
}

// Test setRasterResolution
TEST_F(PSOutputDevFlagTest_1328, SetRasterResolution_Normal_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterResolution(300.0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetRasterResolution_High_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterResolution(1200.0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetRasterResolution_Low_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterResolution(72.0);
    SUCCEED();
}

// Test setOffset
TEST_F(PSOutputDevFlagTest_1328, SetOffset_Zero_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOffset(0.0, 0.0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetOffset_Positive_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOffset(100.0, 200.0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetOffset_Negative_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOffset(-50.0, -75.0);
    SUCCEED();
}

// Test setScale
TEST_F(PSOutputDevFlagTest_1328, SetScale_Identity_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setScale(1.0, 1.0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetScale_Double_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setScale(2.0, 2.0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetScale_Fractional_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setScale(0.5, 0.5);
    SUCCEED();
}

// Test setRotate
TEST_F(PSOutputDevFlagTest_1328, SetRotate_0_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRotate(0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetRotate_90_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRotate(90);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetRotate_180_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRotate(180);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetRotate_270_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRotate(270);
    SUCCEED();
}

// Test setClip
TEST_F(PSOutputDevFlagTest_1328, SetClip_FullPage_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setClip(0.0, 0.0, 612.0, 792.0);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetClip_SmallRegion_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setClip(100.0, 100.0, 200.0, 200.0);
    SUCCEED();
}

// Test setUnderlayCbk and setOverlayCbk with nullptr
TEST_F(PSOutputDevFlagTest_1328, SetUnderlayCbk_Null_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUnderlayCbk(nullptr, nullptr);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetOverlayCbk_Null_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOverlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test setUnderlayCbk with a real callback
static bool underlayCalled = false;
static void testUnderlayCbk(PSOutputDev *psOut, void *data) {
    underlayCalled = true;
}

TEST_F(PSOutputDevFlagTest_1328, SetUnderlayCbk_Valid_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    underlayCalled = false;
    dev->setUnderlayCbk(testUnderlayCbk, nullptr);
    SUCCEED();
}

// Test setOverlayCbk with a real callback
static bool overlayCalled = false;
static void testOverlayCbk(PSOutputDev *psOut, void *data) {
    overlayCalled = true;
}

TEST_F(PSOutputDevFlagTest_1328, SetOverlayCbk_Valid_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    overlayCalled = false;
    dev->setOverlayCbk(testOverlayCbk, nullptr);
    SUCCEED();
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevFlagTest_1328, SetUncompressPreloadedImages_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUncompressPreloadedImages(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetUncompressPreloadedImages_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUncompressPreloadedImages(false);
    SUCCEED();
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevFlagTest_1328, SetPreloadImagesForms_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPreloadImagesForms(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetPreloadImagesForms_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPreloadImagesForms(false);
    SUCCEED();
}

// Test setGenerateOPI
TEST_F(PSOutputDevFlagTest_1328, SetGenerateOPI_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setGenerateOPI(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetGenerateOPI_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setGenerateOPI(false);
    SUCCEED();
}

// Test setUseASCIIHex
TEST_F(PSOutputDevFlagTest_1328, SetUseASCIIHex_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUseASCIIHex(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetUseASCIIHex_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUseASCIIHex(false);
    SUCCEED();
}

// Test setUseBinary
TEST_F(PSOutputDevFlagTest_1328, SetUseBinary_True_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUseBinary(true);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetUseBinary_False_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUseBinary(false);
    SUCCEED();
}

// Test setRasterMono
TEST_F(PSOutputDevFlagTest_1328, SetRasterMono_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setRasterMono();
    SUCCEED();
}

// Test setForceRasterize
TEST_F(PSOutputDevFlagTest_1328, SetForceRasterize_Never_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setForceRasterize(psNeverRasterize);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetForceRasterize_WhenNeeded_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setForceRasterize(psRasterizeWhenNeeded);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetForceRasterize_Always_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setForceRasterize(psAlwaysRasterize);
    SUCCEED();
}

// Test multiple flag toggling in sequence
TEST_F(PSOutputDevFlagTest_1328, MultipleFlags_Toggle_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }

    dev->setEmbedType1(true);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(true);
    dev->setEnableLZW(false);
    dev->setEnableFlate(true);

    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());

    // Toggle all
    dev->setEmbedType1(false);
    dev->setEmbedTrueType(true);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(true);
    dev->setFontPassthrough(false);
    dev->setEnableLZW(true);
    dev->setEnableFlate(false);

    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_TRUE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    EXPECT_FALSE(dev->getFontPassthrough());
    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test isOk after construction
TEST_F(PSOutputDevFlagTest_1328, IsOk_AfterConstruction_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // With a valid PDF, isOk should return true
    EXPECT_TRUE(dev->isOk());
}

// Test that setProcessColorFormat doesn't crash
TEST_F(PSOutputDevFlagTest_1328, SetProcessColorFormat_Mono8_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setProcessColorFormat(splashModeMono8);
    SUCCEED();
}

TEST_F(PSOutputDevFlagTest_1328, SetProcessColorFormat_RGB8_1328) {
    PSOutputDev *dev = createPSOutputDev();
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setProcessColorFormat(splashModeRGB8);
    SUCCEED();
}
