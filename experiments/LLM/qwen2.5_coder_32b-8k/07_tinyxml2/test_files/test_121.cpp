#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_121 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement;

    XMLHandle handle;



    void SetUp() override {

        rootElement = doc.NewElement("Root");

        doc.InsertFirstChild(rootElement);

        handle = XMLHandle(doc).FirstChildElement();

    }

};



TEST_F(XMLHandleTest_121, FirstChildElement_ReturnsSelfWhenNameMatches_121) {

    XMLElement* childElement = doc.NewElement("Child");

    rootElement->InsertEndChild(childElement);



    XMLHandle resultHandle = handle.FirstChildElement("Child");



    EXPECT_EQ(resultHandle.ToElement(), childElement);

}



TEST_F(XMLHandleTest_121, FirstChildElement_ReturnsNullWhenNameDoesNotMatch_121) {

    XMLElement* childElement = doc.NewElement("Child");

    rootElement->InsertEndChild(childElement);



    XMLHandle resultHandle = handle.FirstChildElement("NonExistent");



    EXPECT_EQ(resultHandle.ToElement(), nullptr);

}



TEST_F(XMLHandleTest_121, FirstChildElement_ReturnsNullWhenNoChildren_121) {

    XMLHandle resultHandle = handle.FirstChildElement();



    EXPECT_EQ(resultHandle.ToElement(), nullptr);

}



TEST_F(XMLHandleTest_121, FirstChildElement_IgnoresCaseSensitiveNameMatching_121) {

    XMLElement* childElement = doc.NewElement("child");

    rootElement->InsertEndChild(childElement);



    XMLHandle resultHandle = handle.FirstChildElement("Child");



    EXPECT_EQ(resultHandle.ToElement(), childElement);

}



TEST_F(XMLHandleTest_121, FirstChildElement_ReturnsFirstMatchingChild_121) {

    XMLElement* firstChild = doc.NewElement("Child");

    XMLElement* secondChild = doc.NewElement("Child");

    rootElement->InsertEndChild(firstChild);

    rootElement->InsertEndChild(secondChild);



    XMLHandle resultHandle = handle.FirstChildElement("Child");



    EXPECT_EQ(resultHandle.ToElement(), firstChild);

}



TEST_F(XMLHandleTest_121, FirstChildElement_ReturnsNullWhenNameIsNull_121) {

    XMLElement* childElement = doc.NewElement("Child");

    rootElement->InsertEndChild(childElement);



    XMLHandle resultHandle = handle.FirstChildElement(nullptr);



    EXPECT_EQ(resultHandle.ToElement(), nullptr);

}
