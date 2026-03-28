#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_55 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* root;

    

    void SetUp() override {

        root = new XMLElement(&doc);

        root->SetValue("Root");

    }



    void TearDown() override {

        delete root;

    }

};



TEST_F(XMLNodeTest_55, LastChildElement_ReturnsNullForEmptyNode_55) {

    EXPECT_EQ(root->LastChildElement(), nullptr);

}



TEST_F(XMLNodeTest_55, LastChildElement_ReturnsLastAddedElementWithName_55) {

    XMLElement* child1 = doc.NewElement("Child");

    root->InsertEndChild(child1);



    XMLElement* child2 = doc.NewElement("Child");

    root->InsertEndChild(child2);



    EXPECT_EQ(root->LastChildElement("Child"), child2);

}



TEST_F(XMLNodeTest_55, LastChildElement_ReturnsNullForNonExistentName_55) {

    XMLElement* child1 = doc.NewElement("Child");

    root->InsertEndChild(child1);



    EXPECT_EQ(root->LastChildElement("Nonexistent"), nullptr);

}



TEST_F(XMLNodeTest_55, LastChildElement_IgnoresElementsWithDifferentNames_55) {

    XMLElement* child1 = doc.NewElement("Child");

    root->InsertEndChild(child1);



    XMLElement* child2 = doc.NewElement("AnotherChild");

    root->InsertEndChild(child2);



    EXPECT_EQ(root->LastChildElement("Child"), child1);

}



TEST_F(XMLNodeTest_55, LastChildElement_ReturnsLastAddedElementWithSpecificName_55) {

    XMLElement* child1 = doc.NewElement("Child");

    root->InsertEndChild(child1);



    XMLElement* child2 = doc.NewElement("AnotherChild");

    root->InsertEndChild(child2);



    XMLElement* child3 = doc.NewElement("Child");

    root->InsertEndChild(child3);



    EXPECT_EQ(root->LastChildElement("Child"), child3);

}
