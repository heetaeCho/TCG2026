bool useShadedFills(int type) override {
    return (type < 4 && level >= psLevel2) || (type == 7 && level >= psLevel3);
}
#include <gtest/gtest.h>
#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <vector>

namespace {

class PSOutputDevUseShadedFillsTest_1296 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temp file and return PDFDoc
    std::unique_ptr<PDFDoc> createMinimalPDF() {
        // Create a minimal PDF file
        const char *pdfContent =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n";

        tmpFile = tmpnam(nullptr);
        FILE *f = fopen(tmpFile.c_str(), "wb");
        if (f) {
            fwrite(pdfContent, 1, strlen(pdfContent), f);
            fclose(f);
        }

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
        return doc;
    }

    static void outputFunc(void *stream, const char *data, size_t len) {
        // Discard output
    }

    std::unique_ptr<PSOutputDev> createPSOutputDev(PSLevel level) {
        auto doc = createMinimalPDF();
        if (!doc || !doc->isOk()) {
            return nullptr;
        }
        docs.push_back(std::move(doc));

        std::vector<int> pages = {1};

        auto dev = std::make_unique<PSOutputDev>(
            outputFunc, nullptr, nullptr,
            docs.back().get(), pages,
            psModePS, 612, 792,
            false, false,
            0, 0, 612, 792,
            psRasterizeWhenNeeded, true,
            nullptr, nullptr,
            level
        );
        return dev;
    }

    void TearDown() override {
        docs.clear();
        if (!tmpFile.empty()) {
            unlink(tmpFile.c_str());
        }
    }

    std::vector<std::unique_ptr<PDFDoc>> docs;
    std::string tmpFile;
};

// Test useShadedFills with psLevel1 - types < 4 should return false
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level1Type1ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel1);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(1));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level1Type2ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel1);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(2));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level1Type3ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel1);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(3));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level1Type7ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel1);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(7));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level1Type4ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel1);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(4));
}

// Test useShadedFills with psLevel1Sep
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level1SepType1ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel1Sep);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(1));
}

// Test useShadedFills with psLevel2 - types < 4 should return true
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type1ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(1));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type2ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(2));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type3ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(3));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type0ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(0));
}

// Test type >= 4 at level2 - should return false (except type 7 needs level3)
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type4ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(4));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type5ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(5));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type6ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(6));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2Type7ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel2);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(7));
}

// Test useShadedFills with psLevel2Sep
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2SepType1ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel2Sep);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(1));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level2SepType7ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel2Sep);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(7));
}

// Test useShadedFills with psLevel3 - types < 4 true, type 7 true
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3Type1ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(1));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3Type3ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(3));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3Type7ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(7));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3Type4ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(4));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3Type5ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(5));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3Type6ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(6));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3Type8ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(8));
}

// Test useShadedFills with psLevel3Sep
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3SepType7ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel3Sep);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(7));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3SepType2ReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel3Sep);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_TRUE(dev->useShadedFills(2));
}

// Boundary: type exactly 4 (not < 4, not 7)
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3SepType4ReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel3Sep);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    EXPECT_FALSE(dev->useShadedFills(4));
}

// Negative type
TEST_F(PSOutputDevUseShadedFillsTest_1296, Level3NegativeTypeReturnsTrue_1296) {
    auto dev = createPSOutputDev(psLevel3);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    // -1 < 4 and level >= psLevel2, so should be true
    EXPECT_TRUE(dev->useShadedFills(-1));
}

TEST_F(PSOutputDevUseShadedFillsTest_1296, Level1NegativeTypeReturnsFalse_1296) {
    auto dev = createPSOutputDev(psLevel1);
    if (!dev || !dev->isOk()) GTEST_SKIP();
    // -1 < 4 but level < psLevel2, so false
    EXPECT_FALSE(dev->useShadedFills(-1));
}

} // namespace
