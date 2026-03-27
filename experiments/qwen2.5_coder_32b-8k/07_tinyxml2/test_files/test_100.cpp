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



TEST_F(XMLElementTest_100, SetAttribute_NormalOperation_100) {

    element->SetAttribute("test", static_cast<int64_t>(123));

    EXPECT_EQ(element->Int64Attribute("test"), 123);

}



TEST_F(XMLElementTest_100, SetAttribute_BoundaryConditions_100) {

    element->SetAttribute("min", std::numeric_limits<int64_t>::min());

    element->SetAttribute("max", std::numeric_limits<int64_t>::max());



    EXPECT_EQ(element->Int64Attribute("min"), std::numeric_limits<int64_t>::min());

    EXPECT_EQ(element->Int64Attribute("max"), std::numeric_limits<int64_t>::max());

}



TEST_F(XMLElementTest_100, SetAttribute_MultipleAttributes_100) {

    element->SetAttribute("attr1", static_cast<int64_t>(1));

    element->SetAttribute("attr2", static_cast<int64_t>(2));



    EXPECT_EQ(element->Int64Attribute("attr1"), 1);

    EXPECT_EQ(element->Int64Attribute("attr2"), 2);

}



TEST_F(XMLElementTest_100, SetAttribute_UpdateExistingAttribute_100) {

    element->SetAttribute("test", static_cast<int64_t>(10));

    element->SetAttribute("test", static_cast<int64_t>(20));



    EXPECT_EQ(element->Int64Attribute("test"), 20);

}



TEST_F(XMLElementTest_100, SetAttribute_DefaultValue_100) {

    int64_t value = element->Int64Attribute("nonexistent", static_cast<int64_t>(-1));

    EXPECT_EQ(value, -1);

}
