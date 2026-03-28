#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-private.h"

// Mock for the Annot class used within PopplerAnnot
class MockAnnot : public Annot {
public:
    MOCK_METHOD(const GooString*, getContents, (), (const, override));
};

// Test case for poppler_annot_get_contents with valid PopplerAnnot
TEST_F(PopplerAnnotTest_2063, GetContentsReturnsUtf8String_2063) {
    // Arrange
    PopplerAnnot poppler_annot;
    MockAnnot mock_annot;
    poppler_annot.annot = std::make_shared<MockAnnot>();
    
    const char* expected_contents = "Test content";
    GooString goo_string(expected_contents);
    
    // Expect that getContents() will return a non-empty GooString
    EXPECT_CALL(mock_annot, getContents()).WillOnce(testing::Return(&goo_string));
    
    // Act
    gchar* result = poppler_annot_get_contents(&poppler_annot);
    
    // Assert
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result, expected_contents);
}

// Test case for poppler_annot_get_contents with empty content in PopplerAnnot
TEST_F(PopplerAnnotTest_2063, GetContentsReturnsNullForEmptyContent_2063) {
    // Arrange
    PopplerAnnot poppler_annot;
    MockAnnot mock_annot;
    poppler_annot.annot = std::make_shared<MockAnnot>();
    
    // Expect that getContents() will return an empty GooString
    EXPECT_CALL(mock_annot, getContents()).WillOnce(testing::Return(new GooString()));
    
    // Act
    gchar* result = poppler_annot_get_contents(&poppler_annot);
    
    // Assert
    ASSERT_EQ(result, nullptr);
}

// Test case for poppler_annot_get_contents when PopplerAnnot is invalid
TEST_F(PopplerAnnotTest_2063, GetContentsReturnsNullForInvalidPopplerAnnot_2063) {
    // Arrange
    PopplerAnnot invalid_poppler_annot;  // Invalid PopplerAnnot
    
    // Act
    gchar* result = poppler_annot_get_contents(&invalid_poppler_annot);
    
    // Assert
    ASSERT_EQ(result, nullptr);
}

// Test case for poppler_annot_get_contents where getContents returns nullptr
TEST_F(PopplerAnnotTest_2063, GetContentsReturnsNullForNullContents_2063) {
    // Arrange
    PopplerAnnot poppler_annot;
    MockAnnot mock_annot;
    poppler_annot.annot = std::make_shared<MockAnnot>();
    
    // Expect that getContents() will return nullptr
    EXPECT_CALL(mock_annot, getContents()).WillOnce(testing::Return(nullptr));
    
    // Act
    gchar* result = poppler_annot_get_contents(&poppler_annot);
    
    // Assert
    ASSERT_EQ(result, nullptr);
}