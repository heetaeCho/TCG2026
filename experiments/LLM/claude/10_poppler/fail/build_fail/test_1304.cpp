#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GooString.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

// Output function for PSOutputDev construction
static void testOutputFunc(void *stream, const char *data, size_t len) {
    // Discard output
}

// Helper to create a minimal PSOutputDev via FoFiOutputFunc constructor
// Returns nullptr if construction fails
static std::unique_ptr<PSOutputDev> createTestPSOutputDev(PDFDoc *doc = nullptr) {
    std::vector<int> pages;
    // Use the FoFiOutputFunc variant with manual control to avoid heavy initialization
    auto dev = std::make_unique<PSOutputDev>(
        testOutputFunc, nullptr, nullptr, doc,
        pages, psModePS, 612, 792,
        false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    return dev;
}

// Callback for testing
static void testUnderlayCbk(PSOutputDev *psOut, void *data) {
    if (data) {
        *static_cast<int*>(data) = 42;
    }
}

static void testOverlayCbk(PSOutputDev *psOut, void *data) {
    if (data) {
        *static_cast<int*>(data) = 99;
    }
}

class PSOutputDevSetterTest_1304 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal test PDF file
        tmpFile = tmpnam(nullptr);
        FILE *f = fopen(tmpFile.c_str(), "w");
        if (f) {
            // Write minimal PDF
            fprintf(f, "%%PDF-1.0\n1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
                       "2 0 obj<</Kids[3 0 R]/Count 1/Type/Pages>>endobj\n"
                       "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
                       "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                       "0000000058 00000 n \n0000000115 00000 n \n"
                       "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%%%EOF\n");
            fclose(f);
        }

        auto *gooStr = new GooString(tmpFile.c_str());
        doc = new PDFDoc(gooStr);

        std::vector<int> pages;
        if (doc->isOk() && doc->getNumPages() > 0) {
            pages.push_back(1);
        }

        psOut = new PSOutputDev(testOutputFunc, nullptr, nullptr, doc,
                                pages, psModePS, 612, 792,
                                false, false, 0, 0, 0, 0,
                                psRasterizeWhenNeeded, true,
                                nullptr, nullptr, psLevel2);
    }

    void TearDown() override {
        delete psOut;
        delete doc;
        if (!tmpFile.empty()) {
            remove(tmpFile.c_str());
        }
    }

    PSOutputDev *psOut = nullptr;
    PDFDoc *doc = nullptr;
    std::string tmpFile;
};

// Test setUnderlayCbk with a valid callback and data
TEST_F(PSOutputDevSetterTest_1304, SetUnderlayCbkWithValidCallback_1304) {
    int callbackData = 0;
    ASSERT_NO_THROW(psOut->setUnderlayCbk(testUnderlayCbk, &callbackData));
}

// Test setUnderlayCbk with nullptr callback
TEST_F(PSOutputDevSetterTest_1304, SetUnderlayCbkWithNullCallback_1304) {
    ASSERT_NO_THROW(psOut->setUnderlayCbk(nullptr, nullptr));
}

// Test setUnderlayCbk with nullptr data but valid callback
TEST_F(PSOutputDevSetterTest_1304, SetUnderlayCbkWithNullData_1304) {
    ASSERT_NO_THROW(psOut->setUnderlayCbk(testUnderlayCbk, nullptr));
}

// Test setOverlayCbk with a valid callback and data
TEST_F(PSOutputDevSetterTest_1304, SetOverlayCbkWithValidCallback_1304) {
    int callbackData = 0;
    ASSERT_NO_THROW(psOut->setOverlayCbk(testOverlayCbk, &callbackData));
}

// Test setOverlayCbk with nullptr
TEST_F(PSOutputDevSetterTest_1304, SetOverlayCbkWithNull_1304) {
    ASSERT_NO_THROW(psOut->setOverlayCbk(nullptr, nullptr));
}

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevSetterTest_1304, SetAndGetEmbedType1_1304) {
    psOut->setEmbedType1(true);
    EXPECT_TRUE(psOut->getEmbedType1());
    psOut->setEmbedType1(false);
    EXPECT_FALSE(psOut->getEmbedType1());
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevSetterTest_1304, SetAndGetEmbedTrueType_1304) {
    psOut->setEmbedTrueType(true);
    EXPECT_TRUE(psOut->getEmbedTrueType());
    psOut->setEmbedTrueType(false);
    EXPECT_FALSE(psOut->getEmbedTrueType());
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevSetterTest_1304, SetAndGetEmbedCIDPostScript_1304) {
    psOut->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOut->getEmbedCIDPostScript());
    psOut->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOut->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevSetterTest_1304, SetAndGetEmbedCIDTrueType_1304) {
    psOut->setEmbedCIDTrueType(true);
    EXPECT_TRUE(psOut->getEmbedCIDTrueType());
    psOut->setEmbedCIDTrueType(false);
    EXPECT_FALSE(psOut->getEmbedCIDTrueType());
}

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevSetterTest_1304, SetAndGetFontPassthrough_1304) {
    psOut->setFontPassthrough(true);
    EXPECT_TRUE(psOut->getFontPassthrough());
    psOut->setFontPassthrough(false);
    EXPECT_FALSE(psOut->getFontPassthrough());
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevSetterTest_1304, SetAndGetOptimizeColorSpace_1304) {
    psOut->setOptimizeColorSpace(true);
    EXPECT_TRUE(psOut->getOptimizeColorSpace());
    psOut->setOptimizeColorSpace(false);
    EXPECT_FALSE(psOut->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevSetterTest_1304, SetAndGetPassLevel1CustomColor_1304) {
    psOut->setPassLevel1CustomColor(true);
    EXPECT_TRUE(psOut->getPassLevel1CustomColor());
    psOut->setPassLevel1CustomColor(false);
    EXPECT_FALSE(psOut->getPassLevel1CustomColor());
}

// Test setEnableLZW and getEnableLZW
TEST_F(PSOutputDevSetterTest_1304, SetAndGetEnableLZW_1304) {
    psOut->setEnableLZW(true);
    EXPECT_TRUE(psOut->getEnableLZW());
    psOut->setEnableLZW(false);
    EXPECT_FALSE(psOut->getEnableLZW());
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevSetterTest_1304, SetAndGetEnableFlate_1304) {
    psOut->setEnableFlate(true);
    EXPECT_TRUE(psOut->getEnableFlate());
    psOut->setEnableFlate(false);
    EXPECT_FALSE(psOut->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevSetterTest_1304, UpsideDown_1304) {
    // Just verify it returns a bool without crashing
    bool result = psOut->upsideDown();
    (void)result;
    SUCCEED();
}

// Test useDrawChar
TEST_F(PSOutputDevSetterTest_1304, UseDrawChar_1304) {
    bool result = psOut->useDrawChar();
    (void)result;
    SUCCEED();
}

// Test interpretType3Chars
TEST_F(PSOutputDevSetterTest_1304, InterpretType3Chars_1304) {
    bool result = psOut->interpretType3Chars();
    (void)result;
    SUCCEED();
}

// Test setDisplayText
TEST_F(PSOutputDevSetterTest_1304, SetDisplayText_1304) {
    ASSERT_NO_THROW(psOut->setDisplayText(true));
    ASSERT_NO_THROW(psOut->setDisplayText(false));
}

// Test setPSCenter
TEST_F(PSOutputDevSetterTest_1304, SetPSCenter_1304) {
    ASSERT_NO_THROW(psOut->setPSCenter(true));
    ASSERT_NO_THROW(psOut->setPSCenter(false));
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevSetterTest_1304, SetPSExpandSmaller_1304) {
    ASSERT_NO_THROW(psOut->setPSExpandSmaller(true));
    ASSERT_NO_THROW(psOut->setPSExpandSmaller(false));
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevSetterTest_1304, SetPSShrinkLarger_1304) {
    ASSERT_NO_THROW(psOut->setPSShrinkLarger(true));
    ASSERT_NO_THROW(psOut->setPSShrinkLarger(false));
}

// Test setOverprintPreview
TEST_F(PSOutputDevSetterTest_1304, SetOverprintPreview_1304) {
    ASSERT_NO_THROW(psOut->setOverprintPreview(true));
    ASSERT_NO_THROW(psOut->setOverprintPreview(false));
}

// Test setRasterAntialias
TEST_F(PSOutputDevSetterTest_1304, SetRasterAntialias_1304) {
    ASSERT_NO_THROW(psOut->setRasterAntialias(true));
    ASSERT_NO_THROW(psOut->setRasterAntialias(false));
}

// Test setRasterResolution
TEST_F(PSOutputDevSetterTest_1304, SetRasterResolution_1304) {
    ASSERT_NO_THROW(psOut->setRasterResolution(300.0));
    ASSERT_NO_THROW(psOut->setRasterResolution(72.0));
    ASSERT_NO_THROW(psOut->setRasterResolution(1200.0));
}

// Test setOffset
TEST_F(PSOutputDevSetterTest_1304, SetOffset_1304) {
    ASSERT_NO_THROW(psOut->setOffset(0.0, 0.0));
    ASSERT_NO_THROW(psOut->setOffset(100.0, 200.0));
    ASSERT_NO_THROW(psOut->setOffset(-50.0, -50.0));
}

// Test setScale
TEST_F(PSOutputDevSetterTest_1304, SetScale_1304) {
    ASSERT_NO_THROW(psOut->setScale(1.0, 1.0));
    ASSERT_NO_THROW(psOut->setScale(2.0, 0.5));
}

// Test setRotate
TEST_F(PSOutputDevSetterTest_1304, SetRotate_1304) {
    ASSERT_NO_THROW(psOut->setRotate(0));
    ASSERT_NO_THROW(psOut->setRotate(90));
    ASSERT_NO_THROW(psOut->setRotate(180));
    ASSERT_NO_THROW(psOut->setRotate(270));
}

// Test setClip
TEST_F(PSOutputDevSetterTest_1304, SetClip_1304) {
    ASSERT_NO_THROW(psOut->setClip(0.0, 0.0, 612.0, 792.0));
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevSetterTest_1304, SetUncompressPreloadedImages_1304) {
    ASSERT_NO_THROW(psOut->setUncompressPreloadedImages(true));
    ASSERT_NO_THROW(psOut->setUncompressPreloadedImages(false));
}

// Test setForceRasterize
TEST_F(PSOutputDevSetterTest_1304, SetForceRasterize_1304) {
    ASSERT_NO_THROW(psOut->setForceRasterize(psRasterizeWhenNeeded));
}

// Test setUseBinary
TEST_F(PSOutputDevSetterTest_1304, SetUseBinary_1304) {
    ASSERT_NO_THROW(psOut->setUseBinary(true));
    ASSERT_NO_THROW(psOut->setUseBinary(false));
}

// Test setUseASCIIHex
TEST_F(PSOutputDevSetterTest_1304, SetUseASCIIHex_1304) {
    ASSERT_NO_THROW(psOut->setUseASCIIHex(true));
    ASSERT_NO_THROW(psOut->setUseASCIIHex(false));
}

// Test setting underlay callback multiple times (overwrite)
TEST_F(PSOutputDevSetterTest_1304, SetUnderlayCbkOverwrite_1304) {
    int data1 = 0;
    int data2 = 0;
    psOut->setUnderlayCbk(testUnderlayCbk, &data1);
    psOut->setUnderlayCbk(testOverlayCbk, &data2);
    // No crash, overwrite should work
    SUCCEED();
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevSetterTest_1304, SetPreloadImagesForms_1304) {
    ASSERT_NO_THROW(psOut->setPreloadImagesForms(true));
    ASSERT_NO_THROW(psOut->setPreloadImagesForms(false));
}

// Test setGenerateOPI
TEST_F(PSOutputDevSetterTest_1304, SetGenerateOPI_1304) {
    ASSERT_NO_THROW(psOut->setGenerateOPI(true));
    ASSERT_NO_THROW(psOut->setGenerateOPI(false));
}

// Test boolean getter/setter toggle consistency for EmbedType1
TEST_F(PSOutputDevSetterTest_1304, EmbedType1ToggleConsistency_1304) {
    psOut->setEmbedType1(false);
    EXPECT_FALSE(psOut->getEmbedType1());
    psOut->setEmbedType1(true);
    EXPECT_TRUE(psOut->getEmbedType1());
    psOut->setEmbedType1(true);
    EXPECT_TRUE(psOut->getEmbedType1());
    psOut->setEmbedType1(false);
    EXPECT_FALSE(psOut->getEmbedType1());
}
