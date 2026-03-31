#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <sstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper: output function that writes to a std::string
static void stringOutputFunc(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1334 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a PSOutputDev via the FoFiOutputFunc constructor
    // using a minimal valid PDF document. Returns nullptr if creation fails.
    std::unique_ptr<PSOutputDev> createPSOutputDev(std::string &output, const std::vector<int> &pages, PSOutMode mode = psModePS) {
        // We need a valid PDFDoc. Create a minimal one from a simple PDF in memory.
        // For tests that only exercise setters/getters, we rely on the device being "ok"
        // or we skip if it's not. Many setter/getter tests don't need a valid doc.
        // We'll use the FoFiOutputFunc constructor variant.

        // Create a minimal PDF in memory
        static const char *minimalPDF =
            "%PDF-1.4\n"
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

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        doc_ = std::make_unique<PDFDoc>(stream);
        if (!doc_->isOk()) {
            return nullptr;
        }

        auto dev = std::make_unique<PSOutputDev>(
            (FoFiOutputFunc)stringOutputFunc, &output,
            const_cast<char *>("Test Title"), doc_.get(), pages,
            mode, 612, 792, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);

        return dev;
    }

    std::unique_ptr<PDFDoc> doc_;
};

// Test setUseASCIIHex / basic setter
TEST_F(PSOutputDevTest_1334, SetUseASCIIHex_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Should not throw
    dev->setUseASCIIHex(true);
}

TEST_F(PSOutputDevTest_1334, SetUseASCIIHex_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setUseASCIIHex(false);
}

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevTest_1334, SetGetEmbedType1_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

TEST_F(PSOutputDevTest_1334, SetGetEmbedType1_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevTest_1334, SetGetEmbedTrueType_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1334, SetGetEmbedTrueType_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1334, SetGetEmbedCIDPostScript_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1334, SetGetEmbedCIDPostScript_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1334, SetGetEmbedCIDTrueType_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
}

TEST_F(PSOutputDevTest_1334, SetGetEmbedCIDTrueType_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevTest_1334, SetGetFontPassthrough_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
}

TEST_F(PSOutputDevTest_1334, SetGetFontPassthrough_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevTest_1334, SetGetOptimizeColorSpace_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
}

TEST_F(PSOutputDevTest_1334, SetGetOptimizeColorSpace_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1334, SetGetPassLevel1CustomColor_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
}

TEST_F(PSOutputDevTest_1334, SetGetPassLevel1CustomColor_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevTest_1334, SetGetEnableLZW_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
}

TEST_F(PSOutputDevTest_1334, SetGetEnableLZW_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevTest_1334, SetGetEnableFlate_True_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
}

TEST_F(PSOutputDevTest_1334, SetGetEnableFlate_False_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
}

// Test upsideDown
TEST_F(PSOutputDevTest_1334, UpsideDown_ReturnsFalse_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // PS output typically is not upside down
    EXPECT_FALSE(dev->upsideDown());
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1334, UseDrawChar_ReturnsFalse_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // PSOutputDev uses drawString, not drawChar
    EXPECT_FALSE(dev->useDrawChar());
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1334, UseTilingPatternFill_ReturnsTrue_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1334, UseDrawForm_ReturnsTrue_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_TRUE(dev->useDrawForm());
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1334, InterpretType3Chars_ReturnsFalse_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_FALSE(dev->interpretType3Chars());
}

// Test setter methods that don't have corresponding getters - just ensure they don't crash
TEST_F(PSOutputDevTest_1334, SetDisplayText_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setDisplayText(true));
    EXPECT_NO_THROW(dev->setDisplayText(false));
}

TEST_F(PSOutputDevTest_1334, SetPSCenter_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setPSCenter(true));
    EXPECT_NO_THROW(dev->setPSCenter(false));
}

TEST_F(PSOutputDevTest_1334, SetPSExpandSmaller_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setPSExpandSmaller(true));
    EXPECT_NO_THROW(dev->setPSExpandSmaller(false));
}

TEST_F(PSOutputDevTest_1334, SetPSShrinkLarger_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setPSShrinkLarger(true));
    EXPECT_NO_THROW(dev->setPSShrinkLarger(false));
}

TEST_F(PSOutputDevTest_1334, SetOverprintPreview_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setOverprintPreview(true));
    EXPECT_NO_THROW(dev->setOverprintPreview(false));
}

TEST_F(PSOutputDevTest_1334, SetRasterAntialias_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setRasterAntialias(true));
    EXPECT_NO_THROW(dev->setRasterAntialias(false));
}

TEST_F(PSOutputDevTest_1334, SetRasterResolution_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setRasterResolution(300.0));
    EXPECT_NO_THROW(dev->setRasterResolution(72.0));
    EXPECT_NO_THROW(dev->setRasterResolution(600.0));
}

TEST_F(PSOutputDevTest_1334, SetOffset_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setOffset(10.0, 20.0));
    EXPECT_NO_THROW(dev->setOffset(0.0, 0.0));
    EXPECT_NO_THROW(dev->setOffset(-5.0, -10.0));
}

TEST_F(PSOutputDevTest_1334, SetScale_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setScale(1.0, 1.0));
    EXPECT_NO_THROW(dev->setScale(2.0, 0.5));
}

TEST_F(PSOutputDevTest_1334, SetRotate_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setRotate(0));
    EXPECT_NO_THROW(dev->setRotate(90));
    EXPECT_NO_THROW(dev->setRotate(180));
    EXPECT_NO_THROW(dev->setRotate(270));
}

TEST_F(PSOutputDevTest_1334, SetClip_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setClip(0.0, 0.0, 612.0, 792.0));
}

TEST_F(PSOutputDevTest_1334, SetForceRasterize_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setForceRasterize(psRasterizeWhenNeeded));
    EXPECT_NO_THROW(dev->setForceRasterize(psAlwaysRasterize));
    EXPECT_NO_THROW(dev->setForceRasterize(psNeverRasterize));
}

TEST_F(PSOutputDevTest_1334, SetRasterMono_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setRasterMono());
}

TEST_F(PSOutputDevTest_1334, SetUncompressPreloadedImages_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setUncompressPreloadedImages(true));
    EXPECT_NO_THROW(dev->setUncompressPreloadedImages(false));
}

TEST_F(PSOutputDevTest_1334, SetPreloadImagesForms_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setPreloadImagesForms(true));
    EXPECT_NO_THROW(dev->setPreloadImagesForms(false));
}

TEST_F(PSOutputDevTest_1334, SetGenerateOPI_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setGenerateOPI(true));
    EXPECT_NO_THROW(dev->setGenerateOPI(false));
}

TEST_F(PSOutputDevTest_1334, SetUseBinary_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setUseBinary(true));
    EXPECT_NO_THROW(dev->setUseBinary(false));
}

// Test underlay and overlay callbacks
TEST_F(PSOutputDevTest_1334, SetUnderlayCbk_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    auto cbk = [](PSOutputDev *, void *) {};
    EXPECT_NO_THROW(dev->setUnderlayCbk(cbk, nullptr));
}

TEST_F(PSOutputDevTest_1334, SetOverlayCbk_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    auto cbk = [](PSOutputDev *, void *) {};
    EXPECT_NO_THROW(dev->setOverlayCbk(cbk, nullptr));
}

// Test useShadedFills for various types
TEST_F(PSOutputDevTest_1334, UseShadedFills_VariousTypes_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Types 1-7 are defined in PDF spec
    for (int type = 1; type <= 7; ++type) {
        // Just check it doesn't crash and returns a bool
        bool result = dev->useShadedFills(type);
        (void)result; // suppress unused warning
    }
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1334, NeedClipToCropBox_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // Just verify it returns a consistent boolean value
    bool result = dev->needClipToCropBox();
    (void)result;
}

// Test toggle: set true then false for embed settings
TEST_F(PSOutputDevTest_1334, ToggleEmbedType1_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
}

// Test toggle: set true then false for LZW/Flate
TEST_F(PSOutputDevTest_1334, ToggleEnableLZWAndFlate_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    dev->setEnableLZW(true);
    dev->setEnableFlate(false);
    EXPECT_TRUE(dev->getEnableLZW());
    EXPECT_FALSE(dev->getEnableFlate());

    dev->setEnableLZW(false);
    dev->setEnableFlate(true);
    EXPECT_FALSE(dev->getEnableLZW());
    EXPECT_TRUE(dev->getEnableFlate());
}

// Test isOk after construction
TEST_F(PSOutputDevTest_1334, IsOk_AfterConstruction_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    // The device should report its status
    // With a valid minimal PDF, it should be ok
    EXPECT_TRUE(dev->isOk());
}

// Boundary: empty pages vector
TEST_F(PSOutputDevTest_1334, EmptyPagesVector_1334) {
    std::string output;
    std::vector<int> pages; // empty
    auto dev = createPSOutputDev(output, pages);
    // Either creation succeeds or fails, but shouldn't crash
    if (dev) {
        // It may or may not be ok with empty pages
        dev->isOk();
    }
}

// Test setProcessColorFormat
TEST_F(PSOutputDevTest_1334, SetProcessColorFormat_NoThrow_1334) {
    std::string output;
    std::vector<int> pages = {1};
    auto dev = createPSOutputDev(output, pages);
    if (!dev || !dev->isOk()) {
        GTEST_SKIP() << "Could not create PSOutputDev";
    }
    EXPECT_NO_THROW(dev->setProcessColorFormat(splashModeMono8));
    EXPECT_NO_THROW(dev->setProcessColorFormat(splashModeRGB8));
    EXPECT_NO_THROW(dev->setProcessColorFormat(splashModeCMYK8));
}
