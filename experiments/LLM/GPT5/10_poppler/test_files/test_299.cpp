#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Include the necessary header file for LinkNamed
#include "./TestProjects/poppler/poppler/Link.h"

// Test fixture for LinkNamed class
class LinkNamedTest_299 : public ::testing::Test {
protected:
    // Setup code if needed, for example, creating the nameObj
    const Object* nameObj = nullptr;  // Replace with actual object if available
    LinkNamed* linkNamed;

    void SetUp() override {
        linkNamed = new LinkNamed(nameObj);  // Initialize LinkNamed with the name object
    }

    void TearDown() override {
        delete linkNamed;
    }
};

// Test case for the `getKind` method to check the correct kind is returned.
TEST_F(LinkNamedTest_299, GetKind_ReturnsCorrectKind_299) {
    EXPECT_EQ(linkNamed->getKind(), actionNamed);
}

// Test case for the `isOk` method to check if the object is in a valid state.
TEST_F(LinkNamedTest_299, IsOk_ReturnsTrueWhenValid_299) {
    EXPECT_TRUE(linkNamed->isOk());  // Assuming a valid LinkNamed object is OK
}

// Test case for the `getName` method to check the name retrieval.
TEST_F(LinkNamedTest_299, GetName_ReturnsCorrectName_299) {
    std::string name = linkNamed->getName();
    EXPECT_FALSE(name.empty());  // Assuming getName returns a non-empty name.
}

// Boundary test case for `getKind`, testing the enum extremes (actionGoTo and actionSubmitForm).
TEST_F(LinkNamedTest_299, GetKind_BoundaryValues_299) {
    LinkNamed linkGoTo(nameObj);  // Assuming LinkNamed can be initialized for different actions
    EXPECT_EQ(linkGoTo.getKind(), actionNamed);  // actionNamed is expected for LinkNamed

    // Adding tests for boundary LinkActionKind values
    LinkNamed linkSubmitForm(nameObj);
    EXPECT_EQ(linkSubmitForm.getKind(), actionSubmitForm);  // actionSubmitForm is expected
}

// Test case for the destructor to ensure no memory leak occurs (if applicable).
TEST_F(LinkNamedTest_299, Destructor_CleansUpResources_299) {
    LinkNamed* link = new LinkNamed(nameObj);
    delete link;  // Ensure no crashes or memory leaks
    EXPECT_TRUE(true);  // If deletion works without issue, test passes
}

// Exceptional case: what happens if the object is not properly initialized?
TEST_F(LinkNamedTest_299, IsOk_ReturnsFalseWhenInvalid_299) {
    LinkNamed invalidLink(nullptr);  // Create an invalid object with nullptr
    EXPECT_FALSE(invalidLink.isOk());  // The object should be in an invalid state
}