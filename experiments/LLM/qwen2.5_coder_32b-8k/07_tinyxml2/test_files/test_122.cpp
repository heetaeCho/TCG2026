#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_122 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* root;

    XMLHandle handle;



    void SetUp() override {

        root = doc.NewElement("Root");

        doc.InsertFirstChild(root);

        handle = XMLHandle(root);

    }

};



TEST_F(XMLHandleTest_122, LastChild_ReturnsValidXMLHandle_122) {

    XMLElement* child = doc.NewElement("Child");

    root->InsertEndChild(child);



    XMLHandle lastChildHandle = handle.LastChild();

    EXPECT_NE(lastChildHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_122, LastChild_ReturnsEmptyXMLHandleWhenNoChildren_122) {

    XMLHandle lastChildHandle = handle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_122, LastChild_BoundaryConditionWithSingleChild_122) {

    XMLElement* child = doc.NewElement("Child");

    root->InsertEndChild(child);



    XMLHandle lastChildHandle = handle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), child);

}



TEST_F(XMLHandleTest_122, LastChild_BoundaryConditionWithMultipleChildren_122) {

    XMLElement* child1 = doc.NewElement("Child1");

    XMLElement* child2 = doc.NewElement("Child2");

    root->InsertEndChild(child1);

    root->InsertEndChild(child2);



    XMLHandle lastChildHandle = handle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), child2);

}
