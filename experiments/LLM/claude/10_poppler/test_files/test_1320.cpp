#include <gtest/gtest.h>
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
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1320 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        outputData.clear();
    }

    // Helper to create a PSOutputDev if we have a valid doc
    // Since creating a full PDFDoc is complex, some tests may be skipped
    std::string outputData;
};

// Test that requires a valid PDF document for full construction
// We'll create a minimal PDF in memory or from a temp file

class PSOutputDevWithDocTest_1320 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        outputData.clear();
        
        // Create a minimal PDF file
        const char *minimalPDF = 
            "%PDF-1.0\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n196\n%%EOF\n";

        tmpFileName = std::tmpnam(nullptr);
        FILE *f = fopen(tmpFileName.c_str(), "wb");
        if (f) {
            fwrite(minimalPDF, 1, strlen(minimalPDF), f);
            fclose(f);
        }

        auto *fname = new GooString(tmpFileName.c_str());
        doc = new PDFDoc(fname);
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
        delete doc;
        doc = nullptr;
        if (!tmpFileName.empty()) {
            remove(tmpFileName.c_str());
        }
    }

    PSOutputDev *createDev(PSOutMode mode = psModePS, bool manualCtrl = true) {
        if (!doc || !doc->isOk()) return nullptr;
        std::vector<int> pages = {1};
        dev = new PSOutputDev(outputToString, &outputData, 
                              const_cast<char*>("Test"),
                              doc, pages, mode,
                              612, 792, false, false,
                              0, 0, 612, 792,
                              psRasterizeWhenNeeded, manualCtrl,
                              nullptr, nullptr, psLevel2);
        return dev;
    }

    std::string outputData;
    std::string tmpFileName;
    PDFDoc *doc = nullptr;
    PSOutputDev *dev = nullptr;
};

// Test getFontPassthrough default and setter
TEST_F(PSOutputDevWithDocTest_1320, GetFontPassthrough_Default_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Default value - just check it returns a bool
    bool val = d->getFontPassthrough();
    // The default is determined by globalParams, just verify it's accessible
    (void)val;
    SUCCEED();
}

TEST_F(PSOutputDevWithDocTest_1320, SetFontPassthrough_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setFontPassthrough(true);
    EXPECT_TRUE(d->getFontPassthrough());
}

TEST_F(PSOutputDevWithDocTest_1320, SetFontPassthrough_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setFontPassthrough(false);
    EXPECT_FALSE(d->getFontPassthrough());
}

TEST_F(PSOutputDevWithDocTest_1320, SetFontPassthrough_Toggle_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setFontPassthrough(true);
    EXPECT_TRUE(d->getFontPassthrough());
    d->setFontPassthrough(false);
    EXPECT_FALSE(d->getFontPassthrough());
    d->setFontPassthrough(true);
    EXPECT_TRUE(d->getFontPassthrough());
}

// Test getEmbedType1 / setEmbedType1
TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedType1_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedType1(true);
    EXPECT_TRUE(d->getEmbedType1());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedType1_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedType1(false);
    EXPECT_FALSE(d->getEmbedType1());
}

// Test getEmbedTrueType / setEmbedTrueType
TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedTrueType_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedTrueType(true);
    EXPECT_TRUE(d->getEmbedTrueType());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedTrueType_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedTrueType(false);
    EXPECT_FALSE(d->getEmbedTrueType());
}

// Test getEmbedCIDPostScript / setEmbedCIDPostScript
TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedCIDPostScript_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedCIDPostScript(true);
    EXPECT_TRUE(d->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedCIDPostScript_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedCIDPostScript(false);
    EXPECT_FALSE(d->getEmbedCIDPostScript());
}

// Test getEmbedCIDTrueType / setEmbedCIDTrueType
TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedCIDTrueType_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedCIDTrueType(true);
    EXPECT_TRUE(d->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetEmbedCIDTrueType_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEmbedCIDTrueType(false);
    EXPECT_FALSE(d->getEmbedCIDTrueType());
}

// Test getOptimizeColorSpace / setOptimizeColorSpace
TEST_F(PSOutputDevWithDocTest_1320, SetGetOptimizeColorSpace_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setOptimizeColorSpace(true);
    EXPECT_TRUE(d->getOptimizeColorSpace());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetOptimizeColorSpace_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setOptimizeColorSpace(false);
    EXPECT_FALSE(d->getOptimizeColorSpace());
}

// Test getPassLevel1CustomColor / setPassLevel1CustomColor
TEST_F(PSOutputDevWithDocTest_1320, SetGetPassLevel1CustomColor_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setPassLevel1CustomColor(true);
    EXPECT_TRUE(d->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetPassLevel1CustomColor_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setPassLevel1CustomColor(false);
    EXPECT_FALSE(d->getPassLevel1CustomColor());
}

// Test getEnableLZW / setEnableLZW
TEST_F(PSOutputDevWithDocTest_1320, SetGetEnableLZW_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEnableLZW(true);
    EXPECT_TRUE(d->getEnableLZW());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetEnableLZW_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEnableLZW(false);
    EXPECT_FALSE(d->getEnableLZW());
}

// Test getEnableFlate / setEnableFlate
TEST_F(PSOutputDevWithDocTest_1320, SetGetEnableFlate_True_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEnableFlate(true);
    EXPECT_TRUE(d->getEnableFlate());
}

TEST_F(PSOutputDevWithDocTest_1320, SetGetEnableFlate_False_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setEnableFlate(false);
    EXPECT_FALSE(d->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevWithDocTest_1320, UpsideDown_ReturnsFalse_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // PostScript coordinate system is not upside down
    EXPECT_FALSE(d->upsideDown());
}

// Test useDrawChar
TEST_F(PSOutputDevWithDocTest_1320, UseDrawChar_ReturnsFalse_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_FALSE(d->useDrawChar());
}

// Test useTilingPatternFill
TEST_F(PSOutputDevWithDocTest_1320, UseTilingPatternFill_ReturnsTrue_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_TRUE(d->useTilingPatternFill());
}

// Test useDrawForm
TEST_F(PSOutputDevWithDocTest_1320, UseDrawForm_ReturnsTrue_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_TRUE(d->useDrawForm());
}

// Test interpretType3Chars
TEST_F(PSOutputDevWithDocTest_1320, InterpretType3Chars_ReturnsBool_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Just check it returns without error
    bool val = d->interpretType3Chars();
    (void)val;
    SUCCEED();
}

// Test isOk
TEST_F(PSOutputDevWithDocTest_1320, IsOk_AfterConstruction_1320) {
    auto *d = createDev();
    if (!d) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // With a valid (or at least parseable) PDF, isOk should be true
    EXPECT_TRUE(d->isOk());
}

// Test setDisplayText
TEST_F(PSOutputDevWithDocTest_1320, SetDisplayText_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Just verify it doesn't crash
    d->setDisplayText(true);
    d->setDisplayText(false);
    SUCCEED();
}

// Test setPSCenter
TEST_F(PSOutputDevWithDocTest_1320, SetPSCenter_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setPSCenter(true);
    d->setPSCenter(false);
    SUCCEED();
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevWithDocTest_1320, SetPSExpandSmaller_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setPSExpandSmaller(true);
    d->setPSExpandSmaller(false);
    SUCCEED();
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevWithDocTest_1320, SetPSShrinkLarger_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setPSShrinkLarger(true);
    d->setPSShrinkLarger(false);
    SUCCEED();
}

// Test setOverprintPreview
TEST_F(PSOutputDevWithDocTest_1320, SetOverprintPreview_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setOverprintPreview(true);
    d->setOverprintPreview(false);
    SUCCEED();
}

// Test setRasterAntialias
TEST_F(PSOutputDevWithDocTest_1320, SetRasterAntialias_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setRasterAntialias(true);
    d->setRasterAntialias(false);
    SUCCEED();
}

// Test setRasterResolution
TEST_F(PSOutputDevWithDocTest_1320, SetRasterResolution_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setRasterResolution(300.0);
    d->setRasterResolution(72.0);
    d->setRasterResolution(1200.0);
    SUCCEED();
}

// Test setOffset
TEST_F(PSOutputDevWithDocTest_1320, SetOffset_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setOffset(10.0, 20.0);
    d->setOffset(0.0, 0.0);
    d->setOffset(-5.0, -10.0);
    SUCCEED();
}

// Test setScale
TEST_F(PSOutputDevWithDocTest_1320, SetScale_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setScale(1.0, 1.0);
    d->setScale(2.0, 2.0);
    d->setScale(0.5, 0.5);
    SUCCEED();
}

// Test setRotate
TEST_F(PSOutputDevWithDocTest_1320, SetRotate_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setRotate(0);
    d->setRotate(90);
    d->setRotate(180);
    d->setRotate(270);
    SUCCEED();
}

// Test setClip
TEST_F(PSOutputDevWithDocTest_1320, SetClip_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setClip(0.0, 0.0, 612.0, 792.0);
    d->setClip(100.0, 100.0, 500.0, 700.0);
    SUCCEED();
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevWithDocTest_1320, SetUncompressPreloadedImages_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setUncompressPreloadedImages(true);
    d->setUncompressPreloadedImages(false);
    SUCCEED();
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevWithDocTest_1320, SetPreloadImagesForms_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setPreloadImagesForms(true);
    d->setPreloadImagesForms(false);
    SUCCEED();
}

// Test setGenerateOPI
TEST_F(PSOutputDevWithDocTest_1320, SetGenerateOPI_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setGenerateOPI(true);
    d->setGenerateOPI(false);
    SUCCEED();
}

// Test setUseASCIIHex
TEST_F(PSOutputDevWithDocTest_1320, SetUseASCIIHex_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setUseASCIIHex(true);
    d->setUseASCIIHex(false);
    SUCCEED();
}

// Test setUseBinary
TEST_F(PSOutputDevWithDocTest_1320, SetUseBinary_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setUseBinary(true);
    d->setUseBinary(false);
    SUCCEED();
}

// Test setForceRasterize
TEST_F(PSOutputDevWithDocTest_1320, SetForceRasterize_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setForceRasterize(psRasterizeWhenNeeded);
    d->setForceRasterize(psAlwaysRasterize);
    d->setForceRasterize(psNeverRasterize);
    SUCCEED();
}

// Test multiple setter/getter round trips
TEST_F(PSOutputDevWithDocTest_1320, MultipleSettersGetters_Consistency_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }

    d->setEmbedType1(true);
    d->setEmbedTrueType(false);
    d->setEmbedCIDPostScript(true);
    d->setEmbedCIDTrueType(false);
    d->setFontPassthrough(true);
    d->setOptimizeColorSpace(false);
    d->setEnableLZW(true);
    d->setEnableFlate(false);

    EXPECT_TRUE(d->getEmbedType1());
    EXPECT_FALSE(d->getEmbedTrueType());
    EXPECT_TRUE(d->getEmbedCIDPostScript());
    EXPECT_FALSE(d->getEmbedCIDTrueType());
    EXPECT_TRUE(d->getFontPassthrough());
    EXPECT_FALSE(d->getOptimizeColorSpace());
    EXPECT_TRUE(d->getEnableLZW());
    EXPECT_FALSE(d->getEnableFlate());
}

// Test needClipToCropBox
TEST_F(PSOutputDevWithDocTest_1320, NeedClipToCropBox_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    bool val = d->needClipToCropBox();
    (void)val;
    SUCCEED();
}

// Test useShadedFills for various types
TEST_F(PSOutputDevWithDocTest_1320, UseShadedFills_VariousTypes_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    for (int type = 1; type <= 7; ++type) {
        bool val = d->useShadedFills(type);
        (void)val;
    }
    SUCCEED();
}

// Test underlay callback setter
TEST_F(PSOutputDevWithDocTest_1320, SetUnderlayCbk_NullCallback_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setUnderlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test overlay callback setter
TEST_F(PSOutputDevWithDocTest_1320, SetOverlayCbk_NullCallback_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setOverlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test overlay callback setter with actual callback
static bool overlayCalled = false;
static void overlayCallback(PSOutputDev *psOut, void *data) {
    overlayCalled = true;
}

TEST_F(PSOutputDevWithDocTest_1320, SetOverlayCbk_WithCallback_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    overlayCalled = false;
    int dummyData = 42;
    d->setOverlayCbk(overlayCallback, &dummyData);
    // We can't easily trigger the overlay callback without going through
    // the full page rendering pipeline, so just verify setting doesn't crash
    SUCCEED();
}

// Boundary: setScale with zero
TEST_F(PSOutputDevWithDocTest_1320, SetScale_Zero_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setScale(0.0, 0.0);
    SUCCEED();
}

// Boundary: setScale with negative values
TEST_F(PSOutputDevWithDocTest_1320, SetScale_Negative_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setScale(-1.0, -1.0);
    SUCCEED();
}

// Test setRasterMono
TEST_F(PSOutputDevWithDocTest_1320, SetRasterMono_1320) {
    auto *d = createDev();
    if (!d || !d->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    d->setRasterMono();
    SUCCEED();
}
