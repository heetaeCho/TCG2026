#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_252 : public ::testing::Test {

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



TEST_F(XMLElementTest_252, UnsignedText_ReturnsDefaultValueWhenEmpty_252) {

    unsigned defaultValue = 42;

    EXPECT_EQ(defaultValue, element->UnsignedText(defaultValue));

}



TEST_F(XMLElementTest_252, UnsignedText_ReturnsParsedValueWhenSet_252) {

    unsigned value = 123;

    element->SetText(value);

    EXPECT_EQ(value, element->UnsignedText(0));

}



TEST_F(XMLElementTest_252, UnsignedText_HandlesMaxUnsignedInt_252) {

    unsigned maxUnsigned = UINT_MAX;

    element->SetText(maxUnsigned);

    EXPECT_EQ(maxUnsigned, element->UnsignedText(0));

}



TEST_F(XMLElementTest_252, UnsignedText_ReturnsDefaultValueWhenNonNumeric_252) {

    element->SetText("non-numeric");

    unsigned defaultValue = 7;

    EXPECT_EQ(defaultValue, element->UnsignedText(defaultValue));

}
