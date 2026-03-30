#include "gtest/gtest.h"

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_84 : public ::testing::Test {

protected:

    XMLElement element;

};



TEST_F(XMLElementTest_84, QueryUnsigned64Attribute_NormalOperation_84) {

    uint64_t value;

    const char* attributeName = "testAttr";

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(attributeName, (uint64_t)12345);

    element.SetFirstAttribute(attr);



    EXPECT_EQ(element.QueryUnsigned64Attribute(attributeName, &value), XML_SUCCESS);

    EXPECT_EQ(value, 12345u);

}



TEST_F(XMLElementTest_84, QueryUnsigned64Attribute_AttributeNotFound_84) {

    uint64_t value;

    const char* attributeName = "nonExistentAttr";



    EXPECT_EQ(element.QueryUnsigned64Attribute(attributeName, &value), XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_84, QueryUnsigned64Attribute_BoundaryCondition_ZeroValue_84) {

    uint64_t value;

    const char* attributeName = "zeroAttr";

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(attributeName, (uint64_t)0);

    element.SetFirstAttribute(attr);



    EXPECT_EQ(element.QueryUnsigned64Attribute(attributeName, &value), XML_SUCCESS);

    EXPECT_EQ(value, 0u);

}



TEST_F(XMLElementTest_84, QueryUnsigned64Attribute_BoundaryCondition_MaxValue_84) {

    uint64_t value;

    const char* attributeName = "maxAttr";

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(attributeName, UINT64_MAX);

    element.SetFirstAttribute(attr);



    EXPECT_EQ(element.QueryUnsigned64Attribute(attributeName, &value), XML_SUCCESS);

    EXPECT_EQ(value, UINT64_MAX);

}



TEST_F(XMLElementTest_84, QueryUnsigned64Attribute_ErrorCase_WrongType_84) {

    uint64_t value;

    const char* attributeName = "wrongTypeAttr";

    XMLAttribute* attr = new XMLAttribute();

    attr->SetAttribute(attributeName, "not_a_number");

    element.SetFirstAttribute(attr);



    EXPECT_EQ(element.QueryUnsigned64Attribute(attributeName, &value), XML_WRONG_ATTRIBUTE_TYPE);

}
