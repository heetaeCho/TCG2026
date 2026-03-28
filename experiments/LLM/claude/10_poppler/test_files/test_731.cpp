#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "config.h"
#include "poppler/AnnotStampImageHelper.h"
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/GlobalParams.h"

#include <memory>
#include <cstring>
#include <cstdlib>

class AnnotStampImageHelperTest_731 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }

        // Create a minimal valid PDF in memory
        const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        GooString *pdfContent = new GooString(minimalPDF);
        doc = std::make_unique<PDFDoc>(pdfContent);
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(AnnotStampImageHelperTest_731, ConstructorRGBCreatesValidObject_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 10;
    const int height = 10;
    const int bitsPerComponent = 8;
    const int dataLength = width * height * 3; // RGB
    char *data = new char[dataLength];
    std::memset(data, 0xFF, dataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data, dataLength);

    EXPECT_EQ(helper.getWidth(), width);
    EXPECT_EQ(helper.getHeight(), height);

    Ref ref = helper.getRef();
    EXPECT_NE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);

    delete[] data;
}

TEST_F(AnnotStampImageHelperTest_731, ConstructorGrayCreatesValidObject_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 20;
    const int height = 15;
    const int bitsPerComponent = 8;
    const int dataLength = width * height; // Gray
    char *data = new char[dataLength];
    std::memset(data, 0x80, dataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceGray, bitsPerComponent, data, dataLength);

    EXPECT_EQ(helper.getWidth(), width);
    EXPECT_EQ(helper.getHeight(), height);

    Ref ref = helper.getRef();
    EXPECT_NE(ref.num, 0);

    delete[] data;
}

TEST_F(AnnotStampImageHelperTest_731, GetRefReturnsConsistentValue_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 5;
    const int height = 5;
    const int bitsPerComponent = 8;
    const int dataLength = width * height * 3;
    char *data = new char[dataLength];
    std::memset(data, 0x00, dataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data, dataLength);

    Ref ref1 = helper.getRef();
    Ref ref2 = helper.getRef();

    EXPECT_EQ(ref1.num, ref2.num);
    EXPECT_EQ(ref1.gen, ref2.gen);

    delete[] data;
}

TEST_F(AnnotStampImageHelperTest_731, GetWidthReturnsCorrectValue_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 100;
    const int height = 50;
    const int bitsPerComponent = 8;
    const int dataLength = width * height * 3;
    char *data = new char[dataLength];
    std::memset(data, 0x00, dataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data, dataLength);

    EXPECT_EQ(helper.getWidth(), 100);

    delete[] data;
}

TEST_F(AnnotStampImageHelperTest_731, GetHeightReturnsCorrectValue_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 100;
    const int height = 200;
    const int bitsPerComponent = 8;
    const int dataLength = width * height * 3;
    char *data = new char[dataLength];
    std::memset(data, 0x00, dataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data, dataLength);

    EXPECT_EQ(helper.getHeight(), 200);

    delete[] data;
}

TEST_F(AnnotStampImageHelperTest_731, ConstructorWithSoftMaskRef_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    // First create a soft mask image
    const int width = 10;
    const int height = 10;
    const int bitsPerComponent = 8;
    const int maskDataLength = width * height;
    char *maskData = new char[maskDataLength];
    std::memset(maskData, 0xFF, maskDataLength);

    AnnotStampImageHelper maskHelper(doc.get(), width, height, ColorSpace::DeviceGray, bitsPerComponent, maskData, maskDataLength);
    Ref maskRef = maskHelper.getRef();

    // Now create the main image with soft mask
    const int rgbDataLength = width * height * 3;
    char *rgbData = new char[rgbDataLength];
    std::memset(rgbData, 0x80, rgbDataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, rgbData, rgbDataLength, maskRef);

    EXPECT_EQ(helper.getWidth(), width);
    EXPECT_EQ(helper.getHeight(), height);

    Ref ref = helper.getRef();
    EXPECT_NE(ref.num, 0);
    // The main image ref should be different from the mask ref
    EXPECT_NE(ref.num, maskRef.num);

    delete[] maskData;
    delete[] rgbData;
}

TEST_F(AnnotStampImageHelperTest_731, TwoHelpersHaveDifferentRefs_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 5;
    const int height = 5;
    const int bitsPerComponent = 8;
    const int dataLength = width * height * 3;

    char *data1 = new char[dataLength];
    std::memset(data1, 0x00, dataLength);

    char *data2 = new char[dataLength];
    std::memset(data2, 0xFF, dataLength);

    AnnotStampImageHelper helper1(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data1, dataLength);
    AnnotStampImageHelper helper2(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data2, dataLength);

    Ref ref1 = helper1.getRef();
    Ref ref2 = helper2.getRef();

    // Two different image objects should have different refs
    EXPECT_FALSE(ref1.num == ref2.num && ref1.gen == ref2.gen);

    delete[] data1;
    delete[] data2;
}

TEST_F(AnnotStampImageHelperTest_731, SmallImageOneByOne_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 1;
    const int height = 1;
    const int bitsPerComponent = 8;
    const int dataLength = 3; // 1 pixel RGB
    char data[3] = {(char)0xFF, (char)0x00, (char)0x00};

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data, dataLength);

    EXPECT_EQ(helper.getWidth(), 1);
    EXPECT_EQ(helper.getHeight(), 1);
    EXPECT_NE(helper.getRef().num, 0);
}

TEST_F(AnnotStampImageHelperTest_731, RemoveAnnotStampImageObject_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 10;
    const int height = 10;
    const int bitsPerComponent = 8;
    const int dataLength = width * height * 3;
    char *data = new char[dataLength];
    std::memset(data, 0x00, dataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceRGB, bitsPerComponent, data, dataLength);

    Ref ref = helper.getRef();
    EXPECT_NE(ref.num, 0);

    // Should not crash
    helper.removeAnnotStampImageObject();

    delete[] data;
}

TEST_F(AnnotStampImageHelperTest_731, DifferentBitsPerComponent_731) {
    if (!doc->isOk()) {
        GTEST_SKIP() << "PDF document not valid";
    }

    const int width = 8;
    const int height = 8;
    const int bitsPerComponent = 1;
    // For 1 bit per component, DeviceGray: 1 bit per pixel, 8 pixels per byte
    const int dataLength = (width * height) / 8;
    char *data = new char[dataLength];
    std::memset(data, 0xAA, dataLength);

    AnnotStampImageHelper helper(doc.get(), width, height, ColorSpace::DeviceGray, bitsPerComponent, data, dataLength);

    EXPECT_EQ(helper.getWidth(), width);
    EXPECT_EQ(helper.getHeight(), height);

    delete[] data;
}
