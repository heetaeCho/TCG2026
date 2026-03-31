#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Output function that collects PS output into a string
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1316 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with a FoFiOutputFunc writing to a string
    // Returns nullptr if creation fails (e.g., no valid PDF)
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, std::string &output, 
                                                     std::vector<int> pages = {1},
                                                     PSOutMode mode = psModePS,
                                                     bool manualCtrl = true) {
        char title[] = "Test";
        auto dev = std::make_unique<PSOutputDev>(
            outputToString, &output, title, doc, pages,
            mode, -1, -1, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, manualCtrl,
            nullptr, nullptr, psLevel2);
        if (dev && dev->isOk()) {
            return dev;
        }
        return nullptr;
    }

    // Create a minimal valid PDF in memory
    std::unique_ptr<PDFDoc> createMinimalPDF() {
        // Minimal PDF content
        static const char *pdfContent =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

        int len = strlen(pdfContent);
        auto *stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        if (doc->isOk()) {
            return doc;
        }
        return nullptr;
    }
};

// Test getEmbedType1 / setEmbedType1
TEST_F(PSOutputDevTest_1316, GetSetEmbedType1_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test getEmbedTrueType / setEmbedTrueType
TEST_F(PSOutputDevTest_1316, GetSetEmbedTrueType_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test getEmbedCIDPostScript / setEmbedCIDPostScript
TEST_F(PSOutputDevTest_1316, GetSetEmbedCIDPostScript_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test getEmbedCIDTrueType / setEmbedCIDTrueType
TEST_F(PSOutputDevTest_1316, GetSetEmbedCIDTrueType_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test getFontPassthrough / setFontPassthrough
TEST_F(PSOutputDevTest_1316, GetSetFontPassthrough_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test getOptimizeColorSpace / setOptimizeColorSpace
TEST_F(PSOutputDevTest_1316, GetSetOptimizeColorSpace_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test getPassLevel1CustomColor / setPassLevel1CustomColor
TEST_F(PSOutputDevTest_1316, GetSetPassLevel1CustomColor_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test getEnableLZW / setEnableLZW
TEST_F(PSOutputDevTest_1316, GetSetEnableLZW_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test getEnableFlate / setEnableFlate
TEST_F(PSOutputDevTest_1316, GetSetEnableFlate_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevTest_1316, UpsideDown_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    // upsideDown should return a consistent boolean value
    bool result = dev->upsideDown();
    // PSOutputDev typically returns false for upsideDown
    EXPECT_FALSE(result);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1316, UseDrawChar_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    bool result = dev->useDrawChar();
    EXPECT_FALSE(result);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1316, UseTilingPatternFill_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1316, UseDrawForm_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    bool result = dev->useDrawForm();
    EXPECT_TRUE(result);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1316, InterpretType3Chars_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    bool result = dev->interpretType3Chars();
    // Should return a boolean
    (void)result;
    SUCCEED();
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1316, SetDisplayText_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    // Should not crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);
    SUCCEED();
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1316, SetPSCenter_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setPSCenter(true);
    dev->setPSCenter(false);
    SUCCEED();
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1316, SetPSExpandSmallerAndShrinkLarger_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
    SUCCEED();
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1316, SetOverprintPreview_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
    SUCCEED();
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1316, SetRasterAntialias_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
    SUCCEED();
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1316, SetRasterResolution_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);
    SUCCEED();
}

// Test setOffset
TEST_F(PSOutputDevTest_1316, SetOffset_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setOffset(0.0, 0.0);
    dev->setOffset(100.0, 200.0);
    dev->setOffset(-50.0, -50.0);
    SUCCEED();
}

// Test setScale
TEST_F(PSOutputDevTest_1316, SetScale_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 0.5);
    SUCCEED();
}

// Test setRotate
TEST_F(PSOutputDevTest_1316, SetRotate_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
    SUCCEED();
}

// Test setClip
TEST_F(PSOutputDevTest_1316, SetClip_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setClip(0.0, 0.0, 612.0, 792.0);
    SUCCEED();
}

// Test setUnderlayCbk
TEST_F(PSOutputDevTest_1316, SetUnderlayCbk_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setUnderlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test setOverlayCbk
TEST_F(PSOutputDevTest_1316, SetOverlayCbk_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setOverlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test toggle EmbedType1 multiple times
TEST_F(PSOutputDevTest_1316, ToggleEmbedType1Multiple_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    for (int i = 0; i < 10; i++) {
        bool val = (i % 2 == 0);
        dev->setEmbedType1(val);
        EXPECT_EQ(val, dev->getEmbedType1()) << "Iteration " << i;
    }
}

// Test setForceRasterize
TEST_F(PSOutputDevTest_1316, SetForceRasterize_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);
    SUCCEED();
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1316, SetUncompressPreloadedImages_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
    SUCCEED();
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1316, SetPreloadImagesForms_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
    SUCCEED();
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1316, SetGenerateOPI_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
    SUCCEED();
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1316, SetUseASCIIHex_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    SUCCEED();
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1316, SetUseBinary_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setUseBinary(true);
    dev->setUseBinary(false);
    SUCCEED();
}

// Test useShadedFills with various types
TEST_F(PSOutputDevTest_1316, UseShadedFills_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    // Test with different shading types (1-7 are standard PDF shading types)
    for (int type = 1; type <= 7; type++) {
        bool result = dev->useShadedFills(type);
        (void)result; // Just check it doesn't crash
    }
    SUCCEED();
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1316, NeedClipToCropBox_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    bool result = dev->needClipToCropBox();
    (void)result;
    SUCCEED();
}

// Test isOk returns true for properly constructed device
TEST_F(PSOutputDevTest_1316, IsOkAfterConstruction_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    
    char title[] = "Test";
    std::vector<int> pages = {1};
    PSOutputDev dev(outputToString, &output, title, doc.get(), pages,
                    psModePS, -1, -1, false, false,
                    0, 0, 0, 0,
                    psRasterizeWhenNeeded, true,
                    nullptr, nullptr, psLevel2);
    
    EXPECT_TRUE(dev.isOk());
}

// Test setRasterMono doesn't crash
TEST_F(PSOutputDevTest_1316, SetRasterMono_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setRasterMono();
    SUCCEED();
}

// Test all boolean getters return consistent values after setting
TEST_F(PSOutputDevTest_1316, AllBooleanGettersConsistency_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    // Set all to true
    dev->setEmbedType1(true);
    dev->setEmbedTrueType(true);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(true);
    dev->setFontPassthrough(true);
    dev->setOptimizeColorSpace(true);
    dev->setPassLevel1CustomColor(true);
    dev->setEnableLZW(true);
    dev->setEnableFlate(true);

    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_TRUE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());

    // Set all to false
    dev->setEmbedType1(false);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(false);
    dev->setOptimizeColorSpace(false);
    dev->setPassLevel1CustomColor(false);
    dev->setEnableLZW(false);
    dev->setEnableFlate(false);

    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_FALSE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test setting boundary values for raster resolution
TEST_F(PSOutputDevTest_1316, SetRasterResolutionBoundary_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setRasterResolution(0.0);
    dev->setRasterResolution(1.0);
    dev->setRasterResolution(9999.0);
    SUCCEED();
}

// Test setOffset with zero values
TEST_F(PSOutputDevTest_1316, SetOffsetZero_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setOffset(0.0, 0.0);
    SUCCEED();
}

// Test setScale with extreme values
TEST_F(PSOutputDevTest_1316, SetScaleExtremeValues_1316) {
    std::string output;
    auto doc = createMinimalPDF();
    if (!doc) GTEST_SKIP() << "Could not create minimal PDF";
    auto dev = createPSOutputDev(doc.get(), output);
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev";

    dev->setScale(0.001, 0.001);
    dev->setScale(1000.0, 1000.0);
    SUCCEED();
}
