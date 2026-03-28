#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_57 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* root;

    XMLElement* child1;

    XMLElement* child2;

    XMLElement* child3;



    void SetUp() override {

        root = doc.NewElement("Root");

        doc.InsertFirstChild(root);

        

        child1 = doc.NewElement("Child1");

        root->InsertEndChild(child1);

        

        child2 = doc.NewElement("Child2");

        root->InsertEndChild(child2);

        

        child3 = doc.NewElement("Child3");

        root->InsertEndChild(child3);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLNodeTest_57, PreviousSiblingElement_NoNameGiven_ReturnsPreviousSibling_57) {

    XMLElement* result = child2->PreviousSiblingElement();

    EXPECT_EQ(result, child1);

}



TEST_F(XMLNodeTest_57, PreviousSiblingElement_NameMatches_ReturnsPreviousSibling_57) {

    XMLElement* result = child3->PreviousSiblingElement("Child2");

    EXPECT_EQ(result, child2);

}



TEST_F(XMLNodeTest_57, PreviousSiblingElement_NameDoesNotMatch_ReturnsNull_57) {

    XMLElement* result = child3->PreviousSiblingElement("NonExistent");

    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLNodeTest_57, PreviousSiblingElement_FirstChild_ReturnsNull_57) {

    XMLElement* result = child1->PreviousSiblingElement();

    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLNodeTest_57, PreviousSiblingElement_NameMatchesMultiple_ReturnsClosestPreviousSibling_57) {

    XMLElement* child4 = doc.NewElement("Child2");

    root->InsertEndChild(child4);



    XMLElement* result = child4->PreviousSiblingElement("Child2");

    EXPECT_EQ(result, child2);

}



TEST_F(XMLNodeTest_57, PreviousSiblingElement_EmptyDocument_ReturnsNull_57) {

    XMLDocument emptyDoc;

    XMLElement* emptyRoot = emptyDoc.NewElement("EmptyRoot");

    emptyDoc.InsertFirstChild(emptyRoot);



    XMLElement* result = emptyRoot->PreviousSiblingElement();

    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLNodeTest_57, PreviousSiblingElement_NameMatchesCaseSensitive_ReturnsNull_57) {

    XMLElement* result = child2->PreviousSiblingElement("child1");

    EXPECT_EQ(result, nullptr);

}
