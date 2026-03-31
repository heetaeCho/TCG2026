#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>

#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

// Output function that writes to a string buffer
void outputToString(void *stream, const char *data, size_t len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

class PSOutputDevTest_1299 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal valid PDF in a temp file and return a PDFDoc
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF file
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
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n199\n%%EOF\n";

        tmpFileName = std::tmpnam(nullptr);
        tmpFileName += ".pdf";
        std::ofstream ofs(tmpFileName, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
        ofs.close();

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFileName.c_str()));
        return doc;
    }

    std::string tmpFileName;
};

// Test needClipToCropBox returns true when mode is psModeEPS
TEST_F(PSOutputDevTest_1299, NeedClipToCropBoxReturnsTrueForEPS_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModeEPS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (psOut.isOk()) {
        EXPECT_TRUE(psOut.needClipToCropBox());
    } else {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }
    std::remove(tmpFileName.c_str());
}

// Test needClipToCropBox returns false when mode is psModePS
TEST_F(PSOutputDevTest_1299, NeedClipToCropBoxReturnsFalseForPS_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (psOut.isOk()) {
        EXPECT_FALSE(psOut.needClipToCropBox());
    } else {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }
    std::remove(tmpFileName.c_str());
}

// Test needClipToCropBox returns false when mode is psModeForm
TEST_F(PSOutputDevTest_1299, NeedClipToCropBoxReturnsFalseForForm_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModeForm,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (psOut.isOk()) {
        EXPECT_FALSE(psOut.needClipToCropBox());
    } else {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }
    std::remove(tmpFileName.c_str());
}

// Test setter/getter for EmbedType1
TEST_F(PSOutputDevTest_1299, SetGetEmbedType1_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedType1(true);
    EXPECT_TRUE(psOut.getEmbedType1());

    psOut.setEmbedType1(false);
    EXPECT_FALSE(psOut.getEmbedType1());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for EmbedTrueType
TEST_F(PSOutputDevTest_1299, SetGetEmbedTrueType_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedTrueType(true);
    EXPECT_TRUE(psOut.getEmbedTrueType());

    psOut.setEmbedTrueType(false);
    EXPECT_FALSE(psOut.getEmbedTrueType());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for EmbedCIDPostScript
TEST_F(PSOutputDevTest_1299, SetGetEmbedCIDPostScript_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOut.getEmbedCIDPostScript());

    psOut.setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOut.getEmbedCIDPostScript());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for EmbedCIDTrueType
TEST_F(PSOutputDevTest_1299, SetGetEmbedCIDTrueType_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEmbedCIDTrueType(true);
    EXPECT_TRUE(psOut.getEmbedCIDTrueType());

    psOut.setEmbedCIDTrueType(false);
    EXPECT_FALSE(psOut.getEmbedCIDTrueType());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for FontPassthrough
TEST_F(PSOutputDevTest_1299, SetGetFontPassthrough_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setFontPassthrough(true);
    EXPECT_TRUE(psOut.getFontPassthrough());

    psOut.setFontPassthrough(false);
    EXPECT_FALSE(psOut.getFontPassthrough());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for OptimizeColorSpace
TEST_F(PSOutputDevTest_1299, SetGetOptimizeColorSpace_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setOptimizeColorSpace(true);
    EXPECT_TRUE(psOut.getOptimizeColorSpace());

    psOut.setOptimizeColorSpace(false);
    EXPECT_FALSE(psOut.getOptimizeColorSpace());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for EnableLZW
TEST_F(PSOutputDevTest_1299, SetGetEnableLZW_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEnableLZW(true);
    EXPECT_TRUE(psOut.getEnableLZW());

    psOut.setEnableLZW(false);
    EXPECT_FALSE(psOut.getEnableLZW());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for EnableFlate
TEST_F(PSOutputDevTest_1299, SetGetEnableFlate_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setEnableFlate(true);
    EXPECT_TRUE(psOut.getEnableFlate());

    psOut.setEnableFlate(false);
    EXPECT_FALSE(psOut.getEnableFlate());

    std::remove(tmpFileName.c_str());
}

// Test setter/getter for PassLevel1CustomColor
TEST_F(PSOutputDevTest_1299, SetGetPassLevel1CustomColor_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    psOut.setPassLevel1CustomColor(true);
    EXPECT_TRUE(psOut.getPassLevel1CustomColor());

    psOut.setPassLevel1CustomColor(false);
    EXPECT_FALSE(psOut.getPassLevel1CustomColor());

    std::remove(tmpFileName.c_str());
}

// Test upsideDown returns expected value
TEST_F(PSOutputDevTest_1299, UpsideDown_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // upsideDown() should return a bool - just verify it doesn't crash
    bool result = psOut.upsideDown();
    // PS coordinate system is typically not upside down
    (void)result;

    std::remove(tmpFileName.c_str());
}

// Test useDrawChar
TEST_F(PSOutputDevTest_1299, UseDrawChar_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    // Just verify it returns a valid bool without crashing
    bool result = psOut.useDrawChar();
    (void)result;

    std::remove(tmpFileName.c_str());
}

// Test interpretType3Chars
TEST_F(PSOutputDevTest_1299, InterpretType3Chars_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.interpretType3Chars();
    (void)result;

    std::remove(tmpFileName.c_str());
}

// Test useTilingPatternFill
TEST_F(PSOutputDevTest_1299, UseTilingPatternFill_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.useTilingPatternFill();
    (void)result;

    std::remove(tmpFileName.c_str());
}

// Test useDrawForm
TEST_F(PSOutputDevTest_1299, UseDrawForm_1299) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::string output;
    std::vector<int> pages = {1};
    char title[] = "test";

    PSOutputDev psOut(outputToString, &output, title, doc.get(),
                      pages, psModePS,
                      0, 0, false, false,
                      0, 0, 0, 0,
                      psRasterizeWhenNeeded, true,
                      nullptr, nullptr, psLevel2);

    if (!psOut.isOk()) {
        GTEST_SKIP() << "PSOutputDev initialization failed";
    }

    bool result = psOut.useDrawForm();
    (void)result;

    std::remove(tmpFileName.c_str());
}

} // namespace
