#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to capture PS output
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1301 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with a simple PDF if possible
    // We'll create a minimal test environment
    std::unique_ptr<PSOutputDev> createPSOutputDev(PDFDoc *doc, std::string &output) {
        std::vector<int> pages;
        if (doc && doc->isOk()) {
            for (int i = 1; i <= doc->getNumPages(); i++) {
                pages.push_back(i);
            }
        }
        if (pages.empty()) {
            pages.push_back(1);
        }

        auto dev = std::make_unique<PSOutputDev>(
            outputFunc, &output, nullptr, doc, pages,
            psModePS, -1, -1, false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        return dev;
    }
};

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevTest_1301, SetGetEmbedType1_True_1301) {
    std::string output;
    // We need a valid PDFDoc for construction; use /dev/null or a temp file approach
    // Create a minimal PDF in memory
    GooString fileName("./test_minimal.pdf");

    // Try to create with a file descriptor approach
    // Since we need a valid doc, we'll test setter/getter if we can construct the object
    // For methods that are purely setters/getters on boolean flags, we test them
    // by constructing with FoFiOutputFunc

    // Create minimal PDF content
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());

            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
        }
    }
    remove("test_minimal_1301.pdf");
}

// Test setEmbedTrueType / getEmbedTrueType
TEST_F(PSOutputDevTest_1301, SetGetEmbedTrueType_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_tt.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_tt.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setEmbedTrueType(true);
            EXPECT_TRUE(dev->getEmbedTrueType());

            dev->setEmbedTrueType(false);
            EXPECT_FALSE(dev->getEmbedTrueType());
        }
    }
    remove("test_minimal_1301_tt.pdf");
}

// Test setEmbedCIDPostScript / getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1301, SetGetEmbedCIDPostScript_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_cidps.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_cidps.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setEmbedCIDPostScript(true);
            EXPECT_TRUE(dev->getEmbedCIDPostScript());

            dev->setEmbedCIDPostScript(false);
            EXPECT_FALSE(dev->getEmbedCIDPostScript());
        }
    }
    remove("test_minimal_1301_cidps.pdf");
}

// Test setEmbedCIDTrueType / getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1301, SetGetEmbedCIDTrueType_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_cidtt.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_cidtt.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setEmbedCIDTrueType(true);
            EXPECT_TRUE(dev->getEmbedCIDTrueType());

            dev->setEmbedCIDTrueType(false);
            EXPECT_FALSE(dev->getEmbedCIDTrueType());
        }
    }
    remove("test_minimal_1301_cidtt.pdf");
}

// Test setFontPassthrough / getFontPassthrough
TEST_F(PSOutputDevTest_1301, SetGetFontPassthrough_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_fp.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_fp.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setFontPassthrough(true);
            EXPECT_TRUE(dev->getFontPassthrough());

            dev->setFontPassthrough(false);
            EXPECT_FALSE(dev->getFontPassthrough());
        }
    }
    remove("test_minimal_1301_fp.pdf");
}

// Test setOptimizeColorSpace / getOptimizeColorSpace
TEST_F(PSOutputDevTest_1301, SetGetOptimizeColorSpace_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_ocs.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_ocs.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setOptimizeColorSpace(true);
            EXPECT_TRUE(dev->getOptimizeColorSpace());

            dev->setOptimizeColorSpace(false);
            EXPECT_FALSE(dev->getOptimizeColorSpace());
        }
    }
    remove("test_minimal_1301_ocs.pdf");
}

// Test setEnableLZW / getEnableLZW
TEST_F(PSOutputDevTest_1301, SetGetEnableLZW_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_lzw.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_lzw.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setEnableLZW(true);
            EXPECT_TRUE(dev->getEnableLZW());

            dev->setEnableLZW(false);
            EXPECT_FALSE(dev->getEnableLZW());
        }
    }
    remove("test_minimal_1301_lzw.pdf");
}

// Test setEnableFlate / getEnableFlate
TEST_F(PSOutputDevTest_1301, SetGetEnableFlate_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_flate.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_flate.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setEnableFlate(true);
            EXPECT_TRUE(dev->getEnableFlate());

            dev->setEnableFlate(false);
            EXPECT_FALSE(dev->getEnableFlate());
        }
    }
    remove("test_minimal_1301_flate.pdf");
}

// Test setPassLevel1CustomColor / getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1301, SetGetPassLevel1CustomColor_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_pl1cc.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_pl1cc.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setPassLevel1CustomColor(true);
            EXPECT_TRUE(dev->getPassLevel1CustomColor());

            dev->setPassLevel1CustomColor(false);
            EXPECT_FALSE(dev->getPassLevel1CustomColor());
        }
    }
    remove("test_minimal_1301_pl1cc.pdf");
}

// Test upsideDown, useDrawChar, interpretType3Chars overrides
TEST_F(PSOutputDevTest_1301, QueryMethods_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_query.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_query.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // These should return deterministic values
            // upsideDown for PS is typically false
            EXPECT_FALSE(dev->upsideDown());
            // useDrawChar for PS is typically false
            EXPECT_FALSE(dev->useDrawChar());
            // useTilingPatternFill is typically true
            EXPECT_TRUE(dev->useTilingPatternFill());
            // useDrawForm typically true
            EXPECT_TRUE(dev->useDrawForm());
            // interpretType3Chars typically false
            EXPECT_FALSE(dev->interpretType3Chars());
        }
    }
    remove("test_minimal_1301_query.pdf");
}

// Test useShadedFills with different type values
TEST_F(PSOutputDevTest_1301, UseShadedFillsTypes_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_shaded.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_shaded.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // Test various shading types
            // Type 1 = function-based
            // Type 2 = axial
            // Type 3 = radial
            // Type 6 = patch mesh (Coons)
            // Type 7 = tensor product patch mesh
            // For level 2+, types 1-3 should typically return true
            // We just verify these don't crash and return bool
            bool result1 = dev->useShadedFills(1);
            bool result2 = dev->useShadedFills(2);
            bool result3 = dev->useShadedFills(3);
            bool result4 = dev->useShadedFills(4);
            bool result5 = dev->useShadedFills(5);
            bool result6 = dev->useShadedFills(6);
            bool result7 = dev->useShadedFills(7);

            // At PS level 2, function/axial/radial should be supported
            EXPECT_TRUE(result1);
            EXPECT_TRUE(result2);
            EXPECT_TRUE(result3);
            // Types 4,5 are not typically supported
            EXPECT_FALSE(result4);
            EXPECT_FALSE(result5);
            // Patch mesh types 6,7 typically supported at level 3
            // At level 2 they may or may not be
            (void)result6;
            (void)result7;
        }
    }
    remove("test_minimal_1301_shaded.pdf");
}

// Test multiple setter calls toggling values
TEST_F(PSOutputDevTest_1301, ToggleSetters_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_toggle.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_toggle.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // Toggle EmbedType1 multiple times
            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());
            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
        }
    }
    remove("test_minimal_1301_toggle.pdf");
}

// Test isOk on valid construction
TEST_F(PSOutputDevTest_1301, IsOkValidConstruction_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_isok.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_isok.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        EXPECT_TRUE(dev->isOk());
    }
    remove("test_minimal_1301_isok.pdf");
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1301, NeedClipToCropBox_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_clip.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_clip.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // needClipToCropBox should return a bool without crashing
            bool result = dev->needClipToCropBox();
            // For PS output, this is typically false
            EXPECT_FALSE(result);
        }
    }
    remove("test_minimal_1301_clip.pdf");
}

// Test setter methods that don't have getters (just ensure no crash)
TEST_F(PSOutputDevTest_1301, SettersNoCrash_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_setters.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_setters.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // These setters don't have corresponding getters, just ensure they don't crash
            dev->setOffset(10.0, 20.0);
            dev->setScale(1.5, 2.0);
            dev->setRotate(90);
            dev->setClip(0.0, 0.0, 612.0, 792.0);
            dev->setDisplayText(true);
            dev->setDisplayText(false);
            dev->setPSCenter(true);
            dev->setPSCenter(false);
            dev->setPSExpandSmaller(true);
            dev->setPSExpandSmaller(false);
            dev->setPSShrinkLarger(true);
            dev->setPSShrinkLarger(false);
            dev->setOverprintPreview(true);
            dev->setOverprintPreview(false);
            dev->setRasterAntialias(true);
            dev->setRasterAntialias(false);
            dev->setRasterResolution(300.0);
            dev->setRasterResolution(72.0);
            dev->setUncompressPreloadedImages(true);
            dev->setUncompressPreloadedImages(false);
            dev->setPreloadImagesForms(true);
            dev->setPreloadImagesForms(false);
            dev->setGenerateOPI(true);
            dev->setGenerateOPI(false);
            dev->setUseASCIIHex(true);
            dev->setUseASCIIHex(false);
            dev->setUseBinary(true);
            dev->setUseBinary(false);

            // If we got here without crashing, the test passes
            SUCCEED();
        }
    }
    remove("test_minimal_1301_setters.pdf");
}

// Test setScale with boundary values
TEST_F(PSOutputDevTest_1301, SetScaleBoundaryValues_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_scale.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_scale.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // Test zero scale
            dev->setScale(0.0, 0.0);
            // Test negative scale
            dev->setScale(-1.0, -1.0);
            // Test very large scale
            dev->setScale(1e10, 1e10);
            // Test very small scale
            dev->setScale(1e-10, 1e-10);
            // Test normal scale
            dev->setScale(1.0, 1.0);

            SUCCEED();
        }
    }
    remove("test_minimal_1301_scale.pdf");
}

// Test setOffset with boundary values
TEST_F(PSOutputDevTest_1301, SetOffsetBoundaryValues_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_offset.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_offset.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setOffset(0.0, 0.0);
            dev->setOffset(-100.0, -200.0);
            dev->setOffset(1e10, 1e10);
            dev->setOffset(72.0, 72.0);

            SUCCEED();
        }
    }
    remove("test_minimal_1301_offset.pdf");
}

// Test setRotate with various angles
TEST_F(PSOutputDevTest_1301, SetRotateVariousAngles_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_rotate.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_rotate.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setRotate(0);
            dev->setRotate(90);
            dev->setRotate(180);
            dev->setRotate(270);
            dev->setRotate(360);
            dev->setRotate(-90);

            SUCCEED();
        }
    }
    remove("test_minimal_1301_rotate.pdf");
}

// Test setClip with various rectangles
TEST_F(PSOutputDevTest_1301, SetClipVariousRectangles_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_cliprect.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_cliprect.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // Normal clip
            dev->setClip(0.0, 0.0, 612.0, 792.0);
            // Zero-area clip
            dev->setClip(100.0, 100.0, 100.0, 100.0);
            // Inverted clip (llx > urx)
            dev->setClip(612.0, 792.0, 0.0, 0.0);
            // Negative coordinates
            dev->setClip(-100.0, -100.0, 100.0, 100.0);

            SUCCEED();
        }
    }
    remove("test_minimal_1301_cliprect.pdf");
}

// Test setRasterResolution with boundary values
TEST_F(PSOutputDevTest_1301, SetRasterResolutionBoundary_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_rasterres.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_rasterres.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setRasterResolution(72.0);
            dev->setRasterResolution(150.0);
            dev->setRasterResolution(300.0);
            dev->setRasterResolution(600.0);
            dev->setRasterResolution(1200.0);
            dev->setRasterResolution(0.0);

            SUCCEED();
        }
    }
    remove("test_minimal_1301_rasterres.pdf");
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1301, SetRasterMono_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_mono.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_mono.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // setRasterMono should not crash
            dev->setRasterMono();
            SUCCEED();
        }
    }
    remove("test_minimal_1301_mono.pdf");
}

// Test callback setters (underlay and overlay)
TEST_F(PSOutputDevTest_1301, SetCallbacks_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_cb.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_cb.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            // Setting null callbacks should not crash
            dev->setUnderlayCbk(nullptr, nullptr);
            dev->setOverlayCbk(nullptr, nullptr);

            // Setting a valid callback
            auto dummyCbk = [](PSOutputDev *, void *) {};
            int dummyData = 42;
            dev->setUnderlayCbk(dummyCbk, &dummyData);
            dev->setOverlayCbk(dummyCbk, &dummyData);

            SUCCEED();
        }
    }
    remove("test_minimal_1301_cb.pdf");
}

// Test forceRasterize setter
TEST_F(PSOutputDevTest_1301, SetForceRasterize_1301) {
    std::string output;
    const char *minimalPdf = "%PDF-1.0\n1 0 obj<</Pages 2 0 R>>endobj\n2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\nxref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n0000000043 00000 n \n0000000099 00000 n \ntrailer<</Root 1 0 R/Size 4>>\nstartxref\n174\n%%EOF\n";

    FILE *f = fopen("test_minimal_1301_rasterize.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("test_minimal_1301_rasterize.pdf");
    auto doc = std::make_unique<PDFDoc>(gooFileName.get());

    if (doc && doc->isOk()) {
        auto dev = createPSOutputDev(doc.get(), output);
        if (dev && dev->isOk()) {
            dev->setForceRasterize(psRasterizeWhenNeeded);
            dev->setForceRasterize(psAlwaysRasterize);
            dev->setForceRasterize(psNeverRasterize);

            SUCCEED();
        }
    }
    remove("test_minimal_1301_rasterize.pdf");
}
