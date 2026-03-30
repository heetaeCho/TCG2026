#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_228 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("test");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_228, IntAttribute_ReturnsDefaultValueWhenAttributeNotFound_228) {

    int defaultValue = 42;

    EXPECT_EQ(defaultValue, element->IntAttribute("nonexistent", defaultValue));

}



TEST_F(XMLElementTest_228, IntAttribute_ReturnsAttributeValueWhenFound_228) {

    element->SetAttribute("testAttr", 123);

    EXPECT_EQ(123, element->IntAttribute("testAttr", 42));

}



TEST_F(XMLElementTest_228, IntAttribute_HandlesZeroValueCorrectly_228) {

    element->SetAttribute("testAttr", 0);

    EXPECT_EQ(0, element->IntAttribute("testAttr", 42));

}



TEST_F(XMLElementTest_228, IntAttribute_HandlesNegativeValueCorrectly_228) {

    element->SetAttribute("testAttr", -123);

    EXPECT_EQ(-123, element->IntAttribute("testAttr", 42));

}
