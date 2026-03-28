#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include <QImage>



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class StampAnnotationPrivateTest : public testing::Test {

protected:

    std::unique_ptr<StampAnnotationPrivate> stampAnnotationPrivate;

    DocumentData *parentDoc = nullptr;  // Assuming this is properly set up in a real scenario

    ::Page *pdfPage = nullptr;          // Assuming this is properly set up in a real scenario



    void SetUp() override {

        stampAnnotationPrivate = std::make_unique<StampAnnotationPrivate>();

        stampAnnotationPrivate->parentDoc = parentDoc;

        stampAnnotationPrivate->pdfPage = pdfPage;

    }

};



TEST_F(StampAnnotationPrivateTest, ConvertQImageToAnnotStampImageHelper_MonoLSB_AllGray_1405) {

    QImage qimg(10, 10, QImage::Format_MonoLSB);

    qimg.fill(Qt::black); // All gray

    auto result = stampAnnotationPrivate->convertQImageToAnnotStampImageHelper(qimg);



    EXPECT_EQ(result->getWidth(), 10);

    EXPECT_EQ(result->getHeight(), 10);

}



TEST_F(StampAnnotationPrivateTest, ConvertQImageToAnnotStampImageHelper_MonoLSB_NotAllGray_1405) {

    QImage qimg(10, 10, QImage::Format_MonoLSB);

    qimg.setPixelColor(0, 0, Qt::red); // Not all gray

    auto result = stampAnnotationPrivate->convertQImageToAnnotStampImageHelper(qimg);



    EXPECT_EQ(result->getWidth(), 10);

    EXPECT_EQ(result->getHeight(), 10);

}



TEST_F(StampAnnotationPrivateTest, ConvertQImageToAnnotStampImageHelper_RGB32_1405) {

    QImage qimg(10, 10, QImage::Format_RGB32);

    qimg.fill(Qt::red);

    auto result = stampAnnotationPrivate->convertQImageToAnnotStampImageHelper(qimg);



    EXPECT_EQ(result->getWidth(), 10);

    EXPECT_EQ(result->getHeight(), 10);

}



TEST_F(StampAnnotationPrivateTest, ConvertQImageToAnnotStampImageHelper_Grayscale8_1405) {

    QImage qimg(10, 10, QImage::Format_Grayscale8);

    qimg.fill(qGray(Qt::red));

    auto result = stampAnnotationPrivate->convertQImageToAnnotStampImageHelper(qimg);



    EXPECT_EQ(result->getWidth(), 10);

    EXPECT_EQ(result->getHeight(), 10);

}



TEST_F(StampAnnotationPrivateTest, ConvertQImageToAnnotStampImageHelper_DefaultFormat_1405) {

    QImage qimg(10, 10, QImage::Format_ARGB32_Premultiplied); // Default case

    qimg.fill(Qt::red);

    auto result = stampAnnotationPrivate->convertQImageToAnnotStampImageHelper(qimg);



    EXPECT_EQ(result->getWidth(), 10);

    EXPECT_EQ(result->getHeight(), 10);

}



TEST_F(StampAnnotationPrivateTest, ConvertQImageToAnnotStampImageHelper_EmptyImage_1405) {

    QImage qimg; // Invalid/empty image

    auto result = stampAnnotationPrivate->convertQImageToAnnotStampImageHelper(qimg);



    EXPECT_EQ(result->getWidth(), 0);

    EXPECT_EQ(result->getHeight(), 0);

}
