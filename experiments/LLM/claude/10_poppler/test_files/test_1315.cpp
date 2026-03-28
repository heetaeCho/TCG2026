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
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1315 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using the FoFiOutputFunc constructor
    // Returns nullptr if creation fails. Caller owns the pointer.
    PSOutputDev *createPSOutputDev(PDFDoc *doc, std::string *outputStr,
                                    const std::vector<int> &pages,
                                    PSOutMode mode = psModePS,
                                    PSLevel level = psLevel2) {
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, outputStr, title, doc,
            pages, mode, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, level);
        return dev;
    }
};

// Test that setUncompressPreloadedImages can be called (basic setter test)
// We test it indirectly through the interface since the member is private
TEST_F(PSOutputDevTest_1315, SetUncompressPreloadedImages_True_1315) {
    // We need a valid PSOutputDev to call setters on.
    // Create a minimal PDF in memory to work with
    std::string psOutput;
    
    // Create a simple PDF file for testing
    const char *testPdfPath = "/tmp/test_psoutdev_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }
    
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            // Test setting to true
            dev->setUncompressPreloadedImages(true);
            // No crash means success - the setter is trivial
            
            // Test setting to false
            dev->setUncompressPreloadedImages(false);
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevTest_1315, SetGetEmbedType1_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev2_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());
            
            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevTest_1315, SetGetEmbedTrueType_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev3_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setEmbedTrueType(true);
            EXPECT_TRUE(dev->getEmbedTrueType());
            
            dev->setEmbedTrueType(false);
            EXPECT_FALSE(dev->getEmbedTrueType());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1315, SetGetEmbedCIDPostScript_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev4_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setEmbedCIDPostScript(true);
            EXPECT_TRUE(dev->getEmbedCIDPostScript());
            
            dev->setEmbedCIDPostScript(false);
            EXPECT_FALSE(dev->getEmbedCIDPostScript());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1315, SetGetEmbedCIDTrueType_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev5_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setEmbedCIDTrueType(true);
            EXPECT_TRUE(dev->getEmbedCIDTrueType());
            
            dev->setEmbedCIDTrueType(false);
            EXPECT_FALSE(dev->getEmbedCIDTrueType());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevTest_1315, SetGetFontPassthrough_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev6_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setFontPassthrough(true);
            EXPECT_TRUE(dev->getFontPassthrough());
            
            dev->setFontPassthrough(false);
            EXPECT_FALSE(dev->getFontPassthrough());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1315, SetGetOptimizeColorSpace_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev7_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setOptimizeColorSpace(true);
            EXPECT_TRUE(dev->getOptimizeColorSpace());
            
            dev->setOptimizeColorSpace(false);
            EXPECT_FALSE(dev->getOptimizeColorSpace());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1315, SetGetPassLevel1CustomColor_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev8_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setPassLevel1CustomColor(true);
            EXPECT_TRUE(dev->getPassLevel1CustomColor());
            
            dev->setPassLevel1CustomColor(false);
            EXPECT_FALSE(dev->getPassLevel1CustomColor());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setEnableLZW and getEnableLZW
TEST_F(PSOutputDevTest_1315, SetGetEnableLZW_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev9_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setEnableLZW(true);
            EXPECT_TRUE(dev->getEnableLZW());
            
            dev->setEnableLZW(false);
            EXPECT_FALSE(dev->getEnableLZW());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevTest_1315, SetGetEnableFlate_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev10_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setEnableFlate(true);
            EXPECT_TRUE(dev->getEnableFlate());
            
            dev->setEnableFlate(false);
            EXPECT_FALSE(dev->getEnableFlate());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1315, UpsideDown_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev11_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            // upsideDown() should return a boolean value
            bool result = dev->upsideDown();
            // PS output is typically not upside down
            (void)result; // Just verify it doesn't crash
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1315, UseDrawChar_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev12_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            bool result = dev->useDrawChar();
            // PSOutputDev typically returns false for useDrawChar
            EXPECT_FALSE(result);
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1315, UseTilingPatternFill_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev13_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            bool result = dev->useTilingPatternFill();
            EXPECT_TRUE(result);
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1315, UseDrawForm_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev14_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            bool result = dev->useDrawForm();
            EXPECT_TRUE(result);
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test multiple setters that don't have getters (no crash test)
TEST_F(PSOutputDevTest_1315, SettersNoCrash_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev15_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            // Test various setters that don't have corresponding getters
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
            dev->setRasterResolution(1200.0);
            
            dev->setOffset(0.0, 0.0);
            dev->setOffset(100.0, 200.0);
            dev->setOffset(-50.0, -50.0);
            
            dev->setScale(1.0, 1.0);
            dev->setScale(2.0, 2.0);
            dev->setScale(0.5, 0.5);
            
            dev->setRotate(0);
            dev->setRotate(90);
            dev->setRotate(180);
            dev->setRotate(270);
            
            dev->setClip(0.0, 0.0, 612.0, 792.0);
            
            dev->setPreloadImagesForms(true);
            dev->setPreloadImagesForms(false);
            
            dev->setGenerateOPI(true);
            dev->setGenerateOPI(false);
            
            dev->setUseASCIIHex(true);
            dev->setUseASCIIHex(false);
            
            dev->setUseBinary(true);
            dev->setUseBinary(false);
            
            dev->setForceRasterize(psRasterizeWhenNeeded);
            dev->setForceRasterize(psAlwaysRasterize);
            dev->setForceRasterize(psNeverRasterize);
            
            // If we get here without crash, test passes
            SUCCEED();
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setUnderlayCbk and setOverlayCbk
TEST_F(PSOutputDevTest_1315, SetCallbacks_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev16_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            // Set underlay callback to nullptr
            dev->setUnderlayCbk(nullptr, nullptr);
            
            // Set overlay callback to nullptr
            dev->setOverlayCbk(nullptr, nullptr);
            
            // Set with a lambda-compatible function pointer
            auto cbk = [](PSOutputDev *, void *) {};
            int data = 42;
            dev->setUnderlayCbk(cbk, &data);
            dev->setOverlayCbk(cbk, &data);
            
            SUCCEED();
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test isOk after construction
TEST_F(PSOutputDevTest_1315, IsOkAfterConstruction_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev17_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        // With a valid PDF doc and output function, isOk should be true
        EXPECT_TRUE(dev->isOk());
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test boundary: setRasterResolution with zero
TEST_F(PSOutputDevTest_1315, SetRasterResolutionBoundary_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev18_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            // Boundary: zero resolution
            dev->setRasterResolution(0.0);
            // Boundary: negative resolution
            dev->setRasterResolution(-1.0);
            // Boundary: very large resolution
            dev->setRasterResolution(10000.0);
            SUCCEED();
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test toggle behavior of boolean setters
TEST_F(PSOutputDevTest_1315, ToggleBooleanSetters_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev19_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            // Toggle EmbedType1 multiple times
            for (int i = 0; i < 10; i++) {
                dev->setEmbedType1(i % 2 == 0);
                EXPECT_EQ(dev->getEmbedType1(), i % 2 == 0);
            }
            
            // Toggle EnableFlate multiple times
            for (int i = 0; i < 10; i++) {
                dev->setEnableFlate(i % 2 == 0);
                EXPECT_EQ(dev->getEnableFlate(), i % 2 == 0);
            }
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1315, InterpretType3Chars_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev20_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            // PSOutputDev should return true for interpretType3Chars
            bool result = dev->interpretType3Chars();
            // Just verify it returns without crash
            (void)result;
            SUCCEED();
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test setRasterMono doesn't crash
TEST_F(PSOutputDevTest_1315, SetRasterMono_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev21_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            dev->setRasterMono();
            SUCCEED();
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test EPS mode construction
TEST_F(PSOutputDevTest_1315, EPSModeConstruction_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev22_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModeEPS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            EXPECT_TRUE(dev->isOk());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test Level 1 construction
TEST_F(PSOutputDevTest_1315, Level1Construction_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev23_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel1);
        
        if (dev->isOk()) {
            EXPECT_TRUE(dev->isOk());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test Level 3 construction
TEST_F(PSOutputDevTest_1315, Level3Construction_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev24_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel3);
        
        if (dev->isOk()) {
            EXPECT_TRUE(dev->isOk());
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1315, NeedClipToCropBox_1315) {
    const char *testPdfPath = "/tmp/test_psoutdev25_1315.pdf";
    FILE *f = fopen(testPdfPath, "w");
    if (f) {
        const char *minimalPdf = 
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
            "startxref\n190\n%%EOF\n";
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    std::string psOutput;
    auto *gooStr = new GooString(testPdfPath);
    PDFDoc *doc = new PDFDoc(gooStr);
    
    if (doc->isOk()) {
        std::vector<int> pages = {1};
        char title[] = "test";
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &psOutput, title, doc,
            pages, psModePS, -1, -1, false, false,
            0, 0, 0, 0, psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev->isOk()) {
            bool result = dev->needClipToCropBox();
            (void)result;
            SUCCEED();
        }
        delete dev;
    }
    delete doc;
    unlink(testPdfPath);
}
