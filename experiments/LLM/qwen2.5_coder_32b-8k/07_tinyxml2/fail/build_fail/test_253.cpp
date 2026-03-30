#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

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



TEST_F(XMLElementTest_253, Int64Text_DefaultValue_Returned_WhenNoText_253) {

    int64_t defaultValue = 12345;

    EXPECT_EQ(defaultValue, element->Int64Text(defaultValue));

}



TEST_F(XMLElementTest_253, Int64Text_Value_Returned_WhenValidText_253) {

    int64_t value = 98765;

    element->SetText(value);

    EXPECT_EQ(value, element->Int64Text(0));

}



TEST_F(XMLElementTest_253, Int64Text_DefaultValue_Returned_OnInvalidText_253) {

    element->SetText("invalid");

    int64_t defaultValue = 987;

    EXPECT_EQ(defaultValue, element->Int64Text(defaultValue));

}



TEST_F(XMLElementTest_253, Int64Text_BoundaryMaxValue_Returned_WhenValidText_253) {

    int64_t maxValue = INT64_MAX;

    element->SetText(maxValue);

    EXPECT_EQ(maxValue, element->Int64Text(0));

}



TEST_F(XMLElementTest_253, Int64Text_BoundaryMinValue_Returned_WhenValidText_253) {

    int64_t minValue = INT64_MIN;

    element->SetText(minValue);

    EXPECT_EQ(minValue, element->Int64Text(0));

}
