#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_254 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        doc.InsertEndChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_254, Unsigned64Text_DefaultValueReturnedWhenNoText_254) {

    uint64_t defaultValue = 12345;

    EXPECT_EQ(defaultValue, element->Unsigned64Text(defaultValue));

}



TEST_F(XMLElementTest_254, Unsigned64Text_TextParsedCorrectly_254) {

    const char* textValue = "98765";

    uint64_t expectedValue = 98765;

    element->SetText(textValue);

    EXPECT_EQ(expectedValue, element->Unsigned64Text(0));

}



TEST_F(XMLElementTest_254, Unsigned64Text_BoundaryConditionMaxUint64_254) {

    const char* maxUint64 = "18446744073709551615";

    uint64_t expectedValue = UINT64_MAX;

    element->SetText(maxUint64);

    EXPECT_EQ(expectedValue, element->Unsigned64Text(0));

}



TEST_F(XMLElementTest_254, Unsigned64Text_BoundaryConditionMinUint64_254) {

    const char* minUint64 = "0";

    uint64_t expectedValue = 0;

    element->SetText(minUint64);

    EXPECT_EQ(expectedValue, element->Unsigned64Text(UINT64_MAX));

}



TEST_F(XMLElementTest_254, Unsigned64Text_InvalidTextReturnsDefaultValue_254) {

    const char* invalidText = "not_a_number";

    uint64_t defaultValue = 10101;

    element->SetText(invalidText);

    EXPECT_EQ(defaultValue, element->Unsigned64Text(defaultValue));

}
