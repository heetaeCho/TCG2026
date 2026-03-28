#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"

// Mock for PopplerAnnot class, used for verifying external interactions.
class MockPopplerAnnot : public PopplerAnnot {
public:
    MOCK_METHOD(const GooString*, getModified, (), (const, override));
};

// Test fixture for testing poppler_annot_get_modified function
class PopplerAnnotTest_2066 : public ::testing::Test {
protected:
    // You can add setup/teardown functions if needed.
};

// Test normal operation where the annotation is modified.
TEST_F(PopplerAnnotTest_2066, GetModified_ReturnsValidString_2066) {
    // Arrange
    MockPopplerAnnot mockAnnot;
    const char* expectedText = "Test Annotation";
    GooString gooString(expectedText);

    // Mock the behavior of getModified to return the expected GooString.
    EXPECT_CALL(mockAnnot, getModified())
        .WillOnce(testing::Return(&gooString));

    // Act
    gchar* result = poppler_annot_get_modified(&mockAnnot);

    // Assert
    ASSERT_NE(result, nullptr);  // Ensure the result is not null.
    ASSERT_STREQ(result, expectedText);  // Ensure the returned string is as expected.
}

// Test the case where the annotation has no modification.
TEST_F(PopplerAnnotTest_2066, GetModified_ReturnsNullWhenNoModification_2066) {
    // Arrange
    MockPopplerAnnot mockAnnot;

    // Mock the behavior of getModified to return nullptr.
    EXPECT_CALL(mockAnnot, getModified())
        .WillOnce(testing::Return(nullptr));

    // Act
    gchar* result = poppler_annot_get_modified(&mockAnnot);

    // Assert
    ASSERT_EQ(result, nullptr);  // Ensure the result is null.
}

// Test the case where poppler_annot_get_modified is called on a non-annotated object.
TEST_F(PopplerAnnotTest_2066, GetModified_ThrowsNullPointerWhenInvalidAnnot_2066) {
    // Arrange
    PopplerAnnot* invalidAnnot = nullptr;  // Simulate an invalid annotation object.

    // Act and Assert
    ASSERT_EQ(poppler_annot_get_modified(invalidAnnot), nullptr);  // It should return nullptr as the object is invalid.
}