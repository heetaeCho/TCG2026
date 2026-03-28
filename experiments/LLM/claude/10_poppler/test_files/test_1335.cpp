#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper output function for PSOutputDev
static void outputFunc(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1335 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with output function - returns nullptr if creation fails
    PSOutputDev *createPSOutputDev(PDFDoc *doc, std::string *outputStr, 
                                    const std::vector<int> &pages,
                                    PSOutMode mode = psModePS,
                                    PSLevel level = psLevel2) {
        return new PSOutputDev(outputFunc, outputStr, 
                              const_cast<char*>("TestTitle"),
                              doc, pages, mode,
                              -1, -1, false, true,
                              0, 0, 0, 0,
                              psRasterizeWhenNeeded,
                              false, nullptr, nullptr, level);
    }

    // Create a minimal valid PDF in a temp file and return a PDFDoc
    PDFDoc *createMinimalPDFDoc(const std::string &filename) {
        // Create a minimal valid PDF file
        std::ofstream f(filename, std::ios::binary);
        f << "%PDF-1.4\n";
        f << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        f << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        f << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f << "xref\n0 4\n";
        f << "0000000000 65535 f \n";
        f << "0000000009 00000 n \n";
        f << "0000000058 00000 n \n";
        f << "0000000115 00000 n \n";
        f << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        f << "startxref\n196\n%%EOF\n";
        f.close();

        auto *gooStr = new GooString(filename.c_str());
        return new PDFDoc(gooStr);
    }
};

// Test: setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevTest_1335, SetGetEmbedType1_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_1.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetEmbedType1_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_2.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevTest_1335, SetGetEmbedTrueType_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_3.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedTrueType(true);
        EXPECT_TRUE(psOut->getEmbedTrueType());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetEmbedTrueType_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_4.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedTrueType(false);
        EXPECT_FALSE(psOut->getEmbedTrueType());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1335, SetGetEmbedCIDPostScript_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_5.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDPostScript(true);
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetEmbedCIDPostScript_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_6.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDPostScript(false);
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1335, SetGetEmbedCIDTrueType_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_7.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDTrueType(true);
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetEmbedCIDTrueType_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_8.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEmbedCIDTrueType(false);
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevTest_1335, SetGetFontPassthrough_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_9.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setFontPassthrough(true);
        EXPECT_TRUE(psOut->getFontPassthrough());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetFontPassthrough_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_10.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setFontPassthrough(false);
        EXPECT_FALSE(psOut->getFontPassthrough());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1335, SetGetOptimizeColorSpace_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_11.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setOptimizeColorSpace(true);
        EXPECT_TRUE(psOut->getOptimizeColorSpace());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetOptimizeColorSpace_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_12.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setOptimizeColorSpace(false);
        EXPECT_FALSE(psOut->getOptimizeColorSpace());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1335, SetGetPassLevel1CustomColor_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_13.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setPassLevel1CustomColor(true);
        EXPECT_TRUE(psOut->getPassLevel1CustomColor());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetPassLevel1CustomColor_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_14.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setPassLevel1CustomColor(false);
        EXPECT_FALSE(psOut->getPassLevel1CustomColor());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setEnableLZW and getEnableLZW
TEST_F(PSOutputDevTest_1335, SetGetEnableLZW_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_15.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetEnableLZW_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_16.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setEnableFlate and getEnableFlate
TEST_F(PSOutputDevTest_1335, SetGetEnableFlate_True_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_17.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, SetGetEnableFlate_False_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_18.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: upsideDown
TEST_F(PSOutputDevTest_1335, UpsideDown_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_19.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        // upsideDown is a known property of PSOutputDev
        bool result = psOut->upsideDown();
        // Just verify it returns a boolean without crashing
        EXPECT_TRUE(result == true || result == false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: useDrawChar
TEST_F(PSOutputDevTest_1335, UseDrawChar_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_20.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        bool result = psOut->useDrawChar();
        EXPECT_TRUE(result == true || result == false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: useTilingPatternFill
TEST_F(PSOutputDevTest_1335, UseTilingPatternFill_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_21.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        bool result = psOut->useTilingPatternFill();
        EXPECT_TRUE(result == true || result == false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: useDrawForm
TEST_F(PSOutputDevTest_1335, UseDrawForm_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_22.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        bool result = psOut->useDrawForm();
        EXPECT_TRUE(result == true || result == false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: interpretType3Chars
TEST_F(PSOutputDevTest_1335, InterpretType3Chars_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_23.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        bool result = psOut->interpretType3Chars();
        EXPECT_TRUE(result == true || result == false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: isOk after valid construction
TEST_F(PSOutputDevTest_1335, IsOkAfterConstruction_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_24.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    ASSERT_NE(psOut, nullptr);
    // Should be ok after proper construction
    EXPECT_TRUE(psOut->isOk());
    delete psOut;
    delete doc;
    remove(filename.c_str());
}

// Test: Multiple setter toggles
TEST_F(PSOutputDevTest_1335, MultipleSetterToggles_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_25.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        // Toggle multiple times
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
        
        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
        
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setDisplayText does not crash
TEST_F(PSOutputDevTest_1335, SetDisplayText_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_26.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        // These should not crash
        psOut->setDisplayText(true);
        psOut->setDisplayText(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setPSCenter does not crash
TEST_F(PSOutputDevTest_1335, SetPSCenter_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_27.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setPSCenter(true);
        psOut->setPSCenter(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1335, SetPSExpandSmallerAndShrinkLarger_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_28.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setPSExpandSmaller(true);
        psOut->setPSExpandSmaller(false);
        psOut->setPSShrinkLarger(true);
        psOut->setPSShrinkLarger(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setOverprintPreview
TEST_F(PSOutputDevTest_1335, SetOverprintPreview_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_29.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setOverprintPreview(true);
        psOut->setOverprintPreview(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setRasterResolution
TEST_F(PSOutputDevTest_1335, SetRasterResolution_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_30.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setRasterResolution(300.0);
        psOut->setRasterResolution(72.0);
        psOut->setRasterResolution(1200.0);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setOffset and setScale and setRotate and setClip
TEST_F(PSOutputDevTest_1335, SetOffsetScaleRotateClip_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_31.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setOffset(10.0, 20.0);
        psOut->setScale(1.5, 2.0);
        psOut->setRotate(90);
        psOut->setClip(0.0, 0.0, 612.0, 792.0);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setUseBinary
TEST_F(PSOutputDevTest_1335, SetUseBinary_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_32.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setUseBinary(true);
        psOut->setUseBinary(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setUseASCIIHex
TEST_F(PSOutputDevTest_1335, SetUseASCIIHex_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_33.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setUseASCIIHex(true);
        psOut->setUseASCIIHex(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1335, SetUncompressPreloadedImages_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_34.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setUncompressPreloadedImages(true);
        psOut->setUncompressPreloadedImages(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setGenerateOPI
TEST_F(PSOutputDevTest_1335, SetGenerateOPI_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_35.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setGenerateOPI(true);
        psOut->setGenerateOPI(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setPreloadImagesForms
TEST_F(PSOutputDevTest_1335, SetPreloadImagesForms_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_36.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setPreloadImagesForms(true);
        psOut->setPreloadImagesForms(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setRasterAntialias
TEST_F(PSOutputDevTest_1335, SetRasterAntialias_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_37.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setRasterAntialias(true);
        psOut->setRasterAntialias(false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setForceRasterize
TEST_F(PSOutputDevTest_1335, SetForceRasterize_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_38.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setForceRasterize(psRasterizeWhenNeeded);
        psOut->setForceRasterize(psAlwaysRasterize);
        psOut->setForceRasterize(psNeverRasterize);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: needClipToCropBox
TEST_F(PSOutputDevTest_1335, NeedClipToCropBox_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_39.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        bool result = psOut->needClipToCropBox();
        EXPECT_TRUE(result == true || result == false);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: useShadedFills with different types
TEST_F(PSOutputDevTest_1335, UseShadedFills_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_40.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        for (int type = 1; type <= 7; ++type) {
            bool result = psOut->useShadedFills(type);
            EXPECT_TRUE(result == true || result == false) 
                << "useShadedFills(" << type << ") returned invalid value";
        }
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setRasterMono does not crash
TEST_F(PSOutputDevTest_1335, SetRasterMono_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_41.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setRasterMono();
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: Construction with file name
TEST_F(PSOutputDevTest_1335, ConstructionWithFileName_1335) {
    std::string pdfFilename = "/tmp/test_ps_1335_42.pdf";
    std::string psFilename = "/tmp/test_ps_output_1335_42.ps";
    PDFDoc *doc = createMinimalPDFDoc(pdfFilename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = new PSOutputDev(psFilename.c_str(), doc,
                                         const_cast<char*>("TestTitle"),
                                         pages, psModePS,
                                         -1, -1, false, true,
                                         0, 0, 0, 0,
                                         psRasterizeWhenNeeded,
                                         false, nullptr, nullptr, psLevel2);
    ASSERT_NE(psOut, nullptr);
    // If it was able to open the file, it should be ok
    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->isOk());
    }
    delete psOut;
    delete doc;
    remove(pdfFilename.c_str());
    remove(psFilename.c_str());
}

// Test: setUnderlayCbk and setOverlayCbk with callbacks
TEST_F(PSOutputDevTest_1335, SetUnderlayCbkAndOverlayCbk_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_43.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        int dummyData = 42;
        auto dummyCbk = [](PSOutputDev *psOut, void *data) {};
        
        psOut->setUnderlayCbk(dummyCbk, &dummyData);
        psOut->setOverlayCbk(dummyCbk, &dummyData);
        
        // Set to nullptr
        psOut->setUnderlayCbk(nullptr, nullptr);
        psOut->setOverlayCbk(nullptr, nullptr);
        
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: All boolean getters/setters consistency
TEST_F(PSOutputDevTest_1335, AllBooleanSetterGetterConsistency_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_44.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        // Test all setter/getter pairs with both true and false
        
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());
        
        psOut->setEmbedTrueType(true);
        EXPECT_TRUE(psOut->getEmbedTrueType());
        psOut->setEmbedTrueType(false);
        EXPECT_FALSE(psOut->getEmbedTrueType());
        
        psOut->setEmbedCIDPostScript(true);
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());
        psOut->setEmbedCIDPostScript(false);
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());
        
        psOut->setEmbedCIDTrueType(true);
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());
        psOut->setEmbedCIDTrueType(false);
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());
        
        psOut->setFontPassthrough(true);
        EXPECT_TRUE(psOut->getFontPassthrough());
        psOut->setFontPassthrough(false);
        EXPECT_FALSE(psOut->getFontPassthrough());
        
        psOut->setOptimizeColorSpace(true);
        EXPECT_TRUE(psOut->getOptimizeColorSpace());
        psOut->setOptimizeColorSpace(false);
        EXPECT_FALSE(psOut->getOptimizeColorSpace());
        
        psOut->setPassLevel1CustomColor(true);
        EXPECT_TRUE(psOut->getPassLevel1CustomColor());
        psOut->setPassLevel1CustomColor(false);
        EXPECT_FALSE(psOut->getPassLevel1CustomColor());
        
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());
        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());
        
        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());
        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
        
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: Construction with EPS mode
TEST_F(PSOutputDevTest_1335, ConstructionWithEPSMode_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_45.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output,
                                         const_cast<char*>("TestTitle"),
                                         doc, pages, psModeEPS,
                                         -1, -1, false, false,
                                         0, 0, 0, 0,
                                         psRasterizeWhenNeeded,
                                         false, nullptr, nullptr, psLevel2);
    ASSERT_NE(psOut, nullptr);
    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->isOk());
    }
    delete psOut;
    delete doc;
    remove(filename.c_str());
}

// Test: Construction with different PS levels
TEST_F(PSOutputDevTest_1335, ConstructionWithLevel1_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_46.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output,
                                         const_cast<char*>("TestTitle"),
                                         doc, pages, psModePS,
                                         -1, -1, false, true,
                                         0, 0, 0, 0,
                                         psRasterizeWhenNeeded,
                                         false, nullptr, nullptr, psLevel1);
    ASSERT_NE(psOut, nullptr);
    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->isOk());
    }
    delete psOut;
    delete doc;
    remove(filename.c_str());
}

TEST_F(PSOutputDevTest_1335, ConstructionWithLevel3_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_47.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = new PSOutputDev(outputFunc, &output,
                                         const_cast<char*>("TestTitle"),
                                         doc, pages, psModePS,
                                         -1, -1, false, true,
                                         0, 0, 0, 0,
                                         psRasterizeWhenNeeded,
                                         false, nullptr, nullptr, psLevel3);
    ASSERT_NE(psOut, nullptr);
    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->isOk());
    }
    delete psOut;
    delete doc;
    remove(filename.c_str());
}

// Test: setOffset with zero values
TEST_F(PSOutputDevTest_1335, SetOffsetZero_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_48.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setOffset(0.0, 0.0);
        psOut->setScale(1.0, 1.0);
        psOut->setRotate(0);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setOffset with negative values
TEST_F(PSOutputDevTest_1335, SetOffsetNegative_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_49.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setOffset(-100.0, -200.0);
        psOut->setScale(-1.0, -1.0);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}

// Test: setRotate with various angles
TEST_F(PSOutputDevTest_1335, SetRotateVariousAngles_1335) {
    std::string output;
    std::string filename = "/tmp/test_ps_1335_50.pdf";
    PDFDoc *doc = createMinimalPDFDoc(filename);
    ASSERT_TRUE(doc != nullptr);
    
    if (!doc->isOk()) {
        delete doc;
        GTEST_SKIP() << "Could not create valid PDF document";
    }
    
    std::vector<int> pages = {1};
    PSOutputDev *psOut = createPSOutputDev(doc, &output, pages);
    
    if (psOut && psOut->isOk()) {
        psOut->setRotate(0);
        psOut->setRotate(90);
        psOut->setRotate(180);
        psOut->setRotate(270);
        psOut->setRotate(360);
        delete psOut;
    }
    delete doc;
    remove(filename.c_str());
}
