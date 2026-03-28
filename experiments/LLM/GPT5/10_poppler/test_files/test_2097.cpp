#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"  // Adjust with the actual include for PopplerAnnotFreeText

// Mocking the dependencies (if required)
class MockAnnotFreeText : public AnnotFreeText {
public:
    MOCK_METHOD(AnnotCalloutLine*, getCalloutLine, (), (const, override));
};

class PopplerAnnotFreeTextTest_2097 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialization for each test case
        poppler_annot = nullptr;
        annot = nullptr;
    }

    PopplerAnnotFreeText* poppler_annot;
    MockAnnotFreeText* annot;  // Mocked AnnotFreeText object

    // Helper function to set up the PopplerAnnotFreeText instance
    void SetPopplerAnnotFreeText(MockAnnotFreeText* mockAnnot) {
        poppler_annot = new PopplerAnnotFreeText();
        poppler_annot->font_desc = nullptr;
        poppler_annot->font_color = PopplerColor();
        annot = mockAnnot;
    }

    void TearDown() override {
        // Clean up after each test case
        delete poppler_annot;
    }
};

// Normal operation test case: When a callout line exists
TEST_F(PopplerAnnotFreeTextTest_2097, GetCalloutLine_ReturnsValidLine_2097) {
    // Setting up a mock return value for getCalloutLine()
    AnnotCalloutLine* mockLine = new AnnotCalloutLine(10, 20, 30, 40);
    EXPECT_CALL(*annot, getCalloutLine())
        .WillOnce(testing::Return(mockLine));

    PopplerAnnotCalloutLine* result = poppler_annot_free_text_get_callout_line(poppler_annot);

    ASSERT_NE(result, nullptr);  // Verify that the result is not null
    EXPECT_EQ(result->x1, 10);
    EXPECT_EQ(result->y1, 20);
    EXPECT_EQ(result->x2, 30);
    EXPECT_EQ(result->y2, 40);
    delete result;
}

// Boundary condition test: When no callout line exists
TEST_F(PopplerAnnotFreeTextTest_2097, GetCalloutLine_ReturnsNullWhenNoLine_2097) {
    // No line is set, so it should return nullptr
    EXPECT_CALL(*annot, getCalloutLine())
        .WillOnce(testing::Return(nullptr));

    PopplerAnnotCalloutLine* result = poppler_annot_free_text_get_callout_line(poppler_annot);

    EXPECT_EQ(result, nullptr);  // Verify that the result is null
}

// Boundary condition test: When callout line is of type AnnotCalloutMultiLine
TEST_F(PopplerAnnotFreeTextTest_2097, GetCalloutLine_ReturnsMultiLine_2097) {
    // Create a mock multi-line callout line
    AnnotCalloutMultiLine* multiLine = new AnnotCalloutMultiLine(10, 20, 30, 40, 50, 60);
    EXPECT_CALL(*annot, getCalloutLine())
        .WillOnce(testing::Return(multiLine));

    PopplerAnnotCalloutLine* result = poppler_annot_free_text_get_callout_line(poppler_annot);

    ASSERT_NE(result, nullptr);  // Verify that the result is not null
    EXPECT_TRUE(result->multiline);  // Verify that it's recognized as a multi-line
    EXPECT_EQ(result->x1, 10);
    EXPECT_EQ(result->y1, 20);
    EXPECT_EQ(result->x2, 30);
    EXPECT_EQ(result->y2, 40);
    EXPECT_EQ(result->x3, 50);
    EXPECT_EQ(result->y3, 60);

    delete result;
}

// Exceptional test case: When the input is invalid (not a valid PopplerAnnotFreeText)
TEST_F(PopplerAnnotFreeTextTest_2097, GetCalloutLine_InvalidInput_2097) {
    // Test case when poppler_annot is null
    EXPECT_EQ(poppler_annot_free_text_get_callout_line(nullptr), nullptr);

    // Test case when the poppler_annot is not a valid AnnotFreeText instance
    MockAnnotFreeText invalidAnnot;
    poppler_annot = reinterpret_cast<PopplerAnnotFreeText*>(&invalidAnnot);
    EXPECT_EQ(poppler_annot_free_text_get_callout_line(poppler_annot), nullptr);
}