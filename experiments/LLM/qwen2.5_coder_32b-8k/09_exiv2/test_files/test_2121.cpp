#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



using namespace XMP_NS;



class AddQualifierNodeTest_2121 : public ::testing::Test {

protected:

    XMP_Node* parent;

    XMP_VarString name;

    XMP_VarString value;



    void SetUp() override {

        parent = new XMP_Node(nullptr, "parentName", kXMP_PropIsQualifier);

        name = "qualifierName";

        value = "qualifierValue";

    }



    void TearDown() override {

        delete parent;

    }

};



TEST_F(AddQualifierNodeTest_2121, AddNormalQualifier_2121) {

    XMP_Node* qualifierNode = AddQualifierNode(parent, name, value);

    EXPECT_EQ(qualifierNode->name, name);

    EXPECT_EQ(qualifierNode->value, value);

    EXPECT_EQ(qualifierNode->parent, parent);

    EXPECT_EQ(parent->qualifiers.size(), 1);

    EXPECT_TRUE((parent->options & kXMP_PropHasQualifiers) != 0);

}



TEST_F(AddQualifierNodeTest_2121, AddLangQualifier_2121) {

    name = "xml:lang";

    XMP_Node* qualifierNode = AddQualifierNode(parent, name, value);

    EXPECT_EQ(qualifierNode->name, name);

    EXPECT_EQ(qualifierNode->value, value);

    EXPECT_EQ(qualifierNode->parent, parent);

    EXPECT_EQ(parent->qualifiers.size(), 1);

    EXPECT_TRUE((parent->options & kXMP_PropHasLang) != 0);

    EXPECT_TRUE((parent->options & kXMP_PropHasQualifiers) != 0);

}



TEST_F(AddQualifierNodeTest_2121, AddTypeQualifier_2121) {

    name = "rdf:type";

    XMP_Node* qualifierNode = AddQualifierNode(parent, name, value);

    EXPECT_EQ(qualifierNode->name, name);

    EXPECT_EQ(qualifierNode->value, value);

    EXPECT_EQ(qualifierNode->parent, parent);

    EXPECT_EQ(parent->qualifiers.size(), 1);

    EXPECT_TRUE((parent->options & kXMP_PropHasType) != 0);

    EXPECT_TRUE((parent->options & kXMP_PropHasQualifiers) != 0);

}



TEST_F(AddQualifierNodeTest_2121, AddMultipleQualifiers_2121) {

    XMP_Node* qualifierNode1 = AddQualifierNode(parent, "qualifier1", "value1");

    XMP_Node* qualifierNode2 = AddQualifierNode(parent, "xml:lang", "value2");

    XMP_Node* qualifierNode3 = AddQualifierNode(parent, "rdf:type", "value3");



    EXPECT_EQ(parent->qualifiers.size(), 3);

    EXPECT_TRUE((parent->options & kXMP_PropHasQualifiers) != 0);

    EXPECT_TRUE((parent->options & kXMP_PropHasLang) != 0);

    EXPECT_TRUE((parent->options & kXMP_PropHasType) != 0);



    // Verify order

    EXPECT_EQ(parent->qualifiers[0], qualifierNode2); // xml:lang should be first

    EXPECT_EQ(parent->qualifiers[1], qualifierNode3); // rdf:type should be second

    EXPECT_EQ(parent->qualifiers[2], qualifierNode1); // other qualifiers follow

}



TEST_F(AddQualifierNodeTest_2121, AddExistingLangQualifier_2121) {

    name = "xml:lang";

    XMP_Node* qualifierNode1 = AddQualifierNode(parent, name, "value1");

    XMP_Node* qualifierNode2 = AddQualifierNode(parent, name, "value2");



    EXPECT_EQ(parent->qualifiers.size(), 1);

    EXPECT_TRUE((parent->options & kXMP_PropHasLang) != 0);

    EXPECT_TRUE((parent->options & kXMP_PropHasQualifiers) != 0);



    // Verify that the first lang qualifier is replaced

    EXPECT_EQ(parent->qualifiers[0]->value, "value2");

}



TEST_F(AddQualifierNodeTest_2121, AddExistingTypeQualifier_2121) {

    name = "rdf:type";

    XMP_Node* qualifierNode1 = AddQualifierNode(parent, name, "value1");

    XMP_Node* qualifierNode2 = AddQualifierNode(parent, name, "value2");



    EXPECT_EQ(parent->qualifiers.size(), 2);

    EXPECT_TRUE((parent->options & kXMP_PropHasType) != 0);

    EXPECT_TRUE((parent->options & kXMP_PropHasQualifiers) != 0);



    // Verify that the type qualifier is inserted after any lang qualifiers

    if (XMP_PropHasLang(parent->options)) {

        EXPECT_EQ(parent->qualifiers[1], qualifierNode2);

    } else {

        EXPECT_EQ(parent->qualifiers[0], qualifierNode2);

    }

}
