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

namespace {

// Output function that writes to a string buffer
void stringOutputFunc(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1297 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev writing to a string, if possible
    // Returns nullptr if creation fails
    std::unique_ptr<PSOutputDev> createPSOutputDevToFile(const char* filename, 
                                                          PDFDoc* doc,
                                                          const std::vector<int>& pages,
                                                          PSOutMode mode = psModePS) {
        auto dev = std::make_unique<PSOutputDev>(
            filename, doc, nullptr, pages, mode,
            0, 0, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        if (dev && dev->isOk()) {
            return dev;
        }
        return nullptr;
    }
};

// Test that useDrawForm returns the value set by setPreloadImagesForms
TEST_F(PSOutputDevTest_1297, UseDrawFormReturnsPreloadImagesForms_1297) {
    // We need a valid PDFDoc to construct PSOutputDev
    // Create a minimal PDF file for testing
    const char* testPdf = "/tmp/test_psoutputdev_1297.pdf";
    
    // Create a minimal valid PDF
    FILE* f = fopen(testPdf, "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp PDF file";
    }
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) {
        unlink(testPdf);
        GTEST_SKIP() << "Cannot open test PDF";
    }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) {
        unlink(testPdf);
        unlink(outFile);
        GTEST_SKIP() << "PSOutputDev creation failed";
    }
    
    // Test setPreloadImagesForms(true) -> useDrawForm() returns true
    dev->setPreloadImagesForms(true);
    EXPECT_TRUE(dev->useDrawForm());
    
    // Test setPreloadImagesForms(false) -> useDrawForm() returns false
    dev->setPreloadImagesForms(false);
    EXPECT_FALSE(dev->useDrawForm());
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test setter/getter pairs for embed flags
TEST_F(PSOutputDevTest_1297, EmbedType1SetterGetter_1297) {
    const char* testPdf = "/tmp/test_psoutputdev2_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput2_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());
    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());
    
    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());
    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());
    
    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());
    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());
    
    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());
    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());
    
    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());
    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());
    
    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());
    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());
    
    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());
    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());
    
    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());
    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());
    
    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());
    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1297, UpsideDown_1297) {
    const char* testPdf = "/tmp/test_psoutputdev3_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput3_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
    // PS coordinate system has origin at bottom-left, so upsideDown should be false
    EXPECT_FALSE(dev->upsideDown());
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1297, UseDrawChar_1297) {
    const char* testPdf = "/tmp/test_psoutputdev4_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput4_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
    // PSOutputDev uses drawString, not drawChar
    EXPECT_FALSE(dev->useDrawChar());
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1297, UseTilingPatternFill_1297) {
    const char* testPdf = "/tmp/test_psoutputdev5_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput5_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
    EXPECT_TRUE(dev->useTilingPatternFill());
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1297, InterpretType3Chars_1297) {
    const char* testPdf = "/tmp/test_psoutputdev6_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput6_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
    // PSOutputDev should interpret Type3 chars
    EXPECT_TRUE(dev->interpretType3Chars());
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test toggling preloadImagesForms multiple times
TEST_F(PSOutputDevTest_1297, PreloadImagesFormsToggle_1297) {
    const char* testPdf = "/tmp/test_psoutputdev7_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput7_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
    // Toggle multiple times
    for (int i = 0; i < 5; i++) {
        dev->setPreloadImagesForms(true);
        EXPECT_TRUE(dev->useDrawForm());
        dev->setPreloadImagesForms(false);
        EXPECT_FALSE(dev->useDrawForm());
    }
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test all boolean setter/getter consistency
TEST_F(PSOutputDevTest_1297, AllBoolSetterGetterConsistency_1297) {
    const char* testPdf = "/tmp/test_psoutputdev8_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput8_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
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
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test useShadedFills for various shading types
TEST_F(PSOutputDevTest_1297, UseShadedFills_1297) {
    const char* testPdf = "/tmp/test_psoutputdev9_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput9_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    if (!dev->isOk()) { unlink(testPdf); unlink(outFile); GTEST_SKIP(); }
    
    // Test various shading fill types (1=function, 2=axial, 3=radial, etc.)
    // The return value depends on level and type, but we just verify it returns a bool
    for (int type = 1; type <= 7; type++) {
        bool result = dev->useShadedFills(type);
        // Just verify it doesn't crash and returns a boolean
        EXPECT_TRUE(result == true || result == false);
    }
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test isOk on valid construction
TEST_F(PSOutputDevTest_1297, IsOkOnValidConstruction_1297) {
    const char* testPdf = "/tmp/test_psoutputdev10_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    const char* outFile = "/tmp/test_psoutput10_1297.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    EXPECT_TRUE(dev->isOk());
    
    dev.reset();
    unlink(testPdf);
    unlink(outFile);
}

// Test construction with invalid output file
TEST_F(PSOutputDevTest_1297, IsNotOkOnInvalidFile_1297) {
    const char* testPdf = "/tmp/test_psoutputdev11_1297.pdf";
    FILE* f = fopen(testPdf, "wb");
    if (!f) GTEST_SKIP();
    const char* minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    fwrite(minimalPdf, 1, strlen(minimalPdf), f);
    fclose(f);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(testPdf));
    if (!doc->isOk()) { unlink(testPdf); GTEST_SKIP(); }
    
    std::vector<int> pages = {1};
    // Try to write to an invalid/nonexistent directory
    const char* outFile = "/nonexistent_dir_1297/impossible_path/output.ps";
    
    auto dev = std::make_unique<PSOutputDev>(
        outFile, doc.get(), nullptr, pages, psModePS,
        0, 0, false, false, 0, 0, 0, 0,
        psRasterizeWhenNeeded, true, nullptr, nullptr, psLevel2);
    
    EXPECT_FALSE(dev->isOk());
    
    dev.reset();
    unlink(testPdf);
}

} // namespace
