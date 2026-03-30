#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_183 : public ::testing::Test {

protected:

    virtual void SetUp() {

        xmlDocument = new XMLDocument();

        xmlNode = new XMLNode(xmlDocument);

    }



    virtual void TearDown() {

        delete xmlNode;

        delete xmlDocument;

    }



    XMLDocument* xmlDocument;

    XMLNode* xmlNode;

};



TEST_F(XMLNodeTest_183, ChildElementCount_ZeroChildren_183) {

    EXPECT_EQ(xmlNode->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_183, ChildElementCount_OneChild_183) {

    XMLElement* child = xmlDocument->NewElement("child");

    xmlNode->InsertEndChild(child);

    EXPECT_EQ(xmlNode->ChildElementCount(), 1);

}



TEST_F(XMLNodeTest_183, ChildElementCount_MultipleChildren_183) {

    XMLElement* child1 = xmlDocument->NewElement("child1");

    XMLElement* child2 = xmlDocument->NewElement("child2");

    XMLElement* child3 = xmlDocument->NewElement("child3");

    xmlNode->InsertEndChild(child1);

    xmlNode->InsertEndChild(child2);

    xmlNode->InsertEndChild(child3);

    EXPECT_EQ(xmlNode->ChildElementCount(), 3);

}



TEST_F(XMLNodeTest_183, ChildElementCount_AfterDeleteChildren_183) {

    XMLElement* child = xmlDocument->NewElement("child");

    xmlNode->InsertEndChild(child);

    xmlNode->DeleteChildren();

    EXPECT_EQ(xmlNode->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_183, ChildElementCount_AfterDeleteSpecificChild_183) {

    XMLElement* child = xmlDocument->NewElement("child");

    xmlNode->InsertEndChild(child);

    xmlNode->DeleteChild(child);

    EXPECT_EQ(xmlNode->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_183, ChildElementCount_WithFilteredValue_183) {

    XMLElement* child = xmlDocument->NewElement("child");

    child->SetValue("specificValue");

    xmlNode->InsertEndChild(child);

    EXPECT_EQ(xmlNode->ChildElementCount("specificValue"), 1);

}



TEST_F(XMLNodeTest_183, ChildElementCount_WithNonMatchingFilteredValue_183) {

    XMLElement* child = xmlDocument->NewElement("child");

    child->SetValue("specificValue");

    xmlNode->InsertEndChild(child);

    EXPECT_EQ(xmlNode->ChildElementCount("nonMatchingValue"), 0);

}
