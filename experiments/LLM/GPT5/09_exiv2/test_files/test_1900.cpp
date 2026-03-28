#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"

// Mock class for XMP_Node to avoid dealing with complex internals
class MockXMP_Node : public XMP_Node {
public:
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));

    MockXMP_Node(XMP_Node* _parent, const XMP_VarString& _name, const XMP_VarString& _value, XMP_OptionBits _options)
        : XMP_Node(_parent, _name, _value, _options) {}
    
    MockXMP_Node(XMP_Node* _parent, const XMP_VarString& _name, XMP_OptionBits _options)
        : XMP_Node(_parent, _name, _options) {}
};

// Test Fixture for CloneOffspring tests
class CloneOffspringTest_1900 : public ::testing::Test {
protected:
    MockXMP_Node* origParent;
    MockXMP_Node* cloneParent;

    virtual void SetUp() {
        // Setup: Create original and clone parent nodes for testing
        origParent = new MockXMP_Node(nullptr, "Parent", "Original", 0);
        cloneParent = new MockXMP_Node(nullptr, "Parent", "Clone", 0);
    }

    virtual void TearDown() {
        delete origParent;
        delete cloneParent;
    }
};

// Test Case 1: CloneOffspring should correctly clone the qualifiers
TEST_F(CloneOffspringTest_1900, CloneQualifiers_1900) {
    // Given: Create a mock qualifier node
    MockXMP_Node* origQual = new MockXMP_Node(origParent, "Qualifier", "Value", 0);
    origParent->qualifiers.push_back(origQual);

    // When: CloneOffspring is invoked
    CloneOffspring(origParent, cloneParent);

    // Then: Ensure that the cloned parent has the same qualifier
    ASSERT_EQ(cloneParent->qualifiers.size(), 1);
    EXPECT_EQ(cloneParent->qualifiers[0]->name, "Qualifier");
    EXPECT_EQ(cloneParent->qualifiers[0]->value, "Value");

    delete origQual;
}

// Test Case 2: CloneOffspring should correctly clone the children
TEST_F(CloneOffspringTest_1900, CloneChildren_1900) {
    // Given: Create a mock child node
    MockXMP_Node* origChild = new MockXMP_Node(origParent, "Child", "ChildValue", 0);
    origParent->children.push_back(origChild);

    // When: CloneOffspring is invoked
    CloneOffspring(origParent, cloneParent);

    // Then: Ensure that the cloned parent has the same child
    ASSERT_EQ(cloneParent->children.size(), 1);
    EXPECT_EQ(cloneParent->children[0]->name, "Child");
    EXPECT_EQ(cloneParent->children[0]->value, "ChildValue");

    delete origChild;
}

// Test Case 3: CloneOffspring should handle empty qualifiers and children lists
TEST_F(CloneOffspringTest_1900, EmptyQualifiersAndChildren_1900) {
    // Given: Empty parent node
    origParent->qualifiers.clear();
    origParent->children.clear();

    // When: CloneOffspring is invoked
    CloneOffspring(origParent, cloneParent);

    // Then: Ensure that the clone has no qualifiers or children
    EXPECT_TRUE(cloneParent->qualifiers.empty());
    EXPECT_TRUE(cloneParent->children.empty());
}

// Test Case 4: CloneOffspring should handle the case when qualifiers are present but children are not
TEST_F(CloneOffspringTest_1900, OnlyQualifiers_1900) {
    // Given: Parent with qualifiers but no children
    MockXMP_Node* origQual = new MockXMP_Node(origParent, "Qualifier", "Value", 0);
    origParent->qualifiers.push_back(origQual);
    origParent->children.clear();

    // When: CloneOffspring is invoked
    CloneOffspring(origParent, cloneParent);

    // Then: Ensure that the cloned parent has the same qualifier and no children
    ASSERT_EQ(cloneParent->qualifiers.size(), 1);
    ASSERT_TRUE(cloneParent->children.empty());

    delete origQual;
}

// Test Case 5: CloneOffspring should handle the case when children are present but qualifiers are not
TEST_F(CloneOffspringTest_1900, OnlyChildren_1900) {
    // Given: Parent with children but no qualifiers
    MockXMP_Node* origChild = new MockXMP_Node(origParent, "Child", "ChildValue", 0);
    origParent->children.push_back(origChild);
    origParent->qualifiers.clear();

    // When: CloneOffspring is invoked
    CloneOffspring(origParent, cloneParent);

    // Then: Ensure that the cloned parent has the same child and no qualifiers
    ASSERT_EQ(cloneParent->children.size(), 1);
    ASSERT_TRUE(cloneParent->qualifiers.empty());

    delete origChild;
}