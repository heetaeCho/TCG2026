#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLElement* element;



    void SetUp() override {

        XMLDocument doc;

        element = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_240, SetTextUint64_NormalOperation_240) {

    uint64_t value = 123456789012345;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "123456789012345");

}



TEST_F(XMLElementTest_240, SetTextUint64_BoundaryCondition_MaxValue_240) {

    uint64_t value = UINT64_MAX;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "18446744073709551615");

}



TEST_F(XMLElementTest_240, SetTextUint64_BoundaryCondition_Zero_240) {

    uint64_t value = 0;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}



// Since the implementation does not provide any way to throw exceptions or return errors,

// exceptional cases are not applicable here based on the provided interface.
