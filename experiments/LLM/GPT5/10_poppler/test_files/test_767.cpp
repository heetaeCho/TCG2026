#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"  // Assuming this header includes the AnnotAppearanceCharacs class

class AnnotAppearanceCharacsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // You can initialize any necessary dependencies here.
    }

    void TearDown() override {
        // Clean-up if necessary.
    }
};

TEST_F(AnnotAppearanceCharacsTest, GetBackColor_767) {
    // Arrange
    std::unique_ptr<AnnotColor> backColor = std::make_unique<AnnotColor>();
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setBackColor(std::move(backColor));

    // Act
    const AnnotColor* result = annotAppearanceCharacs.getBackColor();

    // Assert
    EXPECT_NE(result, nullptr);  // Ensure it is not nullptr
}

TEST_F(AnnotAppearanceCharacsTest, SetBackColor_768) {
    // Arrange
    std::unique_ptr<AnnotColor> newBackColor = std::make_unique<AnnotColor>();
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);

    // Act
    annotAppearanceCharacs.setBackColor(std::move(newBackColor));

    // Assert
    EXPECT_NE(annotAppearanceCharacs.getBackColor(), nullptr);  // Should be set to a non-null color
}

TEST_F(AnnotAppearanceCharacsTest, GetRotation_769) {
    // Arrange
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    int expectedRotation = 90;

    // Assuming there's a setter function to set rotation (since it's not specified, we'll assume it exists)
    annotAppearanceCharacs.setRotation(expectedRotation);

    // Act
    int rotation = annotAppearanceCharacs.getRotation();

    // Assert
    EXPECT_EQ(rotation, expectedRotation);  // Should return the set rotation value
}

TEST_F(AnnotAppearanceCharacsTest, GetBorderColor_770) {
    // Arrange
    std::unique_ptr<AnnotColor> borderColor = std::make_unique<AnnotColor>();
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setBorderColor(std::move(borderColor));

    // Act
    const AnnotColor* result = annotAppearanceCharacs.getBorderColor();

    // Assert
    EXPECT_NE(result, nullptr);  // Ensure it is not nullptr
}

TEST_F(AnnotAppearanceCharacsTest, SetBorderColor_771) {
    // Arrange
    std::unique_ptr<AnnotColor> newBorderColor = std::make_unique<AnnotColor>();
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);

    // Act
    annotAppearanceCharacs.setBorderColor(std::move(newBorderColor));

    // Assert
    EXPECT_NE(annotAppearanceCharacs.getBorderColor(), nullptr);  // Should be set to a non-null color
}

TEST_F(AnnotAppearanceCharacsTest, GetNormalCaption_772) {
    // Arrange
    std::unique_ptr<GooString> normalCaption = std::make_unique<GooString>("Normal Caption");
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setNormalCaption(std::move(normalCaption));

    // Act
    const GooString* result = annotAppearanceCharacs.getNormalCaption();

    // Assert
    EXPECT_NE(result, nullptr);  // Ensure it is not nullptr
    EXPECT_EQ(result->c_str(), "Normal Caption");  // Check the caption value
}

TEST_F(AnnotAppearanceCharacsTest, GetRolloverCaption_773) {
    // Arrange
    std::unique_ptr<GooString> rolloverCaption = std::make_unique<GooString>("Rollover Caption");
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setRolloverCaption(std::move(rolloverCaption));

    // Act
    const GooString* result = annotAppearanceCharacs.getRolloverCaption();

    // Assert
    EXPECT_NE(result, nullptr);  // Ensure it is not nullptr
    EXPECT_EQ(result->c_str(), "Rollover Caption");  // Check the caption value
}

TEST_F(AnnotAppearanceCharacsTest, GetAlternateCaption_774) {
    // Arrange
    std::unique_ptr<GooString> alternateCaption = std::make_unique<GooString>("Alternate Caption");
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setAlternateCaption(std::move(alternateCaption));

    // Act
    const GooString* result = annotAppearanceCharacs.getAlternateCaption();

    // Assert
    EXPECT_NE(result, nullptr);  // Ensure it is not nullptr
    EXPECT_EQ(result->c_str(), "Alternate Caption");  // Check the caption value
}

TEST_F(AnnotAppearanceCharacsTest, GetIconFit_775) {
    // Arrange
    std::unique_ptr<AnnotIconFit> iconFit = std::make_unique<AnnotIconFit>();
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setIconFit(std::move(iconFit));

    // Act
    const AnnotIconFit* result = annotAppearanceCharacs.getIconFit();

    // Assert
    EXPECT_NE(result, nullptr);  // Ensure it is not nullptr
}

TEST_F(AnnotAppearanceCharacsTest, GetPosition_776) {
    // Arrange
    AnnotAppearanceCharacsTextPos expectedPos;
    expectedPos.x = 10;
    expectedPos.y = 20;
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setPosition(expectedPos);

    // Act
    AnnotAppearanceCharacsTextPos pos = annotAppearanceCharacs.getPosition();

    // Assert
    EXPECT_EQ(pos.x, 10);
    EXPECT_EQ(pos.y, 20);
}

TEST_F(AnnotAppearanceCharacsTest, Copy_777) {
    // Arrange
    AnnotAppearanceCharacs annotAppearanceCharacs(nullptr);
    annotAppearanceCharacs.setRotation(90);

    // Act
    std::unique_ptr<AnnotAppearanceCharacs> copy = annotAppearanceCharacs.copy();

    // Assert
    EXPECT_NE(copy, nullptr);  // Ensure copy is not null
    EXPECT_EQ(copy->getRotation(), 90);  // Ensure copy has same rotation
}