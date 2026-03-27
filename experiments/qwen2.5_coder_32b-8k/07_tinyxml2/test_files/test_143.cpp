#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_143 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement = nullptr;

    XMLConstHandle handle;



    void SetUp() override {

        rootElement = doc.NewElement("Root");

        doc.InsertFirstChild(rootElement);

        handle = XMLConstHandle(rootElement);

    }



    void TearDown() override {

        delete rootElement;

    }

};



TEST_F(XMLConstHandleTest_143, ToNode_ReturnsCorrectPointer_143) {

    EXPECT_EQ(handle.ToNode(), rootElement);

}



TEST_F(XMLConstHandleTest_143, ToElement_ReturnsCorrectPointer_143) {

    EXPECT_EQ(handle.ToElement(), rootElement);

}



TEST_F(XMLConstHandleTest_143, FirstChild_ReturnsEmptyHandleWhenNoChildren_143) {

    XMLConstHandle firstChildHandle = handle.FirstChild();

    EXPECT_EQ(firstChildHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, FirstChildElement_ReturnsEmptyHandleWhenNoMatchingElements_143) {

    XMLConstHandle firstChildHandle = handle.FirstChildElement("NonExistent");

    EXPECT_EQ(firstChildHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, LastChild_ReturnsEmptyHandleWhenNoChildren_143) {

    XMLConstHandle lastChildHandle = handle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, LastChildElement_ReturnsEmptyHandleWhenNoMatchingElements_143) {

    XMLConstHandle lastChildHandle = handle.LastChildElement("NonExistent");

    EXPECT_EQ(lastChildHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, PreviousSibling_ReturnsEmptyHandleForRoot_143) {

    XMLConstHandle prevSiblingHandle = handle.PreviousSibling();

    EXPECT_EQ(prevSiblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, PreviousSiblingElement_ReturnsEmptyHandleForRoot_143) {

    XMLConstHandle prevSiblingHandle = handle.PreviousSiblingElement("NonExistent");

    EXPECT_EQ(prevSiblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, NextSibling_ReturnsEmptyHandleForRoot_143) {

    XMLConstHandle nextSiblingHandle = handle.NextSibling();

    EXPECT_EQ(nextSiblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, NextSiblingElement_ReturnsEmptyHandleForRoot_143) {

    XMLConstHandle nextSiblingHandle = handle.NextSiblingElement("NonExistent");

    EXPECT_EQ(nextSiblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_143, FirstChild_ReturnsCorrectHandleWhenChildrenExist_143) {

    XMLElement* childElement = doc.NewElement("Child");

    rootElement->InsertFirstChild(childElement);



    XMLConstHandle firstChildHandle = handle.FirstChild();

    EXPECT_EQ(firstChildHandle.ToNode(), childElement);

}



TEST_F(XMLConstHandleTest_143, FirstChildElement_ReturnsCorrectHandleWhenMatchingElementsExist_143) {

    XMLElement* childElement = doc.NewElement("Child");

    rootElement->InsertFirstChild(childElement);



    XMLConstHandle firstChildHandle = handle.FirstChildElement("Child");

    EXPECT_EQ(firstChildHandle.ToNode(), childElement);

}



TEST_F(XMLConstHandleTest_143, LastChild_ReturnsCorrectHandleWhenChildrenExist_143) {

    XMLElement* childElement = doc.NewElement("Child");

    rootElement->InsertFirstChild(childElement);



    XMLConstHandle lastChildHandle = handle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), childElement);

}



TEST_F(XMLConstHandleTest_143, LastChildElement_ReturnsCorrectHandleWhenMatchingElementsExist_143) {

    XMLElement* childElement = doc.NewElement("Child");

    rootElement->InsertFirstChild(childElement);



    XMLConstHandle lastChildHandle = handle.LastChildElement("Child");

    EXPECT_EQ(lastChildHandle.ToNode(), childElement);

}
