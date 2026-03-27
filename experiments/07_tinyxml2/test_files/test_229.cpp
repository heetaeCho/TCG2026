#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_229 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_229, UnsignedAttribute_NormalOperation_229) {

    element->SetAttribute("test", 42u);

    EXPECT_EQ(element->UnsignedAttribute("test", 0), 42u);

}



TEST_F(XMLElementTest_229, UnsignedAttribute_DefaultValue_229) {

    EXPECT_EQ(element->UnsignedAttribute("nonexistent", 17u), 17u);

}



TEST_F(XMLElementTest_229, UnsignedAttribute_ZeroValue_229) {

    element->SetAttribute("zero", 0u);

    EXPECT_EQ(element->UnsignedAttribute("zero", 42u), 0u);

}



TEST_F(XMLElementTest_229, UnsignedAttribute_MaxValue_229) {

    element->SetAttribute("max", UINT_MAX);

    EXPECT_EQ(element->UnsignedAttribute("max", 0), UINT_MAX);

}



TEST_F(XMLElementTest_229, UnsignedAttribute_EmptyString_229) {

    element->SetAttribute("empty", "");

    EXPECT_EQ(element->UnsignedAttribute("empty", 13u), 13u);

}



TEST_F(XMLElementTest_229, UnsignedAttribute_NegativeValueAsString_229) {

    element->SetAttribute("negative", "-42");

    EXPECT_EQ(element->UnsignedAttribute("negative", 0), 0u); // Assuming it treats negative as default

}
