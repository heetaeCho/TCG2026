#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_60 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* parent;



    void SetUp() override {

        parent = new XMLNode(&doc);

    }



    void TearDown() override {

        delete parent;

    }

};



TEST_F(XMLNodeTest_60, LinkEndChild_AddsChildToEnd_60) {

    XMLNode* child1 = new XMLNode(&doc);

    XMLNode* child2 = new XMLNode(&doc);



    parent->LinkEndChild(child1);

    parent->LinkEndChild(child2);



    EXPECT_EQ(parent->FirstChild(), child1);

    EXPECT_EQ(parent->LastChild(), child2);

}



TEST_F(XMLNodeTest_60, LinkEndChild_ReturnsAddedChild_60) {

    XMLNode* child = new XMLNode(&doc);

    EXPECT_EQ(parent->LinkEndChild(child), child);

}



TEST_F(XMLNodeTest_60, LinkEndChild_ChildPointsToParent_60) {

    XMLNode* child = new XMLNode(&doc);

    parent->LinkEndChild(child);



    EXPECT_EQ(child->Parent(), parent);

}



TEST_F(XMLNodeTest_60, ChildElementCount_ZeroInitially_60) {

    EXPECT_EQ(parent->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_60, ChildElementCount_IncreasesWithChildren_60) {

    XMLNode* child1 = new XMLNode(&doc);

    XMLNode* child2 = new XMLNode(&doc);



    parent->LinkEndChild(child1);

    EXPECT_EQ(parent->ChildElementCount(), 1);



    parent->LinkEndChild(child2);

    EXPECT_EQ(parent->ChildElementCount(), 2);

}



TEST_F(XMLNodeTest_60, ChildElementCountWithSpecificValue_60) {

    XMLNode* child1 = new XMLElement(&doc);

    XMLNode* child2 = new XMLElement(&doc);



    child1->SetValue("test");

    parent->LinkEndChild(child1);

    EXPECT_EQ(parent->ChildElementCount("test"), 1);



    parent->LinkEndChild(child2);

    EXPECT_EQ(parent->ChildElementCount("test"), 1);

}



TEST_F(XMLNodeTest_60, LinkEndChild_DoesNotDeleteChildren_60) {

    XMLNode* child = new XMLNode(&doc);

    parent->LinkEndChild(child);



    delete parent;

    // If the test framework does not crash here, it means children are not deleted by parent.

}



TEST_F(XMLNodeTest_60, LinkEndChild_NullChild_ReturnsNull_60) {

    EXPECT_EQ(parent->LinkEndChild(nullptr), nullptr);

}
