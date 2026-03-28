#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annotation.h"  // Assuming the boundaryToPdfRectangle function is declared here.
#include "poppler/Page.h"  // Assuming this includes the Page class and related methods.

using namespace testing;

class MockPage : public Poppler::Page {
public:
    MockPage() : Poppler::Page(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>()) {}

    MOCK_METHOD(double, getCropWidth, (), (const, override));
    MOCK_METHOD(double, getCropHeight, (), (const, override));
    MOCK_METHOD(int, getRotate, (), (const, override));
    MOCK_METHOD(void, fillNormalizationMTX, (Poppler::Page *pdfPage, double* MTX, int pageRotate), (override));
    MOCK_METHOD(void, invTransform, (double* MTX, const QPointF& point, double& x, double& y), (const, override));
};

class BoundaryToPdfRectangleTest : public ::testing::Test {
protected:
    MockPage mockPage;
};

TEST_F(BoundaryToPdfRectangleTest, NormalOperation_1387) {
    // Arrange
    QRectF rect(0, 0, 10, 20);
    int rFlags = 0;
    
    // Set expectations
    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(100.0));
    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(200.0));
    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));
    
    // Act
    Poppler::PDFRectangle result = Poppler::boundaryToPdfRectangle(&mockPage, rect, rFlags);
    
    // Assert
    EXPECT_DOUBLE_EQ(result.getLeft(), 0.0);
    EXPECT_DOUBLE_EQ(result.getBottom(), 0.0);
    EXPECT_DOUBLE_EQ(result.getRight(), 10.0);
    EXPECT_DOUBLE_EQ(result.getTop(), 20.0);
}

TEST_F(BoundaryToPdfRectangleTest, ZeroCropWidth_1387) {
    // Arrange
    QRectF rect(0, 0, 10, 20);
    int rFlags = 0;
    
    // Set expectations
    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(0.0));  // Zero width
    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(200.0));
    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));
    
    // Act
    Poppler::PDFRectangle result = Poppler::boundaryToPdfRectangle(&mockPage, rect, rFlags);
    
    // Assert
    EXPECT_EQ(result.getLeft(), 0.0);  // Expect an empty rectangle
    EXPECT_EQ(result.getBottom(), 0.0);
    EXPECT_EQ(result.getRight(), 0.0);
    EXPECT_EQ(result.getTop(), 0.0);
}

TEST_F(BoundaryToPdfRectangleTest, ZeroCropHeight_1387) {
    // Arrange
    QRectF rect(0, 0, 10, 20);
    int rFlags = 0;
    
    // Set expectations
    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(100.0));
    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(0.0));  // Zero height
    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));
    
    // Act
    Poppler::PDFRectangle result = Poppler::boundaryToPdfRectangle(&mockPage, rect, rFlags);
    
    // Assert
    EXPECT_EQ(result.getLeft(), 0.0);
    EXPECT_EQ(result.getBottom(), 0.0);
    EXPECT_EQ(result.getRight(), 0.0);
    EXPECT_EQ(result.getTop(), 0.0);
}

TEST_F(BoundaryToPdfRectangleTest, RotationFixUp_90Degrees_1387) {
    // Arrange
    QRectF rect(0, 0, 10, 20);
    int rFlags = Poppler::Annotation::FixedRotation;
    
    // Set expectations
    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(100.0));
    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(200.0));
    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(90));  // 90 degrees rotation
    
    // Act
    Poppler::PDFRectangle result = Poppler::boundaryToPdfRectangle(&mockPage, rect, rFlags);
    
    // Assert
    EXPECT_DOUBLE_EQ(result.getLeft(), 0.0);
    EXPECT_DOUBLE_EQ(result.getBottom(), -20.0);  // Height becomes bottom due to rotation
    EXPECT_DOUBLE_EQ(result.getRight(), 10.0);
    EXPECT_DOUBLE_EQ(result.getTop(), 0.0);
}

TEST_F(BoundaryToPdfRectangleTest, RotationFixUp_180Degrees_1387) {
    // Arrange
    QRectF rect(0, 0, 10, 20);
    int rFlags = Poppler::Annotation::FixedRotation;
    
    // Set expectations
    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(100.0));
    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(200.0));
    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(180));  // 180 degrees rotation
    
    // Act
    Poppler::PDFRectangle result = Poppler::boundaryToPdfRectangle(&mockPage, rect, rFlags);
    
    // Assert
    EXPECT_DOUBLE_EQ(result.getLeft(), 10.0);  // X becomes inverted
    EXPECT_DOUBLE_EQ(result.getBottom(), 0.0);
    EXPECT_DOUBLE_EQ(result.getRight(), 20.0);  // Width is swapped with height
    EXPECT_DOUBLE_EQ(result.getTop(), 20.0);
}

TEST_F(BoundaryToPdfRectangleTest, RotationFixUp_270Degrees_1387) {
    // Arrange
    QRectF rect(0, 0, 10, 20);
    int rFlags = Poppler::Annotation::FixedRotation;
    
    // Set expectations
    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(100.0));
    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(200.0));
    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(270));  // 270 degrees rotation
    
    // Act
    Poppler::PDFRectangle result = Poppler::boundaryToPdfRectangle(&mockPage, rect, rFlags);
    
    // Assert
    EXPECT_DOUBLE_EQ(result.getLeft(), 10.0);  // Inverted values for 270 degrees
    EXPECT_DOUBLE_EQ(result.getBottom(), 20.0);
    EXPECT_DOUBLE_EQ(result.getRight(), 20.0);
    EXPECT_DOUBLE_EQ(result.getTop(), 10.0);
}

TEST_F(BoundaryToPdfRectangleTest, NullPagePointer_1387) {
    // Arrange
    QRectF rect(0, 0, 10, 20);
    int rFlags = 0;
    
    // Act
    Poppler::PDFRectangle result = Poppler::boundaryToPdfRectangle(nullptr, rect, rFlags);
    
    // Assert
    EXPECT_EQ(result.getLeft(), 0.0);
    EXPECT_EQ(result.getBottom(), 0.0);
    EXPECT_EQ(result.getRight(), 0.0);
    EXPECT_EQ(result.getTop(), 0.0);
}