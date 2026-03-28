#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/qt5/src/poppler-page.h"

#include "TestProjects/poppler/splash/SplashBitmap.h"



using namespace Poppler;

using namespace ::testing;



class Qt5SplashOutputDevTest : public Test {

protected:

    Qt5SplashOutputDev* outputDev;

    bool ignorePaperColor = false;



    void SetUp() override {

        outputDev = new Qt5SplashOutputDev(SplashModeRGB8, 0, ignorePaperColor, nullptr, true, splashThinLineDefault, false);

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_ReturnsEmptyQImageWhenBitmapConversionFails_1437) {

    // Arrange

    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(false));



    // Act

    QImage image = outputDev->getXBGRImage(false);



    // Assert

    EXPECT_TRUE(image.isNull());

}



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_ReturnsQImageWithCorrectFormatAndSizeWhenConversionSucceeds_1437) {

    // Arrange

    int width = 100;

    int height = 200;

    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(true));

    EXPECT_CALL(*outputDev->getBitmap(), getWidth()).WillRepeatedly(Return(width));

    EXPECT_CALL(*outputDev->getBitmap(), getHeight()).WillRepeatedly(Return(height));



    // Act

    QImage image = outputDev->getXBGRImage(false);



    // Assert

    EXPECT_EQ(image.width(), width);

    EXPECT_EQ(image.height(), height);

}



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_TakesImageDataWhenRequested_1437) {

    // Arrange

    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(true));

    EXPECT_CALL(*outputDev->getBitmap(), takeData()).WillOnce(Return(nullptr));



    // Act

    QImage image = outputDev->getXBGRImage(true);



    // Assert

    // If takeImageData is true, the internal data should be taken and managed by QImage.

}



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_ReturnsQImageInARGBFormatWhenIgnorePaperColorIsTrue_1437) {

    // Arrange

    ignorePaperColor = true;

    outputDev->ignorePaperColor = ignorePaperColor;



    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(true));

    EXPECT_CALL(*outputDev->getBitmap(), getWidth()).WillRepeatedly(Return(100));

    EXPECT_CALL(*outputDev->getBitmap(), getHeight()).WillRepeatedly(Return(200));



    // Act

    QImage image = outputDev->getXBGRImage(false);



    // Assert

    EXPECT_EQ(image.format(), QImage::Format_ARGB32_Premultiplied);

}



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_ReturnsQImageInRGBFormatWhenIgnorePaperColorIsFalse_1437) {

    // Arrange

    ignorePaperColor = false;

    outputDev->ignorePaperColor = ignorePaperColor;



    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(true));

    EXPECT_CALL(*outputDev->getBitmap(), getWidth()).WillRepeatedly(Return(100));

    EXPECT_CALL(*outputDev->getBitmap(), getHeight()).WillRepeatedly(Return(200));



    // Act

    QImage image = outputDev->getXBGRImage(false);



    // Assert

    EXPECT_EQ(image.format(), QImage::Format_RGB32);

}



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_ReturnsCopyOfQImageWhenTakeImageDataIsFalse_1437) {

    // Arrange

    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(true));



    // Act

    QImage image = outputDev->getXBGRImage(false);



    // Assert

    EXPECT_FALSE(image.isNull());

}



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_HandlesBigEndianCorrectly_1437) {

    // Arrange

    QSysInfo::ByteOrder originalByteOrder = QSysInfo::ByteOrder;

    QSysInfo::ByteOrder = QSysInfo::BigEndian;



    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(true));

    EXPECT_CALL(*outputDev->getBitmap(), getWidth()).WillRepeatedly(Return(100));

    EXPECT_CALL(*outputDev->getBitmap(), getHeight()).WillRepeatedly(Return(200));



    // Act

    QImage image = outputDev->getXBGRImage(false);



    // Assert

    // The internal pixel data should be swapped correctly for big-endian systems



    QSysInfo::ByteOrder = originalByteOrder;

}



TEST_F(Qt5SplashOutputDevTest_1437, GetXBGRImage_HandlesLittleEndianCorrectly_1437) {

    // Arrange

    QSysInfo::ByteOrder originalByteOrder = QSysInfo::ByteOrder;

    QSysInfo::ByteOrder = QSysInfo::LittleEndian;



    EXPECT_CALL(*outputDev->getBitmap(), convertToXBGR(_)).WillOnce(Return(true));

    EXPECT_CALL(*outputDev->getBitmap(), getWidth()).WillRepeatedly(Return(100));

    EXPECT_CALL(*outputDev->getBitmap(), getHeight()).WillRepeatedly(Return(200));



    // Act

    QImage image = outputDev->getXBGRImage(false);



    // Assert

    // The internal pixel data should remain unchanged for little-endian systems



    QSysInfo::ByteOrder = originalByteOrder;

}

```


