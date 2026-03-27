#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_96 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_96, QueryAttribute_String_NormalOperation_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "testValue";

    element->SetAttribute(attributeName, attributeValue);



    const char* result = nullptr;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_STREQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryAttribute_String_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    const char** result = nullptr;

    XMLError error = element->QueryAttribute(attributeName, result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryAttribute_String_EmptyAttributeName_96) {

    const char* attributeName = "";

    const char** result = nullptr;

    XMLError error = element->QueryAttribute(attributeName, result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_96, QueryAttribute_String_NullAttributeName_96) {

    const char* attributeName = nullptr;

    const char** result = nullptr;

    XMLError error = element->QueryAttribute(attributeName, result);

    EXPECT_EQ(error, XML_ERROR_PARSING_ELEMENT);

}



TEST_F(XMLElementTest_96, QueryAttribute_String_EmptyAttributeValue_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "";

    element->SetAttribute(attributeName, attributeValue);



    const char* result = nullptr;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_STREQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryIntAttribute_NormalOperation_96) {

    const char* attributeName = "testAttr";

    int attributeValue = 42;

    element->SetAttribute(attributeName, attributeValue);



    int result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryIntAttribute_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    int result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryIntAttribute_WrongType_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "notAnInteger";

    element->SetAttribute(attributeName, attributeValue);



    int result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_96, QueryUnsignedAttribute_NormalOperation_96) {

    const char* attributeName = "testAttr";

    unsigned int attributeValue = 42;

    element->SetAttribute(attributeName, attributeValue);



    unsigned int result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryUnsignedAttribute_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    unsigned int result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryUnsignedAttribute_WrongType_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "notAnInteger";

    element->SetAttribute(attributeName, attributeValue);



    unsigned int result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_96, QueryInt64Attribute_NormalOperation_96) {

    const char* attributeName = "testAttr";

    int64_t attributeValue = 123456789012345LL;

    element->SetAttribute(attributeName, attributeValue);



    int64_t result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryInt64Attribute_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    int64_t result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryInt64Attribute_WrongType_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "notAnInteger";

    element->SetAttribute(attributeName, attributeValue);



    int64_t result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_96, QueryUnsigned64Attribute_NormalOperation_96) {

    const char* attributeName = "testAttr";

    uint64_t attributeValue = 123456789012345ULL;

    element->SetAttribute(attributeName, attributeValue);



    uint64_t result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryUnsigned64Attribute_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    uint64_t result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryUnsigned64Attribute_WrongType_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "notAnInteger";

    element->SetAttribute(attributeName, attributeValue);



    uint64_t result = 0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_96, QueryBoolAttribute_NormalOperation_96) {

    const char* attributeName = "testAttr";

    bool attributeValue = true;

    element->SetAttribute(attributeName, attributeValue);



    bool result = false;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryBoolAttribute_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    bool result = false;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryBoolAttribute_WrongType_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "notABoolean";

    element->SetAttribute(attributeName, attributeValue);



    bool result = false;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_96, QueryDoubleAttribute_NormalOperation_96) {

    const char* attributeName = "testAttr";

    double attributeValue = 3.14159;

    element->SetAttribute(attributeName, attributeValue);



    double result = 0.0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryDoubleAttribute_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    double result = 0.0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryDoubleAttribute_WrongType_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "notADouble";

    element->SetAttribute(attributeName, attributeValue);



    double result = 0.0;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_96, QueryFloatAttribute_NormalOperation_96) {

    const char* attributeName = "testAttr";

    float attributeValue = 3.14f;

    element->SetAttribute(attributeName, attributeValue);



    float result = 0.0f;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_FLOAT_EQ(result, attributeValue);

}



TEST_F(XMLElementTest_96, QueryFloatAttribute_AttributeNotFound_96) {

    const char* attributeName = "nonExistentAttr";

    float result = 0.0f;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_96, QueryFloatAttribute_WrongType_96) {

    const char* attributeName = "testAttr";

    const char* attributeValue = "notAFloat";

    element->SetAttribute(attributeName, attributeValue);



    float result = 0.0f;

    XMLError error = element->QueryAttribute(attributeName, &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

}
