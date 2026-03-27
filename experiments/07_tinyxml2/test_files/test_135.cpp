#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_135 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* root;

    XMLElement* child1;

    XMLElement* child2;



    void SetUp() override {

        root = doc.NewElement("Root");

        child1 = doc.NewElement("Child1");

        child2 = doc.NewElement("Child2");



        root->InsertEndChild(child1);

        root->InsertEndChild(child2);



        doc.InsertFirstChild(root);

    }

};



TEST_F(XMLConstHandleTest_135, FirstChildElement_ReturnsCorrectElement_135) {

    XMLConstHandle handle(root);

    XMLConstHandle child = handle.FirstChildElement("Child1");

    EXPECT_EQ(child.ToNode(), child1);

}



TEST_F(XMLConstHandleTest_135, FirstChildElement_ReturnsNullForNonExistingElement_135) {

    XMLConstHandle handle(root);

    XMLConstHandle child = handle.FirstChildElement("NonExistent");

    EXPECT_EQ(child.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_135, FirstChildElement_ReturnsFirstElementWithMatchingName_135) {

    XMLElement* anotherChild1 = doc.NewElement("Child1");

    root->InsertEndChild(anotherChild1);



    XMLConstHandle handle(root);

    XMLConstHandle child = handle.FirstChildElement("Child1");

    EXPECT_EQ(child.ToNode(), child1);  // Should return the first matching element

}



TEST_F(XMLConstHandleTest_135, FirstChildElement_DefaultReturnsFirstElement_135) {

    XMLConstHandle handle(root);

    XMLConstHandle child = handle.FirstChildElement();

    EXPECT_EQ(child.ToNode(), child1);  // Default should return the first child element

}



TEST_F(XMLConstHandleTest_135, LastChildElement_ReturnsCorrectElement_135) {

    XMLConstHandle handle(root);

    XMLConstHandle child = handle.LastChildElement("Child2");

    EXPECT_EQ(child.ToNode(), child2);

}



TEST_F(XMLConstHandleTest_135, LastChildElement_ReturnsNullForNonExistingElement_135) {

    XMLConstHandle handle(root);

    XMLConstHandle child = handle.LastChildElement("NonExistent");

    EXPECT_EQ(child.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_135, LastChildElement_DefaultReturnsLastElement_135) {

    XMLConstHandle handle(root);

    XMLConstHandle child = handle.LastChildElement();

    EXPECT_EQ(child.ToNode(), child2);  // Default should return the last child element

}
