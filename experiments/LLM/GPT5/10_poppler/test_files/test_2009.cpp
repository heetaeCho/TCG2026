#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/annot_stamp_not_approved.h"
#include "./TestProjects/poppler/poppler/PDFDoc.h"
#include "./TestProjects/poppler/poppler/Dict.h"

// Mocking the PDFDoc class to simulate the document behavior
class MockPDFDoc : public PDFDoc {
public:
    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

// Test fixture for the getNotApprovedStampExtGStateDict function
class AnnotStampNotApprovedTest_2009 : public ::testing::Test {
protected:
    // You can set up any common test resources here
    MockPDFDoc* mockDoc;

    void SetUp() override {
        mockDoc = new MockPDFDoc();
    }

    void TearDown() override {
        delete mockDoc;
    }
};

// Test for normal operation
TEST_F(AnnotStampNotApprovedTest_2009, GetNotApprovedStampExtGStateDict_NormalOperation_2009) {
    // Arrange
    XRef* mockXRef = nullptr;  // Mock the XRef object
    EXPECT_CALL(*mockDoc, getXRef())
        .WillOnce(testing::Return(mockXRef));

    // Act
    Dict* result = getNotApprovedStampExtGStateDict(mockDoc);

    // Assert
    ASSERT_NE(result, nullptr);  // Check if result is not null
    EXPECT_TRUE(result->hasKey("a0"));  // Check if the key "a0" exists in the returned dictionary
    EXPECT_TRUE(result->hasKey("a1"));  // Check if the key "a1" exists in the returned dictionary
}

// Test for boundary conditions
TEST_F(AnnotStampNotApprovedTest_2009, GetNotApprovedStampExtGStateDict_EmptyXRef_2009) {
    // Arrange
    XRef* mockXRef = nullptr;
    EXPECT_CALL(*mockDoc, getXRef())
        .WillOnce(testing::Return(mockXRef));

    // Act
    Dict* result = getNotApprovedStampExtGStateDict(mockDoc);

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a0"));
    EXPECT_TRUE(result->hasKey("a1"));
}

// Test for exceptional or error cases
TEST_F(AnnotStampNotApprovedTest_2009, GetNotApprovedStampExtGStateDict_NullDoc_2009) {
    // Act and Assert
    EXPECT_DEATH(getNotApprovedStampExtGStateDict(nullptr), ".*");  // Expecting a crash if the document is null
}