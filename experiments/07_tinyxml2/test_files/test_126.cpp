#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_126 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* root;

    XMLHandle handle;



    void SetUp() override {

        root = doc.NewElement("Root");

        doc.InsertFirstChild(root);

        handle = XMLHandle(root);

    }

};



TEST_F(XMLHandleTest_126, NextSibling_ReturnsValidHandleForSibling_126) {

    XMLElement* sibling = doc.NewElement("Sibling");

    root->InsertEndChild(sibling);



    XMLHandle nextSiblingHandle = handle.NextSibling();

    EXPECT_EQ(nextSiblingHandle.ToNode(), sibling);

}



TEST_F(XMLHandleTest_126, NextSibling_ReturnsNullHandleForNoSibling_126) {

    XMLHandle nextSiblingHandle = handle.NextSibling();

    EXPECT_EQ(nextSiblingHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_126, NextSibling_BoundaryConditionWithOneElement_126) {

    XMLHandle nextSiblingHandle = handle.NextSibling();

    EXPECT_EQ(nextSiblingHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_126, NextSibling_ExceptionalCaseWithNullNode_126) {

    XMLHandle nullHandle;

    XMLHandle nextSiblingHandle = nullHandle.NextSibling();

    EXPECT_EQ(nextSiblingHandle.ToNode(), nullptr);

}
