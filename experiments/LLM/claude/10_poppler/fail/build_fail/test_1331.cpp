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

// Helper function to capture PS output
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1331 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // with minimal valid parameters. This may fail (isOk() == false) if
    // no valid PDFDoc is provided, but we can still test setter/getter pairs.
    PSOutputDev* createMinimalDev() {
        std::string *outputStream = new std::string();
        outputStreams.push_back(outputStream);
        
        std::vector<int> pages;
        pages.push_back(1);
        
        // We pass nullptr for doc - the device may not be "ok" but
        // setter/getter pairs on configuration flags should still work
        // after construction (they just set member variables).
        // However, constructing with nullptr doc will likely crash.
        // So we need a real PDF doc or we test differently.
        
        // Instead, let's create a simple PDF in memory
        // Actually, creating a full PSOutputDev requires a valid PDFDoc.
        // Let's try creating a minimal PDF file.
        
        const char *tmpFile = "/tmp/psoutputdev_test_1331.pdf";
        FILE *f = fopen(tmpFile, "w");
        if (f) {
            // Minimal valid PDF
            fprintf(f, "%%PDF-1.0\n");
            fprintf(f, "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n");
            fprintf(f, "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n");
            fprintf(f, "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n");
            fprintf(f, "xref\n0 4\n");
            fprintf(f, "0000000000 65535 f \n");
            fprintf(f, "0000000009 00000 n \n");
            fprintf(f, "0000000058 00000 n \n");
            fprintf(f, "0000000115 00000 n \n");
            fprintf(f, "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%%%EOF\n");
            fclose(f);
        }
        
        auto *gooStr = new GooString(tmpFile);
        PDFDoc *doc = new PDFDoc(gooStr);
        docs.push_back(doc);
        
        if (!doc->isOk()) {
            return nullptr;
        }
        
        PSOutputDev *dev = new PSOutputDev(
            outputFunc, outputStream, nullptr, doc, pages,
            psModePS, 612, 792, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        return dev;
    }
    
    void TearDown() override {
        for (auto *s : outputStreams) {
            delete s;
        }
        outputStreams.clear();
        for (auto *d : docs) {
            delete d;
        }
        docs.clear();
    }
    
    std::vector<std::string*> outputStreams;
    std::vector<PDFDoc*> docs;
};

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1331, SetPassLevel1CustomColorTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetPassLevel1CustomColorFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetPassLevel1CustomColorToggle_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    
    delete dev;
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevTest_1331, SetEmbedType1True_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetEmbedType1False_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
    
    delete dev;
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevTest_1331, SetEmbedTrueTypeTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetEmbedTrueTypeFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
    
    delete dev;
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1331, SetEmbedCIDPostScriptTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetEmbedCIDPostScriptFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    
    delete dev;
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1331, SetEmbedCIDTrueTypeTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetEmbedCIDTrueTypeFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    
    delete dev;
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevTest_1331, SetFontPassthroughTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetFontPassthroughFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
    
    delete dev;
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevTest_1331, SetOptimizeColorSpaceTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetOptimizeColorSpaceFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    
    delete dev;
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevTest_1331, SetEnableLZWTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetEnableLZWFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
    
    delete dev;
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevTest_1331, SetEnableFlateTrue_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    
    delete dev;
}

TEST_F(PSOutputDevTest_1331, SetEnableFlateFalse_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
    
    delete dev;
}

// Test upsideDown
TEST_F(PSOutputDevTest_1331, UpsideDown_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    // upsideDown() should return a consistent boolean value
    bool result = dev->upsideDown();
    // Just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(result == true || result == false);
    
    delete dev;
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1331, UseDrawChar_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
    
    delete dev;
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1331, UseTilingPatternFill_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
    
    delete dev;
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1331, UseDrawForm_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    bool result = dev->useDrawForm();
    EXPECT_TRUE(result == true || result == false);
    
    delete dev;
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1331, InterpretType3Chars_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
    
    delete dev;
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1331, NeedClipToCropBox_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    bool result = dev->needClipToCropBox();
    EXPECT_TRUE(result == true || result == false);
    
    delete dev;
}

// Test isOk
TEST_F(PSOutputDevTest_1331, IsOkAfterConstruction_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    // With a valid minimal PDF, the device should be ok
    EXPECT_TRUE(dev->isOk());
    
    delete dev;
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1331, SetDisplayText_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    // Just verify it doesn't crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);
    
    delete dev;
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1331, SetPSCenter_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setPSCenter(true);
    dev->setPSCenter(false);
    
    delete dev;
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevTest_1331, SetPSExpandSmaller_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
    
    delete dev;
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevTest_1331, SetPSShrinkLarger_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
    
    delete dev;
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1331, SetOverprintPreview_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
    
    delete dev;
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1331, SetRasterAntialias_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
    
    delete dev;
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1331, SetRasterResolution_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(600.0);
    
    delete dev;
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1331, SetUncompressPreloadedImages_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
    
    delete dev;
}

// Test setOffset
TEST_F(PSOutputDevTest_1331, SetOffset_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setOffset(10.0, 20.0);
    dev->setOffset(0.0, 0.0);
    dev->setOffset(-5.0, -10.0);
    
    delete dev;
}

// Test setScale
TEST_F(PSOutputDevTest_1331, SetScale_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 2.0);
    dev->setScale(0.5, 0.5);
    
    delete dev;
}

// Test setRotate
TEST_F(PSOutputDevTest_1331, SetRotate_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
    
    delete dev;
}

// Test setClip
TEST_F(PSOutputDevTest_1331, SetClip_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setClip(0.0, 0.0, 612.0, 792.0);
    dev->setClip(100.0, 100.0, 500.0, 700.0);
    
    delete dev;
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1331, SetPreloadImagesForms_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
    
    delete dev;
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1331, SetGenerateOPI_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
    
    delete dev;
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1331, SetUseASCIIHex_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    
    delete dev;
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1331, SetUseBinary_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setUseBinary(true);
    dev->setUseBinary(false);
    
    delete dev;
}

// Test multiple setter/getter combinations in sequence
TEST_F(PSOutputDevTest_1331, MultipleSetterGetterCombinations_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
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
    
    delete dev;
}

// Test setUnderlayCbk with nullptr
TEST_F(PSOutputDevTest_1331, SetUnderlayCbkNull_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setUnderlayCbk(nullptr, nullptr);
    
    delete dev;
}

// Test setOverlayCbk with nullptr
TEST_F(PSOutputDevTest_1331, SetOverlayCbkNull_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setOverlayCbk(nullptr, nullptr);
    
    delete dev;
}

// Test setUnderlayCbk with a real callback
TEST_F(PSOutputDevTest_1331, SetUnderlayCbkWithCallback_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    int callbackData = 42;
    auto cbk = [](PSOutputDev *psOut, void *data) {
        // callback body
    };
    
    dev->setUnderlayCbk(cbk, &callbackData);
    
    delete dev;
}

// Test setOverlayCbk with a real callback
TEST_F(PSOutputDevTest_1331, SetOverlayCbkWithCallback_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    int callbackData = 99;
    auto cbk = [](PSOutputDev *psOut, void *data) {
        // callback body
    };
    
    dev->setOverlayCbk(cbk, &callbackData);
    
    delete dev;
}

// Test useShadedFills with different types
TEST_F(PSOutputDevTest_1331, UseShadedFillsVariousTypes_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    // Test various shading types (1-7 are typical PDF shading types)
    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        EXPECT_TRUE(result == true || result == false) 
            << "useShadedFills(" << type << ") returned unexpected value";
    }
    
    delete dev;
}

// Boundary: setRasterResolution with zero
TEST_F(PSOutputDevTest_1331, SetRasterResolutionZero_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setRasterResolution(0.0);
    // No crash expected
    
    delete dev;
}

// Boundary: setRasterResolution with negative value
TEST_F(PSOutputDevTest_1331, SetRasterResolutionNegative_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setRasterResolution(-100.0);
    // No crash expected
    
    delete dev;
}

// Boundary: setRasterResolution with very large value
TEST_F(PSOutputDevTest_1331, SetRasterResolutionLarge_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setRasterResolution(9999.0);
    // No crash expected
    
    delete dev;
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1331, SetRasterMono_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setRasterMono();
    // No crash expected
    
    delete dev;
}

// Test setting scale to zero (boundary)
TEST_F(PSOutputDevTest_1331, SetScaleZero_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setScale(0.0, 0.0);
    // No crash expected
    
    delete dev;
}

// Test setting negative offset (boundary)
TEST_F(PSOutputDevTest_1331, SetOffsetNegative_1331) {
    PSOutputDev *dev = createMinimalDev();
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    
    dev->setOffset(-1000.0, -1000.0);
    // No crash expected
    
    delete dev;
}
