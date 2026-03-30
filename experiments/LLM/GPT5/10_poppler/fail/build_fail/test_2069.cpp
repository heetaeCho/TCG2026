#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-private.h"

// Mock for testing external dependencies
class MockAnnot {
public:
    MOCK_METHOD(PopplerColor*, getColor, (), (const));
};

// Test Fixture for PopplerAnnot
class PopplerAnnotTest_2069 : public ::testing::Test {
protected:
    // Create a mock PopplerAnnot object
    std::shared_ptr<PopplerAnnot> popplerAnnot;

    void SetUp() override {
        popplerAnnot = std::make_shared<PopplerAnnot>();
    }

    void TearDown() override {
        popplerAnnot.reset();
    }
};

// Normal operation test
TEST_F(PopplerAnnotTest_2069, GetColor_ReturnsColor) {
    // Arrange
    MockAnnot mockAnnot;
    EXPECT_CALL(mockAnnot, getColor())
        .WillOnce(testing::Return(new PopplerColor()));

    // Act
    PopplerColor *result = poppler_annot_get_color(popplerAnnot.get());

    // Assert
    EXPECT_NE(result, nullptr);
}

// Boundary condition test: Null PopplerAnnot
TEST_F(PopplerAnnotTest_2069, GetColor_NullAnnot_ReturnsNull) {
    // Act
    PopplerColor *result = poppler_annot_get_color(nullptr);

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Boundary condition test: Invalid PopplerAnnot
TEST_F(PopplerAnnotTest_2069, GetColor_InvalidAnnot_ReturnsNull) {
    // Arrange
    // Make PopplerAnnot invalid
    popplerAnnot->annot = nullptr;

    // Act
    PopplerColor *result = poppler_annot_get_color(popplerAnnot.get());

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Exceptional case: When annot color conversion fails
TEST_F(PopplerAnnotTest_2069, GetColor_ConversionFails_ReturnsNull) {
    // Arrange
    MockAnnot mockAnnot;
    EXPECT_CALL(mockAnnot, getColor())
        .WillOnce(testing::Return(nullptr));

    // Act
    PopplerColor *result = poppler_annot_get_color(popplerAnnot.get());

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Verify external interaction: Check if the mock `getColor` was called
TEST_F(PopplerAnnotTest_2069, GetColor_VerifyMockInteraction) {
    // Arrange
    MockAnnot mockAnnot;
    EXPECT_CALL(mockAnnot, getColor())
        .Times(1)
        .WillOnce(testing::Return(new PopplerColor()));

    // Act
    PopplerColor *result = poppler_annot_get_color(popplerAnnot.get());

    // Assert
    EXPECT_EQ(result, nullptr);
}