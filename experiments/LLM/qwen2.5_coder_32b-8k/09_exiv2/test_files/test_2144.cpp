#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



// Assuming CompareNodeLangs is part of a class or namespace, we'll mock up necessary structures for testing.

class XMPMetaTest_2144 : public ::testing::Test {

protected:

    XMP_Node* CreateNodeWithLangQualifier(const std::string& langValue) {

        XMP_Node* node = new XMP_Node(nullptr, "test", 0);

        XMP_Node* qualifier = new XMP_Node(node, "xml:lang", langValue.c_str(), 0);

        node->qualifiers.push_back(qualifier);

        return node;

    }



    void TearDown() override {

        // Clean up any allocated nodes

        for (auto node : nodes) {

            node->RemoveQualifiers();

            delete node;

        }

    }



    std::vector<XMP_Node*> nodes;

};



TEST_F(XMPMetaTest_2144, CompareNodeLangs_SameLanguage_2144) {

    XMP_Node* left = CreateNodeWithLangQualifier("en");

    XMP_Node* right = CreateNodeWithLangQualifier("en");



    EXPECT_FALSE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}



TEST_F(XMPMetaTest_2144, CompareNodeLangs_DifferentLanguages_2144) {

    XMP_Node* left = CreateNodeWithLangQualifier("en");

    XMP_Node* right = CreateNodeWithLangQualifier("fr");



    EXPECT_TRUE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}



TEST_F(XMPMetaTest_2144, CompareNodeLangs_LeftXDefault_2144) {

    XMP_Node* left = CreateNodeWithLangQualifier("x-default");

    XMP_Node* right = CreateNodeWithLangQualifier("fr");



    EXPECT_TRUE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}



TEST_F(XMPMetaTest_2144, CompareNodeLangs_RightXDefault_2144) {

    XMP_Node* left = CreateNodeWithLangQualifier("en");

    XMP_Node* right = CreateNodeWithLangQualifier("x-default");



    EXPECT_FALSE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}



TEST_F(XMPMetaTest_2144, CompareNodeLangs_NoLeftQualifier_2144) {

    XMP_Node* left = new XMP_Node(nullptr, "test", 0);

    XMP_Node* right = CreateNodeWithLangQualifier("fr");



    EXPECT_FALSE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}



TEST_F(XMPMetaTest_2144, CompareNodeLangs_NoRightQualifier_2144) {

    XMP_Node* left = CreateNodeWithLangQualifier("en");

    XMP_Node* right = new XMP_Node(nullptr, "test", 0);



    EXPECT_FALSE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}



TEST_F(XMPMetaTest_2144, CompareNodeLangs_WrongLeftQualifierName_2144) {

    XMP_Node* left = new XMP_Node(nullptr, "test", 0);

    XMP_Node* qualifier = new XMP_Node(left, "other:lang", "en", 0);

    left->qualifiers.push_back(qualifier);



    XMP_Node* right = CreateNodeWithLangQualifier("fr");



    EXPECT_FALSE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}



TEST_F(XMPMetaTest_2144, CompareNodeLangs_WrongRightQualifierName_2144) {

    XMP_Node* left = CreateNodeWithLangQualifier("en");



    XMP_Node* right = new XMP_Node(nullptr, "test", 0);

    XMP_Node* qualifier = new XMP_Node(right, "other:lang", "fr", 0);

    right->qualifiers.push_back(qualifier);



    EXPECT_FALSE(CompareNodeLangs(left, right));



    nodes.push_back(left);

    nodes.push_back(right);

}
