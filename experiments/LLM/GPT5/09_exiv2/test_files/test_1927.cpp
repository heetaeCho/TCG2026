#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPMeta-GetSet.h"  // Include the header file where ChooseLocalizedText is declared

// Mock for XMP_Node to be used in tests
class MockXMPNode : public XMP_Node {
public:
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
};

// Test Fixture for ChooseLocalizedText
class ChooseLocalizedTextTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup necessary mock objects or test data here
    }

    void TearDown() override {
        // Clean up mock objects or other resources here
    }
};

// Normal operation test case
TEST_F(ChooseLocalizedTextTest, NormalOperation_1927) {
    XMP_Node* arrayNode = new MockXMPNode();
    XMP_Node* itemNode = nullptr;
    XMP_StringPtr genericLang = "en";
    XMP_StringPtr specificLang = "en-US";

    // Set up the behavior of arrayNode using mocks, including children, options, etc.
    // Example: Expectations for specific function calls that will occur during ChooseLocalizedText execution.

    EXPECT_CALL(*arrayNode, children).WillRepeatedly(testing::Return(...)); // Mock expected children
    EXPECT_CALL(*arrayNode, options).WillRepeatedly(testing::Return(...)); // Mock options

    // Call the function under test
    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, genericLang, specificLang, &itemNode);

    // Check the result and itemNode
    EXPECT_EQ(result, kXMP_CLT_SpecificMatch);
    EXPECT_NE(itemNode, nullptr);  // Ensure itemNode is set
}

// Boundary condition test case (empty children)
TEST_F(ChooseLocalizedTextTest, EmptyChildren_1927) {
    XMP_Node* arrayNode = new MockXMPNode();
    XMP_Node* itemNode = nullptr;
    XMP_StringPtr genericLang = "en";
    XMP_StringPtr specificLang = "en-US";

    // Set the arrayNode's children to be empty
    EXPECT_CALL(*arrayNode, children).WillRepeatedly(testing::Return(std::vector<XMP_Node*>()));
    EXPECT_CALL(*arrayNode, options).WillRepeatedly(testing::Return(...)); // Mock options

    // Call the function under test
    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, genericLang, specificLang, &itemNode);

    // Check the result and itemNode
    EXPECT_EQ(result, kXMP_CLT_NoValues);
    EXPECT_EQ(itemNode, nullptr);  // Ensure itemNode is not set
}

// Boundary condition test case (arrayNode with no language qualifier)
TEST_F(ChooseLocalizedTextTest, NoLanguageQualifier_1927) {
    XMP_Node* arrayNode = new MockXMPNode();
    XMP_Node* itemNode = nullptr;
    XMP_StringPtr genericLang = "en";
    XMP_StringPtr specificLang = "en-US";

    // Set up the children with no language qualifier
    EXPECT_CALL(*arrayNode, children).WillRepeatedly(testing::Return(...)); // Mock children with no language qualifier

    // Call the function under test
    EXPECT_THROW({
        ChooseLocalizedText(arrayNode, genericLang, specificLang, &itemNode);
    }, std::runtime_error);  // Expecting an exception due to missing language qualifier
}

// Test case for multiple generic matches
TEST_F(ChooseLocalizedTextTest, MultipleGenericMatches_1927) {
    XMP_Node* arrayNode = new MockXMPNode();
    XMP_Node* itemNode = nullptr;
    XMP_StringPtr genericLang = "en";
    XMP_StringPtr specificLang = "fr-FR";

    // Set up the children with multiple generic matches
    EXPECT_CALL(*arrayNode, children).WillRepeatedly(testing::Return(...)); // Mock children with multiple partial matches

    // Call the function under test
    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, genericLang, specificLang, &itemNode);

    // Check the result
    EXPECT_EQ(result, kXMP_CLT_MultipleGeneric);
}

// Test case for specific language match
TEST_F(ChooseLocalizedTextTest, SpecificLanguageMatch_1927) {
    XMP_Node* arrayNode = new MockXMPNode();
    XMP_Node* itemNode = nullptr;
    XMP_StringPtr genericLang = "en";
    XMP_StringPtr specificLang = "en-US";

    // Set up the children with the specific language match
    EXPECT_CALL(*arrayNode, children).WillRepeatedly(testing::Return(...)); // Mock children with specificLang match

    // Call the function under test
    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, genericLang, specificLang, &itemNode);

    // Check the result
    EXPECT_EQ(result, kXMP_CLT_SpecificMatch);
}