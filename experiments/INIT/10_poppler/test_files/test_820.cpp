#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"  // Assume the provided header file is included

class AnnotFreeTextTest : public ::testing::Test {
protected:
    // Helper method to create an instance of AnnotFreeText
    AnnotFreeText* createAnnotFreeTextInstance(PDFDoc* doc, PDFRectangle* rect) {
        return new AnnotFreeText(doc, rect);
    }

    // Mock objects for external dependencies (if any)
    // Mock PDFDoc* doc
    class MockPDFDoc : public PDFDoc {};
    MockPDFDoc* mockDoc = nullptr;

    // Mock PDFRectangle* rect
    class MockPDFRectangle : public PDFRectangle {};
    MockPDFRectangle* mockRectangle = nullptr;
};

TEST_F(AnnotFreeTextTest, ConstructorCreatesAnnotFreeText) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();

    // Act
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);

    // Assert
    ASSERT_NE(annot, nullptr);  // The object should be created successfully
}

TEST_F(AnnotFreeTextTest, SetAndGetQuadding) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);
    
    VariableTextQuadding quadding = VariableTextQuadding::eLeft;

    // Act
    annot->setQuadding(quadding);
    
    // Assert
    EXPECT_EQ(annot->getQuadding(), quadding);  // Assert the quadding was set correctly
}

TEST_F(AnnotFreeTextTest, SetAndGetStyleString) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);
    
    GooString* styleString = new GooString("bold");

    // Act
    annot->setStyleString(styleString);

    // Assert
    EXPECT_EQ(annot->getStyleString()->getCString(), styleString->getCString());  // Assert the style string was set correctly
}

TEST_F(AnnotFreeTextTest, SetAndGetIntent) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);
    
    AnnotFreeTextIntent intent = AnnotFreeTextIntent::eNormal;

    // Act
    annot->setIntent(intent);

    // Assert
    EXPECT_EQ(annot->getIntent(), intent);  // Assert the intent was set correctly
}

TEST_F(AnnotFreeTextTest, SetAndGetCalloutLine) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);
    
    AnnotCalloutLine* calloutLine = new AnnotCalloutLine();

    // Act
    annot->setCalloutLine(std::unique_ptr<AnnotCalloutLine>(calloutLine));

    // Assert
    EXPECT_EQ(annot->getCalloutLine(), calloutLine);  // Assert the callout line was set correctly
}

TEST_F(AnnotFreeTextTest, SetAndGetBorderEffect) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);
    
    AnnotBorderEffect* borderEffect = new AnnotBorderEffect();

    // Act
    annot->setBorderEffect(std::unique_ptr<AnnotBorderEffect>(borderEffect));

    // Assert
    EXPECT_EQ(annot->getBorderEffect(), borderEffect);  // Assert the border effect was set correctly
}

TEST_F(AnnotFreeTextTest, GetRectangleReturnsCorrectPointer) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);

    // Act & Assert
    EXPECT_EQ(annot->getRectangle(), mockRectangle);  // Assert that the rectangle pointer matches
}

TEST_F(AnnotFreeTextTest, DefaultAppearanceNotNull) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);

    // Act
    const std::unique_ptr<DefaultAppearance>& da = annot->getDefaultAppearance();

    // Assert
    ASSERT_NE(da, nullptr);  // Default appearance should not be null
}

TEST_F(AnnotFreeTextTest, ExceptionWhenInvalidIntentSet) {
    // Arrange
    mockDoc = new MockPDFDoc();
    mockRectangle = new MockPDFRectangle();
    AnnotFreeText* annot = createAnnotFreeTextInstance(mockDoc, mockRectangle);
    
    // Act & Assert
    EXPECT_THROW(annot->setIntent(static_cast<AnnotFreeTextIntent>(999)), std::invalid_argument);
    // Assume the method throws an invalid_argument exception for an invalid intent
}