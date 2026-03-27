#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"

// Mocks
class MockPopplerAnnot : public PopplerAnnot {
public:
    MOCK_METHOD(AnnotMarkup*, getAnnot, (), (override));
};

// Test Case for poppler_annot_markup_get_subject
TEST_F(PopplerAnnotTest_2086, GetSubjectReturnsNullIfNotValidAnnot_2086) {
    // Arrange
    PopplerAnnotMarkup *poppler_annot = nullptr; // Invalid input

    // Act
    gchar *subject = poppler_annot_markup_get_subject(poppler_annot);

    // Assert
    EXPECT_EQ(subject, nullptr);
}

TEST_F(PopplerAnnotTest_2086, GetSubjectReturnsSubjectIfValidAnnot_2086) {
    // Arrange
    MockPopplerAnnot mockAnnot;
    PopplerAnnotMarkup *poppler_annot = reinterpret_cast<PopplerAnnotMarkup*>(&mockAnnot);
    GooString goo_subject("Test Subject");
    
    // Set up mock to return the expected subject
    EXPECT_CALL(mockAnnot, getAnnot())
        .WillOnce(testing::Return(&goo_subject));

    // Act
    gchar *subject = poppler_annot_markup_get_subject(poppler_annot);

    // Assert
    EXPECT_EQ(subject, "_poppler_goo_string_to_utf8");
}

TEST_F(PopplerAnnotTest_2086, GetSubjectReturnsNullIfNoSubject_2086) {
    // Arrange
    MockPopplerAnnot mockAnnot;
    PopplerAnnotMarkup *poppler_annot = reinterpret_cast<PopplerAnnotMarkup*>(&mockAnnot);
    
    // Set up mock to return null subject
    EXPECT_CALL(mockAnnot, getAnnot())
        .WillOnce(testing::Return(nullptr));

    // Act
    gchar *subject = poppler_annot_markup_get_subject(poppler_annot);

    // Assert
    EXPECT_EQ(subject, nullptr);
}

TEST_F(PopplerAnnotTest_2086, GetSubjectHandlesNullPopplerAnnot_2086) {
    // Arrange
    PopplerAnnotMarkup *poppler_annot = nullptr;  // Invalid PopplerAnnotMarkup

    // Act
    gchar *subject = poppler_annot_markup_get_subject(poppler_annot);

    // Assert
    EXPECT_EQ(subject, nullptr); // Returns nullptr due to invalid annotation
}