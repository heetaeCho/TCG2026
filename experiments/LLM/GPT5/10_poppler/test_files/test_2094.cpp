#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-annot-text-markup.h"
#include "Page.h"  // Required for Page
#include "PDFRectangle.h"  // Required for PDFRectangle

// Mock classes for dependencies
class MockPage : public Page {
public:
    MOCK_METHOD(bool, isValid, (), (const, override));
    MOCK_METHOD(int, getRotate, (), (const, override));
};

class MockAnnotTextMarkup : public AnnotTextMarkup {
public:
    MOCK_METHOD(void, setQuadrilaterals, (const AnnotQuadrilaterals &), (override));
};

// Helper function to create a GArray with quadrilaterals for testing
GArray* createTestQuadrilaterals() {
    GArray* quadrilaterals = g_array_new(FALSE, FALSE, sizeof(PDFRectangle));
    PDFRectangle rect(0, 0, 100, 100);
    g_array_append_val(quadrilaterals, rect);
    return quadrilaterals;
}

// Test fixture class
class PopplerAnnotTest : public ::testing::Test {
protected:
    PopplerAnnotTextMarkup *poppler_annot;
    GArray *quadrilaterals;

    void SetUp() override {
        // Initialize poppler_annot and quadrilaterals
        poppler_annot = new PopplerAnnotTextMarkup();  // Assuming a constructor
        quadrilaterals = createTestQuadrilaterals();
    }

    void TearDown() override {
        g_array_free(quadrilaterals, TRUE);
        delete poppler_annot;
    }
};

// Test for normal operation
TEST_F(PopplerAnnotTest, poppler_annot_text_markup_set_quadrilaterals_2094) {
    EXPECT_NO_THROW({
        poppler_annot_text_markup_set_quadrilaterals(poppler_annot, quadrilaterals);
    });
}

// Test for boundary conditions: Empty quadrilaterals array
TEST_F(PopplerAnnotTest, poppler_annot_text_markup_set_quadrilateralsEmpty_2094) {
    GArray* empty_quads = g_array_new(FALSE, FALSE, sizeof(PDFRectangle));
    EXPECT_THROW({
        poppler_annot_text_markup_set_quadrilaterals(poppler_annot, empty_quads);
    }, std::invalid_argument);  // Assuming the implementation throws an exception on empty quadrilaterals
    g_array_free(empty_quads, TRUE);
}

// Test for exceptional case: Null quadrilaterals
TEST_F(PopplerAnnotTest, poppler_annot_text_markup_set_quadrilateralsNull_2094) {
    EXPECT_THROW({
        poppler_annot_text_markup_set_quadrilaterals(poppler_annot, nullptr);
    }, std::invalid_argument);  // Assuming the implementation throws an exception on null input
}

// Test for verifying external interactions with mock dependencies
TEST_F(PopplerAnnotTest, poppler_annot_text_markup_set_quadrilaterals_Interaction_2094) {
    // Create a mock page and set expectations
    MockPage mockPage;
    EXPECT_CALL(mockPage, getRotate())
        .WillOnce(testing::Return(90));  // Simulating a page with rotation

    // Mock AnnotTextMarkup
    MockAnnotTextMarkup mockAnnot;
    EXPECT_CALL(mockAnnot, setQuadrilaterals(testing::_))
        .Times(1);  // Expect setQuadrilaterals to be called once

    // Simulate the actual test
    poppler_annot_text_markup_set_quadrilaterals(poppler_annot, quadrilaterals);
}