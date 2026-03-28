#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AnnotStampImageHelper.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <cstring>

class AnnotStampImageHelperTest_732 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal valid PDFDoc for testing
    // We need a real PDFDoc to construct AnnotStampImageHelper
    std::unique_ptr<PDFDoc> createTestPDFDoc() {
        // Create a minimal PDF in memory
        static const char *minimalPDF =
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

        int len = strlen(minimalPDF);
        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, len, Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

// Test that getWidth returns the width passed during construction
TEST_F(AnnotStampImageHelperTest_732, GetWidthReturnsCorrectValue_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 100;
    int testHeight = 200;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight * 3; // RGB
    std::vector<char> data(dataLength, 0);

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength);

    EXPECT_EQ(helper.getWidth(), testWidth);
}

// Test that getHeight returns the height passed during construction
TEST_F(AnnotStampImageHelperTest_732, GetHeightReturnsCorrectValue_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 100;
    int testHeight = 200;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight * 3;
    std::vector<char> data(dataLength, 0);

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength);

    EXPECT_EQ(helper.getHeight(), testHeight);
}

// Test with different dimensions
TEST_F(AnnotStampImageHelperTest_732, GetWidthAndHeightWithDifferentValues_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 50;
    int testHeight = 75;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight * 3;
    std::vector<char> data(dataLength, 0);

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength);

    EXPECT_EQ(helper.getWidth(), testWidth);
    EXPECT_EQ(helper.getHeight(), testHeight);
}

// Test with minimum dimensions (1x1)
TEST_F(AnnotStampImageHelperTest_732, MinimumDimensions_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 1;
    int testHeight = 1;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight * 3;
    std::vector<char> data(dataLength, 0);

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength);

    EXPECT_EQ(helper.getWidth(), 1);
    EXPECT_EQ(helper.getHeight(), 1);
}

// Test that getRef returns a valid Ref
TEST_F(AnnotStampImageHelperTest_732, GetRefReturnsValidRef_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 10;
    int testHeight = 10;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight * 3;
    std::vector<char> data(dataLength, 0);

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength);

    Ref ref = helper.getRef();
    // A valid ref should have a non-negative num
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test constructor with softMaskRef
TEST_F(AnnotStampImageHelperTest_732, ConstructorWithSoftMaskRef_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 20;
    int testHeight = 30;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight * 3;
    std::vector<char> data(dataLength, 0);

    // First create a helper to get a valid ref for soft mask
    int maskWidth = 20;
    int maskHeight = 30;
    int maskDataLength = maskWidth * maskHeight;
    std::vector<char> maskData(maskDataLength, 0);

    AnnotStampImageHelper maskHelper(doc.get(), maskWidth, maskHeight, ColorSpace::DeviceGray, 8, maskData.data(), maskDataLength);
    Ref maskRef = maskHelper.getRef();

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength, maskRef);

    EXPECT_EQ(helper.getWidth(), testWidth);
    EXPECT_EQ(helper.getHeight(), testHeight);
}

// Test with large dimensions
TEST_F(AnnotStampImageHelperTest_732, LargeDimensions_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 1024;
    int testHeight = 768;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight * 3;
    std::vector<char> data(dataLength, 0);

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength);

    EXPECT_EQ(helper.getWidth(), testWidth);
    EXPECT_EQ(helper.getHeight(), testHeight);
}

// Test with DeviceGray color space
TEST_F(AnnotStampImageHelperTest_732, DeviceGrayColorSpace_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testWidth = 32;
    int testHeight = 32;
    int bitsPerComponent = 8;
    int dataLength = testWidth * testHeight; // Gray = 1 component
    std::vector<char> data(dataLength, 128);

    AnnotStampImageHelper helper(doc.get(), testWidth, testHeight, ColorSpace::DeviceGray, bitsPerComponent, data.data(), dataLength);

    EXPECT_EQ(helper.getWidth(), testWidth);
    EXPECT_EQ(helper.getHeight(), testHeight);
}

// Test that two different helpers get different refs
TEST_F(AnnotStampImageHelperTest_732, DifferentHelpersGetDifferentRefs_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int bitsPerComponent = 8;

    int w1 = 10, h1 = 10;
    int dataLength1 = w1 * h1 * 3;
    std::vector<char> data1(dataLength1, 0);
    AnnotStampImageHelper helper1(doc.get(), w1, h1, ColorSpace::DeviceRGB, bitsPerComponent, data1.data(), dataLength1);

    int w2 = 20, h2 = 20;
    int dataLength2 = w2 * h2 * 3;
    std::vector<char> data2(dataLength2, 0);
    AnnotStampImageHelper helper2(doc.get(), w2, h2, ColorSpace::DeviceRGB, bitsPerComponent, data2.data(), dataLength2);

    Ref ref1 = helper1.getRef();
    Ref ref2 = helper2.getRef();

    // Two different image objects should have different refs
    EXPECT_FALSE(ref1.num == ref2.num && ref1.gen == ref2.gen);
}

// Test square image dimensions
TEST_F(AnnotStampImageHelperTest_732, SquareImageDimensions_732) {
    auto doc = createTestPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    int testSize = 256;
    int bitsPerComponent = 8;
    int dataLength = testSize * testSize * 3;
    std::vector<char> data(dataLength, 255);

    AnnotStampImageHelper helper(doc.get(), testSize, testSize, ColorSpace::DeviceRGB, bitsPerComponent, data.data(), dataLength);

    EXPECT_EQ(helper.getWidth(), testSize);
    EXPECT_EQ(helper.getHeight(), testSize);
    EXPECT_EQ(helper.getWidth(), helper.getHeight());
}
