#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_53 : public ::testing::Test {

protected:

    XMLDocument* doc;

    XMLNode* node;



    void SetUp() override {

        doc = new XMLDocument();

        node = new XMLElement("root");

        doc->LinkEndChild(node);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLNodeTest_53, FirstChildElement_ReturnsNullForEmptyChildren_53) {

    EXPECT_EQ(nullptr, node->FirstChildElement());

}



TEST_F(XMLNodeTest_53, FirstChildElement_ReturnsCorrectElement_53) {

    XMLElement* child = new XMLElement("child");

    node->InsertEndChild(child);

    EXPECT_EQ(child, node->FirstChildElement());

}



TEST_F(XMLNodeTest_53, FirstChildElement_WithSpecificName_ReturnsNullIfNotFound_53) {

    EXPECT_EQ(nullptr, node->FirstChildElement("nonexistent"));

}



TEST_F(XMLNodeTest_53, FirstChildElement_WithSpecificName_ReturnsCorrectElement_53) {

    XMLElement* child = new XMLElement("child");

    node->InsertEndChild(child);

    EXPECT_EQ(child, node->FirstChildElement("child"));

}



TEST_F(XMLNodeTest_53, ChildElementCount_ReturnsZeroForEmptyChildren_53) {

    EXPECT_EQ(0, node->ChildElementCount());

}



TEST_F(XMLNodeTest_53, ChildElementCount_ReturnsCorrectCount_53) {

    XMLElement* child1 = new XMLElement("child");

    XMLElement* child2 = new XMLElement("child");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    EXPECT_EQ(2, node->ChildElementCount());

}



TEST_F(XMLNodeTest_53, ChildElementCount_WithSpecificName_ReturnsZeroIfNotFound_53) {

    EXPECT_EQ(0, node->ChildElementCount("nonexistent"));

}



TEST_F(XMLNodeTest_53, ChildElementCount_WithSpecificName_ReturnsCorrectCount_53) {

    XMLElement* child1 = new XMLElement("child");

    XMLElement* child2 = new XMLElement("other");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    EXPECT_EQ(1, node->ChildElementCount("child"));

}



TEST_F(XMLNodeTest_53, InsertEndChild_AddsChildToTheEnd_53) {

    XMLElement* child = new XMLElement("child");

    node->InsertEndChild(child);

    EXPECT_EQ(child, node->FirstChildElement());

}



TEST_F(XMLNodeTest_53, DeleteChildren_RemovesAllChildren_53) {

    XMLElement* child1 = new XMLElement("child1");

    XMLElement* child2 = new XMLElement("child2");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChildren();

    EXPECT_EQ(nullptr, node->FirstChildElement());

}



TEST_F(XMLNodeTest_53, DeleteChild_RemovesSpecificChild_53) {

    XMLElement* child1 = new XMLElement("child1");

    XMLElement* child2 = new XMLElement("child2");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChild(child1);

    EXPECT_EQ(child2, node->FirstChildElement());

}



TEST_F(XMLNodeTest_53, Value_ReturnsCorrectValue_53) {

    node->SetValue("test_value");

    EXPECT_STREQ("test_value", node->Value());

}
