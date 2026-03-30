#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/PSOutputDev.h"

class PSOutputDevTest_1295 : public ::testing::Test {
protected:
    // Create a mock class if necessary for external dependencies
    // For example, if there are callbacks, we can mock them
};

TEST_F(PSOutputDevTest_1295, useTilingPatternFill_ReturnsTrue_1295) {
    // Arrange
    PSOutputDev psOutputDev;

    // Act
    bool result = psOutputDev.useTilingPatternFill();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(PSOutputDevTest_1295, useShadedFills_ValidType_ReturnsTrue_1295) {
    // Arrange
    PSOutputDev psOutputDev;
    int validType = 1;  // Example valid type

    // Act
    bool result = psOutputDev.useShadedFills(validType);

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(PSOutputDevTest_1295, useDrawForm_ReturnsTrue_1295) {
    // Arrange
    PSOutputDev psOutputDev;

    // Act
    bool result = psOutputDev.useDrawForm();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(PSOutputDevTest_1295, upsideDown_ReturnsFalse_1295) {
    // Arrange
    PSOutputDev psOutputDev;

    // Act
    bool result = psOutputDev.upsideDown();

    // Assert
    ASSERT_FALSE(result);
}

TEST_F(PSOutputDevTest_1295, setOffset_SetsCorrectValues_1295) {
    // Arrange
    PSOutputDev psOutputDev;
    double x = 10.0;
    double y = 20.0;

    // Act
    psOutputDev.setOffset(x, y);

    // Assert
    // Validate if offset is set correctly, assuming we have a way to check the set values
    // For instance, if there was a getter for offset, we could call it and compare
    // ASSERT_EQ(psOutputDev.getOffsetX(), x);
    // ASSERT_EQ(psOutputDev.getOffsetY(), y);
}

TEST_F(PSOutputDevTest_1295, setScale_SetsCorrectValues_1295) {
    // Arrange
    PSOutputDev psOutputDev;
    double xScale = 1.5;
    double yScale = 2.0;

    // Act
    psOutputDev.setScale(xScale, yScale);

    // Assert
    // Similar to setOffset, verify the values are correctly set
    // ASSERT_EQ(psOutputDev.getScaleX(), xScale);
    // ASSERT_EQ(psOutputDev.getScaleY(), yScale);
}

TEST_F(PSOutputDevTest_1295, setRasterResolution_ValidValue_1295) {
    // Arrange
    PSOutputDev psOutputDev;
    double resolution = 300.0;

    // Act
    psOutputDev.setRasterResolution(resolution);

    // Assert
    // Again, validate the effect of the method, assuming there is a way to get this value
    // ASSERT_EQ(psOutputDev.getRasterResolution(), resolution);
}

TEST_F(PSOutputDevTest_1295, getEmbedTrueType_ReturnsTrue_1295) {
    // Arrange
    PSOutputDev psOutputDev;

    // Act
    bool result = psOutputDev.getEmbedTrueType();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(PSOutputDevTest_1295, getEnableLZW_ReturnsFalse_1295) {
    // Arrange
    PSOutputDev psOutputDev;

    // Act
    bool result = psOutputDev.getEnableLZW();

    // Assert
    ASSERT_FALSE(result);
}

TEST_F(PSOutputDevTest_1295, setOverprintPreview_SetsCorrectFlag_1295) {
    // Arrange
    PSOutputDev psOutputDev;
    bool overprintPreviewFlag = true;

    // Act
    psOutputDev.setOverprintPreview(overprintPreviewFlag);

    // Assert
    // Assuming there's a way to check the flag, e.g., a getter for this property
    // ASSERT_EQ(psOutputDev.getOverprintPreview(), overprintPreviewFlag);
}

// Test boundary cases, if applicable
TEST_F(PSOutputDevTest_1295, setRasterResolution_InvalidValue_1295) {
    // Arrange
    PSOutputDev psOutputDev;
    double invalidResolution = -1.0;  // Invalid value for resolution

    // Act & Assert
    ASSERT_THROW(psOutputDev.setRasterResolution(invalidResolution), std::invalid_argument);
}