#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper: output function that writes to a std::string
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1336 : public ::testing::Test {
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
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages, std::string *outputBuf) {
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, outputBuf,
            nullptr, // psTitleA
            doc,
            pages,
            psModePS,   // modeA
            -1, -1,     // paperWidth, paperHeight
            false,      // noCrop
            true,       // duplex
            0, 0, 0, 0, // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterize
            false,      // manualCtrl
            nullptr,    // customCodeCbk
            nullptr,    // customCodeCbkData
            psLevel2    // level
        );
        return dev;
    }
};

// Test setEnableLZW and getEnableLZW - setting to true
TEST_F(PSOutputDevTest_1336, SetEnableLZW_True_1336) {
    // We need a valid PDFDoc. Use a minimal approach: create from a simple PDF file.
    // Since we can't easily create a full PDFDoc in isolation, we test with the
    // FoFiOutputFunc constructor using a simple blank document if available.
    // For this test, we focus on the setter/getter behavior.
    // We'll try to create PSOutputDev with a file-based constructor and test if it fails gracefully.
    
    // Create a minimal PDF in memory
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to a temporary file
    const char *tmpFile = "/tmp/test_psoutputdev_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));
    
    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);
        
        if (dev && dev->isOk()) {
            dev->setEnableLZW(true);
            EXPECT_TRUE(dev->getEnableLZW());
            
            dev->setEnableLZW(false);
            EXPECT_FALSE(dev->getEnableLZW());
        }
        
        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEnableFlate and getEnableFlate
TEST_F(PSOutputDevTest_1336, SetEnableFlate_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_flate_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setEnableFlate(true);
            EXPECT_TRUE(dev->getEnableFlate());

            dev->setEnableFlate(false);
            EXPECT_FALSE(dev->getEnableFlate());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedType1 and getEmbedType1
TEST_F(PSOutputDevTest_1336, SetEmbedType1_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_embedtype1_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());

            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedTrueType and getEmbedTrueType
TEST_F(PSOutputDevTest_1336, SetEmbedTrueType_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_embedtt_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setEmbedTrueType(true);
            EXPECT_TRUE(dev->getEmbedTrueType());

            dev->setEmbedTrueType(false);
            EXPECT_FALSE(dev->getEmbedTrueType());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedCIDPostScript and getEmbedCIDPostScript
TEST_F(PSOutputDevTest_1336, SetEmbedCIDPostScript_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_cidps_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setEmbedCIDPostScript(true);
            EXPECT_TRUE(dev->getEmbedCIDPostScript());

            dev->setEmbedCIDPostScript(false);
            EXPECT_FALSE(dev->getEmbedCIDPostScript());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setEmbedCIDTrueType and getEmbedCIDTrueType
TEST_F(PSOutputDevTest_1336, SetEmbedCIDTrueType_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_cidtt_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setEmbedCIDTrueType(true);
            EXPECT_TRUE(dev->getEmbedCIDTrueType());

            dev->setEmbedCIDTrueType(false);
            EXPECT_FALSE(dev->getEmbedCIDTrueType());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDevTest_1336, SetFontPassthrough_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_fontpass_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setFontPassthrough(true);
            EXPECT_TRUE(dev->getFontPassthrough());

            dev->setFontPassthrough(false);
            EXPECT_FALSE(dev->getFontPassthrough());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setOptimizeColorSpace and getOptimizeColorSpace
TEST_F(PSOutputDevTest_1336, SetOptimizeColorSpace_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_optcolor_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setOptimizeColorSpace(true);
            EXPECT_TRUE(dev->getOptimizeColorSpace());

            dev->setOptimizeColorSpace(false);
            EXPECT_FALSE(dev->getOptimizeColorSpace());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPassLevel1CustomColor and getPassLevel1CustomColor
TEST_F(PSOutputDevTest_1336, SetPassLevel1CustomColor_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_passlvl1_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setPassLevel1CustomColor(true);
            EXPECT_TRUE(dev->getPassLevel1CustomColor());

            dev->setPassLevel1CustomColor(false);
            EXPECT_FALSE(dev->getPassLevel1CustomColor());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1336, UpsideDown_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_upsidedown_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            // upsideDown() should return a bool - just verify it doesn't crash
            bool result = dev->upsideDown();
            (void)result; // We just verify it's callable
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1336, UseDrawChar_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_usedrawchar_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            bool result = dev->useDrawChar();
            (void)result;
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test multiple setters toggling boolean properties back and forth
TEST_F(PSOutputDevTest_1336, ToggleBooleanProperties_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_toggle_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            // Toggle LZW multiple times
            dev->setEnableLZW(true);
            EXPECT_TRUE(dev->getEnableLZW());
            dev->setEnableLZW(false);
            EXPECT_FALSE(dev->getEnableLZW());
            dev->setEnableLZW(true);
            EXPECT_TRUE(dev->getEnableLZW());

            // Toggle Flate multiple times
            dev->setEnableFlate(false);
            EXPECT_FALSE(dev->getEnableFlate());
            dev->setEnableFlate(true);
            EXPECT_TRUE(dev->getEnableFlate());

            // Toggle EmbedType1 
            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test that setDisplayText doesn't crash
TEST_F(PSOutputDevTest_1336, SetDisplayText_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_displaytext_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setDisplayText(true);
            dev->setDisplayText(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPSCenter
TEST_F(PSOutputDevTest_1336, SetPSCenter_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_pscenter_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setPSCenter(true);
            dev->setPSCenter(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1336, SetPSExpandShrink_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_expandshrink_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setPSExpandSmaller(true);
            dev->setPSExpandSmaller(false);
            dev->setPSShrinkLarger(true);
            dev->setPSShrinkLarger(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1336, SetOverprintPreview_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_overprint_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setOverprintPreview(true);
            dev->setOverprintPreview(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setOffset and setScale
TEST_F(PSOutputDevTest_1336, SetOffsetAndScale_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_offsetscale_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setOffset(10.0, 20.0);
            dev->setScale(1.5, 2.0);
            dev->setRotate(90);
            dev->setClip(0.0, 0.0, 612.0, 792.0);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1336, SetRasterResolution_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_rasterres_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setRasterResolution(300.0);
            dev->setRasterResolution(72.0);
            dev->setRasterResolution(600.0);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1336, SetRasterAntialias_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_antialias_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setRasterAntialias(true);
            dev->setRasterAntialias(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1336, SetUncompressPreloadedImages_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_uncompress_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setUncompressPreloadedImages(true);
            dev->setUncompressPreloadedImages(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setUseASCIIHex and setUseBinary
TEST_F(PSOutputDevTest_1336, SetUseASCIIHexAndBinary_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_asciibinary_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setUseASCIIHex(true);
            dev->setUseASCIIHex(false);
            dev->setUseBinary(true);
            dev->setUseBinary(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setGenerateOPI and setPreloadImagesForms
TEST_F(PSOutputDevTest_1336, SetGenerateOPIAndPreload_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_opipreload_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setGenerateOPI(true);
            dev->setGenerateOPI(false);
            dev->setPreloadImagesForms(true);
            dev->setPreloadImagesForms(false);
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test isOk returns true for valid construction
TEST_F(PSOutputDevTest_1336, IsOk_ValidConstruction_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_isok_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev) {
            EXPECT_TRUE(dev->isOk());
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}

// Test setRasterMono doesn't crash
TEST_F(PSOutputDevTest_1336, SetRasterMono_1336) {
    const char *minimalPdf =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpFile = "/tmp/test_psoutputdev_rastermono_1336.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFilename = std::make_unique<GooString>(tmpFile);
    PDFDoc *doc = new PDFDoc(std::move(gooFilename));

    if (doc->isOk()) {
        std::string outputBuf;
        std::vector<int> pages = {1};
        PSOutputDev *dev = createPSOutputDev(doc, pages, &outputBuf);

        if (dev && dev->isOk()) {
            dev->setRasterMono();
            SUCCEED();
        }

        delete dev;
    }
    delete doc;
    unlink(tmpFile);
}
