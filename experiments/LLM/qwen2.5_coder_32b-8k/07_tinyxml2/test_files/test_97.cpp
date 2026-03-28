#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_97 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        ASSERT_NE(element, nullptr);

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_97, SetAttribute_String_NormalOperation_97) {

    element->SetAttribute("test", "value");

    EXPECT_STREQ(element->Attribute("test"), "value");

}



TEST_F(XMLElementTest_97, SetAttribute_Int_NormalOperation_97) {

    element->SetAttribute("intAttr", 42);

    EXPECT_EQ(element->IntAttribute("intAttr"), 42);

}



TEST_F(XMLElementTest_97, SetAttribute_UnsignedInt_NormalOperation_97) {

    element->SetAttribute("unsignedIntAttr", 100u);

    EXPECT_EQ(element->UnsignedAttribute("unsignedIntAttr"), 100u);

}



TEST_F(XMLElementTest_97, SetAttribute_Int64_NormalOperation_97) {

    element->SetAttribute("int64Attr", 9223372036854775807LL);

    EXPECT_EQ(element->Int64Attribute("int64Attr"), 9223372036854775807LL);

}



TEST_F(XMLElementTest_97, SetAttribute_Unsigned64_NormalOperation_97) {

    element->SetAttribute("unsigned64Attr", 18446744073709551615ULL);

    EXPECT_EQ(element->Unsigned64Attribute("unsigned64Attr"), 18446744073709551615ULL);

}



TEST_F(XMLElementTest_97, SetAttribute_Bool_NormalOperation_97) {

    element->SetAttribute("boolAttr", true);

    EXPECT_EQ(element->BoolAttribute("boolAttr"), true);

}



TEST_F(XMLElementTest_97, SetAttribute_Double_NormalOperation_97) {

    element->SetAttribute("doubleAttr", 3.14159);

    EXPECT_DOUBLE_EQ(element->DoubleAttribute("doubleAttr"), 3.14159);

}



TEST_F(XMLElementTest_97, SetAttribute_Float_NormalOperation_97) {

    element->SetAttribute("floatAttr", 2.718f);

    EXPECT_FLOAT_EQ(element->FloatAttribute("floatAttr"), 2.718f);

}



TEST_F(XMLElementTest_97, Attribute_DefaultValue_ReturnsDefaultValue_97) {

    int result = element->IntAttribute("nonExistent", -1);

    EXPECT_EQ(result, -1);

}



TEST_F(XMLElementTest_97, FindAttribute_AttributeExists_ReturnsAttribute_97) {

    element->SetAttribute("testAttr", "value");

    const XMLAttribute* attr = element->FindAttribute("testAttr");

    ASSERT_NE(attr, nullptr);

    EXPECT_STREQ(attr->Value(), "value");

}



TEST_F(XMLElementTest_97, FindAttribute_AttributeDoesNotExist_ReturnsNull_97) {

    const XMLAttribute* attr = element->FindAttribute("nonExistent");

    EXPECT_EQ(attr, nullptr);

}



TEST_F(XMLElementTest_97, DeleteAttribute_AttributeExists_DeletesAttribute_97) {

    element->SetAttribute("testAttr", "value");

    element->DeleteAttribute("testAttr");

    const XMLAttribute* attr = element->FindAttribute("testAttr");

    EXPECT_EQ(attr, nullptr);

}



TEST_F(XMLElementTest_97, DeleteAttribute_AttributeDoesNotExist_NoError_97) {

    element->DeleteAttribute("nonExistent"); // Should not throw or cause an error

}



TEST_F(XMLElementTest_97, SetAttribute_Overwrite_ReplacesValue_97) {

    element->SetAttribute("testAttr", "value1");

    element->SetAttribute("testAttr", "value2");

    EXPECT_STREQ(element->Attribute("testAttr"), "value2");

}
