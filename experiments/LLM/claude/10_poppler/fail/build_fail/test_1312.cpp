#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

namespace {

// Output function that collects PS output into a string
void psOutputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1312 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create PSOutputDev via FoFiOutputFunc constructor
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        auto dev = std::make_unique<PSOutputDev>(
            psOutputFunc, &outputBuffer,
            const_cast<char *>("Test Title"),
            doc, pages,
            psModePS,   // PSOutMode
            -1, -1,     // paperWidth, paperHeight
            false,      // noCrop
            true,       // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // PSForceRasterize
            false,      // manualCtrl
            nullptr,    // customCodeCbk
            nullptr,    // customCodeCbkData
            psLevel2    // PSLevel
        );
        return dev;
    }

    std::string outputBuffer;
};

// Test setForceRasterize with different enum values
TEST_F(PSOutputDevTest_1312, SetForceRasterize_WhenNeeded_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Should not crash
    dev->setForceRasterize(psRasterizeWhenNeeded);
}

TEST_F(PSOutputDevTest_1312, SetForceRasterize_Always_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setForceRasterize(psAlwaysRasterize);
}

TEST_F(PSOutputDevTest_1312, SetForceRasterize_Never_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setForceRasterize(psNeverRasterize);
}

// Test setter/getter pairs for embed flags
TEST_F(PSOutputDevTest_1312, SetGetEmbedType1_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

TEST_F(PSOutputDevTest_1312, SetGetEmbedTrueType_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1312, SetGetEmbedCIDPostScript_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1312, SetGetEmbedCIDTrueType_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevTest_1312, SetGetFontPassthrough_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

TEST_F(PSOutputDevTest_1312, SetGetOptimizeColorSpace_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevTest_1312, SetGetPassLevel1CustomColor_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevTest_1312, SetGetEnableLZW_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

TEST_F(PSOutputDevTest_1312, SetGetEnableFlate_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test OutputDev interface methods
TEST_F(PSOutputDevTest_1312, UpsideDown_ReturnsFalse_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // PS coordinate system is not upside down
    EXPECT_FALSE(dev->upsideDown());
}

TEST_F(PSOutputDevTest_1312, UseDrawChar_ReturnsFalse_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    EXPECT_FALSE(dev->useDrawChar());
}

TEST_F(PSOutputDevTest_1312, UseTilingPatternFill_ReturnsTrue_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    EXPECT_TRUE(dev->useTilingPatternFill());
}

TEST_F(PSOutputDevTest_1312, UseDrawForm_ReturnsTrue_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    EXPECT_TRUE(dev->useDrawForm());
}

TEST_F(PSOutputDevTest_1312, InterpretType3Chars_ReturnsFalse_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    EXPECT_FALSE(dev->interpretType3Chars());
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1312, SetDisplayText_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Should not crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1312, SetPSCenter_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setPSCenter(true);
    dev->setPSCenter(false);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1312, SetPSExpandSmaller_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);
}

TEST_F(PSOutputDevTest_1312, SetPSShrinkLarger_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1312, SetOverprintPreview_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1312, SetRasterResolution_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);
}

// Test setOffset
TEST_F(PSOutputDevTest_1312, SetOffset_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setOffset(0.0, 0.0);
    dev->setOffset(10.5, 20.3);
    dev->setOffset(-5.0, -10.0);
}

// Test setScale
TEST_F(PSOutputDevTest_1312, SetScale_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 2.0);
    dev->setScale(0.5, 0.5);
}

// Test setRotate
TEST_F(PSOutputDevTest_1312, SetRotate_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);
}

// Test setClip
TEST_F(PSOutputDevTest_1312, SetClip_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setClip(0.0, 0.0, 612.0, 792.0);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1312, SetRasterAntialias_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1312, SetUncompressPreloadedImages_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1312, SetPreloadImagesForms_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1312, SetGenerateOPI_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1312, SetUseASCIIHex_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1312, SetUseBinary_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    dev->setUseBinary(true);
    dev->setUseBinary(false);
}

// Test setUnderlayCbk and setOverlayCbk
static void dummyUnderlayCbk(PSOutputDev *psOut, void *data) {
    // no-op
}

static void dummyOverlayCbk(PSOutputDev *psOut, void *data) {
    // no-op
}

TEST_F(PSOutputDevTest_1312, SetUnderlayCbk_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    int userData = 42;
    dev->setUnderlayCbk(dummyUnderlayCbk, &userData);
    // Setting to nullptr should also work
    dev->setUnderlayCbk(nullptr, nullptr);
}

TEST_F(PSOutputDevTest_1312, SetOverlayCbk_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    int userData = 42;
    dev->setOverlayCbk(dummyOverlayCbk, &userData);
    dev->setOverlayCbk(nullptr, nullptr);
}

// Test useShadedFills for different types
TEST_F(PSOutputDevTest_1312, UseShadedFills_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Test different shading types
    for (int type = 1; type <= 7; ++type) {
        // Just verify it doesn't crash and returns a bool
        bool result = dev->useShadedFills(type);
        (void)result;
    }
}

// Test isOk
TEST_F(PSOutputDevTest_1312, IsOk_WithValidDoc_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // isOk should return true for a valid setup
    EXPECT_TRUE(dev->isOk());
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1312, NeedClipToCropBox_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Just verify it returns a bool without crashing
    bool result = dev->needClipToCropBox();
    (void)result;
}

// Test multiple setter/getter round-trips to verify consistency
TEST_F(PSOutputDevTest_1312, MultipleSetGetRoundTrips_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Toggle all boolean setters and verify getters
    dev->setEmbedType1(true);
    dev->setEmbedTrueType(false);
    dev->setEmbedCIDPostScript(true);
    dev->setEmbedCIDTrueType(false);
    dev->setFontPassthrough(true);
    dev->setOptimizeColorSpace(false);
    dev->setPassLevel1CustomColor(true);
    dev->setEnableLZW(false);
    dev->setEnableFlate(true);

    EXPECT_TRUE(dev->getEmbedType1());
    EXPECT_FALSE(dev->getEmbedTrueType());
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    EXPECT_TRUE(dev->getFontPassthrough());
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());

    // Now toggle the other way
    dev->setEmbedType1(false);
    dev->setEmbedTrueType(true);
    dev->setEmbedCIDPostScript(false);
    dev->setEmbedCIDTrueType(true);
    dev->setFontPassthrough(false);
    dev->setOptimizeColorSpace(true);
    dev->setPassLevel1CustomColor(false);
    dev->setEnableLZW(true);
    dev->setEnableFlate(false);

    EXPECT_FALSE(dev->getEmbedType1());
    EXPECT_TRUE(dev->getEmbedTrueType());
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    EXPECT_FALSE(dev->getFontPassthrough());
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1312, SetRasterMono_1312) {
    GooString fileName("./test_data/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        GTEST_SKIP() << "PSOutputDev creation failed";
    }

    // Should not crash
    dev->setRasterMono();
}

} // namespace
