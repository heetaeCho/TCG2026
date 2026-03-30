#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_78, NameReturnsCorrectValue_78) {

    const char* expectedName = "testElement";

    element->SetName(expectedName);

    EXPECT_STREQ(element->Name(), expectedName);

}



TEST_F(XMLElementTest_78, SetAndGetTextWorksProperly_78) {

    const char* text = "Sample Text";

    element->SetText(text);

    EXPECT_STREQ(element->GetText(), text);

}



TEST_F(XMLElementTest_78, IntAttributeReturnsCorrectValue_78) {

    int expectedValue = 42;

    element->SetAttribute("intValue", expectedValue);

    EXPECT_EQ(element->IntAttribute("intValue"), expectedValue);

}



TEST_F(XMLElementTest_78, UnsignedAttributeReturnsCorrectValue_78) {

    unsigned int expectedValue = 100;

    element->SetAttribute("unsignedValue", expectedValue);

    EXPECT_EQ(element->UnsignedAttribute("unsignedValue"), expectedValue);

}



TEST_F(XMLElementTest_78, Int64AttributeReturnsCorrectValue_78) {

    int64_t expectedValue = 9223372036854775807;

    element->SetAttribute("int64Value", expectedValue);

    EXPECT_EQ(element->Int64Attribute("int64Value"), expectedValue);

}



TEST_F(XMLElementTest_78, Unsigned64AttributeReturnsCorrectValue_78) {

    uint64_t expectedValue = 18446744073709551615U;

    element->SetAttribute("uint64Value", expectedValue);

    EXPECT_EQ(element->Unsigned64Attribute("uint64Value"), expectedValue);

}



TEST_F(XMLElementTest_78, BoolAttributeReturnsCorrectValue_78) {

    bool expectedValue = true;

    element->SetAttribute("boolValue", expectedValue);

    EXPECT_EQ(element->BoolAttribute("boolValue"), expectedValue);

}



TEST_F(XMLElementTest_78, DoubleAttributeReturnsCorrectValue_78) {

    double expectedValue = 3.141592653589793;

    element->SetAttribute("doubleValue", expectedValue);

    EXPECT_DOUBLE_EQ(element->DoubleAttribute("doubleValue"), expectedValue);

}



TEST_F(XMLElementTest_78, FloatAttributeReturnsCorrectValue_78) {

    float expectedValue = 3.14159f;

    element->SetAttribute("floatValue", expectedValue);

    EXPECT_FLOAT_EQ(element->FloatAttribute("floatValue"), expectedValue);

}



TEST_F(XMLElementTest_78, DefaultValuesAreReturnedForNonExistentAttributes_78) {

    int defaultValue = 42;

    EXPECT_EQ(element->IntAttribute("nonexistent", defaultValue), defaultValue);



    unsigned int defaultUnsignedValue = 100;

    EXPECT_EQ(element->UnsignedAttribute("nonexistent", defaultUnsignedValue), defaultUnsignedValue);



    int64_t defaultInt64Value = 9223372036854775807;

    EXPECT_EQ(element->Int64Attribute("nonexistent", defaultInt64Value), defaultInt64Value);



    uint64_t defaultUint64Value = 18446744073709551615U;

    EXPECT_EQ(element->Unsigned64Attribute("nonexistent", defaultUint64Value), defaultUint64Value);



    bool defaultBoolValue = true;

    EXPECT_EQ(element->BoolAttribute("nonexistent", defaultBoolValue), defaultBoolValue);



    double defaultDoubleValue = 3.141592653589793;

    EXPECT_DOUBLE_EQ(element->DoubleAttribute("nonexistent", defaultDoubleValue), defaultDoubleValue);



    float defaultFloatValue = 3.14159f;

    EXPECT_FLOAT_EQ(element->FloatAttribute("nonexistent", defaultFloatValue), defaultFloatValue);

}



TEST_F(XMLElementTest_78, DeleteAttributeRemovesTheCorrectAttribute_78) {

    element->SetAttribute("testAttr", "value");

    EXPECT_STREQ(element->Attribute("testAttr"), "value");



    element->DeleteAttribute("testAttr");

    EXPECT_EQ(element->Attribute("testAttr"), nullptr);

}



TEST_F(XMLElementTest_78, InsertNewChildElementCreatesChildProperly_78) {

    XMLElement* child = element->InsertNewChildElement("childElement");

    EXPECT_STREQ(child->Name(), "childElement");

    EXPECT_EQ(element->FirstChildElement()->Name(), "childElement");

}



TEST_F(XMLElementTest_78, InsertNewCommentCreatesCommentProperly_78) {

    XMLComment* comment = element->InsertNewComment("This is a comment");

    EXPECT_STREQ(comment->Value(), "This is a comment");

    EXPECT_TRUE(element->FirstChild()->ToComment() != nullptr);

}



TEST_F(XMLElementTest_78, InsertNewTextCreatesTextProperly_78) {

    XMLText* text = element->InsertNewText("Sample Text");

    EXPECT_STREQ(text->Value(), "Sample Text");

    EXPECT_TRUE(element->FirstChild()->ToText() != nullptr);

}



TEST_F(XMLElementTest_78, InsertNewDeclarationCreatesDeclarationProperly_78) {

    XMLDeclaration* declaration = element->InsertNewDeclaration("version=\"1.0\"");

    EXPECT_STREQ(declaration->Value(), "version=\"1.0\"");

    EXPECT_TRUE(element->FirstChild()->ToDeclaration() != nullptr);

}



TEST_F(XMLElementTest_78, InsertNewUnknownCreatesUnknownProperly_78) {

    XMLUnknown* unknown = element->InsertNewUnknown("unknown");

    EXPECT_STREQ(unknown->Value(), "unknown");

    EXPECT_TRUE(element->FirstChild()->ToUnknown() != nullptr);

}
