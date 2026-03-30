#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "Dict.h"

// Mocking PDFDoc class for testing purposes.
class MockPDFDoc : public PDFDoc {
public:
    MockPDFDoc() : PDFDoc(nullptr, std::nullopt, std::nullopt, nullptr) {}
    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

// Test fixture for the function getForCommentStampExtGStateDict
class GetForCommentStampExtGStateDictTest_2006 : public ::testing::Test {
protected:
    void SetUp() override {
        mockDoc = std::make_unique<MockPDFDoc>();
    }

    std::unique_ptr<MockPDFDoc> mockDoc;
};

// Normal operation test case
TEST_F(GetForCommentStampExtGStateDictTest_2006, NormalOperation_2006) {
    // Arrange
    XRef mockXRef;
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(&mockXRef));

    // Act
    Dict* result = getForCommentStampExtGStateDict(mockDoc.get());

    // Assert
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(result->hasKey("a0"));
    ASSERT_TRUE(result->hasKey("a1"));
    ASSERT_EQ(result->lookup("a0", 0).toReal(), 0.588235);
    ASSERT_EQ(result->lookup("a1", 0).toReal(), 1.0);
}

// Boundary condition test case - empty document
TEST_F(GetForCommentStampExtGStateDictTest_2006, EmptyDocument_2006) {
    // Arrange
    XRef mockXRef;
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(&mockXRef));

    // Act
    Dict* result = getForCommentStampExtGStateDict(mockDoc.get());

    // Assert
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(result->hasKey("a0"));
    ASSERT_TRUE(result->hasKey("a1"));
}

// Exceptional case - if getXRef() returns nullptr (edge case)
TEST_F(GetForCommentStampExtGStateDictTest_2006, XRefIsNull_2006) {
    // Arrange
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(nullptr));

    // Act
    Dict* result = getForCommentStampExtGStateDict(mockDoc.get());

    // Assert
    ASSERT_EQ(result, nullptr);  // Expecting a nullptr if XRef is null
}