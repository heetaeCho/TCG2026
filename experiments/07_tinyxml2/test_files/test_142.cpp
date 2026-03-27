#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_142 : public ::testing::Test {

protected:

    const XMLNode* mockNode = nullptr;

    XMLConstHandle handleUnderTest;



    void SetUp() override {

        handleUnderTest = XMLConstHandle(mockNode);

    }

};



TEST_F(XMLConstHandleTest_142, ToNodeReturnsInitializedNode_142) {

    EXPECT_EQ(handleUnderTest.ToNode(), mockNode);

}



TEST_F(XMLConstHandleTest_142, FirstChildReturnsValidXMLConstHandle_142) {

    XMLConstHandle childHandle = handleUnderTest.FirstChild();

    EXPECT_NE(&childHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, FirstChildElementWithNameReturnsValidXMLConstHandle_142) {

    const char* elementName = "example";

    XMLConstHandle childElementHandle = handleUnderTest.FirstChildElement(elementName);

    EXPECT_NE(&childElementHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, LastChildReturnsValidXMLConstHandle_142) {

    XMLConstHandle lastChildHandle = handleUnderTest.LastChild();

    EXPECT_NE(&lastChildHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, LastChildElementWithNameReturnsValidXMLConstHandle_142) {

    const char* elementName = "example";

    XMLConstHandle lastChildElementHandle = handleUnderTest.LastChildElement(elementName);

    EXPECT_NE(&lastChildElementHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, PreviousSiblingReturnsValidXMLConstHandle_142) {

    XMLConstHandle previousSiblingHandle = handleUnderTest.PreviousSibling();

    EXPECT_NE(&previousSiblingHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, PreviousSiblingElementWithNameReturnsValidXMLConstHandle_142) {

    const char* elementName = "example";

    XMLConstHandle previousSiblingElementHandle = handleUnderTest.PreviousSiblingElement(elementName);

    EXPECT_NE(&previousSiblingElementHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, NextSiblingReturnsValidXMLConstHandle_142) {

    XMLConstHandle nextSiblingHandle = handleUnderTest.NextSibling();

    EXPECT_NE(&nextSiblingHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, NextSiblingElementWithNameReturnsValidXMLConstHandle_142) {

    const char* elementName = "example";

    XMLConstHandle nextSiblingElementHandle = handleUnderTest.NextSiblingElement(elementName);

    EXPECT_NE(&nextSiblingElementHandle, nullptr);

}



TEST_F(XMLConstHandleTest_142, ToElementReturnsNullForNonElementNode_142) {

    EXPECT_EQ(handleUnderTest.ToElement(), nullptr);

}



TEST_F(XMLConstHandleTest_142, ToTextReturnsNullForNonTextNode_142) {

    EXPECT_EQ(handleUnderTest.ToText(), nullptr);

}



TEST_F(XMLConstHandleTest_142, ToUnknownReturnsNullForNonUnknownNode_142) {

    EXPECT_EQ(handleUnderTest.ToUnknown(), nullptr);

}



TEST_F(XMLConstHandleTest_142, ToDeclarationReturnsNullForNonDeclarationNode_142) {

    EXPECT_EQ(handleUnderTest.ToDeclaration(), nullptr);

}
