#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Annot.h"

// Mock classes for dependencies
class MockPDFDoc : public PDFDoc {};
class MockGfx : public Gfx {};
class MockPDFRectangle : public PDFRectangle {};
class MockAnnotColor : public AnnotColor {};
class MockAnnotBorderEffect : public AnnotBorderEffect {};

class AnnotGeometryTest_843 : public ::testing::Test {
protected:
    std::unique_ptr<MockPDFDoc> mockDoc;
    std::unique_ptr<MockPDFRectangle> mockRect;
    std::unique_ptr<AnnotGeometry> annotGeometry;

    void SetUp() override {
        mockDoc = std::make_unique<MockPDFDoc>();
        mockRect = std::make_unique<MockPDFRectangle>();
        annotGeometry = std::make_unique<AnnotGeometry>(mockDoc.get(), mockRect.get(), AnnotSubtype::kText);
    }
};

// Test for getBorderEffect
TEST_F(AnnotGeometryTest_843, GetBorderEffect_ValidEffect_843) {
    // Setting up the expected behavior of getBorderEffect
    MockAnnotBorderEffect mockEffect;
    EXPECT_CALL(*mockRect, getBorderEffect()).WillOnce(testing::Return(&mockEffect));

    // Verifying that getBorderEffect returns the correct effect
    EXPECT_EQ(annotGeometry->getBorderEffect(), &mockEffect);
}

// Test for getInteriorColor
TEST_F(AnnotGeometryTest_843, GetInteriorColor_ValidColor_843) {
    // Creating a mock color object
    MockAnnotColor mockColor;
    EXPECT_CALL(*mockRect, getInteriorColor()).WillOnce(testing::Return(&mockColor));

    // Verifying that getInteriorColor returns the correct color
    EXPECT_EQ(annotGeometry->getInteriorColor(), &mockColor);
}

// Test for getGeometryRect
TEST_F(AnnotGeometryTest_843, GetGeometryRect_ValidRect_843) {
    // Setting up the expected behavior of getGeometryRect
    EXPECT_CALL(*mockRect, getGeometryRect()).WillOnce(testing::Return(mockRect.get()));

    // Verifying that getGeometryRect returns the correct rectangle
    EXPECT_EQ(annotGeometry->getGeometryRect(), mockRect.get());
}

// Test for setInteriorColor with valid color
TEST_F(AnnotGeometryTest_843, SetInteriorColor_ValidColor_843) {
    MockAnnotColor mockColor;
    EXPECT_CALL(*mockRect, setInteriorColor(testing::_)).Times(1);

    annotGeometry->setInteriorColor(std::make_unique<MockAnnotColor>());
}

// Test for setType with valid type
TEST_F(AnnotGeometryTest_843, SetType_ValidType_843) {
    AnnotSubtype newType = AnnotSubtype::kText;
    EXPECT_CALL(*mockRect, setType(newType)).Times(1);

    annotGeometry->setType(newType);
}

// Test for draw function during printing
TEST_F(AnnotGeometryTest_843, Draw_Printing_843) {
    MockGfx mockGfx;
    EXPECT_CALL(mockGfx, draw(testing::_)).Times(1);

    annotGeometry->draw(&mockGfx, true);
}

// Test for draw function without printing
TEST_F(AnnotGeometryTest_843, Draw_NotPrinting_843) {
    MockGfx mockGfx;
    EXPECT_CALL(mockGfx, draw(testing::_)).Times(1);

    annotGeometry->draw(&mockGfx, false);
}

// Boundary test for invalid color
TEST_F(AnnotGeometryTest_843, SetInteriorColor_InvalidColor_843) {
    // Invalid color input as an integer (out of range or invalid value)
    int invalidColor = -1;
    EXPECT_THROW(annotGeometry->setInteriorColor(invalidColor), std::invalid_argument);
}

// Exceptional case for uninitialized geometry rectangle
TEST_F(AnnotGeometryTest_843, GetGeometryRect_Uninitialized_843) {
    // Setting the mock rectangle to nullptr and verifying the behavior
    annotGeometry = std::make_unique<AnnotGeometry>(mockDoc.get(), nullptr, AnnotSubtype::kText);
    EXPECT_THROW(annotGeometry->getGeometryRect(), std::runtime_error);
}