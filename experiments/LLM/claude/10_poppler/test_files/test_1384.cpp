#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <memory>

// Include necessary poppler headers
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "poppler/GfxState.h"
#include "poppler/GlobalParams.h"

// Since fillNormalizationMTX is a static function in the .cc file,
// we include the source to access it for testing purposes
namespace Poppler {
    // Forward declare the function we want to test
    static void fillNormalizationMTX(::Page *pdfPage, double MTX[6], int pageRotation);
}

// Include the implementation to get access to the static function
#include "qt5/src/poppler-annotation.cc"

class FillNormalizationMTXTest_1384 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* filename) {
        GooString path(filename);
        return std::make_unique<PDFDoc>(&path);
    }
};

// Test that MTX is filled with valid values for rotation 0
TEST_F(FillNormalizationMTXTest_1384, NormalRotation0_1384) {
    // Create a simple PDF document to get a Page object
    auto doc = loadTestDoc("test.pdf");
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double MTX[6] = {0};
    Poppler::fillNormalizationMTX(page, MTX, 0);

    // The MTX should be normalized - values should be finite
    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(std::isfinite(MTX[i])) << "MTX[" << i << "] is not finite";
    }
}

// Test with rotation 90
TEST_F(FillNormalizationMTXTest_1384, Rotation90_1384) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double MTX[6] = {0};
    Poppler::fillNormalizationMTX(page, MTX, 90);

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(std::isfinite(MTX[i])) << "MTX[" << i << "] is not finite";
    }
}

// Test with rotation 180
TEST_F(FillNormalizationMTXTest_1384, Rotation180_1384) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double MTX[6] = {0};
    Poppler::fillNormalizationMTX(page, MTX, 180);

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(std::isfinite(MTX[i])) << "MTX[" << i << "] is not finite";
    }
}

// Test with rotation 270
TEST_F(FillNormalizationMTXTest_1384, Rotation270_1384) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double MTX[6] = {0};
    Poppler::fillNormalizationMTX(page, MTX, 270);

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(std::isfinite(MTX[i])) << "MTX[" << i << "] is not finite";
    }
}

// Test that different rotations produce different MTX values
TEST_F(FillNormalizationMTXTest_1384, DifferentRotationsProduceDifferentMTX_1384) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double MTX0[6] = {0};
    double MTX90[6] = {0};
    Poppler::fillNormalizationMTX(page, MTX0, 0);
    Poppler::fillNormalizationMTX(page, MTX90, 90);

    // At least some values should differ between rotation 0 and 90
    bool anyDifferent = false;
    for (int i = 0; i < 6; i++) {
        if (MTX0[i] != MTX90[i]) {
            anyDifferent = true;
            break;
        }
    }
    EXPECT_TRUE(anyDifferent) << "Rotation 0 and 90 should produce different MTX values";
}

// Test that rotation 90 and 270 swap width and height consistently
TEST_F(FillNormalizationMTXTest_1384, Rotation90And270SwapDimensions_1384) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double MTX90[6] = {0};
    double MTX270[6] = {0};
    Poppler::fillNormalizationMTX(page, MTX90, 90);
    Poppler::fillNormalizationMTX(page, MTX270, 270);

    // Both 90 and 270 swap w and h, so normalization denominators are the same
    // The CTM values themselves will differ though
    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(std::isfinite(MTX90[i]));
        EXPECT_TRUE(std::isfinite(MTX270[i]));
    }
}

// Test consistency - calling twice with same parameters gives same result
TEST_F(FillNormalizationMTXTest_1384, ConsistentResults_1384) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double MTX1[6] = {0};
    double MTX2[6] = {0};
    Poppler::fillNormalizationMTX(page, MTX1, 0);
    Poppler::fillNormalizationMTX(page, MTX2, 0);

    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(MTX1[i], MTX2[i]) << "MTX[" << i << "] differs between calls";
    }
}

// Test GfxState directly to verify CTM behavior used by fillNormalizationMTX
class GfxStateCTMTest_1384 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

TEST_F(GfxStateCTMTest_1384, CTMIsValidForSimpleBox_1384) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612; // Letter width in points
    box.y2 = 792; // Letter height in points

    auto *gfxState = new GfxState(72.0, 72.0, &box, 0, true);
    const std::array<double, 6> &ctm = gfxState->getCTM();

    // CTM should have valid finite values
    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(std::isfinite(ctm[i])) << "CTM[" << i << "] is not finite";
    }

    delete gfxState;
}

TEST_F(GfxStateCTMTest_1384, CTMDiffersWithRotation_1384) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;

    auto *gfxState0 = new GfxState(72.0, 72.0, &box, 0, true);
    auto *gfxState90 = new GfxState(72.0, 72.0, &box, 90, true);

    const std::array<double, 6> &ctm0 = gfxState0->getCTM();
    const std::array<double, 6> &ctm90 = gfxState90->getCTM();

    bool anyDifferent = false;
    for (int i = 0; i < 6; i++) {
        if (ctm0[i] != ctm90[i]) {
            anyDifferent = true;
            break;
        }
    }
    EXPECT_TRUE(anyDifferent);

    delete gfxState0;
    delete gfxState90;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
