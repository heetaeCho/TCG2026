// File: ./TestProjects/tinyxml2/tests/xmlnode_nextsibling_test_58.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

using namespace tinyxml2;

class XMLNodeNextSiblingTest_58 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* MakeRoot(const char* name = "root") {
        XMLElement* root = doc.NewElement(name);
        doc.InsertEndChild(root);
        return root;
    }
};

TEST_F(XMLNodeNextSiblingTest_58, NoNextSiblingReturnsNullptr_58) {
    XMLElement* root = MakeRoot();

    XMLElement* only = doc.NewElement("only");
    root->InsertEndChild(only);

    const XMLNode* constOnly = only;
    EXPECT_EQ(constOnly->NextSibling(), nullptr);
}

TEST_F(XMLNodeNextSiblingTest_58, ReturnsImmediateNextSiblingElement_58) {
    XMLElement* root = MakeRoot();

    XMLElement* first = doc.NewElement("first");
    XMLElement* second = doc.NewElement("second");
    root->InsertEndChild(first);
    root->InsertEndChild(second);

    const XMLNode* constFirst = first;
    EXPECT_EQ(constFirst->NextSibling(), second);

    const XMLNode* constSecond = second;
    EXPECT_EQ(constSecond->NextSibling(), nullptr);
}

TEST_F(XMLNodeNextSiblingTest_58, MiddleSiblingPointsToFollowingSibling_58) {
    XMLElement* root = MakeRoot();

    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    EXPECT_EQ(a->NextSibling(), b);
    EXPECT_EQ(b->NextSibling(), c);
    EXPECT_EQ(c->NextSibling(), nullptr);
}

TEST_F(XMLNodeNextSiblingTest_58, NextSiblingDoesNotSkipDifferentNodeTypes_58) {
    XMLElement* root = MakeRoot();

    XMLElement* firstElem = doc.NewElement("first");
    XMLComment* comment = doc.NewComment("hi");
    XMLElement* secondElem = doc.NewElement("second");

    root->InsertEndChild(firstElem);
    root->InsertEndChild(comment);
    root->InsertEndChild(secondElem);

    // NextSibling() is defined on XMLNode and should return the immediate next node,
    // regardless of the node type.
    const XMLNode* constFirst = firstElem;
    EXPECT_EQ(constFirst->NextSibling(), comment);

    const XMLNode* constComment = comment;
    EXPECT_EQ(constComment->NextSibling(), secondElem);

    const XMLNode* constSecond = secondElem;
    EXPECT_EQ(constSecond->NextSibling(), nullptr);
}

}  // namespace
