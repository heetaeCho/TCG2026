#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"  // Include relevant header files

// Mock dependencies for testing purposes
class MockAnnotTextMarkup : public AnnotTextMarkup {
public:
    MOCK_METHOD(AnnotQuadrilaterals*, getQuadrilaterals, (), (const, override));
    MOCK_METHOD(void, setQuadrilaterals, (const AnnotQuadrilaterals&), (override));
};

// Mock the GArray and other required structs or functions if necessary
extern "C" {
    GArray* create_poppler_quads_from_annot_quads(AnnotQuadrilaterals *quads, const PDFRectangle *crop_box) {
        // Mock implementation if needed or rely on actual function
        return nullptr;
    }
}

// Test fixture for PopplerAnnotTextMarkup testing
class PopplerAnnotTest_2095 : public ::testing::Test {
protected:
    PopplerAnnotTextMarkup *poppler_annot;
    MockAnnotTextMarkup *mock_annot_markup;

    void SetUp() override {
        mock_annot_markup = new MockAnnotTextMarkup();
        poppler_annot = reinterpret_cast<PopplerAnnotTextMarkup*>(mock_annot_markup);  // Assuming correct casting
    }

    void TearDown() override {
        delete mock_annot_markup;
    }
};

// Test case for normal operation of poppler_annot_text_markup_get_quadrilaterals function
TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_ValidCase_2095) {
    // Arrange
    AnnotQuadrilaterals mock_quadrilaterals;
    PDFRectangle crop_box;

    // Mock the behavior of getQuadrilaterals
    EXPECT_CALL(*mock_annot_markup, getQuadrilaterals())
        .WillOnce(testing::Return(&mock_quadrilaterals));

    // Act
    GArray* result = poppler_annot_text_markup_get_quadrilaterals(poppler_annot);

    // Assert
    ASSERT_NE(result, nullptr);  // Check if the result is non-null (indicating success)
}

// Test case for handling invalid PopplerAnnotTextMarkup pointer (null input)
TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_InvalidPopplerAnnot_2095) {
    // Arrange
    PopplerAnnotTextMarkup *invalid_poppler_annot = nullptr;

    // Act
    GArray* result = poppler_annot_text_markup_get_quadrilaterals(invalid_poppler_annot);

    // Assert
    ASSERT_EQ(result, nullptr);  // Should return null on invalid input
}

// Test case for handling PopplerAnnotTextMarkup with no quadrilaterals
TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_NoQuadrilaterals_2095) {
    // Arrange
    AnnotQuadrilaterals empty_quadrilaterals;
    EXPECT_CALL(*mock_annot_markup, getQuadrilaterals())
        .WillOnce(testing::Return(&empty_quadrilaterals));

    // Act
    GArray* result = poppler_annot_text_markup_get_quadrilaterals(poppler_annot);

    // Assert
    ASSERT_NE(result, nullptr);  // Check if the result is non-null (it should return an empty array or valid structure)
}

// Test case for boundary condition: PopplerAnnotTextMarkup with large quadrilaterals
TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_LargeQuadrilaterals_2095) {
    // Arrange
    AnnotQuadrilaterals large_quadrilaterals;
    // Mock large quadrilateral data here if needed

    EXPECT_CALL(*mock_annot_markup, getQuadrilaterals())
        .WillOnce(testing::Return(&large_quadrilaterals));

    // Act
    GArray* result = poppler_annot_text_markup_get_quadrilaterals(poppler_annot);

    // Assert
    ASSERT_NE(result, nullptr);  // The result should still be non-null even for large quadrilaterals
}

// Test case for boundary condition: PopplerAnnotTextMarkup with no crop box
TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_NoCropBox_2095) {
    // Arrange
    AnnotQuadrilaterals mock_quadrilaterals;
    PDFRectangle *crop_box = nullptr;  // No crop box

    EXPECT_CALL(*mock_annot_markup, getQuadrilaterals())
        .WillOnce(testing::Return(&mock_quadrilaterals));

    // Act
    GArray* result = poppler_annot_text_markup_get_quadrilaterals(poppler_annot);

    // Assert
    ASSERT_NE(result, nullptr);  // It should still return a result, even without a crop box
}

// Test case for exceptional case: handling of null quadrilaterals pointer
TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_NullQuadrilaterals_2095) {
    // Arrange
    AnnotQuadrilaterals* null_quadrilaterals = nullptr;
    EXPECT_CALL(*mock_annot_markup, getQuadrilaterals())
        .WillOnce(testing::Return(null_quadrilaterals));

    // Act
    GArray* result = poppler_annot_text_markup_get_quadrilaterals(poppler_annot);

    // Assert
    ASSERT_EQ(result, nullptr);  // It should return null since quadrilaterals are null
}