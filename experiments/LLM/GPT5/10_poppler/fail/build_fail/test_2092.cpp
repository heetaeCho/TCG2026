#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Mocking the AnnotText class for testing
class MockAnnotText : public AnnotText {
public:
    MOCK_METHOD(void, setIcon, (const std::string& new_icon), (override));
};

// Test fixture for testing poppler_annot_text_set_icon
class PopplerAnnotTextSetIconTest_2092 : public ::testing::Test {
protected:
    PopplerAnnotText *poppler_annot;
    MockAnnotText *mock_annot_text;

    virtual void SetUp() override {
        // Set up mock AnnotText and the associated PopplerAnnotText
        mock_annot_text = new MockAnnotText(nullptr, nullptr);  // Mock constructor
        poppler_annot = reinterpret_cast<PopplerAnnotText*>(mock_annot_text);
    }

    virtual void TearDown() override {
        delete mock_annot_text;
    }
};

// Test: Normal case with a valid icon string
TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconValidIcon_2092) {
    std::string icon = "valid_icon";
    EXPECT_CALL(*mock_annot_text, setIcon(icon)).Times(1);

    // Call the function being tested
    poppler_annot_text_set_icon(poppler_annot, icon.c_str());

    // Verify that the mock setIcon was called with the correct argument
    testing::Mock::VerifyAndClearExpectations(mock_annot_text);
}

// Test: Case where the icon is null (empty string)
TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconNull_2093) {
    EXPECT_CALL(*mock_annot_text, setIcon("")).Times(1);

    // Call the function being tested with a null (empty) icon
    poppler_annot_text_set_icon(poppler_annot, nullptr);

    // Verify that the mock setIcon was called with an empty string
    testing::Mock::VerifyAndClearExpectations(mock_annot_text);
}

// Test: Exceptional case with a malformed PopplerAnnotText (invalid cast)
TEST_F(PopplerAnnotTextSetIconTest_2094, SetIconInvalidPopplerAnnotText_2094) {
    // Try casting to invalid type (simulating failure in the static_cast)
    EXPECT_DEATH(poppler_annot_text_set_icon(reinterpret_cast<PopplerAnnotText*>(nullptr), "icon"), ".*");

    // We expect the program to crash due to invalid cast (DEATH test)
}

// Test: Boundary case with an empty string icon
TEST_F(PopplerAnnotTextSetIconTest_2095, SetIconEmptyString_2095) {
    std::string empty_icon = "";
    EXPECT_CALL(*mock_annot_text, setIcon(empty_icon)).Times(1);

    // Call the function being tested with an empty string
    poppler_annot_text_set_icon(poppler_annot, empty_icon.c_str());

    // Verify that the mock setIcon was called with the empty string
    testing::Mock::VerifyAndClearExpectations(mock_annot_text);
}

// Test: Boundary case with a very long string icon
TEST_F(PopplerAnnotTextSetIconTest_2096, SetIconLongString_2096) {
    std::string long_icon(1000, 'a');  // String with 1000 'a' characters
    EXPECT_CALL(*mock_annot_text, setIcon(long_icon)).Times(1);

    // Call the function being tested with a long string
    poppler_annot_text_set_icon(poppler_annot, long_icon.c_str());

    // Verify that the mock setIcon was called with the long string
    testing::Mock::VerifyAndClearExpectations(mock_annot_text);
}