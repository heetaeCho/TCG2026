#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_73 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_73, Unsigned64Value_ReturnsZeroByDefault_73) {

    EXPECT_EQ(attr.Unsigned64Value(), 0);

}



TEST_F(XMLAttributeTest_73, QueryUnsigned64Value_SuccessfulQueryUpdatesValue_73) {

    uint64_t value = 123;

    attr.SetAttribute(value);

    uint64_t result = 0;

    EXPECT_EQ(attr.QueryUnsigned64Value(&result), XML_SUCCESS);

    EXPECT_EQ(result, value);

}



TEST_F(XMLAttributeTest_73, QueryUnsigned64Value_ReturnsErrorForInvalidInput_73) {

    attr.SetAttribute("invalid");

    uint64_t result = 0;

    EXPECT_NE(attr.QueryUnsigned64Value(&result), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_73, SetAttribute_IntegerValueUpdatesCorrectly_73) {

    int value = 123;

    attr.SetAttribute(value);

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, static_cast<uint64_t>(value));

}



TEST_F(XMLAttributeTest_73, SetAttribute_UnsignedIntegerValueUpdatesCorrectly_73) {

    unsigned int value = 123;

    attr.SetAttribute(value);

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, static_cast<uint64_t>(value));

}



TEST_F(XMLAttributeTest_73, SetAttribute_UnsignedLongLongValueUpdatesCorrectly_73) {

    uint64_t value = 123;

    attr.SetAttribute(value);

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, value);

}



TEST_F(XMLAttributeTest_73, SetAttribute_StringValueUpdatesCorrectly_73) {

    uint64_t expectedValue = 123;

    std::string stringValue = std::to_string(expectedValue);

    attr.SetAttribute(stringValue.c_str());

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, expectedValue);

}



TEST_F(XMLAttributeTest_73, SetAttribute_StringValueWithLeadingSpacesUpdatesCorrectly_73) {

    uint64_t expectedValue = 123;

    std::string stringValue = "   " + std::to_string(expectedValue);

    attr.SetAttribute(stringValue.c_str());

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, expectedValue);

}



TEST_F(XMLAttributeTest_73, SetAttribute_StringValueWithTrailingSpacesUpdatesCorrectly_73) {

    uint64_t expectedValue = 123;

    std::string stringValue = std::to_string(expectedValue) + "   ";

    attr.SetAttribute(stringValue.c_str());

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, expectedValue);

}



TEST_F(XMLAttributeTest_73, SetAttribute_StringValueWithSpacesUpdatesCorrectly_73) {

    uint64_t expectedValue = 123;

    std::string stringValue = "   " + std::to_string(expectedValue) + "   ";

    attr.SetAttribute(stringValue.c_str());

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, expectedValue);

}



TEST_F(XMLAttributeTest_73, SetAttribute_StringValueWithNonNumericFailsGracefully_73) {

    std::string stringValue = "abc";

    attr.SetAttribute(stringValue.c_str());

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, 0);

}



TEST_F(XMLAttributeTest_73, SetAttribute_StringValueWithMixedContentFailsGracefully_73) {

    std::string stringValue = "123abc";

    attr.SetAttribute(stringValue.c_str());

    uint64_t result = attr.Unsigned64Value();

    EXPECT_EQ(result, 0);

}
