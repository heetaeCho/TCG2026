#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_136 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement;

    XMLNode* childNode;

    XMLConstHandle handle;



    void SetUp() override {

        rootElement = doc.NewElement("Root");

        childNode = doc.NewElement("Child");

        rootElement->InsertEndChild(childNode);

        doc.InsertFirstChild(rootElement);

        handle = XMLConstHandle(rootElement);

    }

};



TEST_F(XMLConstHandleTest_136, LastChild_ReturnsValidHandle_136) {

    const XMLConstHandle lastChildHandle = handle.LastChild();

    EXPECT_NE(lastChildHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_136, LastChild_NoChildren_ReturnsInvalidHandle_136) {

    XMLConstHandle emptyHandle;

    const XMLConstHandle lastChildHandle = emptyHandle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_136, LastChildElement_MatchingName_ReturnsValidHandle_136) {

    const XMLConstHandle lastChildElementHandle = handle.LastChildElement("Child");

    EXPECT_NE(lastChildElementHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_136, LastChildElement_NoMatchingName_ReturnsInvalidHandle_136) {

    const XMLConstHandle lastChildElementHandle = handle.LastChildElement("NonExistent");

    EXPECT_EQ(lastChildElementHandle.ToNode(), nullptr);

}
