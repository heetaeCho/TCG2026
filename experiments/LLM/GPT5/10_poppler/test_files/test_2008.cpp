#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h" // Include the header for PDFDoc and Dict
#include "Dict.h"

class MockPDFDoc : public PDFDoc {
public:
    MockPDFDoc() : PDFDoc(nullptr, {}, {}, {}) {}
    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

class GetExpiredStampExtGStateDictTest_2008 : public ::testing::Test {
protected:
    // Setup the PDFDoc and MockPDFDoc
    std::unique_ptr<MockPDFDoc> mockDoc;

    void SetUp() override {
        mockDoc = std::make_unique<MockPDFDoc>();
    }
};

// Test for Normal Operation: Check if the dictionary is created as expected.
TEST_F(GetExpiredStampExtGStateDictTest_2008, CreateExpiredStampExtGStateDict_2008) {
    // Mock the return value of getXRef() to return a non-null XRef pointer
    XRef mockXRef;
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(::testing::Return(&mockXRef));

    // Call the function under test
    Dict* dict = getExpiredStampExtGStateDict(mockDoc.get());

    // Assertions to verify the behavior
    ASSERT_NE(dict, nullptr);  // Ensure dict is not null
    EXPECT_TRUE(dict->hasKey("a0")); // Expect key "a0" to exist in the dict
    EXPECT_TRUE(dict->hasKey("a1")); // Expect key "a1" to exist in the dict

    // Clean up if necessary
    delete dict;
}

// Test for Boundary Condition: Check if empty PDFDoc can handle the function
TEST_F(GetExpiredStampExtGStateDictTest_2008, EmptyPDFDoc_2008) {
    // Create an empty PDFDoc and mock getXRef to return a valid pointer
    XRef mockXRef;
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(::testing::Return(&mockXRef));

    // Call the function under test
    Dict* dict = getExpiredStampExtGStateDict(mockDoc.get());

    // Assertions to check if the dictionary is created properly even for an empty doc
    ASSERT_NE(dict, nullptr);
    EXPECT_TRUE(dict->hasKey("a0"));
    EXPECT_TRUE(dict->hasKey("a1"));

    // Clean up if necessary
    delete dict;
}

// Test for Exceptional Case: What happens if getXRef() returns nullptr
TEST_F(GetExpiredStampExtGStateDictTest_2008, NullXRef_2008) {
    // Mock getXRef to return nullptr
    EXPECT_CALL(*mockDoc, getXRef()).WillOnce(::testing::Return(nullptr));

    // Call the function under test and expect it to return nullptr or handle gracefully
    Dict* dict = getExpiredStampExtGStateDict(mockDoc.get());

    // Assertions to verify that function handles the null XRef scenario
    EXPECT_EQ(dict, nullptr);
}