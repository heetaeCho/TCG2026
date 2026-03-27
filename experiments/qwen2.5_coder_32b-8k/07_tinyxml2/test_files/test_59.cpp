#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* node;



    void SetUp() override {

        node = new XMLNode(&doc);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLNodeTest_59, NextSiblingElement_ReturnsNullptrWhenNoSiblings_59) {

    EXPECT_EQ(node->NextSiblingElement(), nullptr);

}



TEST_F(XMLNodeTest_59, NextSiblingElement_ReturnsCorrectSiblingWithMatchingName_59) {

    XMLElement* sibling = doc.NewElement("sibling");

    node->_next = sibling;

    EXPECT_EQ(node->NextSiblingElement("sibling"), sibling);

}



TEST_F(XMLNodeTest_59, NextSiblingElement_ReturnsNullptrWhenNoMatchingName_59) {

    XMLElement* sibling = doc.NewElement("other_sibling");

    node->_next = sibling;

    EXPECT_EQ(node->NextSiblingElement("sibling"), nullptr);

}
