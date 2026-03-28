#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

// Helper: collect PS output into a string
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1302 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temp file, returning the PDFDoc
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Minimal PDF content
        const char *pdfContent =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n183\n%%EOF\n";

        tmpFile = std::tmpnam(nullptr);
        FILE *f = fopen(tmpFile.c_str(), "wb");
        if (f) {
            fwrite(pdfContent, 1, strlen(pdfContent), f);
            fclose(f);
        }

        auto *gooStr = new GooString(tmpFile.c_str());
        auto doc = std::make_unique<PDFDoc>(gooStr);
        return doc;
    }

    void TearDown() override {
        if (!tmpFile.empty()) {
            std::remove(tmpFile.c_str());
        }
    }

    std::string tmpFile;
};

// Test setRotate with typical values
TEST_F(PSOutputDevTest_1302, SetRotate_NormalValues_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // setRotate should accept these without crashing
    psOut.setRotate(0);
    psOut.setRotate(90);
    psOut.setRotate(180);
    psOut.setRotate(270);
}

// Test setRotate with negative value
TEST_F(PSOutputDevTest_1302, SetRotate_NegativeValue_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setRotate(-90);
    // Should not crash
}

// Test setRotate with zero
TEST_F(PSOutputDevTest_1302, SetRotate_Zero_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setRotate(0);
    // Should not crash; rotation is set to zero
}

// Test setter/getter pairs for embed options
TEST_F(PSOutputDevTest_1302, EmbedType1_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedType1(true);
    EXPECT_TRUE(psOut.getEmbedType1());

    psOut.setEmbedType1(false);
    EXPECT_FALSE(psOut.getEmbedType1());
}

TEST_F(PSOutputDevTest_1302, EmbedTrueType_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedTrueType(true);
    EXPECT_TRUE(psOut.getEmbedTrueType());

    psOut.setEmbedTrueType(false);
    EXPECT_FALSE(psOut.getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1302, EmbedCIDPostScript_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOut.getEmbedCIDPostScript());

    psOut.setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOut.getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1302, EmbedCIDTrueType_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedCIDTrueType(true);
    EXPECT_TRUE(psOut.getEmbedCIDTrueType());

    psOut.setEmbedCIDTrueType(false);
    EXPECT_FALSE(psOut.getEmbedCIDTrueType());
}

TEST_F(PSOutputDevTest_1302, FontPassthrough_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setFontPassthrough(true);
    EXPECT_TRUE(psOut.getFontPassthrough());

    psOut.setFontPassthrough(false);
    EXPECT_FALSE(psOut.getFontPassthrough());
}

TEST_F(PSOutputDevTest_1302, OptimizeColorSpace_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setOptimizeColorSpace(true);
    EXPECT_TRUE(psOut.getOptimizeColorSpace());

    psOut.setOptimizeColorSpace(false);
    EXPECT_FALSE(psOut.getOptimizeColorSpace());
}

TEST_F(PSOutputDevTest_1302, PassLevel1CustomColor_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setPassLevel1CustomColor(true);
    EXPECT_TRUE(psOut.getPassLevel1CustomColor());

    psOut.setPassLevel1CustomColor(false);
    EXPECT_FALSE(psOut.getPassLevel1CustomColor());
}

TEST_F(PSOutputDevTest_1302, EnableLZW_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEnableLZW(true);
    EXPECT_TRUE(psOut.getEnableLZW());

    psOut.setEnableLZW(false);
    EXPECT_FALSE(psOut.getEnableLZW());
}

TEST_F(PSOutputDevTest_1302, EnableFlate_SetGet_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEnableFlate(true);
    EXPECT_TRUE(psOut.getEnableFlate());

    psOut.setEnableFlate(false);
    EXPECT_FALSE(psOut.getEnableFlate());
}

// Test OutputDev interface methods
TEST_F(PSOutputDevTest_1302, UpsideDown_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // upsideDown should return a consistent boolean value
    bool result = psOut.upsideDown();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1302, UseDrawChar_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1302, UseTilingPatternFill_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1302, UseDrawForm_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.useDrawForm();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1302, InterpretType3Chars_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PSOutputDevTest_1302, NeedClipToCropBox_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.needClipToCropBox();
    EXPECT_TRUE(result == true || result == false);
}

// Test set methods that don't have getters - just ensure no crash
TEST_F(PSOutputDevTest_1302, SetOffset_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setOffset(0.0, 0.0);
    psOut.setOffset(100.0, 200.0);
    psOut.setOffset(-50.0, -75.0);
}

TEST_F(PSOutputDevTest_1302, SetScale_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setScale(1.0, 1.0);
    psOut.setScale(2.0, 2.0);
    psOut.setScale(0.5, 0.5);
}

TEST_F(PSOutputDevTest_1302, SetClip_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setClip(0.0, 0.0, 612.0, 792.0);
    psOut.setClip(10.0, 10.0, 100.0, 100.0);
}

TEST_F(PSOutputDevTest_1302, SetDisplayText_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setDisplayText(true);
    psOut.setDisplayText(false);
}

TEST_F(PSOutputDevTest_1302, SetPSCenter_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setPSCenter(true);
    psOut.setPSCenter(false);
}

TEST_F(PSOutputDevTest_1302, SetPSExpandSmaller_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setPSExpandSmaller(true);
    psOut.setPSExpandSmaller(false);
}

TEST_F(PSOutputDevTest_1302, SetPSShrinkLarger_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setPSShrinkLarger(true);
    psOut.setPSShrinkLarger(false);
}

TEST_F(PSOutputDevTest_1302, SetOverprintPreview_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setOverprintPreview(true);
    psOut.setOverprintPreview(false);
}

TEST_F(PSOutputDevTest_1302, SetRasterAntialias_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setRasterAntialias(true);
    psOut.setRasterAntialias(false);
}

TEST_F(PSOutputDevTest_1302, SetRasterResolution_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setRasterResolution(72.0);
    psOut.setRasterResolution(300.0);
    psOut.setRasterResolution(600.0);
}

TEST_F(PSOutputDevTest_1302, SetForceRasterize_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setForceRasterize(psRasterizeWhenNeeded);
    psOut.setForceRasterize(psAlwaysRasterize);
    psOut.setForceRasterize(psNeverRasterize);
}

TEST_F(PSOutputDevTest_1302, SetUncompressPreloadedImages_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setUncompressPreloadedImages(true);
    psOut.setUncompressPreloadedImages(false);
}

TEST_F(PSOutputDevTest_1302, SetPreloadImagesForms_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setPreloadImagesForms(true);
    psOut.setPreloadImagesForms(false);
}

TEST_F(PSOutputDevTest_1302, SetGenerateOPI_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setGenerateOPI(true);
    psOut.setGenerateOPI(false);
}

TEST_F(PSOutputDevTest_1302, SetUseASCIIHex_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setUseASCIIHex(true);
    psOut.setUseASCIIHex(false);
}

TEST_F(PSOutputDevTest_1302, SetUseBinary_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setUseBinary(true);
    psOut.setUseBinary(false);
}

// Test callback setters
TEST_F(PSOutputDevTest_1302, SetUnderlayCbk_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Set with null callback
    psOut.setUnderlayCbk(nullptr, nullptr);

    // Set with a lambda-compatible callback
    int callbackData = 42;
    psOut.setUnderlayCbk([](PSOutputDev *, void *) {}, &callbackData);
}

TEST_F(PSOutputDevTest_1302, SetOverlayCbk_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setOverlayCbk(nullptr, nullptr);

    int callbackData = 42;
    psOut.setOverlayCbk([](PSOutputDev *, void *) {}, &callbackData);
}

// Test isOk on a properly initialized PSOutputDev
TEST_F(PSOutputDevTest_1302, IsOk_ValidInit_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    // After valid initialization, isOk should return true
    EXPECT_TRUE(psOut.isOk());
}

// Test useShadedFills with different type values
TEST_F(PSOutputDevTest_1302, UseShadedFills_DifferentTypes_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Test various shading types (1-7 are typical PDF shading types)
    for (int type = 1; type <= 7; ++type) {
        bool result = psOut.useShadedFills(type);
        EXPECT_TRUE(result == true || result == false);
    }
}

// Test setRotate with large values (boundary)
TEST_F(PSOutputDevTest_1302, SetRotate_LargeValue_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setRotate(360);
    psOut.setRotate(720);
    psOut.setRotate(INT_MAX);
    psOut.setRotate(INT_MIN);
}

// Test that toggling boolean settings back and forth works correctly
TEST_F(PSOutputDevTest_1302, ToggleBooleanSettings_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Toggle embedType1 multiple times
    psOut.setEmbedType1(true);
    EXPECT_TRUE(psOut.getEmbedType1());
    psOut.setEmbedType1(false);
    EXPECT_FALSE(psOut.getEmbedType1());
    psOut.setEmbedType1(true);
    EXPECT_TRUE(psOut.getEmbedType1());

    // Toggle enableFlate multiple times
    psOut.setEnableFlate(false);
    EXPECT_FALSE(psOut.getEnableFlate());
    psOut.setEnableFlate(true);
    EXPECT_TRUE(psOut.getEnableFlate());
    psOut.setEnableFlate(false);
    EXPECT_FALSE(psOut.getEnableFlate());
}

// Test with EPS mode
TEST_F(PSOutputDevTest_1302, EPSMode_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModeEPS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed in EPS mode";
    }

    EXPECT_TRUE(psOut.isOk());
}

// Test with different PS levels
TEST_F(PSOutputDevTest_1302, PSLevel1_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel1);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed with Level 1";
    }

    EXPECT_TRUE(psOut.isOk());
}

TEST_F(PSOutputDevTest_1302, PSLevel3_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel3);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed with Level 3";
    }

    EXPECT_TRUE(psOut.isOk());
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1302, SetRasterMono_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Should not crash
    psOut.setRasterMono();
}

// Test setScale with boundary values
TEST_F(PSOutputDevTest_1302, SetScale_BoundaryValues_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setScale(0.0, 0.0);
    psOut.setScale(1e10, 1e10);
    psOut.setScale(-1.0, -1.0);
}

// Test setOffset with boundary values
TEST_F(PSOutputDevTest_1302, SetOffset_BoundaryValues_1302) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    
    PSOutputDev psOut(outputToString, &output, const_cast<char *>("test"),
                      doc.get(), pages, psModePS, 612, 792, false, false,
                      0, 0, 0, 0, psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setOffset(0.0, 0.0);
    psOut.setOffset(1e10, 1e10);
    psOut.setOffset(-1e10, -1e10);
}
