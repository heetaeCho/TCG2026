#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Output function that writes to a std::string buffer
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string*>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1326 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev using FoFiOutputFunc constructor
    // Returns nullptr if creation fails
    PSOutputDev* createPSOutputDev(PDFDoc* doc, const std::vector<int>& pages) {
        PSOutputDev* dev = new PSOutputDev(
            outputToString,      // outputFuncA
            &outputBuffer,       // outputStreamA
            nullptr,             // psTitleA
            doc,                 // docA
            pages,               // pages
            psModePS,            // modeA
            -1,                  // paperWidthA
            -1,                  // paperHeightA
            false,               // noCrop
            true,                // duplexA
            0, 0, 0, 0,         // imgLLX, imgLLY, imgURX, imgURY
            psRasterizeWhenNeeded, // forceRasterizeA
            false,               // manualCtrlA
            nullptr,             // customCodeCbkA
            nullptr,             // customCodeCbkDataA
            psLevel2             // levelA
        );
        return dev;
    }

    std::string outputBuffer;
};

// Test setEmbedType1 / getEmbedType1
TEST_F(PSOutputDevTest_1326, SetGetEmbedType1_True_1326) {
    // We need a valid PDF to create PSOutputDev. Use a minimal approach.
    GooString fileName("./test_minimal.pdf");
    
    // Try to create with a simple file - if doc is not available, 
    // we test the setter/getter pattern through the FoFiOutputFunc constructor
    std::vector<int> pages = {1};
    
    // Create a minimal PDF in memory for testing
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
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    // Write minimal PDF to temp file
    FILE* f = fopen("/tmp/test_psoutputdev_1326.pdf", "w");
    if (f) {
        fwrite(minimalPdf, 1, strlen(minimalPdf), f);
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Test setEmbedType1 / getEmbedType1
    dev->setEmbedType1(true);
    EXPECT_TRUE(dev->getEmbedType1());

    dev->setEmbedType1(false);
    EXPECT_FALSE(dev->getEmbedType1());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetEmbedTrueType_1326) {
    FILE* f = fopen("/tmp/test_psoutputdev_1326.pdf", "r");
    if (!f) {
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
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n183\n%%EOF\n";
        f = fopen("/tmp/test_psoutputdev_1326.pdf", "w");
        if (f) {
            fwrite(minimalPdf, 1, strlen(minimalPdf), f);
            fclose(f);
        }
    } else {
        fclose(f);
    }

    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setEmbedTrueType(true);
    EXPECT_TRUE(dev->getEmbedTrueType());

    dev->setEmbedTrueType(false);
    EXPECT_FALSE(dev->getEmbedTrueType());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetEmbedCIDPostScript_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(dev->getEmbedCIDPostScript());

    dev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(dev->getEmbedCIDPostScript());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetEmbedCIDTrueType_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setEmbedCIDTrueType(true);
    EXPECT_TRUE(dev->getEmbedCIDTrueType());

    dev->setEmbedCIDTrueType(false);
    EXPECT_FALSE(dev->getEmbedCIDTrueType());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetFontPassthrough_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setFontPassthrough(true);
    EXPECT_TRUE(dev->getFontPassthrough());

    dev->setFontPassthrough(false);
    EXPECT_FALSE(dev->getFontPassthrough());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetOptimizeColorSpace_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setOptimizeColorSpace(true);
    EXPECT_TRUE(dev->getOptimizeColorSpace());

    dev->setOptimizeColorSpace(false);
    EXPECT_FALSE(dev->getOptimizeColorSpace());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetPassLevel1CustomColor_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(dev->getPassLevel1CustomColor());

    dev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(dev->getPassLevel1CustomColor());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetEnableLZW_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setEnableLZW(true);
    EXPECT_TRUE(dev->getEnableLZW());

    dev->setEnableLZW(false);
    EXPECT_FALSE(dev->getEnableLZW());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetEnableFlate_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setEnableFlate(true);
    EXPECT_TRUE(dev->getEnableFlate());

    dev->setEnableFlate(false);
    EXPECT_FALSE(dev->getEnableFlate());

    delete dev;
}

TEST_F(PSOutputDevTest_1326, UpsideDown_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // upsideDown() should return a consistent boolean value
    bool result = dev->upsideDown();
    // PS coordinate system is not upside down typically
    EXPECT_FALSE(result);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, UseDrawChar_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // useDrawChar should return a boolean
    bool result = dev->useDrawChar();
    EXPECT_FALSE(result);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, UseTilingPatternFill_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, UseDrawForm_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = dev->useDrawForm();
    EXPECT_TRUE(result);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, InterpretType3Chars_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = dev->interpretType3Chars();
    // PSOutputDev should interpret type3 chars
    EXPECT_FALSE(result);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetDisplayText_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Should not crash
    dev->setDisplayText(true);
    dev->setDisplayText(false);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetPSCenter_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setPSCenter(true);
    dev->setPSCenter(false);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetPSExpandSmaller_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setPSExpandSmaller(true);
    dev->setPSExpandSmaller(false);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetPSShrinkLarger_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setPSShrinkLarger(true);
    dev->setPSShrinkLarger(false);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetOverprintPreview_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setOverprintPreview(true);
    dev->setOverprintPreview(false);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetRasterResolution_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setRasterResolution(300.0);
    dev->setRasterResolution(72.0);
    dev->setRasterResolution(1200.0);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetOffset_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setOffset(10.0, 20.0);
    dev->setOffset(0.0, 0.0);
    dev->setOffset(-5.0, -10.0);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetScale_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setScale(1.0, 1.0);
    dev->setScale(2.0, 2.0);
    dev->setScale(0.5, 0.5);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetRotate_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setRotate(0);
    dev->setRotate(90);
    dev->setRotate(180);
    dev->setRotate(270);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetClip_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setClip(0.0, 0.0, 612.0, 792.0);
    dev->setClip(100.0, 100.0, 500.0, 700.0);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetGetMultipleBooleanProperties_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Test setting all boolean properties to true
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

    // Test setting all boolean properties to false
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

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SettersWithoutGettersDontCrash_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // These setters don't have corresponding getters, just verify they don't crash
    dev->setPreloadImagesForms(true);
    dev->setPreloadImagesForms(false);
    dev->setGenerateOPI(true);
    dev->setGenerateOPI(false);
    dev->setUseASCIIHex(true);
    dev->setUseASCIIHex(false);
    dev->setUseBinary(true);
    dev->setUseBinary(false);
    dev->setRasterAntialias(true);
    dev->setRasterAntialias(false);
    dev->setUncompressPreloadedImages(true);
    dev->setUncompressPreloadedImages(false);
    dev->setRasterMono();

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetUnderlayCbk_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Set underlay callback to nullptr
    dev->setUnderlayCbk(nullptr, nullptr);

    // Set a real callback
    int userData = 42;
    dev->setUnderlayCbk([](PSOutputDev*, void*) {}, &userData);

    // Set back to nullptr
    dev->setUnderlayCbk(nullptr, nullptr);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetOverlayCbk_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setOverlayCbk(nullptr, nullptr);

    int userData = 99;
    dev->setOverlayCbk([](PSOutputDev*, void*) {}, &userData);

    dev->setOverlayCbk(nullptr, nullptr);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, UseShadedFills_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Test different shading types
    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        // Just verify it returns without crashing and returns a bool
        (void)result;
    }

    delete dev;
}

TEST_F(PSOutputDevTest_1326, ToggleEmbedTrueTypeRapidly_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Rapidly toggle to ensure consistency
    for (int i = 0; i < 100; ++i) {
        bool val = (i % 2 == 0);
        dev->setEmbedTrueType(val);
        EXPECT_EQ(dev->getEmbedTrueType(), val);
    }

    delete dev;
}

TEST_F(PSOutputDevTest_1326, IsOk_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    // isOk() should return true for a properly initialized device
    bool ok = dev->isOk();
    EXPECT_TRUE(ok);

    delete dev;
}

TEST_F(PSOutputDevTest_1326, NeedClipToCropBox_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = dev->needClipToCropBox();
    // Just verify it returns a boolean without crashing
    (void)result;

    delete dev;
}

TEST_F(PSOutputDevTest_1326, SetForceRasterize_1326) {
    auto gooFileName = std::make_unique<GooString>("/tmp/test_psoutputdev_1326.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(gooFileName));

    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    std::vector<int> pages = {1};
    PSOutputDev* dev = createPSOutputDev(doc.get(), pages);
    ASSERT_NE(dev, nullptr);

    if (!dev->isOk()) {
        delete dev;
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    dev->setForceRasterize(psRasterizeWhenNeeded);
    dev->setForceRasterize(psAlwaysRasterize);
    dev->setForceRasterize(psNeverRasterize);

    delete dev;
}
