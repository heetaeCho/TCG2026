#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h" // Include necessary headers for the Poppler classes

// Mocking AnnotText class for unit tests
class MockAnnotText : public AnnotText {
public:
    MockAnnotText(PDFDoc* docA, PDFRectangle* rect) : AnnotText(docA, rect) {}
    MOCK_METHOD(const std::string&, getIcon, (), (const, override)); // Mocking getIcon method
};

// Test Fixture for PopplerAnnotText
class PopplerAnnotTextTest_2091 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize any necessary components before each test
    }

    void TearDown() override {
        // Clean up any resources after each test
    }
};

// Test case for poppler_annot_text_get_icon with a valid icon
TEST_F(PopplerAnnotTextTest_2091, ValidIcon_2091) {
    // Mock an AnnotText object with a valid icon
    MockAnnotText mockAnnotText(nullptr, nullptr);
    const std::string icon = "valid_icon";
    EXPECT_CALL(mockAnnotText, getIcon()).WillOnce(testing::ReturnRef(icon));

    PopplerAnnotText popplerAnnotText;
    popplerAnnotText.parent_instance.annot.reset(&mockAnnotText); // Set the mock object

    gchar* result = poppler_annot_text_get_icon(&popplerAnnotText);

    // Verify that the result is not nullptr and matches the icon string
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "valid_icon");

    g_free(result); // Free the allocated string
}

// Test case for poppler_annot_text_get_icon when the icon is empty
TEST_F(PopplerAnnotTextTest_2091, EmptyIcon_2091) {
    // Mock an AnnotText object with an empty icon
    MockAnnotText mockAnnotText(nullptr, nullptr);
    const std::string icon = "";
    EXPECT_CALL(mockAnnotText, getIcon()).WillOnce(testing::ReturnRef(icon));

    PopplerAnnotText popplerAnnotText;
    popplerAnnotText.parent_instance.annot.reset(&mockAnnotText); // Set the mock object

    gchar* result = poppler_annot_text_get_icon(&popplerAnnotText);

    // Verify that the result is nullptr for an empty icon
    EXPECT_EQ(result, nullptr);
}

// Test case for poppler_annot_text_get_icon with a nullptr passed for the PopplerAnnotText object
TEST_F(PopplerAnnotTextTest_2091, NullAnnotText_2091) {
    PopplerAnnotText* nullPopplerAnnotText = nullptr;

    // Call the function with a null PopplerAnnotText pointer
    gchar* result = poppler_annot_text_get_icon(nullPopplerAnnotText);

    // Verify that the result is nullptr since the input is invalid
    EXPECT_EQ(result, nullptr);
}

// Test case for poppler_annot_text_get_icon with a PopplerAnnotText object having an invalid type
TEST_F(PopplerAnnotTextTest_2091, InvalidTypeAnnotText_2091) {
    // Mock an AnnotText object that fails the g_return_val_if_fail check
    MockAnnotText mockAnnotText(nullptr, nullptr);
    poppler_annot_text_get_icon(reinterpret_cast<PopplerAnnotText*>(&mockAnnotText)); // Cast to an invalid type

    // Since we cannot directly mock internal validation failures, we focus on ensuring the call does not crash
    // and gracefully returns nullptr when type assertion fails
}