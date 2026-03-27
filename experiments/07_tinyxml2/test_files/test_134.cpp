#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* root;

    XMLConstHandle handle;



    void SetUp() override {

        root = doc.NewElement("root");

        doc.InsertEndChild(root);

        handle = XMLConstHandle(root);

    }

};



TEST_F(XMLConstHandleTest_134, FirstChild_ReturnsValidHandle_134) {

    XMLElement* child = doc.NewElement("child");

    root->InsertEndChild(child);

    XMLConstHandle childHandle = handle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), child);

}



TEST_F(XMLConstHandleTest_134, FirstChild_ReturnsNullForNoChildren_134) {

    XMLConstHandle childHandle = handle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_134, FirstChildElement_ReturnsValidHandleWithMatchingName_134) {

    XMLElement* child = doc.NewElement("child");

    root->InsertEndChild(child);

    XMLConstHandle childHandle = handle.FirstChildElement("child");

    EXPECT_EQ(childHandle.ToNode(), child);

}



TEST_F(XMLConstHandleTest_134, FirstChildElement_ReturnsNullForNoMatchingName_134) {

    XMLElement* child = doc.NewElement("child");

    root->InsertEndChild(child);

    XMLConstHandle childHandle = handle.FirstChildElement("nonexistent");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_134, FirstChildElement_ReturnsNullForNoChildren_134) {

    XMLConstHandle childHandle = handle.FirstChildElement();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}
