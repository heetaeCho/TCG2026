#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"  // Include header file for the relevant function

// Mocking external collaborators (if needed, e.g., if 'update_font_desc_with_word' is an external function)
class MockFontDescriptionUpdater {
public:
    MOCK_METHOD(bool, update_font_desc_with_word, (PopplerFontDescription &font_desc, const std::string &word), ());
};

// Define the tests for the function
class PopplerFontTest : public ::testing::Test {
protected:
    // You may need to initialize other objects here as needed
    MockFontDescriptionUpdater mock_updater;
};

// Normal operation test case
TEST_F(PopplerFontTest, poppler_font_name_to_description_normal_2043) {
    // Given
    std::string font_name = "Arial Bold 12pt";
    PopplerFontDescription font_desc = {};

    // Simulate the behavior of update_font_desc_with_word
    EXPECT_CALL(mock_updater, update_font_desc_with_word(testing::_, testing::_))
        .Times(3)  // assuming 3 words will be processed
        .WillRepeatedly(testing::Return(true)); // Simulating successful updates

    // When
    poppler_font_name_to_description(font_name, font_desc);

    // Then
    EXPECT_STREQ(font_desc.font_name, "Arial");
    EXPECT_EQ(font_desc.size_pt, 12.0);  // assuming size_pt is set to 12 from font name
    // You can further validate PopplerFontDescription fields if they are updated as expected
}

// Boundary test case (Empty font name)
TEST_F(PopplerFontTest, poppler_font_name_to_description_empty_2044) {
    // Given
    std::string font_name = "";
    PopplerFontDescription font_desc = {};

    // When
    poppler_font_name_to_description(font_name, font_desc);

    // Then
    EXPECT_STREQ(font_desc.font_name, "");
    // You can validate other fields as needed, assuming defaults are set
}

// Boundary test case (No style words, only font name)
TEST_F(PopplerFontTest, poppler_font_name_to_description_no_style_2045) {
    // Given
    std::string font_name = "Helvetica";
    PopplerFontDescription font_desc = {};

    // When
    poppler_font_name_to_description(font_name, font_desc);

    // Then
    EXPECT_STREQ(font_desc.font_name, "Helvetica");
    // Check for other fields if they are handled as expected
}

// Exceptional case (No space characters, no styles)
TEST_F(PopplerFontTest, poppler_font_name_to_description_no_spaces_2046) {
    // Given
    std::string font_name = "TimesNewRoman";
    PopplerFontDescription font_desc = {};

    // When
    poppler_font_name_to_description(font_name, font_desc);

    // Then
    EXPECT_STREQ(font_desc.font_name, "TimesNewRoman");
    // Check for other fields if handled appropriately
}

// Mocked interaction verification
TEST_F(PopplerFontTest, poppler_font_name_to_description_mock_interaction_2047) {
    // Given
    std::string font_name = "Verdana Regular 10pt";
    PopplerFontDescription font_desc = {};

    // Set up mock expectations
    EXPECT_CALL(mock_updater, update_font_desc_with_word(testing::_, testing::_))
        .Times(3)
        .WillRepeatedly(testing::Return(true));

    // When
    poppler_font_name_to_description(font_name, font_desc);

    // Then - Validate the mock function was called the expected number of times
    ASSERT_EQ(Mock::VerifyAndClearExpectations(&mock_updater), true);
}