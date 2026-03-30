#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_243 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument();

        element = new XMLElement(doc);

    }



    void TearDown() override {

        delete element;

        delete doc;

    }



    XMLDocument* doc;

    XMLElement* element;

};



TEST_F(XMLElementTest_243, SetTextDouble_NormalOperation_243) {

    double value = 123.456;

    element->SetText(value);

    const char* text = element->GetText();

    EXPECT_STREQ(text, "123.456");

}



TEST_F(XMLElementTest_243, SetTextDouble_BoundaryCondition_Zero_243) {

    double value = 0.0;

    element->SetText(value);

    const char* text = element->GetText();

    EXPECT_STREQ(text, "0");

}



TEST_F(XMLElementTest_243, SetTextDouble_BoundaryCondition_MaxValue_243) {

    double value = std::numeric_limits<double>::max();

    element->SetText(value);

    const char* text = element->GetText();

    // The exact string representation might vary due to precision limits

    EXPECT_STRNE(text, "");

}



TEST_F(XMLElementTest_243, SetTextDouble_BoundaryCondition_MinValue_243) {

    double value = std::numeric_limits<double>::lowest();

    element->SetText(value);

    const char* text = element->GetText();

    // The exact string representation might vary due to precision limits

    EXPECT_STRNE(text, "");

}



TEST_F(XMLElementTest_243, SetTextDouble_Exceptional_NaN_243) {

    double value = std::numeric_limits<double>::quiet_NaN();

    element->SetText(value);

    const char* text = element->GetText();

    // The exact string representation might vary

    EXPECT_STRNE(text, "");

}



TEST_F(XMLElementTest_243, SetTextDouble_Exceptional_Infinity_243) {

    double value = std::numeric_limits<double>::infinity();

    element->SetText(value);

    const char* text = element->GetText();

    // The exact string representation might vary

    EXPECT_STRNE(text, "");

}
