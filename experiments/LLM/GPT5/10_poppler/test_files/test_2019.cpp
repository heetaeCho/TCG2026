#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h" // Include the header for Annot class and relevant functions
#include "Object.h" // Include Object class and its dependencies
#include "PDFDoc.h" // Include PDFDoc class
#include "LinkAction.h" // Include LinkAction class

using namespace testing;

// Mock classes for dependencies
class MockObject : public Object {
public:
    MOCK_METHOD(bool, isDict, (), (const, override));
    MOCK_METHOD(Object, dictLookup, (std::string_view key), (const, override));
};

class MockPDFDoc : public PDFDoc {
public:
    MOCK_METHOD(XRef*, getXRef, (), (const, override));
    MOCK_METHOD(Catalog*, getCatalog, (), (const, override));
};

// Test fixture for testing getAdditionalAction
class GetAdditionalActionTest_2019 : public Test {
protected:
    MockObject additionalActionsMock;
    MockPDFDoc docMock;

    // Helper to simulate the function call
    std::unique_ptr<LinkAction> callGetAdditionalAction(Annot::AdditionalActionsType type) {
        return getAdditionalAction(type, &additionalActionsMock, &docMock);
    }
};

// Normal operation test: Valid key in the dictionary
TEST_F(GetAdditionalActionTest_2019, ValidAction_ReturnsLinkAction_2019) {
    // Setting up expectations for mock behavior
    EXPECT_CALL(additionalActionsMock, isDict())
        .WillOnce(Return(true));
    EXPECT_CALL(additionalActionsMock, dictLookup("E"))
        .WillOnce(Return(Object(ObjType::dict, "some action")));

    // Test the function
    auto result = callGetAdditionalAction(Annot::actionCursorEntering);

    // Validate the result
    ASSERT_TRUE(result != nullptr);
}

// Boundary condition test: Null or empty action (dictLookup returns null)
TEST_F(GetAdditionalActionTest_2019, EmptyAction_ReturnsNull_2019) {
    EXPECT_CALL(additionalActionsMock, isDict())
        .WillOnce(Return(true));
    EXPECT_CALL(additionalActionsMock, dictLookup("E"))
        .WillOnce(Return(Object(ObjType::null)));

    auto result = callGetAdditionalAction(Annot::actionCursorEntering);

    // Expect no action returned
    ASSERT_EQ(result, nullptr);
}

// Exceptional case test: No matching key found
TEST_F(GetAdditionalActionTest_2019, NoMatchingKey_ReturnsNull_2019) {
    EXPECT_CALL(additionalActionsMock, isDict())
        .WillOnce(Return(true));
    EXPECT_CALL(additionalActionsMock, dictLookup("E"))
        .WillOnce(Return(Object(ObjType::null)));

    auto result = callGetAdditionalAction(Annot::actionCursorEntering);

    ASSERT_EQ(result, nullptr);
}

// Test when the additionalActionsObject is not a dictionary
TEST_F(GetAdditionalActionTest_2019, NotADict_ReturnsNull_2019) {
    EXPECT_CALL(additionalActionsMock, isDict())
        .WillOnce(Return(false)); // Simulate that it's not a dictionary

    auto result = callGetAdditionalAction(Annot::actionCursorEntering);

    ASSERT_EQ(result, nullptr);
}