#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_239 : public ::testing::Test {

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



TEST_F(XMLElementTest_239, SetTextInt64_NormalOperation_239) {

    int64_t value = 123456789012345LL;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "123456789012345");

}



TEST_F(XMLElementTest_239, SetTextInt64_BoundaryCondition_Min_239) {

    int64_t value = INT64_MIN;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "-9223372036854775808");

}



TEST_F(XMLElementTest_239, SetTextInt64_BoundaryCondition_Max_239) {

    int64_t value = INT64_MAX;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "9223372036854775807");

}



TEST_F(XMLElementTest_239, SetTextInt64_BoundaryCondition_Zero_239) {

    int64_t value = 0;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}
