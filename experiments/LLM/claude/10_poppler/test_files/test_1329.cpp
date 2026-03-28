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

class PSOutputDevTest_1329 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with FoFiOutputFunc for testing setters/getters
    // Returns nullptr if creation fails. Caller owns the returned pointer.
    PSOutputDev *createPSOutputDev(PDFDoc *doc, std::string *outputStr) {
        std::vector<int> pages;
        pages.push_back(1);

        PSOutputDev *dev = new PSOutputDev(
            outputFunc, outputStr, nullptr, doc, pages,
            psModePS, -1, -1, false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        return dev;
    }

    // Helper to create a simple PDF in memory for testing
    PDFDoc *createSimplePDFDoc(const char *filename) {
        // Create a minimal PDF file for testing
        FILE *f = fopen(filename, "wb");
        if (!f) return nullptr;
        
        const char *pdfContent = 
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
            "startxref\n198\n%%EOF\n";
        
        fwrite(pdfContent, 1, strlen(pdfContent), f);
        fclose(f);
        
        auto *gooFilename = new GooString(filename);
        PDFDoc *doc = new PDFDoc(gooFilename);
        return doc;
    }
};

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevTest_1329, SetFontPassthroughTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_1.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setFontPassthrough(true);
            EXPECT_TRUE(dev->getFontPassthrough());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetFontPassthroughFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_2.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setFontPassthrough(false);
            EXPECT_FALSE(dev->getFontPassthrough());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetFontPassthroughToggle_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_3.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setFontPassthrough(true);
            EXPECT_TRUE(dev->getFontPassthrough());
            dev->setFontPassthrough(false);
            EXPECT_FALSE(dev->getFontPassthrough());
            dev->setFontPassthrough(true);
            EXPECT_TRUE(dev->getFontPassthrough());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevTest_1329, SetEmbedType1True_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_4.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetEmbedType1False_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_5.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevTest_1329, SetEmbedTrueTypeTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_6.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedTrueType(true);
            EXPECT_TRUE(dev->getEmbedTrueType());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetEmbedTrueTypeFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_7.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedTrueType(false);
            EXPECT_FALSE(dev->getEmbedTrueType());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1329, SetEmbedCIDPostScriptTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_8.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedCIDPostScript(true);
            EXPECT_TRUE(dev->getEmbedCIDPostScript());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetEmbedCIDPostScriptFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_9.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedCIDPostScript(false);
            EXPECT_FALSE(dev->getEmbedCIDPostScript());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1329, SetEmbedCIDTrueTypeTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_10.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedCIDTrueType(true);
            EXPECT_TRUE(dev->getEmbedCIDTrueType());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetEmbedCIDTrueTypeFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_11.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedCIDTrueType(false);
            EXPECT_FALSE(dev->getEmbedCIDTrueType());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1329, SetOptimizeColorSpaceTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_12.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setOptimizeColorSpace(true);
            EXPECT_TRUE(dev->getOptimizeColorSpace());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetOptimizeColorSpaceFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_13.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setOptimizeColorSpace(false);
            EXPECT_FALSE(dev->getOptimizeColorSpace());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1329, SetPassLevel1CustomColorTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_14.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setPassLevel1CustomColor(true);
            EXPECT_TRUE(dev->getPassLevel1CustomColor());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetPassLevel1CustomColorFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_15.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setPassLevel1CustomColor(false);
            EXPECT_FALSE(dev->getPassLevel1CustomColor());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEnableLZW and getEnableLZW
TEST_F(PSOutputDevTest_1329, SetEnableLZWTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_16.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEnableLZW(true);
            EXPECT_TRUE(dev->getEnableLZW());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetEnableLZWFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_17.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEnableLZW(false);
            EXPECT_FALSE(dev->getEnableLZW());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevTest_1329, SetEnableFlateTrue_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_18.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEnableFlate(true);
            EXPECT_TRUE(dev->getEnableFlate());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetEnableFlateFalse_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_19.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEnableFlate(false);
            EXPECT_FALSE(dev->getEnableFlate());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test upsideDown
TEST_F(PSOutputDevTest_1329, UpsideDown_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_20.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            // PSOutputDev::upsideDown() should return a bool
            bool result = dev->upsideDown();
            // Just verify it returns without crashing; the actual value depends on implementation
            (void)result;
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1329, UseDrawChar_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_21.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            bool result = dev->useDrawChar();
            (void)result;
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1329, UseTilingPatternFill_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_22.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            bool result = dev->useTilingPatternFill();
            (void)result;
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1329, UseDrawForm_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_23.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            bool result = dev->useDrawForm();
            (void)result;
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1329, InterpretType3Chars_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_24.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            bool result = dev->interpretType3Chars();
            (void)result;
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test needClipToCropBox
TEST_F(PSOutputDevTest_1329, NeedClipToCropBox_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_25.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            bool result = dev->needClipToCropBox();
            (void)result;
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setDisplayText
TEST_F(PSOutputDevTest_1329, SetDisplayText_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_26.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            // Just verify these don't crash
            dev->setDisplayText(true);
            dev->setDisplayText(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1329, SetPSCenter_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_27.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setPSCenter(true);
            dev->setPSCenter(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPSExpandSmaller
TEST_F(PSOutputDevTest_1329, SetPSExpandSmaller_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_28.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setPSExpandSmaller(true);
            dev->setPSExpandSmaller(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPSShrinkLarger
TEST_F(PSOutputDevTest_1329, SetPSShrinkLarger_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_29.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setPSShrinkLarger(true);
            dev->setPSShrinkLarger(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1329, SetOverprintPreview_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_30.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setOverprintPreview(true);
            dev->setOverprintPreview(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1329, SetRasterResolution_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_31.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setRasterResolution(300.0);
            dev->setRasterResolution(72.0);
            dev->setRasterResolution(1200.0);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setOffset
TEST_F(PSOutputDevTest_1329, SetOffset_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_32.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setOffset(0.0, 0.0);
            dev->setOffset(100.0, 200.0);
            dev->setOffset(-50.0, -75.0);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setScale
TEST_F(PSOutputDevTest_1329, SetScale_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_33.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setScale(1.0, 1.0);
            dev->setScale(2.0, 2.0);
            dev->setScale(0.5, 0.5);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setRotate
TEST_F(PSOutputDevTest_1329, SetRotate_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_34.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setRotate(0);
            dev->setRotate(90);
            dev->setRotate(180);
            dev->setRotate(270);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setClip
TEST_F(PSOutputDevTest_1329, SetClip_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_35.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setClip(0.0, 0.0, 612.0, 792.0);
            dev->setClip(72.0, 72.0, 540.0, 720.0);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1329, SetRasterAntialias_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_36.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setRasterAntialias(true);
            dev->setRasterAntialias(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1329, SetUncompressPreloadedImages_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_37.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setUncompressPreloadedImages(true);
            dev->setUncompressPreloadedImages(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPreloadImagesForms
TEST_F(PSOutputDevTest_1329, SetPreloadImagesForms_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_38.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setPreloadImagesForms(true);
            dev->setPreloadImagesForms(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setGenerateOPI
TEST_F(PSOutputDevTest_1329, SetGenerateOPI_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_39.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setGenerateOPI(true);
            dev->setGenerateOPI(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setUseASCIIHex
TEST_F(PSOutputDevTest_1329, SetUseASCIIHex_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_40.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setUseASCIIHex(true);
            dev->setUseASCIIHex(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setUseBinary
TEST_F(PSOutputDevTest_1329, SetUseBinary_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_41.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setUseBinary(true);
            dev->setUseBinary(false);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test isOk for valid construction
TEST_F(PSOutputDevTest_1329, IsOkAfterConstruction_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_42.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        ASSERT_NE(dev, nullptr);
        // If the PDF doc is valid, the PSOutputDev should be ok
        EXPECT_TRUE(dev->isOk());
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test useShadedFills with different types
TEST_F(PSOutputDevTest_1329, UseShadedFills_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_43.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            // Test with different shading types
            for (int type = 1; type <= 7; ++type) {
                bool result = dev->useShadedFills(type);
                (void)result;
            }
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test multiple setter calls in sequence
TEST_F(PSOutputDevTest_1329, MultipleSettersSequence_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_44.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setEmbedType1(true);
            dev->setEmbedTrueType(false);
            dev->setEmbedCIDPostScript(true);
            dev->setEmbedCIDTrueType(false);
            dev->setFontPassthrough(true);
            dev->setOptimizeColorSpace(false);
            dev->setEnableLZW(true);
            dev->setEnableFlate(false);

            EXPECT_TRUE(dev->getEmbedType1());
            EXPECT_FALSE(dev->getEmbedTrueType());
            EXPECT_TRUE(dev->getEmbedCIDPostScript());
            EXPECT_FALSE(dev->getEmbedCIDTrueType());
            EXPECT_TRUE(dev->getFontPassthrough());
            EXPECT_FALSE(dev->getOptimizeColorSpace());
            EXPECT_TRUE(dev->getEnableLZW());
            EXPECT_FALSE(dev->getEnableFlate());
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setForceRasterize
TEST_F(PSOutputDevTest_1329, SetForceRasterize_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_45.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setForceRasterize(psRasterizeWhenNeeded);
            dev->setForceRasterize(psAlwaysRasterize);
            dev->setForceRasterize(psNeverRasterize);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1329, SetRasterMono_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_46.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setRasterMono();
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setUnderlayCbk and setOverlayCbk
static void dummyUnderlayCbk(PSOutputDev *psOut, void *data) {
    // dummy callback
}

static void dummyOverlayCbk(PSOutputDev *psOut, void *data) {
    // dummy callback
}

TEST_F(PSOutputDevTest_1329, SetUnderlayCbk_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_47.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            int data = 42;
            dev->setUnderlayCbk(dummyUnderlayCbk, &data);
            dev->setUnderlayCbk(nullptr, nullptr);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

TEST_F(PSOutputDevTest_1329, SetOverlayCbk_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_48.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            int data = 99;
            dev->setOverlayCbk(dummyOverlayCbk, &data);
            dev->setOverlayCbk(nullptr, nullptr);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test construction with file name
TEST_F(PSOutputDevTest_1329, ConstructWithFileName_1329) {
    const char *tmpPdf = "/tmp/test_ps_1329_49.pdf";
    const char *tmpPs = "/tmp/test_ps_1329_49.ps";
    PDFDoc *doc = createSimplePDFDoc(tmpPdf);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::vector<int> pages;
        pages.push_back(1);
        
        PSOutputDev *dev = new PSOutputDev(
            tmpPs, doc, nullptr, pages,
            psModePS, -1, -1, false, true,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        
        if (dev) {
            EXPECT_TRUE(dev->isOk());
            delete dev;
        }
        unlink(tmpPs);
    }
    delete doc;
    unlink(tmpPdf);
}

// Test boundary: setting raster resolution to zero
TEST_F(PSOutputDevTest_1329, SetRasterResolutionZero_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_50.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setRasterResolution(0.0);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test boundary: negative raster resolution
TEST_F(PSOutputDevTest_1329, SetRasterResolutionNegative_1329) {
    const char *tmpFile = "/tmp/test_ps_1329_51.pdf";
    PDFDoc *doc = createSimplePDFDoc(tmpFile);
    ASSERT_NE(doc, nullptr);
    
    if (doc->isOk()) {
        std::string output;
        PSOutputDev *dev = createPSOutputDev(doc, &output);
        if (dev && dev->isOk()) {
            dev->setRasterResolution(-100.0);
        }
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}
