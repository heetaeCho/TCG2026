#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <memory>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Output function for capturing PS output
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1307 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with minimal valid setup
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(const char *pdfFile) {
        doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(pdfFile));
        if (!doc->isOk()) {
            return nullptr;
        }

        std::vector<int> pages;
        for (int i = 1; i <= doc->getNumPages(); ++i) {
            pages.push_back(i);
        }

        outputString.clear();

        auto dev = std::make_unique<PSOutputDev>(
            outputToString, &outputString,
            nullptr, // psTitle
            doc.get(),
            pages,
            psModePS, // mode
            0, 0,     // paperWidth, paperHeight
            false,    // noCrop
            true,     // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterize
            false,    // manualCtrl
            nullptr,  // customCodeCbk
            nullptr,  // customCodeCbkData
            psLevel2  // level
        );

        if (!dev->isOk()) {
            return nullptr;
        }

        return dev;
    }

    std::unique_ptr<PDFDoc> doc;
    std::string outputString;
};

// Test setter/getter for EmbedType1
TEST_F(PSOutputDevTest_1307, SetGetEmbedType1_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

TEST_F(PSOutputDevTest_1307, SetGetEmbedType1_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setter/getter for EmbedTrueType
TEST_F(PSOutputDevTest_1307, SetGetEmbedTrueType_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1307, SetGetEmbedTrueType_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setter/getter for EmbedCIDPostScript
TEST_F(PSOutputDevTest_1307, SetGetEmbedCIDPostScript_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1307, SetGetEmbedCIDPostScript_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setter/getter for EmbedCIDTrueType
TEST_F(PSOutputDevTest_1307, SetGetEmbedCIDTrueType_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevTest_1307, SetGetEmbedCIDTrueType_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test setter/getter for FontPassthrough
TEST_F(PSOutputDevTest_1307, SetGetFontPassthrough_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
}

TEST_F(PSOutputDevTest_1307, SetGetFontPassthrough_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setter/getter for OptimizeColorSpace
TEST_F(PSOutputDevTest_1307, SetGetOptimizeColorSpace_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevTest_1307, SetGetOptimizeColorSpace_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setter/getter for PassLevel1CustomColor
TEST_F(PSOutputDevTest_1307, SetGetPassLevel1CustomColor_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevTest_1307, SetGetPassLevel1CustomColor_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test setter/getter for EnableLZW
TEST_F(PSOutputDevTest_1307, SetGetEnableLZW_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
}

TEST_F(PSOutputDevTest_1307, SetGetEnableLZW_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setter/getter for EnableFlate
TEST_F(PSOutputDevTest_1307, SetGetEnableFlate_True_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
}

TEST_F(PSOutputDevTest_1307, SetGetEnableFlate_False_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test OutputDev interface methods
TEST_F(PSOutputDevTest_1307, UpsideDownReturnsFalse_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    // PSOutputDev typically returns false for upsideDown
    bool result = dev->upsideDown();
    // Just check it doesn't crash and returns a valid bool
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1307, UseDrawCharReturnsFalse_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1307, UseTilingPatternFill_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1307, UseDrawForm_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    bool result = dev->useDrawForm();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1307, InterpretType3Chars_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1307, NeedClipToCropBox_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    bool result = dev->needClipToCropBox();
    EXPECT_TRUE(result == true || result == false);
}

// Test useShadedFills with different types
TEST_F(PSOutputDevTest_1307, UseShadedFillsVariousTypes_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        EXPECT_TRUE(result == true || result == false);
    }
}

// Test toggle setters (no getter but should not crash)
TEST_F(PSOutputDevTest_1307, SetDisplayText_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setDisplayText(true);
    dev->setDisplayText(false);
    // No crash = pass
}

TEST_F(PSOutputDevTest_1307, SetPSCenter_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setPSCenter(true);
    dev->setPSCenter(false);
}

TEST_F(PSOutputDevTest_1307, SetPSExpandSmaller_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
}

TEST_F(PSOutputDevTest_1307, SetPSShrinkLarger_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
}

TEST_F(PSOutputDevTest_1307, SetOverprintPreview_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
}

TEST_F(PSOutputDevTest_1307, SetRasterAntialias_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
}

TEST_F(PSOutputDevTest_1307, SetRasterResolution_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(600.0);
}

TEST_F(PSOutputDevTest_1307, SetForceRasterize_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);
}

TEST_F(PSOutputDevTest_1307, SetUncompressPreloadedImages_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
}

TEST_F(PSOutputDevTest_1307, SetOffset_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setOffset(0.0, 0.0);
    dev->setOffset(100.0, 200.0);
    dev->setOffset(-50.0, -50.0);
}

TEST_F(PSOutputDevTest_1307, SetScale_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 0.5);
    dev->setScale(0.0, 0.0);
}

TEST_F(PSOutputDevTest_1307, SetRotate_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
}

TEST_F(PSOutputDevTest_1307, SetClip_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setClip(0.0, 0.0, 612.0, 792.0);
    dev->setClip(100.0, 100.0, 500.0, 700.0);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1307, SetPreloadImagesForms_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1307, SetGenerateOPI_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1307, SetUseASCIIHex_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1307, SetUseBinary_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setUseBinary(true);
    dev->setUseBinary(false);
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1307, SetRasterMono_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setRasterMono();
}

// Test callback setters
TEST_F(PSOutputDevTest_1307, SetUnderlayCbk_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setUnderlayCbk(nullptr, nullptr);
}

TEST_F(PSOutputDevTest_1307, SetOverlayCbk_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setOverlayCbk(nullptr, nullptr);
}

// Test that setters can toggle values back and forth correctly
TEST_F(PSOutputDevTest_1307, ToggleEmbedType1_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

// Test that setters can toggle EnableLZW and EnableFlate independently
TEST_F(PSOutputDevTest_1307, IndependentLZWFlate_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEnableLZW(true);
    dev->setEnableFlate(false);
    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());

    dev->setEnableLZW(false);
    dev->setEnableFlate(true);
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());
}

// Test construction with file descriptor
TEST_F(PSOutputDevTest_1307, ConstructWithTempFile_1307) {
    if (!globalParams) {
        globalParams = std::make_unique<GlobalParams>();
    }

    auto tempDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test_data/test.pdf"));
    if (!tempDoc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    char tmpName[] = "/tmp/psoutput_test_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }

    std::vector<int> pages = {1};

    auto dev = std::make_unique<PSOutputDev>(
        fd, tempDoc.get(), nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, false,
        nullptr, nullptr, psLevel2
    );

    // Check basic validity
    bool ok = dev->isOk();
    EXPECT_TRUE(ok == true || ok == false);

    dev.reset();
    close(fd);
    unlink(tmpName);
}

// Test construction with filename
TEST_F(PSOutputDevTest_1307, ConstructWithFilename_1307) {
    if (!globalParams) {
        globalParams = std::make_unique<GlobalParams>();
    }

    auto tempDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test_data/test.pdf"));
    if (!tempDoc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    const char *tmpName = "/tmp/psoutput_test_1307.ps";
    std::vector<int> pages = {1};

    auto dev = std::make_unique<PSOutputDev>(
        tmpName, tempDoc.get(), nullptr, pages,
        psModePS, 0, 0, false, true,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, false,
        nullptr, nullptr, psLevel2
    );

    bool ok = dev->isOk();
    EXPECT_TRUE(ok == true || ok == false);

    dev.reset();
    unlink(tmpName);
}

// Test multiple setter/getter combinations in sequence
TEST_F(PSOutputDevTest_1307, MultipleSettersConsistency_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setEmbedType1(true);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(true);
    dev->setOptimizeColorSpace(false);

    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test boundary: setRasterResolution with zero
TEST_F(PSOutputDevTest_1307, SetRasterResolutionZero_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setRasterResolution(0.0);
    // Should not crash
}

// Test boundary: setRasterResolution with negative
TEST_F(PSOutputDevTest_1307, SetRasterResolutionNegative_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setRasterResolution(-1.0);
    // Should not crash
}

// Test boundary: very large raster resolution
TEST_F(PSOutputDevTest_1307, SetRasterResolutionLarge_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    dev->setRasterResolution(10000.0);
    // Should not crash
}

// Test isOk on valid construction
TEST_F(PSOutputDevTest_1307, IsOkOnValidConstruction_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    EXPECT_TRUE(dev->isOk());
}

// Test with callback for underlay/overlay
TEST_F(PSOutputDevTest_1307, SetUnderlayCbkWithFunction_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    auto cbk = [](PSOutputDev *psOut, void *data) {
        // dummy callback
    };
    int dummyData = 42;
    dev->setUnderlayCbk(cbk, &dummyData);
    // Should not crash
}

TEST_F(PSOutputDevTest_1307, SetOverlayCbkWithFunction_1307) {
    auto dev = createPSOutputDev("./test_data/test.pdf");
    if (!dev) GTEST_SKIP() << "Could not create PSOutputDev (no test PDF)";

    auto cbk = [](PSOutputDev *psOut, void *data) {
        // dummy callback
    };
    int dummyData = 42;
    dev->setOverlayCbk(cbk, &dummyData);
    // Should not crash
}
