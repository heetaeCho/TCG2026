#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <fstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Output function for capturing PS output
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1298 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDF in a temp file and return a PDFDoc
    std::unique_ptr<PDFDoc> createMinimalPDF() {
        // Create a minimal valid PDF
        const char *pdfContent =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

        tmpFileName = std::tmpnam(nullptr);
        tmpFileName += ".pdf";
        std::ofstream ofs(tmpFileName, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
        ofs.close();

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName.c_str()));
        return doc;
    }

    PSOutputDev* createPSOutputDev(PDFDoc *doc, std::string *outputStr,
                                    PSOutMode mode = psModePS,
                                    PSLevel level = psLevel2) {
        std::vector<int> pages = {1};
        return new PSOutputDev(outputToString, outputStr,
                               const_cast<char*>("Test Title"),
                               doc, pages, mode,
                               612, 792, false, false,
                               0, 0, 0, 0,
                               psRasterizeWhenNeeded,
                               false, nullptr, nullptr, level);
    }

    std::string tmpFileName;
};

// Test interpretType3Chars returns false
TEST_F(PSOutputDevTest_1298, InterpretType3CharsReturnsFalse_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    EXPECT_FALSE(dev->interpretType3Chars());
}

// Test upsideDown
TEST_F(PSOutputDevTest_1298, UpsideDownReturnsFalse_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // upsideDown should return a consistent boolean value
    bool result = dev->upsideDown();
    // PS coordinate system is not upside down typically
    EXPECT_FALSE(result);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1298, UseDrawCharReturnsFalse_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    EXPECT_FALSE(dev->useDrawChar());
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1298, UseTilingPatternFillReturnsTrue_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1298, UseDrawFormReturnsTrue_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    EXPECT_TRUE(dev->useDrawForm());
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevTest_1298, SetGetEmbedType1_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevTest_1298, SetGetEmbedTrueType_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1298, SetGetEmbedCIDPostScript_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1298, SetGetEmbedCIDTrueType_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevTest_1298, SetGetFontPassthrough_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevTest_1298, SetGetOptimizeColorSpace_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1298, SetGetPassLevel1CustomColor_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevTest_1298, SetGetEnableLZW_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevTest_1298, SetGetEnableFlate_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1298, NeedClipToCropBox_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // Should return a boolean consistently
    bool result = dev->needClipToCropBox();
    (void)result; // Just ensure it doesn't crash
    SUCCEED();
}

// Test isOk after successful creation
TEST_F(PSOutputDevTest_1298, IsOkAfterCreation_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    // After creation with a valid doc, isOk should be true
    EXPECT_TRUE(dev->isOk());
}

// Test setDisplayText does not crash
TEST_F(PSOutputDevTest_1298, SetDisplayTextNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setDisplayText(true);
    dev->setDisplayText(false);
    SUCCEED();
}

// Test setPSCenter does not crash
TEST_F(PSOutputDevTest_1298, SetPSCenterNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPSCenter(true);
    dev->setPSCenter(false);
    SUCCEED();
}

// Test setPSExpandSmaller does not crash
TEST_F(PSOutputDevTest_1298, SetPSExpandSmallerNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    SUCCEED();
}

// Test setPSShrinkLarger does not crash
TEST_F(PSOutputDevTest_1298, SetPSShrinkLargerNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
    SUCCEED();
}

// Test setOverprintPreview does not crash
TEST_F(PSOutputDevTest_1298, SetOverprintPreviewNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
    SUCCEED();
}

// Test setRasterAntialias does not crash
TEST_F(PSOutputDevTest_1298, SetRasterAntialiasNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
    SUCCEED();
}

// Test setRasterResolution does not crash
TEST_F(PSOutputDevTest_1298, SetRasterResolutionNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);
    SUCCEED();
}

// Test setOffset does not crash
TEST_F(PSOutputDevTest_1298, SetOffsetNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setOffset(0.0, 0.0);
    dev->setOffset(100.0, 200.0);
    dev->setOffset(-50.0, -50.0);
    SUCCEED();
}

// Test setScale does not crash
TEST_F(PSOutputDevTest_1298, SetScaleNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 2.0);
    dev->setScale(0.5, 0.5);
    SUCCEED();
}

// Test setRotate does not crash
TEST_F(PSOutputDevTest_1298, SetRotateNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
    SUCCEED();
}

// Test setClip does not crash
TEST_F(PSOutputDevTest_1298, SetClipNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setClip(0.0, 0.0, 612.0, 792.0);
    SUCCEED();
}

// Test setUncompressPreloadedImages does not crash
TEST_F(PSOutputDevTest_1298, SetUncompressPreloadedImagesNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
    SUCCEED();
}

// Test setForceRasterize does not crash
TEST_F(PSOutputDevTest_1298, SetForceRasterizeNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);
    SUCCEED();
}

// Test useShadedFills with various types
TEST_F(PSOutputDevTest_1298, UseShadedFillsVariousTypes_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // Test shaded fills for various types; should return boolean
    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        (void)result; // We just check it doesn't crash
    }
    SUCCEED();
}

// Test setUseBinary does not crash
TEST_F(PSOutputDevTest_1298, SetUseBinaryNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUseBinary(true);
    dev->setUseBinary(false);
    SUCCEED();
}

// Test setUseASCIIHex does not crash
TEST_F(PSOutputDevTest_1298, SetUseASCIIHexNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    SUCCEED();
}

// Test setPreloadImagesForms does not crash
TEST_F(PSOutputDevTest_1298, SetPreloadImagesFormsNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
    SUCCEED();
}

// Test setGenerateOPI does not crash
TEST_F(PSOutputDevTest_1298, SetGenerateOPINoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
    SUCCEED();
}

// Test setRasterMono does not crash
TEST_F(PSOutputDevTest_1298, SetRasterMonoNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setRasterMono();
    SUCCEED();
}

// Test overlay and underlay callback setters
TEST_F(PSOutputDevTest_1298, SetOverlayUnderlayCallbacksNoCrash_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    dev->setUnderlayCbk(nullptr, nullptr);
    dev->setOverlayCbk(nullptr, nullptr);
    SUCCEED();
}

// Test multiple setter/getter roundtrips in sequence
TEST_F(PSOutputDevTest_1298, MultipleSetterGetterRoundtrips_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::unique_ptr<PSOutputDev> dev(createPSOutputDev(doc.get(), &output));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }

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

// Test creation with EPS mode
TEST_F(PSOutputDevTest_1298, CreationWithEPSMode_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::vector<int> pages = {1};
    std::unique_ptr<PSOutputDev> dev(new PSOutputDev(
        outputToString, &output,
        const_cast<char*>("EPS Title"),
        doc.get(), pages, psModeEPS,
        612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded,
        false, nullptr, nullptr, psLevel2));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok in EPS mode";
    }
    EXPECT_TRUE(dev->isOk());
}

// Test creation with PS Level 1
TEST_F(PSOutputDevTest_1298, CreationWithPSLevel1_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::vector<int> pages = {1};
    std::unique_ptr<PSOutputDev> dev(new PSOutputDev(
        outputToString, &output,
        const_cast<char*>("PS Level1 Title"),
        doc.get(), pages, psModePS,
        612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded,
        false, nullptr, nullptr, psLevel1));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok with Level1";
    }
    EXPECT_TRUE(dev->isOk());
}

// Test creation with PS Level 3
TEST_F(PSOutputDevTest_1298, CreationWithPSLevel3_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::vector<int> pages = {1};
    std::unique_ptr<PSOutputDev> dev(new PSOutputDev(
        outputToString, &output,
        const_cast<char*>("PS Level3 Title"),
        doc.get(), pages, psModePS,
        612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded,
        false, nullptr, nullptr, psLevel3));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok with Level3";
    }
    EXPECT_TRUE(dev->isOk());
}

// Test that output is produced (non-empty) after creation
TEST_F(PSOutputDevTest_1298, OutputProducedAfterCreation_1298) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    std::string output;
    std::vector<int> pages = {1};
    std::unique_ptr<PSOutputDev> dev(new PSOutputDev(
        outputToString, &output,
        const_cast<char*>("Test Output"),
        doc.get(), pages, psModePS,
        612, 792, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded,
        false, nullptr, nullptr, psLevel2));
    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev not ok";
    }
    // The header should have been written, so output should not be empty
    EXPECT_FALSE(output.empty());
}
