#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_233 : public ::testing::Test {

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



TEST_F(XMLElementTest_233, DoubleAttribute_ReturnsDefaultValue_WhenAttributeNotFound_233) {

    double defaultValue = 42.0;

    EXPECT_EQ(defaultValue, element->DoubleAttribute("nonexistent", defaultValue));

}



TEST_F(XMLElementTest_233, DoubleAttribute_ReturnsAttributeValue_WhenAttributeExists_233) {

    element->SetAttribute("testattr", "123.45");

    EXPECT_DOUBLE_EQ(123.45, element->DoubleAttribute("testattr", 0.0));

}



TEST_F(XMLElementTest_233, DoubleAttribute_ReturnsZero_WhenInvalidAttributeValue_233) {

    element->SetAttribute("testattr", "invalid");

    EXPECT_DOUBLE_EQ(0.0, element->DoubleAttribute("testattr", 0.0));

}



TEST_F(XMLElementTest_233, DoubleAttribute_BoundaryCondition_ZeroValue_233) {

    element->SetAttribute("testattr", "0.0");

    EXPECT_DOUBLE_EQ(0.0, element->DoubleAttribute("testattr", -1.0));

}



TEST_F(XMLElementTest_233, DoubleAttribute_BoundaryCondition_MaxValue_233) {

    double maxValue = std::numeric_limits<double>::max();

    element->SetAttribute("testattr", "1.79769e+308");

    EXPECT_DOUBLE_EQ(maxValue, element->DoubleAttribute("testattr", 0.0));

}



TEST_F(XMLElementTest_233, DoubleAttribute_BoundaryCondition_MinValue_233) {

    double minValue = std::numeric_limits<double>::lowest();

    element->SetAttribute("testattr", "-1.79769e+308");

    EXPECT_DOUBLE_EQ(minValue, element->DoubleAttribute("testattr", 0.0));

}
