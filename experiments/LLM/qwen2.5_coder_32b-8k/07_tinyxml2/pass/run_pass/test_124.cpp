#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_124 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* root;

    XMLElement* child1;

    XMLElement* child2;



    void SetUp() override {

        root = doc.NewElement("Root");

        doc.InsertFirstChild(root);



        child1 = doc.NewElement("Child1");

        root->InsertEndChild(child1);



        child2 = doc.NewElement("Child2");

        root->InsertEndChild(child2);

    }

};



TEST_F(XMLHandleTest_124, PreviousSibling_NormalOperation_124) {

    XMLHandle handle(child2);

    XMLNode* prevSibling = handle.PreviousSibling().ToNode();

    EXPECT_EQ(prevSibling, child1);

}



TEST_F(XMLHandleTest_124, PreviousSibling_BoundaryCondition_FirstChild_124) {

    XMLHandle handle(child1);

    XMLNode* prevSibling = handle.PreviousSibling().ToNode();

    EXPECT_EQ(prevSibling, nullptr);

}



TEST_F(XMLHandleTest_124, PreviousSibling_ExceptionalCase_NullNode_124) {

    XMLHandle handle(static_cast<XMLNode*>(nullptr));

    XMLNode* prevSibling = handle.PreviousSibling().ToNode();

    EXPECT_EQ(prevSibling, nullptr);

}
