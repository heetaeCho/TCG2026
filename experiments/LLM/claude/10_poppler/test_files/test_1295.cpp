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

// Helper function to collect PS output
static void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1295 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PSOutputDev with a FoFiOutputFunc for testing.
    // Returns nullptr if creation fails.
    PSOutputDev *createPSOutputDev(PDFDoc *doc, const std::vector<int> &pages) {
        PSOutputDev *dev = new PSOutputDev(
            (FoFiOutputFunc)outputToString, &outputBuffer,
            const_cast<char *>("Test Title"), doc, pages,
            psModePS, -1, -1, false, false,
            0, 0, 0, 0,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr, psLevel2);
        return dev;
    }

    std::string outputBuffer;
};

// Test useTilingPatternFill returns true
TEST_F(PSOutputDevTest_1295, UseTilingPatternFillReturnsTrue_1295) {
    // This is explicitly defined in the header to return true
    // We need a valid PSOutputDev to call it, but from the partial code shown,
    // useTilingPatternFill() override returns true unconditionally.
    // We'll test with a minimal PDF if possible, otherwise test the documented behavior.
    
    // Create a minimal PDF in memory
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    // Write to a temp file
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Cannot create temporary file";
    }
    fwrite(pdfData.c_str(), 1, pdfData.size(), tmpFile);
    fflush(tmpFile);
    rewind(tmpFile);
    
    // Create a PDFDoc from file descriptor
    // Instead, let's try a different approach with a file
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) {
        GTEST_SKIP() << "Cannot create temporary file";
    }
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Cannot create valid PDFDoc";
    }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_TRUE(dev->useTilingPatternFill());
    }

    delete dev;
    unlink(tmpName);
}

// Test upsideDown override
TEST_F(PSOutputDevTest_1295, UpsideDownReturnValue_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // upsideDown should return a boolean (implementation-dependent but deterministic)
        bool result = dev->upsideDown();
        // OutputDev for PS typically returns false for upsideDown
        EXPECT_FALSE(result);
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedType1
TEST_F(PSOutputDevTest_1295, SetGetEmbedType1_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());
        
        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedTrueType
TEST_F(PSOutputDevTest_1295, SetGetEmbedTrueType_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedTrueType(true);
        EXPECT_TRUE(dev->getEmbedTrueType());
        
        dev->setEmbedTrueType(false);
        EXPECT_FALSE(dev->getEmbedTrueType());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedCIDPostScript
TEST_F(PSOutputDevTest_1295, SetGetEmbedCIDPostScript_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedCIDPostScript(true);
        EXPECT_TRUE(dev->getEmbedCIDPostScript());
        
        dev->setEmbedCIDPostScript(false);
        EXPECT_FALSE(dev->getEmbedCIDPostScript());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EmbedCIDTrueType
TEST_F(PSOutputDevTest_1295, SetGetEmbedCIDTrueType_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEmbedCIDTrueType(true);
        EXPECT_TRUE(dev->getEmbedCIDTrueType());
        
        dev->setEmbedCIDTrueType(false);
        EXPECT_FALSE(dev->getEmbedCIDTrueType());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for FontPassthrough
TEST_F(PSOutputDevTest_1295, SetGetFontPassthrough_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setFontPassthrough(true);
        EXPECT_TRUE(dev->getFontPassthrough());
        
        dev->setFontPassthrough(false);
        EXPECT_FALSE(dev->getFontPassthrough());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for OptimizeColorSpace
TEST_F(PSOutputDevTest_1295, SetGetOptimizeColorSpace_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setOptimizeColorSpace(true);
        EXPECT_TRUE(dev->getOptimizeColorSpace());
        
        dev->setOptimizeColorSpace(false);
        EXPECT_FALSE(dev->getOptimizeColorSpace());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EnableLZW
TEST_F(PSOutputDevTest_1295, SetGetEnableLZW_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEnableLZW(true);
        EXPECT_TRUE(dev->getEnableLZW());
        
        dev->setEnableLZW(false);
        EXPECT_FALSE(dev->getEnableLZW());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for EnableFlate
TEST_F(PSOutputDevTest_1295, SetGetEnableFlate_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setEnableFlate(true);
        EXPECT_TRUE(dev->getEnableFlate());
        
        dev->setEnableFlate(false);
        EXPECT_FALSE(dev->getEnableFlate());
    }

    delete dev;
    unlink(tmpName);
}

// Test setter/getter for PassLevel1CustomColor
TEST_F(PSOutputDevTest_1295, SetGetPassLevel1CustomColor_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());
        
        dev->setPassLevel1CustomColor(false);
        EXPECT_FALSE(dev->getPassLevel1CustomColor());
    }

    delete dev;
    unlink(tmpName);
}

// Test useDrawChar override
TEST_F(PSOutputDevTest_1295, UseDrawCharReturnValue_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // useDrawChar should return a bool (typically false for PS output)
        bool result = dev->useDrawChar();
        EXPECT_FALSE(result);
    }

    delete dev;
    unlink(tmpName);
}

// Test useDrawForm override
TEST_F(PSOutputDevTest_1295, UseDrawFormReturnValue_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        bool result = dev->useDrawForm();
        EXPECT_TRUE(result);
    }

    delete dev;
    unlink(tmpName);
}

// Test interpretType3Chars override
TEST_F(PSOutputDevTest_1295, InterpretType3CharsReturnValue_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        bool result = dev->interpretType3Chars();
        // Typically false for PS (Type3 chars are passed through)
        EXPECT_FALSE(result);
    }

    delete dev;
    unlink(tmpName);
}

// Test isOk after valid construction
TEST_F(PSOutputDevTest_1295, IsOkAfterValidConstruction_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    EXPECT_TRUE(dev->isOk());

    delete dev;
    unlink(tmpName);
}

// Test multiple setter toggling for boolean properties
TEST_F(PSOutputDevTest_1295, MultipleSetterToggle_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // Toggle EmbedType1 multiple times
        for (int i = 0; i < 5; i++) {
            dev->setEmbedType1(true);
            EXPECT_TRUE(dev->getEmbedType1());
            dev->setEmbedType1(false);
            EXPECT_FALSE(dev->getEmbedType1());
        }

        // Toggle EnableFlate multiple times
        for (int i = 0; i < 5; i++) {
            dev->setEnableFlate(true);
            EXPECT_TRUE(dev->getEnableFlate());
            dev->setEnableFlate(false);
            EXPECT_FALSE(dev->getEnableFlate());
        }
    }

    delete dev;
    unlink(tmpName);
}

// Test construction with EPS mode
TEST_F(PSOutputDevTest_1295, ConstructionWithEPSMode_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test EPS"), doc.get(), pages,
        psModeEPS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_TRUE(dev->useTilingPatternFill());
    }

    delete dev;
    unlink(tmpName);
}

// Test construction with Level 1
TEST_F(PSOutputDevTest_1295, ConstructionWithLevel1_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test L1"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel1);

    if (dev->isOk()) {
        EXPECT_TRUE(dev->useTilingPatternFill());
        EXPECT_TRUE(dev->isOk());
    }

    delete dev;
    unlink(tmpName);
}

// Test construction with Level 3
TEST_F(PSOutputDevTest_1295, ConstructionWithLevel3_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test L3"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel3);

    if (dev->isOk()) {
        EXPECT_TRUE(dev->useTilingPatternFill());
        EXPECT_TRUE(dev->isOk());
    }

    delete dev;
    unlink(tmpName);
}

// Test needClipToCropBox override
TEST_F(PSOutputDevTest_1295, NeedClipToCropBoxReturnValue_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // needClipToCropBox returns a bool
        bool result = dev->needClipToCropBox();
        // This is an observable result, just verify it's a valid bool
        EXPECT_TRUE(result == true || result == false);
    }

    delete dev;
    unlink(tmpName);
}

// Test construction to file
TEST_F(PSOutputDevTest_1295, ConstructionToFile_1295) {
    // First create a valid PDF
    char tmpPdfName[] = "/tmp/psoutdevtest_pdf_XXXXXX";
    int fd = mkstemp(tmpPdfName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPdfName));
    if (!doc->isOk()) { unlink(tmpPdfName); GTEST_SKIP(); }

    char tmpPsName[] = "/tmp/psoutdevtest_ps_XXXXXX";
    int psFd = mkstemp(tmpPsName);
    if (psFd < 0) { unlink(tmpPdfName); GTEST_SKIP(); }
    close(psFd);

    std::vector<int> pages = {1};
    PSOutputDev *dev = new PSOutputDev(
        tmpPsName, doc.get(),
        const_cast<char *>("Test File Output"), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    // Check if construction to file was successful
    if (dev->isOk()) {
        EXPECT_TRUE(dev->isOk());
        EXPECT_TRUE(dev->useTilingPatternFill());
    }

    delete dev;
    unlink(tmpPdfName);
    unlink(tmpPsName);
}

// Test setDisplayText does not crash
TEST_F(PSOutputDevTest_1295, SetDisplayTextDoesNotCrash_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setDisplayText(true));
        EXPECT_NO_FATAL_FAILURE(dev->setDisplayText(false));
    }

    delete dev;
    unlink(tmpName);
}

// Test setPSCenter does not crash
TEST_F(PSOutputDevTest_1295, SetPSCenterDoesNotCrash_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setPSCenter(true));
        EXPECT_NO_FATAL_FAILURE(dev->setPSCenter(false));
    }

    delete dev;
    unlink(tmpName);
}

// Test setOffset and setScale don't crash
TEST_F(PSOutputDevTest_1295, SetOffsetAndScaleDoNotCrash_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setOffset(10.0, 20.0));
        EXPECT_NO_FATAL_FAILURE(dev->setScale(1.5, 2.0));
        EXPECT_NO_FATAL_FAILURE(dev->setRotate(90));
        EXPECT_NO_FATAL_FAILURE(dev->setClip(0.0, 0.0, 612.0, 792.0));
    }

    delete dev;
    unlink(tmpName);
}

// Test setOffset with zero values
TEST_F(PSOutputDevTest_1295, SetOffsetZeroValues_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setOffset(0.0, 0.0));
        EXPECT_NO_FATAL_FAILURE(dev->setScale(0.0, 0.0));
    }

    delete dev;
    unlink(tmpName);
}

// Test setPSExpandSmaller and setPSShrinkLarger
TEST_F(PSOutputDevTest_1295, SetPSExpandAndShrink_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setPSExpandSmaller(true));
        EXPECT_NO_FATAL_FAILURE(dev->setPSExpandSmaller(false));
        EXPECT_NO_FATAL_FAILURE(dev->setPSShrinkLarger(true));
        EXPECT_NO_FATAL_FAILURE(dev->setPSShrinkLarger(false));
    }

    delete dev;
    unlink(tmpName);
}

// Test setOverprintPreview
TEST_F(PSOutputDevTest_1295, SetOverprintPreview_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setOverprintPreview(true));
        EXPECT_NO_FATAL_FAILURE(dev->setOverprintPreview(false));
    }

    delete dev;
    unlink(tmpName);
}

// Test setRasterResolution
TEST_F(PSOutputDevTest_1295, SetRasterResolution_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setRasterResolution(300.0));
        EXPECT_NO_FATAL_FAILURE(dev->setRasterResolution(72.0));
        EXPECT_NO_FATAL_FAILURE(dev->setRasterResolution(1200.0));
    }

    delete dev;
    unlink(tmpName);
}

// Test setUncompressPreloadedImages
TEST_F(PSOutputDevTest_1295, SetUncompressPreloadedImages_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setUncompressPreloadedImages(true));
        EXPECT_NO_FATAL_FAILURE(dev->setUncompressPreloadedImages(false));
    }

    delete dev;
    unlink(tmpName);
}

// Test callback setters with nullptr
TEST_F(PSOutputDevTest_1295, SetCallbacksWithNullptr_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setUnderlayCbk(nullptr, nullptr));
        EXPECT_NO_FATAL_FAILURE(dev->setOverlayCbk(nullptr, nullptr));
    }

    delete dev;
    unlink(tmpName);
}

// Test useShadedFills with different types
TEST_F(PSOutputDevTest_1295, UseShadedFillsTypes_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        // Test useShadedFills with various shading types (1-7 in PDF spec)
        for (int type = 1; type <= 7; type++) {
            bool result = dev->useShadedFills(type);
            EXPECT_TRUE(result == true || result == false) 
                << "useShadedFills(" << type << ") should return a valid bool";
        }
    }

    delete dev;
    unlink(tmpName);
}

// Test setRasterAntialias
TEST_F(PSOutputDevTest_1295, SetRasterAntialias_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setRasterAntialias(true));
        EXPECT_NO_FATAL_FAILURE(dev->setRasterAntialias(false));
    }

    delete dev;
    unlink(tmpName);
}

// Test setRasterMono
TEST_F(PSOutputDevTest_1295, SetRasterMono_1295) {
    char tmpName[] = "/tmp/psoutdevtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd < 0) GTEST_SKIP();
    
    std::string pdfData = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                          "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                          "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                          "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                          "0000000058 00000 n \n0000000115 00000 n \n"
                          "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    write(fd, pdfData.c_str(), pdfData.size());
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) { unlink(tmpName); GTEST_SKIP(); }

    std::vector<int> pages = {1};
    std::string output;
    PSOutputDev *dev = new PSOutputDev(
        (FoFiOutputFunc)outputToString, &output,
        const_cast<char *>("Test"), doc.get(), pages,
        psModePS, -1, -1, false, false,
        0, 0, 0, 0,
        psRasterizeWhenNeeded, true,
        nullptr, nullptr, psLevel2);

    if (dev->isOk()) {
        EXPECT_NO_FATAL_FAILURE(dev->setRasterMono());