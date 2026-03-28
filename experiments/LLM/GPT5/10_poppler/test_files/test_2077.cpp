#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"

// Mocking the PopplerAnnot class to mock dependencies.
class MockAnnotMarkup : public AnnotMarkup {
public:
    MOCK_METHOD(AnnotPopup*, getPopup, (), (const, override));  // Mock the getPopup method
};

// Test fixture for PopplerAnnotMarkup tests.
class PopplerAnnotMarkupTest_2077 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any required test data or mocks here.
    }

    void TearDown() override {
        // Clean up any necessary state after each test.
    }
};

// Test for normal operation of poppler_annot_markup_has_popup when the popup exists.
TEST_F(PopplerAnnotMarkupTest_2077, HasPopup_Exists_2077) {
    // Create a PopplerAnnotMarkup mock object
    MockAnnotMarkup mock_annot;
    
    // Setting up the mock to return a non-null popup
    AnnotPopup popup;
    EXPECT_CALL(mock_annot, getPopup())
        .WillOnce(testing::Return(&popup));  // Mock returns a valid popup
    
    // Create a PopplerAnnotMarkup instance to test
    PopplerAnnotMarkup poppler_annot;
    poppler_annot.annot = &mock_annot;

    // Run the function under test
    gboolean result = poppler_annot_markup_has_popup(&poppler_annot);

    // Verify the result
    EXPECT_TRUE(result);  // The result should be TRUE when popup exists
}

// Test for normal operation of poppler_annot_markup_has_popup when the popup does not exist.
TEST_F(PopplerAnnotMarkupTest_2077, HasPopup_DoesNotExist_2077) {
    // Create a PopplerAnnotMarkup mock object
    MockAnnotMarkup mock_annot;
    
    // Setting up the mock to return a null popup
    EXPECT_CALL(mock_annot, getPopup())
        .WillOnce(testing::Return(nullptr));  // Mock returns nullptr
    
    // Create a PopplerAnnotMarkup instance to test
    PopplerAnnotMarkup poppler_annot;
    poppler_annot.annot = &mock_annot;

    // Run the function under test
    gboolean result = poppler_annot_markup_has_popup(&poppler_annot);

    // Verify the result
    EXPECT_FALSE(result);  // The result should be FALSE when popup does not exist
}

// Test for boundary condition where PopplerAnnot is NULL.
TEST_F(PopplerAnnotMarkupTest_2077, AnnotIsNull_2077) {
    // Null PopplerAnnotMarkup
    PopplerAnnotMarkup *poppler_annot = nullptr;

    // Run the function under test with a nullptr
    gboolean result = poppler_annot_markup_has_popup(poppler_annot);

    // Verify the result
    EXPECT_FALSE(result);  // The result should be FALSE when poppler_annot is NULL
}

// Test for boundary condition where AnnotMarkup is invalid.
TEST_F(PopplerAnnotMarkupTest_2077, InvalidAnnotMarkup_2077) {
    // Create a PopplerAnnotMarkup with invalid type (not an AnnotMarkup)
    PopplerAnnotMarkup poppler_annot;
    poppler_annot.annot = nullptr;  // Invalid annot pointer

    // Run the function under test
    gboolean result = poppler_annot_markup_has_popup(&poppler_annot);

    // Verify the result
    EXPECT_FALSE(result);  // The result should be FALSE when annot is invalid
}