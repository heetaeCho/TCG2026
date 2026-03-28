#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_89 : public ::testing::Test {

protected:

    XMLElement* element;



    virtual void SetUp() {

        // Since we cannot directly instantiate XMLElement, we assume a way to get an instance

        // For the sake of testing, let's mock this part.

        XMLDocument doc;

        element = new XMLElement(&doc);

    }



    virtual void TearDown() {

        delete element;

    }

};



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_Int_89) {

    int value = 0;

    element->SetAttribute("test", 123);

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 123);

}



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_UnsignedInt_89) {

    unsigned int value = 0;

    element->SetAttribute("test", static_cast<unsigned>(123));

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 123u);

}



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_Int64_89) {

    int64_t value = 0;

    element->SetAttribute("test", static_cast<int64_t>(123));

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 123ll);

}



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_UnsignedInt64_89) {

    uint64_t value = 0;

    element->SetAttribute("test", static_cast<uint64_t>(123));

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 123ull);

}



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_Bool_89) {

    bool value = false;

    element->SetAttribute("test", true);

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_TRUE(value);

}



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_Double_89) {

    double value = 0.0;

    element->SetAttribute("test", 123.456);

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 123.456);

}



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_Float_89) {

    float value = 0.0f;

    element->SetAttribute("test", 123.456f);

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_FLOAT_EQ(value, 123.456f);

}



TEST_F(XMLElementTest_89, QueryAttribute_NormalOperation_String_89) {

    const char* value;

    element->SetAttribute("test", "hello");

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_STREQ(value, "hello");

}



TEST_F(XMLElementTest_89, QueryAttribute_AttributeNotFound_89) {

    int value;

    XMLError result = element->QueryAttribute("nonexistent", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_89, QueryAttribute_DefaultValue_UnsignedInt_89) {

    unsigned int defaultValue = 456;

    unsigned int value = element->UnsignedAttribute("test", defaultValue);

    EXPECT_EQ(value, defaultValue);

}



TEST_F(XMLElementTest_89, QueryAttribute_DefaultValue_Bool_89) {

    bool defaultValue = true;

    bool value = element->BoolAttribute("test", defaultValue);

    EXPECT_TRUE(value);

}



TEST_F(XMLElementTest_89, QueryAttribute_DefaultValue_Double_89) {

    double defaultValue = 456.789;

    double value = element->DoubleAttribute("test", defaultValue);

    EXPECT_DOUBLE_EQ(value, defaultValue);

}



TEST_F(XMLElementTest_89, QueryAttribute_DefaultValue_Float_89) {

    float defaultValue = 456.789f;

    float value = element->FloatAttribute("test", defaultValue);

    EXPECT_FLOAT_EQ(value, defaultValue);

}
