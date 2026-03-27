#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_141 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* root;

    XMLElement* child1;

    XMLElement* child2;



    void SetUp() override {

        root = doc.NewElement("Root");

        child1 = doc.NewElement("Child");

        child2 = doc.NewElement("Child");



        root->InsertEndChild(child1);

        root->InsertEndChild(child2);



        doc.InsertFirstChild(root);

    }

};



TEST_F(XMLConstHandleTest_141, NextSiblingElement_NoName_141) {

    XMLConstHandle handle(child1);

    XMLConstHandle nextSibling = handle.NextSiblingElement();



    EXPECT_EQ(nextSibling.ToNode(), child2);

}



TEST_F(XMLConstHandleTest_141, NextSiblingElement_SpecificNameMatch_141) {

    XMLConstHandle handle(child1);

    XMLConstHandle nextSibling = handle.NextSiblingElement("Child");



    EXPECT_EQ(nextSibling.ToNode(), child2);

}



TEST_F(XMLConstHandleTest_141, NextSiblingElement_SpecificNameNoMatch_141) {

    XMLConstHandle handle(child1);

    XMLConstHandle nextSibling = handle.NextSiblingElement("NonExistent");



    EXPECT_EQ(nextSibling.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_141, NextSiblingElement_LastElement_141) {

    XMLConstHandle handle(child2);

    XMLConstHandle nextSibling = handle.NextSiblingElement();



    EXPECT_EQ(nextSibling.ToNode(), nullptr);

}
