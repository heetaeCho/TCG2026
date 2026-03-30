// File: ./TestProjects/tinyxml2/tests/test_xmlelement_query_unsigned64_attribute_84.cpp

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryUnsigned64AttributeTest_84 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* ParseSingleElement(const char* xml) {
        doc.Clear();
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        return root;
    }
};

TEST_F(QueryUnsigned64AttributeTest_84, ReturnsNoAttributeWhenMissing_84) {
    XMLElement* root = ParseSingleElement("<root a='1'/>");

    uint64_t value = 0;
    const XMLError err = root->QueryUnsigned64Attribute("missing", &value);

    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(QueryUnsigned64AttributeTest_84, ReadsUnsigned64AttributeFromStringNumber_84) {
    XMLElement* root = ParseSingleElement("<root u64='42'/>");

    uint64_t value = 0;
    const XMLError err = root->QueryUnsigned64Attribute("u64", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, static_cast<uint64_t>(42));
}

TEST_F(QueryUnsigned64AttributeTest_84, ReadsUnsigned64AttributeMaxValue_84) {
    // 2^64 - 1
    XMLElement* root = ParseSingleElement("<root u64='18446744073709551615'/>");

    uint64_t value = 0;
    const XMLError err = root->QueryUnsigned64Attribute("u64", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

TEST_F(QueryUnsigned64AttributeTest_84, ReadsUnsigned64AttributeSetViaSetAttribute_84) {
    XMLElement* root = ParseSingleElement("<root/>");

    const uint64_t expected = 1234567890123456789ULL;
    root->SetAttribute("u64", expected);

    uint64_t value = 0;
    const XMLError err = root->QueryUnsigned64Attribute("u64", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, expected);
}

TEST_F(QueryUnsigned64AttributeTest_84, ReturnsWrongTypeForNonNumericValue_84) {
    XMLElement* root = ParseSingleElement("<root u64='not_a_number'/>");

    uint64_t value = 0;
    const XMLError err = root->QueryUnsigned64Attribute("u64", &value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(QueryUnsigned64AttributeTest_84, ReturnsWrongTypeForNegativeNumberString_84) {
    XMLElement* root = ParseSingleElement("<root u64='-1'/>");

    uint64_t value = 0;
    const XMLError err = root->QueryUnsigned64Attribute("u64", &value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}
