#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_131 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new XMLDocument();

        rootElement = document->NewElement("Root");

        document->InsertEndChild(rootElement);

        xmlHandle = XMLHandle(document).FirstChildElement("Root");

    }



    void TearDown() override {

        delete document;

    }



    XMLDocument* document;

    XMLElement* rootElement;

    XMLHandle xmlHandle;

};



TEST_F(XMLHandleTest_131, ToUnknown_ReturnsNullWhenNodeIsNotXMLUnknown_131) {

    EXPECT_EQ(xmlHandle.ToUnknown(), nullptr);

}



TEST_F(XMLHandleTest_131, ToUnknown_ReturnsPointerWhenNodeIsXMLUnknown_131) {

    XMLUnknown* unknown = document->NewUnknown("unknown");

    rootElement->InsertEndChild(unknown);

    xmlHandle = xmlHandle.FirstChild();

    EXPECT_NE(xmlHandle.ToUnknown(), nullptr);

}



TEST_F(XMLHandleTest_131, ToUnknown_ReturnsNullWhenNodeIsNull_131) {

    XMLHandle nullHandle(nullptr);

    EXPECT_EQ(nullHandle.ToUnknown(), nullptr);

}
