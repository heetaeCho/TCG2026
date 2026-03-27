#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Annot.h"

class AnnotAppearanceCharacsTest : public ::testing::Test {
protected:
    AnnotAppearanceCharacsTest() : annotAppearanceCharacs(nullptr) {}

    void SetUp() override {
        // Set up any necessary dependencies or mocks here.
        annotAppearanceCharacs = std::make_unique<AnnotAppearanceCharacs>(nullptr);
    }

    std::unique_ptr<AnnotAppearanceCharacs> annotAppearanceCharacs;
};

TEST_F(AnnotAppearanceCharacsTest, GetRolloverCaption_ValidCase_770) {
    // Arrange
    const GooString expectedRolloverCaption("Test Rollover Caption");
    annotAppearanceCharacs->rolloverCaption = std::make_unique<GooString>(expectedRolloverCaption);

    // Act
    const GooString* actualRolloverCaption = annotAppearanceCharacs->getRolloverCaption();

    // Assert
    ASSERT_EQ(*actualRolloverCaption, expectedRolloverCaption);
}

TEST_F(AnnotAppearanceCharacsTest, GetRolloverCaption_NullCase_771) {
    // Arrange
    annotAppearanceCharacs->rolloverCaption.reset();

    // Act
    const GooString* actualRolloverCaption = annotAppearanceCharacs->getRolloverCaption();

    // Assert
    ASSERT_EQ(actualRolloverCaption, nullptr);
}

TEST_F(AnnotAppearanceCharacsTest, SetBorderColor_ValidCase_772) {
    // Arrange
    std::unique_ptr<AnnotColor> newColor = std::make_unique<AnnotColor>(255, 0, 0);  // Red color
    annotAppearanceCharacs->setBorderColor(std::move(newColor));

    // Act
    const AnnotColor* borderColor = annotAppearanceCharacs->getBorderColor();

    // Assert
    ASSERT_EQ(borderColor->getRed(), 255);
    ASSERT_EQ(borderColor->getGreen(), 0);
    ASSERT_EQ(borderColor->getBlue(), 0);
}

TEST_F(AnnotAppearanceCharacsTest, SetBackColor_ValidCase_773) {
    // Arrange
    std::unique_ptr<AnnotColor> newBackColor = std::make_unique<AnnotColor>(0, 255, 0);  // Green color
    annotAppearanceCharacs->setBackColor(std::move(newBackColor));

    // Act
    const AnnotColor* backColor = annotAppearanceCharacs->getBackColor();

    // Assert
    ASSERT_EQ(backColor->getRed(), 0);
    ASSERT_EQ(backColor->getGreen(), 255);
    ASSERT_EQ(backColor->getBlue(), 0);
}

TEST_F(AnnotAppearanceCharacsTest, GetNormalCaption_ValidCase_774) {
    // Arrange
    const GooString expectedNormalCaption("Test Normal Caption");
    annotAppearanceCharacs->normalCaption = std::make_unique<GooString>(expectedNormalCaption);

    // Act
    const GooString* actualNormalCaption = annotAppearanceCharacs->getNormalCaption();

    // Assert
    ASSERT_EQ(*actualNormalCaption, expectedNormalCaption);
}

TEST_F(AnnotAppearanceCharacsTest, GetAlternateCaption_ValidCase_775) {
    // Arrange
    const GooString expectedAlternateCaption("Test Alternate Caption");
    annotAppearanceCharacs->alternateCaption = std::make_unique<GooString>(expectedAlternateCaption);

    // Act
    const GooString* actualAlternateCaption = annotAppearanceCharacs->getAlternateCaption();

    // Assert
    ASSERT_EQ(*actualAlternateCaption, expectedAlternateCaption);
}

TEST_F(AnnotAppearanceCharacsTest, GetPosition_ValidCase_776) {
    // Arrange
    AnnotAppearanceCharacsTextPos expectedPosition = AnnotAppearanceCharacsTextPos::TopLeft;
    annotAppearanceCharacs->position = expectedPosition;

    // Act
    AnnotAppearanceCharacsTextPos actualPosition = annotAppearanceCharacs->getPosition();

    // Assert
    ASSERT_EQ(actualPosition, expectedPosition);
}

TEST_F(AnnotAppearanceCharacsTest, GetRotation_ValidCase_777) {
    // Arrange
    int expectedRotation = 90;
    annotAppearanceCharacs->rotation = expectedRotation;

    // Act
    int actualRotation = annotAppearanceCharacs->getRotation();

    // Assert
    ASSERT_EQ(actualRotation, expectedRotation);
}

TEST_F(AnnotAppearanceCharacsTest, Copy_ValidCase_778) {
    // Arrange
    annotAppearanceCharacs->rolloverCaption = std::make_unique<GooString>("Test Caption");

    // Act
    auto copiedAnnotAppearanceCharacs = annotAppearanceCharacs->copy();

    // Assert
    ASSERT_NE(copiedAnnotAppearanceCharacs, nullptr);
    ASSERT_EQ(*copiedAnnotAppearanceCharacs->getRolloverCaption(), *annotAppearanceCharacs->getRolloverCaption());
}

TEST_F(AnnotAppearanceCharacsTest, SetBackColor_EmptyColor_779) {
    // Arrange
    std::unique_ptr<AnnotColor> emptyColor = std::make_unique<AnnotColor>(0, 0, 0);  // Black color
    annotAppearanceCharacs->setBackColor(std::move(emptyColor));

    // Act
    const AnnotColor* backColor = annotAppearanceCharacs->getBackColor();

    // Assert
    ASSERT_EQ(backColor->getRed(), 0);
    ASSERT_EQ(backColor->getGreen(), 0);
    ASSERT_EQ(backColor->getBlue(), 0);
}