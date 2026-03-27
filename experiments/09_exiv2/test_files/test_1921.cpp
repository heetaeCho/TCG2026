#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"



using namespace testing;



// Mock class for XMP_Node to verify interactions

class MockXMPNode : public XMP_Node {

public:

    MockXMPNode(XMP_Node * _parent, const XMP_VarString & _name, XMP_OptionBits _options)

        : XMP_Node(_parent, _name, _options) {}



    MOCK_METHOD(void, RemoveChildren, (), (override));

    MOCK_METHOD(void, RemoveQualifiers, (), (override));

    MOCK_METHOD(void, ClearNode, (), (override));

};



// Test fixture for the tests

class RemoveSchemaChildrenTest_1921 : public ::testing::Test {

protected:

    void SetUp() override {

        parent = new XMP_Node(nullptr, "Parent", 0);

        schemaNode = new XMP_Node(parent, "SchemaName", kXMP_MarkNodeIsSchema);

        propertyNode = new XMP_Node(schemaNode, "PropertyName", 0);



        schemaNode->children.push_back(propertyNode);

        parent->children.push_back(schemaNode);

    }



    void TearDown() override {

        delete parent;

    }



    XMP_Node* parent;

    XMP_Node* schemaNode;

    XMP_Node* propertyNode;

};



TEST_F(RemoveSchemaChildrenTest_1921, RemoveSingleProperty_1921) {

    size_t initialSize = schemaNode->children.size();

    RemoveSchemaChildren(schemaNode->children.begin(), false);

    EXPECT_EQ(schemaNode->children.size(), initialSize - 1);

}



TEST_F(RemoveSchemaChildrenTest_1921, RemoveAllProperties_1921) {

    XMP_Node* anotherProperty = new XMP_Node(schemaNode, "AnotherPropertyName", 0);

    schemaNode->children.push_back(anotherProperty);



    size_t initialSize = schemaNode->children.size();

    RemoveSchemaChildren(schemaNode->children.begin(), true);

    EXPECT_EQ(schemaNode->children.empty(), true);

}



TEST_F(RemoveSchemaChildrenTest_1921, SchemaRemovedWhenEmpty_1921) {

    RemoveSchemaChildren(schemaNode->children.begin(), false);

    EXPECT_TRUE(std::find(parent->children.begin(), parent->children.end(), schemaNode) == parent->children.end());

}



TEST_F(RemoveSchemaChildrenTest_1921, NoPropertiesToRemove_1921) {

    XMP_Node* emptySchema = new XMP_Node(parent, "EmptySchema", kXMP_MarkNodeIsSchema);

    parent->children.push_back(emptySchema);



    size_t initialParentSize = parent->children.size();

    RemoveSchemaChildren(emptySchema->children.begin(), false);

    EXPECT_EQ(parent->children.size(), initialParentSize);

}



TEST_F(RemoveSchemaChildrenTest_1921, ExternalPropertyNotRemovedWhenFalseFlag_1921) {

    // Assuming IsExternalProperty returns true for "PropertyName"

    ON_CALL(*propertyNode, /* Mock method call if needed */).WillByDefault(Return(true));



    size_t initialSize = schemaNode->children.size();

    RemoveSchemaChildren(schemaNode->children.begin(), false);

    EXPECT_EQ(schemaNode->children.size(), initialSize);

}



TEST_F(RemoveSchemaChildrenTest_1921, ExternalPropertyRemovedWhenTrueFlag_1921) {

    // Assuming IsExternalProperty returns true for "PropertyName"

    ON_CALL(*propertyNode, /* Mock method call if needed */).WillByDefault(Return(true));



    size_t initialSize = schemaNode->children.size();

    RemoveSchemaChildren(schemaNode->children.begin(), true);

    EXPECT_EQ(schemaNode->children.size(), initialSize - 1);

}

```


