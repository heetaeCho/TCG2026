#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/annot_stamp_sold.h"  // Adjust this include path to your actual file
#include "poppler/PDFDoc.h"
#include "poppler/Dict.h"
#include "poppler/Object.h"

// Mock class for PDFDoc since getSoldStampExtGStateDict depends on it
class MockPDFDoc : public PDFDoc {
public:
    MOCK_METHOD(XRef*, getXRef, (), (const, override));  // Mocking getXRef method
};

// Test suite for getSoldStampExtGStateDict
class AnnotStampSoldTest : public ::testing::Test {
protected:
    MockPDFDoc* mockDoc;  // Pointer to mock PDFDoc

    void SetUp() override {
        // Create mock PDFDoc
        mockDoc = new MockPDFDoc(/* parameters as needed */);
    }

    void TearDown() override {
        delete mockDoc;
    }
};

// Test normal operation of getSoldStampExtGStateDict
TEST_F(AnnotStampSoldTest, getSoldStampExtGStateDict_NormalOperation_2011) {
    // Arrange
    XRef* mockXRef = nullptr; // Use the actual mock or a dummy instance if needed
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* result = getSoldStampExtGStateDict(mockDoc);

    // Assert: Check that the result is not nullptr and is of the expected type
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a0"));
    EXPECT_TRUE(result->hasKey("a1"));
}

// Test if the method handles the case when PDFDoc's getXRef returns a null XRef
TEST_F(AnnotStampSoldTest, getSoldStampExtGStateDict_NullXRef_2011) {
    // Arrange: Mock PDFDoc to return a null XRef
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(nullptr));

    // Act
    Dict* result = getSoldStampExtGStateDict(mockDoc);

    // Assert: Check that result is not nullptr (since Dict constructor will still return a valid Dict object)
    ASSERT_NE(result, nullptr);
}

// Test exceptional case: Check if the dictionary is properly set when XRef is valid
TEST_F(AnnotStampSoldTest, getSoldStampExtGStateDict_ValidXRef_2011) {
    // Arrange: Mock the XRef and the behavior of getXRef to return it
    XRef* mockXRef = new XRef();  // Assuming XRef constructor is available
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* result = getSoldStampExtGStateDict(mockDoc);

    // Assert: Check that the dictionary contains keys and values as expected
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a0"));
    EXPECT_TRUE(result->hasKey("a1"));
    EXPECT_EQ(result->lookup("a0", 0).getReal(), 0.588235);
    EXPECT_EQ(result->lookup("a1", 0).getReal(), 1);
}

// Test boundary case: Empty PDFDoc scenario, where getXRef may return null or an empty XRef
TEST_F(AnnotStampSoldTest, getSoldStampExtGStateDict_EmptyPDFDoc_2011) {
    // Arrange: Mock PDFDoc to return a null XRef
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(nullptr));

    // Act
    Dict* result = getSoldStampExtGStateDict(mockDoc);

    // Assert: Ensure that the result is still a valid Dict object, but check its contents
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->hasKey("a0"));
    EXPECT_FALSE(result->hasKey("a1"));
}

// Test case where the PDFDoc object is invalid
TEST_F(AnnotStampSoldTest, getSoldStampExtGStateDict_InvalidPDFDoc_2011) {
    // Arrange: Simulate an invalid PDFDoc behavior by mocking error state, if applicable
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(nullptr));  // Invalid or corrupted XRef

    // Act
    Dict* result = getSoldStampExtGStateDict(mockDoc);

    // Assert: Ensure result is still returned (even in an invalid state), or we handle error properly
    ASSERT_NE(result, nullptr);
    // Depending on design, you could check for specific error handling in the Dict object
}

// Test case where the Dict returned by getSoldStampExtGStateDict is not empty but invalid in some way
TEST_F(AnnotStampSoldTest, getSoldStampExtGStateDict_InvalidDictContent_2011) {
    // Arrange: Mock PDFDoc and return a valid XRef
    XRef* mockXRef = new XRef();
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* result = getSoldStampExtGStateDict(mockDoc);

    // Assert: The returned Dict should not contain invalid keys
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->hasKey("invalidKey"));
}