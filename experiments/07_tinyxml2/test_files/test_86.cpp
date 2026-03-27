#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_86 : public ::testing::Test {

protected:

    XMLElement element;

};



TEST_F(XMLElementTest_86, QueryDoubleAttribute_NormalOperation_86) {

    double value;

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(3.14);

    EXPECT_CALL(attr, QueryDoubleValue(&value)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(3.14), ::testing::Return(XML_SUCCESS)));



    element._rootAttribute = attr;

    XMLError result = element.QueryDoubleAttribute("test", &value);



    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 3.14);

}



TEST_F(XMLElementTest_86, QueryDoubleAttribute_NoAttribute_86) {

    double value;



    XMLError result = element.QueryDoubleAttribute("nonexistent", &value);



    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_86, QueryDoubleAttribute_NullPointerValue_86) {

    const char* attrName = "test";



    XMLError result = element.QueryDoubleAttribute(attrName, nullptr);



    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_86, QueryDoubleAttribute_BoundaryCondition_LargeNumber_86) {

    double value;

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(1.7976931348623157E+308); // DBL_MAX

    EXPECT_CALL(attr, QueryDoubleValue(&value)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(1.7976931348623157E+308), ::testing::Return(XML_SUCCESS)));



    element._rootAttribute = attr;

    XMLError result = element.QueryDoubleAttribute("test", &value);



    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 1.7976931348623157E+308);

}



TEST_F(XMLElementTest_86, QueryDoubleAttribute_BoundaryCondition_SmallNumber_86) {

    double value;

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(-1.7976931348623157E+308); // -DBL_MAX

    EXPECT_CALL(attr, QueryDoubleValue(&value)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(-1.7976931348623157E+308), ::testing::Return(XML_SUCCESS)));



    element._rootAttribute = attr;

    XMLError result = element.QueryDoubleAttribute("test", &value);



    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, -1.7976931348623157E+308);

}



TEST_F(XMLElementTest_86, QueryDoubleAttribute_BoundaryCondition_Zero_86) {

    double value;

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(0.0);

    EXPECT_CALL(attr, QueryDoubleValue(&value)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(0.0), ::testing::Return(XML_SUCCESS)));



    element._rootAttribute = attr;

    XMLError result = element.QueryDoubleAttribute("test", &value);



    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 0.0);

}
