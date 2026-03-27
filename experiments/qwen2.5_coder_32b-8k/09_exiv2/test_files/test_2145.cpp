#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



using namespace std;



// Test Fixture for XMP_Node and SortWithinOffspring function.

class SortWithinOffspringTest_2145 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or state before each test

        root = new XMP_Node(nullptr, "Root", 0);

    }



    void TearDown() override {

        // Clean up after each test (delete allocated memory)

        delete root;

    }



    XMP_Node* root;

};



// Test normal operation with a simple structure.

TEST_F(SortWithinOffspringTest_2145, SortSimpleStructure_2145) {

    XMP_Node* child1 = new XMP_Node(root, "ChildB", 0);

    XMP_Node* child2 = new XMP_Node(root, "ChildA", 0);



    root->children.push_back(child1);

    root->children.push_back(child2);



    SortWithinOffspring(root->children);



    EXPECT_EQ(root->children[0]->name, "ChildA");

    EXPECT_EQ(root->children[1]->name, "ChildB");



    delete child1;

    delete child2;

}



// Test boundary condition with an empty node vector.

TEST_F(SortWithinOffspringTest_2145, SortEmptyVector_2145) {

    XMP_NodeOffspring nodeVec;

    SortWithinOffspring(nodeVec);

    EXPECT_TRUE(nodeVec.empty());

}



// Test normal operation with a nested structure.

TEST_F(SortWithinOffspringTest_2145, SortNestedStructure_2145) {

    XMP_Node* child1 = new XMP_Node(root, "ChildB", 0);

    XMP_Node* child2 = new XMP_Node(root, "ChildA", 0);



    root->children.push_back(child1);

    root->children.push_back(child2);



    XMP_Node* grandchild1 = new XMP_Node(child1, "GrandChildZ", 0);

    XMP_Node* grandchild2 = new XMP_Node(child1, "GrandChildY", 0);



    child1->children.push_back(grandchild1);

    child1->children.push_back(grandchild2);



    SortWithinOffspring(root->children);



    EXPECT_EQ(root->children[0]->name, "ChildA");

    EXPECT_EQ(root->children[1]->name, "ChildB");



    EXPECT_EQ(child1->children[0]->name, "GrandChildY");

    EXPECT_EQ(child1->children[1]->name, "GrandChildZ");



    delete child1;

    delete child2;

    delete grandchild1;

    delete grandchild2;

}



// Test sorting of unordered array.

TEST_F(SortWithinOffspringTest_2145, SortUnorderedArray_2145) {

    XMP_Node* arrayNode = new XMP_Node(root, "Array", kXMP_PropValueIsArray | kXMP_PropArrayIsUnordered);

    root->children.push_back(arrayNode);



    XMP_Node* item3 = new XMP_Node(arrayNode, "ItemC", "ValueC", 0);

    XMP_Node* item1 = new XMP_Node(arrayNode, "ItemA", "ValueA", 0);

    XMP_Node* item2 = new XMP_Node(arrayNode, "ItemB", "ValueB", 0);



    arrayNode->children.push_back(item3);

    arrayNode->children.push_back(item1);

    arrayNode->children.push_back(item2);



    SortWithinOffspring(root->children);



    // Unordered arrays should maintain stable order relative to their original position.

    EXPECT_EQ(arrayNode->children[0]->name, "ItemC");

    EXPECT_EQ(arrayNode->children[1]->name, "ItemA");

    EXPECT_EQ(arrayNode->children[2]->name, "ItemB");



    delete arrayNode;

    delete item1;

    delete item2;

    delete item3;

}



// Test sorting of alt-text array.

TEST_F(SortWithinOffspringTest_2145, SortAltTextArray_2145) {

    XMP_Node* arrayNode = new XMP_Node(root, "AltText", kXMP_PropValueIsArray | kXMP_PropArrayIsAltText);

    root->children.push_back(arrayNode);



    XMP_Node* item3 = new XMP_Node(arrayNode, "ItemC", "ValueC", kXMP_PropHasLang);

    item3->qualifiers.emplace_back(new XMP_Node(item3, "xml:lang", "en-US", 0));



    XMP_Node* item1 = new XMP_Node(arrayNode, "ItemA", "ValueA", kXMP_PropHasLang);

    item1->qualifiers.emplace_back(new XMP_Node(item1, "xml:lang", "de-DE", 0));



    XMP_Node* item2 = new XMP_Node(arrayNode, "ItemB", "ValueB", kXMP_PropHasLang);

    item2->qualifiers.emplace_back(new XMP_Node(item2, "xml:lang", "fr-FR", 0));



    arrayNode->children.push_back(item3);

    arrayNode->children.push_back(item1);

    arrayNode->children.push_back(item2);



    SortWithinOffspring(root->children);



    // alt-text arrays should be sorted by the language.

    EXPECT_EQ(arrayNode->children[0]->qualifiers[0]->value, "de-DE");

    EXPECT_EQ(arrayNode->children[1]->qualifiers[0]->value, "en-US");

    EXPECT_EQ(arrayNode->children[2]->qualifiers[0]->value, "fr-FR");



    for (auto* qualifier : item3->qualifiers) delete qualifier;

    for (auto* qualifier : item1->qualifiers) delete qualifier;

    for (auto* qualifier : item2->qualifiers) delete qualifier;



    delete arrayNode;

    delete item1;

    delete item2;

    delete item3;

}



// Test sorting of structured nodes.

TEST_F(SortWithinOffspringTest_2145, SortStructuredNodes_2145) {

    XMP_Node* structNode = new XMP_Node(root, "Struct", kXMP_PropValueIsStruct);

    root->children.push_back(structNode);



    XMP_Node* child3 = new XMP_Node(structNode, "ChildC", 0);

    XMP_Node* child1 = new XMP_Node(structNode, "ChildA", 0);

    XMP_Node* child2 = new XMP_Node(structNode, "ChildB", 0);



    structNode->children.push_back(child3);

    structNode->children.push_back(child1);

    structNode->children.push_back(child2);



    SortWithinOffspring(root->children);



    EXPECT_EQ(structNode->children[0]->name, "ChildA");

    EXPECT_EQ(structNode->children[1]->name, "ChildB");

    EXPECT_EQ(structNode->children[2]->name, "ChildC");



    delete structNode;

    delete child1;

    delete child2;

    delete child3;

}
