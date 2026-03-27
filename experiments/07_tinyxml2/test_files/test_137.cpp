#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement = nullptr;

    XMLElement* childElement1 = nullptr;

    XMLElement* childElement2 = nullptr;

    XMLConstHandle handle;



    void SetUp() override {

        rootElement = doc.NewElement("Root");

        childElement1 = doc.NewElement("Child1");

        childElement2 = doc.NewElement("Child2");



        rootElement->InsertEndChild(childElement1);

        rootElement->InsertEndChild(childElement2);



        handle = XMLConstHandle(rootElement);

    }

};



TEST_F(XMLConstHandleTest_137, LastChildElement_ReturnsLastElementWithGivenName_137) {

    const XMLConstHandle lastChild = handle.LastChildElement("Child2");

    EXPECT_EQ(lastChild.ToNode(), childElement2);

}



TEST_F(XMLConstHandleTest_137, LastChildElement_ReturnsNullIfNoMatchingElementFound_137) {

    const XMLConstHandle lastChild = handle.LastChildElement("NonExistent");

    EXPECT_TRUE(lastChild.ToNode() == nullptr);

}



TEST_F(XMLConstHandleTest_137, LastChildElement_ReturnsLastElementWhenNameIsNull_137) {

    const XMLConstHandle lastChild = handle.LastChildElement();

    EXPECT_EQ(lastChild.ToNode(), childElement2);

}



TEST_F(XMLConstHandleTest_137, LastChildElement_ReturnsNullForEmptyDocument_137) {

    XMLConstHandle emptyHandle;

    const XMLConstHandle lastChild = emptyHandle.LastChildElement("Child1");

    EXPECT_TRUE(lastChild.ToNode() == nullptr);

}
