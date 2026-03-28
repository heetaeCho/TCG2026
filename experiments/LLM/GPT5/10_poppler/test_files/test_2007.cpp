#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/annot_stamp_experimental.h"
#include "poppler/Dict.h"
#include "poppler/PDFDoc.h"

// Mock dependencies
class MockXRef : public XRef {
public:
    MOCK_METHOD(void, someMethod, (), (override));
};

class MockPDFDoc : public PDFDoc {
public:
    MockPDFDoc() : PDFDoc(nullptr, std::optional<GooString>(), std::optional<GooString>(), nullptr) {}

    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

// Test Fixture for getExperimentalStampExtGStateDict
class GetExperimentalStampExtGStateDictTest_2007 : public testing::Test {
protected:
    MockPDFDoc mockDoc;

    void SetUp() override {
        // Set up mock expectations if needed
    }
};

// Normal operation test
TEST_F(GetExperimentalStampExtGStateDictTest_2007, NormalOperation_2007) {
    // Arrange
    XRef *mockXRef = mockDoc.getXRef();

    // Mock expected behavior for the getXRef() function
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict *result = getExperimentalStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a0"));
    EXPECT_TRUE(result->hasKey("a1"));
}

// Boundary conditions test
TEST_F(GetExperimentalStampExtGStateDictTest_2007, EmptyPDFDoc_2007) {
    // Arrange
    MockPDFDoc emptyDoc;

    // Act
    Dict *result = getExperimentalStampExtGStateDict(&emptyDoc);

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a0"));
    EXPECT_TRUE(result->hasKey("a1"));
}

// Exceptional case test
TEST_F(GetExperimentalStampExtGStateDictTest_2007, NullXRef_2007) {
    // Arrange
    MockPDFDoc nullXRefDoc;
    EXPECT_CALL(nullXRefDoc, getXRef()).WillOnce(testing::Return(nullptr));

    // Act
    Dict *result = getExperimentalStampExtGStateDict(&nullXRefDoc);

    // Assert
    ASSERT_EQ(result, nullptr);  // Should return nullptr as the XRef is invalid
}