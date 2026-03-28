#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_140 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup a simple XML structure for testing

        doc = new XMLDocument();

        root = doc->NewElement("Root");

        child1 = doc->NewElement("Child1");

        child2 = doc->NewElement("Child2");

        root->InsertEndChild(child1);

        root->InsertEndChild(child2);

        doc->InsertFirstChild(root);



        handleRoot = XMLConstHandle(doc->RootElement());

        handleChild1 = XMLConstHandle(child1);

        handleChild2 = XMLConstHandle(child2);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

    XMLElement* root;

    XMLElement* child1;

    XMLElement* child2;

    XMLConstHandle handleRoot;

    XMLConstHandle handleChild1;

    XMLConstHandle handleChild2;

};



TEST_F(XMLConstHandleTest_140, NextSibling_ReturnsNextSibling_140) {

    EXPECT_EQ(handleChild1.NextSibling().ToNode(), child2);

}



TEST_F(XMLConstHandleTest_140, NextSibling_EndOfSiblings_ReturnsNull_140) {

    EXPECT_EQ(handleChild2.NextSibling().ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_140, NextSibling_EmptyDocument_ReturnsNull_140) {

    XMLDocument emptyDoc;

    XMLConstHandle handleEmpty(&emptyDoc);

    EXPECT_EQ(handleEmpty.NextSibling().ToNode(), nullptr);

}
