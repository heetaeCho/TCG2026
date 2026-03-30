#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_88 : public ::testing::Test {

protected:

    XMLElementTest_88() {

        // Initialize XMLDocument and create an element for testing

        doc = new XMLDocument();

        element = doc->NewElement("TestElement");

        doc->LinkEndChild(element);

    }



    ~XMLElementTest_88() override {

        delete doc;

    }



    XMLDocument* doc;

    XMLElement* element;

};



TEST_F(XMLElementTest_88, QueryStringAttribute_SuccessfulQuery_88) {

    const char* value = "testValue";

    element->SetAttribute("testName", value);



    const char* result = nullptr;

    XMLError error = element->QueryStringAttribute("testName", &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_STREQ(result, value);

}



TEST_F(XMLElementTest_88, QueryStringAttribute_NoSuchAttribute_88) {

    const char* result = nullptr;

    XMLError error = element->QueryStringAttribute("nonExistent", &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLElementTest_88, QueryStringAttribute_NullValuePointer_88) {

    XMLError error = element->QueryStringAttribute("testName", nullptr);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}
