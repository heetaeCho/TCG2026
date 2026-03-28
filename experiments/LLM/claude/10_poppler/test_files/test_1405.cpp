#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QImage>
#include <QColor>
#include <memory>

// Include necessary headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "AnnotStampImageHelper.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

namespace {

class StampAnnotationConvertTest_1405 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize globalParams if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        
        // Create a minimal PDFDoc for the AnnotStampImageHelper
        // We need a valid DocumentData with a doc pointer
        docData = std::make_unique<Poppler::DocumentData>(nullptr, nullptr);
    }

    void TearDown() override {
    }

    std::unique_ptr<Poppler::DocumentData> docData;

    Poppler::StampAnnotationPrivate* createStampPrivate() {
        auto* priv = new Poppler::StampAnnotationPrivate();
        priv->parentDoc = docData.get();
        return priv;
    }
};

// Test with RGB888 format - should stay as DeviceRGB
TEST_F(StampAnnotationConvertTest_1405, ConvertRGB888Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(10, 10, QImage::Format_RGB888);
    img.fill(QColor(255, 0, 0));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 10);
    EXPECT_EQ(result->getHeight(), 10);
    
    delete priv;
}

// Test with Grayscale8 format - should stay as DeviceGray
TEST_F(StampAnnotationConvertTest_1405, ConvertGrayscale8Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(8, 8, QImage::Format_Grayscale8);
    img.fill(QColor(128, 128, 128));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 8);
    EXPECT_EQ(result->getHeight(), 8);
    
    delete priv;
}

// Test with ARGB32 format - should produce sMask due to alpha channel
TEST_F(StampAnnotationConvertTest_1405, ConvertARGB32Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(5, 5, QImage::Format_ARGB32);
    img.fill(QColor(255, 0, 0, 128));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 5);
    EXPECT_EQ(result->getHeight(), 5);
    
    delete priv;
}

// Test with Mono format (grayscale) - should be 1 bit DeviceGray
TEST_F(StampAnnotationConvertTest_1405, ConvertMonoGrayImage_1405) {
    auto* priv = createStampPrivate();
    QImage img(16, 16, QImage::Format_Mono);
    img.fill(0);
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 16);
    EXPECT_EQ(result->getHeight(), 16);
    
    delete priv;
}

// Test with RGB32 format - should convert to ARGB32
TEST_F(StampAnnotationConvertTest_1405, ConvertRGB32Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(12, 12, QImage::Format_RGB32);
    img.fill(QColor(0, 255, 0));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 12);
    EXPECT_EQ(result->getHeight(), 12);
    
    delete priv;
}

// Test with Grayscale16 format - should convert to Grayscale8
TEST_F(StampAnnotationConvertTest_1405, ConvertGrayscale16Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(4, 4, QImage::Format_Grayscale16);
    img.fill(QColor(200, 200, 200));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 4);
    EXPECT_EQ(result->getHeight(), 4);
    
    delete priv;
}

// Test with RGB555 format - should convert to RGB888
TEST_F(StampAnnotationConvertTest_1405, ConvertRGB555Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(6, 6, QImage::Format_RGB555);
    img.fill(QColor(100, 150, 200));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 6);
    EXPECT_EQ(result->getHeight(), 6);
    
    delete priv;
}

// Test with RGBA8888 format
TEST_F(StampAnnotationConvertTest_1405, ConvertRGBA8888Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(7, 7, QImage::Format_RGBA8888);
    img.fill(QColor(50, 100, 150, 200));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 7);
    EXPECT_EQ(result->getHeight(), 7);
    
    delete priv;
}

// Test with 1x1 pixel image - boundary case
TEST_F(StampAnnotationConvertTest_1405, ConvertSinglePixelImage_1405) {
    auto* priv = createStampPrivate();
    QImage img(1, 1, QImage::Format_RGB888);
    img.fill(QColor(255, 255, 255));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 1);
    EXPECT_EQ(result->getHeight(), 1);
    
    delete priv;
}

// Test with ARGB32_Premultiplied - should convert to ARGB32
TEST_F(StampAnnotationConvertTest_1405, ConvertARGB32PremultipliedImage_1405) {
    auto* priv = createStampPrivate();
    QImage img(10, 10, QImage::Format_ARGB32_Premultiplied);
    img.fill(QColor(255, 128, 0, 200));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 10);
    EXPECT_EQ(result->getHeight(), 10);
    
    delete priv;
}

// Test with MonoLSB format (grayscale) - should convert to Mono
TEST_F(StampAnnotationConvertTest_1405, ConvertMonoLSBGrayImage_1405) {
    auto* priv = createStampPrivate();
    QImage img(16, 16, QImage::Format_MonoLSB);
    img.fill(0);
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 16);
    EXPECT_EQ(result->getHeight(), 16);
    
    delete priv;
}

// Test with large image
TEST_F(StampAnnotationConvertTest_1405, ConvertLargeImage_1405) {
    auto* priv = createStampPrivate();
    QImage img(100, 100, QImage::Format_RGB888);
    img.fill(QColor(64, 128, 192));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 100);
    EXPECT_EQ(result->getHeight(), 100);
    
    delete priv;
}

// Test with Alpha8 format - should convert to ARGB32
TEST_F(StampAnnotationConvertTest_1405, ConvertAlpha8Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(8, 8, QImage::Format_Alpha8);
    img.fill(128);
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 8);
    EXPECT_EQ(result->getHeight(), 8);
    
    delete priv;
}

// Test with RGB16 format - should convert to RGB888
TEST_F(StampAnnotationConvertTest_1405, ConvertRGB16Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(10, 5, QImage::Format_RGB16);
    img.fill(QColor(200, 100, 50));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 10);
    EXPECT_EQ(result->getHeight(), 5);
    
    delete priv;
}

// Test non-square image dimensions are preserved
TEST_F(StampAnnotationConvertTest_1405, ConvertNonSquareImage_1405) {
    auto* priv = createStampPrivate();
    QImage img(20, 5, QImage::Format_RGB888);
    img.fill(QColor(0, 0, 255));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 20);
    EXPECT_EQ(result->getHeight(), 5);
    
    delete priv;
}

// Test with RGBX8888 format
TEST_F(StampAnnotationConvertTest_1405, ConvertRGBX8888Image_1405) {
    auto* priv = createStampPrivate();
    QImage img(3, 3, QImage::Format_RGBX8888);
    img.fill(QColor(10, 20, 30));
    
    auto result = priv->convertQImageToAnnotStampImageHelper(img);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getWidth(), 3);
    EXPECT_EQ(result->getHeight(), 3);
    
    delete priv;
}

} // namespace
