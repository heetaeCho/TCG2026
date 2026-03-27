#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLElementTest_95 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_95, QueryFloatAttribute_NormalOperation_95) {

    float value = 0.0f;

    element->SetAttribute("test", 123.456f);

    XMLError result = element->QueryFloatAttribute("test", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, 123.456f);

}



TEST_F(XMLElementTest_95, QueryFloatAttribute_AttributeNotFound_95) {

    float value = 0.0f;

    XMLError result = element->QueryFloatAttribute("nonexistent", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_95, QueryFloatAttribute_InvalidType_95) {

    float value = 0.0f;

    element->SetAttribute("test", "not_a_float");

    XMLError result = element->QueryFloatAttribute("test", &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_95, QueryFloatAttribute_DefaultValue_95) {

    float value = 0.0f;

    XMLError result = element->QueryFloatAttribute("nonexistent", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

    EXPECT_FLOAT_EQ(value, 0.0f); // Default value remains unchanged

}



TEST_F(XMLElementTest_95, QueryFloatAttribute_ZeroValue_95) {

    float value = -1.0f;

    element->SetAttribute("test", 0.0f);

    XMLError result = element->QueryFloatAttribute("test", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, 0.0f);

}



TEST_F(XMLElementTest_95, QueryFloatAttribute_MaxValue_95) {

    float value = 0.0f;

    element->SetAttribute("test", std::numeric_limits<float>::max());

    XMLError result = element->QueryFloatAttribute("test", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, std::numeric_limits<float>::max());

}



TEST_F(XMLElementTest_95, QueryFloatAttribute_MinValue_95) {

    float value = 0.0f;

    element->SetAttribute("test", std::numeric_limits<float>::lowest());

    XMLError result = element->QueryFloatAttribute("test", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, std::numeric_limits<float>::lowest());

}
