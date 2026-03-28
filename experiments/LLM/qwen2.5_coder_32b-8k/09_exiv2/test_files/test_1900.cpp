#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class CloneOffspringTest_1900 : public ::testing::Test {

protected:

    XMP_Node* origParent;

    XMP_Node* cloneParent;



    void SetUp() override {

        origParent = new XMP_Node(nullptr, "parent", 0);

        cloneParent = new XMP_Node(nullptr, "cloneParent", 0);

    }



    void TearDown() override {

        delete origParent;

        delete cloneParent;

    }

};



TEST_F(CloneOffspringTest_1900, NoChildrenNoQualifiers_1900) {

    CloneOffspring(origParent, cloneParent);

    EXPECT_EQ(cloneParent->children.size(), 0u);

    EXPECT_EQ(cloneParent->qualifiers.size(), 0u);

}



TEST_F(CloneOffspringTest_1900, SingleQualifier_1900) {

    XMP_Node* origQual = new XMP_Node(origParent, "qualifier", "value", 0);

    origParent->qualifiers.push_back(origQual);



    CloneOffspring(origParent, cloneParent);



    EXPECT_EQ(cloneParent->children.size(), 0u);

    EXPECT_EQ(cloneParent->qualifiers.size(), 1u);

    EXPECT_EQ(cloneParent->qualifiers[0]->name, "qualifier");

    EXPECT_EQ(cloneParent->qualifiers[0]->value, "value");



    delete origQual;

}



TEST_F(CloneOffspringTest_1900, MultipleQualifiers_1900) {

    XMP_Node* origQual1 = new XMP_Node(origParent, "qualifier1", "value1", 0);

    XMP_Node* origQual2 = new XMP_Node(origParent, "qualifier2", "value2", 0);

    origParent->qualifiers.push_back(origQual1);

    origParent->qualifiers.push_back(origQual2);



    CloneOffspring(origParent, cloneParent);



    EXPECT_EQ(cloneParent->children.size(), 0u);

    EXPECT_EQ(cloneParent->qualifiers.size(), 2u);

    EXPECT_EQ(cloneParent->qualifiers[0]->name, "qualifier1");

    EXPECT_EQ(cloneParent->qualifiers[0]->value, "value1");

    EXPECT_EQ(cloneParent->qualifiers[1]->name, "qualifier2");

    EXPECT_EQ(cloneParent->qualifiers[1]->value, "value2");



    delete origQual1;

    delete origQual2;

}



TEST_F(CloneOffspringTest_1900, SingleChild_1900) {

    XMP_Node* origChild = new XMP_Node(origParent, "child", "value", 0);

    origParent->children.push_back(origChild);



    CloneOffspring(origParent, cloneParent);



    EXPECT_EQ(cloneParent->qualifiers.size(), 0u);

    EXPECT_EQ(cloneParent->children.size(), 1u);

    EXPECT_EQ(cloneParent->children[0]->name, "child");

    EXPECT_EQ(cloneParent->children[0]->value, "value");



    delete origChild;

}



TEST_F(CloneOffspringTest_1900, MultipleChildren_1900) {

    XMP_Node* origChild1 = new XMP_Node(origParent, "child1", "value1", 0);

    XMP_Node* origChild2 = new XMP_Node(origParent, "child2", "value2", 0);

    origParent->children.push_back(origChild1);

    origParent->children.push_back(origChild2);



    CloneOffspring(origParent, cloneParent);



    EXPECT_EQ(cloneParent->qualifiers.size(), 0u);

    EXPECT_EQ(cloneParent->children.size(), 2u);

    EXPECT_EQ(cloneParent->children[0]->name, "child1");

    EXPECT_EQ(cloneParent->children[0]->value, "value1");

    EXPECT_EQ(cloneParent->children[1]->name, "child2");

    EXPECT_EQ(cloneParent->children[1]->value, "value2");



    delete origChild1;

    delete origChild2;

}



TEST_F(CloneOffspringTest_1900, NestedChildrenAndQualifiers_1900) {

    XMP_Node* origChild = new XMP_Node(origParent, "child", 0);

    origParent->children.push_back(origChild);



    XMP_Node* origQual = new XMP_Node(origChild, "qualifier", "value", 0);

    origChild->qualifiers.push_back(origQual);



    CloneOffspring(origParent, cloneParent);



    EXPECT_EQ(cloneParent->qualifiers.size(), 0u);

    EXPECT_EQ(cloneParent->children.size(), 1u);

    XMP_Node* cloneChild = cloneParent->children[0];

    EXPECT_EQ(cloneChild->name, "child");

    EXPECT_EQ(cloneChild->qualifiers.size(), 1u);



    XMP_Node* cloneQual = cloneChild->qualifiers[0];

    EXPECT_EQ(cloneQual->name, "qualifier");

    EXPECT_EQ(cloneQual->value, "value");



    delete origQual;

    delete origChild;

}
