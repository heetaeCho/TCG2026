#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



using namespace testing;



class CompareSubtreesTest_1902 : public ::testing::Test {

protected:

    XMP_Node* createNode(XMP_StringPtr name, XMP_StringPtr value = nullptr, XMP_OptionBits options = 0) {

        return new XMP_Node(nullptr, name, value, options);

    }



    void addQualifier(XMP_Node* node, XMP_StringPtr qualName, XMP_StringPtr qualValue = nullptr) {

        XMP_Node* qualifier = createNode(qualName, qualValue);

        node->qualifiers.push_back(qualifier);

    }



    void addChild(XMP_Node* parent, XMP_Node* child) {

        child->parent = parent;

        parent->children.push_back(child);

    }



    ~CompareSubtreesTest_1902() override {

        // Clean up nodes

    }

};



TEST_F(CompareSubtreesTest_1902, IdenticalNodes_1902) {

    XMP_Node* node1 = createNode("test", "value");

    XMP_Node* node2 = createNode("test", "value");



    EXPECT_TRUE(CompareSubtrees(*node1, *node2));



    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, DifferentValues_1902) {

    XMP_Node* node1 = createNode("test", "value1");

    XMP_Node* node2 = createNode("test", "value2");



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, DifferentOptions_1902) {

    XMP_Node* node1 = createNode("test", "value", kXMP_PropValueIsURI);

    XMP_Node* node2 = createNode("test", "value");



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, DifferentNumberOfChildren_1902) {

    XMP_Node* node1 = createNode("test", "value");

    XMP_Node* node2 = createNode("test", "value");



    addChild(node1, createNode("child"));

    

    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1->children[0];

    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, DifferentChildrenContent_1902) {

    XMP_Node* node1 = createNode("test", "value");

    XMP_Node* node2 = createNode("test", "value");



    addChild(node1, createNode("child1"));

    addChild(node2, createNode("child2"));



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1->children[0];

    delete node2->children[0];

    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, DifferentNumberOfQualifiers_1902) {

    XMP_Node* node1 = createNode("test", "value");

    XMP_Node* node2 = createNode("test", "value");



    addQualifier(node1, "qualifier");



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1->qualifiers[0];

    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, DifferentQualifiersContent_1902) {

    XMP_Node* node1 = createNode("test", "value");

    XMP_Node* node2 = createNode("test", "value");



    addQualifier(node1, "qualifier1");

    addQualifier(node2, "qualifier2");



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1->qualifiers[0];

    delete node2->qualifiers[0];

    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, NestedIdenticalNodes_1902) {

    XMP_Node* node1 = createNode("test", "value");

    XMP_Node* node2 = createNode("test", "value");



    addChild(node1, createNode("child"));

    addChild(node2, createNode("child"));



    EXPECT_TRUE(CompareSubtrees(*node1, *node2));



    delete node1->children[0];

    delete node2->children[0];

    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, NestedDifferentNodes_1902) {

    XMP_Node* node1 = createNode("test", "value");

    XMP_Node* node2 = createNode("test", "value");



    addChild(node1, createNode("child1"));

    addChild(node2, createNode("child2"));



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1->children[0];

    delete node2->children[0];

    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, SchemaNodeDifferentChildrenOrder_1902) {

    XMP_Node* node1 = createNode("test", "value", kXMP_SchemaNode);

    XMP_Node* node2 = createNode("test", "value", kXMP_SchemaNode);



    addChild(node1, createNode("child1"));

    addChild(node1, createNode("child2"));



    addChild(node2, createNode("child2"));

    addChild(node2, createNode("child1"));



    EXPECT_TRUE(CompareSubtrees(*node1, *node2));



    for (auto child : node1->children) delete child;

    for (auto child : node2->children) delete child;



    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, AltTextDifferentChildrenOrder_1902) {

    XMP_Node* node1 = createNode("test", "value", kXMP_PropArrayIsAltText);

    XMP_Node* node2 = createNode("test", "value", kXMP_PropArrayIsAltText);



    XMP_Node* child1_1 = createNode("child1");

    XMP_Node* child1_2 = createNode("child2");



    addQualifier(child1_1, "xml:lang", "en");

    addQualifier(child1_2, "xml:lang", "fr");



    addChild(node1, child1_1);

    addChild(node1, child1_2);



    XMP_Node* child2_1 = createNode("child2");

    XMP_Node* child2_2 = createNode("child1");



    addQualifier(child2_1, "xml:lang", "fr");

    addQualifier(child2_2, "xml:lang", "en");



    addChild(node2, child2_1);

    addChild(node2, child2_2);



    EXPECT_TRUE(CompareSubtrees(*node1, *node2));



    for (auto child : node1->children) delete child;

    for (auto child : node2->children) delete child;



    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, AltTextMissingLanguageQualifier_1902) {

    XMP_Node* node1 = createNode("test", "value", kXMP_PropArrayIsAltText);

    XMP_Node* node2 = createNode("test", "value", kXMP_PropArrayIsAltText);



    XMP_Node* child1_1 = createNode("child1");

    addQualifier(child1_1, "xml:lang", "en");



    addChild(node1, child1_1);

    addChild(node2, createNode("child2"));



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1->children[0];

    delete node2->children[0];



    delete node1;

    delete node2;

}



TEST_F(CompareSubtreesTest_1902, AltTextMismatchedLanguages_1902) {

    XMP_Node* node1 = createNode("test", "value", kXMP_PropArrayIsAltText);

    XMP_Node* node2 = createNode("test", "value", kXMP_PropArrayIsAltText);



    XMP_Node* child1_1 = createNode("child1");

    addQualifier(child1_1, "xml:lang", "en");



    XMP_Node* child2_1 = createNode("child1");

    addQualifier(child2_1, "xml:lang", "fr");



    addChild(node1, child1_1);

    addChild(node2, child2_1);



    EXPECT_FALSE(CompareSubtrees(*node1, *node2));



    delete node1->children[0];

    delete node2->children[0];



    delete node1;

    delete node2;

}
