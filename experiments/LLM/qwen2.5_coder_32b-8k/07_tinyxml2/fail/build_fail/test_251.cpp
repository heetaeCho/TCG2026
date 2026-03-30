#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_251, IntText_DefaultValueReturnedWhenEmpty_251) {

    int defaultValue = 42;

    EXPECT_EQ(element->IntText(defaultValue), defaultValue);

}



TEST_F(XMLElementTest_251, IntText_ReturnsParsedValue_251) {

    element->SetText("123");

    EXPECT_EQ(element->IntText(0), 123);

}



TEST_F(XMLElementTest_251, IntText_ReturnsDefaultValueOnParseFailure_251) {

    element->SetText("abc");

    int defaultValue = 99;

    EXPECT_EQ(element->IntText(defaultValue), defaultValue);

}



TEST_F(XMLElementTest_251, IntText_BoundaryConditionNegativeValue_251) {

    element->SetText("-456");

    EXPECT_EQ(element->IntText(0), -456);

}



TEST_F(XMLElementTest_251, IntText_BoundaryConditionMaxIntValue_251) {

    element->SetText(std::to_string(INT_MAX).c_str());

    EXPECT_EQ(element->IntText(0), INT_MAX);

}



TEST_F(XMLElementTest_251, IntText_BoundaryConditionMinIntValue_251) {

    element->SetText(std::to_string(INT_MIN).c_str());

    EXPECT_EQ(element->IntText(0), INT_MIN);

}
